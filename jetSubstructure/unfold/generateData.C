#include "../commonUtility.h"
#include "TRandom3.h"
#include "TCanvas.h"
void generateData(){

  TRandom *rand = new TRandom();
  rand->SetSeed(0);
  double norm = 1;
  double n = 2.;
  double res = 2.0;

  TF1 *ftrue = new TF1("ftrue","[0]/pow(x,[1])",1,1000);
  ftrue->SetParameters(norm,n);

  //  TH1D *hcurve = new TH1D("hcurve","hcurve",1000,0,100);
  //  for ( int i =1 ; i<=hcurve->GetNbinsX() ; i++) {
  //    hcurve->SetBinContent( i , ftrue->Eval( hcurve->GetBinCenter(i)) );
  //  }
  TH1D *htrue = new TH1D("htrue","htrue",150,-500,1000);
  TH1D *hmeas = new TH1D("hmeas","hmeas",150,-500,1000);
  TH2D *hres = new TH2D("hres","hres",150,-500,1000,150,-500,1000);

  //double res = 1.0;  // originially it was 0.5
  double min_true = 0;
  double min_reco = 10;
  

  //  TF1* f = new TF1("fitFunc","[0]*x^[1]",5,1000);
  //  f->SetParameters(3.16538e-01, -5.20299e-01);
  
  //  TFile* fr = new TFile("reweight_from_n2res1_to_n2.5res1.root");
  //  TFile* fr = new TFile("reweight_from_n2res0.5_to_n2.5res0.5.root");
  TFile* fr = new TFile("reweight_from_n2.0_res2.0_ton2.0_res2.5.root");
  //TFile* fr = new TFile("out_n2.000000_res0.500000_reweightedBy_reweight_from_n2res0.5_to_n2.5res0.5.root");
  TH1D* hr = (TH1D*)fr->Get("hr");

  int npts = 100000000;
  cout << "generating " << npts << " points" << endl;
  for(int i=0; i<npts; i++){
    double val = ftrue->GetRandom();
    //    double val = hcurve->GetRandom();
    //    if ( val>1 ) cout << "val = " << val << endl;
    double smeared = val*rand->Gaus(1,res);

    
    double reFac=  1; 
    //      double reFac = f->Eval( smeared ) ;
    //    double reFac = hr->GetBinContent( hr->FindBin(smeared));

    //    double reFac = hr->GetBinContent( hr->FindBin(smeared));
    //    double reFac = hr->GetBinContent( hr->FindBin(val));
    
    htrue->Fill(val,reFac);
    
    if(val > min_true && smeared > min_reco){
      hres->Fill(smeared,val, reFac);
      hmeas->Fill(smeared, reFac);
    }
    
  }
  
  TCanvas *c2 = new TCanvas("c2","c2",1000,300);
  c2->Divide(3,1);
  c2->cd(1);
  htrue->Draw();
  ftrue->SetLineColor(2);
  ftrue->Draw("same");
  gPad->SetLogy();
  c2->cd(2);
  hmeas->Draw();
  c2->cd(3);
  hres->Draw("colz");
  TFile *fout = new TFile(Form("out_n%.1f_res%.1f.root",(float)n,(float)res),"RECREATE");
  //  TFile *fout = new TFile(Form("out_n%f_res%f_reweighted_by_from_n2res1_to_n2.5res1_FIT.root",(float)n,(float)res),"RECREATE");
  //  TFile *fout = new TFile(Form("out_n%f_res%f_reweighted_by_from_n2res1_to_n2.5res1.root",(float)n,(float)res),"RECREATE");
  htrue->Write();
  hmeas->Write();
  hres->Write();
}
