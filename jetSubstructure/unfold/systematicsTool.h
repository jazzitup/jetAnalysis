#include "../getSdHists.C"
#include "../ntupleDefinition.h"
#include "../commonUtility.h"
#include "../jzWeight.h"
#include "../commonUtility.h"
#include "../JssUtils.h"
#include "unfoldingUtil.h"

void getDATAresults(int kSample=0, int icent=0, int ix=0, TH1D* hdataUnfSq=0, TString dir="");


TH1D* getSysA(int kSample= kPP, int icent = 0, int ix=7, TString s1 ="reweight00varM50percent", TString s2="reweight00varP50percent" )   {
  
  int optX = 1; 
  int optY = 2;

  int nXbins;
  double xBin[30];
  getXbin(nXbins, xBin, optX);

  int nYbins ;
  double yBin[30] ;
  getYbin(nYbins, yBin, optY);
  TH1D* tempHistYsq = new TH1D("tempHistY",";m/p_{T};",nYbins,yBin);

  TH1D* h1 = new TH1D("h1","",nYbins,yBin);
  TH1D* h2 = (TH1D*)h1->Clone("h2");
  
  getDATAresults( kSample, icent, ix, h1, s1);
  getDATAresults( kSample, icent, ix, h2, s2);
  
  TH1D* ret = (TH1D*)h2->Clone(Form("kSample%d_icent%d_ix%d_%s_%s",kSample,icent,ix,s1.Data(), s2.Data()) );
  ret->Add(h1,-1);
  ret->Divide(h1);

  return ret;

}  
 

void getDATAresults(int kSample, int icent, int ix, TH1D* hdataUnfSq, TString dir) {
  
  bool matRwt = 1; 
  bool specRwt = 1;
  int nIter = getRefIter( kSample, icent);
  TFile * fin = new TFile(Form("unfSpectra/%s/kSample%d_matrixRwt%d_spectraRwt%d.root",dir.Data(),kSample, (int)matRwt, (int)specRwt));
  TH1D* hUnf = (TH1D*)fin->Get(Form("hdataUnf1d_icent%d_ix%d_iter%d",icent,ix,nIter));
  //  TH1D* hRaw = (TH1D*)fin->Get(Form("hdataRaw1d_icent%d_ix%d",icent,ix));
  
  hdataUnfSq->Reset();
  cout << " here 1 " << endl;
  hdataUnfSq->Add(hUnf);
  cout << " here 2 " << endl;
  //  hdataRawSq->Reset();
  //  hdataRawSq->Add(hRaw);

}
