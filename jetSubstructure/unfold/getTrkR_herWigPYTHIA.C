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

double statUsed = 001;

int lowPtBin = 1;  int highPtBin = 13;

int nPtPannels = highPtBin-lowPtBin+1;

void getHerwigR(int kSample=kPbPb, int icent=0,  TH2D* hmc=0, int ptCut=6, TString varName="", int im=1 );
void getPYTHIAR(int kSample=kPbPb, int icent=0,  TH2D* hmc=0, int ptCut=6, TString varName="", int im=1);
TH1D* getVariedHist(TH1D* hin=0, double variation=0);
void getMeanPt(int kSample=kPP, int icent=0, TH1D* hMean=0);

double findPeak(TF1* f, double low =2,double high = 4 ) {
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

void getTrkR_herWigPYTHIA(int im=1)  {
  int kSample = kPP;
  int icent=0;
  int ptCut =1;
  
  TH1::SetDefaultSumw2();
  
  int optX = 1;    int optY = 2;  

  //  int nXbins;
  //  double xBin[30];
  //  getXbin(nXbins, xBin, optX);
  //  int lowPtBin = 6;
  //  int highPtBin = 11;
  //  int nPtPannels = highPtBin-lowPtBin+1;
  int nXbins = 7;
  double xBin[30] = { 120,140,160,180,210,250,350,500}; 
  //  double xBin[30] = { 120,140,160,180,210,250,350,800}; 
  int lowPtBin = 1;
  int highPtBin = nXbins;
  

  int nPtPannels = highPtBin-lowPtBin+1;


  int nYbins ;
  double yBin[30] ;
  getYbin(nYbins, yBin, optY);

  int nRbins = 15;
  TH2D* hTemp = new TH2D("rTemp","", nRbins, 0,8, nXbins, xBin);
  TH1D* hTrkR = new TH1D(Form("hTrkR_kSample%d_icent%d",kSample,icent),";p_{T} (GeV/c);R^{trk};",nXbins, xBin);
  // MC 
  TH2D* hHerwig = (TH2D*)hTemp->Clone(Form("hHerwig_kSample%d_icent%d",kSample,icent));
  TH2D* hPythia = (TH2D*)hTemp->Clone(Form("hPythia_kSample%d_icent%d",kSample,icent));
  TH1D* h1herwig[20];
  TH1D* h1pythia[20];

  double Rx[30];
  double Ry[30];
  double RxErr[30];
  double RyErr[30];

  //  getHerwigR   ( kSample, icent, hHerwig, ptCut, "trkJetMassRcSub2");
  //  getPYTHIAR   ( kSample, icent, hPythia, ptCut,"trkJetMassRcSub2");
  //  getHerwigR   ( kSample, icent, hHerwig, ptCut, "");
  //  getPYTHIAR   ( kSample, icent, hPythia, ptCut,"");

  getHerwigR   ( kSample, icent, hHerwig, ptCut, "",im);
  getPYTHIAR   ( kSample, icent, hPythia, ptCut,"",im);
  
  TH1D* hMeanPt = new TH1D("hmeanpt","",nXbins,xBin);
  getMeanPt(0,0,hMeanPt);

  TCanvas* c2 =  new TCanvas("c2","",1200,400);
  makeMultiPanelCanvas(c2,nPtPannels, 1, 0.0, 0.01, 0.3, 0.2, 0.05);
  for ( int ix = lowPtBin ; ix<= highPtBin ; ix++) {
    c2->cd(ix - lowPtBin + 1);
    h1herwig[ix] = (TH1D*)hHerwig->ProjectionX(Form("h1herwig_ipt%d",ix),ix,ix);
    h1pythia[ix] = (TH1D*)hPythia->ProjectionX(Form("h1pythia_ipt%d",ix),ix,ix);
    
    scaleInt(h1herwig[ix]);
    scaleInt(h1pythia[ix]);
    
    handsomeTH1(h1herwig[ix],1);
    handsomeTH1(h1pythia[ix],2);

    cleverRange(h1herwig[ix],2.);
    /*   TF1 *f1mc = new TF1(Form("fitH1herwig_ix%d",ix),"[0]*TMath::Landau(x-[3],[1],[2])",0,20);
    f1mc->SetParameter(0,1);
    f1mc->SetParameter(1,2);
    f1mc->SetParameter(2,2);
    f1mc->SetParameter(3,1);

    TF1 *f1pythia = new TF1(Form("fitH1pythia_ix%d",ix),"[0]*TMath::Landau(x-[3],[1],[2])",0,20);
    f1pythia->SetParameter(0,1);
    f1pythia->SetParameter(1,2);
    f1pythia->SetParameter(2,2);
    f1pythia->SetParameter(3,1);
    */
    TF1 *f1Herwig = new TF1(Form("fitH1herwig_ix%d",ix),"[0]*TMath::Landau(x,[1],[2])",0,8);
    f1Herwig->SetParameter(0,2);
    f1Herwig->SetParameter(1,2.4);
    f1Herwig->SetParameter(2,0.6);
    //    f1Herwig->SetParameter(3,1);

    TF1 *f1pythia = new TF1(Form("fitH1pythia_ix%d",ix),"[0]*TMath::Landau(x,[1],[2])",0,8);
    f1pythia->SetParameter(0,2);
    f1pythia->SetParameter(1,2.4);
    f1pythia->SetParameter(2,0.6);
    //    f1pythia->SetParameter(3,1);


    h1herwig[ix]->Fit(f1Herwig->GetName(),"","",1,5);
    h1pythia[ix]->Fit(f1pythia->GetName(),"","",1,5);
    h1herwig[ix]->GetFunction(f1Herwig->GetName())->SetLineColor(1);
    h1pythia[ix]->GetFunction(f1pythia->GetName())->SetLineColor(2);
    h1herwig[ix]->Draw();
    h1pythia[ix]->Draw("same");

    // Peak = ([1] - 0.22278)* [2] 
    // https://root.cern.ch/root/html528/TMath.html#TMath:Landau

    double herwigPeak = findPeak(f1Herwig,0,4);
    double pythiaPeak = findPeak(f1pythia,0,4);
    double herwigPeakErr = errPeak(f1Herwig);
    double pythiaPeakErr = errPeak(f1pythia);
    double peakRatio = herwigPeak/pythiaPeak; 
    double peakRatioErr =  peakRatio * sqrt (  pow(herwigPeakErr/herwigPeak,2) + pow(pythiaPeakErr/pythiaPeak,2) );

    cout << ix <<"th bin: "<< endl;
    cout << " MC peak  : " << herwigPeak << endl;
    cout << " Data peak  : " << pythiaPeak << endl;
    cout << "Peak ratio = " << pythiaPeak/herwigPeak << endl;
    cout << "Herwig maean, RMS = " << h1herwig[ix]->GetMean() << ",   " << h1herwig[ix]->GetRMS() << endl;
    cout << "PYTHIA maean, RMS = " << h1pythia[ix]->GetMean() << ",   " << h1pythia[ix]->GetRMS() << endl;
    cout << "Herwig/PYTHIA mean = " <<  h1herwig[ix]->GetMean()/ h1pythia[ix]->GetMean() << endl;
    double meanRatio = f1pythia->Mean(0,20) / f1Herwig->Mean(0,20);
    //    if ( ix== lowPtBin)    drawCentrality(kSample, icent, 0.60,0.86,1,24);
    if ( ix== lowPtBin)    drawText("R^{trk} of Herwig/PYTHIA", 0.30,0.86,1,16);
    drawBin(xBin,ix,"GeV",0.4,0.79,49,16);
    drawText(Form("R_{fit} = %.2f", (float)peakRatio), 0.35, 0.72,1,20);
    //    drawText(Form("R_{mean} = %.2f", (float)meanRatio), 0.35, 0.65,1,20);
    
	     //    c2->cd(ix - lowPtBin +1 + nPtPannels);
	     //    TH1D* hratio = (TH1D*)h1pythia[ix]->Clone(Form("ratio_%s",h1pythia[ix]->GetName()));
	     //   hratio->Divide(h1herwig[ix]);
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
  c2->SaveAs(Form("pdfsJMS/JMS_ptCut%d_kSample%d_cent%d_im%d.pdf",(int)ptCut,kSample,icent,im));
  TCanvas* c3 = new TCanvas("c3","",500,500);
  hTrkR->SetAxisRange(0.8,1.2,"Y");
  //  TF1* f1 = new TF1("f1","[0] +x*[1]",xBin[0], xBin[nXbins]);
  TF1* f1 = new TF1("f1","[0] +log(x)*[1] + log(x)*log(x)*[2]",xBin[0], xBin[nXbins]);
  //  hTrkR->Fit("f1");
  handsomeTH1(hTrkR,0);
  hTrkR->SetAxisRange(121,450,"X");
  hTrkR->Draw();
  jumSun(xBin[0],1, xBin[nXbins],1);
  drawText("R^{trk} of Herwig/PYTHIA", 0.30,0.86,1,20);

  TGraphErrors* gr = new TGraphErrors(nXbins,Rx,Ry,RxErr,RyErr);
  gr->Fit("f1","","",125,500);
  //  gr->Fit("f1","O");
  gr->Draw("same p");
  
  TF1* f2 = new TF1("f2","2- ([0] +log(x)*[1] + log(x)*log(x)*[2])",xBin[0], xBin[nXbins]);
  f2->SetParameter( 0, f1->GetParameter(0));
  f2->SetParameter( 1, f1->GetParameter(1));
  f2->SetParameter( 2, f1->GetParameter(2));
  f2->SetLineColor(2);
  f2->SetLineStyle(2);
  //  f2->Draw("same");
  c3->SaveAs(Form("pdfsJMS/trkR_ptCut%d_kSample%d_cent%d_pythiaHerwig_im%d.pdf",(int)ptCut,kSample,icent,im));

  TFile* fout = new TFile("R_trk/Rtrk_PYTHIA_herwig-test.root","update");
  f2->SetName(Form("rtrk_im%d",im));
  f2->Write("",TObject::kOverwrite);
  fout->Close();

}


void getHerwigR(int kSample, int icent, TH2D* hmc, int ptCut, TString varName, int im) { 
  
  TH1::SetDefaultSumw2();
  hmc->Reset();

  TString jz2;
  TString jz3;
  TString jz4;
  if ( kSample == kPbPb ) {
    jz2 = "jetSubstructure_pbpbMC_HION9_jz2_v51_april124.root";
    jz3 = "jetSubstructure_pbpbMC_HION9_jz3_v51_april124.root";
    jz4 = "jetSubstructure_pbpbMC_HION9_jz4_v51_april124.root";
  }
  else if ( kSample == kPP ) {
    //    jz2 = "jetSubstructure_ppMC_HION9_jz2_v51_april124.root";
    //    jz3 = "jetSubstructure_ppMC_HION9_jz3_v51_april124.root";
    //   jz4 = "jetSubstructure_ppMC_HION9_jz4_v51_april124.root";
    jz2 = "jetSubstructure_ppMC_HION9_jz2_v51ppHerwig_april124.root";
    jz3 = "jetSubstructure_ppMC_HION9_jz3_v51ppHerwig_april124.root";
    jz4 = "jetSubstructure_ppMC_HION9_jz4_v51ppHerwig_april124.root";
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

  
  //  if ( ptCut ==1 ) 
  //    trkMassVar =  "chMassRaw"

  
  cout << " Setting tree branch address..." << endl;
  TFile* fjz2 = new TFile(Form("../ntuples/%s",jz2.Data()));
  TTree* tr2 = (TTree*)fjz2->Get("tr");
  tr2->SetBranchAddress("jets", &(myJetMc.cent), &b_myJetSubMc);
  tr2->SetBranchAddress(varName.Data(), &trkJetMass, &b_trkJetMass);
  
  TFile* fjz3 = new TFile(Form("../ntuples/%s",jz3.Data()));
  TTree* tr3 = (TTree*)fjz3->Get("tr");
  tr3->SetBranchAddress("jets", &(myJetMc.cent), &b_myJetSubMc);
  tr3->SetBranchAddress(varName.Data(), &trkJetMass, &b_trkJetMass);

  TFile* fjz4 = new TFile(Form("../ntuples/%s",jz4.Data()));
  TTree* tr4 = (TTree*)fjz4->Get("tr");
  tr4->SetBranchAddress("jets", &(myJetMc.cent), &b_myJetSubMc);
  tr4->SetBranchAddress(varName.Data(), &trkJetMass, &b_trkJetMass);

  TH1D* hptmc = new TH1D("hptmc","",200,0,800);
  
  for ( int ijz =2 ; ijz<=4 ; ijz++) {
    TTree* tr;
    double jzNorm=0;
    if ( ijz==2)  {
      tr = tr2;
      jzNorm = HerwigEvtWgtJZ2;
    }
    else if ( ijz==3)  {
      tr = tr3;
      jzNorm = HerwigEvtWgtJZ3;
    }
    else if ( ijz==4)  {
      tr = tr4;
      jzNorm = HerwigEvtWgtJZ4;
    }
    
    cout << "Scanning JZ"<<ijz<<" file.  Total events = " << tr->GetEntries() << endl;
    for (Int_t i= 0; i<tr->GetEntries() ; i++) {
      if ( i > tr->GetEntries() * statUsed ) break;

      tr->GetEntry(i);


      if ( ! passEvent(myJetMc, icent, true) )        continue;

      double mpt =  myJetMc.recoMass / myJetMc.recoPt ;
      double recoMass = myJetMc.recoMass ;
      //      if (!( (recoMass>-100) && (recoMass<21)  ) )
      //        continue;

      if ( im != findMbin(mpt) )        continue;

      double recoPt = myJetMc.recoPt;
      double theR = myJetMc.recoMass / myJetMc.recoChMassRcSubt ;

      if ( varName == "")	theR = myJetMc.recoMass / myJetMc.recoChMassRcSubt;

      double fcalWeight = 1.0;
      if ( kSample==kPbPb) {
	fcalWeight = hFcalReweight->GetBinContent(hFcalReweight->GetXaxis()->FindBin(myJetMc.fcalet));
        //      cout <<" fcal, weight = "<<myJetMc.fcalet<<", "<<fcalWeight<<endl;
      }
      hmc->Fill(theR, recoPt, jzNorm * fcalWeight);
      hptmc->Fill( recoPt, jzNorm);
    }
  }
  
  TCanvas* c2 = new TCanvas("c1","",500,500);
  hptmc->Draw();
}

void getPYTHIAR(int kSample, int icent,  TH2D* hmc, int ptCut, TString varName, int im) {

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
      
      double mpt =  myJetMc.recoMass / myJetMc.recoPt ;
      double recoMass = myJetMc.recoMass ;
      //      if (!( (recoMass>-100) && (recoMass<21)  ) )
      //        continue;

      if ( im != findMbin(mpt) )        continue;
      
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

  for (Int_t i= 0; i<tr->GetEntries() *0.1 ; i++) {
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


