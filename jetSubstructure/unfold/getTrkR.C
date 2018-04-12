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

void getMCR(int kSample=kPP, int icent=0,  TH2D* hmc=0, int ptCut=6);
void getDATAR(int kSample=kPP, int icent=0,  TH2D* hdata=0, int ptCut=6);
TH1D* getVariedHist(TH1D* hin=0, double variation=0);

void getTrkR(int kSample = kPP, int icent=0, int ptCut =6 ) {   // opt1 : mass,   opt2 : m/pT  
  TH1::SetDefaultSumw2();

  int optX = 1;    int optY = 2;  

  int nXbins;
  double xBin[30];
  getXbin(nXbins, xBin, optX);

  int nYbins ;
  double yBin[30] ;
  getYbin(nYbins, yBin, optY);

  int nRbins = 30;
  TH2D* hTemp = new TH2D("rTemp","", nRbins, 0,50, nXbins, xBin);
  
  // MC 
  TH2D* hmc = (TH2D*)hTemp->Clone(Form("hmc_kSample%d_icent%d",kSample,icent));
  TH2D* hdata = (TH2D*)hTemp->Clone(Form("hdata_kSample%d_icent%d",kSample,icent));
  TH1D* h1mc[20];
  TH1D* h1data[20];

  getMCR   ( kSample, icent, hmc, ptCut);
  getDATAR ( kSample, icent, hdata, ptCut);


  int lowPtBin = 6;
  int highPtBin = 11;
  int nPtPannels = highPtBin-lowPtBin+1;
  
  TCanvas* c2 =  new TCanvas("c2","",1200,400);
  makeMultiPanelCanvas(c2,nPtPannels, 2, 0.0, 0.01, 0.3, 0.2, 0.05);
  for ( int ix = lowPtBin ; ix<= highPtBin ; ix++) {
    c2->cd(ix - lowPtBin + 1);
    h1mc[ix] = (TH1D*)hmc->ProjectionX(Form("h1mc_ipt%d",ix),ix,ix);
    h1data[ix] = (TH1D*)hdata->ProjectionX(Form("h1data_ipt%d",ix),ix,ix);

    scaleInt(h1mc[ix]);
    scaleInt(h1data[ix]);
    
    handsomeTH1(h1mc[ix],1);
    handsomeTH1(h1data[ix],2);

    cleverRange(h1mc[ix],1.5);
    h1mc[ix]->Draw();
    h1data[ix]->Draw("same");
    cout << ix <<"th bin: "<< endl;
    cout << "MC maean, RMS = " << h1mc[ix]->GetMean() << ",   " << h1mc[ix]->GetRMS() << endl;
    cout << "DATA maean, RMS = " << h1data[ix]->GetMean() << ",   " << h1data[ix]->GetRMS() << endl;

    //    gPad->SetLogy();
    
    if ( ix== lowPtBin)    drawCentrality(kSample, icent, 0.60,0.86,1,24);
    drawBin(xBin,ix,"GeV",0.4,0.78,49,16);
    
    c2->cd(ix - lowPtBin +1 + nPtPannels);
    TH1D* hratio = (TH1D*)h1data[ix]->Clone(Form("ratio_%s",h1data[ix]->GetName()));
    hratio->Divide(h1mc[ix]);
    hratio->SetAxisRange(0,2,"Y");
    hratio->SetYTitle("Data/MC");
    hratio->Draw();
    jumSun(0,1,50,1);
  }
  
}


void getMCR(int kSample, int icent, TH2D* hmc, int ptCut) { 
  
  TH1::SetDefaultSumw2();
  hmc->Reset();

  TString jz2;
  TString jz3;
  TString jz4;
  if ( kSample == kPbPb ) {
    jz2 = "jetSubstructure_MC_HION9_pbpb_v50_jz2_SmallSet.root";
    jz3 = "jetSubstructure_MC_HION9_pbpb_v50_jz3_SmallSet.root";
    jz4 = "jetSubstructure_MC_HION9_pbpb_v50_jz4_SmallSet.root";
  }
  else if ( kSample == kPP ) {
    jz2 = "jetSubstructure_MC_HION9_pp_v50_jz2_SmallSet.root";
    jz3 = "jetSubstructure_MC_HION9_pp_v50_jz3_SmallSet.root";
    jz4 = "jetSubstructure_MC_HION9_pp_v50_jz4_SmallSet.root";
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
  TString trkMassVar = Form("trkJetMass%d",ptCut);
  TString trkPtVar = Form("trkJetPt%d",ptCut);
  
  cout << " Setting tree branch address..." << endl;
  TFile* fjz2 = new TFile(Form("../ntuples/%s",jz2.Data()));
  TTree* tr2 = (TTree*)fjz2->Get("tr");
  tr2->SetBranchAddress("jets", &(myJetMc.cent), &b_myJetSubMc);
  tr2->SetBranchAddress(trkMassVar.Data(), &trkJetMass, &b_trkJetMass);
  tr2->SetBranchAddress(trkPtVar.Data(), &trkJetPt, &b_trkJetPt);
  
  TFile* fjz3 = new TFile(Form("../ntuples/%s",jz3.Data()));
  TTree* tr3 = (TTree*)fjz3->Get("tr");
  tr3->SetBranchAddress("jets", &(myJetMc.cent), &b_myJetSubMc);
  tr3->SetBranchAddress(trkMassVar.Data(), &trkJetMass, &b_trkJetMass);
  tr3->SetBranchAddress(trkPtVar.Data(), &trkJetPt, &b_trkJetPt);

  TFile* fjz4 = new TFile(Form("../ntuples/%s",jz4.Data()));
  TTree* tr4 = (TTree*)fjz4->Get("tr");
  tr4->SetBranchAddress("jets", &(myJetMc.cent), &b_myJetSubMc);
  tr4->SetBranchAddress(trkMassVar.Data(), &trkJetMass, &b_trkJetMass);
  tr4->SetBranchAddress(trkPtVar.Data(), &trkJetPt, &b_trkJetPt);

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
      if (i%2==0)  continue;

      tr->GetEntry(i);

      if ( ! passEvent(myJetMc, icent, true) ) // isMC = true
        continue;
      
      

      // cut on trakc mass 
      if ( trkJetMass < 0.2 ) 
	continue;
      //      if ( ( myJetMc.recoMass / myJetMc.recoPt ) > 0.1 ) 
      //      	continue;
    
      
      double mpt =  myJetMc.recoMass / myJetMc.recoPt ;
      double recoMass = myJetMc.recoMass ;
      if (!( (recoMass>-100) && (recoMass<21)  ) )
	continue;
      
      double recoPt = myJetMc.recoPt;
      double theR = myJetMc.recoMass / trkJetMass;
      
      double fcalWeight = 1.0;
      if ( kSample==kPbPb) {
	fcalWeight = hFcalReweight->GetBinContent(hFcalReweight->GetXaxis()->FindBin(myJetMc.fcalet));
        //      cout <<" fcal, weight = "<<myJetMc.fcalet<<", "<<fcalWeight<<endl;
      }
      hmc->Fill(theR, recoPt, myJetMc.weight * jzNorm * fcalWeight);
      
    }
  }
  
}

void getDATAR(int kSample, int icent,  TH2D* hdata, int ptCut) {

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
  float trkJetPt;
  float trkJetMass;
  TBranch *b_trkJetPt;
  TBranch *b_trkJetMass;
  TString trkMassVar = Form("trkJetMass%d",ptCut);
  TString trkPtVar = Form("trkJetPt%d",ptCut);


  tr->SetBranchAddress("jets", &(myJet.cent), &b_myJet);
  tr->SetBranchAddress(trkPtVar.Data(), &trkJetPt, &b_trkJetPt);
  tr->SetBranchAddress(trkMassVar.Data(), &trkJetMass, &b_trkJetMass);

  if ( kSample == kPP )  cout << " pp " ;
  else if ( kSample == kPbPb) cout << " PbPb " ;
  cout << "data entries = " << tr->GetEntries() << endl;
  
  for (Int_t i= 0; i<tr->GetEntries() ; i++) {
    tr->GetEntry(i);
    if ( i > tr->GetEntries() * statUsed) break;

    if ( ! passEvent(myJet, icent, false) ) // isMC = false
      continue;

    // cut on trakc mass
    if ( trkJetMass < 0.2 )
      continue;
    //    if ( ( myJet.recoMass / myJet.recoPt ) > 0.1 ) 
    //      continue;

    double mpt = myJet.recoMass / myJet.recoPt;
    double recoMass = myJet.recoMass ;
    if (!( (recoMass>-100) && (recoMass<21)  ) )
      continue;
	

    
    double recoPt = myJet.recoPt;
    double theR = myJet.recoMass / trkJetMass;

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
