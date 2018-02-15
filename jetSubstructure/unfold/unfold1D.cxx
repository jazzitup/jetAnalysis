
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

void getMCspectra(int kSample=kPP, int icent=0, int optX=1, TH1D* hmcRaw=0, TH1D* hmcTruth=0, double radius=0.4);

void unfold1D(int kSample = kPP, int optX =1, double radius= 0.4, int nIter=1) {
  TH1::SetDefaultSumw2();
  int nXbins;
  double xBin[30];
  getXbin(nXbins, xBin, optX);
  cout << " nXbins = " << nXbins << endl; 
  cout << " xBin = " << xBin[0] << ",   " << xBin[1] << ",   " <<xBin[2] << ", ..." <<endl;

  TH1D* hTemp = new TH1D("hptTemp","",nXbins,xBin);
  RooUnfoldResponse* res[7];
  
  TH1D* hmcRaw[7];
  TH1D* hmcTruth[7];
  TH1D* hmcUnf[7];
  TH1D* hmcRatio[7];  // unf / truth

  TH1D* hdataRaw[7];
  //  TH1D* hdataTruth[7];
  TH1D* hdataUnf[7];
  
  int matrixWeight = 1;
  TFile* fmatrix = new TFile(Form("spectraFiles/unfoldingMatrix1D_coll%d_optX%d_radius%.1f_doReweight%d.root",kSample,optX,(float)radius,matrixWeight));
  
  for ( int i=0 ; i<=6; i++) {
    int icent = i;
    if ( !selectedCent(i) )  continue;
    if ( (kSample == kPP) && ( i != 0 ) )      continue;
    res[i] = (RooUnfoldResponse*)fmatrix->Get(Form("responseMatrix_icent%d_reweight0",icent)); // Ignore reweight0!!!
  }
  
  for ( int i=0 ; i<=6; i++) {
    int icent = i;
    if ( !selectedCent(icent))       continue;
    if ( (kSample == kPP) && ( icent != 0 ) )      continue;

    hmcRaw[i] = (TH1D*)hTemp->Clone(Form("hmcRaw_icent%d",i));
    hmcTruth[i] = (TH1D*)hTemp->Clone(Form("hmcTruth_icent%d",i));
    hmcUnf[i] = (TH1D*)hTemp->Clone(Form("hmcUnf_icent%d",i));
    
    getMCspectra(kSample, icent, optX, hmcRaw[i], hmcTruth[i], radius) ;
  }

  cout << "================================ MC UNFOLD ===================================" << endl;
  for ( int icent=0 ; icent<=6; icent++) {
    if ( !selectedCent(icent) )  continue;
    if ( (kSample == kPP) && ( icent != 0 ) )      continue;
    
    RooUnfoldBayes unfoldMc (res[icent], hmcRaw[icent], nIter);    // OR
    hmcUnf[icent]  = (TH1D*)unfoldMc.Hreco();
    hmcUnf[icent]->SetName( Form("hmcUnf_icent%d",icent));

    TH1ScaleByWidth(hmcUnf[icent]);
    TH1ScaleByWidth(hmcTruth[icent]);
    TH1ScaleByWidth(hmcRaw[icent]);
    
    
    hmcRatio[icent] = (TH1D*)hmcUnf[icent]->Clone(Form("hmcRatio_icent%d",icent));
    hmcRatio[icent]->Divide(hmcTruth[icent]);
    
    TCanvas* c1 = new TCanvas(Form("c1_icent%d",icent),"",600,800);
    makeEfficiencyCanvas(c1,1,  0.05, 0.01, 0.1, 0.3, 0.01);
    c1->cd(1);
    cleverRangeLog(hmcTruth[icent],10,0.000000001);
    handsomeTH1(hmcTruth[icent],1);
    handsomeTH1(hmcUnf[icent],2);
    hmcTruth[icent]->Draw("hist");
    hmcUnf[icent]->Draw("same");
    gPad->SetLogy();
    c1->cd(2);
    handsomeTH1(hmcRatio[icent],1);
    hmcRatio[icent]->SetAxisRange(0.,2,"Y");
    hmcRatio[icent]->Draw();
    jumSun(20,1,1000,1);
    drawText(Form("%dth iteration",nIter),0.45,0.75,2,16);
    c1->SaveAs(Form("mcUnfodling_kSample%d_icent%d_matrixRwt%d_iter%d.pdf",kSample,icent,matrixWeight,nIter));
    c1->SaveAs(Form("mcUnfodling_kSample%d_icent%d_matrixRwt%d_iter%d.png",kSample,icent,matrixWeight,nIter));
  }
}


void getMCspectra(int kSample, int icent, int optX, TH1D* hmcRaw, TH1D* hmcTruth, double radius) {
  
  TH1::SetDefaultSumw2();
  hmcRaw->Reset();
  hmcTruth->Reset();

  TString jz2;
  TString jz3;
  TString jz4;
  if ( kSample == kPbPb ) {
    if ( radius==0.4 ) {
      jz2 = "jetSubstructure_MC_HION9_jz2_v4.7_v4_Jan23_ptCut90Eta2.1.root";
      jz3 = "jetSubstructure_MC_HION9_jz3_v4.7_v4_Jan23_ptCut90Eta2.1.root";
      jz4 = "jetSubstructure_MC_HION9_jz4_v4.7_v4_Jan23_ptCut90Eta2.1.root";
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
      //      if ( i > tr->GetEntries() ) continue;
      tr->GetEntry(i);

      if ( ! passEvent(myJetMc, icent, true) ) // isMC = true
        continue;

      double recoVarX, truthVarX;
      getXvalues( recoVarX, truthVarX, myJetMc, optX);
      // Data/MC reweighting factors
      double rewFact = 1;
      //      if ( doReweight) {
      //        int rewBin = hReweight->FindBin(recoVarX,recoVarY);
      //        rewFact = hReweight->GetBinContent(rewBin);
      //      }

      hmcRaw->Fill( recoVarX, myJetMc.weight * rewFact * jzNorm);
      hmcTruth->Fill( truthVarX, myJetMc.weight * rewFact * jzNorm );
    }
  }
  
}



#ifndef __CINT__
int main2 () { unfold1D(); return 0; }  // Main program when run stand-alone
#endif





