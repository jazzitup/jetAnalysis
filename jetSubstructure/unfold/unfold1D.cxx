
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


bool doJES = true;

bool doCheckSmearing = false; //true;	
int selBinX = 6; // 199 GeV - 251 GeV

bool checkClosure=true;

double fracStst=01;
double fracStstData=01;

double ptCut = 100;
double ptCutGen = 20;

bool useFullMC = true;

bool doReweight = false;

const Double_t cutdummy= -99999.0;

//
bool selectedCent(int icent=0) {
  if ( icent ==0 )  return true;
  /*  if ( icent ==6 )  return true;
  if ( icent ==1 )  return true;
  if ( icent ==2 )  return true;
  if ( icent ==3 )  return true;
  if ( icent ==4 )  return true;
  if ( icent ==5 )  return true;*/
  return false;
}


//==============================================================================
// Gaussian smearing, systematic translation, and variable inefficiency
//==============================================================================

void getXbin(int &nBins, double* xBin, int optX) { 
  if ( optX == 1 ) {
    
    nBins = 12;  // default
    double ptBin[13]={63.096, 82., 100.000, 125.892,  158.488,  199.525,  251.186,  316.224,  398.101,  500.,  630.944, 794.308, 999.970};
    //        nBins = 2;
    //        double ptBin[3]={125.892,  251.186,  630.944};

    //    nBins = 16;
    //    double ptBin[17]={25.119, 31.623, 40.0, 50.119, 63.096, 82., 100.000, 125.892,  158.488,  199.525,  251.186,  316.224,  398.101,  500.,  630.944, 794.308, 999.970};

    //    nBins = 8; 
    //    double ptBin[9]= {100, 126, 158, 200, 251, 316, 398, 501, 800};
    for ( int i=0 ; i<= nBins ; i++) {
      xBin[i] = ptBin[i] ; 
    }    
  }
  else if ( optX == 2) { 
    nBins = 6;
    for ( int i=0 ; i<= nBins ; i++) {
      xBin[i] = -10 + ( 35 + 10 ) * float(i)/nBins;
    }
  }
}

void getXvalues( double &recoVarX, double &truthVarX, jetSubStr myJetMc, int optX) {
  if ( optX == 1 ) { 
    truthVarX = myJetMc.genPt;
    recoVarX = myJetMc.recoPt;
  }
  if ( optX == 2 )  {
    recoVarX = myJetMc.nTrkRaw - myJetMc.nTrkBkg;
    truthVarX = myJetMc.genNch;
  }
}

void getYbin(int &nBins, double* yBin, double *yBinSqrt, int optY) {

  if ( optY == 1) {
    nBins = 18;
    double massBin[19] = { -35,-19,-17,-15, -13,-10,0,10,13,15,17,19,21,24,28,35,50,100,200};
    for ( int i=0 ; i<= nBins ; i++) {
      yBinSqrt[i] = massBin[i];
    }
    for ( int i=0 ; i<= nBins ; i++) {
      yBin[i] = massBin[i]*massBin[i];
      if ( massBin[i] < 0 ) 
	yBin[i] = - yBin[i]; 
    }
  }
  else if ( optY == 2) {
    nBins = 12;
    double massBin[13] = { -0.15,-0.06,-0.03,0,0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3,0.35};
    for ( int i=0 ; i<= nBins ; i++) {
      yBinSqrt[i] = massBin[i];
    }
    for ( int i=0 ; i<= nBins ; i++) {
      if  ( massBin[i] > 0 )     
	yBin[i] = massBin[i]*massBin[i];
      else 
	yBin[i] = -1.0 * massBin[i]*massBin[i];
    }
  }
  
  else if ( optY == 7)   {
    nBins = 12 ;
    for ( int i=0 ; i<= nBins ; i++) {
      yBin[i] = -2000 + (2000+2000) * float(i)/nBins ; 
    }
  }

  else if ( optY == 8)   {
    nBins = 12 ;
    double massBin[13] = { -0.3,-0.2,-0.1,0,0.03,0.06,0.09,0.12,0.15,0.2,0.25, 0.3,0.5};
    for ( int i=0 ; i<= nBins ; i++) {
      yBinSqrt[i] = massBin[i];
    }
    for ( int i=0 ; i<= nBins ; i++) {
      if  ( massBin[i] > 0 )
        yBin[i] = massBin[i]*massBin[i];
      else
        yBin[i] = -1.0 * massBin[i]*massBin[i];
    }
  }
  
  
  
}


void getYvalues( double &recoVarY, double &truthVarY, jetSubStr myJetMc, int optY) {
  
  double genM2 = myJetMc.genMass* myJetMc.genMass;
  double recoM2 = myJetMc.recoMass * myJetMc.recoMass;
  double genPt2 = myJetMc.genPt* myJetMc.genPt;
  double recoPt2 = myJetMc.recoPt * myJetMc.recoPt;


  if ( myJetMc.recoMass < 0 ) recoM2 = - recoM2;
  double genMoverPt2 = genM2 / genPt2; 
  double recoMoverPt2 = recoM2 / recoPt2;

  if (optY==1)  {
    recoVarY = recoM2;
    truthVarY = genM2;
  }
  if (optY==2)  {
    recoVarY = recoMoverPt2;
    truthVarY = genMoverPt2;
  }

  else if ( optY == 7) { // charge assisted mass
    truthVarY = genM2;
    float recoVarYsqrt = myJetMc.recoChMassRcSubt * myJetMc.recoPt / myJetMc.recoChPtRcSubt ;
    recoVarY = recoVarYsqrt * recoVarYsqrt;
    if ( recoVarYsqrt < 0)   recoVarY = - recoVarY ;
  }

  else if ( optY == 8) { // charge assisted mass
    truthVarY = genMoverPt2;
    float recoVarYsqrt = myJetMc.recoChMassRcSubt / myJetMc.recoChPtRcSubt ;
    recoVarY = recoVarYsqrt * recoVarYsqrt;
    if ( recoVarYsqrt < 0)   recoVarY = - recoVarY ;
  }
  
}

void transformSqrt (TH1D* h1, TH1D* h2) { 
  h2->Reset();
  for ( int i = 0 ; i <=h1->GetNbinsX() ; i++) { 
    double xx = h1->GetBinCenter(i);
    double yy = h1->GetBinContent(i);
    double yye = h1->GetBinError(i);
    //    if ( yy < 0 ) 
    //      continue;
    int theBin;
    if ( xx >= 0 )    theBin = h2->FindBin( sqrt(xx) );
    else    theBin = h2->FindBin( - sqrt(-xx) );
    h2->SetBinContent(theBin, yy);
    h2->SetBinError(theBin, yye);
  }
}

bool passEvent( jetSubStr myJetMc, int icent, bool isMC)  {
  if ( myJetMc.cent != icent ) 
    return false;
  if ( myJetMc.recoPt < ptCut )
    return false;
  if ( (isMC) && ( myJetMc.genPt < ptCutGen ) ) // Must be the same to the lowest pT bin 
    return false;
  
  return true;
  
}

RooUnfoldResponse* getResponse( int kSample = kPP, int icent = 0, int optX=1, TH1D* hTruth=0, TH1D* hReco=0, double radius =0.4);


void unfold1D(int kSample = kPP, int optX =1, double radius= 0.4) {
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
    
    res[i] = getResponse(kSample, i, optX, hTruth[i], hReco[i], radius);

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

RooUnfoldResponse* getResponse(int kSample,  int icent,  int optX, TH1D* hTruth, TH1D* hReco, double radius)
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
  res->SetName(Form("responseMatrix_icent%d_reweight%d",icent,doReweight));

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
int main () { unfold1D(); return 0; }  // Main program when run stand-alone
#endif





