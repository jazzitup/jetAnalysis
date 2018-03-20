
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
#include "unfoldingUtil.h"
#include "TRandom3.h"


void toy() { 
  TH1::SetDefaultSumw2();
  TRandom ran(100);
 
  TH1D* hGen  = new TH1D("hgen","",300,-50,50);
  TH1D* hRec  = new TH1D("hreco","",300,-50,50);

  RooUnfoldResponse* res = new RooUnfoldResponse( hGen, hRec );

  TF1 *fgen = new TF1("fgen","10 + x",-10,10);
  for (int  i = 0 ; i<=10000000; i++) {
    double genVal = fgen->GetRandom();
    double fluc = ran.Gaus(0,1.5);   //ran.Gaus(0, fabs(genVal)*0.1+ 0.1);
    //double fluc = 0.5 ; //
    double recoVal =  genVal + fluc ;
    
    if ( i%2 ==0 ) { 
      hGen->Fill(genVal);
      hRec->Fill(recoVal);
    }
    else { 
      res->Fill(  recoVal, genVal, 1. + fabs(recoVal)*0.05  );
      //      res->Fill(  recoVal, genVal);
    }
  }
  
  vector<int> iter;
  iter.push_back(1); iter.push_back(2);  iter.push_back(4);  iter.push_back(8);  iter.push_back(12);  iter.push_back(20);
  //  iter.push_back(100); 

  TH1D* hUnf[20]; 
  for ( int in = 0 ; in < iter.size() ; in++)  {
    RooUnfoldBayes unfoldMc( res, hRec, iter[in]) ;
    hUnf[in] = (TH1D*)unfoldMc.Hreco();
    handsomeTH1(hUnf[in],in+1);
  }
  TCanvas* c1 = new TCanvas("c1","",800,400);
  c1->Divide(2,1);
  c1->cd(1);
  hGen->Draw("hist");
  hRec->Draw("same e");
  c1->cd(2);
  TH1D* hMatrix = (TH1D*)res->Hresponse();
  hMatrix->Draw("colz");

  TCanvas* c2 = new TCanvas("c2","",600,600);
  makeEfficiencyCanvas(c2,1, 0.05, 0.01, 0.1, 0.3, 0.01);
  c2->cd(1);
  hGen->SetAxisRange(0.-20,20,"X");
  hGen->Draw("hist");
  TLegend *leg1 = new TLegend(0.2386514,0.2288023,0.7574586,0.4411159,NULL,"brNDC");
  easyLeg(leg1,"");
  leg1->AddEntry(hGen,"Truth");
  for ( int in = 0 ; in < iter.size() ; in++)  {
    hUnf[in]->Draw("same");
    leg1->AddEntry(hUnf[in],Form("Iteration %d",iter[in]));
  }
  leg1->Draw();

  c2->cd(2);
  TH1D* ratio[20];
  for ( int in = 0 ; in < iter.size() ; in++)  {
    ratio[in] = (TH1D*)hUnf[in]->Clone(Form("hratio%d",in));
    ratio[in]->Divide(hGen);
    ratio[in]->SetAxisRange(0.-20,20,"X");
    ratio[in]->SetAxisRange(0.7,1.3,"Y");
   if ( in==0) ratio[in]->Draw();
    else ratio[in]->Draw("same");
  }
  jumSun(-20,1,20,1);
}

#ifndef __CINT__
int main () { toy(); return 0; }  // Main program when run stand-alone
#endif






