#include "commonUtility.h"
#include <vector>

void getEfficiency (TString prefix = "pbpb",
			  TString fname = "ntuples/jetSubstructure_himix_r1.0_cs_ptCut1_jz3_v3.1.root",
			  int centBin = 0
			  ) {
  
  TH1::SetDefaultSumw2();
  TFile* inf = new TFile(fname.Data());
  TH3D* h_allGen_pt_dphi_cent;
  TH3D* h_trkGen_pt_dphi_cent;
  TH3D* h_allGen_pt_drap_cent;
  TH3D* h_trkGen_pt_drap_cent;
  
  h_allGen_pt_dphi_cent = (TH3D*)inf->Get(Form("h_allGen_dphi_cent%d",centBin));
  h_trkGen_pt_dphi_cent = (TH3D*)inf->Get(Form("h_trkGen_dphi_cent%d",centBin));
  h_allGen_pt_drap_cent = (TH3D*)inf->Get(Form("h_allGen_drap_cent%d",centBin));
  h_trkGen_pt_drap_cent = (TH3D*)inf->Get(Form("h_trkGen_drap_cent%d",centBin));

  TH1D* hjetpt = (TH1D*)h_allGen_pt_dphi_cent->ProjectionX();
  int bin150 = hjetpt->FindBin(150.0001);
  int bin250 = hjetpt->FindBin(249.9999);

  TH1D* hDenDphi[20];
  TH1D* hDenDrap[20];
  TH1D* hEffDphi[20];
  TH1D* hEffDrap[20];

  TH1D* htrkpt = (TH1D*)h_allGen_pt_dphi_cent->ProjectionY();
  int nTrkPt = htrkpt->GetNbinsX();
  for ( int i= 1 ; i<= nTrkPt ; i++) { 
    hDenDrap[i] = h_allGen_pt_drap_cent->ProjectionZ(Form("hDenDrap_trkPt%d_cent%d",i,centBin), bin150, bin250, i, i);
    hDenDphi[i] = h_allGen_pt_dphi_cent->ProjectionZ(Form("hDenDphi_trkPt%d_cent%d",i,centBin), bin150, bin250, i, i);
    hEffDrap[i] = h_trkGen_pt_drap_cent->ProjectionZ(Form("hEffDrap_trkPt%d_cent%d",i,centBin), bin150, bin250, i, i);
    hEffDphi[i] = h_trkGen_pt_dphi_cent->ProjectionZ(Form("hEffDphi_trkPt%d_cent%d",i,centBin), bin150, bin250, i, i);

    hEffDrap[i]->Divide(hDenDrap[i]);
    hEffDphi[i]->Divide(hDenDphi[i]);
  }

  const int nTrkPtBinForEff = 15;
  double trkPtBinForEff[nTrkPtBinForEff+1] = {0,0.5,0.7,0.8,0.9,1,1.5,2,4,6,8,14,20,40,100,200};

  TCanvas* c1 = new TCanvas("c1","",1200,600);
  c1->Divide(6,2);
  for ( int i=1; i<= 6; i++) {
    c1->cd(i);
    handsomeTH1(hEffDrap[i+9],1);
    hEffDrap[i+9]->SetAxisRange(0,1.3,"Y");
    hEffDrap[i+9]->Draw();
    drawText(Form("%.1f < p_{T} < %.1f GeV/c",(float)trkPtBinForEff[i+9 - 1], (float)trkPtBinForEff[i+9]),0.25,0.8,1,15);
    c1->cd(i+ 6);
    handsomeTH1(hEffDphi[i+9],1);
    hEffDphi[i+9]->SetAxisRange(0,1.3,"Y");
    hEffDphi[i+9]->Draw();
  }
}
