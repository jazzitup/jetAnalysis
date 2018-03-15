#include "../getSdHists.C"
#include "../ntupleDefinition.h"
#include "../commonUtility.h"
#include "../jzWeight.h"
#include "../commonUtility.h"
#include "../JssUtils.h"
#include "unfoldingUtil.h"

void getDATAresults(int kSample=0, int icent=0, int ix=0, int nIter=0,  bool matRwt=1, bool specRwt=0, TH1D* hdataRawSq=0, TH1D* hdataUnfSq=0);

void getUnfoldingStabilityData(int kSample= kPP, int icent = 0, int nIter=1, int optX=1, int optY=2) {

  bool specRwt=0;

  bool matRwt=1;

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
  
  
  if ( (kSample == kPP) && (icent!=0) ) {
    cout << " pp sample must have cent = 0" << endl;
    return;
  }
  
  //  int lowPtBin = 6;
  //  int highPtBin = 11;
  int lowPtBin = 6;
  int highPtBin = nXbins-1;
  int nPtPannels = highPtBin-lowPtBin+1;


  TH1D* hdataUnfSq[30]; 
  TH1D* hdataRawSq[30]; 
  TH1D* hdataUnfSqRw[30]; 
  TH1D* hdataRawSqRw[30]; 

  TH1D* hdataRatioSq[30]; // Rw/Unrw
  
  for ( int ix = lowPtBin ; ix<= highPtBin ; ix++)  { 

    hdataUnfSq[ix] = (TH1D*)tempHistYsq->Clone(Form("dataUnfSq_ix%d_in%d",ix,nIter));
    hdataRawSq[ix] = (TH1D*)tempHistYsq->Clone(Form("dataRawSq_ix%d_in%d",ix,nIter));
    hdataUnfSqRw[ix] = (TH1D*)tempHistYsq->Clone(Form("dataUnfSqRw_ix%d_in%d",ix,nIter));
    hdataRawSqRw[ix] = (TH1D*)tempHistYsq->Clone(Form("dataRawSqRw_ix%d_in%d",ix,nIter));
    getDATAresults(kSample, icent, ix, nIter, 0, specRwt ,  hdataRawSq[ix], hdataUnfSq[ix]);
    getDATAresults(kSample, icent, ix, nIter, 1, specRwt ,  hdataRawSqRw[ix], hdataUnfSqRw[ix]);
  }
  
  
  TCanvas* c2 =  new TCanvas("c2","",1200,550);
  //  c2->Divide((nPtBinDraw+1)/2,2);
  makeEfficiencyCanvas(c2,nPtPannels, 0.05, 0.01, 0.1, 0.3, 0.01);
  
  for ( int ipt = lowPtBin ; ipt<= highPtBin ; ipt++)  {
    c2->cd(ipt - lowPtBin + 1);
    
    if ( optY==1)  hdataUnfSq[ipt]->SetAxisRange(0,100,"X");
    else if ( optY==2) hdataUnfSq[ipt]->SetAxisRange(0.001,0.2999,"X");
    if ( optY==1)    hdataUnfSq[ipt]->SetXTitle("m GeV");
    else if ( optY==2)    hdataUnfSq[ipt]->SetXTitle("m/p_{T}");
    if ( hdataUnfSq[ipt]->Integral()>0) cleverRangeLog(hdataUnfSq[ipt],100,0.000001);
    hdataUnfSq[ipt]->SetYTitle("Entries");
    handsomeTH1(hdataUnfSq[ipt],1);
    handsomeTH1(hdataUnfSqRw[ipt],2);
    hdataUnfSq[ipt]->Draw("");
    hdataUnfSqRw[ipt]->Draw("same e");
      
    drawBin(xBin,ipt,"GeV",0.2,0.78,1,18);
    gPad->SetLogy();
    
    if ( ipt == lowPtBin ) {
      drawCentrality(kSample, icent, 0.45,0.86,1,24);
      TLegend *leg1 = new  TLegend(0.2396099,0.1195233,0.7575544,0.3318368,NULL,"brNDC");
      easyLeg(leg1,"Unfolded by ",0.08);
      leg1->AddEntry(hdataUnfSq[ipt], "Un-Rwt matrix","lp");
      leg1->AddEntry(hdataUnfSqRw[ipt], "Rwt matrix","lp");
      leg1->Draw();
    }
    if ( ipt == lowPtBin+1 ) 
      drawText(Form("Iteration: %d",nIter), 0.25,0.86,4,24);
    
    c2->cd(ipt - lowPtBin + 1 + nPtPannels);
    bool drawFirst=true; 
    hdataRatioSq[ipt] = (TH1D*)hdataUnfSqRw[ipt]->Clone(Form("dataRatioSq_ix%d",ipt));
    hdataRatioSq[ipt]->Divide(hdataUnfSq[ipt]);
    hdataRatioSq[ipt]->SetAxisRange(0.5,1.5,"Y");
    hdataRatioSq[ipt]->SetAxisRange(0.001,0.299,"X");
    if ( optY==1) hdataRatioSq[ipt]->SetAxisRange(0.0,100,"X");
    hdataRatioSq[ipt]->SetYTitle("Rwt'd/Un-Rwt");
    hdataRatioSq[ipt]->SetNdivisions(505,"X");
    hdataRatioSq[ipt]->Draw();
    jumSun(0,1,0.3,1);
    
  }
  //  c2->SaveAs(Form("stabilitiy/dataRatioRWTtoNORWT_coll%d_icent%d_nIter%d.pdf",kSample,icent,nIter));
  c2->SaveAs(Form("stabilitiy/dataRatioRWTtoNORWT_coll%d_icent%d_nIter%d.png",kSample,icent,nIter));
}

void getDATAresults(int kSample, int icent, int ix, int nIter,  bool matRwt, bool specRwt, TH1D* hdataRawSq, TH1D* hdataUnfSq) {
  TFile * fin = new TFile(Form("unfSpectra/kSample%d_matrixRwt%d_spectraRwt%d.root",kSample, (int)matRwt, (int)specRwt));
  cout << "Reading " << fin->GetName() << endl;
  TH1D* hUnf = (TH1D*)fin->Get(Form("hdataUnfSq_icent%d_ix%d_iter%d",icent,ix,nIter));
  TH1D* hRaw = (TH1D*)fin->Get(Form("hdataRawSq_icent%d_ix%d",icent,ix));

  hdataUnfSq->Reset();
  hdataUnfSq->Add(hUnf);
  hdataRawSq->Reset();
  hdataRawSq->Add(hRaw);

}

