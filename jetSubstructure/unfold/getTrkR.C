#include <iostream>
using std::cout;
using std::endl;

#include "TRandom.h"
#include "TH1D.h"
#include "../getSdHists.C"
#include "../ntupleDefinition_v50.h"
#include "../commonUtility.h"
#include "../jzWeight.h"
#include "unfoldingUtil.h"
#include "../JssUtils.h"
#include <TPaletteAxis.h>
#include <TGraphErrors.h>

double statUsed = 1;


void getMCR(int kSample=kPP, int icent=0,  int im=0, TH2D* hmc=0);

void getDATAR (int kSample=kPP, int icent=0, int im=0,  TH2D* hdata=0);
void getMeanPt(int kSample=kPP, int icent=0, TH1D* hMean=0);

TH1D* getVariedHist(TH1D* hin=0, double variation=0);

double findPeak(TF1* f) { 
  double v1 = f->GetParameter(1);
  double v2 = f->GetParameter(2);
  // Peak = ([1] - 0.22278) 
  // https://root.cern.ch/root/html528/TMath.html#TMath:Landau
  return (v1-0.22278);
}
/*  double step = 0.001;
  double maxY =  -10000;
  double peakPosition  = 0;
  for ( double xx = low ; xx<= high ; xx = xx+step){ 
    double yy = f->Eval(xx);
    if ( yy > maxY)  {
      maxY  = yy; 
      peakPosition = xx;
    }
  }
  return peakPosition;
*/


double errPeak(TF1* f) { 
  double v1 = f->GetParameter(1);
  double v2 = f->GetParameter(2);
  double e1 = f->GetParError(1);
  //  double e2 = f->GetParError(2);
  // Peak = ([1] - 0.22278)* [2]
  // https://root.cern.ch/root/html528/TMath.html#TMath:Landau
  //  double ec1 =  (v1-0.22278)*e2  ;
  //  double ec2 =  e1 * v2 ; 
  return e1; 
}

void getTrkR(int kSample = kPbPb, int icent=0, int im=1) {   // opt1 : mass,   opt2 : m/pT  
  TH1::SetDefaultSumw2();

  int optX = 1;    int optY = 2;  
  
  int nXbins = 7;
  double xBin[30] = { 120,140,160,180,210,250,350,800}; 
  int lowPtBin = 1;
  int highPtBin = 7;
  

  int nPtPannels = highPtBin-lowPtBin+1;


  int nYbins ;
  double yBin[30] ;
  getYbin(nYbins, yBin, optY);

  int nRbins = 35;
  TH2D* hTemp = new TH2D("rTemp","", nRbins, 0,20, nXbins, xBin);
  TH1D* hTrkR = new TH1D(Form("hTrkR_kSample%d_icent%d",kSample,icent),";p_{T} (GeV/c);R^{trk};",nXbins, xBin);
  //  TH1D* hTrkR = new TH1D(Form("hTrkR_kSample%d_icent%d",kSample,icent),";p_{T} (GeV/c);R^{trk};",100,120,500);
  // MC 
  double Rx[30];
  double Ry[30];
  double RxErr[30];
  double RyErr[30];
  

  TH2D* hmc = (TH2D*)hTemp->Clone(Form("hmc_kSample%d_icent%d",kSample,icent));
  TH2D* hdata = (TH2D*)hTemp->Clone(Form("hdata_kSample%d_icent%d",kSample,icent));
  TH1D* h1mc[20];
  TH1D* h1data[20];

  getMCR   ( kSample, icent, im, hmc);
  getDATAR ( kSample, icent, im, hdata);

  TCanvas* c1 = new TCanvas("c1","",400,400);
  TH1D* hMeanPt = new TH1D("hmeanpt","",nXbins,xBin);
  getMeanPt(kSample,icent,hMeanPt);
  hMeanPt->DrawCopy();

  
  TCanvas* c2 =  new TCanvas("c2","",1200,400);
  makeMultiPanelCanvas(c2,nPtPannels, 1, 0.0, 0.01, 0.3, 0.2, 0.05);
  for ( int ix = lowPtBin ; ix<= highPtBin ; ix++) {
    c2->cd(ix - lowPtBin + 1);
    h1mc[ix] = (TH1D*)hmc->ProjectionX(Form("h1mc_ipt%d",ix),ix,ix);
    h1data[ix] = (TH1D*)hdata->ProjectionX(Form("h1data_ipt%d",ix),ix,ix);

    scaleInt(h1mc[ix]);
    scaleInt(h1data[ix]);
    
    handsomeTH1(h1mc[ix],1);
    handsomeTH1(h1data[ix],2);

    cleverRange(h1mc[ix],2.);
    /*   TF1 *f1mc = new TF1(Form("fitH1mc_ix%d",ix),"[0]*TMath::Landau(x-[3],[1],[2])",0,20);
    f1mc->SetParameter(0,1);
    f1mc->SetParameter(1,2);
    f1mc->SetParameter(2,2);
    f1mc->SetParameter(3,1);

    TF1 *f1data = new TF1(Form("fitH1data_ix%d",ix),"[0]*TMath::Landau(x-[3],[1],[2])",0,20);
    f1data->SetParameter(0,1);
    f1data->SetParameter(1,2);
    f1data->SetParameter(2,2);
    f1data->SetParameter(3,1);
    */
    TF1 *f1mc = new TF1(Form("fitH1mc_ix%d",ix),"[0]*TMath::Landau(x,[1],[2])",0,20);
    f1mc->SetParameter(0,2);
    f1mc->SetParameter(1,2.4);
    f1mc->SetParameter(2,0.6);
    //    f1mc->SetParameter(3,1);

    TF1 *f1data = new TF1(Form("fitH1data_ix%d",ix),"[0]*TMath::Landau(x,[1],[2])",0,20);
    f1data->SetParameter(0,2);
    f1data->SetParameter(1,2.4);
    f1data->SetParameter(2,0.6);
    //    f1data->SetParameter(3,1);


    h1mc[ix]->Fit(f1mc->GetName(),"","",0,10);
    h1data[ix]->Fit(f1data->GetName(),"","",0,10);
    h1mc[ix]->GetFunction(f1mc->GetName())->SetLineColor(1);
    h1data[ix]->GetFunction(f1data->GetName())->SetLineColor(2);
    h1mc[ix]->Draw();
    h1data[ix]->Draw("same");

    // Peak = ([1] - 0.22278)* [2] 
    // https://root.cern.ch/root/html528/TMath.html#TMath:Landau

    double mcPeak = findPeak(f1mc);
    double dataPeak = findPeak(f1data);
    double mcPeakErr = errPeak(f1mc);
    double dataPeakErr = errPeak(f1data);
    double peakRatio = dataPeak/mcPeak; 
    double peakRatioErr =  peakRatio * sqrt (  pow(mcPeakErr/mcPeak,2) + pow(dataPeakErr/dataPeak,2) );

    cout << ix <<"th bin: "<< endl;
    cout << " MC peak  : " << mcPeak << endl;
    cout << " Data peak  : " << dataPeak << endl;
    cout << "Peak ratio = " << dataPeak/mcPeak << endl;
    cout << "MC maean, RMS = " << h1mc[ix]->GetMean() << ",   " << h1mc[ix]->GetRMS() << endl;
    cout << "DATA maean, RMS = " << h1data[ix]->GetMean() << ",   " << h1data[ix]->GetRMS() << endl;
    cout << "DATA/MC mean = " << h1data[ix]->GetMean()/ h1mc[ix]->GetMean() << endl;
    double meanRatio = f1data->Mean(0,20) / f1mc->Mean(0,20);
    if ( ix== lowPtBin)    drawCentrality(kSample, icent, 0.60,0.86,1,24);
    drawBin(xBin,ix,"GeV",0.4,0.79,49,16);
    drawText(Form("R_{fit} = %.2f", (float)peakRatio), 0.35, 0.72,1,20);
    //    drawText(Form("R_{mean} = %.2f", (float)meanRatio), 0.35, 0.65,1,20);
    
	     //    c2->cd(ix - lowPtBin +1 + nPtPannels);
	     //    TH1D* hratio = (TH1D*)h1data[ix]->Clone(Form("ratio_%s",h1data[ix]->GetName()));
	     //   hratio->Divide(h1mc[ix]);
    //    hratio->SetAxisRange(0,2,"Y");
    ///    hratio->SetYTitle("Data/MC");
    //    hratio->Draw();
    //    jumSun(0,1,50,1);
    
    hTrkR->SetBinContent(ix, peakRatio);
    hTrkR->SetBinError(ix, peakRatioErr);
    
    Rx[ix-1] = hMeanPt->GetBinContent(ix);
    RxErr[ix-1] = hMeanPt->GetBinError(ix);
    Ry[ix-1] = peakRatio;
    RyErr[ix-1] = peakRatioErr;
  }
  c2->SaveAs(Form("pdfsJMS/JMS_kSample%d_cent%d_im%d.pdf",kSample,icent,im));
  TCanvas* c3 = new TCanvas("c3","",500,500);
  hTrkR->SetAxisRange(0.8,1.2,"Y");

  //  TF1* f1 = new TF1("f1","[0] +x*[1]",xBin[0], xBin[nXbins]);
  TF1* f1 = new TF1("f1","[0] +log(x)*[1] + log(x)*log(x)*[2]",xBin[0], xBin[nXbins]);
  //  hTrkR->Fit("f1");
  //  hTrkR->Fit("f1");
  handsomeTH1(hTrkR,0);
  hTrkR->Draw();
  f1->SetParameter(0,8.41757e-01); 
  f1->SetParameter(1,8.26199e-02);
  f1->SetParameter(2,-1.05534e-02);


  TGraphErrors* gr = new TGraphErrors(nXbins,Rx,Ry,RxErr,RyErr);
  gr->Fit("f1","","",125,500);
  //  gr->Fit("f1","O");
  gr->Draw("same p");
  jumSun(xBin[0],1, xBin[nXbins],1);
  drawCentrality(kSample, icent, 0.40,0.86,1,24);
  if ( im==1)  drawText("m/p_{T} < 0.06", 0.40,0.75,1,24);
  if ( im==2)  drawText("0.06 < m/p_{T} < 0.1", 0.40,0.75,1,24);
  if ( im==3)  drawText("0.1 < m/p_{T} < 0.15", 0.40,0.75,1,24);
  if ( im==4)  drawText("0.15 < m/p_{T}", 0.40,0.75,1,24);

  TF1* f2 = new TF1("f2","2- ([0] +log(x)*[1] + log(x)*log(x)*[2])",xBin[0], xBin[nXbins]);
  f2->SetParameter( 0, f1->GetParameter(0));  
  f2->SetParameter( 1, f1->GetParameter(1));  
  f2->SetParameter( 2, f1->GetParameter(2));
  f2->SetLineColor(2);
  f2->SetLineStyle(2);
  //  f2->Draw("same");
  c3->SaveAs(Form("pdfsJMS/trkR_kSample%d_cent%d_massBin%d.pdf",kSample,icent,im));

  TFile* fout = new TFile(Form("R_trk/Rtrk_kSample%d_cent%d_temp.root",kSample,icent),"update");
  gr->SetName(Form("hRtrk_im%d",im));
  f2->SetName(Form("rtrk_im%d",im));
  gr->Write("",TObject::kOverwrite);
  f2->Write("",TObject::kOverwrite);
  fout->Close();
}


void getMCR(int kSample, int icent, int im, TH2D* hmc) { 
  
  TH1::SetDefaultSumw2();
  hmc->Reset();

  TString jz2;
  TString jz3;
  TString jz4;
  if ( kSample == kPbPb ) {
    jz2 = "jetSubstructure_MC_HION9_pbpb_v50_jz2_april11.root";
    jz3 = "jetSubstructure_MC_HION9_pbpb_v50_jz3_april11.root";
    jz4 = "jetSubstructure_MC_HION9_pbpb_v50_jz4_april11.root";
  }
  else if ( kSample == kPP ) {
    jz2 = "jetSubstructure_MC_HION9_pp_v50_jz2_april11.root";
    jz3 = "jetSubstructure_MC_HION9_pp_v50_jz3_april11.root";
    jz4 = "jetSubstructure_MC_HION9_pp_v50_jz4_april11.root";
  }
  
  
  TH1D* hFcalReweight;
  if ( kSample == kPbPb ) {
    TFile* fcal = new TFile("reweightFactors/FCal_HP_v_MB_weights.root");
    hFcalReweight = (TH1D*)fcal->Get("FCal_HP_v_MBOV_weights");
  }
  
  jetSubStr  myJetMc;
  TBranch  *b_myJetSubMc;
  
  float trkJetPt;
  float trkJetMass;
  TBranch *b_trkJetPt;
  TBranch *b_trkJetMass;
  //  TString trkMassVar = Form("trkJetMass%d",ptCut);
  //  TString trkPtVar = Form("trkJetPt%d",ptCut);
  
  //  if ( ptCut ==1 ) 
  //    trkMassVar =  "chMassRaw"

  
  cout << " Setting tree branch address..." << endl;
  TFile* fjz2 = new TFile(Form("../ntuples/%s",jz2.Data()));
  TTree* tr2 = (TTree*)fjz2->Get("tr");
  tr2->SetBranchAddress("jets", &(myJetMc.cent), &b_myJetSubMc);
  //  tr2->SetBranchAddress(trkMassVar.Data(), &trkJetMass, &b_trkJetMass);
  //  tr2->SetBranchAddress(trkPtVar.Data(), &trkJetPt, &b_trkJetPt);
  
  TFile* fjz3 = new TFile(Form("../ntuples/%s",jz3.Data()));
  TTree* tr3 = (TTree*)fjz3->Get("tr");
  tr3->SetBranchAddress("jets", &(myJetMc.cent), &b_myJetSubMc);
  //  tr3->SetBranchAddress(trkMassVar.Data(), &trkJetMass, &b_trkJetMass);
  //  tr3->SetBranchAddress(trkPtVar.Data(), &trkJetPt, &b_trkJetPt);

  TFile* fjz4 = new TFile(Form("../ntuples/%s",jz4.Data()));
  TTree* tr4 = (TTree*)fjz4->Get("tr");
  tr4->SetBranchAddress("jets", &(myJetMc.cent), &b_myJetSubMc);
  //  tr4->SetBranchAddress(trkMassVar.Data(), &trkJetMass, &b_trkJetMass);
  //  tr4->SetBranchAddress(trkPtVar.Data(), &trkJetPt, &b_trkJetPt);

  for ( int ijz =2 ; ijz<=4 ; ijz++) {
    TTree* tr;
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
      if ( i > tr->GetEntries() * statUsed ) break;

      tr->GetEntry(i);

      if ( ! passEvent(myJetMc, icent, true) )        continue;
      //      if ( (ptCut != 1 ) && (trkJetMass < 0.2) )        continue;         // cut on trakc mass 
      
      double mpt =  myJetMc.recoMass / myJetMc.recoPt ;
      double recoMass = myJetMc.recoMass ;
      //      if (!( (recoMass>-100) && (recoMass<21)  ) )
      //	continue;
      
      if ( im != findMbin(mpt) )  	continue;
      
      double recoPt = myJetMc.recoPt;

      double theR = myJetMc.recoMass / myJetMc.recoChMassRcSubt ; 
      
      
      double fcalWeight = 1.0;
      if ( kSample==kPbPb) {
	fcalWeight = hFcalReweight->GetBinContent(hFcalReweight->GetXaxis()->FindBin(myJetMc.fcalet));
        //      cout <<" fcal, weight = "<<myJetMc.fcalet<<", "<<fcalWeight<<endl;
      }
      hmc->Fill(theR, recoPt, myJetMc.weight * jzNorm * fcalWeight);
      
    }
  }
  
}

void getDATAR(int kSample, int icent, int im,  TH2D* hdata) {

  TH1::SetDefaultSumw2();
  hdata->Reset();
  TString fname;
  if ( kSample == kPbPb ) {
    fname = "jetSubstructure_data_HION9_v50_r4_pbpb_apr11.root";
  }
  else if ( kSample == kPP) {
    fname = "jetSubstructure_data_HION9_v50_r4_pp_apr11.root";
  }
  
  TFile* fData = new TFile(Form("../ntuples/%s",fname.Data()));
  TTree* tr = (TTree*)fData->Get("tr");
  jetSubStr myJet;
  TBranch       *b_myJet;
  //  float trkJetPt;
  //  float trkJetMass;
  //  TBranch *b_trkJetPt;
  //  TBranch *b_trkJetMass;
  //  TString trkMassVar = Form("trkJetMass%d",ptCut);
  //  TString trkPtVar = Form("trkJetPt%d",ptCut);


  tr->SetBranchAddress("jets", &(myJet.cent), &b_myJet);
  //  tr->SetBranchAddress(trkPtVar.Data(), &trkJetPt, &b_trkJetPt);
  //  tr->SetBranchAddress(trkMassVar.Data(), &trkJetMass, &b_trkJetMass);

  if ( kSample == kPP )  cout << " pp " ;
  else if ( kSample == kPbPb) cout << " PbPb " ;
  cout << "data entries = " << tr->GetEntries() << endl;
  
  for (Int_t i= 0; i<tr->GetEntries() ; i++) {
    tr->GetEntry(i);
    if ( i > tr->GetEntries() * statUsed) break;

    if ( ! passEvent(myJet, icent, false) )       continue;
    //    if ( (ptCut != 1 ) && (trkJetMass < 0.2) )        continue;         // cut on trakc mass 

    double mpt = myJet.recoMass / myJet.recoPt;
    double recoMass = myJet.recoMass ;
    //    if (!( (recoMass>-100) && (recoMass<21)  ) )
    //      continue;
    
    if ( im != findMbin(mpt) )  	continue;
    
    
    double recoPt = myJet.recoPt;
    //    double theR = myJet.recoMass / trkJetMass;

    double theR = myJet.recoMass / myJet.recoChMassRcSubt ;
    
    hdata->Fill( theR, recoPt);
  }
  
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

void getMeanPt(int kSample, int icent, TH1D* hMean){ 
  TH1::SetDefaultSumw2();
  TString fname;
  if ( kSample == kPbPb ) {
    fname = "jetSubstructure_data_HION9_v50_r4_pbpb_apr11.root";
  }
  else if ( kSample == kPP) {
    fname = "jetSubstructure_data_HION9_v50_r4_pp_apr11.root";
  }

  TH1D* htempPt = (TH1D*)hMean->Clone("htempPt");
  TH1D* htempN = (TH1D*)hMean->Clone("htempN");
  htempPt->Reset();
  htempN->Reset();

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
    if ( i > tr->GetEntries() * statUsed) break;
    if ( ! passEvent(myJet, icent, false) )       continue;

    double mpt = myJet.recoMass / myJet.recoPt;

    htempPt->Fill(myJet.recoPt, myJet.recoPt);
    htempN->Fill(myJet.recoPt);
  }
  
  htempPt->Divide(htempN);
  hMean->Reset();
  hMean->Add(htempPt);  
}



