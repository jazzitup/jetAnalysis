
#if !(defined(__CINT__) || defined(__CLING__)) || defined(__ACLIC__)
#include <iostream>
using std::cout;
using std::endl;

#include "TRandom.h"
#include "TH1D.h"
#include "TH2D.h"

//#include "RooUnfoldResponse.h"
//#include "RooUnfoldBayes.h"

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

bool useFullMC = false;

void getResponse( int kSample = kPP, int icent = 0, int optX=1, int optY=2, TH1D* hTruth1d=0, TH1D* hReco1d=0, TH2D* hMatrix=0, TH2D* respX=0, TH2D* respY=0, double radius =0.4,bool doReweight = true);

bool isTooSmall(TH2D* hEntries=0, int recoVarX=0, int recoVarY=0, int minEntries=10);

void makeUnfMatrix2D(int kSample = kPbPb, int optX =1, int optY=2, double radius= 0.4, bool doReweight=true) {
  TH1::SetDefaultSumw2();
  int nXbins;
  double xBin[30];
  getXbin(nXbins, xBin, optX);
  cout << " nXbins = " << nXbins << endl; 
  cout << " xBin = " << xBin[0] << ",   " << xBin[1] << ",   " <<xBin[2] << ", ..." <<endl;
  
  TH1D* histXbin = new TH1D("histXbin","",nXbins, xBin);

  int nYbins ;
  double yBin[30] ;
  getYbin(nYbins, yBin, optY);

  TH1D* histYbin = new TH1D("histYbin","",nYbins, yBin);

  TH2D* hTruthTemp = new TH2D("hTruth","",nXbins,xBin,nYbins,yBin);
  TH2D* hRecoTemp = (TH2D*)hTruthTemp->Clone("hReco");

  
  //  TH2D* hTruth[7];
  //  TH2D* hReco[7];
  
  TH1D* hTruth1d[7];
  TH1D* hReco1d[7];
  TH2D* hMatrix[7];   
  
  
  TH2D* hResX[7]; // response matrix for pT ( mass integrated)
  TH2D* hResY[7]; // response matrix for mass ( pT integrated)
  TH2D* h2dtempM = new TH2D("h2dtemp",";Truth m/p_{T};Reco m/p_{T}",100,-0.5,0.5,100,-0.5,0.5);
  for ( int i=0 ; i<=6; i++) {
    int icent = i;
    if ( !selectedCent(icent))       continue;
    if ( (kSample == kPP) && ( icent != 0 ) )      continue;

    //    hTruth[i] = (TH2D*)hTruthTemp->Clone(Form("%s_icent%d",hTruthTemp->GetName(),i));
    //    hReco[i] = (TH2D*)hRecoTemp->Clone(Form("%s_icent%d",hRecoTemp->GetName(),i));
    //    hTruth[i]->Reset();
    //    hReco[i]->Reset();
    
    hTruth1d[i] = new TH1D(Form("hTruth1d_icent%d",i),"",maxBin1d,0.5,maxBin1d+0.5);
    hReco1d[i] = new TH1D(Form("hReco1d_icent%d",i),"",maxBin1d,0.5,maxBin1d+0.5);
    hMatrix[i] = new TH2D(Form("hMatrix1d_icent%d",i),"",maxBin1d,0.5,maxBin1d+0.5, maxBin1d,0.5,maxBin1d+0.5);
    
    hResX[i] = new TH2D(Form("hResPt_icent%d",icent), ";Truth p_{T} (GeV/c);Reco p_{T} (GeV/c)",nXbins,xBin,nXbins,xBin);
    hResY[i] = new TH2D(Form("hResM_icent%d",icent), ";Truth m/p_{T};Reco m/p_{T}",nYbins,yBin,nYbins,yBin);

    getResponse(kSample, i, optX, optY, hTruth1d[i], hReco1d[i], hMatrix[i], hResX[i], hResY[i], radius,doReweight);

    TCanvas* c01 = new TCanvas("c01", "",600,500);
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
    hMatrix[i]->Write();
    hReco1d[i]->Write();
    hTruth1d[i]->Write();
    
  }
  fout->Close();
}

void getResponse(int kSample,  int icent,  int optX, int optY, TH1D* hTruth1d, TH1D* hReco1d, TH2D* hMatrix, TH2D* respX, TH2D* respY, double radius, bool doReweight)
{
  TH1::SetDefaultSumw2();
  int nXbins;
  double xBin[30];
  getXbin(nXbins, xBin, optX);
  TH1D* histXbin = new TH1D("histXbin","",nXbins, xBin);

  int nYbins ;
  double yBin[30] ;
  getYbin(nYbins, yBin, optY);
  TH1D* histYbin = new TH1D("histYbin","",nYbins, yBin);


  TString jz2;
  TString jz3;
  TString jz4;
  if ( kSample == kPbPb ) {
    if ( radius==0.4 ) {
      // v50
      //      jz2 = "jetSubstructure_MC_HION9_pbpb_v50_jz2.root";
      //      jz3 = "jetSubstructure_MC_HION9_pbpb_v50_jz3.root";
      //      jz4 = "jetSubstructure_MC_HION9_pbpb_v50_jz4.root";
      jz2 = "jetSubstructure_MC_HION9_jz2_v4.7_v4_Jan23_ptCut90Eta2.1.root";
      jz3 = "jetSubstructure_MC_HION9_jz3_v4.7_v4_Jan23_ptCut90Eta2.1.root";
      jz4 = "jetSubstructure_MC_HION9_jz4_v4.7_v4_Jan23_ptCut90Eta2.1.root";
    }
  }
  else if ( kSample == kPP ) {
    if ( radius==0.4 ) {
      //  jz2 = "jetSubstructure_MC_HION9_pp_v50_jz2.root";
      //      jz3 = "jetSubstructure_MC_HION9_pp_v50_jz3.root";
      //      jz4 = "jetSubstructure_MC_HION9_pp_v50_jz4.root";
      jz2 = "jetSubstructure_MC_HION9_jz2_v4.7_r4_pp_Jan23_ptCut90Eta2.1.root";
      jz3 = "jetSubstructure_MC_HION9_jz3_v4.7_r4_pp_Jan23_ptCut90Eta2.1.root";
      jz4 = "jetSubstructure_MC_HION9_jz4_v4.7_r4_pp_Jan23_ptCut90Eta2.1.root";
    }
  }
  
  TH1D* hFcalReweight;
  if ( kSample == kPbPb ) {
    //    TFile* fcal = new TFile("reweightFactors/FCal_HP_v_MB_weights.root");
    //    hFcalReweight = (TH1D*)fcal->Get("FCal_HP_v_MBOV_weights");
  }
  
  
  TH2D* hReweight;
  if ( doReweight ) {
    hReweight = getRewTable(kSample, icent);
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
      
      if ( useFullMC && (i%2==0) )
	continue;
      
      if ( ! passEvent(myJetMc, icent, true) ) // isMC = true
	continue;
      
      double recoVarX, truthVarX;
      getXvalues( recoVarX, truthVarX, myJetMc, optX);
      
      double recoVarY, truthVarY;
      getYvalues( recoVarY, truthVarY, myJetMc, optY);
      
      double fcalWeight = 1.0; 
      if ( kSample==kPbPb) {
	//	fcalWeight = hFcalReweight->GetBinContent(hFcalReweight->GetXaxis()->FindBin(myJetMc.fcalet));
      }
      
      // Data/MC reweighting factors 
      double rewFact = 1; 
      if ( doReweight) { 
	int rewBin = hReweight->FindBin(myJetMc.recoPt, myJetMc.recoMass);
	rewFact = hReweight->GetBinContent(rewBin);
      }

      int truthXbin = histXbin->FindBin( truthVarX) ;
      int recoXbin = histXbin->FindBin( recoVarX) ;
      int truthYbin = histYbin->FindBin( truthVarY) ;
      int recoYbin = histYbin->FindBin( recoVarY) ;
      
      int truth1dBin = get1dBin( truthXbin,truthYbin);
      int reco1dBin = get1dBin( recoXbin, recoYbin);
      
      hTruth1d->Fill( truth1dBin, myJetMc.weight * rewFact * jzNorm * fcalWeight);
      hReco1d->Fill( reco1dBin, myJetMc.weight * rewFact * jzNorm * fcalWeight);
      hMatrix->Fill( reco1dBin, truth1dBin, myJetMc.weight * rewFact * jzNorm * fcalWeight);
      
      respX->Fill( truthVarX, recoVarX,  myJetMc.weight * rewFact * jzNorm* fcalWeight);
      respY->Fill( truthVarY, recoVarY,  myJetMc.weight * rewFact * jzNorm* fcalWeight);
      
      
    }
  }

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


