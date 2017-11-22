#include "commonUtility.h"
#include "TCut.h"
void drawZgChZg() { 
  TH1::SetDefaultSumw2();
  TFile* f = new TFile("ntuples/jetSubstructure_pythia_r1.0_cs_ptCut1.0_sdPtCut1.0_jz3_v3.1.root");
  TTree* tr = (TTree*)f->Get("tr");
  TH2D* h2[10]; // in dr bins 
  TH1D* h1d[10]; // in dr bins 
  TH2D* hRes2d[10]; // in dr bins 
  TH1D* hRes1d[10]; // in dr bins 

  const int nDrBins  = 5;
  double drBin[nDrBins+1] = {0,0.1,0.2,0.4,0.6,1.0};
  TString ptCut = "(genPt>150 && genPt<250)";

  for ( int i= 1;  i<=nDrBins ; i++) {
    TString drCut = Form("genTheta>%f && genTheta<=%f",(float)drBin[i-1],(float)drBin[i]);
    TString drCutCh = Form("genChTheta>%f && genChTheta<=%f",(float)drBin[i-1],(float)drBin[i]);
    int nXbin = 20;
    int nYbin = 50;
    h2[i] = new TH2D(Form("drBin_%d",i), "",nXbin,0,0.6,nYbin,-.5,.5);
    hRes2d[i] = new TH2D(Form("hRes2d_%d",i), "",nXbin,0,0.6,nYbin,-.5,.5);
    TString finalCut = "(  ("+ptCut+")&&("+drCut+") ) * weight";
    TString finalCutCh = "(  ("+ptCut+")&&("+drCutCh+") ) * weight";
    tr->Draw(Form("genChZg-genZg:genZg >> %s", h2[i]->GetName()) , finalCut.Data() );
    tr->Draw(Form("(chZg-genChZg):genChZg >> %s", hRes2d[i]->GetName()) , finalCutCh.Data() );
    h1d[i] = (TH1D*)h2[i]->ProjectionY(Form("h1d_%d",i),1,nXbin);
    hRes1d[i] = (TH1D*)hRes2d[i]->ProjectionY(Form("hRes1d_%d",i),1,nXbin);
  }
  TCanvas* c1 = new TCanvas("c10","",1200,400);
  c1->Divide(nDrBins,1);
  for ( int i= 1;  i<=nDrBins ; i++) {
    c1->cd(i);
    h2[i]->SetXTitle("z_{g}");
    h2[i]->SetYTitle("z_{g}^{ch} - z_{g}");
    h2[i]->Draw("colz");
    if ( i==1)  drawText("Powheg*PYTHIA",0.3,0.9,2);
    drawText(Form("%.1f < #theta < %.1f",(float)drBin[i-1],(float)drBin[i]), 0.45,0.8);
  }  
  c1->SaveAs("zg_full_vs_charge_in_truth.png");

  TCanvas* c2 = new TCanvas("c2","",1200,400);
  c2->Divide(nDrBins,1);
  for ( int i= 1;  i<=nDrBins ; i++) {
    c2->cd(i);
    hRes2d[i]->SetXTitle("Truth z_{g}^{ch}");
    hRes2d[i]->SetYTitle("Reco - Truth");
    hRes2d[i]->Draw("colz");
    if ( i==1)  drawText("Powheg*PYTHIA",0.3,0.9,2);
    drawText(Form("%.1f < #theta < %.1f",(float)drBin[i-1],(float)drBin[i]), 0.45,0.8);
  }  
  c2->SaveAs("zg_ch_reco_vs_truth.png");



  TCanvas* c3 = new TCanvas("c3","",600,600);
  for ( int i= 1;  i<=nDrBins ; i++) {
    h1d[i]->SetXTitle("Charged Z_{g} - FullParticle Z_{g}");
    h1d[i]->SetYTitle("Normalized Entries");
    scaleInt(h1d[i]);
    handsomeTH1(h1d[i],40+i);
    h1d[i]->SetAxisRange(5e-4,2,"Y");
    if ( i==1)       h1d[i]->Draw();
    else             h1d[i]->Draw("same");
  }

  TLegend *leg2 = new TLegend(0.1844532,0.6568421,0.770751,0.9010526,NULL,"brNDC");
  easyLeg(leg2,"PYTHIA*Powheg");
  for ( int i= 1;  i<=nDrBins ; i++) {
    leg2->AddEntry(h1d[i],Form("%.1f < #theta < %.1f",(float)drBin[i-1],(float)drBin[i]));
  }
  leg2->Draw();
  gPad->SetLogy();
  c3->SaveAs("zg_full_vs_charge_in_truth_1d.png");

  TCanvas* c4 = new TCanvas("c4","",600,600);
  for ( int i= 1;  i<=nDrBins ; i++) {
    hRes1d[i]->SetXTitle("(Reco - Truth) of z_{g}^{ch}");
    hRes1d[i]->SetYTitle("Normalized Entries");
    scaleInt(hRes1d[i]);
    handsomeTH1(hRes1d[i],40+i);
    hRes1d[i]->SetAxisRange(5e-4,2,"Y");
    if ( i==1)       hRes1d[i]->Draw();
    else             hRes1d[i]->Draw("same");
  }
  
  leg2->Draw();
  gPad->SetLogy();
  c4->SaveAs("zg_ch_reco_vs_truth_1d.png");

}
