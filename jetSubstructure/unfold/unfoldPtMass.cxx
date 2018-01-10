
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
  hists[3] = drawOne(3, fnameData, fnameMc, optX, optY);
  hists[6] = drawOne(6, fnameData, fnameMc, optX, optY);

  TCanvas* c10mass = new TCanvas("c10_centmass","",500,500);
  makeEfficiencyCanvas(c10mass,1);
  c10mass->cd(1);
  //  cleverRange(hists[0].hmassTruth,1.8);
  hists[0].hmassTruth->SetNdivisions(505);
  hists[0].hmassTruth->Draw("hist");
  hists[0].hmassUnf->Draw("e same");
  hists[0].hmassReco->Draw("same");
  gPad->SetLogy();
  drawCentrality(0, 0.6,0.8,1,30);
  TLegend *leg2 = new TLegend(0.3646586,0.0627959,1,0.4054297,NULL,"brNDC");
  easyLeg(leg2,"MC closure test");
  leg2->AddEntry(hists[0].hmassTruth,"Truth","l");
  leg2->AddEntry(hists[0].hmassReco,"Reco","pl");
  leg2->AddEntry(hists[0].hmassUnf,"Unfolded","pl");
  leg2->Draw();

  c10mass->cd(2);
  TH1D* hRatio0 = (TH1D*)hists[0].hmassTruth->Clone(Form("%s_r1",hists[0].hmassTruth->GetName()));
  TH1D* hRatio1 = (TH1D*)hists[0].hmassReco->Clone(Form("%s_r1",hists[0].hmassReco->GetName()));
  TH1D* hRatio2 = (TH1D*)hists[0].hmassUnf->Clone(Form("%s_r1",hists[0].hmassUnf->GetName()));
  hRatio0->Divide(hists[0].hmassTruth);
  hRatio1->Divide(hists[0].hmassTruth);
  hRatio2->Divide(hists[0].hmassTruth);
  hRatio0->SetAxisRange(0,3,"Y");
  fixedFontHist(hRatio0,3);
  hRatio0->DrawCopy("hist");
  hRatio1->DrawCopy("same");
  hRatio2->DrawCopy("same");



  TCanvas* c10pt = new TCanvas("c10_centpt","",500,500);
  makeEfficiencyCanvas(c10pt,1);
  c10pt->cd(1);
  //  cleverRange(hists[0].hptTruth,1.8);
  hists[0].hptTruth->SetNdivisions(505);
  hists[0].hptTruth->DrawCopy("hist");
  hists[0].hptUnf->DrawCopy("e same");
  hists[0].hptReco->DrawCopy("same");
  gPad->SetLogy();
  
  c10pt->cd(2);
  hRatio0 = (TH1D*)hists[0].hptTruth->Clone(Form("%s_r1",hists[0].hptTruth->GetName()));
  hRatio1 = (TH1D*)hists[0].hptReco->Clone(Form("%s_r1",hists[0].hptReco->GetName()));
  hRatio2 = (TH1D*)hists[0].hptUnf->Clone(Form("%s_r1",hists[0].hptUnf->GetName()));
  hRatio0->Divide(hists[0].hptTruth);
  hRatio1->Divide(hists[0].hptTruth);
  hRatio2->Divide(hists[0].hptTruth);
  hRatio0->SetAxisRange(0,3,"Y");
  fixedFontHist(hRatio0,3);
  hRatio0->DrawCopy("hist");
  hRatio1->DrawCopy("same");
  hRatio2->DrawCopy("same");


  TCanvas* c10pmass = new TCanvas("c10_perimass","",500,500);
  makeEfficiencyCanvas(c10pmass,1);

  c10pmass->cd(1);
  //  cleverRange(hists[6].hmassTruth,1.8);
  hists[6].hmassTruth->SetNdivisions(505);
  hists[6].hmassTruth->Draw("hist");
  hists[6].hmassUnf->Draw("e same");
  hists[6].hmassReco->Draw("same");
  drawCentrality(6, 0.6,0.7,1,30);
  gPad->SetLogy();
  
  c10pmass->cd(2);
  hRatio0 = (TH1D*)hists[6].hmassTruth->Clone(Form("%s_r1",hists[6].hmassTruth->GetName()));
  hRatio1 = (TH1D*)hists[6].hmassReco->Clone(Form("%s_r1",hists[6].hmassReco->GetName()));
  hRatio2 = (TH1D*)hists[6].hmassUnf->Clone(Form("%s_r1",hists[6].hmassUnf->GetName()));
  hRatio0->Divide(hists[6].hmassTruth);
  hRatio1->Divide(hists[6].hmassTruth);
  hRatio2->Divide(hists[6].hmassTruth);
  hRatio0->SetAxisRange(0,3,"Y");
  fixedFontHist(hRatio0,3);
  hRatio0->DrawCopy("hist");
  hRatio1->DrawCopy("same");
  hRatio2->DrawCopy("same");



  TCanvas* c10ppt = new TCanvas("c10_peript","",500,500);
  makeEfficiencyCanvas(c10ppt,1);
  c10ppt->cd(1);
  //  cleverRange(hists[6].hptTruth,1.8);
  hists[6].hptTruth->SetNdivisions(505);
  hists[6].hptTruth->DrawCopy("hist");
  hists[6].hptUnf->DrawCopy("e same");
  hists[6].hptReco->DrawCopy("same");
  gPad->SetLogy();

  c10ppt->cd(2);
  hRatio0 = (TH1D*)hists[6].hptTruth->Clone(Form("%s_r1",hists[6].hptTruth->GetName()));
  hRatio1 = (TH1D*)hists[6].hptReco->Clone(Form("%s_r1",hists[6].hptReco->GetName()));
  hRatio2 = (TH1D*)hists[6].hptUnf->Clone(Form("%s_r1",hists[6].hptUnf->GetName()));
  hRatio0->Divide(hists[6].hptTruth);
  hRatio1->Divide(hists[6].hptTruth);
  hRatio2->Divide(hists[6].hptTruth);
  hRatio0->SetAxisRange(0,3,"Y");
  fixedFontHist(hRatio0,3);
  hRatio0->DrawCopy("hist");
  hRatio1->DrawCopy("same");
  hRatio2->DrawCopy("same");
  
  c10pt->SaveAs(Form("%s_optX%d_optY%d_central_pt.pdf",fnameData.Data(),optX,optY));
  c10mass->SaveAs(Form("%s_optX%d_optY%d_central_mass.pdf",fnameData.Data(),optX,optY));
  c10ppt->SaveAs(Form("%s_optX%d_optY%d_peri_pt.pdf",fnameData.Data(),optX,optY));
  c10pmass->SaveAs(Form("%s_optX%d_optY%d_peri_mass.pdf",fnameData.Data(),optX,optY));
  


  TCanvas* c11_1 = new TCanvas("c11_1","",500,500);
  makeEfficiencyCanvas(c11_1,1);
  c11_1->cd(1);
  //  cleverRange(hists[0].hmassDataRaw,2);
  hists[0].hmassDataRaw->SetNdivisions(505);
  handsomeTH1(hists[0].hmassDataRaw,8);
  handsomeTH1(hists[0].hmassDataUnf,2);
  hists[0].hmassDataRaw->SetXTitle("m^{2} (GeV^{2})");
  cleverRangeLog(hists[0].hmassDataRaw,10,1e-3);
  hists[0].hmassDataRaw->Draw("hist");
  hists[0].hmassDataUnf->Draw("e same");
  drawCentrality(0, 0.6,0.7,1,25);
  TLegend *leg3 = new TLegend(0.463962,0.755645,0.9999478,0.9294355,NULL,"brNDC");
  easyLeg(leg3,"PbPb Data, 5.02 TeV");
  leg3->AddEntry(hists[0].hmassDataRaw,"Reco","l");
  leg3->AddEntry(hists[0].hmassDataUnf,"Unfolded","pl");
  leg3->Draw();
  gPad->SetLogy();
  
  c11_1->cd(2);
  hRatio0 = (TH1D*)hists[0].hmassDataUnf->Clone(Form("%s_r1_unfol",hists[0].hmassDataUnf->GetName()));
  hRatio1 = (TH1D*)hists[0].hmassDataRaw->Clone(Form("%s_r1_unRaw",hists[0].hmassDataRaw->GetName()));
  hRatio0->Divide(hists[0].hmassDataUnf);
  hRatio1->Divide(hists[0].hmassDataUnf);
  hRatio0->SetAxisRange(0,3,"Y");
  fixedFontHist(hRatio0,3);
  hRatio0->SetNdivisions(505);
  hRatio0->DrawCopy("hist");
  hRatio1->DrawCopy("same");

  
  TCanvas* c11_2 = new TCanvas("c11_2","",500,500);
  makeEfficiencyCanvas(c11_2,1);
  c11_2->cd(1);

  //  cleverRange(hists[0].hptDataRaw,2);
  hists[0].hptDataRaw->SetNdivisions(505);
  handsomeTH1(hists[0].hptDataRaw,8);
  handsomeTH1(hists[0].hptDataUnf,2);
  hists[0].hptDataRaw->SetXTitle("p_{T} GeV");
  hists[0].hptDataRaw->Draw("hist");
  hists[0].hptDataUnf->Draw("e same");
  gPad->SetLogy();

  c11_2->cd(2);
  hRatio0 = (TH1D*)hists[0].hptDataUnf->Clone(Form("%s_r1_unfol",hists[0].hptDataUnf->GetName()));
  hRatio1 = (TH1D*)hists[0].hptDataRaw->Clone(Form("%s_r1_unRaw",hists[0].hptDataRaw->GetName()));
  hRatio0->Divide(hists[0].hptDataUnf);
  hRatio1->Divide(hists[0].hptDataUnf);
  hRatio0->SetAxisRange(0,3,"Y");
  fixedFontHist(hRatio0,3);
  hRatio0->SetNdivisions(505);
  hRatio0->DrawCopy("hist");
  hRatio1->DrawCopy("same");


  TCanvas* c11_3 = new TCanvas("c11_3","",500,500);
  makeEfficiencyCanvas(c11_3,1);
  c11_3->cd(1);
  hists[6].hmassDataRaw->SetNdivisions(505);
  handsomeTH1(hists[6].hmassDataRaw,8);
  handsomeTH1(hists[6].hmassDataUnf,2);
  hists[6].hmassDataRaw->SetXTitle("m^{2} (GeV^{2})");
  hists[6].hmassDataRaw->Draw("hist");
  hists[6].hmassDataUnf->Draw("e same");
  drawCentrality(6, 0.6,0.7,1,25);
  gPad->SetLogy();

  c11_3->cd(2);
  hRatio0 = (TH1D*)hists[6].hmassDataUnf->Clone(Form("%s_r1_unfol",hists[6].hmassDataUnf->GetName()));
  hRatio1 = (TH1D*)hists[6].hmassDataRaw->Clone(Form("%s_r1_unRaw",hists[6].hmassDataRaw->GetName()));
  hRatio0->Divide(hists[6].hmassDataUnf);
  hRatio1->Divide(hists[6].hmassDataUnf);
  hRatio0->SetAxisRange(0,3,"Y");
  fixedFontHist(hRatio0,3);
  hRatio0->SetNdivisions(505);
  hRatio0->DrawCopy("hist");
  hRatio1->DrawCopy("same");


  TCanvas* c11_4 = new TCanvas("c11_4","",500,500);
  makeEfficiencyCanvas(c11_4,1);
  c11_4->cd(1);

  hists[6].hptDataRaw->SetNdivisions(505);
  handsomeTH1(hists[6].hptDataRaw,8);
  handsomeTH1(hists[6].hptDataUnf,2);
  hists[6].hptDataRaw->SetXTitle("p_{T} GeV");
  hists[6].hptDataRaw->Draw("hist");
  hists[6].hptDataUnf->Draw("e same");
  gPad->SetLogy();

  c11_4->cd(2);
  hRatio0 = (TH1D*)hists[6].hptDataUnf->Clone(Form("%s_r1_unfol",hists[6].hptDataUnf->GetName()));
  hRatio1 = (TH1D*)hists[6].hptDataRaw->Clone(Form("%s_r1_unRaw",hists[6].hptDataRaw->GetName()));
  hRatio0->Divide(hists[6].hptDataUnf);
  hRatio1->Divide(hists[6].hptDataUnf);
  hRatio0->SetAxisRange(0,3,"Y");
  fixedFontHist(hRatio0,3);
  hRatio0->SetNdivisions(505);
  hRatio0->DrawCopy("hist");
  hRatio1->DrawCopy("same");

  c11_1->SaveAs(Form("%s_optX%d_optY%d_DATA_1.pdf",fnameData.Data(),optX,optY));
  c11_2->SaveAs(Form("%s_optX%d_optY%d_DATA_2.pdf",fnameData.Data(),optX,optY));
  c11_3->SaveAs(Form("%s_optX%d_optY%d_DATA_3.pdf",fnameData.Data(),optX,optY));
  c11_4->SaveAs(Form("%s_optX%d_optY%d_DATA_4.pdf",fnameData.Data(),optX,optY));
  
  TCanvas* c21 = new TCanvas("c21","",1000,1000);
  c21->Divide(2,2);
  c21->cd(1);
  handsomeTH1(hists[0].hptUnf,1);
  handsomeTH1(hists[3].hptUnf,2);
  handsomeTH1(hists[6].hptUnf,4);
  scaleInt(hists[0].hptUnf);
  scaleInt(hists[3].hptUnf);
  scaleInt(hists[6].hptUnf);
  hists[0].hptUnf->SetAxisRange(0.001,1,"Y");
  hists[0].hptUnf->SetTitle("");
  hists[0].hptUnf->SetXTitle("pT (GeV)");
  hists[0].hptUnf->SetYTitle("Normalized Entries");
  hists[0].hptUnf->SetAxisRange(151,380,"X");
  hists[0].hptUnf->DrawCopy();
  hists[3].hptUnf->DrawCopy("same");
  hists[6].hptUnf->DrawCopy("same");
  gPad->SetLogy();
  
  c21->cd(2);
  handsomeTH1(hists[0].hptDataUnf,1);
  handsomeTH1(hists[3].hptDataUnf,2);
  handsomeTH1(hists[6].hptDataUnf,4);
  scaleInt(hists[0].hptDataUnf);
  scaleInt(hists[3].hptDataUnf);
  scaleInt(hists[6].hptDataUnf);
  hists[0].hptDataUnf->SetAxisRange(0.001,1,"Y");
  hists[0].hptDataUnf->SetTitle("");
  hists[0].hptDataUnf->SetXTitle("pT (GeV)");
  hists[0].hptDataUnf->SetYTitle("Normalized Entries");
  hists[0].hptDataUnf->SetAxisRange(151,380,"X");
  hists[0].hptDataUnf->DrawCopy();
  hists[3].hptDataUnf->DrawCopy("same");
  hists[6].hptDataUnf->DrawCopy("same");
  gPad->SetLogy();

  c21->cd(3);
  hRatio0 = (TH1D*)hists[0].hptUnf->Clone(Form("%s_hRatio0",hists[0].hptUnf->GetName()));
  TH1D* hRatio3 = (TH1D*)hists[3].hptUnf->Clone(Form("%s_hRatio0",hists[3].hptUnf->GetName()));
  TH1D* hRatio6 = (TH1D*)hists[6].hptUnf->Clone(Form("%s_hRatio0",hists[6].hptUnf->GetName()));
  hRatio0->Divide(hists[6].hptUnf);
  hRatio3->Divide(hists[6].hptUnf);
  hRatio6->Divide(hists[6].hptUnf);
  hRatio0->SetAxisRange(0.5,1.5,"Y");
  hRatio0->DrawCopy("");
  hRatio3->DrawCopy("same");
  hRatio6->DrawCopy("same hist");

  c21->cd(4);
  hRatio0 = (TH1D*)hists[0].hptDataUnf->Clone(Form("%s_hRatio0",hists[0].hptDataUnf->GetName()));
  hRatio3 = (TH1D*)hists[3].hptDataUnf->Clone(Form("%s_hRatio0",hists[3].hptDataUnf->GetName()));
  hRatio6 = (TH1D*)hists[6].hptDataUnf->Clone(Form("%s_hRatio0",hists[6].hptDataUnf->GetName()));
  hRatio0->Divide(hists[6].hptDataUnf);
  hRatio3->Divide(hists[6].hptDataUnf);
  hRatio6->Divide(hists[6].hptDataUnf);
  hRatio0->SetAxisRange(0.5,1.5,"Y");
  hRatio0->DrawCopy("");
  hRatio3->DrawCopy("same");
  hRatio6->DrawCopy("same hist");

  c21->SaveAs(Form("%s_optX%d_optY%d_pt_centralityDependence.pdf",fnameData.Data(),optX,optY));

  TCanvas* c22 = new TCanvas("c22","",1000,1000);
  c22->Divide(2,2);
  c22->cd(1);
  handsomeTH1(hists[0].hmassUnf,1);
  handsomeTH1(hists[3].hmassUnf,2);
  handsomeTH1(hists[6].hmassUnf,4);
  scaleInt(hists[0].hmassUnf);
  scaleInt(hists[3].hmassUnf);
  scaleInt(hists[6].hmassUnf);
  hists[0].hmassUnf->SetAxisRange(0.001,1,"Y");
  hists[0].hmassUnf->SetTitle("");
  hists[0].hmassUnf->SetXTitle("m^{2} (GeV^{2})");
  hists[0].hmassUnf->SetYTitle("Normalized Entries");
  hists[0].hmassUnf->DrawCopy();
  hists[3].hmassUnf->DrawCopy("same");
  hists[6].hmassUnf->DrawCopy("same");
  gPad->SetLogy();

  c22->cd(2);
  handsomeTH1(hists[0].hmassDataUnf,1);
  handsomeTH1(hists[3].hmassDataUnf,2);
  handsomeTH1(hists[6].hmassDataUnf,4);
  scaleInt(hists[0].hmassDataUnf);
  scaleInt(hists[3].hmassDataUnf);
  scaleInt(hists[6].hmassDataUnf);
  hists[0].hmassDataUnf->SetAxisRange(0.001,1,"Y");
  hists[0].hmassDataUnf->SetTitle("");
  hists[0].hmassDataUnf->SetXTitle("m^{2} (GeV^{2})");
  hists[0].hmassDataUnf->SetYTitle("Normalized Entries");
  hists[0].hmassDataUnf->DrawCopy();
  hists[3].hmassDataUnf->DrawCopy("same");
  hists[6].hmassDataUnf->DrawCopy("same");
  gPad->SetLogy();

  c22->cd(3);
  hRatio0 = (TH1D*)hists[0].hmassUnf->Clone(Form("%s_hRatio0",hists[0].hmassUnf->GetName()));
  hRatio3 = (TH1D*)hists[3].hmassUnf->Clone(Form("%s_hRatio0",hists[3].hmassUnf->GetName()));
  hRatio6 = (TH1D*)hists[6].hmassUnf->Clone(Form("%s_hRatio0",hists[6].hmassUnf->GetName()));
  hRatio0->Divide(hists[6].hmassUnf);
  hRatio3->Divide(hists[6].hmassUnf);
  hRatio6->Divide(hists[6].hmassUnf);
  hRatio0->SetAxisRange(0.5,1.5,"Y");
  hRatio0->DrawCopy("");
  hRatio3->DrawCopy("same");
  hRatio6->DrawCopy("same hist");

  c22->cd(4);
  hRatio0 = (TH1D*)hists[0].hmassDataUnf->Clone(Form("%s_hRatio0",hists[0].hmassDataUnf->GetName()));
  hRatio3 = (TH1D*)hists[3].hmassDataUnf->Clone(Form("%s_hRatio0",hists[3].hmassDataUnf->GetName()));
  hRatio6 = (TH1D*)hists[6].hmassDataUnf->Clone(Form("%s_hRatio0",hists[6].hmassDataUnf->GetName()));
  hRatio0->Divide(hists[6].hmassDataUnf);
  hRatio3->Divide(hists[6].hmassDataUnf);
  hRatio6->Divide(hists[6].hmassDataUnf);
  hRatio0->SetAxisRange(0.5,1.5,"Y");
  hRatio0->DrawCopy("");
  hRatio3->DrawCopy("same");
  hRatio6->DrawCopy("same hist");


  c22->SaveAs(Form("%s_optX%d_optY%d_mass_centralityDependence.pdf",fnameData.Data(),optX,optY));

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
  

  const int nMassBins = 12;
  double massBin[nMassBins+1] = { 0,0,0,10,13,15,17,19,21,24,28,35,200};

  double mass2Bin[nMassBins+1];
  for ( int i=0 ; i<= nMassBins ; i++) { 
    if ( optY == 1) {
      if (i==0) 
	mass2Bin[i] = -500; 
      else if (i==1)  
	mass2Bin[i] = -75; 
      else   
	mass2Bin[i] = massBin[i]*massBin[i];
    }
    else if ( optY == 2) 
      mass2Bin[i] = -.03 + (0.07+0.03) * float(i)/nMassBins ;
    else if ( optY == 3) 
      mass2Bin[i] = -10 + (60) * float(i)/nMassBins ;
    else if ( optY == 4) 
      mass2Bin[i] = -.1 + (0.4) * float(i)/nMassBins ;
    else if ( optY == 5) 
      mass2Bin[i] = -200 + (800+100) * float(i)/nMassBins ;
    else if ( optY == 6) 
      mass2Bin[i] = -.05 + (0.15) * float(i)/nMassBins ;
    else if ( optY == 7) 
      mass2Bin[i] = -2000 + (2000+2000) * float(i)/nMassBins ;
  }
  
  

  TH2D* hTruth = new TH2D("hTruth","",nXbins,xBin,nMassBins,mass2Bin);
  TH2D* hReco = new TH2D("hReco","",nXbins,xBin,nMassBins,mass2Bin);
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

  TCanvas* c1 = new TCanvas("c1","",800,400);
  c1->Divide(2,1);
  c1->cd(1);

  TH1D* hmassTrueMc = (TH1D*) hTrueMc->ProjectionY();
  TH1D* hmassRawMc = (TH1D*) hRecoMc->ProjectionY();
  TH1D* hmassResultMc = (TH1D*) hResultMc->ProjectionY("hResultMc_projectionY");
  handsomeTH1(hmassTrueMc,1);
  handsomeTH1(hmassRawMc,8);
  handsomeTH1(hmassResultMc,2);
  if ( optY==1)  { 
    hmassRawMc->SetXTitle("m^{2} (GeV^{2})");
    hmassTrueMc->SetXTitle("m^{2} (GeV^{2})");
    hTrueMc->SetYTitle("m^{2} (GeV^{2})");
    hRecoMc->SetYTitle("m^{2} (GeV^{2})");
  }
  else if (optY==2) {
    hmassRawMc->SetXTitle("(m/p_{T})^{2}");
    hmassTrueMc->SetXTitle("(m/p_{T})^{2}");
    hTrueMc->SetYTitle("(m/p_{T})^{2}");
    hRecoMc->SetYTitle("(m/p_{T})^{2}");
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


  //  TH1ScaleByWidth(hmassRawMc);
  //  TH1ScaleByWidth(hmassTrueMc);
  //  TH1ScaleByWidth(hmassResultMc);

  cleverRange(hmassRawMc,1.8);
  hmassRawMc->SetNdivisions(505);
  //  hmassRawMc->Draw("e");
  //  hmassTrueMc->Draw("hist same");
  //  hmassResultMc->Draw("e same");
  
  /*
    TLegend *leg2 = new TLegend(0.563962,0.6955645,0.9999478,0.9294355,NULL,"brNDC");
    easyLeg(leg2,"Projection");
    leg2->AddEntry(hmassTrueMc,"MC Truth","l");
    leg2->AddEntry(hmassRawMc,"MC Reco","p");
    leg2->AddEntry(hmassResultMc,"MC Unfolded","p");
    leg2->Draw();
  */
  
  
  TH1D* hptTrueMc = (TH1D*) hTrueMc->ProjectionX();
  TH1D* hptRawMc = (TH1D*) hRecoMc->ProjectionX();
  TH1D* hptResultMc = (TH1D*) hResultMc->ProjectionX("hResultMc_hptresultMc");
  handsomeTH1(hptTrueMc,1);
  handsomeTH1(hptRawMc,8);
  handsomeTH1(hptResultMc,2);
  if ( optX==1) { 
    hptRawMc->SetXTitle("p_{T} (GeV)");
    hptTrueMc->SetXTitle("p_{T} (GeV)");
    hTrueMc->SetXTitle("p_{T} (GeV)");
    hRecoMc->SetXTitle("p_{T} (GeV)");
  }
  else if (optX ==2 ) {
    hptRawMc->SetXTitle("N_{ch}");
    hptTrueMc->SetXTitle("N_{ch}");
    hTrueMc->SetXTitle("N_{ch}");
    hRecoMc->SetXTitle("N_{ch}");
  }
    
  //  TH1ScaleByWidth(hptRawMc);
  //  TH1ScaleByWidth(hptTrueMc);
  //  TH1ScaleByWidth(hptResultMc);

  cleverRange(hptRawMc,1.8);
  hptRawMc->SetNdivisions(505);
  //  hptRawMc->Draw("e");
  //  hptTrueMc->Draw("hist same");
  //  hptResultMc->Draw("e same");

  //  leg2->Draw();

  //  drawCentrality(icent, 0.2,0.8,1,30);

  c1->cd(1);
  hTrueMc->Draw("colz");
  c1->cd(2);
  hRecoMc->Draw("colz");
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
