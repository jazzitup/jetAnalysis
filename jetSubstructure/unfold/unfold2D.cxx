
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

int mFlag = 0 ;
//==============================================================================
// Global definitions
//==============================================================================

#include "../JssUtils.h"
#include <TPaletteAxis.h>
#include "unfoldingUtil.h"

double statFrac = 001;
double fracStstData = 001;
bool doUnfData = true ;

int lowPtBin = 1;  int highPtBin = 13;
//int lowPtBin = 6;   int highPtBin = 11;

int nPtPannels = highPtBin-lowPtBin+1;

void getMCspectra(int kSample=kPP, int icent=0, int optX=1, int optY=3, TH2D* hmcRaw=0, TH2D* hmcTruth=0, double radius=0.4, bool doReweight=true);
void getDATAspectra(int kSample=kPP, int icent=0, int optX=1, int optY=3, TH2D* hdataRaw=0, double radius=0.4);

void transformSqrt( TH1D* h1=0, TH1D* h2=0);
bool isTooSmall(TH2D* hEntries=0, int recoVarX=0, int recoVarY=0, int minEntries=10);

void unfold2D_matrixWeight0(int kSample = kPP, int optX =1, int optY=2, double radius= 0.4, bool doReweight=false) {
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


  TH2D* hTemp = new TH2D("hptTemp","",nXbins,xBin,nYbins, yBin);
  RooUnfoldResponse* res[7];
  
  TH2D* hmcRaw[7];
  TH2D* hmcTruth[7];
  TH2D* hmcUnf[7][20]; // unfolding iter

  TH2D* hdataRaw[7];
  TH2D* hdataUnf[7][20]; // unfolding iter

  int matrixWeight = 0;
  TFile* fmatrix = new TFile(Form("spectraFiles/unfoldingMatrix2D_coll%d_optX%d_optY%d_radius%.1f_doReweight%d.root",
				  kSample,optX,optY,(float)radius,(int)matrixWeight));
  cout << " matrix name : "  << fmatrix->GetName() << endl;
  
  for ( int i=0 ; i<=6; i++) {
    int icent = i;
    if ( !selectedCent(i) )  continue;
    if ( (kSample == kPP) && ( i != 0 ) )      continue;
    res[i] = (RooUnfoldResponse*)fmatrix->Get(Form("responseMatrix_icent%d",icent));// ignore reweight0 !
  }
  
  for ( int i=0 ; i<=6; i++) {
    int icent = i;
    if ( !selectedCent(icent))       continue;
    if ( (kSample == kPP) && ( icent != 0 ) )      continue;

    // MC 
    hmcRaw[i] = (TH2D*)hTemp->Clone(Form("hmcRaw_icent%d",i));
    hmcTruth[i] = (TH2D*)hTemp->Clone(Form("hmcTruth_icent%d",i));
    getMCspectra(kSample, icent, optX, optY, hmcRaw[i], hmcTruth[i], radius, doReweight) ;

        
    // Data
    if ( doUnfData )  { 
      hdataRaw[i] =  (TH2D*)hTemp->Clone(Form("hdataRaw_icent%d",i));
      getDATAspectra(kSample, icent, optX, optY, hdataRaw[i], radius) ;
    }
    
  }
  
  vector<int> nIter;
  nIter.push_back(1);
  nIter.push_back(2);
  nIter.push_back(4);
  nIter.push_back(6);
  nIter.push_back(8);
  nIter.push_back(12);
  nIter.push_back(16);
  nIter.push_back(20);
  nIter.push_back(40);
  nIter.push_back(100);
  
  cout << "================================ UNFOLD ===================================" << endl;
  for ( int icent=0 ; icent<=6; icent++) {
    if ( !selectedCent(icent) )  continue;
    if ( (kSample == kPP) && ( icent != 0 ) )      continue;
    
    for ( int it = 0 ; it< int(nIter.size()) ; it++) {  
      RooUnfoldBayes unfoldMc (res[icent], hmcRaw[icent], nIter[it]);    
      hmcUnf[icent][it] = (TH2D*)unfoldMc.Hreco();
      hmcUnf[icent][it]->SetName( Form("hmcUnf_icent%d_iter%d",icent,nIter[it]));
    }
    // Data
    if ( doUnfData )  {
      for ( int it = 0 ; it< int(nIter.size()) ; it++) {      
	RooUnfoldBayes unfoldData (res[icent], hdataRaw[icent], nIter[it]);    
	hdataUnf[icent][it]= (TH2D*)unfoldData.Hreco();
	hdataUnf[icent][it]->SetName( Form("hdataUnf_icent%d_iter%d",icent,nIter[it]));
      }
    }
    
  }
  
  // Let's draw.
  TH1D* hmcUnf1d[7][30][20]; // cent, pT bin
  TH1D* hmcTruth1d[7][30]; // cent, pT bin
  TH1D* hmcRaw1d[7][30]; // cent, pT bin
  
  TH1D* hmcUnfSq[7][30][20]; // cent, pT bin
  TH1D* hmcTruthSq[7][30]; // cent, pT bin
  TH1D* hmcRawSq[7][30]; // cent, pT bin
  
  TH1D* hdataUnf1d[7][30][20]; // cent, pT bin
  TH1D* hdataRaw1d[7][30]; // cent, pT bin
  
  TH1D* hdataUnfSq[7][30][20]; // cent, pT bin
  TH1D* hdataRawSq[7][30]; // cent, pT bin

  for ( int icent=0 ; icent<=6; icent++) {
    if ( !selectedCent(icent) )  continue;
    if ( (kSample == kPP) && ( icent != 0 ) )      continue;
    
    // project to 1D
    for ( int ix = 1 ; ix<= nXbins ; ix++) { 
      // mc 
      hmcTruth1d[icent][ix] = (TH1D*)hmcTruth[icent]->ProjectionY(Form("hmcTruth1d_icent%d_ix%d",icent,ix),ix,ix);
      hmcRaw1d[icent][ix] = (TH1D*)hmcRaw[icent]->ProjectionY(Form("hmcRaw1d_icent%d_ix%d",icent,ix),ix,ix);
      for ( int it = 0 ; it< int(nIter.size()) ; it++) {
	hmcUnf1d[icent][ix][it] = (TH1D*)hmcUnf[icent][it]->ProjectionY(Form("hmcUnf1d_icent%d_ix%d_iter%d",icent,ix,nIter[it]),ix,ix);
      }

      hmcTruthSq[icent][ix] = new TH1D(Form("hmcTruthSq_icent%d_ix%d",icent,ix),";m/p_{T};",nYbins,yBinSqrt);
      hmcRawSq[icent][ix] = new TH1D(Form("hmcRawSq_icent%d_ix%d",icent,ix),";m/p_{T};",nYbins,yBinSqrt);
      for ( int it = 0 ; it< int(nIter.size()) ; it++) {
	hmcUnfSq[icent][ix][it] = new TH1D(Form("hmcUnfSq_icent%d_ix%d_iter%d",icent,ix,nIter[it]),";m/p_{T};",nYbins,yBinSqrt);
      }

      int nRebin;
      double yRebin[20];
      getRebinMpt(nRebin, yRebin, icent, ix);

      transformSqrt( hmcTruth1d[icent][ix], hmcTruthSq[icent][ix]) ; 
      hmcTruthSq[icent][ix] = (TH1D*)hmcTruthSq[icent][ix]->Rebin(nRebin,"",yRebin);
      TH1ScaleByWidth(hmcTruthSq[icent][ix]);

      transformSqrt( hmcRaw1d[icent][ix], hmcRawSq[icent][ix]) ; 
      hmcRawSq[icent][ix] = (TH1D*)hmcRawSq[icent][ix]->Rebin(nRebin,"",yRebin);
      TH1ScaleByWidth(hmcRawSq[icent][ix]);

      for ( int it = 0 ; it< int(nIter.size()) ; it++) {      
	transformSqrt( hmcUnf1d[icent][ix][it], hmcUnfSq[icent][ix][it]) ; 
	hmcUnfSq[icent][ix][it]  =	(TH1D*)hmcUnfSq[icent][ix][it]->Rebin(nRebin,"",yRebin);
	TH1ScaleByWidth(hmcUnfSq[icent][ix][it]);
      }
      
      // data
      if ( doUnfData )  {   
	for ( int it = 0 ; it< int(nIter.size()) ; it++) {
	  hdataUnf1d[icent][ix][it] = (TH1D*)hdataUnf[icent][it]->ProjectionY(Form("hdataUnf1d_icent%d_ix%d_iter%d",icent,ix,nIter[it]),ix,ix);
	}
	hdataRaw1d[icent][ix] = (TH1D*)hdataRaw[icent]->ProjectionY(Form("hdataRaw1d_icent%d_ix%d",icent,ix),ix,ix);
	
	hdataRawSq[icent][ix] = new TH1D(Form("hdataRawSq_icent%d_ix%d",icent,ix),";m/p_{T};",nYbins,yBinSqrt);
	for ( int it = 0 ; it< int(nIter.size()) ; it++) {
	  hdataUnfSq[icent][ix][it] = new TH1D(Form("hdataUnfSq_icent%d_ix%d_iter%d",icent,ix,nIter[it]),";m/p_{T};",nYbins,yBinSqrt);
	}	
	
	transformSqrt( hdataRaw1d[icent][ix], hdataRawSq[icent][ix]) ; 
	hdataRawSq[icent][ix] = 	(TH1D*)hdataRawSq[icent][ix]->Rebin(nRebin,"",yRebin);
 TH1ScaleByWidth(hdataRawSq[icent][ix]);
	
	for ( int it = 0 ; it< int(nIter.size()) ; it++) {
	  transformSqrt( hdataUnf1d[icent][ix][it], hdataUnfSq[icent][ix][it]) ; 
	  hdataUnfSq[icent][ix][it] = 	  (TH1D*)hdataUnfSq[icent][ix][it]->Rebin(nRebin,"",yRebin);
 TH1ScaleByWidth(hdataUnfSq[icent][ix][it]);
	}	
	
      }
      
      
    }
  }
  
  TFile * fout = new TFile(Form("unfSpectra/kSample%d_matrixRwt%d_spectraRwt%d.root",kSample,matrixWeight,doReweight),"recreate");
  for ( int icent=0 ; icent<=6; icent++) {
    if ( !selectedCent(icent) )  continue;
    if ( (kSample == kPP) && ( icent != 0 ) )      continue;
    for ( int ix = 1 ; ix<= nXbins ; ix++) {
      
      hmcTruthSq[icent][ix]->Write();
      hmcRawSq[icent][ix]->Write();

      for ( int it = 0 ; it< int(nIter.size()) ; it++) {
	hmcUnfSq[icent][ix][it]->Write();
      }
      if ( doUnfData )  {
	hdataRawSq[icent][ix]->Write();
	for ( int it = 0 ; it< int(nIter.size()) ; it++) {
	  hdataUnfSq[icent][ix][it]->Write();
	}
	
      }
    }
  }
  fout->Close();
  
}


void getMCspectra(int kSample, int icent, int optX, int optY, TH2D* hmcRaw, TH2D* hmcTruth, double radius, bool doReweight) {
  
  TH1::SetDefaultSumw2();
  hmcRaw->Reset();
  hmcTruth->Reset();



  
  //  TFile* checkEntries = new TFile(Form("checkEntry/entries_kSample%d_icent%d_optX%d_optY%d.root",kSample,icent,optX,optY));
  //  TH2D* recoEntries_jz2 = (TH2D*)checkEntries->Get("reco_jz2");
  //  TH2D* recoEntries_jz3 = (TH2D*)checkEntries->Get("reco_jz3");
  //  TH2D* recoEntries_jz4 = (TH2D*)checkEntries->Get("reco_jz4");

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
    //    TH2D* hRecoEntries;
    double jzNorm=0;
    if ( ijz==2)  {
      tr = tr2;
      jzNorm = hi9EvtWgtJZ2;
      //      hRecoEntries = recoEntries_jz2;
    }
    else if ( ijz==3)  {
      tr = tr3;
      jzNorm = hi9EvtWgtJZ3;
      //      hRecoEntries = recoEntries_jz3;
    }
    else if ( ijz==4)  {
      tr = tr4;
      jzNorm = hi9EvtWgtJZ4;
      //      hRecoEntries = recoEntries_jz4;
    }
    
  


    TH2D* hReweight;
    TFile* fReweight;
    if ( doReweight ) {
      fReweight = new TFile(fReweightName);
      //      hReweight = (TH2D*)fReweight->Get(Form("hRatioSmooth_kSample%d_icent%d_opt1",kSample,icent));
      hReweight = (TH2D*)fReweight->Get(Form("hRatioFit_kSample%d_icent%d_opt2",kSample,icent));
    }



    cout << "Scanning JZ"<<ijz<<" file.  Total events = " << tr->GetEntries() << endl;
    for (Int_t i= 0; i<tr->GetEntries() ; i++) {
      if ( i > tr->GetEntries() * statFrac ) continue;
      if (i%2==0)  continue;

      tr->GetEntry(i);

      if ( ! passEvent(myJetMc, icent, true) ) // isMC = true
        continue;
      
      double recoVarX, truthVarX;
      getXvalues( recoVarX, truthVarX, myJetMc, optX);
      double recoVarY, truthVarY;
      getYvalues( recoVarY, truthVarY, myJetMc, optY);

      
      // Black list?
      //      if ( isTooSmall(hRecoEntries, recoVarX, recoVarY,10) ) {
	//        cout << "isTooSmall! " << endl;
	//        cout << "jz"<<ijz<<":   pT, (m/pT)^2 =" << recoVarX <<", "<<recoVarY<<endl;
      //        continue;
      //      }
    
      double rewFact = 1;
      if ( doReweight) {
	double recoM2 = myJetMc.recoMass * myJetMc.recoMass;
        double recoPt2 = myJetMc.recoPt * myJetMc.recoPt;
	if ( myJetMc.recoMass < 0 ) recoM2 = - recoM2;
        double recoVarY =  recoM2 / recoPt2;

	int rewBin = hReweight->FindBin(myJetMc.recoPt, myJetMc.recoMass / myJetMc.recoPt);
        rewFact = hReweight->GetBinContent(rewBin);
	
	//	rewFact = 3000 + recoVarX ;

	
        // ONLY FOR 0-10% PbPb
	//        if ( (icent == 0) && ( kSample==kPbPb) ) {
	//          rewFact = 63619.9 + 240 * recoVarX ;
	//        }
      }
      
      
      //      rewFact = 600 + recoVarX ;
      //      if ( doReweight) {
      //        int rewBin = hReweight->FindBin(recoVarX,recoVarY);
      //        rewFact = hReweight->GetBinContent(rewBin);
      //      }

      hmcRaw->Fill( recoVarX, recoVarY, myJetMc.weight * rewFact * jzNorm);
      hmcTruth->Fill( truthVarX, truthVarY, myJetMc.weight * rewFact * jzNorm );
    }
  }
  
}


void getDATAspectra(int kSample, int icent, int optX, int optY, TH2D* hdataRaw, double radius) {
  TH1::SetDefaultSumw2();
  hdataRaw->Reset();





  TString fname;
  if ( radius == 0.4 ) {
    if ( kSample == kPbPb ) {
      fname = "jetSubstructure_Data_HION9_v4.7_r4_pbpb_Jan23_ptCut90Eta2.1.root"; }
    else if ( kSample == kPP) {
      fname = "jetSubstructure_data_HION9_v4.7_r4_pp_Feb26_ptCut90Eta2.1_fullLumi.root"; }
  }
  
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

    double recoVarX, truthVarX;
    getXvalues( recoVarX, truthVarX, myJet, optX);
    double recoVarY, truthVarY;
    getYvalues( recoVarY, truthVarY, myJet, optY);
    

    hdataRaw->Fill ( recoVarX, recoVarY); 
  }
  
}

void transformSqrt( TH1D* h1, TH1D* h2) { 
  h2->Reset();
  for ( int i = 1 ; i <=h1->GetNbinsX() ; i++) {
    h2->SetBinContent(i,  h1->GetBinContent(i) );
    h2->SetBinError(i,  h1->GetBinError(i) );
  }
}


bool isTooSmall(TH2D* hEntries, int recoVarX, int recoVarY, int minEntries) {
  int theBin = hEntries->FindBin(recoVarX, recoVarY);
  if (  hEntries->GetBinContent(theBin) < minEntries )
    return true;

  return false;

}


#ifndef __CINT__
int main2 () { unfold2D_matrixWeight0(); return 0; }  // Main program when run stand-alone
#endif





