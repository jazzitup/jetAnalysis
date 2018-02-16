
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

#include "../JssUtils.h"
#include <TPaletteAxis.h>
#include "unfoldingUtil.h"

double fracStst = 0001;

double minPt = 100;
double minPtMcTruth = 20;
TString prefix = ""; //Form("ptCut_%d_%d",(int)minPt,(int)minPtMcTruth);

void checkEntries(int kSample= kPP, int icent = 0, int optX =1, int optY=2) {
  
  double radius=0.4;
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
  TH2D* hTruth[10]; // jz N
  TH2D* hReco[10]; // jz N
  
  TH1::SetDefaultSumw2();
  
  TString jz2;  
  TString jz3;
  TString jz4;
  if ( radius==0.4 )      {
    if ( kSample == kPbPb )  	{
      jz2 = "jetSubstructure_MC_HION9_jz2_v4.7_v4_Jan23_ptCut90Eta2.1.root";
      jz3 = "jetSubstructure_MC_HION9_jz3_v4.7_v4_Jan23_ptCut90Eta2.1.root";
      jz4 = "jetSubstructure_MC_HION9_jz4_v4.7_v4_Jan23_ptCut90Eta2.1.root";
    }
    else if ( kSample == kPP ) {
      if ( radius==0.4 ) {
	jz2 = "jetSubstructure_MC_HION9_jz2_v4.7_r4_pp_Jan23_ptCut90Eta2.1.root";
	jz3 = "jetSubstructure_MC_HION9_jz3_v4.7_r4_pp_Jan23_ptCut90Eta2.1.root";
	jz4 = "jetSubstructure_MC_HION9_jz4_v4.7_r4_pp_Jan23_ptCut90Eta2.1.root";
      }
    }
  }
  
  jetSubStr  myJetMc;
  TBranch  *b_myJetSubMc;

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
      tr = tr2;      jzNorm = hi9EvtWgtJZ2;
    }
    else if ( ijz==3)  {
      tr = tr3;      jzNorm = hi9EvtWgtJZ3;
    }
    else if ( ijz==4)  {
      tr = tr4;      jzNorm = hi9EvtWgtJZ4;
    }

    hTruth[ijz] = (TH2D*)hTruthTemp->Clone(Form("truth_jz%d",ijz));
    hReco[ijz] = (TH2D*)hRecoTemp->Clone(Form("reco_jz%d",ijz));
    
    hTruth[ijz]->Reset();
    hReco[ijz]->Reset();
    
    for (Int_t i= 0; i<tr->GetEntries() ; i++) {
      if ( i > tr->GetEntries() * fracStst ) continue;

      tr->GetEntry(i);
      
      if ( myJetMc.cent != icent ) continue;

      double recoVarX, truthVarX;
      getXvalues( recoVarX, truthVarX, myJetMc, optX);

      double recoVarY, truthVarY;
      getYvalues( recoVarY, truthVarY, myJetMc, optY);
      
      hTruth[ijz]->Fill( truthVarX, truthVarY);
      hReco[ijz]->Fill( recoVarX, recoVarY);
    }
    TCanvas* c1 = new TCanvas(Form("c_jz%d",ijz),"",1200,600);  
    c1->Divide(2,1);
    c1->cd(1);
    hTruth[ijz]->Draw("TEXT45 colz");
    c1->cd(1)->SetRightMargin(0.2);
    gPad->SetLogz();
    c1->cd(2);
    hReco[ijz]->Draw("TEXT45 colz");
    c1->cd(2)->SetRightMargin(0.2);
    gPad->SetLogz();
    c1->SaveAs(Form("checkEntry/raw_entries_kSample%d_icent%d_optX%d_optY%d_jz%d.pdf",kSample,icent,optX,optY,ijz));
    c1->SaveAs(Form("checkEntry/raw_entries_kSample%d_icent%d_optX%d_optY%d_jz%d.png",kSample,icent,optX,optY,ijz));

    for ( int ix=1 ;ix <=nXbins ; ix++) {
      for ( int iy=1 ;iy <=nYbins ; iy++) {
	double val = hReco[ijz]->GetBinContent(ix,iy);
	if ( val == 0) continue; 
	if (val < 10 ) {
	  cout << "N = " << val << endl; 
	  cout << " x : " << xBin[ix-1] <<" , " << xBin[ix] << endl;
	  cout << " y : " << yBin[iy-1] <<" , " << yBin[iy] << endl;
	}
      }
    }
  }
  
  TFile* fout = new TFile(Form("checkEntry/entries_kSample%d_icent%d_optX%d_optY%d.root",kSample,icent,optX,optY),"recreate");
    for ( int ijz =2 ; ijz<=4 ; ijz++) {
      hReco[ijz]->Write();
      hTruth[ijz]->Write();
    }
}
