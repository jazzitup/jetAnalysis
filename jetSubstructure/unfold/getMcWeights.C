#include <iostream>
using std::cout;
using std::endl;

#include "TRandom.h"
#include "TH1D.h"

#include "../getSdHists.C"
#include "../ntupleDefinition.h"
#include "../commonUtility.h"
#include "../jzWeight.h"
#include "unfoldingUtil.h"

#include "../JssUtils.h"
#include <TPaletteAxis.h>

double statFrac = 001;
double fracStstData = 001;
bool doUnfData = true ;

int lowPtBin = 1;  int highPtBin = 13;
//int lowPtBin = 6;   int highPtBin = 11;

int nPtPannels = highPtBin-lowPtBin+1;

bool isTooSmall(TH2D* hEntries=0, int recoVarX=0, int recoVarY=0, int minEntries=10);

void getMCspectra(int kSample=kPP, int icent=0, int opt=1, TH2D* hmcRaw=0,  TH2D* hmcTruth=0);
void getDATAspectra(int kSample=kPP, int icent=0, int opt=1, TH2D* hdataRaw=0);

//bool isTooSmall(TH2D* hEntries=0, int recoVarX=0, int recoVarY=0, int minEntries=10);

void removeFluc2(TH2* h) {
  for ( int i =1 ;  i<=h->GetNbinsX() ; i++) {
    for ( int j =1 ;  j<=h->GetNbinsY() ; j++) {
      double val  = h->GetBinContent(i,j);
      double error  = h->GetBinError(i,j);
      if ( error > val * 0.3 )   {
	h->SetBinContent(i,j,0);
	h->SetBinError(i,j,0);
      }
    }
  }
}

void getMcWeights(int kSample = kPP, int icent=0, float weightCut = 10, int opt=771) {   // opt1 : mass,   opt2 : m/pT  
  TH1::SetDefaultSumw2();
  
  int nXbins;
  double xBin[30];
  if ( opt==1 ) getXbin(nXbins, xBin, 77);
  if ( opt==2 ) getXbin(nXbins, xBin, 77);
  if ( opt==771 ) getXbin(nXbins, xBin, 77);
  cout << " nXbins = " << nXbins << endl;
  cout << " xBin = " << xBin[0] << ",   " << xBin[1] << ",   " <<xBin[2] << ", ..." <<endl;


  int nYbins ;
  double y2Bin[30] ;
  double yBin[30] ;
  if ( opt==1)  getYbin(nYbins, y2Bin, yBin, 77);
  else if ( opt==2)  getYbin(nYbins, y2Bin, yBin, 77);
  else if ( opt==771)  getYbin(nYbins, y2Bin, yBin, 771);
  
  TH2D* hTemp = new TH2D("hptTemp","", nXbins, xBin, nYbins, yBin);
  
  int i = icent;

  // MC 
  TH2D* hmcRaw   = (TH2D*)hTemp->Clone(Form("hmcRaw_kSample%d_icent%d_opt%d",kSample,i,opt));
  TH2D* hmcTruth = (TH2D*)hTemp->Clone(Form("hmcTruth_kSample%d_icent%d_opt%d",kSample,i,opt));
  TH2D* hdataRaw = (TH2D*)hTemp->Clone(Form("hdataRaw_kSample%d_icent%d_opt%d",kSample,i,opt));

  //void getMCspectra(int kSample=kPP, int icent=0, int opt=1, TH2D* hmcRaw=0,  TH2D* hmcTruth=0); 
  getMCspectra   ( kSample, icent, opt, hmcRaw, hmcTruth);
  getDATAspectra ( kSample, icent, opt, hdataRaw);
  
  
  for ( int ix= 1 ; ix<= nXbins; ix++) {
    for ( int iy= 1 ; iy<= nYbins; iy++) {
      if ( hmcRaw->GetBinContent(ix,iy) == 0 )  cout << "MC :found a null bin ix, iy = " << ix<<", "<<iy<< endl;
      if ( hdataRaw->GetBinContent(ix,iy) == 0 )  cout << "DATA :found a null bin ix, iy = " << ix<<", "<<iy<< endl;
    }
  }
  
  scaleInt(hmcRaw);
  scaleInt(hdataRaw);

  TH2D* hRatioRaw = (TH2D*)hdataRaw->Clone(Form("hRatioRaw_kSample%d_icent%d_opt%d",kSample,i,opt));
  hRatioRaw->Divide(hmcRaw);
  removeFluc2(hRatioRaw);
  TH2D* hRatioSmooth2 = (TH2D*)hRatioRaw->Clone(Form("hRatioSmooth2_kSample%d_icent%d_opt%d",kSample,i,opt));
  hRatioSmooth2->Smooth();

  TH2D* hmcRawSmooth = (TH2D*)hmcRaw->Clone(Form("%s_smooth",hmcRaw->GetName()));
  TH2D* hdataRawSmooth = (TH2D*)hdataRaw->Clone(Form("%s_smooth",hdataRaw->GetName()));
  
  //  scaleInt(hmcRawSmooth);
  //  scaleInt(hdataRawSmooth);

  hmcRawSmooth->Smooth();
  hdataRawSmooth->Smooth();
  TH2D* hRatioSmoothRaw = (TH2D*)hdataRawSmooth->Clone(Form("hRatioSmoothRaw_kSample%d_icent%d_opt%d",kSample,i,opt));
  hRatioSmoothRaw->Divide(hmcRawSmooth);
  
  TH2D* hRatioSmooth = (TH2D*)hRatioSmoothRaw->Clone(Form("hRatioSmooth_kSample%d_icent%d_opt%d",kSample,i,opt));
  
  for ( int ix= 1 ; ix<= nXbins; ix++) {
    for ( int iy= 1 ; iy<= nYbins; iy++) {
      if ( hRatioSmooth->GetBinContent( ix, iy ) > weightCut ) 
	hRatioSmooth->SetBinContent(ix, iy, weightCut ); 
      if ( hRatioSmooth->GetBinContent( ix, iy ) < 0.2 ) 
	hRatioSmooth->SetBinContent(ix, iy, 0.2 ); 
    }
  }

  
  TFile * fout = new TFile(Form("reweightFactors/reweightingFactor_weightCut%d_opt%d_removeFluc.root",(int)weightCut,opt),"update");
  hmcRaw->Write();
  hmcTruth->Write();
  hdataRaw->Write();
  hmcRawSmooth->Write();
  hdataRawSmooth->Write();
  hdataRawSmooth->Write();
  hRatioSmoothRaw->Write();
  hRatioSmooth->Write();
  hRatioRaw->Write();
  hRatioSmooth2->Write();
  fout->Close();
  
}


void getMCspectra(int kSample, int icent, int opt, TH2D* hmcRaw,  TH2D* hmcTruth) {
  
  TH1::SetDefaultSumw2();
  hmcRaw->Reset();
  hmcTruth->Reset();

  TString jz2;
  TString jz3;
  TString jz4;
  if ( kSample == kPbPb ) {
    jz2 = "jetSubstructure_MC_HION9_jz2_v4.7_v4_Jan23_ptCut90Eta2.1.root";
    jz3 = "jetSubstructure_MC_HION9_jz3_v4.7_v4_Jan23_ptCut90Eta2.1.root";
    jz4 = "jetSubstructure_MC_HION9_jz4_v4.7_v4_Jan23_ptCut90Eta2.1.root";
  }
  else if ( kSample == kPP ) {
    jz2 = "jetSubstructure_MC_HION9_jz2_v4.7_r4_pp_Jan23_ptCut90Eta2.1.root";
    jz3 = "jetSubstructure_MC_HION9_jz3_v4.7_r4_pp_Jan23_ptCut90Eta2.1.root";
    jz4 = "jetSubstructure_MC_HION9_jz4_v4.7_r4_pp_Jan23_ptCut90Eta2.1.root";
  }
  
  TH1D* hReweight;
  TFile* fReweight;

  jetSubStr  myJetMc;
  TBranch  *b_myJetSubMc;

  TFile* checkEntries = new TFile(Form("checkEntry/entries_kSample%d_icent%d_optX1_optY2.root",kSample,icent));
  TH2D* recoEntries_jz2 = (TH2D*)checkEntries->Get("reco_jz2");
  TH2D* recoEntries_jz3 = (TH2D*)checkEntries->Get("reco_jz3");
  TH2D* recoEntries_jz4 = (TH2D*)checkEntries->Get("reco_jz4");
  TH2D* hRecoEntries;

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
      if ( i > tr->GetEntries() * statFrac ) continue;
      if (i%2==0)  continue;

      tr->GetEntry(i);

      if ( ! passEvent(myJetMc, icent, true) ) // isMC = true
        continue;
      
      double genX;
      double genY;
      if ( opt ==1 ) {
	genX = myJetMc.genPt; 
	genY = myJetMc.genMass;
      }
      else  if ( (opt ==2) || (opt==771) ) {
	genX = myJetMc.genPt;
	genY = myJetMc.genMass;
      }
      
      
      double recoX  = -10000; 
      double recoY  = -10000; 
      if ( opt == 1 ) {
	recoX = myJetMc.recoPt;
	recoY = myJetMc.recoMass ;
      }
      else  if ( (opt ==2) || (opt==771) ) {
	recoX = myJetMc.recoPt;
	recoY = myJetMc.recoMass;
      }
      
      //      if ( opt==2) {  
      //	if ( isTooSmall(hRecoEntries, recoX, recoY,10) ) {
      //	  cout << "isTooSmall! " << endl;
      //  cout << "jz"<<ijz<<":   pT, (m/pT)^2 =" << recoX <<", "<<recoY<<endl;
      //	  continue;
      //	}
      //      }
      
      hmcRaw->Fill( recoX, recoY, myJetMc.weight * jzNorm);
      hmcTruth->Fill( genX, genY, myJetMc.weight * jzNorm);
    }
  }
  
}

void getDATAspectra(int kSample, int icent, int opt, TH2D* hdataRaw) { 

  TH1::SetDefaultSumw2();
  hdataRaw->Reset();
  TString fname;
  if ( kSample == kPbPb ) {
    fname = "jetSubstructure_Data_HION9_v4.7_r4_pbpb_Jan23_ptCut90Eta2.1.root"; }
  else if ( kSample == kPP) {
    fname = "jetSubstructure_data_HION9_v4.7_r4_pp_Feb26_ptCut90Eta2.1_fullLumi.root"; }
  
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
    if ( i > tr->GetEntries() * fracStstData) continue;

    if ( ! passEvent(myJet, icent, false) ) // isMC = false
      continue;

    double recoX  = -10000;
    double recoY  = -10000;
    if ( opt == 1 ) {
      recoX = myJet.recoPt;
      recoY = myJet.recoMass;
    }
    else if ( (opt == 2) || (opt==771) ) {
      recoX = myJet.recoPt;
      recoY = myJet.recoMass;
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


