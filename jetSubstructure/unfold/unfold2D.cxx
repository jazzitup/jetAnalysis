
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
//#include "../ntupleDefinition_v50.h"
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
bool doUnfData = false ;

bool useFullMC = false;

int lowPtBin = 1;  int highPtBin = 13;
//int lowPtBin = 6;   int highPtBin = 11;

int nPtPannels = highPtBin-lowPtBin+1;

void getMCspectra(int kSample=kPP, int icent=0, int optX=1, int optY=2, TH1D* hmcRawFlat=0, TH1D* hmcTruthFlat=0, double radius=0.4, bool doReweight=true);
void getDATAspectra(int kSample=kPP, int icent=0, int optX=1, int optY=2, TH2D* hdataRaw=0, double radius=0.4);

void unflatten( TH1D* hFlat=0, TH2D* h2d=0) ;

bool isTooSmall(TH2D* hEntries=0, int recoVarX=0, int recoVarY=0, int minEntries=10);

void unfold2D(int kSample = kPP, int optX =1, int optY=2, double radius= 0.4, bool doReweight=false) {
  TH1::SetDefaultSumw2();
  int nXbins;
  double xBin[30];
  getXbin(nXbins, xBin, optX);
  cout << " nXbins = " << nXbins << endl; 
  cout << " xBin = " << xBin[0] << ",   " << xBin[1] << ",   " <<xBin[2] << ", ..." <<endl;

  int nYbins ;
  double yBin[30] ;
  getYbin(nYbins, yBin, optY);


  TH2D* hTemp = new TH2D("hptTemp","",nXbins,xBin,nYbins, yBin);
  TH1D* hTempFlat =  new TH1D("hTempFlat","",maxBin1d,0.5,maxBin1d+0.5);

  RooUnfoldResponse* res[7];

  const int maxIter = 60;
  
  TH2D* hmcRaw[7];
  TH2D* hmcTruth[7];
  TH2D* hmcUnf[7][maxIter]; // unfolding iter

  TH1D* hmcRawFlat[7];
  TH1D* hmcTruthFlat[7];
  TH1D* hmcUnfFlat[7][maxIter]; // unfolding iter

  TH2D* hdataRaw[7];
  TH2D* hdataUnf[7][maxIter]; // unfolding iter

  TH1D* hdataRawFlat[7];
  TH1D* hdataUnfFlat[7][maxIter]; // unfolding iter

  int matrixWeight = 1;
  TFile* fmatrix = new TFile(Form("spectraFiles/unfoldingMatrix2D_coll%d_optX%d_optY%d_radius%.1f_doReweight%d.root",
				  kSample,optX,optY,(float)radius,(int)matrixWeight));
  cout << " matrix name : "  << fmatrix->GetName() << endl;
  
  
  for ( int i=0 ; i<=6; i++) {
    int icent = i;
    if ( !selectedCent(icent))       continue;
    if ( (kSample == kPP) && ( icent != 0 ) )      continue;

    // MC 
    hmcRawFlat[i] = (TH1D*)hTempFlat->Clone(Form("hmcRawFlat_icent%d",i));
    hmcTruthFlat[i] = (TH1D*)hTempFlat->Clone(Form("hmcTruthFlat_icent%d",i));
    getMCspectra(kSample, icent, optX, optY, hmcRawFlat[i], hmcTruthFlat[i], radius, doReweight) ;

        
    // Data
    if ( doUnfData )  { 
      hdataRaw[i] =  (TH2D*)hTemp->Clone(Form("hdataRaw_icent%d",i));
      getDATAspectra(kSample, icent, optX, optY, hdataRaw[i], radius) ;
    }
    
  }

  for ( int i=0 ; i<=6; i++) {
    int icent = i;
    if ( !selectedCent(i) )  continue;
    if ( (kSample == kPP) && ( i != 0 ) )      continue;
    //    res[i] = (RooUnfoldResponse*)fmatrix->Get(Form("responseMatrix_icent%d",icent)); //
    //    res[i] = new RooUnfoldResponse(hmcRaw[i], hmcTruth[i], h2ResMatrix);
    //    TH2D* h2Reco  = (TH2D*)fmatrix->Get(Form("hReco_icent%d",icent)); //
    //    TH2D* h2Truth = (TH2D*)fmatrix->Get(Form("hTruth_icent%d",icent)); //
    //RooUnfoldResponse* tempRes  = (RooUnfoldResponse*)fmatrix->Get(Form("responseMatrix_icent%d",icent)); //
    //    TH2D* h2ResMatrix = (TH2D*)tempRes->Hresponse(); 
    //    res[i] = new RooUnfoldResponse(hmcRaw[i], hmcTruth[i], h2ResMatrix);
    //    res[i] = new RooUnfoldResponse(0,0, h2ResMatrix);
    //    TH2D* h2Reco  = (TH2D*)fmatrix->Get(Form("hReco_icent%d",icent)); //
    //    TH2D* h2Truth = (TH2D*)fmatrix->Get(Form("hTruth_icent%d",icent)); //
    //    TH2D* h2RecoTemp = (TH2D*)h2Reco->Clone("h2RecoTemp");
    //    TH2D* h2TruthTemp = (TH2D*)h2Truth->Clone("h2TruthTemp");
    //    h2RecoTemp->Reset();
    //    h2TruthTemp->Reset();
    
    TH2D* h2ResMatrix = (TH2D*)fmatrix->Get(Form("hMatrix1d_icent%d",icent));
    //    TH1D* hReco1d =     (TH1D*)fmatrix->Get(Form("hReco1d_icent%d",icent));
    //    TH1D* hTruth1d = (TH1D*)fmatrix->Get(Form("hTruth1d_icent%d",icent));
    res[i] = new RooUnfoldResponse(hmcRawFlat[icent], hmcTruthFlat[icent], h2ResMatrix);
    //    res[i] = new RooUnfoldResponse(0, 0, h2ResMatrix);
    //    res[i] = new RooUnfoldResponse(hmcRawFlat[i], hmcTruthFlat[i], h2ResMatrix);
    //    res[i] = new RooUnfoldResponse(h2Reco, h2Truth, h2ResMatrix);
    //res[i] = (RooUnfoldResponse*)fmatrix->Get(Form("responseMatrix_icent%d",icent)); 
    
  }
  
  
  
  vector<int> nIter;
  for ( int it = 1 ; it<=15 ; it++) { 
    nIter.push_back(it);
    if ( it > maxIter -1 )   cout << " The size of array is not enough! " << endl;
  }
  
  cout << "================================ UNFOLD ===================================" << endl;
  for ( int icent=0 ; icent<=6; icent++) {
    if ( !selectedCent(icent) )  continue;
    if ( (kSample == kPP) && ( icent != 0 ) )      continue;
    
    for ( int it = 0 ; it< int(nIter.size()) ; it++) {  
      RooUnfoldBayes unfoldMc (res[icent], hmcRawFlat[icent], nIter[it]);    
      hmcUnfFlat[icent][it] = (TH1D*)unfoldMc.Hreco();
      hmcUnfFlat[icent][it]->SetName( Form("hmcUnfFlat_icent%d_iter%d",icent,nIter[it]));
      // Unflatten 2d -> 1d 
      hmcUnf[icent][it] = (TH2D*)hTemp->Clone(Form("hmcUnf_icent%d_iter%d",icent,it));
      unflatten(hmcUnfFlat[icent][it], hmcUnf[icent][it]);
    }
    // Unflatten 2d -> 1d 
    hmcRaw[icent] = (TH2D*)hTemp->Clone(Form("hmcRaw_icent%d",icent));
    hmcTruth[icent] = (TH2D*)hTemp->Clone(Form("hmcTruth_icent%d",icent));
    unflatten(hmcRawFlat[icent], hmcRaw[icent]);
    unflatten(hmcTruthFlat[icent], hmcTruth[icent]);
    
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

  TH1D* hmcUnf1d[7][30][maxIter]; // cent, pT bin
  TH1D* hmcTruth1d[7][30]; // cent, pT bin
  TH1D* hmcRaw1d[7][30]; // cent, pT bin
  
  //  TH1D* hmcUnfSq[7][30][maxIter]; // cent, pT bin
  //  TH1D* hmcTruthSq[7][30]; // cent, pT bin
  //  TH1D* hmcRawSq[7][30]; // cent, pT bin
  
  TH1D* hdataUnf1d[7][30][maxIter]; // cent, pT bin
  TH1D* hdataRaw1d[7][30]; // cent, pT bin
  
  //  TH1D* hdataUnfSq[7][30][maxIter]; // cent, pT bin
  //  TH1D* hdataRawSq[7][30]; // cent, pT bin

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

      TH1ScaleByWidth(hmcTruth1d[icent][ix]);
      TH1ScaleByWidth(hmcRaw1d[icent][ix]);
      for ( int it = 0 ; it< int(nIter.size()) ; it++) {      
	TH1ScaleByWidth(hmcUnf1d[icent][ix][it]);
      }
      
      // data
      if ( doUnfData )  {   
	for ( int it = 0 ; it< int(nIter.size()) ; it++) {
	  hdataUnf1d[icent][ix][it] = (TH1D*)hdataUnf[icent][it]->ProjectionY(Form("hdataUnf1d_icent%d_ix%d_iter%d",icent,ix,nIter[it]),ix,ix);
	}
	hdataRaw1d[icent][ix] = (TH1D*)hdataRaw[icent]->ProjectionY(Form("hdataRaw1d_icent%d_ix%d",icent,ix),ix,ix);
	
	TH1ScaleByWidth(hdataRaw1d[icent][ix]);
	for ( int it = 0 ; it< int(nIter.size()) ; it++) {
	  TH1ScaleByWidth(hdataUnf1d[icent][ix][it]);
	}	
	
      }
      
      
    }
  }
  
  TFile * fout = new TFile(Form("unfSpectra/kSample%d_matrixRwt%d_spectraRwt%d.root",kSample,matrixWeight,doReweight),"recreate");
  for ( int icent=0 ; icent<=6; icent++) {
    if ( !selectedCent(icent) )  continue;
    if ( (kSample == kPP) && ( icent != 0 ) )      continue;
    
    for ( int ix = 1 ; ix<= nXbins ; ix++) {
      
      hmcTruth1d[icent][ix]->Write("",TObject::kOverwrite);
      hmcRaw1d[icent][ix]->Write("",TObject::kOverwrite);
      
      for ( int it = 0 ; it< int(nIter.size()) ; it++) {
	hmcUnf1d[icent][ix][it]->Write("",TObject::kOverwrite);
      }
      
      if ( doUnfData )  {
	hdataRaw1d[icent][ix]->Write("",TObject::kOverwrite);
	for ( int it = 0 ; it< int(nIter.size()) ; it++) {
	  hdataUnf1d[icent][ix][it]->Write("",TObject::kOverwrite);
	}
	
      }
      
    }
  }
  fout->Close();
  
  
}


void getMCspectra(int kSample, int icent, int optX, int optY, TH1D* hmcRawFlat, TH1D* hmcTruthFlat, double radius, bool doReweight) {
  
  TH1::SetDefaultSumw2();
  hmcRawFlat->Reset();
  hmcTruthFlat->Reset();

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
    if ( doReweight ) {
      hReweight = getRewTable(kSample, icent);
    }

    cout << "Scanning JZ"<<ijz<<" file.  Total events = " << tr->GetEntries() << endl;
    for (Int_t i= 0; i<tr->GetEntries() ; i++) {
      if ( i > tr->GetEntries() * statFrac ) continue;

      tr->GetEntry(i);

      if ( useFullMC && (i%2 != 1) )
	continue;


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
	//	double recoM2 = myJetMc.recoMass * myJetMc.recoMass;
	//        double recoPt2 = myJetMc.recoPt * myJetMc.recoPt;
	//	if ( myJetMc.recoMass < 0 ) recoM2 = - recoM2;
	//        double recoVarY =  recoM2 / recoPt2;
	//	int rewBin = hReweight->FindBin(myJetMc.recoPt, myJetMc.recoMass / myJetMc.recoPt);
	int rewBin = hReweight->FindBin(myJetMc.recoPt, myJetMc.recoMass);
        rewFact = hReweight->GetBinContent(rewBin);
      }
      
      // FCAL reweighting factors 
      double fcalWeight = 1.0;
      if ( kSample==kPbPb) {
	//        fcalWeight = hFcalReweight->GetBinContent(hFcalReweight->GetXaxis()->FindBin(myJetMc.fcalet));
      }
      int truthXbin = histXbin->FindBin( truthVarX) ;
      int recoXbin = histXbin->FindBin( recoVarX) ;
      int truthYbin = histYbin->FindBin( truthVarY) ;
      int recoYbin = histYbin->FindBin( recoVarY) ;
      int truth1dBin = get1dBin( truthXbin,truthYbin);
      int reco1dBin = get1dBin( recoXbin, recoYbin);
            
      hmcRawFlat->Fill(   reco1dBin,  myJetMc.weight * rewFact * jzNorm * fcalWeight);
      hmcTruthFlat->Fill( truth1dBin,  myJetMc.weight * rewFact * jzNorm * fcalWeight);
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

void unflatten(TH1D* hFlat, TH2D* h2d) {
  for (int ii = 1 ; ii<= hFlat->GetNbinsX() ; ii++) {
    double theVal = hFlat->GetBinContent(ii);
    double theErr = hFlat->GetBinError(ii);
    int ix = getXBinFrom2d(ii);
    int iy = getYBinFrom2d(ii);
    if ( ix >= maxXbins-1 ) 
      continue;
    if ( iy >= maxYbins-1 ) 
      continue;

    if ( get1dBin( ix, iy) != ii ) {
      cout << " get1dBin and get2d bin are incompatible!!!" << endl;
      cout << "ix = " << ix << endl;
      cout << "iy = " << iy << endl;
      cout << "ii = " << ii << endl;
      cout << "get1dBin( ix, iy) = " << get1dBin( ix, iy) << endl;

    }

    h2d->SetBinContent( ix, iy, theVal);
    h2d->SetBinError  ( ix, iy, theErr);
    
  }
}






bool isTooSmall(TH2D* hEntries, int recoVarX, int recoVarY, int minEntries) {
  int theBin = hEntries->FindBin(recoVarX, recoVarY);
  if (  hEntries->GetBinContent(theBin) < minEntries )
    return true;

  return false;

}


#ifndef __CINT__
int main2 () { unfold2D(); return 0; }  // Main program when run stand-alone
#endif





