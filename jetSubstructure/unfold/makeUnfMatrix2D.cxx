
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

RooUnfoldResponse* getResponse( int kSample = kPP, int icent = 0, int optX=1, int optY=2, TH2D* hTruth=0, TH2D* hReco=0, TH2D* respX=0, TH2D* respY=0, double radius =0.4,bool doReweight = true);

bool isTooSmall(TH2D* hEntries=0, int recoVarX=0, int recoVarY=0, int minEntries=10);

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
  
  TH2D* hMatrix[7]; // 4-d matrix unrolled to 2-d
  
  TH2D* hResX[7]; // response matrix for pT ( mass integrated)
  TH2D* hResY[7]; // response matrix for mass ( pT integrated)
  TH2D* h2dtempM = new TH2D("h2dtemp",";Truth (m/p_{T})^{2};Reco (m/p_{T})^{2}",100,-0.02,0.12,100,-0.02,0.12);
  for ( int i=0 ; i<=6; i++) {
    int icent = i;
    if ( !selectedCent(icent))       continue;
    if ( (kSample == kPP) && ( icent != 0 ) )      continue;

    hTruth[i] = (TH2D*)hTruthTemp->Clone(Form("%s_icent%d",hTruthTemp->GetName(),i));
    hReco[i] = (TH2D*)hRecoTemp->Clone(Form("%s_icent%d",hRecoTemp->GetName(),i));
    hTruth[i]->Reset();
    hReco[i]->Reset();
    
    hResX[i] = new TH2D(Form("hResPt_icent%d",icent), ";Truth p_{T} (GeV/c);Reco p_{T} (GeV/c)",nXbins,xBin,nXbins,xBin);
    hResY[i] = new TH2D(Form("hResM_icent%d",icent), ";Truth (m/p_{T})^{2};Reco (m/p_{T})^{2}",nYbins,yBin,nYbins,yBin);

    res[i] = getResponse(kSample, i, optX, optY, hTruth[i], hReco[i], hResX[i], hResY[i], radius,doReweight);

    TCanvas* c01 = new TCanvas("c01", "",600,500);
    hMatrix[i] = (TH2D*)res[i]->Hresponse();
    hMatrix[i]->SetXTitle("Bin # of reco (p_{T}, m/p_{T})");
    hMatrix[i]->SetYTitle("Bin # of truth (p_{T}, m/p_{T})");
    hMatrix[i]->SetTitle("MC Response matrix");
    c01->SetRightMargin(0.2);
    hMatrix[i]->Draw("colz");
    c01->SaveAs(Form("pdfs/correlation_2dUnf_coll%d_cent%d_radius0%d_doReweight%d.pdf",kSample,i,(int)(radius*10.),doReweight));
    TCanvas* c02 = new TCanvas("c02","",1000,500);
    c02->Divide(2,1);
    c02->cd(1);
    hResX[i]->SetNdivisions(505,"X");
    hResX[i]->Draw("colz");
    c02->cd(1)->SetRightMargin(0.2);
    gPad->SetLogz();
    c02->cd(2);
    h2dtempM->SetNdivisions(505,"X");
    h2dtempM->Draw();
    hResY[i]->Draw("colz same");
    c02->cd(2)->SetRightMargin(0.2);
    gPad->SetLogz();
    c02->SaveAs(Form("pdfs/PtMassResp_coll%d_cent%d_radius%.1f_doReweight%d.pdf",kSample,i,(float)radius,doReweight));
    
  }
  
  TFile* fout = new TFile(Form("spectraFiles/unfoldingMatrix2D_coll%d_optX%d_optY%d_radius%.1f_doReweight%d.root",kSample,optX,optY,(float)radius,(int)doReweight),"recreate");
  for ( int i=0 ; i<=6; i++) {
    int icent = i;
    if ( !selectedCent(icent))      continue;
    if ( (kSample == kPP) && ( icent !=0 ) )      continue;
    res[i]->Write();
    hMatrix[i]->Write();
  }
  fout->Close();
}

RooUnfoldResponse* getResponse(int kSample,  int icent,  int optX, int optY, TH2D* hTruth, TH2D* hReco, TH2D* respX, TH2D* respY, double radius, bool doReweight)
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
    fReweight = new TFile(fReweightName);
    //    hReweight = (TH2D*)fReweight->Get(Form("hRatioSmooth_kSample%d_icent%d_opt2",kSample,icent));
    //    hReweight = (TH2D*)fReweight->Get(Form("hRatioFit_kSample%d_icent%d_opt2",kSample,icent));
    hReweight = (TH2D*)fReweight->Get(Form("hRatioSmooth_kSample%d_icent%d_opt771",kSample,icent));
  }
  
  TFile* checkEntries = new TFile(Form("checkEntry/entries_kSample%d_icent%d_optX%d_optY%d.root",kSample,icent,optX,optY));
  TH2D* recoEntries_jz2 = (TH2D*)checkEntries->Get("reco_jz2");
  TH2D* recoEntries_jz3 = (TH2D*)checkEntries->Get("reco_jz3");
  TH2D* recoEntries_jz4 = (TH2D*)checkEntries->Get("reco_jz4");
  
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
  res->SetName(Form("responseMatrix_icent%d",icent));

  for ( int ijz =2 ; ijz<=4 ; ijz++) { 
    TTree* tr;
    TH2D* hRecoEntries;
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
      if ( i > tr->GetEntries() * fracStst ) continue;
      tr->GetEntry(i);
      
      if ( ! passEvent(myJetMc, icent, true) ) // isMC = true
	continue;

      double recoVarX, truthVarX;
      getXvalues( recoVarX, truthVarX, myJetMc, optX);

      double recoVarY, truthVarY;
      getYvalues( recoVarY, truthVarY, myJetMc, optY);
      
      // Black list?
      if ( isTooSmall(hRecoEntries, recoVarX, recoVarY,10) ) {
	cout << "isTooSmall! " << endl;
	cout << "jz"<<ijz<<":   pT, (m/pT)^2 =" << recoVarX <<", "<<recoVarY<<endl;
	continue;
      }
      
      // Data/MC reweighting factors 
      double rewFact = 1; 
      if ( doReweight) { 
	
	//        int rewBin = hReweight->FindBin(myJetMc.recoPt, myJetMc.recoMass / myJetMc.recoPt);
	int rewBin = hReweight->FindBin(myJetMc.recoPt, myJetMc.recoMass);

      	rewFact = hReweight->GetBinContent(rewBin);
	
	// ONLY FOR 0-10% PbPb
	//	if ( (icent == 0) && ( kSample==kPbPb) ) { 
	//	  rewFact = 63619.9 + 240 * recoVarX ; 
	//  }
      }
      
      if ( useFullMC || (i%2==0) )  {
	res->Fill(  recoVarX, recoVarY, truthVarX, truthVarY, myJetMc.weight * rewFact * jzNorm);
	respX->Fill( truthVarX, recoVarX,  myJetMc.weight * rewFact * jzNorm);
	respY->Fill( truthVarY, recoVarY,  myJetMc.weight * rewFact * jzNorm);

      }
    }
  }
  return res;
}

bool isTooSmall(TH2D* hEntries, int recoVarX, int recoVarY, int minEntries) {
  int theBin = hEntries->FindBin(recoVarX, recoVarY);
  if (  hEntries->GetBinContent(theBin) < minEntries ) 
    return true;

  return false;
  
}


#ifndef __CINT__
int main () { makeUnfMatrix2D(); return 0; }  // Main program when run stand-alone
#endif


