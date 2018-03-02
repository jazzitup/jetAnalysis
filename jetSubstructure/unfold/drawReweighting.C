#include <iostream>
using std::cout;
using std::endl;

#include "TRandom.h"
#include "TH1D.h"

#include "../getSdHists.C"
#include "../ntupleDefinition.h"
#include "../commonUtility.h"
#include "../jzWeight.h"
#include "unfoldingUtil.h"
#include <TPaletteAxis.h>
#include "../JssUtils.h"

void drawReweighting() { 

  int nXbins;
  double xBin[30];
  getXbin(nXbins, xBin, 1);

  TFile* fin = new TFile("reweightFactors/reweightingFactor_weightCut10_v3.root");
  TH2D* raw2 = (TH2D*)fin->Get("hRatioRaw_kSample1_icent0_opt2");
  TH2D* smooth2 = (TH2D*)fin->Get("hRatioSmooth_kSample1_icent0_opt2");

  TCanvas* cm = new TCanvas("cm","",1200,800);
  cm->Divide(4,3);
  for ( int ix= 1 ; ix<= raw2->GetNbinsX(); ix++) {
    cm->cd(ix);
    TH1D* raw1 = (TH1D*)raw2->ProjectionY(Form("raw1_ix%d",ix),ix,ix);
    TH1D* smooth1 = (TH1D*)smooth2->ProjectionY(Form("smooth_ix%d",ix),ix,ix);
    handsomeTH1(raw1,1);
    handsomeTH1(smooth1,2);
    raw1->Draw();
    smooth1->Draw("same");
    drawText("PbPb 0-10%", 0.2,0.9,1,16);
    drawBin(xBin,ix,"GeV",0.2, 0.8,1,16);    

    drawText("Raw ratio", 0.3,0.7,1,16);
    drawText("Smoothened", 0.3,0.6,2,16);
    
  }
  
}
