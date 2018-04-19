#ifndef GETSDHISTS_H
#define GETSDHISTS_H

#include "commonUtility.h"
#include <vector>

struct sdVariable {
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
  TH1D* hGenMass;
  TH1D* hGenRelMass;
  TH1D* hRecoMass;
  TH1D* hRecoCham;
  TH1D* hRecoRelCham;
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

  TH1D* _hGenMass  = new TH1D(Form("_hGenMass_cent%d_%s",centBin,prefix.Data()), ";Mass GeV;",40,0,150);
  TH1D* _hRecoMass = (TH1D*)_hGenMass->Clone(Form("_hRecoMass_cent%d_%s",centBin,prefix.Data()));
  TH1D* _hRecoCham = (TH1D*)_hGenMass->Clone(Form("_hRecoCham_cent%d_%s",centBin,prefix.Data()));
  TH1D* _hGenRelMass  = new TH1D(Form("_hGenRelMass_cent%d_%s",centBin,prefix.Data()), ";Mass/p_{T} GeV;",40,0,0.7);
  TH1D* _hRecoRelCham = (TH1D*)_hGenRelMass->Clone(Form("_hRecoRelCham_cent%d_%s",centBin,prefix.Data()));
  
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

  tree->Draw( Form("genMass>>%s",     _hGenMass->GetName()), cutWeightGenTheta, "",totalEvents );
  tree->Draw( Form("mass>>%s",        _hRecoMass->GetName()), cutWeightGenTheta, "",totalEvents );
  tree->Draw( Form("genMass/genPt>>%s",     _hGenRelMass->GetName()), cutWeightGenTheta, "",totalEvents );
  tree->Draw( Form("chMass*pt/chPt>>%s",     _hRecoCham->GetName()), cutWeightGenTheta, "",totalEvents );
  tree->Draw( Form("chMass/chPt>>%s",     _hRecoRelCham->GetName()), cutWeightGenTheta, "",totalEvents );




  sdVariable ret;
  //  TCanvas* c0 = new TCanvas("c0","",500,500);
  //  _hRecoTheta->Draw();
  
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

  ret.hGenMass = _hGenMass;
  ret.hGenRelMass = _hGenRelMass;
  ret.hRecoMass = _hRecoMass;
  ret.hRecoCham = _hRecoCham;
  ret.hRecoRelCham = _hRecoRelCham;
  
  return ret;
}




#endif
