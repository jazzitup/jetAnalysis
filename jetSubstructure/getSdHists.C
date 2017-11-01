#include "commonUtility.h"
#include <vector>

struct sdVariable {
  TH1D* hEffDphi;
  TH1D* hEffDrap;
  TH1D* hGenTheta;
  TH1D* hGenChTheta;
  TH1D* hRecoTheta;
  TH1D* hRecoChTheta;
  TH1D* hRecoZg;
  TH1D* hGenZg;
  TH1D* hRecoChZg;
  TH1D* hGenChZg;
  TH1D* hRecoSdM;
  TH1D* hGenSdM;
  TH1D* hRecoChSdM;
  TH1D* hGenChSdM;

} ;

sdVariable getSdHists (TString prefix = "pbpb",
		       TString fname = "ntuples/jetSubstructure_output_DAOD_HION9.11573635._000058.pool.root.1",
		       int centBin = 0,
		       TString theCut = "genPt>250 && genPt<400",
		       float thetaCut = 0.1,
		       int totalEvents=-1
		       ) {
  
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
  TString cutWeightRecoTheta = Form("((cent==%d)&&(%s)&&(theta>%f))*weight", centBin, theCut.Data(), (float)thetaCut );
  TString cutWeightGenTheta  = Form("((cent==%d)&&(%s)&&(genTheta>%f))*weight", centBin, theCut.Data(), (float)thetaCut );
  TString cutWeightRecoChTheta  = Form("((cent==%d)&&(%s)&&(chTheta>%f))*weight", centBin, theCut.Data(), (float)thetaCut );
  TString cutWeightGenChTheta  = Form("((cent==%d)&&(%s)&&(genChTheta>%f))*weight", centBin, theCut.Data(), (float)thetaCut );

  const int nThetaBins = 10;
  double thetaBin[nThetaBins+1] = {0,0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.4, 0.5, 0.7,1.0};
  TH1D* _hGenTheta = new TH1D(Form("_hGenTheta_cent%d_%s",centBin,prefix.Data()), "; #theta;",nThetaBins, thetaBin);
  TH1D* _hGenChTheta = (TH1D*)_hGenTheta->Clone(Form("_hGenChTheta_cent%d_%s",centBin,prefix.Data()));
  TH1D* _hRecoTheta = (TH1D*)_hGenTheta->Clone(Form("_hRecoTheta_cent%d_%s",centBin,prefix.Data()));
  TH1D* _hRecoChTheta = (TH1D*)_hGenTheta->Clone(Form("_hRecoChTheta_cent%d_%s",centBin,prefix.Data()));
  
  TH1D* _hRecoChZg = new TH1D(Form("_hRecoChZg_cent%d_%s",centBin,prefix.Data()), "; z_{g};",12,0,0.6);
  TH1D* _hGenChZg = (TH1D*)_hRecoChZg->Clone(Form("_hGenChZg_cent%d_%s",centBin,prefix.Data()));
  TH1D* _hGenZg = (TH1D*)_hRecoChZg->Clone(Form("_hGenZg_cent%d_%s",centBin,prefix.Data()));
  TH1D* _hRecoZg = (TH1D*)_hRecoChZg->Clone(Form("_hRecoZg_cent%d_%s",centBin,prefix.Data()));
  
  TH1D* _hRecoSdM = new TH1D(Form("_hRecoSdM_cent%d_%s",centBin,prefix.Data()), ";Mass;",10,0,100);
  TH1D* _hGenSdM = (TH1D*)_hRecoSdM->Clone(Form("_hGenSdM_cent%d_%s",centBin,prefix.Data()) );
  TH1D* _hRecoChSdM = (TH1D*)_hRecoSdM->Clone(Form("_hRecoChSdM_cent%d_%s",centBin,prefix.Data()) );
  TH1D* _hGenChSdM = (TH1D*)_hGenSdM->Clone(Form("_hGenChSdM_cent%d_%s",centBin,prefix.Data()) );
  
  tree->Draw( Form("theta>>%s",     _hRecoTheta->GetName()), cutWeight ,"", totalEvents);
  tree->Draw( Form("chTheta>>%s",   _hRecoChTheta->GetName()), cutWeight,"", totalEvents );
  tree->Draw( Form("genTheta>>%s",  _hGenTheta->GetName()), cutWeight,"", totalEvents );
  tree->Draw( Form("genChTheta>>%s",_hGenChTheta->GetName()), cutWeight, "",totalEvents );

  tree->Draw( Form("zg>>%s",     _hRecoZg->GetName()), cutWeightRecoTheta, "",totalEvents );
  tree->Draw( Form("genZg>>%s",     _hGenZg->GetName()), cutWeightGenTheta, "",totalEvents );
  tree->Draw( Form("chZg>>%s",     _hRecoChZg->GetName()), cutWeightRecoChTheta, "",totalEvents );
  tree->Draw( Form("genChZg>>%s",     _hGenChZg->GetName()), cutWeightGenChTheta, "",totalEvents );

  tree->Draw( Form("sdMass>>%s",     _hRecoSdM->GetName()), cutWeightRecoTheta, "",totalEvents );
  tree->Draw( Form("genSdMass>>%s",  _hGenSdM->GetName()), cutWeightGenTheta, "",totalEvents );
  tree->Draw( Form("chSdMass>>%s",   _hRecoChSdM->GetName()), cutWeightRecoChTheta, "",totalEvents );
  tree->Draw( Form("genChSdMass>>%s",_hGenChSdM->GetName()), cutWeightGenChTheta, "",totalEvents );

  sdVariable ret;
  //  TCanvas* c0 = new TCanvas("c0","",500,500);
  //  _hRecoTheta->Draw();
  
  ret.hEffDphi = heff_dphi_cent ; 
  ret.hEffDrap = heff_drap_cent ; 
  ret.hGenTheta = _hGenTheta;
  ret.hGenChTheta = _hGenChTheta;
  ret.hRecoTheta = _hRecoTheta;
  ret.hRecoChTheta = _hRecoChTheta;
  ret.hRecoZg = _hRecoZg;
  ret.hRecoChZg = _hRecoChZg;
  ret.hGenZg = _hGenZg;
  ret.hGenChZg = _hGenChZg;

  ret.hRecoSdM = _hRecoSdM;
  ret.hGenSdM = _hGenSdM;
  ret.hRecoChSdM = _hRecoChSdM;
  ret.hGenChSdM = _hGenChSdM;


  return ret;
}
