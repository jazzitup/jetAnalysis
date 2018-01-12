
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
void drawBin(double *xBin, int ix, TString demen = "GeV", float xp=0.2, float yp=0.8, int textColor=kBlack, int textSize=18){
  drawText( Form("%d - %d %s", (int)(xBin[ix-1]),  (int)(xBin[ix]), demen.Data()) , xp,yp,textColor,textSize) ;
}

void getXbin(int &nBins, double* xBin, int optX) { 
  if ( optX == 1 ) {
    nBins = 6; 
    double ptBin[7]= {110,130,150,170,200,250,400};
    //    nBins = 1; 
    //    double ptBin[2]= {0,1000};
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
    nBins = 14;
    double massBin[15] = { -2,-1,0,10,13,15,17,19,21,24,28,35,50,75,100};
    for ( int i=0 ; i<= nBins ; i++) {
      yBinSqrt[i] = massBin[i];
    }
    yBin[0] = -1000;
    yBin[1] = -500;
    for ( int i=2 ; i<= nBins ; i++) {
      yBin[i] = massBin[i]*massBin[i];
    }
  }
  else if ( optY == 2) {
    nBins = 11;
    double massBin[12] = { -0.02,-0.01,0,0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.21, 0.24, 0.27};
    for ( int i=0 ; i<= nBins ; i++) {
      yBinSqrt[i] = massBin[i];
    }
    yBin[0] = -0.03;
    yBin[1] = -0.001;
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
  
}
void transformSqrt (TH1D* h1, TH1D* h2) { 
  h2->Reset();
  for ( int i = 0 ; i <=h1->GetNbinsX() ; i++) { 
    double xx = h1->GetBinCenter(i);
    double yy = h1->GetBinContent(i);
    double yye = h1->GetBinError(i);
    if ( yy < 0 ) 
      continue;
    int theBin = h2->FindBin( sqrt(xx) );
    h2->SetBinContent(theBin, yy);
    h2->SetBinError(theBin, yye);
  }
}

bool passEvent( jetSubStr myJetMc, int icent, bool isMC)  {
  if ( myJetMc.cent != icent ) 
    return false;
  if ( myJetMc.recoPt < 80 )
    return false;
  if ( (isMC) && ( myJetMc.genPt < 80 ) )
    return false;
  
  return true;
  
}

RooUnfoldResponse* getResponce( int icent = 0, int optX=1, int optY=1,  TH2D* hTruth=0, TH2D* hReco=0 );
void getDataSpectra( int icent=0,  int optX=1, int optY=1, TH2D* hReco=0);

void unfoldPtMass(int optX =1, int optY = 1, TString fnameData = "jetSubstructure_Data_HION9_v4.7_v1_Jan7") { 
  int nXbins;
  double xBin[30];
  getXbin(nXbins, xBin, optX);
  cout << " nXbins = " << nXbins << endl; 
  cout << " xBin = " << xBin[0] << ",   " << xBin[1] << ",   " <<xBin[2] << ", ..." <<endl;

  int nYbins ;
  double yBin[30] ;
  double yBinSqrt[30] ; 
  getYbin(nYbins, yBin, yBinSqrt, optY);

  TH2D* hTruthTemp = new TH2D("hTruth","",nXbins,xBin,nYbins, yBin);
  TH2D* hRecoTemp = (TH2D*)hTruthTemp->Clone("hReco");
  RooUnfoldResponse* res[7];
  TH2D* hTruth[7];
  TH2D* hReco[7];
  TH2D* hResultMc[7];

  TH2D* hRecoData[7];
  TH2D* hResultData[7];

  TCanvas* c01 = new TCanvas("c01", "",1000,500);
  c01->Divide(2,1); 
  for ( int i=0 ; i<=6; i++) {
    int icent = i;
    if ( (icent!=0) && (icent!=3) && (icent!=6) )
      //if ( (icent!=0) )
      continue; 
    hTruth[i] = (TH2D*)hTruthTemp->Clone(Form("%s_icent%d",hTruthTemp->GetName(),i));
    hReco[i] = (TH2D*)hRecoTemp->Clone(Form("%s_icent%d",hRecoTemp->GetName(),i));
    res[i] = getResponce(i, optX, optY, hTruth[i], hReco[i]);
    c01->cd(1);   hTruth[0]->Draw("colz");
    c01->cd(2);   hReco[0]->Draw("colz");
    c01->SaveAs(Form("correlation_cent%d.pdf",i));
    
    hRecoData[i] = (TH2D*)hRecoTemp->Clone(Form("hRecoData_icent%d",icent));
    getDataSpectra( icent, optX, optY, hRecoData[i]) ;
  }
  
  cout << "================================ MC UNFOLD ===================================" << endl;
  for ( int icent=0 ; icent<=6; icent++) {
    if ( (icent!=0) && (icent!=3) && (icent!=6) )       
	continue;
    
    TCanvas* c1 = new TCanvas(Form("c1_icent%d",icent),"",1200,400);
    //    c1->Divide(6,1);
    makeEfficiencyCanvas(c1,6,  0.05, 0.01, 0.1, 0.3, 0.01);
    RooUnfoldBayes unfoldMc (res[icent], hReco[icent], nIter);    // OR
    hResultMc[icent]  = (TH2D*)unfoldMc.Hreco();
    hResultMc[icent]->SetName( Form("hresultmc_icent%d",icent) );
    //    unfoldMc.PrintTable (cout, hTruth[icent]);
    // MC! 
    for ( int ix = 1 ; ix<= nXbins ; ix++) { 
      c1->cd(ix);
      TH1D* hmassRaw = (TH1D*)hReco[icent]->ProjectionY(Form("hmassMCRaw_icent%d_ipt%d",icent,ix),ix,ix);
      TH1D* hmassGen = (TH1D*)hTruth[icent]->ProjectionY(Form("hmassMCTruth_icent%d_ipt%d",icent,ix),ix,ix);
      TH1D* hmassUnf = (TH1D*)hResultMc[icent]->ProjectionY(Form("hmassMCUnf_icent%d_ipt%d",icent,ix),ix,ix);
      
      TH1ScaleByWidth(hmassRaw);
      TH1ScaleByWidth(hmassGen);
      TH1ScaleByWidth(hmassUnf);

      hmassGen->SetNdivisions(505);
      handsomeTH1(hmassRaw,8);
      handsomeTH1(hmassUnf,2);
      hmassGen->SetXTitle("m^{2} (GeV^{2})");
      if ( optY == 1)   hmassGen->SetAxisRange(-500,35*35-1);
      if ( optY == 2)   hmassGen->SetAxisRange(-0.02,0.08);
      cleverRangeLog(hmassGen, 10, 0.0001);
      hmassGen->DrawCopy("hist");
      hmassRaw->DrawCopy("e same");
      hmassUnf->DrawCopy("e same");
      if ( ix==1)  drawCentrality(icent, 0.35,0.85,1,20);
      drawBin(xBin,ix,"GeV",0.35,0.75,1,18);
      gPad->SetLogy();
      
      c1->cd(ix + nXbins);
      TH1D* rRaw = (TH1D*)hmassRaw->Clone(Form("%s_r",hmassRaw->GetName()));
      TH1D* rGen = (TH1D*)hmassGen->Clone(Form("%s_r",hmassGen->GetName()));
      TH1D* rUnf = (TH1D*)hmassUnf->Clone(Form("%s_r",hmassUnf->GetName()));
      rRaw->Divide( hmassGen ) ;
      rGen->Divide( hmassGen ) ;
      rUnf->Divide( hmassGen ) ;
      rGen->SetAxisRange(0,3,"Y");
      fixedFontHist(rGen,2.5);
      rGen->DrawCopy("hist");
      rRaw->DrawCopy("same");
      rUnf->DrawCopy("same");

    }

    // DATA! 
    TCanvas* c2 = new TCanvas(Form("c2_icent%d",icent),"",1200,400);
    //    c1->Divide(6,1);
    makeEfficiencyCanvas(c2,6,  0.05, 0.01, 0.1, 0.3, 0.01);
    RooUnfoldBayes unfoldData (res[icent], hRecoData[icent], nIter);    // OR
    hResultData[icent] = (TH2D*)unfoldData.Hreco();
    hResultData[icent]->SetName( Form("hresultData_icent%d",icent) );
    
    TH1D* hmassUnfSqrt[10];
    for ( int ix = 1 ; ix<= nXbins ; ix++) { 
      c2->cd(ix);
      TH1D* hmassRaw = (TH1D*)hRecoData[icent]->ProjectionY(Form("hmassDataRaw_icent%d_ipt%d",icent,ix),ix,ix);
      TH1D* hmassUnf = (TH1D*)hResultData[icent]->ProjectionY(Form("hmassDataUnf_icent%d_ipt%d",icent,ix),ix,ix);
      hmassUnfSqrt[ix] = new TH1D(Form("%s_sqrt",hmassUnf->GetName()),"; m (GeV) ; Entries", nYbins, yBinSqrt);
      transformSqrt(hmassUnf, hmassUnfSqrt[ix] ) ;

      TH1ScaleByWidth(hmassRaw);
      TH1ScaleByWidth(hmassUnf);
      TH1ScaleByWidth(hmassUnfSqrt[ix]);
      
      scaleInt(hmassUnfSqrt[ix]);
      
      hmassUnf->SetNdivisions(505);
      handsomeTH1(hmassRaw,8);
      handsomeTH1(hmassUnf,2);
      handsomeTH1(hmassUnfSqrt[ix],2);
      hmassRaw->SetXTitle("m^{2} (GeV^{2})");
      if ( optY==1) {  
	hmassRaw->SetAxisRange(-500,35*35-1);
	hmassUnf->SetAxisRange(-500,35*35-1);
      }
      else if ( optY==2) { 
	hmassRaw->SetAxisRange(-.1, .1);
	hmassUnf->SetAxisRange(-.1, .1);
      }
      cleverRangeLog(hmassRaw, 20, 0.0001);
      hmassRaw->DrawCopy("e");
      hmassUnf->DrawCopy("e same");
      
      if ( ix==1)  drawCentrality(icent, 0.35,0.85,1,20);
      drawBin(xBin,ix,"GeV",0.35,0.75,1,18);
      gPad->SetLogy();
      
      c2->cd(ix + nXbins);
      TH1D* rRaw = (TH1D*)hmassRaw->Clone(Form("%s_r",hmassRaw->GetName()));
      TH1D* rUnf = (TH1D*)hmassUnf->Clone(Form("%s_r",hmassUnf->GetName()));
      rRaw->Divide( hmassUnf ) ;
      rUnf->Divide( hmassUnf ) ;
      fixedFontHist(rRaw,2.5);
      rRaw->SetAxisRange(0,3,"Y");
      rRaw->DrawCopy("");
      rUnf->DrawCopy("hist same");
      
    }
    
    TCanvas* c3 = new TCanvas(Form("c3_icent%d",icent),"",1200,800);
    c3->Divide(3,2);
    for ( int ix = 1 ; ix<= nXbins ; ix++) {
      c3->cd(ix);
      hmassUnfSqrt[ix]->SetXTitle("m (GeV)");
      if ( optY==1)   hmassUnfSqrt[ix]->SetAxisRange(0.00001,0.1,"Y");
      else if ( optY==2)   hmassUnfSqrt[ix]->SetAxisRange(0.00001,15,"Y");
      hmassUnfSqrt[ix]->DrawCopy("e");
      if ( ix==1)  drawCentrality(icent, 0.5,0.85,1,20);
      drawBin(xBin,ix,"GeV",0.5,0.8,1,18);
      //      gPad->SetLogy();
    }
    c3->SaveAs(Form("c3_icent%d.pdf",icent));
  }
}

RooUnfoldResponse* getResponce( int icent,  int optX, int optY, TH2D* hTruth, TH2D* hReco)
{
  TString jz3 = "jetSubstructure_himix_test_v4.6_r4_Trimming_rSub0.25_fCut0.10.root" ;
  
  cout << "==================================== TRAIN ====================================" << endl;
  TFile* fMc = new TFile(Form("../ntuples/%s",jz3.Data()));
  TTree* trMc = (TTree*)fMc->Get("tr");
  jetSubStr myJetMc;
  TBranch       *b_myJetSubMc;
  trMc->SetBranchAddress("jets", &(myJetMc.cent), &b_myJetSubMc);

  // Train with a Breit-Wigner, mean 0.3 and width 2.5.
  cout << " JZ3 entries = " << trMc->GetEntries() << endl;
  

  TH2D* hTruthMc = (TH2D*)hTruth->Clone("hTruthMc");
  TH2D* hRecoMc = (TH2D*)hReco->Clone("hRecoMc");

  RooUnfoldResponse* res = new RooUnfoldResponse( hTruthMc, hRecoMc );
  res->SetName(Form("responseMatrix_icent%d",icent));

  for (Int_t i= 0; i<trMc->GetEntries() ; i++) {
    trMc->GetEntry(i);
    if ( ! passEvent(myJetMc, icent, true) )  // isMC = true
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


void getDataSpectra( int icent,  int optX, int optY, TH2D* hReco)  {
  TString fname = "jetSubstructure_Data_HION9_v4.7_v1_Jan7.root";
  TFile* fData = new TFile(Form("../ntuples/%s",fname.Data()));
  TTree* tr = (TTree*)fData->Get("tr");
  jetSubStr myJet;
  TBranch       *b_myJet;
  tr->SetBranchAddress("jets", &(myJet.cent), &b_myJet);

  // Train with a Breit-Wigner, mean 0.3 and width 2.5.
  cout << " Data entries = " << tr->GetEntries() << endl;

  hReco->Reset();

  for (Int_t i= 0; i<tr->GetEntries() ; i++) {
    tr->GetEntry(i);
    if ( ! passEvent(myJet, icent, false) ) // isMC = false
      continue;

    double recoVarX, truthVarX;
    getXvalues( recoVarX, truthVarX, myJet, optX);
    double recoVarY, truthVarY;
    getYvalues( recoVarY, truthVarY, myJet, optY);

    hReco->Fill ( recoVarX, recoVarY);  // no reweighting for data
    
  }
}
 
#ifndef __CINT__
int main () { unfoldPtMass(); return 0; }  // Main program when run stand-alone
#endif





