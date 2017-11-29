#include "commonUtility.h"
#include <vector>

struct trkSpectra {
  TH1D* pre;
  TH1D* post;
  TH1D* gen;
} ; 

trkSpectra getSpectraOfTracks ( int centBin = 0,
			  TString fname = "ntuples/jetSubstructure_himix_r1.0_cs_ptCut1.0_sdPtCut1.0_jz3_v3.1.root"
			  ) {
  
  trkSpectra ret; 
  TH1::SetDefaultSumw2();
  TFile* inf = new TFile(fname.Data());
  TH2D* hTrkPtEta_preCS;
  TH2D* hTrkPtEta_postCS;
  TH2D* hTrkPtEta_gen;
  hTrkPtEta_preCS = (TH2D*)inf->Get(Form("hTrkPtEta_preCS_cent%d",centBin));
  hTrkPtEta_postCS = (TH2D*)inf->Get(Form("hTrkPtEta_postCS_cent%d",centBin));
  hTrkPtEta_gen = (TH2D*)inf->Get(Form("hTrkPtEta_genMatch_cent%d",centBin));

  TH1D* htemp = (TH1D*)hTrkPtEta_preCS->ProjectionY("hTrkPtEta_preCS_centProjected");
  int binLow = htemp->FindBin( -2.39999);
  int binHigh = htemp->FindBin( 2.3999999);
  

  ret.pre = (TH1D*)hTrkPtEta_preCS->ProjectionX("hPt_pre",binLow,binHigh);
  ret.post = (TH1D*)hTrkPtEta_postCS->ProjectionX("hPt_post",binLow,binHigh);
  ret.gen = (TH1D*)hTrkPtEta_gen->ProjectionX("hPt_gen",binLow,binHigh);
  handsomeTH1(ret.pre,1);
  handsomeTH1(ret.post,2);
  handsomeTH1(ret.gen,4);

  return ret; 
  /*
  TCanvas* c1 = new TCanvas("c1","",400,400);
  double integral = ret.pre->Integral();
  ret.pre->Scale(1./integral);
  ret.post->Scale(1./integral);
  cleverRange(ret.pre,100,1.e-8);
  ret.pre->SetXTitle("p_{T} (GeV)");
  ret.pre->SetYTitle("Integrated by pre-CS entries");
  ret.pre->Draw("");
  ret.post->Draw("same");
  gPad->SetLogy();
  gPad->SetLogx();
  drawText("track |eta| < 2.4",0.4,0.65,1,20);
  if ( centBin ==0)  drawText("0-10%",0.4,0.8,1,20);
  if ( centBin ==1)  drawText("10-20%",0.4,0.8,1,20);
  if ( centBin ==2)  drawText("20-30%",0.4,0.8,1,20);
  if ( centBin ==3)  drawText("30-40%",0.4,0.8,1,20);
  if ( centBin ==4)  drawText("40-50%",0.4,0.8,1,20);
  if ( centBin ==5)  drawText("50-60%",0.4,0.8,1,20);
  if ( centBin ==6)  drawText("60-80%",0.4,0.8,1,20);
  c1->SaveAs(Form("trackSpectra_cent%d.gif",centBin));
  */
}
