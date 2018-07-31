#include <iostream>
using std::cout;
using std::endl;

#include <TRandom3.h>
#include "TH1D.h"

#include "../getSdHists.C"
//#include "../ntupleDefinition.h"
#include "../ntupleDefinition.h"
#include "../commonUtility.h"
#include "../jzWeight.h"
#include "unfoldingUtil.h"

#include "../JssUtils.h"
#include <TPaletteAxis.h>
#include "systematicsTool.h"

double statFrac = 001;
bool doUnfData = true ;

int lowPtBin = 1;  int highPtBin = 13;
int nPtPannels = highPtBin-lowPtBin+1;

bool isTooSmall(TH2D* hEntries=0, int recoVarX=0, int recoVarY=0, int minEntries=10);
void getMCspectra(int kSample=kPP, int icent=0, int etaBin=0, TH2D* hmcRaw=0,  TH2D* hmcTruth=0, TF1* ptScale=0, int nSys=-1);
void getDATAspectra(int kSample=kPP, int icent=0, int etaBin=0, TH2D* hdataRaw=0, int nSys=0);

TH1D* getVariedHist(TH1D* hin=0, double variation=0);
//bool isTooSmall(TH2D* hEntries=0, int recoVarX=0, int recoVarY=0, int minEntries=10);

float flucCut = 0.3;
void removeFluc2(TH2* h=0);

void getMcWeights(int kSample = kPP, int icent=0, int etaBin=2, float weightCut = 10, int nSys=-1) { 
  
  TH1::SetDefaultSumw2();
  
  int nXbins;
  double xBin[30];
  getXbin(nXbins, xBin, 77);
  cout << " nXbins = " << nXbins << endl;
  cout << " xBin = " << xBin[0] << ",   " << xBin[1] << ",   " <<xBin[2] << ", ..." <<endl;


  int nYbins ;
  double yBin[200] ;

  getYbin(nYbins, yBin, 772);
  cout << " nYbins = " << nYbins << endl;
  cout << " yBin = " << yBin[0] << ",   " << yBin[1] << ",   " <<yBin[2] << ", ..." <<endl;
  
  TH2D* hTemp = new TH2D("hptTemp","", nXbins, xBin, nYbins, yBin);

  int i = icent;


  // MC 
  TH2D* hmcRaw   = (TH2D*)hTemp->Clone(Form("hmcRaw_kSample%d_icent%d",kSample,i));
  TH2D* hmcTruth = (TH2D*)hTemp->Clone(Form("hmcTruth_kSample%d_icent%d",kSample,i));
  TH2D* hdataRaw = (TH2D*)hTemp->Clone(Form("hdataRaw_kSample%d_icent%d",kSample,i));

  getMCspectra   ( kSample, icent, etaBin, hmcRaw, hmcTruth, 0, nSys);
  getDATAspectra ( kSample, icent, etaBin, hdataRaw, nSys);

  
  for ( int ix= 1 ; ix <= nXbins; ix++) {
    for ( int iy= 1 ; iy <= nYbins; iy++) {
      //      if ( hmcRaw->GetBinContent(ix,iy) == 0 )  cout << "MC :found a null bin ix, iy = " << ix<<", "<<iy<< endl;
      //      if ( hdataRaw->GetBinContent(ix,iy) == 0 )  cout << "DATA :found a null bin ix, iy = " << ix<<", "<<iy<< endl;
    }
  }
  
  //  scaleInt(hmcRaw);
  //  scaleInt(hdataRaw);

  TH2D* hRatioRaw = (TH2D*)hdataRaw->Clone(Form("hRatioRaw_kSample%d_icent%d",kSample,i));
  hRatioRaw->Divide(hmcRaw);
  removeFluc2(hRatioRaw);
  TH2D* hRatioSmooth2 = (TH2D*)hRatioRaw->Clone(Form("hRatioSmooth2_kSample%d_icent%d",kSample,i));
  hRatioSmooth2->Smooth();

  TH2D* hmcRawSmooth = (TH2D*)hmcRaw->Clone(Form("%s_smooth",hmcRaw->GetName()));
  TH2D* hdataRawSmooth = (TH2D*)hdataRaw->Clone(Form("%s_smooth",hdataRaw->GetName()));
  
  //  scaleInt(hmcRawSmooth);
  //  scaleInt(hdataRawSmooth);

  hmcRawSmooth->Smooth();
  hdataRawSmooth->Smooth();
  TH2D* hRatioSmoothRaw = (TH2D*)hdataRawSmooth->Clone(Form("hRatioSmoothRaw_kSample%d_icent%d",kSample,i));
  hRatioSmoothRaw->Divide(hmcRawSmooth);
  
  TH2D* hRatioSmooth = (TH2D*)hRatioSmoothRaw->Clone(Form("hRatioSmooth_kSample%d_icent%d",kSample,i));
  
  for ( int ix= 1 ; ix<= nXbins; ix++) {
    for ( int iy= 1 ; iy<= nYbins; iy++) {
      if ( hRatioSmooth->GetBinContent( ix, iy ) > weightCut ) 
	hRatioSmooth->SetBinContent(ix, iy, weightCut ); 
      if ( hRatioSmooth->GetBinContent( ix, iy ) < 0.2 ) 
	hRatioSmooth->SetBinContent(ix, iy, 0.2 ); 
    }
  }
  
  TCanvas* c1=  new TCanvas("c1","",500,500);
  makeEfficiencyCanvas(c1,1, 0.0, 0.01, 0.2, 0.25, 0.01);
  c1->cd(1);
  TH1D* ptmc = (TH1D*)hmcRaw->ProjectionX("ptmc");
  TH1D* ptdata = (TH1D*)hdataRaw->ProjectionX("ptdata");
  handsomeTH1(ptmc,1);
  handsomeTH1(ptdata,2);
  ptmc->SetAxisRange(1e-6,1e8,"Y");
  ptmc->SetYTitle("dN/dp_{T}^{Reco}");
  ptmc->Draw(); 
  ptdata->Draw("same");
  gPad->SetLogy();
  drawCentrality(kSample, icent, 0.6,0.86,1,24);

  TLegend *leg1 = new TLegend(0.60,0.5583593,1,0.8023161,NULL,"brNDC");

  easyLeg(leg1,"Mass integrated");
  leg1->AddEntry(ptdata, "Data","pl");
  leg1->AddEntry(ptmc, "MC","pl");
  leg1->Draw();
  ATLASLabel(0.22, 0.88, "Internal");//, "Pb+Pb  #sqrt{#font[12]{s_{NN}}} = 5.02 TeV, 0.49 nb^{-1}", kBlack);

  c1->cd(2);
  TH1D* hptRatio = (TH1D*)ptdata->Clone("hptRatio");
  hptRatio->Divide(ptmc);
  if ( kSample == 0) hptRatio->SetAxisRange(0,1e5,"Y");

  hptRatio->SetXTitle("p_{T} (GeV)");
  hptRatio->SetYTitle("Data/MC");
  fixedFontHist(hptRatio,3,2,20);
  hptRatio->SetNdivisions(505,"X");
  hptRatio->Draw();
  
  c1->SaveAs(Form("reweightFactors/pTreweighting_kSample%d_icent%d_etaBin%d.pdf",kSample,icent,etaBin));
  TF1* fit;
  
  if ( kSample == kPP ) {
    hptRatio->Fit("pol2","","",100,900);
    fit = new TF1("myFit","[0]+ [1]*x + [2]*x*x",100,900);
    fit->SetParameter(0, hptRatio->GetFunction("pol2")->GetParameter(0));
    fit->SetParameter(1, hptRatio->GetFunction("pol2")->GetParameter(1));
    fit->SetParameter(2, hptRatio->GetFunction("pol2")->GetParameter(2));
  }
  else {
    hptRatio->Fit("pol1","","",100,700);
    fit = new TF1("myFit","[0]+ [1]*x",100,900);
    fit->SetParameter(0, hptRatio->GetFunction("pol1")->GetParameter(0));
    fit->SetParameter(1, hptRatio->GetFunction("pol1")->GetParameter(1));
  }
  fit->SetName("fitFunction");

  c1->SaveAs(Form("reweightFactors/pTreweighting_kSample%d_icent%d_etaBin%d_fit.pdf",kSample,icent,etaBin));

  TH2D* hmcPtCorr   = (TH2D*)hTemp->Clone(Form("hmcRawPtCorr_kSample%d_icent%d",kSample,i));
  TH2D* hmcTruthPtCorr = (TH2D*)hTemp->Clone(Form("hmcTruthPtCorr_kSample%d_icent%d",kSample,i));

  getMCspectra   ( kSample, icent, etaBin,  hmcPtCorr, hmcTruthPtCorr,fit, nSys);



  TCanvas* c1ptCorr=  new TCanvas("c1ptCorr","",500,500);
  makeEfficiencyCanvas(c1ptCorr,1, 0.05, 0.01, 0.1, 0.3, 0.01);
  c1ptCorr->cd(1);
  TH1D* ptmcCorr = (TH1D*)hmcPtCorr->ProjectionX("ptmcCorr");
  handsomeTH1(ptmcCorr,1);
  cleverRangeLog(ptmcCorr,10,1e-7);
  ptmcCorr->Draw();
  ptdata->Draw("same");
  gPad->SetLogy();
  c1ptCorr->cd(2);
  TH1D* hptRatioPtCorr = (TH1D*)ptdata->Clone("hptRatioPtcorr");
  hptRatioPtCorr->Divide(ptmcCorr);
  hptRatioPtCorr->Draw();

  

  TCanvas* c15=  new TCanvas("c15","",500,500);
  makeEfficiencyCanvas(c15,1, 0.05, 0.01, 0.1, 0.3, 0.01);
  c15->cd(1);
  TH1D* h1mcAllPt = (TH1D*)hmcPtCorr->ProjectionY("hmcPtCorrAllPt");
  TH1D* h1dataAllPt = (TH1D*)hdataRaw->ProjectionY("hdataRawAllPt");
  float tempMax = cleverRange(h1mcAllPt,10,1);
  //  float tempMax = cleverRange(h1mcAllPt,100,1e-8);
  //  h1mcAllPt->SetAxisRange(1,tempMax*10,"Y");
  handsomeTH1(h1mcAllPt,1);
  handsomeTH1(h1dataAllPt,2);
  fixedFontHist(h1mcAllPt,2.5,2,20);
  h1mcAllPt->Draw();
  h1dataAllPt->Draw("same");
  gPad->SetLogy();
  drawCentrality(kSample, icent, 0.70,0.86,1,24);
  TLegend *leg2 = new TLegend(0.1871854,0.6894175,0.7049639,0.9033743,NULL,"brNDC");
  easyLeg(leg2,"After p_{T} weighting");
  leg2->AddEntry(ptdata, "Data","pl");
  leg2->AddEntry(ptmc, "MC","pl");
  leg2->Draw();
  c15->cd(2);
  TH1D* hmptRatioPtAll = (TH1D*)h1dataAllPt->Clone("hmptRatioPtAll");
  hmptRatioPtAll->Divide(h1mcAllPt);
  TH1D* hmptRatioPtAllsmooth = (TH1D*)hmptRatioPtAll->Clone("hmptRatioPtAllsmooth");

  hmptRatioPtAllsmooth->Smooth();
  hmptRatioPtAll->SetAxisRange(0,5,"Y");
  hmptRatioPtAll->SetXTitle("m/p_{T}^{Reco}");
  hmptRatioPtAll->SetYTitle("Data/MC");
  hmptRatioPtAll->SetNdivisions(505,"X");
  fixedFontHist(hmptRatioPtAll,3,2,20);
  hmptRatioPtAll->Draw();
  hmptRatioPtAllsmooth->Draw("same hist");
  jumSun(-.2,1,0.35,1);
  
  TH1D* hsmooVarP = getVariedHist(hmptRatioPtAllsmooth,0.5);
  TH1D* hsmooVarM = getVariedHist(hmptRatioPtAllsmooth,-0.5);

  handsomeTH1( hsmooVarP,4);
  handsomeTH1( hsmooVarM,kGreen+4);

  hsmooVarP->SetLineWidth(2);
  hsmooVarM->SetLineWidth(2);
  hsmooVarP->SetLineStyle(9);
  hsmooVarM->SetLineStyle(6);

  c15->SaveAs(Form("reweightFactors/MassIntreweighting_etaBin%d_kSample%d_icent%d.pdf",etaBin,kSample,icent));

  TCanvas* c16 = new TCanvas("c16","",500,500);

  cleverRange(hmptRatioPtAllsmooth,3);
  hmptRatioPtAllsmooth->SetAxisRange(-0.07,0.3,"X");
  if ( kSample == 1) hmptRatioPtAllsmooth->SetAxisRange(-0.18,0.3,"X");
  jumSun(-.2,1,0.35,1);
  hmptRatioPtAllsmooth->SetXTitle("m/p_{T}");
  hmptRatioPtAllsmooth->SetYTitle("Data/MC");
  hmptRatioPtAllsmooth->Draw("hist");
  jumSun(-0.18,1,0.3,1);
  hmptRatioPtAll->Draw("same");
  hsmooVarP->Draw("same hist");
  hsmooVarM->Draw("same hist");
  drawCentrality(kSample, icent, 0.50,0.86,1,24);
  
  TLegend *leg3 = new TLegend(0.523618,0.6186667,0.959799,0.832,NULL,"brNDC");
  easyLeg(leg3,"Reweight factor");
  leg3->AddEntry(hsmooVarP, "Varied by +50%","l");
  leg3->AddEntry(hmptRatioPtAll, "Nominal","l");
  leg3->AddEntry(hsmooVarM, "Varied by -50%","l");
  leg3->Draw();

  ATLASLabel(0.18, 0.88, "Internal",0.05);//, "Pb+Pb  #sqrt{#font[12]{s_{NN}}} = 5.02 TeV, 0.49 nb^{-1}", kBlack);

  c16->SaveAs(Form("reweightFactors/MassIntreweighting_etaBin%d_kSample%d_icent%d_ratioOnly.pdf",etaBin,kSample,icent));
  


  TH1D* hRatio[20];
  TH1D* hRatioSmoPtBin[20];
  TCanvas* c2=  new TCanvas("c2","",1200,600);
  c2->Divide(5,2);
  for ( int ix = 1 ; ix<= nXbins ; ix++) {
    c2->cd(ix);
    TH1D* h1mc = (TH1D*)hmcPtCorr->ProjectionY(Form("hmcPtCorr_%d",ix),ix,ix);
    TH1D* h1data = (TH1D*)hdataRaw->ProjectionY(Form("hdataRaw_%d",ix),ix,ix);
    //    scaleInt(h1data);
    //    scaleInt(h1mc);
    handsomeTH1(h1mc,1);
    handsomeTH1(h1data,2);
    cleverRangeLog(h1mc,10,1e-7);
    h1mc->Draw();
    h1data->Draw("same");
    gPad->SetLogy();

    if ( ix==1)    drawCentrality(kSample, icent, 0.60,0.86,1,24);
    drawBin(xBin,ix,"GeV",0.4,0.78,49,16);
    //    drawBin(xBin,ix,"GeV",0.16 + (0.05* (ix==lowPtBin)), 0.78,1,16);
    
    hRatio[ix] = (TH1D*)h1data->Clone(Form("hRatio_ix%d",ix));
    hRatio[ix]->Divide(h1mc);
    hRatioSmoPtBin[ix] = (TH1D*)hRatio[ix]->Clone(Form("hRatioSmoPtBin_ix%d",ix));
    hRatioSmoPtBin[ix]->Smooth();
  }
  
  TCanvas* c3=  new TCanvas("c3","",1200,600);
  c3->Divide(5,2);
  for ( int ix = 1 ; ix<= nXbins ; ix++) {
    c3->cd(ix);
    hRatio[ix]->SetYTitle("Data/MC");
    //    cleverRangeLog(hRatio[ix],1000,1e-9);
    hRatio[ix]->SetAxisRange(0,5,"Y");
    hRatio[ix]->Draw();
    hRatioSmoPtBin[ix]->Draw("same hist");
    if ( ix==1)    drawCentrality(kSample, icent, 0.60,0.86,1,24);
    drawBin(xBin,ix,"GeV",0.4,0.78,49,16);
    jumSun(-0.5,1,0.5,1);
    //    drawBin(xBin,ix,"GeV",0.16 + (0.05* (ix==lowPtBin)), 0.78,1,16);
    //    hRatio[ix]->Fit("gaus");
    //    gPad->SetLogy();
  }


  TH2D* hFacRatio = new TH2D(Form("factorizedRatio_kSample%d_icent%d",kSample,i),"", nXbins, xBin, nYbins, yBin);
  TH2D* hFacRatioVarP = new TH2D(Form("factorizedRatioVarP_kSample%d_icent%d",kSample,i),"", nXbins, xBin, nYbins, yBin);
  TH2D* hFacRatioVarM = new TH2D(Form("factorizedRatioVarM_kSample%d_icent%d",kSample,i),"", nXbins, xBin, nYbins, yBin);
  TH2D* hFacRatio2 = new TH2D(Form("factorizedRatio2_kSample%d_icent%d",kSample,i),"", nXbins, xBin, nYbins, yBin);
  TH1D* hTemp1x  = (TH1D*)hFacRatio->ProjectionX("htemp1x");
  TH1D* hTemp1y  = (TH1D*)hFacRatio->ProjectionY("htemp1y");
  for ( int ii = 1 ; ii<=hFacRatio->GetNbinsX() ; ii++) {
    for ( int jj = 1 ; jj<=hFacRatio->GetNbinsY() ; jj++) {
      double recoPt = hTemp1x->GetBinCenter(ii);
      double ptWeight = fit->Eval(recoPt);

      double recoM  = hTemp1y->GetBinCenter(jj);

      int theYBin = hmptRatioPtAll->FindBin( recoM);
      double mWeight = hmptRatioPtAll->GetBinContent(theYBin);
      hFacRatio->SetBinContent(ii,jj, ptWeight * mWeight);

      double mWeightVarP = hsmooVarP->GetBinContent(theYBin);
      hFacRatioVarP->SetBinContent(ii,jj, ptWeight * mWeightVarP);

      double mWeightVarM = hsmooVarM->GetBinContent(theYBin);
      hFacRatioVarM->SetBinContent(ii,jj, ptWeight * mWeightVarM);

      int theYBin2 = hRatioSmoPtBin[ii]->FindBin(recoM);
      double mWeight2 = hRatioSmoPtBin[ii]->GetBinContent(theYBin2);
      hFacRatio2->SetBinContent(ii,jj, ptWeight * mWeight2);
    }
  }

  
  TFile * fout;
  if ( nSys < 0 ) 
    fout = new TFile(Form("reweightFactors/reweightingFactor_etaBin%d_weightCut%d_flucCut%.1f_factorized_v60.root",etaBin, (int)weightCut,(float)flucCut),"update");
  else
    fout = new TFile(Form("reweightFactors/reweightingFactor_etaBin%d_weightCut%d_flucCut%.1f_factorized_v60_nSys%d.root",etaBin, (int)weightCut,(float)flucCut,nSys),"update");
  
  hmcPtCorr->Write("",TObject::kOverwrite);
  hmcTruth->Write("",TObject::kOverwrite);
  hdataRaw->Write("",TObject::kOverwrite);
  hmcRawSmooth->Write("",TObject::kOverwrite);
  hdataRawSmooth->Write("",TObject::kOverwrite);
  hdataRawSmooth->Write("",TObject::kOverwrite);
  hRatioSmoothRaw->Write("",TObject::kOverwrite);
  hRatioSmooth->Write("",TObject::kOverwrite);
  hRatioRaw->Write("",TObject::kOverwrite);
  hRatioSmooth2->Write("",TObject::kOverwrite);
  hFacRatio->Write("",TObject::kOverwrite);
  hFacRatioVarP->Write("",TObject::kOverwrite);
  hFacRatioVarM->Write("",TObject::kOverwrite);
  hFacRatio2->Write("",TObject::kOverwrite);
  
  fout->Close();
  
}


void getMCspectra(int kSample, int icent, int etaBin,  TH2D* hmcRaw,  TH2D* hmcTruth, TF1* ptScale, int nSys) {
  
  TRandom3 genRandom;
  genRandom.SetSeed(200);

  TH1::SetDefaultSumw2();
  hmcRaw->Reset();
  hmcTruth->Reset();

  TF1* fjmscal[30];
  if( nSys == 300) {   
    TFile* fin = new TFile(Form("fJMScalibration_kSample%d_icent%d_mPt2.root",kSample,icent));
    for ( int ix = lowPtBin ; ix<=highPtBin ; ix++) {
      fjmscal[ix] = (TF1*)fin->Get(Form("f1_kSample%d_icent%d_ix%d",kSample,icent,ix));
    }
  }

  int nXbinsCal;
  double xBinCal[30];
  getXbin(nXbinsCal, xBinCal, 1);
  TH1D* xBinTemp = new TH1D("xBinTemp","", nXbinsCal, xBinCal);


  TString jz2;
  TString jz3;
  TString jz4;
  if ( kSample == kPbPb ) {
    if ( (nSys >= 0)&&(nSys<200)) {
      jz2 = jz2PbPbStringSys;
      jz3 = jz3PbPbStringSys;
      jz4 = jz4PbPbStringSys;
    }
    else {
      jz2 = jz2PbPbString;
      jz3 = jz3PbPbString;
      jz4 = jz4PbPbString;
    }
  }
  else if ( kSample == kPP ) {
    if ( (nSys >= 0)&&(nSys<200)) {
      jz2 = jz2PPStringSys;
      jz3 = jz3PPStringSys;
      jz4 = jz4PPStringSys;
    }
    else {
      jz2 = jz2PPString;
      jz3 = jz3PPString;
      jz4 = jz4PPString;
    }
  }
  
  RtrkProvider rtrkProv;
  rtrkProv.Setup(kSample, icent);



  TH1D* hFcalReweight;
  if ( kSample == kPbPb ) {
    TFile* fcal = new TFile("reweightFactors/FCal_HP_v_MB_weights.root");
    hFcalReweight = (TH1D*)fcal->Get("FCal_HP_v_MBOV_weights");
  }
  
  jetSubStr  myJetMc;
  TBranch  *b_myJetSubMc;

  TFile* checkEntries = new TFile(Form("checkEntry/entries_kSample%d_icent%d_optX1_optY2.root",kSample,icent));
  TH2D* recoEntries_jz2 = (TH2D*)checkEntries->Get("reco_jz2");
  TH2D* recoEntries_jz3 = (TH2D*)checkEntries->Get("reco_jz3");
  TH2D* recoEntries_jz4 = (TH2D*)checkEntries->Get("reco_jz4");
  TH2D* hRecoEntries;

  float ptSys;
  TBranch *b_ptSys;
  TString jetSysName = getPtSysName(nSys);
  cout << " jetSysName = " << jetSysName << endl;

  cout << " Setting tree branch address..." << endl;
  TFile* fjz2 = new TFile(Form("../ntuples/%s",jz2.Data()));
  TTree* tr2 = (TTree*)fjz2->Get("tr");
  tr2->SetBranchAddress("jets", &(myJetMc.cent), &b_myJetSubMc);
  if ( (nSys>=0) && (nSys<200) )
    tr2->SetBranchAddress(jetSysName.Data(), &ptSys, &b_ptSys);

  TFile* fjz3 = new TFile(Form("../ntuples/%s",jz3.Data()));
  TTree* tr3 = (TTree*)fjz3->Get("tr");
  tr3->SetBranchAddress("jets", &(myJetMc.cent), &b_myJetSubMc);
  if ( (nSys>=0) && (nSys<200) )
    tr3->SetBranchAddress(jetSysName.Data(), &ptSys, &b_ptSys);

  TFile* fjz4 = new TFile(Form("../ntuples/%s",jz4.Data()));
  TTree* tr4 = (TTree*)fjz4->Get("tr");
  tr4->SetBranchAddress("jets", &(myJetMc.cent), &b_myJetSubMc);
  if ( (nSys>=0) && (nSys<200) )
    tr4->SetBranchAddress(jetSysName.Data(), &ptSys, &b_ptSys);


  for ( int ijz =2 ; ijz<=4 ; ijz++) {
    TTree* tr;
    //    TH2D* hRecoEntries;
    double jzNorm=0;
    if ( ijz==2)  {
      tr = tr2;
      jzNorm = hi9EvtWgtJZ2;
      hRecoEntries = recoEntries_jz2;
    }
    else if ( ijz==3)  {
      tr = tr3;
      jzNorm = hi9EvtWgtJZ3;
      hRecoEntries = recoEntries_jz3;
    }
    else if ( ijz==4)  {
      tr = tr4;
      jzNorm = hi9EvtWgtJZ4;
      hRecoEntries = recoEntries_jz4;
    }
    
    cout << "Scanning JZ"<<ijz<<" file.  Total events = " << tr->GetEntries() << endl;
    for (Int_t i= 0; i<tr->GetEntries() ; i++) {
      if ( i > tr->GetEntries() * statFrac ) break;
      if (i%2==0)  continue;

      tr->GetEntry(i);

      if ( ! passEvent(myJetMc, icent, true) ) // isMC = true
        continue;
      if ( !passEtaCut(myJetMc, etaBin) )
        continue;
      
      double genX;
      double genY;
      double recoX  = -10000; 
      double recoY  = -10000; 

      genX = myJetMc.genPt;
      genY = myJetMc.genMass /  myJetMc.genPt;
      recoX = myJetMc.recoPt;
      recoY = myJetMc.recoMass / myJetMc.recoPt;

      if ( genY < 0 ) genY = 0.000001;
      
      double fcalWeight = 1.0;
      if ( kSample==kPbPb) {
	//        fcalWeight = hFcalReweight->GetBinContent(hFcalReweight->GetXaxis()->FindBin(myJetMc.fcalet));
        //      cout <<" fcal, weight = "<<myJetMc.fcalet<<", "<<fcalWeight<<endl;
      }
      
      double ptWeight = 1;
      if ( ptScale != 0) {
	ptWeight = ptScale->Eval(recoX);
      }
      
      if ( (nSys>=0) && (nSys<200) ) {
	double extraPtScale = ptSys / myJetMc.recoPt ;
	recoX = recoX * extraPtScale ; //pt
	myJetMc.recoPt = ptSys;  // New pT!!!
	myJetMc.recoMass = myJetMc.recoMass * extraPtScale ; // new mass so that m/pT is invariant.
      }
      
      if (nSys==200) { // JMR
	// smear by 20% the recoY
	double theCenter = genY * getJMSscale( kSample, icent, myJetMc.recoPt);
	double recoDev = recoY - theCenter; 
	double theResol = getJMRsigma( kSample, icent, myJetMc.recoPt);
        double jmrUnc = getJmrUnc( kSample, icent, myJetMc.recoPt);
        double theVariation = sqrt ( (1 +jmrUnc)*(1+jmrUnc) - 1 );
	recoY = theCenter + recoDev * genRandom.Gaus(1, theVariation * theResol);  
	//	recoY = theCenter + recoDev * genRandom.Gaus(1, 0.66 * theResol);  
      }
      if (nSys==201) { // JMR HI
	// smear by 20% the recoY
	double theCenter = genY * getJMSscale( kSample, icent, myJetMc.recoPt);
	double recoDev = recoY - theCenter; 
	double theResol = getJMRsigma( kSample, icent, myJetMc.recoPt);
        double jmrUnc = getJmrUncHI( kSample, icent, myJetMc.recoPt);
        double theVariation = sqrt ( (1 +jmrUnc)*(1+jmrUnc) - 1 );
	recoY = theCenter + recoDev * genRandom.Gaus(1, theVariation * theResol);  
	//	recoY = theCenter + recoDev * genRandom.Gaus(1, 0.66 * theResol);  
      }
      if (nSys==210) { // JMS
	double theRtrk = rtrkProv.getR( myJetMc);
	recoY = recoY * theRtrk;
      }
      if (nSys==211) { // JMS
	recoY = recoY * 1.008;
      }
      if (nSys==213) { // JMS by Herwig
	double theRtrk = rtrkProv.getRPyHer(myJetMc);
	recoY = recoY / theRtrk;
      }
      if (nSys==217) { // JMS by Herwig
	recoY = recoY * 1.05;
      }
      if (nSys==300) { // JMS calibration
	int xx = xBinTemp->FindBin( myJetMc.recoPt);
	if ( xx > 11 )  xx = 11;
	if ( xx < 5 )  xx = 5;
	float mptVal = recoY;
	if (mptVal <0 )  mptVal = 0;

	double theFac = 1;
	if ( recoY < 0 )
	  theFac = 1;
	else if ( recoY > 0.25 )
	  theFac = fjmscal[xx]->Eval(0.25);
	else
	  theFac = fjmscal[xx]->Eval(recoY);

	recoY = recoY / theFac;
      }

      
      hmcRaw->Fill( recoX, recoY, myJetMc.weight * jzNorm * fcalWeight * ptWeight);
      hmcTruth->Fill( genX, genY, myJetMc.weight * jzNorm * fcalWeight * ptWeight);
    }
  }
  
}

void getDATAspectra(int kSample, int icent, int etaBin, TH2D* hdataRaw, int nSys) { 

  TH1::SetDefaultSumw2();
  hdataRaw->Reset();
  TString fname;
  if ( kSample == kPbPb ) {
    fname = pbpbDataString; 
  }
  else if ( kSample == kPP) {
    fname = ppDataString;
  }

  TF1* fjmscal[30];
  if( nSys == 300) {
    TFile* fin = new TFile(Form("fJMScalibration_kSample%d_icent%d_num.root",kSample,icent));
    for ( int ix = lowPtBin ; ix<=highPtBin ; ix++) {
      fjmscal[ix] = (TF1*)fin->Get(Form("f1_kSample%d_icent%d_ix%d",kSample,icent,ix));
    }
    }
  int nXbinsCal;
  double xBinCal[30];
  getXbin(nXbinsCal, xBinCal, 1);
  TH1D* xBinTemp = new TH1D("xBinTemp","", nXbinsCal, xBinCal);
  
  
  TFile* fData = new TFile(Form("../ntuples/%s",fname.Data()));
  TTree* tr = (TTree*)fData->Get("tr");
  jetSubStr myJet;
  TBranch       *b_myJet;
  tr->SetBranchAddress("jets", &(myJet.cent), &b_myJet);
  if ( kSample == kPP )  cout << " pp " ;
  else if ( kSample == kPbPb) cout << " PbPb " ;
  cout << "data entries = " << tr->GetEntries() << endl;
  
  for (Int_t i= 0; i<tr->GetEntries() ; i++) {
    tr->GetEntry(i);
    if ( i > tr->GetEntries() * statFrac) break;

    if ( ! passEvent(myJet, icent, false) ) // isMC = false
      continue;
    if ( !passEtaCut(myJet, etaBin) )
      continue;
    
    
    double recoX  = -10000;
    double recoY  = -10000;
    recoX = myJet.recoPt;
    recoY = myJet.recoMass / myJet.recoPt;
    
    if (nSys==300) { // JMS calibration
      int xx = xBinTemp->FindBin( myJet.recoPt);
      if ( xx > 11 )  xx = 11;
      if ( xx < 5 )  xx = 5;
      float mptVal = recoY;
      if (mptVal <0 )  mptVal = 0;
      double theFac = 1;
      if ( recoY < 0 )
	theFac = 1; 
      else if ( recoY > 0.25 )
	theFac = fjmscal[xx]->Eval(0.25);
      else
	theFac = fjmscal[xx]->Eval(recoY);
      recoY = recoY / theFac;
    }

    
    hdataRaw->Fill ( recoX, recoY);
  }
  
}


bool isTooSmall(TH2D* hEntries, int recoVarX, int recoVarY, int minEntries) {
  int theBin = hEntries->FindBin(recoVarX, recoVarY);
  if (  hEntries->GetBinContent(theBin) < minEntries )
    return true;
  
  return false;

}


TH1D* getVariedHist(TH1D* hin, double variation)  {
  
  TH1D* hout = (TH1D*)hin->Clone(Form("%s_var%.2f",hin->GetName(),variation));
  hout->Reset();
  for ( int i = 1 ; i<= hin->GetNbinsX() ; i++) {
    double yin = hin->GetBinContent(i);
    double newY = (yin - 1 ) * (1+variation) + 1; 
    hout->SetBinContent(i, newY);
  }
  
  return hout;
  
  
}

void removeFluc2(TH2* h) {
  for ( int i =1 ;  i<=h->GetNbinsX() ; i++) {
    for ( int j =1 ;  j<=h->GetNbinsY() ; j++) {
      double val  = h->GetBinContent(i,j);
      double error  = h->GetBinError(i,j);
      if ( error > val * flucCut )   {
	h->SetBinContent(i,j,1);
	h->SetBinError(i,j, error/val);
      }
    }
  }
}
