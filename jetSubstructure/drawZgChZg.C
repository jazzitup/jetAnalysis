#include "commonUtility.h"
#include "TCut.h"
void drawZgChZg() { 
  TH1::SetDefaultSumw2();
  TFile* f = new TFile("ntuples/jetSubstructure_pythia_r1.0_cs_ptCut1.0_sdPtCut1.0_jz3_v3.1.root");
  TTree* tr = (TTree*)f->Get("tr");
  TH2D* h2[10]; // in dr bins 
  TH1D* h1d[10]; // in dr bins 
  TH1D* h1dzg[10]; // in zg bins 
  TH2D* hRes2d[10]; // in dr bins 
  TH1D* hRes1d[10]; // in dr bins 
  TH2D* hCorrZg2d[10]; // in dr bins 
  TH2D* hCorrDr2d;
  TH1D* hResDr1d;

  const int nDrBins  = 3;
  double drBin[nDrBins+1] = {0,0.2, .4,1.0};
  TString ptCut = "(genPt>150 && genPt<250)";

  hCorrDr2d = new TH2D("hRes2d",";#theta;#theta^{ch}",30,0,1.1,30,0,1.1);
  hResDr1d = new TH1D("hResDr1d",";#theta^{ch}-#theta;Entries",200,-1,1);
  TString zgCut = Form("genZg>0.1 && genChZg>0.1");
  TString finalCutForDr = "(  ("+ptCut+")&&("+zgCut+") ) * weight";
  tr->Draw(Form("genChTheta:genTheta >> %s", hCorrDr2d->GetName()) , finalCutForDr.Data() );
  tr->Draw(Form("genChTheta-genTheta >> %s", hResDr1d->GetName()) , finalCutForDr.Data() );
  
  for ( int i= 1;  i<=nDrBins ; i++) {
    TString drCut = Form("genTheta>%f && genTheta<=%f",(float)drBin[i-1],(float)drBin[i]);
    TString drCutCh = Form("genChTheta>%f && genChTheta<=%f",(float)drBin[i-1],(float)drBin[i]);
    int nXbin = 20;
    int nYbin = 50;
    h2[i] = new TH2D(Form("drBin_%d",i), "",nXbin,0,0.6,nYbin,-.5,.5);
    hRes2d[i] = new TH2D(Form("hRes2d_%d",i), "",nXbin,0,0.6,nYbin,-.5,.5);
    hCorrZg2d[i] = new TH2D(Form("hRes2d_%d",i), "",nXbin,0,0.6,nXbin,0,0.6);
    
    TString finalCut = "(  ("+ptCut+")&&("+drCut+") ) * weight";
    TString finalCutCh = "(  ("+ptCut+")&&("+drCutCh+") ) * weight";
    tr->Draw(Form("genChZg-genZg:genZg >> %s", h2[i]->GetName()) , finalCut.Data() );
    tr->Draw(Form("(chZg-genChZg):genChZg >> %s", hRes2d[i]->GetName()) , finalCutCh.Data() );
    tr->Draw(Form("genChZg:genZg >> %s", hCorrZg2d[i]->GetName()) , finalCut.Data() );
  
    h1d[i] = (TH1D*)h2[i]->ProjectionY(Form("h1d_%d",i),1,nXbin);
    hRes1d[i] = (TH1D*)hRes2d[i]->ProjectionY(Form("hRes1d_%d",i),1,nXbin);
  }
  
  
  

  
  TCanvas* c0 = new TCanvas("c00","",1200,500);
  //  makeMultiPanelCanvas(c0, nDrBins,1);
  c0->Divide(nDrBins,1);
  for ( int i= 1;  i<=nDrBins ; i++) {
    c0->cd(i);
    hCorrZg2d[i]->SetAxisRange(0.1,0.5,"X");
    hCorrZg2d[i]->SetAxisRange(0.1,0.6,"Y");
    hCorrZg2d[i]->SetXTitle("z_{g}");
    hCorrZg2d[i]->SetYTitle("z_{g}^{ch}");
    handsomeTH1(hCorrZg2d[i]);
    hCorrZg2d[i]->Draw("colz");
    if ( i==1)  drawText("Powheg*PYTHIA",0.3,0.9,2);
    drawText(Form("%.1f < #theta < %.1f",(float)drBin[i-1],(float)drBin[i]), 0.5,0.83,1,30);
  }  
  c0->SaveAs("full_Vs_ch_zg_in_truth.png");

  TCanvas* c0Dr = new TCanvas("c0Dr0","",1200,500);
  c0Dr->Divide(nDrBins,1);
  c0Dr->cd(1);
  hCorrDr2d->SetXTitle("#theta");
  hCorrDr2d->SetYTitle("#theta^{ch}");
  handsomeTH1(hCorrDr2d);
  hCorrDr2d->Draw("colz");
  drawText("Powheg*PYTHIA",0.3,0.9,2);
  c0Dr->cd(2);
  handsomeTH1(hResDr1d,1);
  scaleInt(hResDr1d);
  hResDr1d->Draw("hist");
  //  gPad->SetLogy();
  c0Dr->SaveAs("full_Vs_ch_theta_in_truth.png");
  
  cout << " width = " << hResDr1d->GetRMS() << endl;
  cout << " mean = " << hResDr1d->GetMean() << endl;
  
  TCanvas* c1 = new TCanvas("c10","",700,400);
  c1->Divide(nDrBins,1);
  for ( int i= 1;  i<=nDrBins ; i++) {
    c1->cd(i);
    h2[i]->SetXTitle("z_{g}");
    h2[i]->SetYTitle("z_{g}^{ch} - z_{g}");
    h2[i]->Draw("colz");
    if ( i==1)  drawText("Powheg*PYTHIA",0.3,0.9,2);
    drawText(Form("%.1f < #theta < %.1f",(float)drBin[i-1],(float)drBin[i]), 0.45,0.8);
  }  
  c1->SaveAs("resolution_full_Vs_ch_zg_in_truth.png");

  TCanvas* c2 = new TCanvas("c2","",700,400);
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



  TCanvas* c3 = new TCanvas("c3","",500,500);
  for ( int i= 1;  i<=nDrBins ; i++) {
    h1d[i]->SetXTitle("z_{g}^{ch} - z_{g}");
    h1d[i]->SetYTitle("Normalized Entries");
    scaleInt(h1d[i]);
    handsomeTH1(h1d[i],1);
    if ( i==1) handsomeTH1(h1d[i],1);
    if ( i==2) handsomeTH1(h1d[i],kMagenta);
    if ( i==3) handsomeTH1(h1d[i],kBlue);

    h1d[i]->SetAxisRange(9e-4,1.2,"Y");
    if ( i==1)       h1d[i]->Draw("hist");
    else             h1d[i]->Draw("same hist");
  }

  TLegend *leg2 = new TLegend(0.2008032,0.7178947,0.6807229,0.8968421,NULL,"brNDC");
  easyLeg(leg2,"PYTHIA*Powheg");
  for ( int i= 1;  i<=nDrBins ; i++) {
    leg2->AddEntry(h1d[i],Form("%.1f < #theta < %.1f",(float)drBin[i-1],(float)drBin[i]));
  }
  leg2->Draw();
  //  gPad->SetLogy();
  c3->SaveAs("zg_full_vs_charge_in_truth_1d.png");

  TCanvas* czg = new TCanvas("czg","",500,500);
  const int nZgBins  = 3;
  double zgBin[nZgBins+1] = {0.1,0.2,.3,0.5};
  for ( int i= 1;  i<=nZgBins ; i++) {
    h1dzg[i] = new TH1D(Form("h1dzg_%d",i),";z_{g}^{ch};Entries",20,0.1,0.5);
    TString zgCut = Form("theta>0.2 && zg>%f && zg<=%f",(float)zgBin[i-1],(float)zgBin[i]);
    TString finalCut = "(  ("+ptCut+")&&("+zgCut+") ) * weight";
    tr->Draw(Form("chZg>>%s",h1dzg[i]->GetName()), finalCut);
  }  
  for ( int i= 1;  i<=nZgBins ; i++) {
    scaleInt(h1dzg[i]);
    handsomeTH1(h1dzg[i],1);
    if ( i==1) handsomeTH1(h1dzg[i],1);
    if ( i==2) handsomeTH1(h1dzg[i],kMagenta);
    if ( i==3) handsomeTH1(h1dzg[i],kBlue);

    h1dzg[i]->SetAxisRange(9e-4,0.2,"Y");
    if ( i==1)       h1dzg[i]->Draw("hist");
    else             h1dzg[i]->Draw("same hist");
  }
  
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
