
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

double fracStst=1;

const Double_t cutdummy= -99999.0;
const int nIter = 4;
bool useHalfStat = true;


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
    //    nBins = 10; 
    //    double ptBin[11]= {100,110, 120, 130, 150, 170,200,250,300,400,1000};
    // jet FF bins 
    nBins = 8; 
    double ptBin[9]= {100, 126, 158, 200, 251, 316, 398, 501, 800};
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
    double massBin[15] = { -2,-1,0,10,13,15,17,19,21,24,28,35,50,100,200};
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
  if ( myJetMc.recoPt < 100 )
    return false;
  if ( (isMC) && ( myJetMc.genPt < 100 ) ) // Must be the same to the lowest pT bin 
    return false;
  
  return true;
  
}

RooUnfoldResponse* getResponse( int icent = 0, int optX=1, int optY=1,  TH2D* hTruth=0, TH2D* hReco=0, double radius =0.4);
void getDataSpectra( int icent=0,  int optX=1, int optY=1, TH2D* hReco=0, double radius=0.4);

void unfoldPtMass(int optX =1, int optY = 1, double radius= 0.4) {
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
    //    hTruth[i]->Reset();
    //    hReco[i]->Reset();
    
    res[i] = getResponse(i, optX, optY, hTruth[i], hReco[i], radius);
    
    c01->cd(1);   hTruth[0]->Draw("colz");
    c01->cd(2);   hReco[0]->Draw("colz");
    c01->SaveAs(Form("correlation_cent%d_radius%.1f.pdf",i,(float)radius));
    
    hRecoData[i] = (TH2D*)hRecoTemp->Clone(Form("hRecoData_icent%d",icent));
    getDataSpectra( icent, optX, optY, hRecoData[i], radius) ;
  }
  
  cout << "================================ MC UNFOLD ===================================" << endl;
  for ( int icent=0 ; icent<=6; icent++) {
    if ( (icent!=0) && (icent!=3) && (icent!=6) )       
	continue;
    
    TCanvas* c1a = new TCanvas(Form("c1a_icent%d",icent),"",1200,400);
    TCanvas* c1b = new TCanvas(Form("c1b_icent%d",icent),"",1200,400);
    //    c1->Divide(6,1);
    makeEfficiencyCanvas(c1a,(nXbins+1)/2,  0.05, 0.01, 0.1, 0.3, 0.01);
    makeEfficiencyCanvas(c1b,(nXbins+1)/2,  0.05, 0.01, 0.1, 0.3, 0.01);
    RooUnfoldBayes unfoldMc (res[icent], hReco[icent], nIter);    // OR
    hResultMc[icent]  = (TH2D*)unfoldMc.Hreco();
    hResultMc[icent]->SetName( Form("hresultmc_icent%d",icent) );
    //    unfoldMc.PrintTable (cout, hTruth[icent]);
    // MC! 
    for ( int ix = 1 ; ix<= nXbins ; ix++) { 
      
      if ( ix <= (nXbins+1)/2 )
	c1a->cd(ix);
      else 
	c1b->cd(ix - (nXbins+1)/2);
      
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
      if ( optY == 1)   hmassGen->SetAxisRange(1,2000);
      if ( optY == 2)   hmassGen->SetAxisRange(-0.02,0.08);
      cleverRangeLog(hmassGen, 10, 0.0001);
      hmassGen->SetTitleOffset(1.5,"Y");
      hmassGen->DrawCopy("hist");
      hmassRaw->DrawCopy("e same");
      hmassUnf->DrawCopy("e same");
      if ( ix==1)  drawCentrality(icent, 0.45,0.9,1,20);
      drawBin(xBin,ix,"GeV",0.45,0.8,1,18);
      gPad->SetLogy();
      
      if ( ix <= (nXbins+1)/2 )
        c1a->cd(ix + (nXbins+1)/2);
      else
        c1b->cd(ix);

      TH1D* rRaw = (TH1D*)hmassRaw->Clone(Form("%s_r",hmassRaw->GetName()));
      TH1D* rGen = (TH1D*)hmassGen->Clone(Form("%s_r",hmassGen->GetName()));
      TH1D* rUnf = (TH1D*)hmassUnf->Clone(Form("%s_r",hmassUnf->GetName()));
      rRaw->Divide( hmassGen ) ;
      rGen->Divide( hmassGen ) ;
      rUnf->Divide( hmassGen ) ;
      
      rGen->SetTitleOffset(1.5,"Y");
      rGen->SetAxisRange(0.88,1.12,"Y");
      rGen->SetNdivisions(503,"Y");
      rGen->SetYTitle("Ratio");

      fixedFontHist(rGen,2.5);
      rGen->DrawCopy("hist");
      rRaw->DrawCopy("same");
      rUnf->DrawCopy("same");
    }
    c1a->SaveAs(Form("c1a_icent%d_optX%d_optY%d_radius%.1f.pdf",icent,optX,optY,(float)radius));
    c1b->SaveAs(Form("c1b_icent%d_optX%d_optY%d_radius%.1f.pdf",icent,optX,optY,(float)radius));
    
    // DATA! 
    TCanvas* c2a = new TCanvas(Form("c2a_icent%d",icent),"",1200,400);
    TCanvas* c2b = new TCanvas(Form("c2b_icent%d",icent),"",1200,400);
    //    c1->Divide(6,1);
    makeEfficiencyCanvas(c2a,(nXbins+1)/2,  0.05, 0.01, 0.1, 0.3, 0.01);
    makeEfficiencyCanvas(c2b,(nXbins+1)/2,  0.05, 0.01, 0.1, 0.3, 0.01);
    RooUnfoldBayes unfoldData (res[icent], hRecoData[icent], nIter);    // OR
    hResultData[icent] = (TH2D*)unfoldData.Hreco();
    hResultData[icent]->SetName( Form("hresultData_icent%d",icent) );
    
    TH1D* hmassUnfSqrt[10];
    for ( int ix = 1 ; ix<= nXbins ; ix++) { 
      if ( ix <= (nXbins+1)/2 )
        c2a->cd(ix);
      else
        c2b->cd(ix - (nXbins+1)/2);

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
	hmassRaw->SetAxisRange(1,2000);
	hmassUnf->SetAxisRange(1,2000);
      }
      else if ( optY==2) { 
	hmassRaw->SetAxisRange(-.1, .1);
	hmassUnf->SetAxisRange(-.1, .1);
      }
      cleverRangeLog(hmassRaw, 20, 0.0001);
      hmassRaw->SetNdivisions(505);
      hmassRaw->SetTitleOffset(1.5,"Y");
      hmassRaw->DrawCopy("e");
      hmassUnf->DrawCopy("e same");
      
      if ( ix==1)  drawCentrality(icent, 0.35,0.9,1,20);
      drawBin(xBin,ix,"GeV",0.35,0.82,1,18);
      gPad->SetLogy();
      
      if ( ix <= (nXbins+1)/2 )
        c2a->cd(ix + (nXbins+1)/2);
      else
        c2b->cd(ix);
      TH1D* rRaw = (TH1D*)hmassRaw->Clone(Form("%s_r",hmassRaw->GetName()));
      TH1D* rUnf = (TH1D*)hmassUnf->Clone(Form("%s_r",hmassUnf->GetName()));
      rRaw->Divide( hmassUnf ) ;
      rUnf->Divide( hmassUnf ) ;
      fixedFontHist(rRaw,2.5);
      rRaw->SetTitleOffset(1.5,"Y");
      //      rRaw->SetNdivisions(505,"Y");
      rRaw->SetYTitle("Ratio");
      rRaw->SetAxisRange(0.,3,"Y");
      rRaw->SetNdivisions(505);
      rRaw->DrawCopy("");
      rUnf->DrawCopy("hist same");
    }
    c2a->SaveAs(Form("c2a_icent%d_optX%d_optY%d_radius%.1f.pdf",icent,optX,optY,(float)radius));      
    c2b->SaveAs(Form("c2b_icent%d_optX%d_optY%d_radius%.1f.pdf",icent,optX,optY,(float)radius));      
    
    TCanvas* c3 = new TCanvas(Form("c3_icent%d",icent),"",1200,600);
    c3->Divide( (int)((nXbins+0.1)/2.),2);
    for ( int ix = 1 ; ix<= nXbins ; ix++) {
      c3->cd(ix);
      hmassUnfSqrt[ix]->SetXTitle("m (GeV)");
      if ( optY==1)   hmassUnfSqrt[ix]->SetAxisRange(0.00001,0.1,"Y");
      else if ( optY==2)   hmassUnfSqrt[ix]->SetAxisRange(0.00001,15,"Y");
      hmassUnfSqrt[ix]->DrawCopy("e");
      if ( ix==1)  drawCentrality(icent, 0.45,0.85,1,20);
      drawBin(xBin,ix,"GeV",0.45,0.8,1,18);
      //      gPad->SetLogy();
    }
    c3->SaveAs(Form("c3_icent%d_optX%d_optY%d_radius%.1f.pdf",icent,optX,optY,(float)radius));
  }
}

RooUnfoldResponse* getResponse( int icent,  int optX, int optY, TH2D* hTruth, TH2D* hReco, double radius)
{
  TH1::SetDefaultSumw2();
  TString jz2;
  TString jz3;
  TString jz4;
  if ( radius==0.4 ) { 
    jz2 = "jetSubstructure_MC_HION9_jz2_r4_Jan10.root";
    jz3 = "jetSubstructure_MC_HION9_jz3_r4_Jan10.root";
    jz4 = "jetSubstructure_MC_HION9_jz4_r4_Jan10.root";
  }
  else if ( radius==0.6) { 
    jz2 = "jetSubstructure_MC_HION9_jz2_r6_Jan11.root";
    jz3 = "jetSubstructure_MC_HION9_jz3_r6_Jan11.root";
    jz4 = "jetSubstructure_MC_HION9_jz4_r6_Jan11.root";
  }
  //  if ( nJz ==2 ) jzNorm = hi9EvtWgtJZ2;
  //  if ( nJz ==3 ) jzNorm = hi9EvtWgtJZ3;
  //  if ( nJz ==4 ) jzNorm = hi9EvtWgtJZ4;
  
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

  // Train with a Breit-Wigner, mean 0.3 and width 2.5.
  TH2D* hTruthMc = (TH2D*)hTruth->Clone("hTruthMc");
  TH2D* hRecoMc = (TH2D*)hReco->Clone("hRecoMc");

  RooUnfoldResponse* res = new RooUnfoldResponse( hTruthMc, hRecoMc );
  res->SetName(Form("responseMatrix_icent%d",icent));
  
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
      double recoVarY, truthVarY;
      getYvalues( recoVarY, truthVarY, myJetMc, optY);
      if ( useHalfStat && (i%2==0) )  
	res->Fill(  recoVarX, recoVarY,    truthVarX, truthVarY, myJetMc.weight * jzNorm);
      if ( useHalfStat && (i%2==1) )   {
	hReco->Fill ( recoVarX, recoVarY, myJetMc.weight * jzNorm);
	hTruth->Fill ( truthVarX, truthVarY, myJetMc.weight * jzNorm);
      }
    }
    
  }
  return res;
}


void getDataSpectra( int icent,  int optX, int optY, TH2D* hReco, double radius)  {
  TH1::SetDefaultSumw2();
  TString fname;
  if ( radius == 0.4 ) { 
    fname = "jetSubstructure_Data_HION9_v4.7_r4_Jan12.root";
  }
  else if ( radius==0.6) { 
    fname = "jetSubstructure_Data_HION9_v4.7_r6_Jan12.root";
  }

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
    //    if ( i > tr->GetEntry(i) * 0.05) continue;

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





