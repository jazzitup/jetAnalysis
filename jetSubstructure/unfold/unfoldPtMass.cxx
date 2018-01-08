
//=====================================================================-*-C++-*-
// File and Version Information:
//      $Id: RooUnfoldExample.cxx 348 2014-08-08 22:18:23Z T.J.Adye@rl.ac.uk $
//
// Description:
//      Simple example usage of the RooUnfold package using toy MC.
//
// Authors: Tim Adye <T.J.Adye@rl.ac.uk> and Fergus Wilson <fwilson@slac.stanford.edu>
//
//==============================================================================


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
Double_t smear (Double_t xt)
{
  Double_t xeff= 0.3 + (1.0-0.3)/20*(xt+10.0);  // efficiency
  Double_t x= gRandom->Rndm();
  if (x>xeff) return cutdummy;
  Double_t xsmear= gRandom->Gaus(-2.5,0.2);     // bias and smear
  return xt+xsmear;
}

//==============================================================================
// Example Unfolding
//==============================================================================

struct unfoldHists {
  TH1D* hptTruth;
  TH1D* hmassTruth;
  TH1D* hptReco;
  TH1D* hmassReco;
  TH1D* hptUnf;
  TH1D* hmassUnf;
  
  TH1D* hptDataRaw;
  TH1D* hptDataUnf;
  TH1D* hmassDataRaw;
  TH1D* hmassDataUnf;


};

unfoldHists drawOne( int icent = 0, TString fnameData = "", TString fnameMc="", int optX=1, int optY=3);

void unfoldPtMass(int optX =1, int optY = 1, TString fnameData = "jetSubstructure_Data_HION9_v4.7_v1_Jan7", TString fnameMc="jetSubstructure_himix_test_v4.6_r4_Trimming_rSub0.25_fCut0.10") {
  
  unfoldHists hists[7]; 
  hists[0] = drawOne(0, fnameData, fnameMc, optX, optY);
  hists[6] = drawOne(6, fnameData, fnameMc, optX, optY);

  TCanvas* c10 = new TCanvas("c10","",800,800);
  c10->Divide(2,2);
  c10->cd(1);
  cleverRange(hists[0].hmassTruth,1.8);
  hists[0].hmassTruth->SetNdivisions(505);
  hists[0].hmassTruth->Draw("hist");
  hists[0].hmassUnf->Draw("e same");
  hists[0].hmassReco->Draw("same");
  drawCentrality(0, 0.6,0.5,1,30);
  TLegend *leg2 = new TLegend(0.363962,0.6955645,0.9999478,0.9294355,NULL,"brNDC");
  easyLeg(leg2,"MC closure test");
  leg2->AddEntry(hists[0].hmassTruth,"Truth","l");
  leg2->AddEntry(hists[0].hmassReco,"Reco","pl");
  leg2->AddEntry(hists[0].hmassUnf,"Unfolded","pl");
  leg2->Draw();

  c10->cd(2);
  cleverRange(hists[0].hptTruth,1.8);
  hists[0].hptTruth->SetNdivisions(505);
  hists[0].hptTruth->Draw("hist");
  hists[0].hptUnf->Draw("e same");
  hists[0].hptReco->Draw("same");

  c10->cd(3);
  cleverRange(hists[6].hmassTruth,1.8);
  hists[6].hmassTruth->SetNdivisions(505);
  hists[6].hmassTruth->Draw("hist");
  hists[6].hmassUnf->Draw("e same");
  hists[6].hmassReco->Draw("same");
  drawCentrality(6, 0.6,0.5,1,30);
  c10->cd(4);
  cleverRange(hists[6].hptTruth,1.8);
  hists[6].hptTruth->SetNdivisions(505);
  hists[6].hptTruth->Draw("hist");
  hists[6].hptUnf->Draw("e same");
  hists[6].hptReco->Draw("same");
  
  c10->SaveAs(Form("%s_optX%d_optY%d.pdf",fnameData.Data(),optX,optY));



  TCanvas* c11 = new TCanvas("c11","",800,800);
  c11->Divide(2,2);
  c11->cd(1);
  cleverRange(hists[0].hmassDataRaw,2);
  hists[0].hmassDataRaw->SetNdivisions(505);
  handsomeTH1(hists[0].hmassDataRaw,8);
  handsomeTH1(hists[0].hmassDataUnf,2);
  hists[0].hmassDataRaw->SetXTitle("m^{2} (GeV^{2})");
  hists[0].hmassDataRaw->Draw("hist");
  hists[0].hmassDataUnf->Draw("e same");
  drawCentrality(0, 0.6,0.5,1,30);
  TLegend *leg3 = new TLegend(0.363962,0.755645,0.9999478,0.9294355,NULL,"brNDC");
  easyLeg(leg3,"PbPb Data, 5.02 TeV");
  leg3->AddEntry(hists[0].hmassDataRaw,"Reco","l");
  leg3->AddEntry(hists[0].hmassDataUnf,"Unfolded","pl");
  leg3->Draw();

  c11->cd(2);
  cleverRange(hists[0].hptDataRaw,2);
  hists[0].hptDataRaw->SetNdivisions(505);
  handsomeTH1(hists[0].hptDataRaw,8);
  handsomeTH1(hists[0].hptDataUnf,2);
  hists[0].hptDataRaw->SetXTitle("p_{T} GeV");
  hists[0].hptDataRaw->Draw("hist");
  hists[0].hptDataUnf->Draw("e same");

  c11->cd(3);
  cleverRange(hists[6].hmassDataRaw,2);
  hists[6].hmassDataRaw->SetNdivisions(505);
  handsomeTH1(hists[6].hmassDataRaw,8);
  handsomeTH1(hists[6].hmassDataUnf,2);
  hists[6].hmassDataRaw->SetXTitle("m^{2} (GeV^{2})");
  hists[6].hmassDataRaw->Draw("hist");
  hists[6].hmassDataUnf->Draw("e same");
  drawCentrality(6, 0.6,0.5,1,30);


  c11->cd(4);
  cleverRange(hists[6].hptDataRaw,2);
  hists[6].hptDataRaw->SetNdivisions(505);
  handsomeTH1(hists[6].hptDataRaw,8);
  handsomeTH1(hists[6].hptDataUnf,2);
  hists[6].hptDataRaw->SetXTitle("p_{T} GeV");
  hists[6].hptDataRaw->Draw("hist");
  hists[6].hptDataUnf->Draw("e same");

  c11->SaveAs(Form("%s_optX%d_optY%d_DATA.pdf",fnameData.Data(),optX,optY));

}

unfoldHists drawOne( int icent, TString fnameData, TString fnameMc , int optX, int optY)
{
  int nIter = 4;
  cout << "==================================== TRAIN ====================================" << endl;
  TFile* fMc = new TFile(Form("../ntuples/%s.root",fnameMc.Data()));
  TTree* trMc = (TTree*)fMc->Get("tr");
  jetSubStr myJetMc;
  TBranch       *b_myJetSubMc;
  trMc->SetBranchAddress("jets", &(myJetMc.cent), &b_myJetSubMc);
  // Train with a Breit-Wigner, mean 0.3 and width 2.5.
  cout << " MC entries = " << trMc->GetEntries() << endl;

  TFile* fData = new TFile(Form("../ntuples/%s.root",fnameData.Data()));
  TTree* trData = (TTree*)fData->Get("tr");
  jetSubStr myJetData;
  TBranch       *b_myJetSubData;
  trData->SetBranchAddress("jets", &(myJetData.cent), &b_myJetSubData);
  // Train with a Breit-Wigner, mean 0.3 and width 2.5.
  cout << " Data entries = " << trData->GetEntries() << endl;



  const int nPtBins = 9;
  double ptBin[nPtBins+1] = {130,150,170,190,210,240,270,300,350,400};
  const int nNTrkBins = 15;
  const int nMassBins = 28;
  double massBin[nMassBins+1];

  TH1D* hptTemp = new TH1D("hptTemp","",nPtBins,ptBin);

  int nXbins;
  double xBin[100];
  if ( optX == 1 ) {   
    nXbins = nPtBins;
    for ( int i=0 ; i<= nXbins ; i++) {
      xBin[i] = ptBin[i] ;
    }
  }
  else if ( optX == 2)  {  // nTrks
    nXbins = nNTrkBins;
    for ( int i=0 ; i<= nXbins ; i++) {
      xBin[i] = -10 + ( 35 + 10 ) * float(i)/nXbins; 
    }
  }
  
  for ( int i=0 ; i<= nMassBins ; i++) { 
    if ( optY == 1)       
      massBin[i] = -500. + (3000.+500.) * float(i)/nMassBins ;
    else if ( optY == 2) 
      massBin[i] = -.03 + (0.07+0.03) * float(i)/nMassBins ;
    else if ( optY == 3) 
      massBin[i] = -10 + (60) * float(i)/nMassBins ;
    else if ( optY == 4) 
      massBin[i] = -.1 + (0.4) * float(i)/nMassBins ;
    else if ( optY == 5) 
      massBin[i] = -200 + (800+100) * float(i)/nMassBins ;
    else if ( optY == 6) 
      massBin[i] = -.05 + (0.15) * float(i)/nMassBins ;
    else if ( optY == 7) 
      massBin[i] = -2000 + (2000+2000) * float(i)/nMassBins ;
  }
  
  

  TH2D* hTruth = new TH2D("hTruth","",nXbins,xBin,nMassBins,massBin);
  TH2D* hReco = new TH2D("hReco","",nXbins,xBin,nMassBins,massBin);
  RooUnfoldResponse* res = new RooUnfoldResponse( hTruth, hReco );

  TH2D* hTrueMc = (TH2D*)hTruth->Clone("hTrueMc");
  TH2D* hRecoMc = (TH2D*)hReco->Clone("hRecoMc");

  TH2D* hRawData = (TH2D*)hReco->Clone("hRawData");
  
  for (Int_t i= 0; i<trMc->GetEntries() ; i++) {
    trMc->GetEntry(i);
    if ( myJetMc.cent != icent ) continue; 
    if ( myJetMc.recoPt < 100 ) continue;
    if ( myJetMc.genPt < 150 ) continue;

    double genM2 = myJetMc.genMass* myJetMc.genMass;
    double recoM2 = myJetMc.recoMass * myJetMc.recoMass;  
    if ( myJetMc.recoMass < 0 ) recoM2 = - recoM2;
    //    res->Fill( myJetMc.genPt, genM2 , myJetMc.recoPt, recoM2, myJetMc.weight );
    
    double genMoverPt2 = genM2 / (myJetMc.genPt*myJetMc.genPt);
    double recoMoverPt2 = recoM2 / (myJetMc.recoPt*myJetMc.recoPt);
    
    double genTrimMass = myJetMc.genTrMass;
    double recoTrimMass = myJetMc.recoTrMassCorr;
    
    double recoVarY, truthVarY;
    if (optY==1)  { 
      recoVarY = recoM2;
      truthVarY = genM2;
    }
    else if ( optY==2) {
      recoVarY = recoMoverPt2;
      truthVarY = genMoverPt2;
    }
    else if ( optY==3) {
      truthVarY = genTrimMass;
      recoVarY = recoTrimMass;
    }
    else if ( optY==4) {
      truthVarY = genTrimMass/myJetMc.genPt;
      recoVarY = recoTrimMass/myJetMc.recoPt;
    }
    else if ( optY == 5) { 
      truthVarY = myJetMc.recoChMassGm* myJetMc.recoChMassGm;
      recoVarY = myJetMc.recoChMassRcSubt * myJetMc.recoChMassRcSubt;
      if ( myJetMc.recoChMassRcSubt < 0)   recoVarY = - recoVarY ; 
    }
    else if ( optY == 6) { 
      truthVarY = (myJetMc.genMass * myJetMc.genMass)  / ( myJetMc.genPt * myJetMc.genPt);
      recoVarY = myJetMc.recoChMassRcSubt * myJetMc.recoChMassRcSubt / (myJetMc.recoChPtRcSubt*myJetMc.recoChPtRcSubt);
      if ( myJetMc.recoChMassRcSubt < 0)   recoVarY = - recoVarY ; 
    }
    else if ( optY == 7) { // charge assisted mass
      truthVarY = genM2;
      float recoVarYsqrt = myJetMc.recoChMassRcSubt * myJetMc.recoPt / myJetMc.recoChPtRcSubt ;
      recoVarY = recoVarYsqrt * recoVarYsqrt;
      if ( recoVarYsqrt < 0)   recoVarY = - recoVarY ;
    }
    
    double recoVarX, truthVarX;
    if (optX ==1)  {
      truthVarX = myJetMc.genPt;
      recoVarX = myJetMc.recoPt;
    }
    else if (optX ==2 ) { 
      //      truthVarX = myJetMc.genNch;
      recoVarX = myJetMc.nTrkRaw - myJetMc.nTrkBkg;
      truthVarX = myJetMc.genNch;
    }

    res->Fill(  recoVarX, recoVarY,    truthVarX, truthVarY, myJetMc.weight);
    hRecoMc->Fill ( recoVarX, recoVarY, myJetMc.weight);
    hTrueMc->Fill ( truthVarX, truthVarY, myJetMc.weight);

  }


  cout << "====Fill data ==========" << endl;
  for (Int_t i= 0; i<trData->GetEntries() ; i++) {
    trData->GetEntry(i);
    if ( myJetData.cent != icent ) continue;
    if ( myJetData.recoPt < 150 ) continue;

    double genM2 = myJetData.genMass* myJetData.genMass;
    double recoM2 = myJetData.recoMass * myJetData.recoMass;
    if ( myJetData.recoMass < 0 ) recoM2 = - recoM2;
    //    res->Fill( myJetData.genPt, genM2 , myJetData.recoPt, recoM2, myJetData.weight );

    double genMoverPt2 = genM2 / (myJetData.genPt*myJetData.genPt);
    double recoMoverPt2 = recoM2 / (myJetData.recoPt*myJetData.recoPt);

    double genTrimMass = myJetData.genTrMass;
    double recoTrimMass = myJetData.recoTrMassCorr;

    double recoVarY, truthVarY;
    if (optY==1)  {
      recoVarY = recoM2;
      truthVarY = genM2;
    }
    else if ( optY==2) {
      recoVarY = recoMoverPt2;
      truthVarY = genMoverPt2;
    }
    else if ( optY==3) {
      truthVarY = genTrimMass;
      recoVarY = recoTrimMass;
    }
    else if ( optY==4) {
      truthVarY = genTrimMass/myJetData.genPt;
      recoVarY = recoTrimMass/myJetData.recoPt;
    }
    else if ( optY == 5) {
      truthVarY = myJetData.recoChMassGm* myJetData.recoChMassGm;
      recoVarY = myJetData.recoChMassRcSubt * myJetData.recoChMassRcSubt;
      if ( myJetData.recoChMassRcSubt < 0)   recoVarY = - recoVarY ;
    }
    else if ( optY == 6) {
      truthVarY = (myJetData.genMass * myJetData.genMass)  / ( myJetData.genPt * myJetData.genPt);
      recoVarY = myJetData.recoChMassRcSubt * myJetData.recoChMassRcSubt / (myJetData.recoChPtRcSubt*myJetData.recoChPtRcSubt);
      if ( myJetData.recoChMassRcSubt < 0)   recoVarY = - recoVarY ;
    }
    else if ( optY == 7) { // charge assisted mass 
      truthVarY = genM2; 
      float recoVarYsqrt = myJetData.recoChMassRcSubt * myJetData.recoPt / myJetData.recoChPtRcSubt ;
      recoVarY = recoVarYsqrt * recoVarYsqrt;
      if ( recoVarYsqrt < 0)   recoVarY = - recoVarY ;
    }
    
    double recoVarX, truthVarX;
    if (optX ==1)  {
      truthVarX = myJetData.genPt;
      recoVarX = myJetData.recoPt;
    }
    else if (optX ==2 ) {
      //      truthVarX = myJetData.genNch;
      recoVarX = myJetData.nTrkRaw - myJetData.nTrkBkg;
      truthVarX = myJetData.genNch;
    }
    hRawData->Fill(recoVarX, recoVarY);
  }
  
  cout << "==================================== UNFOLD ===================================" << endl;
  RooUnfoldBayes   unfoldMc (res, hRecoMc, nIter);    // OR
  TH2D* hResultMc  = (TH2D*) unfoldMc.Hreco();
  unfoldMc.PrintTable (cout, hTrueMc);
  
  RooUnfoldBayes   unfoldData (res, hRawData, nIter);    // OR
  TH2D* hResultData  = (TH2D*) unfoldData.Hreco();
  
  int lowXbin =1;
  if ( (optX == 1) && (optY==1) ) {
    lowXbin = hptTemp->FindBin(170.1); 
  }
  TH1D* hptRawData = (TH1D*)hRawData->ProjectionX();
  TH1D* hmassRawData = (TH1D*)hRawData->ProjectionY("hmassRawData",lowXbin);
  TH1D* hptResultData =   (TH1D*)hResultData->ProjectionX();
  TH1D* hmassResultData = (TH1D*)hResultData->ProjectionY("hmassResultData",lowXbin);

  
  

  //  unfoldData.PrintTable (cout, hTrueMc);

  TCanvas* c1 = new TCanvas("c1","",1200,800);
  c1->Divide(3,2);
  c1->cd(1);
  hTrueMc->Draw("colz");
  c1->cd(2);
  hRecoMc->Draw("colz");
  c1->cd(3);
  hResultMc->Draw("colz");
  c1->cd(4);
  TH1D* hmassTrueMc = (TH1D*) hTrueMc->ProjectionY();
  TH1D* hmassRawMc = (TH1D*) hRecoMc->ProjectionY();
  TH1D* hmassResultMc = (TH1D*) hResultMc->ProjectionY("hResultMc_projectionY");
  handsomeTH1(hmassTrueMc,1);
  handsomeTH1(hmassRawMc,8);
  handsomeTH1(hmassResultMc,2);
  if ( optY==1)  { 
    hmassRawMc->SetXTitle("m^{2} (GeV^{2})");
    hmassTrueMc->SetXTitle("m^{2} (GeV^{2})");
  }
  else if (optY==2) {
    hmassRawMc->SetXTitle("(m/p_{T})^{2}");
    hmassTrueMc->SetXTitle("(m/p_{T})^{2}");
  }
  else if (optY==3) {
    hmassRawMc->SetXTitle("Trimmed M (GeV)");
    hmassTrueMc->SetXTitle("Trimmed M (GeV)");
  }
  else if (optY==4) {
    hmassRawMc->SetXTitle("Trimmed m/p_{T}");
    hmassTrueMc->SetXTitle("Trimmed m/p_{T}");
  }
  else if (optY==5) {
    hmassRawMc->SetXTitle("m^{2}_{tracks} (GeV^{2})");
    hmassTrueMc->SetXTitle("m^{2}_{ch} (GeV^{2})");
  }
  else if (optY==6) {
    hmassRawMc->SetXTitle("(m/p_{T})^{2}_{tracks} (GeV^{2})");
    hmassTrueMc->SetXTitle("(m/p_{T})^{2}_{ch} (GeV^{2})");
  }
  else if (optY==7) {
    hmassRawMc->SetXTitle("Track Assisted m^{2} (GeV^{2})");
    hmassTrueMc->SetXTitle("Track Assisted m^{2} (GeV^{2})");
  }


  TH1ScaleByWidth(hmassRawMc);
  TH1ScaleByWidth(hmassTrueMc);
  TH1ScaleByWidth(hmassResultMc);

  cleverRange(hmassRawMc,1.8);
  hmassRawMc->SetNdivisions(505);
  hmassRawMc->Draw("e");
  hmassTrueMc->Draw("hist same");
  hmassResultMc->Draw("e same");
  
  TLegend *leg2 = new TLegend(0.563962,0.6955645,0.9999478,0.9294355,NULL,"brNDC");
  easyLeg(leg2,"Projection");
  leg2->AddEntry(hmassTrueMc,"MC Truth","l");
  leg2->AddEntry(hmassRawMc,"MC Reco","p");
  leg2->AddEntry(hmassResultMc,"MC Unfolded","p");
  leg2->Draw();

  c1->cd(5);
  TH1D* hptTrueMc = (TH1D*) hTrueMc->ProjectionX();
  TH1D* hptRawMc = (TH1D*) hRecoMc->ProjectionX();
  TH1D* hptResultMc = (TH1D*) hResultMc->ProjectionX("hResultMc_hptresultMc");
  handsomeTH1(hptTrueMc,1);
  handsomeTH1(hptRawMc,8);
  handsomeTH1(hptResultMc,2);
  if ( optX==1) { 
    hptRawMc->SetXTitle("p_{T} (GeV)");
    hptTrueMc->SetXTitle("p_{T} (GeV)");
  }
  else if (optX ==2 ) {
    hptRawMc->SetXTitle("N_{ch}");
    hptTrueMc->SetXTitle("N_{ch}");
  }
    
  TH1ScaleByWidth(hptRawMc);
  TH1ScaleByWidth(hptTrueMc);
  TH1ScaleByWidth(hptResultMc);

  cleverRange(hptRawMc,1.8);
  hptRawMc->SetNdivisions(505);
  hptRawMc->Draw("e");
  hptTrueMc->Draw("hist same");
  hptResultMc->Draw("e same");

  leg2->Draw();

  c1->cd(6);
  drawCentrality(icent, 0.2,0.8,1,30);

  c1->SaveAs(Form("%s_cent%d.pdf",fnameData.Data(),icent));


  unfoldHists ret;
  ret.hptTruth = hptTrueMc;
  ret.hptReco = hptRawMc;
  ret.hptUnf  = hptResultMc;
  ret.hmassTruth = hmassTrueMc;
  ret.hmassReco = hmassRawMc;
  ret.hmassUnf  = hmassResultMc;
  
  ret.hptDataRaw = hptRawData;
  ret.hmassDataRaw = hmassRawData;
  ret.hptDataUnf = hptResultData;
  ret.hmassDataUnf = hmassResultData;
 
  return ret;
}

#ifndef __CINT__
int main () { unfoldPtMass(); return 0; }  // Main program when run stand-alone
#endif
