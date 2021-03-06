#include "getSdHists.C"
/*
  TH1D* hEffDphi[10];
  TH1D* hEffDrap[10];
*/
void macro1(TString name="file",
                         int ptLow=150, int ptHigh=400,
                         TString varX = "chPtRcSubt", TString nameX ="#Sigmap_{T}^{ch}", float xMin = -20, float xMax = 300,
                         TString varY = "chMassRcSubt", TString nameY ="m_{Subt}^{ch}", float yMin = -30, float yMax = 50
                         );

void drawMassCorrelation() {
  //  TString name="jetSubstructure_himix_test_v4.6_r4_Trimming_rSub0.15_fCut0.05.root";
  TString name="jetSubstructure_himix_test_v4.6_r4_Trimming_rSub0.10_fCut0.05.root";
  /*  macro1(name, 150, 400,  "m2overPt2_full_gen","Truth (m/p_{T})^{2}", -0.02,0.1, "m2overPt2_full", "Calo (m/p_{T})^{2}", -.02,0.1);
    macro1(name, 150, 400, "chPtRcSubt", "#Sigmap_{T}^{trk}", -20, 300, "m2_trk", "m_{trk}^{2} (Subtracted)", -500, 900) ;
    macro1(name, 150, 400, "chPtRcSubt", "#Sigmap_{T}^{trk}", -20, 300, "m2overPt2_trk", "m_{trk}^{2}/#Sigmap_{T}^{trk 2}", -.05,.1);
    macro1(name, 150, 400, "nTrk", "N^{trk}", -10, 20, "m2_trk", "m_{trk}^{2} (Subtracted)", -500, 900) ;
    macro1(name, 150, 400, "nTrk", "N^{trk}", -10, 20, "m2overPt2_trk", "m_{trk}^{2}/#Sigmap_{T}^{trk 2}", -.05,.1);
    macro1(name, 150, 400, "maxPoverPtTrk", "Max[pT^{trk}]/#Sigmap_{T}^{trk}", 0, 1.2, "m2_trk", "m_{trk}^{2} (Subtracted)", -500, 900) ;
    macro1(name, 150, 400, "maxPoverPtTrk", "Max[pT^{trk}]/#Sigmap_{T}^{trk}", 0, 1.2, "m2overPt2_trk", "m_{trk}^{2}/#Sigmap_{T}^{trk 2}", -.05,.1);
    
    macro1(name, 150, 400, "chPtRcSubt", "#Sigmap_{T}^{trk}", -20, 300, "m2_full", "m_{full}^{2}", -500, 3000) ;
    macro1(name, 150, 400, "chPtRcSubt", "#Sigmap_{T}^{trk}", -20, 300, "m2overPt2_full", "m_{full}^{2}/p_{T}^{Jet 2}", -.05,.1);
    macro1(name, 150, 400, "nTrk", "N^{trk}", -10, 20,  "m2_full", "m_{full}^{2}", -500, 3000) ;
    macro1(name, 150, 400, "nTrk", "N^{trk}", -10, 20, "m2overPt2_full", "m_{full}^{2}/p_{T}^{Jet 2}", -.05,.1);
    macro1(name, 150, 400, "maxPoverPtTrk", "Max[pT^{trk}]/#Sigmap_{T}^{trk}", 0, 1.2,  "m2_full", "m_{full}^{2}", -500, 3000) ;
    macro1(name, 150, 400, "maxPoverPtTrk", "Max[pT^{trk}]/#Sigmap_{T}^{trk}", 0, 1.2,  "m2overPt2_full", "m_{full}^{2}/p_{T}^{Jet 2}", -.05,.1);  


  macro1(name, 150, 400,  "m2_full_gen","Truth m^{2}", -1000,3000, "m2_full", "Calo m^{2}", -1000, 3000);
  macro1(name, 150, 400,  "m2_trk_gen","Truth Charged m^{2}", -300,1000, "m2_trk", "Track m^{2}", -300, 1000);
  macro1(name, 150, 400,  "m2overPt2_trk_gen","Truth Charged (m/p_{T})^{2}", -.1,.1, "m2overPt2_trk", "Track (m/p_{T})^{2}", -.1,.1);
  */
    macro1(name, 150, 400, "pt", "p_{T}", 150, 400,   "genTrimM","Truth m, trimmed", -10,100);
  //  macro1(name, 150, 400, "pt", "p_{T}", 150, 400,  "m2_trk", "m_{trk}^{2} (Subtracted)", -900, 900) ;
  //  macro1(name, 150, 400,  "(genTrimM*genTrimM)","Truth m^{2}, trimmed", -1000,3000, "(trimMcorr*trimMcorr)", "Calo m^{2}, trimmed", -1000, 3000);
  //  macro1(name, 150, 400,  "genTrimM","Truth m, trimmed", -10,100, "trimMcorr", "Calo m, trimmed", -10, 100);


}

void macro1(TString name,
	    int ptLow, int ptHigh,
	    TString varX, TString nameX, float xMin, float xMax,
	    TString varY, TString nameY, float yMin, float yMax
	    ){
  
  int nBins = 100;
  int nXbins= nBins;
  int nYbins = nBins;
  //  TString prefix = "testDir";
  TFile* fnameAA =  new TFile(Form("ntuples/%s", name.Data()));
  TTree* tr = (TTree*)fnameAA->Get("tr");
  tr->SetAlias("m2_trk","chMassRcSubt^2*( (chMassRcSubt>0) - (chMassRcSubt<0) )");
  tr->SetAlias("m2overPt2_trk","m2_trk/(chPtRcSubt*chPtRcSubt)");
  tr->SetAlias("m2_trk_gen","chMassGm*chMassGm");
  tr->SetAlias("m2overPt2_trk_gen","m2_trk_gen/chPtRcSubt/chPtRcSubt");
  tr->SetAlias("m2_full","mass^2*( (mass>0) - (mass<0) )");
  tr->SetAlias("m2_full_gen","genMass*genMass");
  tr->SetAlias("chMoverPt","chMassRcSubt/chPtRcSubt");
  tr->SetAlias("m2overPt2_full","m2_full/(pt)^2");
  tr->SetAlias("m2overPt2_full_gen","m2_full_gen/(genPt^2)");
  tr->SetAlias("nTrk","nTrkRaw-nTrkBkg");
  tr->SetAlias("maxPoverPtTrk","maxTrkPt/chPtRcSubt");

  TString ptCut = Form("genPt>80 && pt>%d && pt<%d  ",ptLow, ptHigh) ;     // dr>0  : Gen Matching
  
  TH2D* corr[7];
  TH2D* mass2Full[7];
  
  for ( int icent = 0 ; icent<=6 ; icent++) {
    corr[icent] = new TH2D(Form("corr_%d",icent),";;",nXbins,xMin,xMax,nYbins,yMin,yMax);
    corr[icent]->SetXTitle(nameX.Data());
    corr[icent]->SetYTitle(nameY.Data());
    handsomeTH1(corr[icent]);
    TString centCut = Form("cent == %d",icent);
    TString  theCut = Form("weight*( (%s) && (%s) )", ptCut.Data(),centCut.Data()); 
    tr->Draw(Form("(%s):%s>>%s",varY.Data(),varX.Data(),corr[icent]->GetName()),theCut);
      
  }
  
  TCanvas* c1=  new TCanvas("c1","",800,750);
  c1->Divide(2,2);
  for ( int icent = 0 ; icent<=6 ; icent++) {
    int panel = 0 ;
    if      ( icent == 0 ) panel = 1 ;
    else if ( icent == 2 ) panel = 2 ;
    else if ( icent == 4 ) panel = 3 ;
    else if ( icent == 6 ) panel = 4 ;
    else continue;
    c1->cd(panel)->SetRightMargin(0.2);    
    c1->cd(panel)->SetTopMargin(0.2);
    corr[icent]->Draw("colz");
    float corrFact = corr[icent]->GetCorrelationFactor();
    drawText(Form("Corr. factor = %f",corrFact), 0.5,0.87,1,20);
    if ( icent == 0 )   drawText("PbPb 0-10%", 0.2, 0.8,1,20);
    if ( icent == 2 )   drawText("PbPb 20-30%", 0.2, 0.8,1,20);
    if ( icent == 4 )   drawText("PbPb 40-50%", 0.2, 0.8,1,20);
    if ( icent == 6 )   drawText("PbPb 60-80%", 0.2, 0.8,1,20);
    
  }
  c1->SaveAs(Form("%s_%s_corr.pdf",varX.Data(),varY.Data()));
  
}
