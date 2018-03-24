
#if !(defined(__CINT__) || defined(__CLING__)) || defined(__ACLIC__)
#include <iostream>
using std::cout;
using std::endl;

#include "TRandom.h"
#include "TH1D.h"

#include "RooUnfoldResponse.h"
#include "RooUnfoldBayes.h"
#include "RooUnfoldSvd.h"
#include "RooUnfoldTUnfold.h"

#include "../commonUtility.h"
#endif

//==============================================================================
// Global definitions
//==============================================================================

//#include "../JssUtils.h"
#include <TPaletteAxis.h>
//#include "unfoldingUtil.h"
#include "TRandom3.h"


void toy2() { 
  TH1::SetDefaultSumw2();
  TRandom ran(100);
  //  TFile* fmc = new TFile("out_n2.0_res2.0.root_reweight_from_n2.0_res2.0_ton2.0_res2.5.root");
  TFile* fmc = new TFile("outResponse_n2.0_res2.0.root");
  //  TFile* fmc = new TFile("out_20_res100_10e7.root");
  //  TFile* fmc = new TFile("out_n2.0_res2.0_nr.root");
  //  TFile* fmc = new TFile("out_n2.0_res2.0.root_reweight_from_n2.0_res2.0_ton2.0_res2.5_by_truthVariable.root");
  //  TFile* fmc = new TFile("out_n2.0_res2.0_nr1000.root");
  //  TFile* fmc = new TFile("out_n2.0_res1.0_reweight_from_n2res1.0_to_n2.5res1.0_applyTruth.root");
  //  TFile* fmc = new TFile("out_n2.0_res1.0_reweight_from_n2res1.0_to_n2.5res1.0.root");
  //  TFile* fmc = new TFile("out_n2.0_res1.0_noRwt.root");
  //  TFile* fmc = new TFile("out_n2.0_res0.500000.root");
  //  TFile* fmc = new TFile("out_n2.0_res0.500000_reweightedBy_reweight_from_n2res0.5_to_n2.5res0.5_applyTruth.root");
  //  TFile* fmc = new TFile("out_n2.0_res0.500000_reweightedBy_reweight_from_n2res0.5_to_n2.5res0.5.root");
  //  TFile* fmc = new TFile("/Users/yongsunkim/uiucAnalysis/jetAnalysis/jetSubstructure/unfold/out_n2.0_res1.0_reweighted_by_from_n2res1_to_n2.5res1_FIT.root");
  //  TFile* fmc = new TFile("/Users/yongsunkim/uiucAnalysis/jetAnalysis/jetSubstructure/unfold/out_n2.0_res1.0_reweighted_by_from_n2res1_to_n2.5res1.root");
  //  TFile* fmc = new TFile("/Users/yongsunkim/uiucAnalysis/jetAnalysis/jetSubstructure/unfold/out_n2.0_res1.0.root");
  //  TFile* fmc = new TFile("/Users/yongsunkim/Dropbox/unfolding_toys/out_2_10e7.root");
  //  TFile* fmc = new TFile("out_2_reweighted-to-2.5.root");
  TH1D* mcTruth = (TH1D*)fmc->Get("htrue");
  TH1D* mcReco = (TH1D*)fmc->Get("hmeas");
  TH2D* h2McRes  = (TH2D*)fmc->Get("h2Res");
  TH2D* hmeas_htrue  = (TH2D*)fmc->Get("hmeas_htrue");
  RooUnfoldResponse* hmcRes = (RooUnfoldResponse*)fmc->Get("res");
  //  TH2D* hmcRes = (TH2D*)fmc->Get("hres");
  hmcRes->SetName("hmcRes");

  TFile* fdata = new TFile("outResponse_n2.5_res2.0.root");
  //  TFile* fdata = new TFile("out_25_res100_10e7.root");
  //  TFile* fdata = new TFile("out_n2.5_res2.0_nr_ptCut10.root");
  //  TFile* fdata = new TFile("out_n2.5_res2.0_nr1000.root");

  //TFile* fdata = new TFile("out_n2.500000_res0.500000.root");
  //  TFile* fdata = new TFile("out_n2.500000_res1.0_noRwt.root");

  //  TFile* fdata = new TFile("/Users/yongsunkim/uiucAnalysis/jetAnalysis/jetSubstructure/unfold/out_n2.500000_res1.0.root");
  //  TFile* fdata = new TFile("/Users/yongsunkim/Dropbox/unfolding_toys/out_25_10e7_2.root");
  TH1D* dataTruth = (TH1D*)fdata->Get("htrue");
  TH1D* dataReco = (TH1D*)fdata->Get("hmeas");
  RooUnfoldResponse* hdataRes = (RooUnfoldResponse*)fdata->Get("res");
  //  TH2D* dataRes = (TH2D*)fdata->Get("hres");
  hdataRes->SetName("hdataRes");
  
  TH1D* hr = (TH1D*)dataReco->Clone("hr");
  hr->Divide(mcReco);

  TFile* hout = new TFile("reweight.root","recreate");
  hr->Write();
  hout->Close();
  
  //  RooUnfoldResponse* res = hmcRes ;
  //  RooUnfoldResponse* res = new RooUnfoldResponse(0, 0, hmcRes);
  //  RooUnfoldResponse* res = new RooUnfoldResponse(mcReco, mcTruth, hmcRes);
  //  TH2D* matrix2d = (TH2D*)hmcRes->Hresponse();
  
  RooUnfoldResponse* res = new RooUnfoldResponse(mcReco, mcTruth, hmeas_htrue);
  //RooUnfoldResponse* res = new RooUnfoldResponse(mcReco, mcTruth, h2McRes);
  //  RooUnfoldResponse* res = new RooUnfoldResponse(mcReco, mcTruth, matrix2d);
  //  RooUnfoldResponse* res = new RooUnfoldResponse(dataReco, dataTruth, matrix2d);
  res->SetName("newRes");
  
  vector<int> iter;
  iter.push_back(1); iter.push_back(2);  iter.push_back(4);  iter.push_back(10);  
  //  iter.push_back(20); //iter.push_back(40);  iter.push_back(100);
  
  TH1D* mcUnf[50]; 
  TH1D* dataUnf[50]; 
  for ( int in = 0 ; in < iter.size() ; in++)  {
    RooUnfoldBayes unfoldMc( res, mcReco, iter[in]) ;
    mcUnf[in] = (TH1D*)unfoldMc.Hreco();
    handsomeTH1(mcUnf[in],in+1);
    
    RooUnfoldBayes unfoldData( res, dataReco, iter[in]) ;
    dataUnf[in] = (TH1D*)unfoldData.Hreco();
    handsomeTH1(dataUnf[in],in+1);
  }
  
  TCanvas* c2 = new TCanvas("c2","",800,500);
  makeEfficiencyCanvas(c2,2, 0.05, 0.01, 0.1, 0.3, 0.01);
  c2->cd(1);
  mcTruth->Draw("hist");
  handsomeTH1(mcReco,4);
  mcReco->Draw("same hist");
  TLegend *leg1 = new TLegend(0.5384286,0.5098167,1,0.9309817,NULL,"brNDC");
  easyLeg(leg1,"");
  leg1->AddEntry(mcTruth,"Truth (n=2)","l");
  cout << "here 1 "<< endl;
  leg1->AddEntry(mcTruth,"Raw   (n=2)","l");
  for ( int in = 0 ; in < iter.size() ; in++)  {
    mcUnf[in]->Draw("same");
    leg1->AddEntry(mcUnf[in],Form("Iteration %d",iter[in]));
  }
  leg1->Draw();
  gPad->SetLogy();

  cout << "here 1 "<< endl;
  c2->cd(3);
  TH1D* ratio[50];
  for ( int in = 0 ; in < iter.size() ; in++)  {
  cout << "here 1 "<< endl;
    ratio[in] = (TH1D*)mcUnf[in]->Clone(Form("hratio%d",in));
    ratio[in]->Divide(mcTruth);
  cout << "here 1 "<< endl;
    //    ratio[in]->SetAxisRange(0.-20,20,"X");
    ratio[in]->SetAxisRange(0,3,"Y");
   if ( in==0) ratio[in]->Draw();
   else ratio[in]->Draw("same");
   jumSun(-500,1,1000,1);
  }
  
  c2->cd(2);
  int reBin = 1;
  dataTruth->Rebin(reBin);
  dataReco->Rebin(reBin);
  dataTruth->Draw("hist");
  handsomeTH1(dataReco,kBlue);
  dataReco->Draw("same hist");
  TLegend *leg2 = new TLegend(0.5384286,0.5098167,1,0.9309817,NULL,"brNDC");
  easyLeg(leg2,"Data");
  leg2->AddEntry(dataTruth,"Truth n=2.5","l");
  leg2->AddEntry(dataReco,"Raw n=2.5","l");
  for ( int in = 0 ; in < iter.size() ; in++)  {
        dataUnf[in]->Rebin(reBin);
        dataUnf[in]->Draw("same");
        leg2->AddEntry(dataUnf[in],Form("Iteration %d",iter[in]));
  }
  leg2->Draw();
  gPad->SetLogy();

  c2->cd(4);
  TH1D* ratioData[50];
  TH1D* ratioRaw = (TH1D*)dataReco->Clone("ratioRaw");
  ratioRaw->Divide(dataTruth);
  for ( int in = 0 ; in < iter.size() ; in++)  {
    ratioData[in] = (TH1D*)dataUnf[in]->Clone(Form("hratioData%d",in));
    ratioData[in]->Divide(dataTruth);
    //    ratioData[in]->SetAxisRange(0.-20,20,"X");
    ratioData[in]->SetAxisRange(0,3,"Y");
    if ( in==0) ratioData[in]->Draw();
    else ratioData[in]->Draw("same");
    jumSun(-500,1,1000,1);

  }
  ratioRaw->Draw("same");


}

#ifndef __CINT__
int main () { toy2(); return 0; }  // Main program when run stand-alone
#endif






