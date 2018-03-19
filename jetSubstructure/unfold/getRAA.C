#include "../getSdHists.C"
#include "../ntupleDefinition.h"
#include "../commonUtility.h"
#include "../jzWeight.h"
#include "../commonUtility.h"
#include "../JssUtils.h"
#include "unfoldingUtil.h"

void getDATAresults(int kSample=0, int icent=0, int ix=0, int nIter=0, TH1D* hdataRawSq=0, TH1D* hdataUnfSq=0);

void getRAA(int icent=0, int nIter =10, int optX=1, int optY=2 ) {
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

  TH1D* hPPRawSq[30]; // 
  TH1D* hPPUnfSq[30]; // 
  TH1D* hPbPbRawSq[30]; // 
  TH1D* hPbPbUnfSq[30]; // 

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
  makeMultiPanelCanvas(c1,nPtPannels, 2);

  for ( int ipt = lowPtBin ; ipt<= highPtBin ; ipt++)  {
    c1->cd(ipt - lowPtBin + 1);
    
    if ( optY==1)  hPPUnfSq[ipt]->SetAxisRange(-300,2000,"X");
    else if ( optY==2) hPPUnfSq[ipt]->SetAxisRange(0.001,0.299,"X");
    if ( optY==1)    hPPUnfSq[ipt]->SetXTitle("m (GeV)");
    else if ( optY==2)    hPPUnfSq[ipt]->SetXTitle("m/p_{T}");
    
    hPPUnfSq[ipt]->SetYTitle("dN/d(m/p_{T})");
    handsomeTH1(hPPUnfSq[ipt],1);
    handsomeTH1(hPbPbUnfSq[ipt],2);
    scaleInt(hPPUnfSq[ipt]);
    scaleInt(hPbPbUnfSq[ipt]);
    cleverRangeLog(hPPUnfSq[ipt],100,0.0000002);
    hPPUnfSq[ipt]->SetNdivisions(505,"X");
    hPPUnfSq[ipt]->Draw();
    hPbPbUnfSq[ipt]->Draw("same");
    gPad->SetLogy();
    
    if ( ipt == lowPtBin ) {
      drawCentrality(kPbPb, icent, 0.3,0.83,1,20);
      TLegend *leg1 = new TLegend(0.2714489,0.09583328,0.7891275,0.3791666,NULL,"brNDC");
      easyLeg(leg1,"Per-jet distribution",0.08);
      leg1->AddEntry(hPPUnfSq[ipt], "pp","pl");
      leg1->AddEntry(hPbPbUnfSq[ipt], "PbPb","pl");
      leg1->Draw();
    }
    drawBin(xBin,ipt,"GeV",0.3,0.75,1,20);


    c1->cd(ipt - lowPtBin + 1 + nPtPannels);
    hRAA[ipt] = (TH1D*)hPbPbUnfSq[ipt]->Clone(Form("hRAA_icent%d_ipt%d",icent,ipt));
    hRAA[ipt]->Divide(hPPUnfSq[ipt]);
    
    if ( optY==1)  hRAA[ipt]->SetAxisRange(-300,2000,"X");
    else if ( optY==2) hRAA[ipt]->SetAxisRange(0.001,0.299,"X");
    if ( optY==1)    hRAA[ipt]->SetXTitle("m (GeV)");
    else if ( optY==2)    hRAA[ipt]->SetXTitle("m/p_{T}");
    
    hRAA[ipt]->SetNdivisions(505,"X");
    hRAA[ipt]->SetAxisRange( 0,2,"Y");
    
    hRAA[ipt]->SetYTitle("PbPb/pp");
    hRAA[ipt]->Draw();

    //    drawText("Ratio of per-jet distribution",0.3,0.78,2,16);

  }
  c1->SaveAs(Form("raaResults/RAA_2d_optX%d_optY%d_icent%d_iter%d.pdf",optX,optY,icent,nIter));
  //  c1->SaveAs(Form("raaResults/RAA_2d_optX%d_optY%d_icent%d_iter%d.png",optX,optY,icent));
  
  c1->Update();
}



void getDATAresults(int kSample, int icent, int ix, int nIter, TH1D* hdataRawSq, TH1D* hdataUnfSq) {
  TFile * fin = new TFile(Form("unfSpectra/kSample%d_matrixRwt1_spectraRwt0.root",kSample));
  TH1D* hUnf = (TH1D*)fin->Get(Form("hdataUnfSq_icent%d_ix%d_iter%d",icent,ix,nIter));
  TH1D* hRaw = (TH1D*)fin->Get(Form("hdataRawSq_icent%d_ix%d_iter%d",icent,ix,nIter));

  hdataUnfSq->Reset();
  hdataUnfSq->Add(hUnf);
  //  hdataRawSq->Reset();
  //  hdataRawSq->Add(hRaw);


}




