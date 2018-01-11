
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
const int nIter = 4;

//==============================================================================
// Gaussian smearing, systematic translation, and variable inefficiency
//==============================================================================
void drawCentrality(int icent = 0, float xp=0.2, float yp=0.8, int textColor=kBlack, int textSize=18){
  if ( icent==0 )  drawText( "0-10%",xp,yp,textColor,textSize) ;
  if ( icent==1 )  drawText( "10-20%",xp,yp,textColor,textSize) ;
  if ( icent==2 )  drawText( "20-30%",xp,yp,textColor,textSize) ;
  if ( icent==3 )  drawText( "30-40%",xp,yp,textColor,textSize) ;
  if ( icent==4 )  drawText( "40-50%",xp,yp,textColor,textSize) ;
  if ( icent==5 )  drawText( "50-60%",xp,yp,textColor,textSize) ;
  if ( icent==6 )  drawText( "60-80%",xp,yp,textColor,textSize) ;
}
void getXbin(int &nBins, double* xBin, int optX) { 
  if ( optX == 1 ) {
    nBins = 6; 
    double ptBin[7]= {110,130,150,170,200,250,400};
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

void getYbin(int &nBins, double* yBin, int optY) {

  if ( optY == 1) {
    nBins = 12;
    double massBin[13] = { 0,0,0,10,13,15,17,19,21,24,28,35,200};
    yBin[0] = -500;
    yBin[1] = -75;
    for ( int i=2 ; i<= nBins ; i++) {
      yBin[i] = massBin[i]*massBin[i];
    }
  }
  else if ( optY == 7)   {
    nBins = 12 ;
    for ( int i=0 ; i<= nBins ; i++) {
      yBin[i] = -2000 + (2000+2000) * float(i)/nBins ; 
    }
  }
}

void getYvalues( double &recoVarY, double &truthVarY, jetSubStr myJetMc, int optY) {
  
  double genM2 = myJetMc.genMass* myJetMc.genMass;
  double recoM2 = myJetMc.recoMass * myJetMc.recoMass;
  if ( myJetMc.recoMass < 0 ) recoM2 = - recoM2;
  double genMoverPt2 = genM2 / (myJetMc.genPt*myJetMc.genPt);
  double recoMoverPt2 = recoM2 / (myJetMc.recoPt*myJetMc.recoPt);

  if (optY==1)  {
    recoVarY = recoM2;
    truthVarY = genM2;
  }
  else if ( optY == 7) { // charge assisted mass
    truthVarY = genM2;
    float recoVarYsqrt = myJetMc.recoChMassRcSubt * myJetMc.recoPt / myJetMc.recoChPtRcSubt ;
    recoVarY = recoVarYsqrt * recoVarYsqrt;
    if ( recoVarYsqrt < 0)   recoVarY = - recoVarY ;
  }
  
}

bool passEvent( jetSubStr myJetMc, int icent)  {
  if ( myJetMc.cent != icent ) 
    return false;
  if ( myJetMc.recoPt < 100 )
    return false;
  if ( myJetMc.genPt < 70 ) 
    return false;
  
  return true;
  
}

RooUnfoldResponse* getResponce( int icent = 0, int optX=1, int optY=1,  TH2D* hTruth=0, TH2D* hReco=0 );

void unfoldPtMass(int optX =1, int optY = 1, TString fnameData = "jetSubstructure_Data_HION9_v4.7_v1_Jan7") { 
  int nIter = 4;
  int nXbins;
  double xBin[30];
  getXbin(nXbins, xBin, optX);
  cout << " nXbins = " << nXbins << endl; 
  cout << " xBin = " << xBin[0] << ",   " << xBin[1] << ",   " <<xBin[2] << ", ..." <<endl;

  int nYbins ;
  double yBin[30] ;
  getYbin(nYbins, yBin, optY);

  TH2D* hTruthTemp = new TH2D("hTruth","",nXbins,xBin,nYbins, yBin);
  TH2D* hRecoTemp = (TH2D*)hTruthTemp->Clone("hReco");
  RooUnfoldResponse* res[7];
  TH2D* hTruth[7];
  TH2D* hReco[7];
  TH2D* hResultMc[7];

  TCanvas* c01 = new TCanvas("c01", "",1000,500);
  c01->Divide(2,1); 
  for ( int i=0 ; i<=6; i++) {
    if ( (i!=0) && (i!=3) && (i!=6))
      continue; 
    
    hTruth[i] = (TH2D*)hTruthTemp->Clone(Form("%s_icent%d",hTruthTemp->GetName(),i));
    hReco[i] = (TH2D*)hRecoTemp->Clone(Form("%s_icent%d",hRecoTemp->GetName(),i));
    res[i] = getResponce(i, optX, optY, hTruth[i], hReco[i]);
    
    c01->cd(1);   hTruth[0]->Draw("colz");
    c01->cd(2);   hReco[0]->Draw("colz");
    c01->SaveAs(Form("correlation_cent%d.pdf",i));
  }

  cout << "================================ MC UNFOLD ===================================" << endl;
  for ( int icent=0 ; icent<=6; icent++) {
    if ( (icent!=0) && (icent!=3) && (icent!=6) )       
      continue;

    TCanvas* c1 = new TCanvas(Form("c1_icent%d",icent),"",1200,800);
    c1->Divide(3,2);
    RooUnfoldBayes unfoldMc (res[icent], hReco[icent], nIter);    // OR
    hResultMc[icent]  = (TH2D*)unfoldMc.Hreco();
    hResultMc[icent]->SetName( Form("hresultmc_icent%d",icent) );
    //    unfoldMc.PrintTable (cout, hTruth[icent]);
    for ( int ix = 1 ; ix<= nXbins ; ix++) { 
      c1->cd(ix);
      TH1D* hmassRaw = (TH1D*)hReco[icent]->ProjectionY(Form("hmassMCRaw_icent%d_ipt%d",icent,ix),ix,ix);
      TH1D* hmassGen = (TH1D*)hTruth[icent]->ProjectionY(Form("hmassMCTruth_icent%d_ipt%d",icent,ix),ix,ix);
      TH1D* hmassUnf = (TH1D*)hResultMc[icent]->ProjectionY(Form("hmassMCUnf_icent%d_ipt%d",icent,ix),ix,ix);
      hmassGen->SetNdivisions(505);
      handsomeTH1(hmassRaw,8);
      handsomeTH1(hmassUnf,2);
      hmassGen->SetXTitle("m^{2} (GeV^{2})");
      //      cleverRangeLog(hmassGen,2,1e-3);
      hmassGen->DrawCopy("hist");
      hmassRaw->DrawCopy("e same");
      hmassUnf->DrawCopy("e same");
      if ( ix==1)  drawCentrality(icent, 0.6,0.7,1,25);
      
    }
    
  }
  
}

RooUnfoldResponse* getResponce( int icent,  int optX, int optY, TH2D* hTruth, TH2D* hReco)
{


  TString jz3 = "jetSubstructure_himix_test_v4.6_r4_Trimming_rSub0.25_fCut0.10" ;
  
  cout << "==================================== TRAIN ====================================" << endl;
  TFile* fMc = new TFile(Form("../ntuples/%s.root",jz3.Data()));
  TTree* trMc = (TTree*)fMc->Get("tr");
  jetSubStr myJetMc;
  TBranch       *b_myJetSubMc;
  trMc->SetBranchAddress("jets", &(myJetMc.cent), &b_myJetSubMc);

  // Train with a Breit-Wigner, mean 0.3 and width 2.5.
  cout << " JZ3 entries = " << trMc->GetEntries() << endl;
  

  TH2D* hTruthMc = (TH2D*)hTruth->Clone("hTruthMc");
  TH2D* hRecoMc = (TH2D*)hReco->Clone("hRecoMc");

  RooUnfoldResponse* res = new RooUnfoldResponse( hTruthMc, hRecoMc );

  for (Int_t i= 0; i<trMc->GetEntries() ; i++) {
    trMc->GetEntry(i);
    if ( ! passEvent(myJetMc, icent) ) 
      continue; 

    double recoVarX, truthVarX;
    getXvalues( recoVarX, truthVarX, myJetMc, optX);
    double recoVarY, truthVarY;
    getYvalues( recoVarY, truthVarY, myJetMc, optY);
    res->Fill(  recoVarX, recoVarY,    truthVarX, truthVarY, myJetMc.weight);
    hReco->Fill ( recoVarX, recoVarY, myJetMc.weight);
    hTruth->Fill ( truthVarX, truthVarY, myJetMc.weight);
  }
  
  return res;
}

#ifndef __CINT__
int main () { unfoldPtMass(); return 0; }  // Main program when run stand-alone
#endif





