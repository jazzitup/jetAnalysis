
#if !(defined(__CINT__) || defined(__CLING__)) || defined(__ACLIC__)
#include <iostream>
using std::cout;
using std::endl;

#include "TRandom.h"
#include "TH1D.h"
#include "TH2D.h"

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

double fracStst=0001;
double fracStstData=01;

bool useFullMC = true;

RooUnfoldResponse* getResponse( int kSample = kPP, int icent = 0, int optX=1, int optY=2, TH2D* hTruth=0, TH2D* hReco=0, double radius =0.4,bool doReweight = false);


void makeUnfMatrix2D(int kSample = kPP, int optX =1, int optY=2, double radius= 0.4, bool doReweight=true) {
  TH1::SetDefaultSumw2();
  int nXbins;
  double xBin[30];
  getXbin(nXbins, xBin, optX);
  cout << " nXbins = " << nXbins << endl; 
  cout << " xBin = " << xBin[0] << ",   " << xBin[1] << ",   " <<xBin[2] << ", ..." <<endl;
  
  int nYbins ;
  double yBin[30] ;
  double yBinSqrt[30] ;
  getYbin(nYbins, yBin, yBinSqrt, optY);


  TH2D* hTruthTemp = new TH2D("hTruth","",nXbins,xBin,nYbins,yBin);
  TH2D* hRecoTemp = (TH2D*)hTruthTemp->Clone("hReco");
  RooUnfoldResponse* res[7];
  
  TH2D* hTruth[7];
  TH2D* hReco[7];
  TH2D* hResultMc[7];
  
  TH2D* hMatrix[7];
  

  for ( int i=0 ; i<=6; i++) {
    int icent = i;
    if ( !selectedCent(icent))       continue;
    if ( (kSample == kPP) && ( icent != 0 ) )      continue;

    hTruth[i] = (TH2D*)hTruthTemp->Clone(Form("%s_icent%d",hTruthTemp->GetName(),i));
    hReco[i] = (TH2D*)hRecoTemp->Clone(Form("%s_icent%d",hRecoTemp->GetName(),i));
    hTruth[i]->Reset();
    hReco[i]->Reset();
    
    res[i] = getResponse(kSample, i, optX, optY, hTruth[i], hReco[i], radius,doReweight);

    TCanvas* c01 = new TCanvas("c01", "",500,500);
    hMatrix[i] = (TH2D*)res[i]->Hresponse();
    hMatrix[i]->Draw("colz");
    c01->SaveAs(Form("pdfs/correlation_2dUnf_coll%d_cent%d_radius%.1f.pdf",kSample,i,(float)radius));
  }
  
  TFile* fout = new TFile(Form("spectraFiles/unfoldingMatrix2D_coll%d_optX%d_radius%.1f_doReweight%d.root",kSample,optX,(float)radius,(int)doReweight),"recreate");
  for ( int i=0 ; i<=6; i++) {
    int icent = i;
    if ( !selectedCent(icent))      continue;
    if ( (kSample == kPP) && ( icent !=0 ) )      continue;
    res[i]->Write();
    hMatrix[i]->Write();
  }
}

RooUnfoldResponse* getResponse(int kSample,  int icent,  int optX, int optY, TH2D* hTruth, TH2D* hReco, double radius, bool doReweight)
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

  TH2D* hReweight;
  TFile* fReweight;
  if ( doReweight ) {
    if ( kSample == kPP)         fReweight = new TFile(fReweightPP) ;
    else if ( kSample == kPbPb)  fReweight = new TFile(fReweightPbPb) ;
    hReweight = (TH2D*)fReweight->Get(Form("hWeight_icent%d",icent));
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

      double recoVarY, truthVarY;
      getYvalues( recoVarY, truthVarY, myJetMc, optY);

      // Data/MC reweighting factors 
      double rewFact = 1; 
      if ( doReweight) { 
	double recoM2 = myJetMc.recoMass * myJetMc.recoMass;
	double recoPt2 = myJetMc.recoPt * myJetMc.recoPt;
	if ( myJetMc.recoMass < 0 ) recoM2 = - recoM2;
	double recoVarY =  recoM2 / recoPt2; 
	
      	int rewBin = hReweight->FindBin(recoVarX,recoVarY); 
      	rewFact = hReweight->GetBinContent(rewBin);

	// ONLY FOR 0-10% PbPb
	if ( (icent == 0) && ( kSample==kPbPb) ) { 
	  rewFact = 63619.9 + 240 * recoVarX ; 
	}
      }
      //      cout << " rew = " << rewFact << endl;
      //      cout << "myJetMc.weight= " << myJetMc.weight << endl;
      //      cout << "jzNorm = " << jzNorm << endl;
      //      cout << recoVarX << ", " << recoVarY << ", "<< truthVarX << ", "<< truthVarY << endl;

      if ( useFullMC || (i%2==0) )  {

	res->Fill(  recoVarX, recoVarY, truthVarX, truthVarY, myJetMc.weight * rewFact * jzNorm);
      }
    }
  }
  return res;
}


#ifndef __CINT__
int main () { makeUnfMatrix2D(); return 0; }  // Main program when run stand-alone
#endif


