#include "commonUtility.h"
#include <vector>

struct sdVariable {
  TH1D* hEffDphi;
  TH1D* hEffDrap;
  TH1D* hGenTheta;
  TH1D* hGenChTheta;
  TH1D* hRecoTheta;
  TH1D* hRecoChTheta;
} ;

sdVariable getSdHists (TString prefix = "pbpb",
		       TString fname = "ntuples/jetSubstructure_output_DAOD_HION9.11573635._000058.pool.root.1",
		       int centBin = 0,
		       TString theCut = "genPt>150 && genPt<250") {
  
  TH1::SetDefaultSumw2();
  TFile* inf = new TFile(fname.Data());
  TTree* tree = (TTree*) inf->Get("tr");
  TH2D* h_allGen_pt_dphi_cent;
  TH2D* h_trkGen_pt_dphi_cent;
  TH2D* h_allGen_pt_drap_cent;
  TH2D* h_trkGen_pt_drap_cent;
  
  TH1D* hpt ; 
  h_allGen_pt_dphi_cent = (TH2D*)inf->Get(Form("h_allGen_pt_dphi_cent%d",centBin));
  h_trkGen_pt_dphi_cent = (TH2D*)inf->Get(Form("h_trkGen_pt_dphi_cent%d",centBin));
  h_allGen_pt_drap_cent = (TH2D*)inf->Get(Form("h_allGen_pt_drap_cent%d",centBin));
  h_trkGen_pt_drap_cent = (TH2D*)inf->Get(Form("h_trkGen_pt_drap_cent%d",centBin));
    
  hpt = (TH1D*)h_allGen_pt_dphi_cent->ProjectionX();
  int bin150 = hpt->FindBin(150.0001);
  int bin400 = hpt->FindBin(399.9999);
  TH1D* hden_dphi_cent = h_allGen_pt_dphi_cent->ProjectionY(Form("hden_dphi_cent%d_%s",centBin,prefix.Data()), bin150, bin400);
  TH1D* heff_dphi_cent = h_trkGen_pt_dphi_cent->ProjectionY(Form("heff_dphi_cent%d_%s",centBin,prefix.Data()), bin150, bin400);
  TH1D* hden_drap_cent = h_allGen_pt_drap_cent->ProjectionY(Form("hden_drap_cent%d_%s",centBin,prefix.Data()), bin150, bin400);
  TH1D* heff_drap_cent = h_trkGen_pt_drap_cent->ProjectionY(Form("heff_drap_cent%d_%s",centBin,prefix.Data()), bin150, bin400);
  
  heff_dphi_cent->Divide(hden_dphi_cent);
  heff_drap_cent->Divide(hden_drap_cent);

  // SD variables
  TString cutWeight = Form("((cent==%d)&&(%s))*weight", centBin, theCut.Data() );
  TH1D* _hGenTheta = new TH1D(Form("_hGenTheta_cent%d_%s",centBin,prefix.Data()), "; #theta;",20,0,1);
  TH1D* _hGenChTheta = (TH1D*)_hGenTheta->Clone(Form("_hGenChTheta_cent%d_%s",centBin,prefix.Data()));
  TH1D* _hRecoTheta = (TH1D*)_hGenTheta->Clone(Form("_hRecoTheta_cent%d_%s",centBin,prefix.Data()));
  TH1D* _hRecoChTheta = (TH1D*)_hGenTheta->Clone(Form("_hRecoChTheta_cent%d_%s",centBin,prefix.Data()));
  tree->Draw( Form("theta>>%s",     _hRecoTheta->GetName()), cutWeight );
  tree->Draw( Form("chTheta>>%s",   _hRecoChTheta->GetName()), cutWeight );
  tree->Draw( Form("genTheta>>%s",  _hGenTheta->GetName()), cutWeight );
  tree->Draw( Form("genChTheta>>%s",_hGenChTheta->GetName()), cutWeight );
  sdVariable ret;
  //  TCanvas* c0 = new TCanvas("c0","",500,500);
  //  _hRecoTheta->Draw();
  
  ret.hEffDphi = heff_dphi_cent ; 
  ret.hEffDrap = heff_drap_cent ; 
  ret.hGenTheta = _hGenTheta;
  ret.hGenChTheta = _hGenChTheta;
  ret.hRecoTheta = _hRecoTheta;
  ret.hRecoChTheta = _hRecoChTheta;

  return ret;
}
