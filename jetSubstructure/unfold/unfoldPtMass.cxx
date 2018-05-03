
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
#include "../commonUtility.h"
#include "../jzWeight.h"
#include "unfoldingUtil.h"

#endif

//==============================================================================
// Global definitions
//==============================================================================

#include "../JssUtils.h"
#include <TPaletteAxis.h>

bool applyMDJ=false;

bool doJES = true;

bool doCheckSmearing = false; //true;	
int selBinX = 6; // 199 GeV - 251 GeV

bool checkClosure=true;

double fracStst=0.01;

double ptCut = 100;
double ptCutGen = 20;
int nIterCan=1;

bool useFullMC = true;

bool doReweight = false;
TString fReweightPP = "reweightFactors/unfoldingResult_coll0_optX1_optY2_radius0.4_nIter4.root";
TString fReweightPbPb = "reweightFactors/unfoldingResult_coll1_optX1_optY2_radius0.4_nIter4.root";

struct jesHists {
  TH2D* hgTheta;
  TH2D* hgK;
  TH2D* hgMean;
  TH2D* hJES;
} ;


RooUnfoldResponse* getResponse( int kSample = kPP, int icent = 0, int optX=1, int optY=1,  TH2D* hTruth=0, TH2D* hReco=0, double radius =0.4);

void unfoldPtMass(int kSample = kPP, int optX =1, int optY = 2, double radius= 0.4) {
  TH1::SetDefaultSumw2();
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
      jz2 = jz2PbPbStringSys;
      jz3 = jz3PbPbStringSys;
      jz4 = jz4PbPbStringSys;
    }
  }
  else if ( kSample == kPP ) {
    if ( radius==0.4 ) {
      jz2 = jz2PPStringSys ; 
      jz3 = jz3PPStringSys ; 
      jz4 = jz4PPStringSys ; 
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
  if ( optY==8)   hJES->SetYTitle("Reco (m/p_{T})^{2}");
  hJES->SetXTitle("Truth p_{T} (GeV/c)");
  TH2D* hJER = (TH2D*)hJES->Clone("hJER");
  handsomeTH1(hJES);
  handsomeTH1(hJER);

  int nYbins ;
  double yBin[30] ;
  getYbin(nYbins, yBin, optY);
  int nXbins;
  double xBin[30];
  getXbin(nXbins, xBin, optX);

  TH1D* yBinTemp = new TH1D("yBinTemp","", nYbins, yBin);
  TH1D* xBinTemp = new TH1D("xBinTemp","", nXbins, xBin);
  TH1D* hdist[30][30];
  TH1D* hdistMass[30][30];

  TH2D* hResY[20]; // pt Bin
  if ( doJES) {   
    for ( int ix = 1 ; ix<=nXbins ;ix++) {
      hResY[ix] = new TH2D(Form("hMassResponse_ix%d",ix),";Truth m^{2}/p_{T}^{2};Reco m^{2}/p_{T}^{2}",nYbins, yBin,nYbins, yBin);
      for ( int iy = 1 ; iy<=nYbins ;iy++) {
	hdist[ix][iy] = new TH1D(Form("jes_iy%d_ipt%d",iy,ix),";JES;Entries",100,0,2);   // JES
	hdistMass[ix][iy] = new TH1D(Form("jms_iy%d_ipt%d",iy,ix),";Mass scale;Entries",100,-2,4);
      }
    }
  }  

  TH1D* hMassByPtMig[20]; // in Truth pT bin,
  TH1D* hMassByMassMig[20]; // in truth mass bin  
  
  
  
  RooUnfoldResponse* res = new RooUnfoldResponse( hTruthMc, hRecoMc );
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
	double theRatioX = recoVarX / truthVarX ;
	double theRatioY = recoVarY / truthVarY ;

	int theXBin = xBinTemp->FindBin(truthVarX);
	int theYBin = yBinTemp->FindBin(truthVarY);
	//int theYBin = yBinTemp->FindBin(recoVarY);
	if ( (theXBin > nXbins) || (theXBin < 1) ||(theYBin > nYbins) || (theYBin < 1)  )
	  continue;
	hdist[theXBin][theYBin]->Fill(theRatioX, myJetMc.weight * rewFact * jzNorm ) ;
	hdistMass[theXBin][theYBin]->Fill(theRatioY, myJetMc.weight * rewFact * jzNorm ) ;
	
	hResY[theXBin]->Fill(truthVarY,recoVarY,myJetMc.weight * rewFact * jzNorm );
      }
      
      // smearing check 
	
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
      cJes->SaveAs(Form("pdfs/jesDist_kSample%d_icent%d_optX%d_optY%d_ix%d_applyMDJ%d.pdf",kSample, icent, optX, optY,ix,(int)applyMDJ));
      
      TCanvas * cJms = new TCanvas(Form("jes_%d",nIterCan),"",1200,400);
      makeMultiPanelCanvas(cJms,nMassBinDraw,1);
      //      makeMultiPanelCanvas(cJms,(nMassBinDraw+1)/2,2);
      for ( int iy = lowMassBin ; iy<= highMassBin ; iy++)  {   //      for ( int iy=1 ; iy<=nYbins;iy++) {
        cJms->cd(iy - lowMassBin + 1);
	handsomeTH1(hdistMass[ix][iy],1);
	scaleInt(hdistMass[ix][iy],2);
	cleverRange(hdistMass[ix][iy],2);
        hdistMass[ix][iy]->SetAxisRange(0.5,1.5,"X");
        hdistMass[ix][iy]->Draw();
	hJES->SetBinContent(ix,iy, hdistMass[ix][iy]->GetMean() );
        hJES->SetBinError(ix,iy, hdistMass[ix][iy]->GetMeanError() );
	hJER->SetBinContent(ix,iy, hdistMass[ix][iy]->GetRMS() );
        hJER->SetBinError(ix,iy, hdistMass[ix][iy]->GetRMSError() );
        if ( iy == lowMassBin) drawBin(xBin,ix,"GeV",0.25,0.85,1,18);
        drawBin(yBin,iy,"",0.25,0.78,1,15);
        jumSun(1,0,1,100);
      }
      cJms->SaveAs(Form("pdfs/jmsDist_kSample%d_icent%d_optX%d_optY%d_ix%d_applyMDJ%d.pdf",kSample, icent, optX, optY,ix,(int)applyMDJ));

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
    cJes2->SaveAs(Form("pdfs/JESJER_kSample%d_icent%d_optX%d_optY%d_applyMDJ%d.pdf",kSample, icent, optX, optY,(int)applyMDJ));
    //    for ( int ix = 1 ; ix<=nXbins ;ix++) {
    //      for ( int iy = 1 ; iy<=nYbins ;iy++) {
    //        delete hdist[ix][iy];
    //      }
    //    }
    
    for ( int ix=1 ; ix<=nXbins;ix++) {
      TCanvas * cResp = new TCanvas(Form("jes_%d",nIterCan),"",500,500);
      hResY[ix]->Draw("colz");
      drawCentrality(kSample,icent, 0.3,0.9,1,20);
      drawBin(xBin,ix,"GeV",0.48,0.82,1,20);
      drawText("Truth p_{T}:",0.3,0.82,1,20);
      cResp->SaveAs(Form("pdfs/massResponse_kSample%d_icent%d_optX%d_optY%d_ix%d_%d.pdf",kSample, icent, optX, optY,ix,(int)applyMDJ));
      
    }
    TString sampleName;
    if ( kSample == kPP ) sampleName = "pp";
    else if ( kSample == kPbPb) sampleName = "PbPb";
    //    TFile* fJes = new TFile(Form("jes_%s_cent%d.root",sampleName.Data(),icent),"recreate");
    //    for ( int iy = 1 ; iy<=nYbins ;iy++) {
    //      for ( int ix = 1 ; ix<=nXbins ;ix++) {
	//	hdist[ix][iy]->Write();
    //      }
    //    }
    
  }

  
  // smearing check
  if (doCheckSmearing) {
    TCanvas* cSmear = new TCanvas("csmear","",800,500);
    cSmear->Divide(2,1);
    cSmear->cd(1);
    TH1D* hTemp1[20];
    for ( int ix = 1 ; ix<=nXbins ;ix++) {
      hTemp1[ix] = (TH1D*)hMassByPtMig[ix]->Clone(Form("hTemp1_ix%d",ix));
      if ( ix>1) hTemp1[ix]->Add( hTemp1[ix-1] );
    }
    TLegend *leg2 = new TLegend(0.4464808,0.3843537,0.9999478,0.9122449,NULL,"brNDC");
    easyLeg(leg2,"From other pT^{Truth}");
    for ( int ix = nXbins ; ix>=1 ;ix--) {
      hTemp1[ix]->SetLineColor(ix);
      hTemp1[ix]->SetFillColor(ix);
      cleverRange(hTemp1[ix],1.5,0.000001);
      if ( ix == nXbins) hTemp1[ix]->Draw("hist");
      else hTemp1[ix]->Draw("hist same");
      //      if ( abs(ix - selBinX ) < 3) 
      leg2->AddEntry(hTemp1[ix], Form("%d <p_{T}< %d GeV",(int)xBin[ix], (int)xBin[ix+1]), "lf" );
    }
    leg2->Draw();

    cSmear->cd(2);
    TH1D* hTemp2[20];
    TLegend *leg3 = new TLegend(0.4464808,0.3843537,0.9999478,0.9122449,NULL,"brNDC");
    easyLeg(leg3,"From other m/pT^{truth}");
    for ( int iy = 1;  iy<= nYbins ; iy++) {
      hTemp2[iy] = (TH1D*)hMassByMassMig[iy]->Clone(Form("hTemp2_iy%d",iy));
      if ( iy>1) hTemp2[iy]->Add( hTemp1[iy-1] );
    }
    for ( int iy = nYbins ; iy>=1 ;iy--) {
      hTemp2[iy]->SetLineColor(iy);
      hTemp2[iy]->SetFillColor(iy);
      cleverRange(hTemp2[iy],1.5,0.000001);
      if ( iy == nYbins) hTemp2[iy]->Draw("hist");
      else hTemp2[iy]->Draw("hist same");
      if ( iy>=4) leg3->AddEntry(hTemp2[iy], Form("%.2f <m/p_{T} < %.2f ",(float)yBin[iy], (float)yBin[iy+1]), "lf" );
    }
    leg3->Draw();
    cSmear->SaveAs("pdfs/cSmear.pdf");
  }
  
  
  return res;
}
 
#ifndef __CINT__
int main () { unfoldPtMass(); return 0; }  // Main program when run stand-alone
#endif





