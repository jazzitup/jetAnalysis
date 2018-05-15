#include "../getSdHists.C"
#include "../ntupleDefinition.h"
#include "../commonUtility.h"
#include "../jzWeight.h"
#include "../commonUtility.h"
#include "../JssUtils.h"
#include "unfoldingUtil.h"
#include "../TAA.h"
void getRAWresults(int kSample=0, int icent=0, int ix=0, TH1D* hdataRawSq=0, TH1D* hmcRawSq=0);

void getRecoRAA(int icent=0, int optX=1, int optY=2 ) {
  //  double ptBin[9]= {100, 126, 158, 200, 251, 316, 398, 501, 800};
  //  double ptBin[9]= {110, 136, 150, 168, 200, 251, 398, 501, 800};
  //  const int nPtBin = 7;
  //  double ptBin[nPtBin+1] = {158, 200, 251, 316, 398, 501, 800};
  //  double ptBin[nPtBin+1] = {126, 158, 200, 251, 316, 398, 501, 800};
  

  int nXbins;
  double xBin[30];
  getXbin(nXbins, xBin, optX);

  int nYbins ;
  double yBin[30] ;
  double yBinSqrt[30] ;
  getYbin(nYbins, yBin, yBinSqrt, optY);
  TH1D* tempHistYsq;
  if ( optY == 1 ) tempHistYsq = new TH1D("tempHistY",";mass(GeV);",nYbins,yBinSqrt);
  if ( optY == 2 ) tempHistYsq = new TH1D("tempHistY",";m/p_{T};",nYbins,yBinSqrt);

  int lowPtBin = 6;
  int highPtBin = 11;
  int nPtPannels = highPtBin-lowPtBin+1;

  TH1D* hPPmc[30]; // 
  TH1D* hPbPbmc[30]; //
  TH1D* hPPdata[30]; // 
  TH1D* hPbPbdata[30]; //

  TH1D* hRAA[30]; 
  
  for ( int ix = lowPtBin ; ix<= highPtBin ; ix++)  {
    hPPmc[ix] = (TH1D*)tempHistYsq->Clone(Form("hPPmc_ix%d",ix));
    hPbPbmc[ix] = (TH1D*)tempHistYsq->Clone(Form("hPbPbmc_ix%d",ix));
    hPPdata[ix] = (TH1D*)tempHistYsq->Clone(Form("hPPdata_ix%d",ix));
    hPbPbdata[ix] = (TH1D*)tempHistYsq->Clone(Form("hPbPbdata_ix%d",ix));
    getRAWresults(kPP,   0, ix, hPPdata[ix], hPPmc[ix]);
    getRAWresults(kPbPb, icent, ix, hPbPbdata[ix], hPbPbmc[ix]);
  }
  
  
  TCanvas* c1=  new TCanvas("c1","",1200,550);
  makeMultiPanelCanvas(c1,nPtPannels, 2);

  for ( int ipt = lowPtBin ; ipt<= highPtBin ; ipt++)  {
    c1->cd(ipt - lowPtBin + 1);
    
    if ( optY==1)  hPbPbmc[ipt]->SetAxisRange(-300,2000,"X");
    else if ( optY==2) hPbPbmc[ipt]->SetAxisRange(.001,0.299,"X");
    if ( optY==1)    hPbPbmc[ipt]->SetXTitle("m (GeV)");
    else if ( optY==2)    hPbPbmc[ipt]->SetXTitle("m/p_{T}");
    
    hPbPbmc[ipt]->SetYTitle("dN/d(m/p_{T})");
    handsomeTH1(hPPdata[ipt],1);
    handsomeTH1(hPbPbdata[ipt],2);
    CsScalePP(hPPdata[ipt]);
    CsScalePbPb(hPbPbdata[ipt],icent);
    cleverRangeLog(hPbPbdata[ipt],100,0.0000002);
    hPbPbmc[ipt]->SetNdivisions(505,"X");
    hPbPbdata[ipt]->Draw();
    hPPdata[ipt]->Draw("same");
    gPad->SetLogy();
    
    if ( ipt == lowPtBin ) {
      drawCentrality(kPbPb, icent, 0.3,0.83,1,20);
      TLegend *leg1 = new TLegend(0.2714489,0.09583328,0.7891275,0.3791666,NULL,"brNDC");
      easyLeg(leg1,"Per-jet distribution",0.08);
      leg1->AddEntry(hPPdata[ipt], "pp","pl");
      leg1->AddEntry(hPbPbdata[ipt], "PbPb","pl");
      leg1->Draw();
    }
    drawBin(xBin,ipt,"GeV",0.3,0.75,1,20);
    
    
    c1->cd(ipt - lowPtBin + 1 + nPtPannels);
    hRAA[ipt] = (TH1D*)hPbPbdata[ipt]->Clone(Form("hRAA_icent%d_ipt%d",icent,ipt));
    hRAA[ipt]->Divide(hPPdata[ipt]);
    
    if ( optY==1)  hRAA[ipt]->SetAxisRange(-300,2000,"X");
    else if ( optY==2) hRAA[ipt]->SetAxisRange(.001,0.299,"X");
    if ( optY==1)    hRAA[ipt]->SetXTitle("m (GeV)");
    else if ( optY==2)    hRAA[ipt]->SetXTitle("m/p_{T}");
    
    hRAA[ipt]->SetNdivisions(505,"X");
    hRAA[ipt]->SetAxisRange( 0,3,"Y");
    
    hRAA[ipt]->SetYTitle("Data/MC");
    hRAA[ipt]->Draw();

    //    drawText("Ratio of per-jet distribution",0.3,0.78,2,16);

  }
  c1->SaveAs(Form("raaResults/recoDataMC_PbPb_2d_optX%d_optY%d_icent%d.pdf",optX,optY,icent));
  //  c1->SaveAs(Form("raaResults/RAA_2d_optX%d_optY%d_icent%d_iter%d.png",optX,optY,icent));
  
  c1->Update();
}



void getRAWresults(int kSample, int icent, int ix, TH1D* hdataRawSq, TH1D* hmcRawSq) {
  TFile * fin = new TFile(Form("unfSpectra/kSample%d_matrixRwt1_spectraRwt0.root",kSample));
  TH1D* hdata = (TH1D*)fin->Get(Form("hdataRawSq_icent%d_ix%d",icent,ix));
  TH1D* hmc = (TH1D*)fin->Get(Form("hmcRawSq_icent%d_ix%d",icent,ix));
  //  TH1D* hRaw = (TH1D*)fin->Get(Form("hdataRawSq_icent%d_ix%d_iter%d",icent,ix));

  hdataRawSq->Reset();
  hdataRawSq->Add(hdata);
  hmcRawSq->Reset();
  hmcRawSq->Add(hmc);

}




