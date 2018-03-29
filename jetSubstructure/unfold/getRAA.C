#include "../getSdHists.C"
#include "../ntupleDefinition.h"
#include "../commonUtility.h"
#include "../jzWeight.h"
#include "../commonUtility.h"
#include "../JssUtils.h"
#include "unfoldingUtil.h"
#include "../TAA.h"
void getDATAresults(int kSample=0, int icent=0, int ix=0, int nIter=0, TH1D* hdataRawSq=0, TH1D* hdataUnfSq=0);
void getErrorHist(TH1D* hh=0, int kSample=kPP, int icent =0, int ipt =0, int nIter=-1 ){
  int nbins = hh->GetNbinsX();
  TFile* fsys = new TFile(Form("uncertainty/unc_unfold_kSample%d_icent%d.root",kSample,icent));
  TH1D* histsys = (TH1D*)fsys->Get(Form("unc_ipt%d_nIter%d",ipt,nIter));
  for (int ii = 1 ; ii<=nbins; ii++) {
    hh->SetBinContent( ii,fabs(histsys->GetBinContent(ii))); 
    if ( ii == nbins ) 
      hh->SetBinContent( ii,0);
  }
}


void getRAA(int icent=0, int nIter =4, int optX=1, int optY=2 ) {
  
  int nXbins;
  double xBin[30];
  getXbin(nXbins, xBin, optX);

  int nYbins ;
  double yBin[30] ;
  getYbin(nYbins, yBin, optY);
  TH1D* tempHistYsq;
  if ( optY == 1 ) tempHistYsq = new TH1D("tempHistY",";mass(GeV);",nYbins,yBin);
  if ( optY == 2 ) tempHistYsq = new TH1D("tempHistY",";m/p_{T};",nYbins,yBin);

  int lowPtBin = 6;
  int highPtBin = 11;
  int nPtPannels = highPtBin-lowPtBin+1;

  TH1D* hPPRawSq[30]; // 
  TH1D* hPPUnfSq[30]; // 
  TH1D* hPbPbRawSq[30]; // 
  TH1D* hPbPbUnfSq[30]; // 

  TH1D* hPPUnfSys[30]; // 
  TH1D* hPbPbUnfSys[30]; // 
  TH1D* hRAAUnfSys[30]; // 
  


  TH1D* hRAA[30]; 
  

  for ( int ix = lowPtBin ; ix<= highPtBin ; ix++)  {
    hPPRawSq[ix] = (TH1D*)tempHistYsq->Clone(Form("hPPRawSq_ix%d",ix));
    hPPUnfSq[ix] = (TH1D*)tempHistYsq->Clone(Form("hPPUnfSq_ix%d",ix));
    hPbPbRawSq[ix] = (TH1D*)tempHistYsq->Clone(Form("hPbPbRawSq_ix%d",ix));
    hPbPbUnfSq[ix] = (TH1D*)tempHistYsq->Clone(Form("hPbPbUnfSq_ix%d",ix));
    getDATAresults(kPP,   0, ix, nIter,  hPPRawSq[ix], hPPUnfSq[ix]);
    getDATAresults(kPbPb, icent, ix, nIter,  hPbPbRawSq[ix], hPbPbUnfSq[ix]);

  }
  
  TCanvas* c1=  new TCanvas("c1","",1200,550);
  makeMultiPanelCanvas(c1,nPtPannels, 2, 0.0, 0.01, 0.3, 0.2, 0.05);

  for ( int ipt = lowPtBin ; ipt<= highPtBin ; ipt++)  {
    c1->cd(ipt - lowPtBin + 1);
    
    if ( optY==1)  hPPUnfSq[ipt]->SetAxisRange(-300,2000,"X");
    else if ( optY==2) hPPUnfSq[ipt]->SetAxisRange(0.001,0.299,"X");
    if ( optY==1)    hPPUnfSq[ipt]->SetXTitle("m (GeV)");
    else if ( optY==2)    hPPUnfSq[ipt]->SetXTitle("m/p_{T}");
    
    hPPUnfSq[ipt]->SetYTitle("Cross section (#mub^{-1} GeV^{-1})");
    handsomeTH1(hPPUnfSq[ipt],1);
    handsomeTH1(hPbPbUnfSq[ipt],kRed);
    //    scaleInt(hPPUnfSq[ipt]);
    //    scaleInt(hPbPbUnfSq[ipt]);
    CsScalePP(hPPUnfSq[ipt]);
    CsScalePbPb(hPbPbUnfSq[ipt],icent);
    double maxY = cleverRange(hPPUnfSq[ipt],2.0,0.00000001);
    hPPUnfSq[ipt]->SetAxisRange(maxY *-0.05, maxY,"Y");
    hPPUnfSq[ipt]->SetNdivisions(505,"X");
    hPPUnfSq[ipt]->SetNdivisions(505,"Y");
 
    fixedFontHist(hPPUnfSq[ipt],2,2.2,20);
    hPPUnfSq[ipt]->Draw();
    hPbPbUnfSq[ipt]->Draw("same");
    onSun(0,0,0.3,0);
//    gPad->SetLogy();
    
 
//    hPPUnfSys[ipt] = (TH1D*)hPPUnfSq[ipt]->Clone(Form("hPPSys_ipt%d",ipt));
//    hPbPbUnfSys[ipt] = (TH1D*)hPbPbUnfSq[ipt]->Clone(Form("hPbPbSys_ipt%d",ipt));
//    hRAAUnfSys[ipt] = (TH1D*)hPPUnfSys[ipt]->Clone(Form("hRAASys_ipt%d",ipt));
//    hPPUnfSys[ipt]->Reset(); 
//    hPbPbUnfSys[ipt]->Reset(); 
//    hRAAUnfSys[ipt]->Reset(); 
    //    getErrorHist(hPPUnfSys[ipt], kPP, 0,ipt,nIter);
    //    getErrorHist(hPbPbUnfSys[ipt], kPbPb, icent,ipt,nIter);
    //    quadraticSum(hRAAUnfSys[ipt], hPPUnfSys[ipt], hPbPbUnfSys[ipt]);
    //    drawSys( hPbPbUnfSq[ipt], hPbPbUnfSys[ipt], 4, 1);
    //    drawSys( hPPUnfSq[ipt], hPPUnfSys[ipt], 1, 1);
    hPPUnfSq[ipt]->SetFillStyle(1);
    hPbPbUnfSq[ipt]->SetFillStyle(1);
    hPPUnfSq[ipt]->Draw("same");
    hPbPbUnfSq[ipt]->Draw("same");
    

    if ( ipt == lowPtBin ) {
      TLegend *leg1 = new TLegend(0.5043845,0.5860943,0.9997715,0.8591246,NULL,"brNDC");
      easyLeg(leg1," ");
      leg1->AddEntry(hPPUnfSq[ipt], "pp","pf"); // #frac{d#sigma}{dp_{T}}","pl");
      leg1->AddEntry(hPbPbUnfSq[ipt], "PbPb","pf");// #frac{dN}{dp_{T}}#frac{1}{T_{AA}}","pl");
      leg1->Draw();
    }
    if ( ipt==lowPtBin)  drawBin(xBin,ipt,"GeV",0.35,0.83,1,18);
    else drawBin(xBin,ipt,"GeV",0.35,0.83,1,18);

    gPad->RedrawAxis();

    c1->cd(ipt - lowPtBin + 1 + nPtPannels);
    hRAA[ipt] = (TH1D*)hPbPbUnfSq[ipt]->Clone(Form("hRAA_icent%d_ipt%d",icent,ipt));
    hRAA[ipt]->Divide(hPPUnfSq[ipt]);
    
    if ( optY==1)  hRAA[ipt]->SetAxisRange(-300,2000,"X");
    else if ( optY==2) hRAA[ipt]->SetAxisRange(0.001,0.299,"X");
    if ( optY==1)    hRAA[ipt]->SetXTitle("m (GeV)");
    else if ( optY==2)    hRAA[ipt]->SetXTitle("m/p_{T}");
    
    hRAA[ipt]->SetNdivisions(505,"X");
    hRAA[ipt]->SetAxisRange( -0.05,1.99,"Y");
    
    hRAA[ipt]->SetYTitle("R_{AA}");
    fixedFontHist(hRAA[ipt],2,2.2,20);

    hRAA[ipt]->Draw();
    //    drawSys( hRAA[ipt], hRAAUnfSys[ipt], kYellow);
    hRAA[ipt]->Draw("same");
    //    drawText("Ratio of per-jet distribution",0.3,0.78,2,16);
    jumSun(0,1,0.3,1);
    if ( ipt == lowPtBin ) {
      drawCentrality(kPbPb, icent, 0.37,0.83,1,20);
    }
    // lumi uncertainty 
    double lumiUnc = getLumiRelErr(icent);
    drawErrorBox( 0, 1-lumiUnc, 0.025, 1+lumiUnc, 1);

    
    gPad->RedrawAxis();
    
    c1->cd(ipt - lowPtBin + 1);

    hPPUnfSq[ipt]->Draw();
    hPbPbUnfSq[ipt]->Draw("same");
    //    drawSys( hPbPbUnfSq[ipt], hPbPbUnfSys[ipt], kRed, 1);
    //    drawSys( hPPUnfSq[ipt], hPPUnfSys[ipt], 1, 1);
    if ( ipt == lowPtBin ) {
      drawText("#bf{#it{ATLAS}} Preliminary",0.33,0.85,1,20);
      TLegend *leg1 = new TLegend(0.7043845,0.4860943,0.9997715,0.7591246,NULL,"brNDC");
      easyLeg(leg1," ");
      leg1->AddEntry(hPPUnfSq[ipt], "pp","pf"); // #frac{d#sigma}{dp_{T}}","pl");
      leg1->AddEntry(hPbPbUnfSq[ipt], "PbPb","pf");// #frac{dN}{dp_{T}}#frac{1}{T_{AA}}","pl");
      leg1->Draw();
    }
    if ( ipt == lowPtBin+1 ) {
    drawText("#it{pp} 25 pb^{-1}, PbPb 0.49 nb^{-1}",0.05,0.83,1,18);
    //    drawText("PbPb 0.49 nb^{-1}",0.4,0.78,1,15);
    }
    if ( ipt==lowPtBin)  drawBin(xBin,ipt,"GeV",0.35,0.73,1,16);
    else drawBin(xBin,ipt,"GeV",0.35,0.73,1,16);
    gPad->RedrawAxis();
    
  }
  //  c1->SaveAs(Form("raaResults/RAA_2d_optX%d_optY%d_icent%d_iter%d.png",optX,optY,icent));
  
  c1->Update();
  c1->SaveAs(Form("raaResults/RAA_2d_optX%d_optY%d_icent%d_iter%d.pdf",optX,optY,icent,nIter));
}



void getDATAresults(int kSample, int icent, int ix, int nIter, TH1D* hdataRawSq, TH1D* hdataUnfSq) {
  TFile * fin = new TFile(Form("unfSpectra/kSample%d_matrixRwt1_spectraRwt1.root",kSample));
  TH1D* hUnf = (TH1D*)fin->Get(Form("hdataUnf1d_icent%d_ix%d_iter%d",icent,ix,nIter));
  //  TH1D* hRaw = (TH1D*)fin->Get(Form("hdataRaw1d_icent%d_ix%d_iter%d",icent,ix,nIter));

  hdataUnfSq->Reset();
  hdataUnfSq->Add(hUnf);
  //  hdataRawSq->Reset();
  //  hdataRawSq->Add(hRaw);


}




