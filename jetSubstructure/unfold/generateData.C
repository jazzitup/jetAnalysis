//#include "../commonUtility.h"
#include "TRandom3.h"
void generateData(){

  TRandom *rand = new TRandom2();
  rand->SetSeed(0);
  double norm = 1;
  double n = 2;
  TF1 *ftrue = new TF1("ftrue","[0]/pow(x,[1])",0,100);
  ftrue->SetParameters(norm,n);

  TH1D *hcurve = new TH1D("hcurve","hcurve",1000,0,100);
  for ( int i =1 ; i<=hcurve->GetNbinsX() ; i++) {
    hcurve->SetBinContent( i , ftrue->Eval( hcurve->GetBinCenter(i)) );
  }
  TH1D *htrue = new TH1D("htrue","htrue",100,0,100);
  TH1D *hmeas = new TH1D("hmeas","hmeas",100,0,100);
  TH2D *hres = new TH2D("hres","hres",100,0,100,100,0,100);

  double res = 0.5;
  double min_true = 0;
  double min_reco = 10;
  
  
  TFile* fr = new TFile("reweight.root");
  TH1D* hr = (TH1D*)fr->Get("hr");

  int npts = 10000000;
  cout << "generating " << npts << " points" << endl;
  for(int i=0; i<npts; i++){
    //    double val = ftrue->GetRandom();
    double val = hcurve->GetRandom();
    //    if ( val>1 ) cout << "val = " << val << endl;
    htrue->Fill(val);
    double smeared = val*rand->Gaus(1,res);
    
    if(val > min_true && smeared > min_reco){
      double reFac = hr->GetBinContent( hr->FindBin(smeared));
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
  c2->cd(2);
  hmeas->Draw();
  c2->cd(3);
  hres->Draw("colz");
  TFile *fout = new TFile("out.root","RECREATE");
  htrue->Write();
  hmeas->Write();
  hres->Write();
}
