#include <iostream>
using std::cout;
using std::endl;

#include "TRandom.h"
#include "TH1D.h"
#include "../getSdHists.C"
#include "../ntupleDefinition_v50.h"
#include "../commonUtility.h"
#include "../jzWeight.h"
#include "unfoldingUtil.h"
#include "../JssUtils.h"
#include <TPaletteAxis.h>
#include <TGraphErrors.h>

double statUsed = 1;

void drawTrkR() { 
  TH1::SetDefaultSumw2();


  TCanvas* c1 = new TCanvas("c1","",500,500);
  TH1D* htemp = new TH1D("htemp",";p_{T};R^{trk}",100,0,500);
  handsomeTH1(htemp,1);
  htemp->SetAxisRange(0.85,1.2,"Y");
  htemp->Draw();
  TFile* fpp = new TFile("R_trk/Rtrk_kSample0_cent0.root");
  TGraphErrors* gpp1 = (TGraphErrors*)fpp->Get("hRtrk_im2");
  TGraphErrors* gpp2 = (TGraphErrors*)fpp->Get("hRtrk_im4");
  TFile* fpbpb = new TFile("R_trk/Rtrk_kSample1_cent0.root");
  TGraphErrors* gpbpb1 = (TGraphErrors*)fpbpb->Get("hRtrk_im2");
  TGraphErrors* gpbpb2 = (TGraphErrors*)fpbpb->Get("hRtrk_im4");
  handsomeTG1(gpp1,1);
  handsomeTG1(gpp2,1);
  handsomeTG1(gpbpb1,2);
  handsomeTG1(gpbpb2,2);
  gpp2->SetMarkerStyle(25);
  gpbpb2->SetMarkerStyle(25);

  gpp1->GetFunction("f1")->SetBit(TF1::kNotDraw);
  gpp2->GetFunction("f1")->SetBit(TF1::kNotDraw);
  gpbpb1->GetFunction("f1")->SetBit(TF1::kNotDraw);
  gpbpb2->GetFunction("f1")->SetBit(TF1::kNotDraw);

  gpp1->Draw("same p");
  gpp2->Draw("same p");
  gpbpb1->Draw("same p");
  gpbpb2->Draw("same p");

  ATLASLabel(0.2,0.88,"Internal",0.05,0.16);

  TLegend *leg1 = new TLegend(0.2,0.6435294,0.7397321,0.9082353,NULL,"brNDC");
  easyLeg(leg1,"",0.04);
  leg1->AddEntry(gpp1,"pp, 0.06 < m/p_{T} < 0.1","pl");
  leg1->AddEntry(gpp2,"pp, 0.15 < m/p_{T}","pl");
  leg1->AddEntry(gpbpb1,"PbPb, 0.06 < m/p_{T} < 0.1","pl");
  leg1->AddEntry(gpbpb2,"PbPb, 0.15 < m/p_{T}","pl");
  leg1->Draw();

}
