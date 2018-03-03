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

void removeFluc1(TH1* h) { 
  for ( int i =1 ;  i<=h->GetNbinsX() ; i++) {
    double val  = h->GetBinContent(i);
    double error  = h->GetBinError(i);
    if ( error > val * 0.3 )   {
      h->SetBinContent(i,0);
      h->SetBinError(i,0);
    }
  } 
}

void drawReweighting(int kSample=1, int icent=0) { 

  int nXbins;
  double xBin[30];
  getXbin(nXbins, xBin, 1);

  int nYbins;
  double y2Bin[30];
  double yBin[30];
  getYbin(nYbins, y2Bin, yBin, 78);

  TFile* fin = new TFile("reweightFactors/reweightingFactor_weightCut10_v4.root");
  TH2D* raw2 = (TH2D*)fin->Get(Form("hRatioRaw_kSample%d_icent%d_opt2",kSample,icent));
  TH2D* smooth2 = (TH2D*)fin->Get(Form("hRatioSmooth_kSample%d_icent%d_opt2",kSample,icent));

  TCanvas* cm = new TCanvas("cm","",900,900);
  cm->Divide(3,3);
  for ( int ix= 1 ; ix<= raw2->GetNbinsX(); ix++) {
    cm->cd(ix);
    TH1D* raw1 = (TH1D*)raw2->ProjectionY(Form("raw1_ix%d",ix),ix,ix);
    TH1D* smooth1 = (TH1D*)smooth2->ProjectionY(Form("smooth_ix%d",ix),ix,ix);
    handsomeTH1(raw1,1);
    handsomeTH1(smooth1,2);
    raw1->Draw();
    smooth1->Draw("same hist");
    //    drawdrawText("PbPb 0-10%", 0.2,0.9,1,16);
    drawBin(xBin,ix,"GeV",0.2, 0.8,1,16);    
    
    drawText("Raw ratio", 0.3,0.7,1,16);
    drawText("Smoothened", 0.3,0.6,2,16);
    
  }

  TF1* fit[20];
  int nFineBins = 100;
  float fineEnd = xBin[nXbins];
  float fineBegin = xBin[0];
  TH2D* hout = new TH2D(Form("hRatioFit_kSample%d_icent%d_opt2",kSample,icent),";pT;m/pT",nFineBins,fineBegin,fineEnd, nYbins,yBin);
  TCanvas* cm2 = new TCanvas("cm2","",900,600);
  cm2->Divide(3,2);
  for ( int iy= 1 ; iy<= raw2->GetNbinsY(); iy++) {
    cm2->cd(iy);
    TH1D* raw1 = (TH1D*)raw2->ProjectionX(Form("raw1_iy%d",iy),iy,iy);
    //    TH1D* smooth1 = (TH1D*)smooth2->ProjectionX(Form("smooth_iy%d",iy),iy,iy);
    handsomeTH1(raw1,1);
    //    handsomeTH1(smooth1,2);
    raw1->SetAxisRange(0,6,"Y");
    if ( (kSample==kPP) && (icent==0) && (iy==1) ) { 
      raw1->SetAxisRange(0,14,"Y"); raw1->SetAxisRange(100,350,"X");
    }
    removeFluc1(raw1);

    if ( kSample == kPP ) { 
      raw1->Fit("pol2","","",100,900);
      fit[iy] = raw1->GetFunction("pol2");
    }
    else {
      raw1->Fit("pol1","","",100,900);
      fit[iy] = raw1->GetFunction("pol1");
    }
    //    raw1->Fit("pol1","","",100,900);
    raw1->Draw();
    //    smooth1->Draw("same hist");
    //    drawText("PbPb 0-10%", 0.2,0.9,1,16);
    drawCentrality(kSample, icent, 0.2,0.85,1,16);
    drawBin(yBin,iy," for m/p_{T}",0.2, 0.73,1,16);
    //    drawText("Raw ratio", 0.3,0.7,1,16);
    //    drawText("Smoothened", 0.3,0.6,2,16);

    fit[iy]->SetName(Form("weightFit_kSample_icent_iy%d",iy));
    cout << " p1 = " << fit[iy]->GetParameter(1);
    for ( int ii = 1 ; ii<= hout->GetNbinsX() ; ii++)  {
      hout->SetBinContent( ii, iy,   fit[iy]->Eval( fineBegin + (fineEnd - fineBegin)/nFineBins * ii ) );
      hout->SetBinError( ii, iy, 0.0001);
    }
    
    TH1D* htemp = (TH1D*)hout->ProjectionX(Form("_%d_iy",iy),iy,iy);
    handsomeTH1(htemp,2);
    //    htemp->Draw("same e");
  }  

  cm2->SaveAs(Form("reweightFactors/fit_kSample%d_icent%d.pdf",kSample,icent));
  
  TFile* fout = new TFile("reweightFactors/reweightingFactor_v4_fit.root","update");
  for ( int iy= 1 ; iy<= raw2->GetNbinsY(); iy++) {
    fit[iy]->Write();
  }
  hout->Write();  
  
    
}
