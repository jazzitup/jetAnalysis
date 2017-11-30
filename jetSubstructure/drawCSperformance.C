#include "getSpectraOfTracks.C"
#include "commonUtility.h"
#include "TCut.h"
void drawCSperformance(TString name ="scan2_v3.5_alphaSubtr0_csMaxR0.60", bool jetCone=true) {
  TH1::SetDefaultSumw2();
  TString fname = Form("ntuples/jetSubstructure_himix_%s.root",name.Data());
  TFile* f = new TFile(fname.Data());
  
  trkSpectra tracks[10]; // centrality bins
  for ( int i = 0; i<=6 ; i++) {
    tracks[i] = getSpectraOfTracks(i,fname.Data());
    handsomeTH1(tracks[i].post,46-i);
    handsomeTH1(tracks[i].pre,46-i);
    int bin10GeV = tracks[i].post->FindBin(10.001);
    float integral = tracks[i].gen->Integral(1,-1);
    tracks[i].post->Scale(1./integral);
    tracks[i].pre->Scale(1./integral);
    tracks[i].gen->Scale(1./integral);
    tracks[i].pre->SetMarkerSize(0.7);
    tracks[i].post->SetMarkerSize(0.7);
    tracks[i].gen->SetMarkerSize(0.7);
  }
  
  TCanvas* cTrackSpec = new TCanvas("cTrackSpec","",1193,619);
  cTrackSpec->Divide(2,1);
  cTrackSpec->cd(1);
  for ( int i = 0; i<=6 ; i++) {
    cleverRange(tracks[i].pre,100,1.e-8);
    tracks[i].pre->SetAxisRange(0.007,100,"Y");
    tracks[i].pre->SetAxisRange(0,9.5,"X");
    tracks[i].pre->SetXTitle("p_{T} (GeV)");
    tracks[i].pre->SetYTitle("Integrated by post-CS entries");
    if ( i == 0 )  tracks[i].pre->Draw(" ");
    else  tracks[i].pre->Draw("same");
    if ( i == 0 )  tracks[i].gen->Draw("same hist ");
    gPad->SetLogy();
    //    gPad->SetLogx();
  }

  TLegend *legSpec = new TLegend(0.5371711,0.4484642,0.998968,0.9191576,NULL,"brNDC");
  easyLeg(legSpec,"Before CS");
  legSpec->AddEntry( tracks[0].pre, "0-10 %","p");
  legSpec->AddEntry( tracks[1].pre, "10-20 %","p");
  legSpec->AddEntry( tracks[2].pre, "20-30 %","p");
  legSpec->AddEntry( tracks[3].pre, "30-40 %","p");
  legSpec->AddEntry( tracks[4].pre, "40-50 %","p");
  legSpec->AddEntry( tracks[5].pre, "50-60 %","p");
  legSpec->AddEntry( tracks[6].pre, "60-80 %","p");
  legSpec->AddEntry( tracks[0].gen, "MC Truth","l");
  legSpec->Draw();
  jumSun(10,0.0005,10,0.1);

  cTrackSpec->cd(2);
  for ( int i = 0; i<=6 ; i++) {
    cleverRange(tracks[i].post,100,1.e-8);
    tracks[i].post->SetAxisRange(0.007,100,"Y");
    tracks[i].post->SetAxisRange(0,9.5,"X");
    tracks[i].post->SetXTitle("p_{T} (GeV)");
    tracks[i].post->SetYTitle("Integrated by post-CS entries");
    if ( i == 0 )  tracks[i].post->Draw(" ");
    else  tracks[i].post->Draw("same");
    if ( i == 0 )  tracks[i].gen->Draw("same hist ");
    gPad->SetLogy();
    //    gPad->SetLogx();
  }
  legSpec = new TLegend(0.5362965,0.4398749,0.9980933,0.9191576,NULL,"brNDC");
  easyLeg(legSpec,"After CS");
  legSpec->AddEntry( tracks[0].pre, "0-10 %","p");
  legSpec->AddEntry( tracks[1].pre, "10-20 %","p");
  legSpec->AddEntry( tracks[2].pre, "20-30 %","p");
  legSpec->AddEntry( tracks[3].pre, "30-40 %","p");
  legSpec->AddEntry( tracks[4].pre, "40-50 %","p");
  legSpec->AddEntry( tracks[5].pre, "50-60 %","p");
  legSpec->AddEntry( tracks[6].pre, "60-80 %","p");
  legSpec->AddEntry( tracks[0].gen, "MC Truth","l");
  legSpec->Draw();

  cTrackSpec->SaveAs(Form("%s_trackSpectra.pdf",name.Data()));

  TCanvas* c1 = new TCanvas("c10","",1000,600);

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
    hPtTrk[icent]->GetYaxis()->SetTitleOffset(1.8);
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
    hPtTrkWiped[icent]->GetYaxis()->SetTitleOffset(1.8);
    hPtTrkWiped[icent]->SetNdivisions(505,"X");
    hPtTrkWiped[icent]->SetNdivisions(505,"Y");
    hPtTrkWiped[icent]->Draw("hist");
    if ( i==1) drawText("Removal rate",0.5,0.7,2);
    jumSun(0,1,23,1);
    //    gPad->SetLogy();
    
  }
  c2->SaveAs(Form("%s_Ratio_of_removed_tracks_by_CS_isJetCone%d.pdf",name.Data(),jetCone));


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
  c3->SaveAs(Form("%s_pT_before_after_CS_isJetCone%d.pdf",name.Data(),jetCone));


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
  c4->SaveAs(Form("%s_deltaPt_by_CS_isJetCone%d.pdf",name.Data(),jetCone));

}
