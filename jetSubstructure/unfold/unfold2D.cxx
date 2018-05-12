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
#include "../ntupleDefinition_v50.h"
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

double statFrac = 1;
double fracStstData = 001;
bool doUnfData = true ;

bool useFullMC = false;

int lowPtBin = 1;  int highPtBin = 13;
//int lowPtBin = 6;   int highPtBin = 11;

int nPtPannels = highPtBin-lowPtBin+1;

void getMCspectra(int kSample=kPP, int icent=0, int optX=1, int optY=2, TH2D* hmcRaw=0, TH2D* hmcTruth=0, double radius=0.4, bool doReweight=true);
void getDATAspectra(int kSample=kPP, int icent=0, int optX=1, int optY=2, TH2D* hdataRaw=0, double radius=0.4,int nSys=0);

bool isTooSmall(TH2D* hEntries=0, int recoVarX=0, int recoVarY=0, int minEntries=10);

void unfold2D(int kSample = kPP, int optX =1, int optY=2, double radius= 0.4, bool doReweight=false, int nSys=-1) {

  if ( nSys < 0 )
    cout << "===== Nominal mode =====" << endl;
  else if ( (nSys >= 0 ) && ( nSys <= 21 ) )
    cout << "===== pp intrinsic JES sys mode ======" << endl;
  else if ( (nSys >= 100 ) && ( nSys <= 106 ) )
    cout << "===== HI JES sys mode =====" << endl;
  else if ( (nSys >= 200 ) && ( nSys <= 250 ) )
    cout << "===== JMS/JMR sys mode =====" << endl;
  else if  (nSys == 300 )
    cout << "===== Jet mass calibration =====" << endl;
  else if  (nSys == 401 )
    cout << "Do both 101 and 300" << endl;
  else { 
    cout << "===== Invald nSys option ===== " << nSys << endl;
    return ;
  }
  


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
  RooUnfoldResponse* res[7];

  const int maxIter = 60;
  
  TH2D* hmcRaw[7];
  TH2D* hmcTruth[7];
  TH2D* hmcUnf[7][maxIter]; // unfolding iter

  TH2D* hdataRaw[7];
  TH2D* hdataUnf[7][maxIter]; // unfolding iter

  int matrixWeight = 1;
  
  TString matrixName = Form("spectraFiles/unfoldingMatrix2D_coll%d_optX%d_optY%d_radius%.1f_doReweight%d.root",
			    kSample,optX,optY,(float)radius,(int)matrixWeight);
  if ( nSys>= 0) {
    matrixName =       Form("spectraFiles/sys/unfoldingMatrix2D_coll%d_optX%d_optY%d_radius%.1f_doReweight%d_sys%d.root",
		            kSample,optX,optY,(float)radius,(int)matrixWeight,nSys);
  }
  
  TFile* fmatrix = new TFile(matrixName.Data());
  cout << " matrix name : "  << fmatrix->GetName() << endl;
  
  
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
      getDATAspectra(kSample, icent, optX, optY, hdataRaw[i], radius, nSys) ;
    }
    
  }

  for ( int i=0 ; i<=6; i++) {
    int icent = i;
    if ( !selectedCent(i) )  continue;
    if ( (kSample == kPP) && ( i != 0 ) )      continue;
    //    res[i] = (RooUnfoldResponse*)fmatrix->Get(Form("responseMatrix_icent%d",icent)); //
    //    TH2D* h2ResMatrix = (TH2D*)fmatrix->Get(Form("hReco_icent%d_hTruth_icent%d",icent,icent)); //
    //    res[i] = new RooUnfoldResponse(hmcRaw[i], hmcTruth[i], h2ResMatrix);
    //    TH2D* h2Reco  = (TH2D*)fmatrix->Get(Form("hReco_icent%d",icent)); //
    //    TH2D* h2Truth = (TH2D*)fmatrix->Get(Form("hTruth_icent%d",icent)); //
    //    RooUnfoldResponse* tempRes  = (RooUnfoldResponse*)fmatrix->Get(Form("responseMatrix_icent%d",icent)); //
    //    TH2D* h2ResMatrix = (TH2D*)tempRes->Hresponse(); 
    //    res[i] = new RooUnfoldResponse(hmcRaw[i], hmcTruth[i], h2ResMatrix);
    //    res[i] = new RooUnfoldResponse(0,0, h2ResMatrix);
    //    TH2D* h2Reco  = (TH2D*)fmatrix->Get(Form("hReco_icent%d",icent)); //
    //    TH2D* h2Truth = (TH2D*)fmatrix->Get(Form("hTruth_icent%d",icent)); //
    //    TH2D* h2RecoTemp = (TH2D*)h2Reco->Clone("h2RecoTemp");
    //    TH2D* h2TruthTemp = (TH2D*)h2Truth->Clone("h2TruthTemp");
    //    h2RecoTemp->Reset();
    //    h2TruthTemp->Reset();
    //    res[i] = new RooUnfoldResponse(h2RecoTemp, h2TruthTemp, h2ResMatrix);
    //    res[i] = new RooUnfoldResponse(h2Reco, h2Truth, h2ResMatrix);
    res[i] = (RooUnfoldResponse*)fmatrix->Get(Form("responseMatrix_icent%d",icent)); 
  }
  
  
  
  vector<int> nIter;
  for ( int it = 1 ; it<=50 ; it++) { 
    nIter.push_back(it);
    if ( it > maxIter -1 )   cout << " The size of array is not enough! " << endl;
  }
  
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
  
  TString foutName = Form("unfSpectra/kSample%d_matrixRwt%d_spectraRwt%d.root",kSample,matrixWeight,doReweight); 
  if ( nSys >=0 ) { 
    foutName = Form("unfSpectra/sys/kSample%d_matrixRwt%d_spectraRwt%d_sys%d.root",kSample,matrixWeight,doReweight,nSys);
  }
    

  TFile * fout = new TFile(foutName.Data(), "recreate");
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
      // v50
      //      jz2 = "jetSubstructure_MC_HION9_pbpb_v50_jz2.root";
      //      jz3 = "jetSubstructure_MC_HION9_pbpb_v50_jz3.root";
      //      jz4 = "jetSubstructure_MC_HION9_pbpb_v50_jz4.root";
      jz2 = jz2PbPbString;
      jz3 = jz3PbPbString;
      jz4 = jz4PbPbString;
    }
  }
  else if ( kSample == kPP ) {
    if ( radius==0.4 ) {
      //  jz2 = "jetSubstructure_MC_HION9_pp_v50_jz2.root";
      //      jz3 = "jetSubstructure_MC_HION9_pp_v50_jz3.root";
      //      jz4 = "jetSubstructure_MC_HION9_pp_v50_jz4.root";
      jz2 = jz2PPString;
      jz3 = jz3PPString;
      jz4 = jz4PPString;
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

      if ( (!useFullMC) && (i%2 == 1) )
	continue;

      if ( passEvent(myJetMc, icent, true) == false )
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
	int rewBin = hReweight->FindBin(myJetMc.recoPt, myJetMc.recoMass / myJetMc.recoPt);
	//	int rewBin = hReweight->FindBin(myJetMc.recoPt, myJetMc.recoMass);
        rewFact = hReweight->GetBinContent(rewBin);
      }
      
      // FCAL reweighting factors 
      double fcalWeight = 1.0;
      if ( kSample==kPbPb) {
	//        fcalWeight = hFcalReweight->GetBinContent(hFcalReweight->GetXaxis()->FindBin(myJetMc.fcalet));
      }
      
	hmcRaw->Fill( recoVarX, recoVarY, myJetMc.weight * rewFact * jzNorm * fcalWeight);
	hmcTruth->Fill( truthVarX, truthVarY, myJetMc.weight * rewFact * jzNorm * fcalWeight);

    }
  }
  
}


void getDATAspectra(int kSample, int icent, int optX, int optY, TH2D* hdataRaw, double radius, int nSys) {
  TH1::SetDefaultSumw2();
  hdataRaw->Reset();

  TString fname;
  if ( radius == 0.4 ) {
    if ( kSample == kPbPb ) {
      fname = pbpbDataString; 
    }
    else if ( kSample == kPP) {
      fname = ppDataString;
    }
  }

  TF1* fjmscal[30];
  if( ( nSys == 300)||( nSys==401) )  {
    TFile* fin = new TFile(Form("fJMScalibration_kSample%d_icent%d_num.root",kSample,icent));
    for ( int ix = 5 ; ix<=11 ; ix++) {
      fjmscal[ix] = (TF1*)fin->Get(Form("f1_kSample%d_icent%d_ix%d",kSample,icent,ix));
    }
  }
  int nXbinsCal;
  double xBinCal[30];
  getXbin(nXbinsCal, xBinCal, 1);
  TH1D* xBinTempCal = new TH1D("xBinTempCal","", nXbinsCal, xBinCal);


  
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

    if ( passEvent(myJet, icent, false) == false ) // isMC = false
      continue;
    
    double recoVarX, truthVarX;
    getXvalues( recoVarX, truthVarX, myJet, optX);
    double recoVarY, truthVarY;
    getYvalues( recoVarY, truthVarY, myJet, optY);
    
    if ( (nSys==300)||(nSys==401) ) { // JMS calibration
      int xx = xBinTempCal->FindBin( myJet.recoPt);
      if ( xx > 11 )  xx = 11;
      if ( xx < 5 )  xx = 5;
      float mptVal = recoVarY;
      if (mptVal <0 )  mptVal = 0;
      double theFac = 1;
      if ( recoVarY < 0 )
	theFac = 1;
      else if ( recoVarY > 0.25 )
	theFac = fjmscal[xx]->Eval(0.25);
      else
	theFac = fjmscal[xx]->Eval(recoVarY);
      recoVarY = recoVarY / theFac;
    }
    
    hdataRaw->Fill ( recoVarX, recoVarY); 
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





