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
#include <TCut.h>
double statUsed = 0001;

int lowPtBin = 1;  int highPtBin = 13;

int nPtPannels = highPtBin-lowPtBin+1;


double findPeakLandau(TF1* f) {
  double v1 = f->GetParameter(1);
  double v2 = f->GetParameter(2);
  // Peak = ([1] - 0.22278)
  // https://root.cern.ch/root/html528/TMath.html#TMath:Landau
  return (v1-0.22278);
}

void compareEmHIjets() { 
  TH1::SetDefaultSumw2();

  TFile* fmc2 = new TFile("../ntuples/JZ2.root");
  TTree* mc2 = (TTree*)fmc2->Get("tree_performance");
  TFile* fmc3 = new TFile("../ntuples/JZ3.root");
  TTree* mc3 = (TTree*)fmc3->Get("tree_performance");

  TFile* fdata = new TFile("../ntuples/data.root");
  TTree* data = (TTree*)fdata->Get("tree_performance");

  const int nXbins = 6;
  double xBin[nXbins+1] = {125.892,  158.488,  199.525,  251.186,  316.224,  398.101, 500};
  //  const int nXbins = 1;
  //  double xBin[nXbins+1] = {125.892,  158.488};
  
  TH1D* mcDist[20];
  TH1D* dataDist[20];
  
  TH1D* hmcSigma = new TH1D("hmcSigma",";p_{T} (GeV);#sigma of distribution",nXbins,xBin);
  TH1D* hdataSigma = (TH1D*)hmcSigma->Clone("hdataSigma");
  
  TCut generalCut = "abs(jet_eta) < 2.1";
  
  int nmc2 = mc2->GetEntries();
  float jz2Scale = perEvtWgtJZ2;
  int nmc3 = mc3->GetEntries();
  float jz3Scale = perEvtWgtJZ3;

  int ndata = data->GetEntries();
  for ( int ix = 1 ; ix<= nXbins ;ix++) { 
    int nRbins = 35;
    mcDist[ix] = new TH1D(Form("mcDist_%d",ix),";m^{HI}/m^{EM Topo};",nRbins,0,3);
    dataDist[ix] = new TH1D(Form("dataDist_%d",ix),";m^{HI}/m^{EM Topo};",nRbins,0,3);
    
    TCut ptCut = Form( "(jet_pt_xcalib >= %f)  && (jet_pt_xcalib < %f)", float(xBin[ix-1]), float(xBin[ix]) );
    
    mc2->Draw(Form("jet_m_EM/test_jet_m_EM >> %s", mcDist[ix]->GetName() ),  Form("(%s)*(%s)*%f",generalCut.GetTitle(), ptCut.GetTitle(), jz2Scale),  "", nmc2*statUsed);
    mc3->Draw(Form("jet_m_EM/test_jet_m_EM >>+ %s", mcDist[ix]->GetName() ),  Form("(%s)*(%s)*%f",generalCut.GetTitle(), ptCut.GetTitle(), jz3Scale),  "", nmc3*statUsed);

    data->Draw(Form("jet_m_EM/test_jet_m_EM>>%s",dataDist[ix]->GetName() ),generalCut && ptCut, "", ndata*statUsed);
  }
  TCanvas* c1 = new TCanvas("c1","",1200,800);
  c1->Divide(3,2);
  for ( int ix = 1 ; ix<= nXbins ; ix++) {
    c1->cd(ix);
    handsomeTH1(mcDist[ix],1);
    handsomeTH1(dataDist[ix],2);
    scaleInt(mcDist[ix]);
    scaleInt(dataDist[ix]);
    
    cleverRange(mcDist[ix],2);
    mcDist[ix]->Draw();
    dataDist[ix]->Draw("same");

    TF1 *f1mc = new TF1(Form("fitH1mc_ix%d",ix),"[0]*TMath::Landau(x,[1],[2])",0,3);
    f1mc->SetParameter(0,2);
    f1mc->SetParameter(1,2.4);
    f1mc->SetParameter(2,0.6);

    TF1 *f1data = new TF1(Form("fitH1data_ix%d",ix),"[0]*TMath::Landau(x,[1],[2])",0,3);
    f1data->SetParameter(0,2);
    f1data->SetParameter(1,2.4);
    f1data->SetParameter(2,0.6);
    
    if ( ix == 1) { 
      mcDist[ix]->Fit(f1mc->GetName(),"","",.8,1.5);
      dataDist[ix]->Fit(f1data->GetName(),"","",.8,1.5);
    }
    else {
      mcDist[ix]->Fit(f1mc->GetName(),"","",.8,2);
      dataDist[ix]->Fit(f1data->GetName(),"","",.8,2);
    }
    mcDist[ix]->GetFunction(f1mc->GetName())->SetLineColor(1);
    dataDist[ix]->GetFunction(f1data->GetName())->SetLineColor(2);

    drawBin(xBin,ix,"GeV",0.2,0.85,1,20);
    double mcSigma = f1mc->GetParameter(2) / f1mc->GetParameter(1);
    double mcSigmaErr = f1mc->GetParError(2);
    double dataSigma = f1data->GetParameter(2) / f1data->GetParameter(1);
    double dataSigmaErr = f1data->GetParError(2);
    
    hmcSigma->SetBinContent(ix, mcSigma);
    hmcSigma->SetBinError(ix, mcSigmaErr);
    hdataSigma->SetBinContent(ix, dataSigma);
    hdataSigma->SetBinError(ix, dataSigmaErr);
  }

  TCanvas* c2 = new TCanvas("c2","", 400,400);
  handsomeTH1(hmcSigma,1);
  handsomeTH1(hdataSigma,1);
  hdataSigma->Divide(hmcSigma);
  hdataSigma->SetAxisRange(0.5,1.5,"Y");
  hdataSigma->Draw();
  
  TF1* f1 = new TF1("f1","1 + 0.06 + 0.06*((x-300)/150)^2",125,500);
  TF1* f2 = new TF1("f2","1 - 0.06 - 0.06*((x-300)/150)^2",125,500);
  f1->SetLineColor(4);
  f2->SetLineColor(4);
  f1->Draw("same");
  f2->Draw("same");
}
