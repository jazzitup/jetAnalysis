#include "commonUtility.h"
#include "TCut.h"
void drawCSperformance(bool jetCone=false) {
  TH1::SetDefaultSumw2();
  TFile* f = new TFile("ntuples/testCondor_v3.5.root");

  TH2D* hPrePtPostPt[10]; // in centrality bin
  TH2D* hDptPt[10]; // in centrality bin
  TH2D* hDr[10];

  TH1D* hPtTrk[10];
  TH1D* hPtTrkWiped[10];

  const int nCent = 7 ; 
  double centBin[nCent+1] = { 0,10,20,30,40,50,60,80}; 
  
  for ( int icent = 0 ; icent < nCent ; icent++) {
    TString postfix = "";
    if ( jetCone) postfix = "_jetCone";
    hPrePtPostPt[icent] = (TH2D*)f->Get(Form("h_bkgSubt_prePt_postPt%s_cent%d", postfix.Data(), icent));
    hDptPt[icent]       = (TH2D*)f->Get(Form("h_trkPt_trkBkgPt%s_cent%d", postfix.Data(), icent));
    hDr[icent]          = (TH2D*)f->Get(Form("h_dRSubt_trkPt%s_cent%d", postfix.Data(), icent));
    
    TH1D* htemp = (TH1D*)hDr[icent]->ProjectionX();
    int nXbins = htemp->GetNbinsX();  //cout << "xbins = " << nXbins << endl;
    hPtTrk[icent] = (TH1D*)hDr[icent]->ProjectionY(Form("hPtTrk_%d",icent),1, -1);
    hPtTrkWiped[icent] = (TH1D*)hDr[icent]->ProjectionY(Form("hPtTrkWiped_%d",icent),2, -1);
    
    handsomeTH1(hPtTrk[icent],1);
    handsomeTH1(hPtTrkWiped[icent],2);
    mcStyle1(hPtTrkWiped[icent]);
  }
  TCanvas* c1 = new TCanvas("c10","",1000,600);
  c1->Divide(nCent,2);
  for ( int icent = 0 ; icent < nCent ; icent++) {
    c1->cd(icent+1);
    hDr[icent]->Draw("colz");
    c1->cd(icent + nCent +1);
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
    hPtTrk[icent]->SetAxisRange(0.5,23,"X");
    hPtTrk[icent]->SetYTitle("Entries");
    hPtTrk[icent]->DrawCopy();
    hPtTrkWiped[icent]->DrawCopy("same hist");
    gPad->SetLogy();
    if ( i==1) { 
      drawText("PbPb MC", 0.5, 0.9);
      TLegend *leg = new TLegend(0.4124564,0.5044259,0.9992266,0.7484586,NULL,"brNDC");
      easyLeg(leg,"");
      leg->AddEntry(hPtTrk[icent], "All tracks","p");
      leg->AddEntry(hPtTrkWiped[icent], "Removed tracks","lf");
      leg->Draw();

    }
    drawText(centText.Data(), 0.5,0.8);
    if (jetCone) drawText("Jet cone, (pT > 150 GeV)",0.5,0.7,1,13);
    else         drawText("|#eta|<2.4",0.5,0.7);
    
    c2->cd(i+3);
    hPtTrkWiped[icent]->Divide(hPtTrk[icent]);
    hPtTrkWiped[icent]->SetAxisRange(0.001,1.2,"Y");
    hPtTrkWiped[icent]->SetAxisRange(0.5,23,"X");
    mcStyle1(hPtTrkWiped[icent]);
    fixedFontHist(hPtTrkWiped[icent],3);
    hPtTrkWiped[icent]->SetYTitle("Removed/all");
    hPtTrkWiped[icent]->SetXTitle("Track p_{T} (GeV/c)");
    hPtTrkWiped[icent]->SetNdivisions(505,"X");
    hPtTrkWiped[icent]->SetNdivisions(505,"Y");
    hPtTrkWiped[icent]->Draw("hist");
    if ( i==1) drawText("Removal rate",0.5,0.7,2);
    jumSun(0,1,23,1);
    //    gPad->SetLogy();
    
  }
  c2->SaveAs(Form("Ratio_of_removed_tracks_by_CS_isJetCone%d.png",jetCone));


  TCanvas* c3 = new TCanvas("c30","",900,300);
  c3->Divide(3,1);
  for ( int i=1 ; i<=3 ; i++) {  
    c3->cd(i);
    int icent = 0; 
    if (i==1) icent = 6;
    if (i==2) icent = 3; 
    if (i==3) icent = 0;
    TString centText = Form("%d%% - %d%%",(int)centBin[icent],(int)centBin[icent+1]);
    hPrePtPostPt[icent]->SetAxisRange(0,40,"X");
    hPrePtPostPt[icent]->SetAxisRange(0,40,"Y");
    hPrePtPostPt[icent]->SetXTitle("p_{T} before CS (GeV)");
    hPrePtPostPt[icent]->SetYTitle("p_{T} after CS (Gev)");
    hPrePtPostPt[icent]->DrawCopy("colz");
    if ( i==1) { 
      drawText("PbPb MC", 0.2, 0.87);
    if (jetCone) drawText("Jet cone, (pT > 150 GeV)",0.2,0.7,1,13);
    else         drawText("|#eta|<2.4",0.2,0.7);
    }
    drawText(centText.Data(), 0.2,0.8);
  }
  c3->SaveAs(Form("pT_before_after_CS_isJetCone%d.png",jetCone));


  TCanvas* c4 = new TCanvas("c40","",900,300);
  c4->Divide(3,1);
  for ( int i=1 ; i<=3 ; i++) {  
    c4->cd(i);
    int icent = 0; 
    if (i==1) icent = 6;
    if (i==2) icent = 3; 
    if (i==3) icent = 0;
    TString centText = Form("%d%% - %d%%",(int)centBin[icent],(int)centBin[icent+1]);
    hDptPt[icent]->SetAxisRange(0,100,"X");
    hDptPt[icent]->SetAxisRange(-0.5,10,"Y");
    hDptPt[icent]->SetYTitle("#Deltap_{T} by CS(GeV)");
    hDptPt[icent]->SetXTitle("p_{T}");
    hDptPt[icent]->DrawCopy("colz");
    TH1D* hpr = (TH1D*)hDptPt[icent]->ProfileX();
    //    hpr->Rebin(10);  //  hpr->Scale(1./10);
    hpr->Draw("same");

    if ( i==1) { 
      drawText("PbPb MC", 0.3, 0.87);
    }
    drawText(centText.Data(), 0.3,0.8);
    if (jetCone) drawText("Jet cone, (pT > 150 GeV)",0.3,0.7,1,13);
    else         drawText("|#eta|<2.4",0.3,0.7);
  }
  c4->SaveAs(Form("deltaPt_by_CS_isJetCone%d.png",jetCone));

}
