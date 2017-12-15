//=====================================================================-*-C++-*-
// File and Version Information:
//      $Id: RooUnfoldExample.cxx 348 2014-08-08 22:18:23Z T.J.Adye@rl.ac.uk $
//
// Description:
//      Simple example usage of the RooUnfold package using toy MC.
//
// Authors: Tim Adye <T.J.Adye@rl.ac.uk> and Fergus Wilson <fwilson@slac.stanford.edu>
//
//==============================================================================

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
#endif

//==============================================================================
// Global definitions
//==============================================================================

const Double_t cutdummy= -99999.0;

//==============================================================================
// Gaussian smearing, systematic translation, and variable inefficiency
//==============================================================================

Double_t smear (Double_t xt)
{
  Double_t xeff= 0.3 + (1.0-0.3)/20*(xt+10.0);  // efficiency
  Double_t x= gRandom->Rndm();
  if (x>xeff) return cutdummy;
  Double_t xsmear= gRandom->Gaus(-2.5,0.2);     // bias and smear
  return xt+xsmear;
}

//==============================================================================
// Example Unfolding
//==============================================================================

void RooUnfoldExample()
{
  cout << "==================================== TRAIN ====================================" << endl;
  TFile* f = new TFile("../ntuples/jetSubstructure_himix_test_v4.5_r4_reco_track_pT_cut_postCS0_alphaSubtr2_csMaxR3.00.root");
  TTree* tr = (TTree*)f->Get("tr");
  jetSubStr myJet;
  TBranch       *b_myJetSub;
  tr->SetBranchAddress("jets", &(myJet.cent), &b_myJetSub);
  // Train with a Breit-Wigner, mean 0.3 and width 2.5.
  cout << " entries = " << tr->GetEntries() << endl;
  const int nPtBins = 5; 
  double ptBin[nPtBins+1] = {100,120,150,200,300,400};
  const int nMassBins = 20;
  double massBin[nMassBins+1];
  for ( int i=0 ; i<= nMassBins ; i++) { 
    massBin[i] = -500 + (3000.+500.) * float(i)/nMassBins ;
  }

  TH2D* hTruth = new TH2D("hTruth","",nPtBins,ptBin,nMassBins,massBin);
  TH2D* hReco = new TH2D("hReco","",nPtBins,ptBin,nMassBins,massBin);
  RooUnfoldResponse* res = new RooUnfoldResponse( hTruth, hReco );
  TH2D* hTrue = (TH2D*)hTruth->Clone("htruth");
  TH2D* hRaw = (TH2D*)hReco->Clone("hraw");

  for (Int_t i= 0; i<tr->GetEntries() ; i++) {
    tr->GetEntry(i);
    if ( myJet.cent !=2 ) continue; 
    if ( myJet.recoPt < 150 ) continue;
    if ( myJet.genPt < 100 ) continue;

    double genM2 = myJet.genMass* myJet.genMass;
    double recoM2 = myJet.recoMass * myJet.recoMass;  
    if ( myJet.recoMass < 0 ) recoM2 = - recoM2;
    //    res->Fill( myJet.genPt, genM2 , myJet.recoPt, recoM2, myJet.weight );
    if ( i<tr->GetEntries()/2)  { 
      res->Fill(  myJet.recoPt, recoM2,    myJet.genPt, genM2, myJet.weight);
    }
    else  {
      hTrue->Fill( myJet.genPt, genM2, myJet.weight);
      hRaw->Fill( myJet.recoPt, recoM2, myJet.weight);
    }
  }
  
  cout << "==================================== UNFOLD ===================================" << endl;
  RooUnfoldBayes   unfold (res, hRaw, 4);    // OR
  //RooUnfoldSvd     unfold (&response, hMeas, 20);   // OR
  //RooUnfoldTUnfold unfold (&response, hMeas);
  
  TH2D* hResult= (TH2D*) unfold.Hreco();

  unfold.PrintTable (cout, hTrue);
  TCanvas* c1 = new TCanvas("c1","",1200,800);
  c1->Divide(3,2);
  c1->cd(1);
  hTrue->Draw("colz");
  c1->cd(2);
  hRaw->Draw("colz");
  c1->cd(3);
  hResult->Draw("colz");
  c1->cd(4);
  TH1D* hmassTrue = (TH1D*) hTrue->ProjectionY();
  TH1D* hmassRaw = (TH1D*) hRaw->ProjectionY();
  TH1D* hmassResult = (TH1D*) hResult->ProjectionY();
  handsomeTH1(hmassTrue,1);
  handsomeTH1(hmassRaw,1);
  handsomeTH1(hmassResult,2);
  hmassRaw->SetXTitle("m^{2} (GeV^{2})");
  cleverRange(hmassRaw,1.8);

  hmassRaw->Draw("e");
  hmassTrue->Draw("hist same");
  hmassResult->Draw("e same");
  
  TLegend *leg2 = new TLegend(0.5517022,0.6969086,0.9999478,0.9038978,NULL,"brNDC");
  easyLeg(leg2,"Mass Projection");
  leg2->AddEntry(hmassTrue,"Truth","l");
  leg2->AddEntry(hmassRaw,"Reco","p");
  leg2->AddEntry(hmassResult,"Unfolded","p");
  leg2->Draw();

  c1->cd(5);
  TH1D* hptTrue = (TH1D*) hTrue->ProjectionX();
  TH1D* hptRaw = (TH1D*) hRaw->ProjectionX();
  TH1D* hptResult = (TH1D*) hResult->ProjectionX();
  handsomeTH1(hptTrue,1);
  handsomeTH1(hptRaw,1);
  handsomeTH1(hptResult,2);
  hptRaw->SetXTitle("p_{T} (GeV)");
  cleverRange(hptRaw,1.8);

  hptRaw->Draw("e");
  hptTrue->Draw("hist same");
  hptResult->Draw("e same");

  leg2->Draw();

}

#ifndef __CINT__
int main () { RooUnfoldExample(); return 0; }  // Main program when run stand-alone
#endif
