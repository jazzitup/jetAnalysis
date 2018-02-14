
#if !(defined(__CINT__) || defined(__CLING__)) || defined(__ACLIC__)
#include <iostream>
using std::cout;
using std::endl;

#include "TRandom.h"
#include "TH1D.h"

#include "RooUnfoldResponse.h"
#include "RooUnfoldBayes.h"
//#include "RooUnfoldSvd.h"
//#include "RooUnfoldTUnfold.h"

#include "../getSdHists.C"
#include "../ntupleDefinition.h"
#include "../commonUtility.h"
#include "../jzWeight.h"
#endif

//==============================================================================
// Global definitions
//==============================================================================

#include "../JssUtils.h"
#include <TPaletteAxis.h>
#include "unfoldingUtil.h"

bool doJES = true;

bool doCheckSmearing = false; //true;	
int selBinX = 6; // 199 GeV - 251 GeV

bool checkClosure=true;

double fracStst=01;
double fracStstData=01;

bool useFullMC = true;

RooUnfoldResponse* getResponse( int kSample = kPP, int icent = 0, int optX=1, TH1D* hTruth=0, TH1D* hReco=0, double radius =0.4,bool doReweight = false);


void makeUnfMatrix1D(int kSample = kPP, int optX =1, double radius= 0.4) {
  TH1::SetDefaultSumw2();
  int nXbins;
  double xBin[30];
  getXbin(nXbins, xBin, optX);
  cout << " nXbins = " << nXbins << endl; 
  cout << " xBin = " << xBin[0] << ",   " << xBin[1] << ",   " <<xBin[2] << ", ..." <<endl;

  TH1D* hTruthTemp = new TH1D("hTruth","",nXbins,xBin);
  TH1D* hRecoTemp = (TH1D*)hTruthTemp->Clone("hReco");
  RooUnfoldResponse* res[7];
  
  TH1D* hTruth[7];
  TH1D* hReco[7];
  TH1D* hResultMc[7];
  
  TH2D* hMatrix[7];
  

  for ( int i=0 ; i<=6; i++) {
    int icent = i;
    if ( !selectedCent(icent)) 
      continue;
    if ( (kSample == kPP) && ( icent != 0 ) )
      continue;

    hTruth[i] = (TH1D*)hTruthTemp->Clone(Form("%s_icent%d",hTruthTemp->GetName(),i));
    hReco[i] = (TH1D*)hRecoTemp->Clone(Form("%s_icent%d",hRecoTemp->GetName(),i));
    //    hTruth[i]->Reset();
    //    hReco[i]->Reset();
    
    res[i] = getResponse(kSample, i, optX, hTruth[i], hReco[i], radius,false);

    TCanvas* c01 = new TCanvas("c01", "",500,500);
    hMatrix[i] = (TH2D*)res[i]->Hresponse();
    hMatrix[i]->Draw("colz");
    c01->SaveAs(Form("pdfs/correlation_coll%d_cent%d_radius%.1f.pdf",kSample,i,(float)radius));
  }
  
  TFile* fout = new TFile(Form("spectraFiles/unfoldingMatrix1D_coll%d_optX%d_radius%.1f.root",kSample,optX,(float)radius),"recreate");
  for ( int i=0 ; i<=6; i++) {
    int icent = i;
    if ( !selectedCent(icent))      continue;
    if ( (kSample == kPP) && ( icent !=0 ) )      continue;
    res[i]->Write();
    hMatrix[i]->Write();
  }
}

RooUnfoldResponse* getResponse(int kSample,  int icent,  int optX, TH1D* hTruth, TH1D* hReco, double radius, bool doReweight)
{

  TH1::SetDefaultSumw2();
  TString jz2;
  TString jz3;
  TString jz4;
  if ( kSample == kPbPb ) {
    if ( radius==0.4 ) { 
      jz2 = "jetSubstructure_MC_HION9_jz2_v4.7_v4_Jan23_ptCut90Eta2.1.root";
      jz3 = "jetSubstructure_MC_HION9_jz3_v4.7_v4_Jan23_ptCut90Eta2.1.root";
      jz4 = "jetSubstructure_MC_HION9_jz4_v4.7_v4_Jan23_ptCut90Eta2.1.root";
    }
    else if ( radius==0.6) { 
      //      jz2 = "jetSubstructure_MC_HION9_jz2_r6_Jan11.root";
      //      jz3 = "jetSubstructure_MC_HION9_jz3_r6_Jan11.root";
      //      jz4 = "jetSubstructure_MC_HION9_jz4_r6_Jan11.root";
    }
  }
  else if ( kSample == kPP ) {
    if ( radius==0.4 ) {
      jz2 = "jetSubstructure_MC_HION9_jz2_v4.7_r4_pp_Jan23_ptCut90Eta2.1.root";
      jz3 = "jetSubstructure_MC_HION9_jz3_v4.7_r4_pp_Jan23_ptCut90Eta2.1.root";
      jz4 = "jetSubstructure_MC_HION9_jz4_v4.7_r4_pp_Jan23_ptCut90Eta2.1.root";
    }

  }

  TH1D* hReweight; 
  TFile* fReweight; 

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

  TH1D* xBinTemp = new TH1D("xBinTemp","", nXbins, xBin);

  RooUnfoldResponse* res = new RooUnfoldResponse( hTruth, hReco );
  res->SetName(Form("responseMatrix_icent%d_reweight%d",icent,false));

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
      if ( i > tr->GetEntries() * fracStst ) continue;
      tr->GetEntry(i);
      
      if ( ! passEvent(myJetMc, icent, true) ) // isMC = true
	continue;

      double recoVarX, truthVarX;
      getXvalues( recoVarX, truthVarX, myJetMc, optX);

      // Data/MC reweighting factors 
      double rewFact = 1; 
      //      if ( doReweight) { 
      //	int rewBin = hReweight->FindBin(recoVarX,recoVarY); 
      //	rewFact = hReweight->GetBinContent(rewBin);
      //      }
      
      if ( useFullMC || (i%2==0) )  
	res->Fill(  recoVarX, truthVarX, myJetMc.weight * rewFact * jzNorm);
    }
  }
  return res;
}


#ifndef __CINT__
int main () { makeUnfMatrix1D(); return 0; }  // Main program when run stand-alone
#endif





