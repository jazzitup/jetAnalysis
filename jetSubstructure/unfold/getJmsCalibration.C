double fracStst=0.1;
bool doCal=0;

#if !(defined(__CINT__) || defined(__CLING__)) || defined(__ACLIC__)
#include <iostream>
using std::cout;
using std::endl;



#include "TRandom.h"
#include "TH1D.h"
#include "TH2D.h"


#include "../getSdHists.C"
#include "../ntupleDefinition.h"
//#include "../ntupleDefinition_v50.h"
#include "../commonUtility.h"
#include "../jzWeight.h"
#endif

//==============================================================================
// Global definitions
//==============================================================================

#include "../JssUtils.h"
#include <TPaletteAxis.h>
#include "unfoldingUtil.h"
#include <TGraphErrors.h>


struct valErr {
  double val;
  double err;
};

int lowPtBin = 1;

valErr getMeanValue(TH1D* h1, double x1, double x2) {
  valErr ret;
  
  TH1D* htemp = (TH1D*)h1->Clone("htemp");

  int ix1 = htemp->FindBin(x1);
  int ix2 = htemp->FindBin(x2);
  
  for ( int ix = 1 ; ix<= htemp->GetNbinsX() ; ix++) { 
    
    if ( (ix >= ix1) && ( ix<ix2) )  continue;
    
    htemp->SetBinContent(ix,0);
    htemp->SetBinError(ix,0);
  }
  ret.val = htemp->GetMean();
  ret.err = htemp->GetMeanError();

  return ret;
}

bool selectedPt(int ipt = 0) {
  if ( ipt == lowPtBin ) return true;
  if ( ipt == 7 ) return true;
  if ( ipt == 11 ) return true;
  return false;
}




void getDist( int kSample = kPP, int icent = 0, int optX=1, int optY=2, TH2D* hJMS=0, TH2D* hJMR=0, TH2D* hJES=0, TH2D* hJER=0, TH2D* hFineMpt=0, bool doReweight = true);

void getJmsCalibration(int kSample = kPP, int icent=0, int optX =79, int optY=79, bool doReweight=false) {
  TH1::SetDefaultSumw2();
  int nXbins;
  double xBin[30];
  getXbin(nXbins, xBin, optX);
  cout << " nXbins = " << nXbins << endl; 
  cout << " xBin = " << xBin[0] << ",   " << xBin[1] << ",   " <<xBin[2] << ", ..." <<endl;
  
  int highPtBin = nXbins-1;
  
  int vColor[20] =   {1,20, 2, 38,40,41,4,44,46,6,4};
  int vStyle[20] =   {20,21,25,23,29,33,28,47,43};
  //  int vStylePP[20] = {24,25,26,32,30,37,38,46,42};

  int nYbins ;
  double yBin[30] ;
  getYbin(nYbins, yBin, optY);
  
  /*  nYbins = 8;
  yBin[0] = 0;
  yBin[1] = 0.01;
  yBin[2] = 0.02;
  yBin[3] = 0.04;
  yBin[4] = 0.07;
  yBin[5] = 0.1;
  yBin[6] = 0.15;
  yBin[7] = 0.24;
  */


  TH2D* hJMS = new TH2D("hJMS",";p_{T} (GeV) ; m/p_{T}", nXbins, xBin, nYbins, yBin);
  TH2D* hJMR = (TH2D*)hJMS->Clone("hJMR");
  TH2D* hJES = (TH2D*)hJMS->Clone("hJES");
  TH2D* hJER = (TH2D*)hJMS->Clone("hJER");
  TH2D* hFineMpt = new TH2D("hFineMpt",";p_{T} (GeV); m/p_{T}",nXbins, xBin, 1000,0.9,1.1);
  

  getDist(kSample, icent, optX, optY, hJMS, hJMR, hJES, hJER, hFineMpt, doReweight);

  
  TCanvas* c01 = new TCanvas("c01", "",800,400);
  c01->Divide(2,1);
  c01->cd(1);
  hJMS->Draw("colz");
  c01->cd(2);
  hJMR->Draw("colz");

  
  //  return;
  
  TCanvas* c2s = new TCanvas("c2s", "",500,500);
  TLegend *leg1s = new TLegend(0.5061446,0.6142105,0.9599598,0.915789,NULL,"brNDC");
  easyLeg(leg1s,"Jet p_{T}");
  
  TF1* f1[20];
  TGraphErrors* gr[30];
  TGraphErrors* grInv[30];
  double Rx[20];
  double Ry[20];
  double RxErr[20];
  double RyErr[20];

  double RyInv[20];
  double RyInvErr[20];

  for ( int ix = lowPtBin ; ix<=highPtBin ; ix++) { 
    TH1D* hs = (TH1D*)hJMS->ProjectionY(Form("hs_ix%d",ix),ix,ix);
    handsomeTH1(hs,vColor[ix-lowPtBin]);
    hs->SetXTitle("[m/p_{T}]^{2}_{Truth}");
    hs->SetYTitle("JMS^2");
    hs->SetAxisRange(0.001,0.239,"X");
    hs->SetAxisRange(0.8,1.2,"Y");
    hs->SetNdivisions(505,"X");
    hs->SetNdivisions(505,"Y");
    if ( ix == lowPtBin) hs->Draw();
    else hs->Draw("same");

    TH1D* hFineMpt1d = (TH1D*)hFineMpt->ProjectionY(Form("_%d",ix),ix,ix);
    int nPoints=0;
    for ( int im = 2 ; im <= hs->GetNbinsX() ; im++) {
      valErr meanPair = getMeanValue(hFineMpt1d, hs->GetBinLowEdge(im), hs->GetBinLowEdge(im+1));
      cout << " Range = " <<  hs->GetBinLowEdge(im) <<" - " << hs->GetBinLowEdge(im+1) << endl;
      cout << "mean = " << meanPair.val << endl;
      
     
      /*  // sqrt  
      Rx[nPoints] = meanPair.val * sqrt(hs->GetBinContent(im));
      RxErr[nPoints] = meanPair.err * sqrt(hs->GetBinContent(im));
      Ry[nPoints] = sqrt(hs->GetBinContent(im));
      RyErr[nPoints] = hs->GetBinError(im) / ( 2 * sqrt( Ry[nPoints] ) ) ;
      */

      Rx[nPoints] = meanPair.val * hs->GetBinContent(im);
      RxErr[nPoints] = meanPair.err * hs->GetBinContent(im);
      Ry[nPoints] = hs->GetBinContent(im);
      RyErr[nPoints] = hs->GetBinError(im);

      RyInv[nPoints] = 1./Ry[nPoints];
      RyInvErr[nPoints] = RyInv[nPoints] * ( RyErr[nPoints] / Ry[nPoints] ) ;
      
      nPoints++;
    }
    gr[ix] = new TGraphErrors(nPoints, Rx,Ry,RxErr,RyErr);
    grInv[ix] = new TGraphErrors(nPoints, Rx,RyInv,RxErr,RyInvErr);
    handsomeTG1(gr[ix],vColor[ix-lowPtBin]);
    handsomeTG1(grInv[ix],vColor[ix-lowPtBin]);
    
  }
  jumSun(0,1,0.36,1);
  drawCentrality(kSample, icent, 0.2,0.85,1,25);
  //  drawText("<p_{T}^{Reco}/p_{T}^{Truth}>", 0.2,0.78,1,25);
  leg1s->Draw();
 
  c2s->SaveAs(Form("jmsCalib/jes_kSample%d_icent%d-3.pdf",kSample,icent));
  
  
  TLegend *leg2 = new TLegend(0.4673663,0.5040816,0.8668024,0.9040816,NULL,"brNDC");
  easyLeg(leg2,"Jet p^{Reco}_{T}");

  TCanvas* c4 = new TCanvas("c4","",1000,500);
  c4->Divide(2,1);
  c4->cd(1);
  TH1D* htemp = new TH1D("htemp",";[m/p_{T}]^{2} * R;R",1000,1,1.1);
  htemp->SetAxisRange(0.98,1.015,"Y");
  htemp->DrawCopy();
  //  gPad->SetLogy();
  for ( int ix = lowPtBin ; ix<=highPtBin ; ix++) {
    gr[ix]->Draw("same p");
    leg2->AddEntry(gr[ix], textBin2(xBin,ix,"GeV").Data(),"pl" );
    //    f1[ix] = new TF1(Form("f1_kSample%d_icent%d_ix%d",kSample,icent,ix),"[0] + [1]/sqrt(x) + [2]/x + [3]/sqrt(x*x*x)",0.01,0.24);
    //    f1[ix] = new TF1(Form("f1_kSample%d_icent%d_ix%d",kSample,icent,ix),"[0] + TMath::Exp(-x/[1])",0.01,0.24);
    //  f1[ix] = new TF1(Form("f1_kSample%d_icent%d_ix%d",kSample,icent,ix),"[0] + [1]*log(x+1) + [2]*log(x+1)*log(x+1) + [3]*pow(log(x+1),3)",1,1.1);
    //    f1[ix] = new TF1(Form("f1_kSample%d_icent%d_ix%d",kSample,icent,ix),"[0] + [1]*log(x+0.05) + [2]*log(x+0.05)*log(x+0.05) + [3]*pow(log(x+0.05),3) + [4]*pow(log(x+0.05),4)",1,1.1);
    //    f1[ix] = new TF1(Form("f1_kSample%d_icent%d_ix%d",kSample,icent,ix),"[0] + [1]*log(x+0.1) + [2]*log(x+0.1)*log(x+0.1) + [3]*pow(log(x+0.1),3)",1,1.1);
    //    f1[ix] = new TF1(Form("f1_kSample%d_icent%d_ix%d",kSample,icent,ix),"[0] + [1]*log(x+0.1) + [2]*log(x+0.1)*log(x+0.1) + [3]*pow(log(x+0.1),3) + [4]*pow(log(x+0.1),4) +  [5]*pow(log(x+0.1),5)",1,1.1);
    //f1[ix] = new TF1(Form("f1_kSample%d_icent%d_ix%d",kSample,icent,ix),"[0] + [1]*log(x+1) + [2]*log(x+1)*log(x+1) + [3]*pow(log(x+1),3) + [4]*pow(log(x+1),4) + [5]*pow(log(x+1),5) + [6]*pow(log(x+1),6)",1,1.1);
    //    f1[ix] = new TF1(Form("f1_kSample%d_icent%d_ix%d",kSample,icent,ix),"[0] + [1]*x + [2]*x*x + [3]*x*x*x + [4]*x*x*x*x",0.9,1.1);
    //f1[ix] = new TF1(Form("f1_kSample%d_icent%d_ix%d",kSample,icent,ix),"[0] + [1]*x");

    f1[ix] = new TF1(Form("f1_kSample%d_icent%d_ix%d",kSample,icent,ix),"[0] + [1]*exp(x) + [2]*exp(x)*exp(x) + [3]*pow(exp(x),3) + [4]*pow(exp(x),4) +  [5]*pow(exp(x),5)",1,1.1);

    if ( !doCal) { 
      //      f1[ix]->SetParameter(0,1);

      gr[ix]->Fit(f1[ix]);
      gr[ix]->GetFunction(f1[ix]->GetName())->SetLineColor(vColor[ix-lowPtBin]);
    }
    
  }
  //  leg2->Draw();

  c4->cd(2);
  htemp->SetAxisRange(0,3.2,"Y");
  htemp->SetYTitle("1/R");
  htemp->DrawCopy();
  for ( int ix = lowPtBin ; ix<=highPtBin ; ix++) {
    grInv[ix]->Draw("same p");
  }
  leg2->Draw();

  if ( !doCal) {
    TFile* foutJMS = new TFile(Form("jmsCalib/jmsCorrectionFactor_kSample%d_icent%d_optX%d_optY%d.root",kSample,icent,optX,optY),"recreate");
    for ( int ix = lowPtBin ; ix<=highPtBin ; ix++) {
      gr[ix]->GetFunction(f1[ix]->GetName())->Write();
    }
    foutJMS->Close();
  }
  
  // resolution 

  TCanvas* c3a = new TCanvas("c3a", "",500,500);

  for ( int ix = lowPtBin ; ix<=highPtBin ; ix++) { 
    TH1D* hr = (TH1D*)hJMR->ProjectionY(Form("hr_ix%d",ix),ix,ix);
    handsomeTH1(hr,vColor[ix-lowPtBin]);
    hr->SetXTitle("(m/p_{T})^{Truth}");
    hr->SetYTitle("JMR");
    hr->SetAxisRange(0.001,0.239,"X");
    hr->SetAxisRange(0,0.01,"Y");
    hr->SetNdivisions(505,"X");
    hr->SetNdivisions(505,"Y");
    if ( ix == lowPtBin) hr->Draw();
    else hr->Draw("same");
  }
  drawCentrality(kSample, icent, 0.2,0.85,1,25);
  drawText("#sigma[p_{T}^{Reco}/p_{T}^{Truth}]", 0.2,0.78,1,25);
  leg1s->Draw();
  c3a->SaveAs(Form("jmsCalib/jer_kSample%d_icent%d-3.pdf",kSample,icent));


  return;
  
  TCanvas* c2 = new TCanvas("c2", "",500,500);
  //  TLegend *leg1 = new TLegend(0.5220884,0.2,0.9859438,0.4968421,NULL,"brNDC");
  TLegend *leg1 = new TLegend(0.2108434,0.56,0.6084337,0.7347368,NULL,"brNDC");
  easyLeg(leg1,"Jet p_{T}");
  

  c2->SetLeftMargin(0.20);
 
  for ( int ix = lowPtBin ; ix<=highPtBin ; ix++) { 
    
    if ( !selectedPt(ix) ) continue;
 
    TH1D* hs = (TH1D*)hJMS->ProjectionY(Form("hm_ix%d",ix),ix,ix);
    handsomeTH1(hs,vColor[ix-lowPtBin],1,vStyle[ix-lowPtBin]);
    hs->SetXTitle("(m/p_{T})_{Truth}");
    hs->SetYTitle("<(m/p_{T})^{2}_{Reco}>");
    //hs->SetYTitle("#sqrt{<(m/p_{T})^{2}_{Reco}>}");
    hs->GetYaxis()->SetTitleOffset(1.67);
    hs->SetAxisRange(0.001,0.239,"X");
    hs->SetAxisRange(0,16.0,"Y");
    hs->SetNdivisions(505,"X");
    hs->SetNdivisions(505,"Y");

    if ( ix == lowPtBin) hs->Draw();
    else hs->Draw("same");

    leg1->AddEntry(hs, textBin2(xBin,ix,"GeV").Data(),"pl" );
  }
  jumSun(0,1,0.24,1);
  ATLASLabel(0.23,0.88,"Simulation Preliminary",0.05,0.16);
  drawText("#sqrt{#font[12]{s}} = 5.02 TeV", 0.23, 0.82,1,25);
  drawCentrality(kSample, icent, 0.23,0.76,1,25);
  
  if ( !doCal )
    drawText("Before Calibration",0.2,0.77,4,22);
  else 
    drawText("After mass Calibration",0.2,0.77,4,22);
  
  
  //  drawText("<m/p_{T}]>", 0.2,0.78,1,25);
  leg1->Draw();
  c2->SaveAs(Form("jmsCalib/jms_kSample%d_icent%d-3.pdf",kSample,icent));


  TCanvas* c3 = new TCanvas("c3", "",500,500);

  for ( int ix = lowPtBin ; ix<=highPtBin ; ix++) { 
    if ( !selectedPt(ix) ) continue;

    TH1D* hr = (TH1D*)hJMR->ProjectionY(Form("hr_ix%d",ix),ix,ix);
    handsomeTH1(hr,vColor[ix-lowPtBin],1,vStyle[ix-lowPtBin]);

    handsomeTH1(hr,vColor[ix-lowPtBin],1,vStyle[ix-lowPtBin]);
    hr->SetXTitle("(m/p_{T})_{Truth}");
    hr->SetYTitle("#sigma[(m/p_{T})^{2}_{Reco}]");
    hr->GetYaxis()->SetTitleOffset(1.4);
    hr->SetAxisRange(0.001,0.239,"X");
    hr->SetAxisRange(0,0.027,"Y");
    hr->SetNdivisions(505,"X");
    hr->SetNdivisions(505,"Y");
    if ( ix == lowPtBin) hr->Draw();
    else hr->Draw("same");
  }

  //  jumSun(0,0,0.36,0);
  ATLASLabel(0.23,0.88,"Simulation Preliminary",0.05,0.16);
  drawText("#sqrt{#font[12]{s}} = 5.02 TeV", 0.23, 0.82,1,25);
  drawCentrality(kSample, icent, 0.23,0.76,1,25);
  //  drawText("#sigma[m/p_{T}]", 0.2,0.78,1,25);
  c3->SaveAs(Form("jmsCalib/jmr_kSample%d_icent%d-3.pdf",kSample,icent));


}

void getDist( int kSample, int icent, int optX, int optY, TH2D* hJMS, TH2D* hJMR, TH2D* hJES, TH2D* hJER, TH2D* hFineMpt, bool doReweight ) { 
  
  double radius = 0.4;
  
  TH1::SetDefaultSumw2();
  TString jz2;
  TString jz3;
  TString jz4;
  if ( kSample == kPbPb ) {
    if ( radius==0.4 ) {
      // v50
      //      jz2 = "jetSubstructure_MC_HION9_pbpb_v50_jz2.root";
      //      jz3 = "jetSubstructure_MC_HION9_pbpb_v50_jz3.root";
      //      jz4 = "jetSubstructure_MC_HION9_pbpb_v50_jz4.root";
      jz2 = "jetSubstructure_pbpbMC_HION9_jz2_v51_april124.root";
      jz3 = "jetSubstructure_pbpbMC_HION9_jz3_v51_april124.root";
      jz4 = "jetSubstructure_pbpbMC_HION9_jz4_v51_april124.root";

    }
  }
  else if ( kSample == kPP ) {
    if ( radius==0.4 ) {
      //  jz2 = "jetSubstructure_MC_HION9_pp_v50_jz2.root";
      //      jz3 = "jetSubstructure_MC_HION9_pp_v50_jz3.root";
      //      jz4 = "jetSubstructure_MC_HION9_pp_v50_jz4.root";
      jz2 = "jetSubstructure_ppMC_HION9_jz2_v52_april124.root";
      jz3 = "jetSubstructure_ppMC_HION9_jz3_v52_april124.root";
      jz4 = "jetSubstructure_ppMC_HION9_jz4_v52_april124.root";
    }
  }
  
  TH1D* hFcalReweight;
  if ( kSample == kPbPb ) {
    //    TFile* fcal = new TFile("reweightFactors/FCal_HP_v_MB_weights.root");
    //    hFcalReweight = (TH1D*)fcal->Get("FCal_HP_v_MBOV_weights");
  }
  
  
  TH2D* hReweight;
  if ( doReweight ) {
    hReweight = getRewTable(kSample, icent);
  }
  
  
  jetSubStr  myJetMc;
  TBranch  *b_myJetSubMc;
  
  cout << " Setting tree branch address..." << endl;
  TFile* fjz2 = new TFile(Form("../ntuples/%s",jz2.Data()));
  TTree* tr2 = (TTree*)fjz2->Get("tr");
  tr2->SetBranchAddress("jets", &(myJetMc.cent), &b_myJetSubMc);
  
  
  TFile* fjz3 = new TFile(Form("../ntuples/%s",jz3.Data()));
  TTree* tr3 = (TTree*)fjz3->Get("tr");
  tr3->SetBranchAddress("jets", &(myJetMc.cent), &b_myJetSubMc);

  TFile* fjz4 = new TFile(Form("../ntuples/%s",jz4.Data()));
  TTree* tr4 = (TTree*)fjz4->Get("tr");
  tr4->SetBranchAddress("jets", &(myJetMc.cent), &b_myJetSubMc);

  int nXbins;
  double xBin[30];
  getXbin(nXbins, xBin, optX);

  int highPtBin = nXbins-1;

  int nYbins ;
  double yBin[30] ;
  getYbin(nYbins, yBin, optY);

  TH1D* xBinTemp = new TH1D("xBinTemp","", nXbins, xBin);
  TH1D* yBinTemp = new TH1D("yBinTemp","", nYbins, yBin);
  
  

  //  TH1D* hDist[20][20]; // gen pT  // gen m/pT
  //  TH1D* hDistReco[20][20]; // gen pT  // gen m/pT
  TH1D* hDistJms[20][20]; // gen pT  // gen m/pT
  TH1D* hDistMpt2[20][20]; // gen pT  // gen m/pT
  for ( int ix = 0 ; ix <= nXbins+1   ;  ix++) {
    for ( int iy = 0 ; iy <= nYbins+1 ; iy++) {
      //      hDist[ix][iy] = new TH1D(Form("hDist_ix%d_iy%d",ix,iy),";(m/p_{T})^{Reco} - (m/p_{T})^{Truth};", 100,-3,10);
      //      hDistJms[ix][iy] = new TH1D(Form("hDistJms_ix%d_iy%d",ix,iy),";p_{T}^{Reco}/p_{T}^{Truth};", 100,0,2);
      //      hDist[ix][iy] = new TH1D(Form("hDist_ix%d_iy%d",ix,iy),";(m/p_{T})^{Reco} - (m/p_{T})^{Truth};", 100,-0.05,0.15);
      //      hDistReco[ix][iy] = new TH1D(Form("hDistReco_ix%d_iy%d",ix,iy),";(m/p_{T})^{Reco} - (m/p_{T})^{Truth};", 200,-0.2,0.4);

      /*      m/pT^2
	      
	      if ( iy >= 6)  hDistJms[ix][iy] = new TH1D(Form("hDistJms_ix%d_iy%d",ix,iy),";[m/p_{T}]^2_{Reco} / [m/p_{T}]^2_{Truth};", 50,-0.5,3);
	      else if ( iy >= 4)  hDistJms[ix][iy] = new TH1D(Form("hDistJms_ix%d_iy%d",ix,iy),";[m/p_{T}]^2_{Reco} / [m/p_{T}]^2_{Truth};", 40,-1,10);
	      else if ( iy >= 3)  hDistJms[ix][iy] = new TH1D(Form("hDistJms_ix%d_iy%d",ix,iy),";[m/p_{T}]^2_{Reco} / [m/p_{T}]^2_{Truth};", 30,-5,40);
	      else hDistJms[ix][iy] = new TH1D(Form("hDistJms_ix%d_iy%d",ix,iy),";[m/p_{T}]^2_{Reco} / [m/p_{T}]^2_{Truth};", 30,-20,100);
      */
      
      if ( iy <= 2 ) 
	hDistJms[ix][iy] = new TH1D(Form("hDistJms_ix%d_iy%d",ix,iy),";[m/p_{T}]^2_{Reco} / [m/p_{T}]^2_{Truth};", 120,0.98,1.02);
      else if ( iy <= 4 ) 
	hDistJms[ix][iy] = new TH1D(Form("hDistJms_ix%d_iy%d",ix,iy),";[m/p_{T}]^2_{Reco} / [m/p_{T}]^2_{Truth};", 60,0.98,1.02);
      else 
	hDistJms[ix][iy] = new TH1D(Form("hDistJms_ix%d_iy%d",ix,iy),";[m/p_{T}]^2_{Reco} / [m/p_{T}]^2_{Truth};", 30,0.98,1.02);

      //      hDistMpt2[ix][iy] = new TH1D(Form("hDistMpt2_ix%d_iy%d",ix,iy),";[m/p_{T}]^2_{Reco};", 100,-0.02,0.08);
      hDistMpt2[ix][iy] = new TH1D(Form("hDistMpt2_ix%d_iy%d",ix,iy),";[m/p_{T}]^2_{Reco};", 100,0.9,1.1);

    }
  }

  TF1* fjmscal[30];
  if ( doCal) {  
    
    TFile* fin = new TFile(Form("jmsCalib/jmsCorrectionFactor_kSample0_icent%d_optX%d_optY%d.root", icent,optX,optY));
    for ( int ix = lowPtBin  ; ix<=highPtBin ; ix++) { 
      //      fjmscal[ix] = (TF1*)fin->Get(Form("f1_kSample%d_icent%d_ix%d",kSample,icent,ix));
      fjmscal[ix] = (TF1*)fin->Get(Form("f1_kSample0_icent0_ix%d",ix));
    }
  }
  
  for ( int ijz =2 ; ijz<=4 ; ijz++) { 
    TTree* tr;
    TH2D* hRecoEntries;
    double jzNorm=0;
    if ( ijz==2)  {
      tr = tr2;   
      jzNorm = hi9EvtWgtJZ2; 
    }
    else if ( ijz==3)  {
      tr = tr3;   
      jzNorm = hi9EvtWgtJZ3; 
    }
    else if ( ijz==4)  {
      tr = tr4;   
      jzNorm = hi9EvtWgtJZ4; 
    }
    cout << "Scanning JZ"<<ijz<<" file.  Total events = " << tr->GetEntries() << endl;
    
    for (Int_t i= 0; i<tr->GetEntries() ; i++) {
      if ( i > tr->GetEntries() * fracStst ) continue;
      tr->GetEntry(i);
      
      if ( passJesEvent(myJetMc, icent) == false ) // true = isMC
	continue;
      
      double recoVarX, truthVarX;
      getXvalues( recoVarX, truthVarX, myJetMc, optX);
      
      double recoVarY, truthVarY;
      getYvalues( recoVarY, truthVarY, myJetMc, optY);
      
      double fcalWeight = 1.0; 
      if ( kSample==kPbPb) {
	//	fcalWeight = hFcalReweight->GetBinContent(hFcalReweight->GetXaxis()->FindBin(myJetMc.fcalet));
      }
      
      // Data/MC reweighting factors 
      double rewFact = 1; 
      if ( doReweight) { 
	//	  int rewBin = hReweight->FindBin(myJetMc.recoPt, myJetMc.recoMass);
	int rewBin = hReweight->FindBin(myJetMc.recoPt, myJetMc.recoMass/myJetMc.recoPt);
	rewFact = hReweight->GetBinContent(rewBin);
      }
      
      int xx = xBinTemp->FindBin( recoVarX);
      //      int xx = xBinTemp->FindBin( truthVarX);
      
      int yy = yBinTemp->FindBin( truthVarY);
      //int yy = yBinTemp->FindBin( recoVarY);
      
      double calFac = 1;
      if (  ( xx <= highPtBin  ) && ( xx>=lowPtBin) ) { 
	if ( doCal) {
	  if ( recoVarY < 0 ) 
	    calFac = fjmscal[xx]->Eval(0.000001);
	  else if ( recoVarY > 0.25 ) 
	    calFac = fjmscal[xx]->Eval(0.25);
	  else 
	    calFac = fjmscal[xx]->Eval(recoVarY);

	  recoVarY = recoVarY / calFac;
	}
      }
      //      cout << " calFac = " << calFac << endl;
      float theWeight = myJetMc.weight * rewFact * jzNorm;
      hDistJms[xx][yy]->Fill( recoVarY / truthVarY, theWeight );
      hDistMpt2[xx][yy]->Fill( recoVarY, theWeight );

      hFineMpt->Fill( truthVarX, truthVarY, theWeight);
      
    }
    
  }
  
  for ( int ix = 1 ; ix <= nXbins ; ix++) {
    for ( int iy = 1 ; iy <= nYbins ; iy++)  {
      //      hDist[ix][iy]->Fit("gaus");
      //      hDistReco[ix][iy]->Fit("gaus");
      int peakBin  = hDistJms[ix][iy]->GetMaximumBin();
      double peak =  hDistJms[ix][iy]->GetBinCenter(peakBin);
      double sigma = hDistJms[ix][iy]->GetRMS();
      cout << " peak = " << peak << endl;
      cout << " sigma = " << sigma << endl;;
      hDistJms[ix][iy]->Fit("gaus","","",peak-sigma,peak+sigma);
      //      hDistJms[ix][iy]->Fit("gaus");

      if ( hDistJms[ix][iy]->GetFunction("gaus") == NULL ) {
	hJMS->SetBinContent(ix,iy,-100);
	hJMS->SetBinError(ix,iy,-100);
	hJMR->SetBinContent(ix,iy,-100);
	hJMR->SetBinError(ix,iy,-100);
      }
      else {
	float theReco =  hDistJms[ix][iy]->GetFunction("gaus")->GetParameter(1) ;
	float theRecoErr = hDistJms[ix][iy]->GetFunction("gaus")->GetParError(1);
	float theJMS = hDistJms[ix][iy]->GetFunction("gaus")->GetParameter(1);
	float theJMSerr = hDistJms[ix][iy]->GetFunction("gaus")->GetParError(1);
	float theJMR = hDistJms[ix][iy]->GetFunction("gaus")->GetParameter(2);
	float theJMRerr = hDistJms[ix][iy]->GetFunction("gaus")->GetParError(2);
	// fill square root of it. 

	hJMS->SetBinContent(ix,iy,theReco);
	hJMS->SetBinError(ix,iy,theRecoErr);
	hJMR->SetBinContent(ix,iy,theJMR);
	hJMR->SetBinError(ix,iy,theJMRerr);
      }
    }
  }
  /*
  for ( int ix = 1 ; ix <= nXbins ; ix++) {
    for ( int iy = 1 ; iy <= nYbins ; iy++)  {
      hDistJms[ix][iy]->Fit("gaus");
      if ( hDistJms[ix][iy]->GetFunction("gaus") == NULL ) {
        hJES->SetBinContent(ix,iy,-100);
        hJES->SetBinError(ix,iy,-100);
        hJER->SetBinContent(ix,iy,-100);
        hJER->SetBinError(ix,iy,-100);
      }
      else {
        float theJMS = hDistJms[ix][iy]->GetFunction("gaus")->GetParameter(1);
        float theJMSerr = hDistJms[ix][iy]->GetFunction("gaus")->GetParError(1);
        float theJMR = hDistJms[ix][iy]->GetFunction("gaus")->GetParameter(2);
        float theJMRerr = hDistJms[ix][iy]->GetFunction("gaus")->GetParError(2);
        hJES->SetBinContent(ix,iy,theJMS);
        hJES->SetBinError(ix,iy,theJMSerr);
        hJER->SetBinContent(ix,iy,theJMR);
        hJER->SetBinError(ix,iy,theJMRerr);
      }
    }
  }
  
  */
  TCanvas* cDist = new TCanvas("cDist","",1200,500);
  cDist->Divide(5,2);
  for ( int ix = 1 ; ix <= nXbins ; ix++) {
    for ( int iy = 2 ; iy <= nYbins ; iy++)  {
      cDist->cd(iy-1);
      cleverRange(hDistJms[ix][iy],1.5,0.00000001);
      hDistJms[ix][iy]->Draw();
      drawBinPt(xBin,ix,"GeV", 0.25 ,0.88,1,18);
      drawBinMpt2(yBin,iy,"", 0.25 ,0.8,1,18);
    }
    cDist->SaveAs(Form("jmsCalib/m2scale_pt%d_kSample%d.png",ix,kSample));
  }

  TCanvas* cDistMpt = new TCanvas("cDistMpt","",1200,500);
  cDistMpt->Divide(5,2);
  for ( int ix = 1 ; ix <= nXbins ; ix++) {
    for ( int iy = 2 ; iy <= nYbins ; iy++)  {
      cDistMpt->cd(iy-1);
      cleverRange(hDistMpt2[ix][iy],1.5,0.00000001);
      hDistMpt2[ix][iy]->Draw();
      drawBinPt(xBin,ix,"GeV", 0.25 ,0.88,1,18);
      drawBinMpt2(yBin,iy,"", 0.25 ,0.8,1,18);
    }
    cDist->SaveAs(Form("jmsCalib/mpt2reco_pt%d_kSample%d.png",ix,kSample));
  }

  
  TFile* foutJMS = new TFile(Form("jmsCalib/jms_kSample%d_icent%d_optX%d_optY%d.root",kSample,icent,optX,optY),"recreate");
  for ( int ix = 1 ; ix <= nXbins ; ix++) {
    for ( int iy = 2 ; iy <= nYbins ; iy++)  {
      //      hDist[ix][iy]->Write();
      hDistJms[ix][iy]->Write();
      hDistMpt2[ix][iy]->Write();
    }
  }
  hFineMpt->Write();
  foutJMS->Close();
  
}
 
