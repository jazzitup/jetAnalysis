
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
  TFile* fmc = new TFile("/Users/yongsunkim/Dropbox/unfolding_toys/out_2_10e7.root");
  //  TFile* fmc = new TFile("out_2_reweighted-to-2.5.root");
  TH1D* mcTruth = (TH1D*)fmc->Get("htrue");
  TH1D* mcReco = (TH1D*)fmc->Get("hmeas");
  TH2D* hmcRes = (TH2D*)fmc->Get("hres");

  TFile* fdata = new TFile("/Users/yongsunkim/Dropbox/unfolding_toys/out_25_10e7_2.root");
  TH1D* dataTruth = (TH1D*)fdata->Get("htrue");
  TH1D* dataReco = (TH1D*)fdata->Get("hmeas");
  TH2D* dataRes = (TH2D*)fdata->Get("hres");
  
  TH1D* hr = (TH1D*)dataReco->Clone("hr");
  hr->Divide(mcReco);

  TFile* hout = new TFile("reweight.root","recreate");
  hr->Write();
  hout->Close();
  
  RooUnfoldResponse* res = new RooUnfoldResponse(0, 0, hmcRes);
    
  vector<int> iter;
  iter.push_back(1); iter.push_back(2);  iter.push_back(4);  iter.push_back(8);  iter.push_back(12);  iter.push_back(20);

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
  TLegend *leg1 = new TLegend(0.4386514,0.2288023,0.7574586,0.8411159,NULL,"brNDC");
  easyLeg(leg1,"(n=2.5), Unfolded by n=2.5");
  leg1->AddEntry(mcTruth,"Truth (n=2)","l");
  for ( int in = 0 ; in < iter.size() ; in++)  {
    mcUnf[in]->Draw("same");
    leg1->AddEntry(mcUnf[in],Form("Iteration %d",iter[in]));
  }
  leg1->Draw();
  gPad->SetLogy();

  c2->cd(3);
  TH1D* ratio[50];
  for ( int in = 0 ; in < iter.size() ; in++)  {
    ratio[in] = (TH1D*)mcUnf[in]->Clone(Form("hratio%d",in));
    ratio[in]->Divide(mcTruth);
    //    ratio[in]->SetAxisRange(0.-20,20,"X");
    ratio[in]->SetAxisRange(0,2,"Y");
   if ( in==0) ratio[in]->Draw();
    else ratio[in]->Draw("same");
   jumSun(0,1,100,1);
  }
  
  c2->cd(2);
  int reBin = 10;
  dataTruth->Rebin(10);
  dataReco->Rebin(10);
  dataTruth->Draw("hist");
  handsomeTH1(dataReco,kBlue);
  dataReco->Draw("same hist");
  TLegend *leg2 = new TLegend(0.4386514,0.2288023,0.7574586,0.8411159,NULL,"brNDC");
  easyLeg(leg2,"Data");
  leg2->AddEntry(dataTruth,"Truth","l");
  leg2->AddEntry(dataReco,"Raw","l");
  for ( int in = 0 ; in < iter.size() ; in++)  {
    dataUnf[in]->Rebin(10);
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
    ratioData[in]->SetAxisRange(0,2,"Y");
   if ( in==0) ratioData[in]->Draw();
    else ratioData[in]->Draw("same");
   jumSun(0,1,100,1);
  }
  ratioRaw->Draw("same");


}

#ifndef __CINT__
int main () { toy2(); return 0; }  // Main program when run stand-alone
#endif






