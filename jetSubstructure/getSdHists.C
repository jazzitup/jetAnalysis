#include "commonUtility.h"
#include <vector>

struct sdVariable {
  TH1D* hEffDphi;
  TH1D* hEffDrap;
} ;


sdVariable getSdHists (TString prefix = "pbpb",
		       TString fname = "ntuples/jetSubstructure_output_DAOD_HION9.11573635._000058.pool.root.1",
		       int centBin = 0,
		       TString theCut = "genPt>150 && genPt<250") {
  
  TFile* inf = new TFile(fname.Data());
  TTree* tree = (TTree*) inf->Get("tr");
  TH2D* h_allGen_pt_dphi_cent;
  TH2D* h_trkGen_pt_dphi_cent;
  TH2D* h_allGen_pt_drap_cent;
  TH2D* h_trkGen_pt_drap_cent;
  
  TH1D* hden_dphi_cent;
  TH1D* heff_dphi_cent;
  TH1D* hden_drap_cent;
  TH1D* heff_drap_cent;

  TH1D* hpt ; 
  h_allGen_pt_dphi_cent = (TH2D*)inf->Get(Form("h_allGen_pt_dphi_cent%d",centBin));
  h_trkGen_pt_dphi_cent = (TH2D*)inf->Get(Form("h_trkGen_pt_dphi_cent%d",centBin));
  h_allGen_pt_drap_cent = (TH2D*)inf->Get(Form("h_allGen_pt_drap_cent%d",centBin));
  h_trkGen_pt_drap_cent = (TH2D*)inf->Get(Form("h_trkGen_pt_drap_cent%d",centBin));
    
  hpt = (TH1D*)h_allGen_pt_dphi_cent->ProjectionX();
  int bin150 = hpt->FindBin(150.0001);
  int bin400 = hpt->FindBin(399.9999);
  hden_dphi_cent = h_allGen_pt_dphi_cent->ProjectionY(Form("hden_dphi_cent%d_%s",centBin,prefix.Data()), bin150, bin400);
  heff_dphi_cent = h_trkGen_pt_dphi_cent->ProjectionY(Form("heff_dphi_cent%d_%s",centBin,prefix.Data()), bin150, bin400);
  hden_drap_cent = h_allGen_pt_drap_cent->ProjectionY(Form("hden_drap_cent%d_%s",centBin,prefix.Data()), bin150, bin400);
  heff_drap_cent = h_trkGen_pt_drap_cent->ProjectionY(Form("heff_drap_cent%d_%s",centBin,prefix.Data()), bin150, bin400);
  
  heff_dphi_cent->Divide(hden_dphi_cent);
  heff_drap_cent->Divide(hden_drap_cent);

  sdVariable ret;

  heff_dphi_cent->Draw("hist");
  heff_drap_cent->Draw("same e");
  
  ret.hEffDphi = heff_dphi_cent ; 
  ret.hEffDrap = heff_drap_cent ; 
  return ret;
}
