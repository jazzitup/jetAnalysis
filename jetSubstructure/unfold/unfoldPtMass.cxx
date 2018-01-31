
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

#include "unfoldingUtils.h"
#include <TPaletteAxis.h>

bool doJES = true;
bool checkClosure=true;
double fracStst=1;
bool useFullMC = true;

double fracStstData=1;

double ptCut = 100;
double ptCutGen = 20;
int nIterCan=1;

bool doReweight = true;
TString fReweightPP = "reweightFactors/unfoldingResult_coll0_optX1_optY2_radius0.4_nIter4.root";
TString fReweightPbPb = "reweightFactors/unfoldingResult_coll1_optX1_optY2_radius0.4_nIter4.root";

const Double_t cutdummy= -99999.0;

//
bool selectedCent(int icent=0) {
  if ( icent ==0 )  return true;
  if ( icent ==6 )  return true;

  //   if ( icent ==1 )  return true;
  //  if ( icent ==2 )  return true;
  if ( icent ==3 )  return true;
  //  if ( icent ==4 )  return true;
  //  if ( icent ==5 )  return true;
  return false;
}


//==============================================================================
// Gaussian smearing, systematic translation, and variable inefficiency
//==============================================================================

void getXbin(int &nBins, double* xBin, int optX) { 
  if ( optX == 1 ) {

    nBins = 12;
    double ptBin[13]={63.096, 82., 100.000, 125.892,  158.488,  199.525,  251.186,  316.224,  398.101,  500.,  630.944, 794.308, 999.970};

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

RooUnfoldResponse* getResponse( int kSample = kPP, int icent = 0, int optX=1, int optY=1,  TH2D* hTruth=0, TH2D* hReco=0, double radius =0.4);
void getDataSpectra( int kSample = kPP, int icent=0,  int optX=1, int optY=1, TH2D* hReco=0, double radius=0.4);


void unfoldPtMass(int kSample = kPP, int optX =1, int optY = 2, double radius= 0.4, int nIter=4) {
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
  
  TH2D* hRatio[7];  // = hRecoData / hReco


  TH1D* hFinalMass[20][10]; // pT, centrality
  TH1D* hRawMC[20][10]; // pT, centrality
  TH1D* hRawData[20][10]; // pT, centrality
  
  
  TCanvas* c01 = new TCanvas("c01", "",1000,500);
  c01->Divide(2,1); 
  for ( int i=0 ; i<=6; i++) {
    int icent = i;
    if ( !selectedCent(icent)) 
      continue;
    if ( (kSample == kPP) && ( icent != 0 ) )
      continue;

    hTruth[i] = (TH2D*)hTruthTemp->Clone(Form("%s_icent%d",hTruthTemp->GetName(),i));
    hReco[i] = (TH2D*)hRecoTemp->Clone(Form("%s_icent%d",hRecoTemp->GetName(),i));
    //    hTruth[i]->Reset();
    //    hReco[i]->Reset();
    
    res[i] = getResponse(kSample, i, optX, optY, hTruth[i], hReco[i], radius);
    
    c01->cd(1);   hTruth[i]->Draw("colz");
    c01->cd(2);   hReco[i]->Draw("colz");
    c01->SaveAs(Form("pdfs/correlation_coll%d_cent%d_radius%.1f.pdf",kSample,i,(float)radius));
    
    hRecoData[i] = (TH2D*)hRecoTemp->Clone(Form("hRecoData_icent%d",icent));
    getDataSpectra( kSample, icent, optX, optY, hRecoData[i], radius) ;
    
    
    hRatio[i] = (TH2D*)hRecoData[i]->Clone(Form("hWeight_icent%d",icent));
    hRatio[i]->Divide(hReco[i]);
    //    scaleInt2(hRatio[i]);

  }

  cout << "================================ MC UNFOLD ===================================" << endl;
  for ( int icent=0 ; icent<=6; icent++) {
    if ( !selectedCent(icent)) 
      continue;
    if ( (kSample == kPP) && ( icent !=0 ) )
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
      if ( ix==1)  drawCentrality(kSample,icent, 0.45,0.9,1,20);
      drawBin(xBin,ix,"GeV",0.45,0.8,1,18);
      gPad->SetLogy();
      hRawMC[ix][icent] = (TH1D*)hmassRaw->Clone(Form("hmassRawMC_ix%d_icent%d",ix,icent)); 
      TLegend *leg1;
      if ( ix==1)  	 {
	leg1 = new TLegend(0.4370346,0.4055221,0.9584778,0.7726996,NULL,"brNDC");
	easyLeg(leg1,"MC");
	leg1->AddEntry(hmassGen,"Truth", "l");
	leg1->AddEntry(hmassRaw,"Reco", "lp");
	leg1->AddEntry(hmassUnf,"Unfolded","lp");
	leg1->Draw();
      }

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
      if (checkClosure) rGen->SetAxisRange(0.88,1.12,"Y");
      else rGen->SetAxisRange(0,3,"Y");
      rGen->SetNdivisions(503,"Y");
      rGen->SetYTitle("Ratio");

      fixedFontHist(rGen,2.5);
      rGen->DrawCopy("hist");
      rRaw->DrawCopy("same");
      rUnf->DrawCopy("same");

      //      TLegend *leg2 = new TLegend(0.2064611,0.6408163,0.8804568,0.7959184,NULL,"brNDC");
      //      easyLeg(leg2,"Ratio");
      //      leg2->AddEntry(rUnf,"Unfolded/Truth","lp");
      //      leg2->Draw();
    }


    c1a->SaveAs(Form("pdfs/massClosure1_coll%d_icent%d_optX%d_optY%d_radius%.1f.pdf",kSample,icent,optX,optY,(float)radius));
    c1b->SaveAs(Form("pdfs/massClosure2_coll%d_icent%d_optX%d_optY%d_radius%.1f.pdf",kSample,icent,optX,optY,(float)radius));

    ////////// Beginning of pT closure 
    TCanvas* c1c = new TCanvas(Form("xBin_closure_icent%d",icent),"",500,500);
    makeEfficiencyCanvas(c1c,1,  0.05, 0.01, 0.1, 0.3, 0.01);
    c1c->cd(1);
    TH1D* hxRaw = (TH1D*)hReco[icent]->ProjectionX(Form("hxMCRaw_icent%d",icent));
    TH1D* hxGen = (TH1D*)hTruth[icent]->ProjectionX(Form("hxMCTruth_icent%d",icent));
    TH1D* hxUnf = (TH1D*)hResultMc[icent]->ProjectionX(Form("hxMCUnf_icent%d",icent));
    TH1ScaleByWidth(hxRaw);
    TH1ScaleByWidth(hxGen);
    TH1ScaleByWidth(hxUnf);
    hxGen->SetNdivisions(505);
    handsomeTH1(hxRaw,8);
    handsomeTH1(hxUnf,2);
    if ( optX == 1 )  hxGen->SetXTitle("p_{T} (GeV/c)");
    cleverRangeLog(hxGen, 100, 1.e-9);
    hxGen->SetTitleOffset(1.2,"Y");
    hxGen->SetTitle("");
    hxGen->SetYTitle("dN/dp_{T} (GeV^-1)");
    hxGen->DrawCopy("hist");
    hxRaw->DrawCopy("e same");
    hxUnf->DrawCopy("e same");
    drawCentrality(kSample,icent, 0.7,0.9,1,25);
    gPad->SetLogy();
    TLegend *leg1c;
    leg1c = new TLegend(0.5070346,0.5555221,0.9884778,0.9226996,NULL,"brNDC");
    easyLeg(leg1c,"MC");
    leg1c->AddEntry(hxGen,"Truth", "l");
    leg1c->AddEntry(hxRaw,"Reco", "lp");
    leg1c->AddEntry(hxUnf,"Unfolded","lp");
    leg1c->Draw();
    
    c1c->cd(2);
    TH1D* rRaw = (TH1D*)hxRaw->Clone(Form("%s_r",hxRaw->GetName()));
    TH1D* rGen = (TH1D*)hxGen->Clone(Form("%s_r",hxGen->GetName()));
    TH1D* rUnf = (TH1D*)hxUnf->Clone(Form("%s_r",hxUnf->GetName()));
    rRaw->Divide( hxGen ) ;
    rGen->Divide( hxGen ) ;
    rUnf->Divide( hxGen ) ;
    
    rGen->SetTitleOffset(1.5,"Y");
    if (checkClosure) rGen->SetAxisRange(0.88,1.12,"Y");
    else rGen->SetAxisRange(0.,3,"Y");
    rGen->SetNdivisions(503,"Y");
    rGen->SetYTitle("Ratio");
    
    fixedFontHist(rGen,2.5);
    rGen->DrawCopy("hist");
    rRaw->DrawCopy("same");
    rUnf->DrawCopy("same");


    c1c->SaveAs(Form("pdfs/xBinClosure1_coll%d_icent%d_optX%d_optY%d_radius%.1f_nIter%d.pdf",kSample,icent,optX,optY,(float)radius,nIter));
    ////////// end of pT closure 
    
    
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
      if ( optY==1) {  
	hmassRaw->SetAxisRange(1,2000);
	hmassUnf->SetAxisRange(1,2000);
      }
      else if ( optY==2) { 
	hmassRaw->SetAxisRange(-.02, .08);
	hmassUnf->SetAxisRange(-.02, .08);
      }
      cleverRangeLog(hmassRaw, 20, 0.0001);
      hmassRaw->SetNdivisions(505);
      hmassRaw->SetTitleOffset(1.5,"Y");
      if ( optY==1)	   hmassRaw->SetXTitle("m^{2} (GeV^{2})");
      else if ( optY==2)   hmassRaw->SetXTitle("(m/p_{T})^{2} (GeV^{2})");
      hmassRaw->DrawCopy("e");
      hmassUnf->DrawCopy("e same");
    
      hRawData[ix][icent] = (TH1D*)hmassRaw->Clone(Form("hmassRawData_ix%d_icent%d",ix,icent));

      if ( ix==1)  drawCentrality(kSample,icent, 0.35,0.9,1,20);
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
      rRaw->SetTitle("");
      rRaw->DrawCopy("");
      rUnf->DrawCopy("hist same");
    }
    c2a->SaveAs(Form("pdfs/c2a_coll%d_icent%d_optX%d_optY%d_radius%.1f_nIter%d.pdf",kSample,icent,optX,optY,(float)radius,nIter));     
    c2b->SaveAs(Form("pdfs/c2b_coll%d_icent%d_optX%d_optY%d_radius%.1f_nIter%d.pdf",kSample,icent,optX,optY,(float)radius,nIter));
     
    
    ////////// Beginning of pT unfolding
    TCanvas* c2c = new TCanvas(Form("xBin_dataUnfolding_icent%d",icent),"",500,500);
    makeEfficiencyCanvas(c2c,1,  0.05, 0.01, 0.1, 0.3, 0.01);
    c2c->cd(1);
    TH1D* hxDataRaw = (TH1D*)hRecoData[icent]->ProjectionX(Form("hxdataDataRaw_icent%d",icent));
    TH1D* hxDataUnf = (TH1D*)hResultData[icent]->ProjectionX(Form("hxdataDataUnf_icent%d",icent));

    TH1ScaleByWidth(hxDataRaw);
    TH1ScaleByWidth(hxDataUnf);
    hxDataUnf->SetNdivisions(505);
    handsomeTH1(hxDataRaw,8);
    handsomeTH1(hxDataUnf,2);
    if ( optX == 1 )  hxDataUnf->SetXTitle("p_{T} (GeV/c)");
    cleverRangeLog(hxDataUnf, 100, 1.e-9);
    hxDataUnf->SetTitleOffset(1.2,"Y");
    hxDataUnf->SetYTitle("dN/dp_{T} (GeV^-1)");
    hxDataUnf->SetTitle("");
    hxDataUnf->DrawCopy();
    hxDataRaw->DrawCopy("e same");
    drawCentrality(kSample,icent, 0.7,0.9,1,25);
    gPad->SetLogy();

    c2c->cd(2);
    TH1D* rDataRaw = (TH1D*)hxDataRaw->Clone(Form("%s_r",hxDataRaw->GetName()));
    TH1D* rDataUnf = (TH1D*)hxDataUnf->Clone(Form("%s_r",hxDataUnf->GetName()));
    rDataRaw->Divide( hxDataUnf ) ;
    rDataUnf->Divide( hxDataUnf ) ;

    rDataUnf->SetTitleOffset(1.5,"Y");
    rDataUnf->SetAxisRange(0,3,"Y");
    rDataUnf->SetNdivisions(505,"Y");
    rDataUnf->SetTitle("");
    rDataUnf->SetYTitle("Ratio");

    fixedFontHist(rDataUnf,2.5);
    rDataUnf->DrawCopy("hist");
    rDataRaw->DrawCopy("same");
    c2c->SaveAs(Form("pdfs/c2c_coll%d_icent%d_optX%d_optY%d_radius%.1f_nIter%d.pdf",kSample,icent,optX,optY,(float)radius,nIter));
    ////////// end of pT unfolding

    TCanvas* c3 = new TCanvas(Form("c3_icent%d",icent),"",1200,600);
    c3->Divide( (int)((nXbins+0.1)/2.),2);
    for ( int ix = 1 ; ix<= nXbins ; ix++) {
      c3->cd(ix);
      if ( optY==1)   hmassUnfSqrt[ix]->SetXTitle("m^{2} (GeV)");
      if ( optY==2)   hmassUnfSqrt[ix]->SetXTitle("m^{2}/p_{T}^{2}");
      hmassUnfSqrt[ix]->SetXTitle("m (GeV)");
      if ( optY==1)   hmassUnfSqrt[ix]->SetAxisRange(0.00001,0.1,"Y");
      else if ( optY==2)   hmassUnfSqrt[ix]->SetAxisRange(0.00001,15,"Y");
      
      if ( optY==1)   hmassUnfSqrt[ix]->SetAxisRange(-20,100,"X");
      if ( optY==2)   hmassUnfSqrt[ix]->SetAxisRange(-.05,0.25,"X");

      hmassUnfSqrt[ix]->DrawCopy("e");
      if ( ix==1)  drawCentrality(kSample,icent, 0.45,0.85,1,20);
      drawBin(xBin,ix,"GeV",0.30,0.8,1,18);
      //      gPad->SetLogy();
      hFinalMass[ix][icent] = (TH1D*)hmassUnfSqrt[ix]->Clone(Form("hmassFinal_ix%d_icent%d",ix,icent));
    }
    c3->SaveAs(Form("pdfs/c3_coll%d_icent%d_optX%d_optY%d_radius%.1f_nIter%d.pdf",kSample,icent,optX,optY,(float)radius,nIter));
    
  }

  int periBin = 6;
  if ( selectedCent(periBin) && (kSample == kPbPb ) ){
    for ( int icent=0 ; icent<=periBin ;icent++) {
      if ( !(selectedCent(icent)) )	continue;
      
      if ( icent == periBin )	continue;

      TCanvas* c4 = new TCanvas(Form("c4_icent%d",icent),"",1200,600);
      c4->Divide( (int)((nXbins+0.1)/2.),2);
      for ( int ix = 1 ; ix<= nXbins ; ix++) {
	c4->cd(ix);
	TH1D* rcp = (TH1D*)hFinalMass[ix][icent]->Clone(Form("%s_rcp",hFinalMass[ix][icent]->GetName()));
	rcp->SetAxisRange(0,2,"Y");
	rcp->Divide(hFinalMass[ix][periBin]);
	if ( optY==1)   rcp->SetAxisRange(0.0000,45,"X");
	if ( optY==2)   rcp->SetAxisRange(0.0000,0.25,"X");
	rcp->DrawCopy("e");
	if ( ix==2)  drawCentralityRCP(icent, 0.35,0.85,1,20);
	drawBin(xBin,ix,"GeV",0.30,0.8,1,18);
	jumSun(0,1,200,1);
      }
      c4->SaveAs(Form("pdfs/RCP_icent%d_optX%d_optY%d_radius%.1f_nIter%d.pdf",icent,optX,optY,(float)radius,nIter));

      TCanvas* c5 = new TCanvas(Form("c5_icent%d",icent),"",1200,600);
      c5->Divide( (int)((nXbins+0.1)/2.),2);
      for ( int ix = 1 ; ix<= nXbins ; ix++) {
	c5->cd(ix);
	handsomeTH1(hFinalMass[ix][periBin],1);
	handsomeTH1(hFinalMass[ix][icent],2);
	cleverRange(hFinalMass[ix][periBin],2);
	if ( optY==1)   hFinalMass[ix][periBin]->SetAxisRange(0.0000,100,"X");
        if ( optY==2)   hFinalMass[ix][periBin]->SetAxisRange(0.0000,0.25,"X");
	hFinalMass[ix][periBin]->Draw();
	hFinalMass[ix][icent]->Draw("same");
	//	rcp->DrawCopy("e");
	if ( ix==2)  drawCentrality(kSample,icent, 0.3,0.85,1,20);
	drawBin(xBin,ix,"GeV",0.35,0.8,1,18);
      }
      c5->SaveAs(Form("pdfs/Cent-Peri_icent%d_optX%d_optY%d_radius%.1f_nIter%d.pdf",icent,optX,optY,(float)radius,nIter));
      
    }
  }

  
  TFile* fout = new TFile(Form("spectraFiles/unfoldingResult_coll%d_optX%d_optY%d_radius%.1f_nIter%d.root",kSample,optX,optY,(float)radius,nIter),"recreate");
  for ( int i=0 ; i<=6; i++) {
    int icent = i;
    if ( !selectedCent(icent))      continue;
    if ( (kSample == kPP) && ( icent !=0 ) )      continue;

    hReco[i]->Write();
    hRecoData[i]->Write();
    hRatio[i]->Write();

    for ( int ix = 1 ; ix<= nXbins ; ix++) {
      hFinalMass[ix][icent]->Write();
      hRawMC[ix][icent]->Write();
      hRawData[ix][icent]->Write();
    }
  }
}

RooUnfoldResponse* getResponse(int kSample,  int icent,  int optX, int optY, TH2D* hTruth, TH2D* hReco, double radius)
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
    if ( kSample == kPP)         fReweight = new TFile(fReweightPP) ;
    else if ( kSample == kPbPb)  fReweight = new TFile(fReweightPbPb) ;
    hReweight = (TH2D*)fReweight->Get(Form("hWeight_icent%d",icent));
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

  // Train with a Breit-Wigner, mean 0.3 and width 2.5.
  TH2D* hTruthMc = (TH2D*)hTruth->Clone("hTruthMc");
  TH2D* hRecoMc = (TH2D*)hReco->Clone("hRecoMc");

  // JES 
  TH2D* hJES = (TH2D*)hTruthMc->Clone("hJES");
  //  if ( optY==1)   hJES->SetYTitle("Truth m^{2} (GeV)");
  //  if ( optY==2)   hJES->SetYTitle("Truth (m/p_{T})^{2}");
  if ( optY==1)   hJES->SetYTitle("Reco m^{2} (GeV)");
  if ( optY==2)   hJES->SetYTitle("Reco (m/p_{T})^{2}");
  hJES->SetXTitle("Truth p_{T} (GeV/c)");
  TH2D* hJER = (TH2D*)hJES->Clone("hJER");
  handsomeTH1(hJES);
  handsomeTH1(hJER);

  int nYbins ;
  double yBin[30] ;
  double yBinSqrt[30] ;
  getYbin(nYbins, yBin, yBinSqrt, optY);
  int nXbins;
  double xBin[30];
  getXbin(nXbins, xBin, optX);

  TH1D* yBinTemp = new TH1D("yBinTemp","", nYbins, yBin);
  TH1D* xBinTemp = new TH1D("xBinTemp","", nXbins, xBin);
  TH1D* hdist[30][30];

  TH2D* hResY[20]; // pt Bin



  if ( doJES) {   
    for ( int iy = 1 ; iy<=nYbins ;iy++) {
      for ( int ix = 1 ; ix<=nXbins ;ix++) {
	hdist[ix][iy] = new TH1D(Form("hdist_iy%d_ix%d",iy,ix),";JES;Entries",100,0,2);
	hResY[ix] = new TH2D(Form("hMassResponse_ix%d",ix),";Truth m^{2}/p_{T}^{2};Reco m^{2}/p_{T}^{2}",nYbins, yBin,nYbins, yBin);
      }
    }
  }  
  
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

      // Data/MC reweighting factors 
      double rewFact = 1; 
      if ( doReweight) { 
	int rewBin = hReweight->FindBin(recoVarX,recoVarY); 
	rewFact = hReweight->GetBinContent(rewBin);
      }
      
      if ( useFullMC || (i%2==0) )  
	res->Fill(  recoVarX, recoVarY,    truthVarX, truthVarY, myJetMc.weight * rewFact * jzNorm);
      if ( useFullMC || (i%2==1) )   {
	hReco->Fill ( recoVarX, recoVarY, myJetMc.weight * rewFact * jzNorm);
	hTruth->Fill ( truthVarX, truthVarY, myJetMc.weight * rewFact * jzNorm);
      }
      // JES
      if ( doJES) {
	double theRatio = recoVarX / truthVarX ;
	int theXBin = xBinTemp->FindBin(truthVarX);
	int theYBin = yBinTemp->FindBin(truthVarY);
	//int theYBin = yBinTemp->FindBin(recoVarY);
	if ( (theXBin > nXbins) || (theXBin < 1) ||(theYBin > nYbins) || (theYBin < 1)  )
	  continue;
	hdist[theXBin][theYBin]->Fill(theRatio, myJetMc.weight * rewFact * jzNorm ) ;
	
	hResY[theXBin]->Fill(truthVarY,recoVarY,myJetMc.weight * rewFact * jzNorm );
      }
      
    }
    
  }
  if ( doJES) {
    int lowMassBin = 4;
    int highMassBin = 12;
    int nMassBinDraw = highMassBin - lowMassBin + 1;
    
    
    nIterCan++;
    for ( int ix=1 ; ix<=nXbins;ix++) {
      TCanvas * cJes = new TCanvas(Form("jes_%d",nIterCan),"",1200,400);
      makeMultiPanelCanvas(cJes,nMassBinDraw,1);
      //      makeMultiPanelCanvas(cJes,(nMassBinDraw+1)/2,2);
      for ( int iy = lowMassBin ; iy<= highMassBin ; iy++)  {   //      for ( int iy=1 ; iy<=nYbins;iy++) {
	cJes->cd(iy - lowMassBin + 1);
	handsomeTH1(hdist[ix][iy],1);
	scaleInt(hdist[ix][iy],2);
	cleverRange(hdist[ix][iy],2);
	hdist[ix][iy]->SetAxisRange(0.5,1.5,"X");
	hdist[ix][iy]->Draw();
	hJES->SetBinContent(ix,iy, hdist[ix][iy]->GetMean() );
	hJES->SetBinError(ix,iy, hdist[ix][iy]->GetMeanError() );
	hJER->SetBinContent(ix,iy, hdist[ix][iy]->GetRMS() );
	hJER->SetBinError(ix,iy, hdist[ix][iy]->GetRMSError() );
	if ( iy == lowMassBin) drawBin(xBin,ix,"GeV",0.25,0.85,1,18);
	drawBin(yBin,iy,"",0.25,0.78,1,15);
	jumSun(1,0,1,100);
      }
      cJes->SaveAs(Form("pdfs/jesDist_kSample%d_icent%d_optX%d_optY%d_ix%d.pdf",kSample, icent, optX, optY,ix));
    }
    
    nIterCan++;
    TCanvas * cJes2 = new TCanvas(Form("jes2_%d",nIterCan),"",800,400);
    cJes2->Divide(2,1);
    cJes2->cd(1);
    hJES->SetAxisRange(0.8,1.2,"Z");
    hJES->Draw("colz");
    gPad->SetLogx();
    drawText("Energy Scale",0.55,0.88,1,20);
    drawCentrality(kSample,icent, 0.55,0.8,1,20);
    cJes2->cd(2);
    hJER->SetAxisRange(0.,0.25,"Z");
    hJER->Draw("colz");
    gPad->SetLogx();
    drawText("Resolution",0.5,0.88,1,20);
    cJes2->cd(1)->Update();
    TPaletteAxis *palette1 = (TPaletteAxis*)hJES->GetListOfFunctions()->FindObject("palette");
    palette1->SetX1NDC(0.87);
    palette1->SetX2NDC(0.92);
    cJes2->cd(2)->Update();
    TPaletteAxis *palette2 = (TPaletteAxis*)hJER->GetListOfFunctions()->FindObject("palette");
    palette2->SetX1NDC(0.87);
    palette2->SetX2NDC(0.92);
    //    palette1->SetY1NDC(0.1);
    //    palette1->SetY2NDC(0.95);
    cJes2->SaveAs(Form("pdfs/JESJER_kSample%d_icent%d_optX%d_optY%d.pdf",kSample, icent, optX, optY));
    for ( int ix = 1 ; ix<=nXbins ;ix++) {
      for ( int iy = 1 ; iy<=nYbins ;iy++) {
        delete hdist[ix][iy];
      }
    }
    
    for ( int ix=1 ; ix<=nXbins;ix++) {
      TCanvas * cResp = new TCanvas(Form("jes_%d",nIterCan),"",500,500);
      hResY[ix]->Draw("colz");
      cResp->SaveAs(Form("pdfs/massResponse_kSample%d_icent%d_optX%d_optY%d_ix%d.pdf",kSample, icent, optX, optY,ix));
    }
    
    
  }
  
  return res;
}


void getDataSpectra(int kSample,  int icent,  int optX, int optY, TH2D* hReco, double radius)  {
  TH1::SetDefaultSumw2();
  TString fname;
  if ( kSample == kPbPb ) {
    if ( radius == 0.4 ) { 
      fname = "jetSubstructure_Data_HION9_v4.7_r4_pbpb_Jan23_ptCut90Eta2.1.root";
    }
    else if ( radius==0.6) { 
      fname = "jetSubstructure_Data_HION9_v4.7_r6_Jan12.root";
    }
  }
  else if ( kSample == kPP) {
    if ( radius == 0.4 ) { 
      fname = "jetSubstructure_data_HION9_v4.7_r4_pp_Jan23_ptCut90Eta2.1.root";
      //      fname = "jetSubstructure_Data_HION9_v4.7_r4_Jan12.root";
    }

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
    if ( i > tr->GetEntries() * fracStstData) continue;
    
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





