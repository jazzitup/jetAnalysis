#include "commonUtility.h"
#include "TCut.h"
void drawCSperformance() {
  TH1::SetDefaultSumw2();
  TFile* f = new TFile("ntuples/testCondor_v3.5.root");
  TH2D* hPrePtPostPt[10]; // in centrality bin
  TH2D* hDptPt[10]; // in centrality bin
  TH2D* hPrePtPostPtJc[10]; // Jc = Jet cone  
  TH2D* hDptPtJc[10]; // 


  TH2D* hDr[10];
  TH2D* hDrJc[10];
  TH1D* hPtTrk[10];
  TH1D* hPtTrkWiped[10];
  TH1D* hPtTrkJc[10];
  TH1D* hPtTrkWipedJc[10];

  const int nCent = 7 ; 
  double centBin[nCent+1] = { 0,10,20,30,40,50,60,80}; 
  
  for ( int icent = 0 ; icent < nCent ; icent++) {
    hPrePtPostPt[icent] = (TH2D*)f->Get(Form("h_bkgSubt_prePt_postPt_cent%d",icent));
    hDptPt[icent]       = (TH2D*)f->Get(Form("h_trkPt_trkBkgPt_cent%d",icent));
    hDr[icent]          = (TH2D*)f->Get(Form("h_dRSubt_trkPt_cent%d",icent));
    hPrePtPostPtJc[icent] = (TH2D*)f->Get(Form("h_bkgSubt_prePt_postPt_jetCone_cent%d",icent));
    hDptPtJc[icent]       = (TH2D*)f->Get(Form("h_trkPt_trkBkgPt_jetCone_cent%d",icent));
    hDrJc[icent]          = (TH2D*)f->Get(Form("h_dRSubt_trkPt_jetCone_cent%d",icent));
    
    TH1D* htemp = (TH1D*)hDr[icent]->ProjectionX();
    int nXbins = htemp->GetNbinsX();  cout << "xbins = " << nXbins << endl;
    hPtTrk[icent] = (TH1D*)hDr[icent]->ProjectionY(Form("hPtTrk_%d",icent),1, nXbins); 
    hPtTrkWiped[icent] = (TH1D*)hDr[icent]->ProjectionY(Form("hPtTrkWiped_%d",icent),2, nXbins); 
    hPtTrkJc[icent] = (TH1D*)hDrJc[icent]->ProjectionY(Form("hPtTrkJc_%d",icent),1, nXbins); 
    hPtTrkWipedJc[icent] = (TH1D*)hDrJc[icent]->ProjectionY(Form("hPtTrkWipedJc_%d",icent),2, nXbins); 
    
    handsomeTH1(hPtTrk[icent],1);
    handsomeTH1(hPtTrkWiped[icent],2);
    mcStyle1(hPtTrkWiped[icent]);
    handsomeTH1(hPtTrkJc[icent],1);
    handsomeTH1(hPtTrkWipedJc[icent],2);
    mcStyle1(hPtTrkWipedJc[icent]);
  }
  TCanvas* c1 = new TCanvas("c10","",1000,600);
  c1->Divide(nCent,2);
  for ( int icent = 0 ; icent < nCent ; icent++) {
    c1->cd(icent+1);
    hDr[icent]->Draw("colz");
    c1->cd(icent + nCent +1);
    hDrJc[icent]->Draw("colz");
  }

  TCanvas* c2 = new TCanvas("c20","",900,500);
  makeEfficiencyCanvas(c2, 3);
  for ( int i=1 ; i<=3 ; i++) {  
    c2->cd(i);
    int icent = 0; 
    if (i==1) icent = 6;
    if (i==2) icent = 3; 
    if (i==3) icent = 0;
    TString centText = Form("%d%% - %d%%",(int)centBin[icent],(int)centBin[icent+1]);
    hPtTrk[icent]->SetAxisRange(0,20,"X");
    hPtTrk[icent]->DrawCopy();
    hPtTrkWiped[icent]->DrawCopy("same hist");
    gPad->SetLogy();
    if ( i==1) drawText("PbPb MC", 0.5, 0.9);
    drawText(centText.Data(), 0.5,0.8,2);
    c2->cd(i+3);
    hPtTrkWiped[icent]->Divide(hPtTrk[icent]);
    hPtTrkWiped[icent]->SetAxisRange(0.001,1.5,"Y");
    hPtTrkWiped[icent]->SetAxisRange(0,20,"X");
    mcStyle1(hPtTrkWiped[icent]);
    fixedFontHist(hPtTrkWiped[icent]);
    hPtTrkWiped[icent]->SetXTitle("Track p_{T} (GeV/c)");
    hPtTrkWiped[icent]->SetNdivisions(505,"X");
    hPtTrkWiped[icent]->SetNdivisions(505,"Y");
    hPtTrkWiped[icent]->Draw("hist");
    if ( i==1) drawText("Removal rate",0.5,0.8,2);
    jumSun(0,1,20,1);
    //    gPad->SetLogy();
    
  }
  
  
}
