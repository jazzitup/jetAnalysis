#include "../TAA.h"
#include "systematicsTool.h"

void getDATAforRAA(int kSample=0, int icent=0, int ix=0, int nIter=0, TH1D* hdataRawSq=0, TH1D* hdataUnfSq=0);
JetSys getFinalSys(int icent =0, int nVar=0);  
void narrowSys( TH1D* hsys=0, double xlow=0, double xhigh=0);


void getRAA(int icent=0, int optX=1, int optY=2 ) {

  int nIterPP = getRefIter(0,0);
  int nIterAA = getRefIter(1,icent);
  
  //int nIterPP = 6 ;
  //  int nIterAA = 6 ;
  
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

  JetSys sysPlus;
  JetSys sysMinus;
  sysPlus = getFinalSys(icent, 1);
  sysMinus = getFinalSys(icent, -1);


  TH1D* hRAA[30]; 
  TH1D* hRAApt = new TH1D("hraapt",";p_{T};R_{AA}",nXbins,xBin);
  
  
  for ( int ix = lowPtBin ; ix<= highPtBin ; ix++)  {
    hPPRawSq[ix] = (TH1D*)tempHistYsq->Clone(Form("hPPRawSq_ix%d",ix));
    hPPUnfSq[ix] = (TH1D*)tempHistYsq->Clone(Form("hPPUnfSq_ix%d",ix));
    hPbPbRawSq[ix] = (TH1D*)tempHistYsq->Clone(Form("hPbPbRawSq_ix%d",ix));
    hPbPbUnfSq[ix] = (TH1D*)tempHistYsq->Clone(Form("hPbPbUnfSq_ix%d",ix));
    getDATAforRAA(kPP,   0, ix, nIterPP,  hPPRawSq[ix], hPPUnfSq[ix]);
    getDATAforRAA(kPbPb, icent, ix, nIterAA,  hPbPbRawSq[ix], hPbPbUnfSq[ix]);

  }



  TCanvas* c1=  new TCanvas("c1","",1200,550);
  makeMultiPanelCanvas(c1,nPtPannels, 2, 0.0, 0.01, 0.3, 0.2, 0.05);

  for ( int ipt = lowPtBin ; ipt<= highPtBin ; ipt++)  {
    c1->cd(ipt - lowPtBin + 1);
    
    narrowSys( sysPlus.pp[ipt], 0, 0.24);
    narrowSys( sysPlus.pbpb[ipt], 0, 0.24);
    narrowSys( sysPlus.raa[ipt], 0, 0.24);

    if ( optY==1)  hPPUnfSq[ipt]->SetAxisRange(-300,2000,"X");
    else if ( optY==2) hPPUnfSq[ipt]->SetAxisRange(0.001,0.239,"X");
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
 
    drawSys( hPbPbUnfSq[ipt], sysPlus.pbpb[ipt], 4, 1);
    drawSys( hPPUnfSq[ipt], sysPlus.pp[ipt], 1, 1);
    hPPUnfSq[ipt]->SetFillStyle(1);
    hPbPbUnfSq[ipt]->SetFillStyle(1);
    hPPUnfSq[ipt]->Draw("same");
    hPbPbUnfSq[ipt]->Draw("same");
    
  
    if ( ipt==lowPtBin)  drawBin(xBin,ipt,"GeV",0.35,0.83,1,18);
    else drawBin(xBin,ipt,"GeV",0.35,0.83,1,18);

    gPad->RedrawAxis();

    c1->cd(ipt - lowPtBin + 1 + nPtPannels);
    hRAA[ipt] = (TH1D*)hPbPbUnfSq[ipt]->Clone(Form("hRAA_icent%d_ipt%d",icent,ipt));
    hRAA[ipt]->Divide(hPPUnfSq[ipt]);
    
    double theRAA =  hPbPbUnfSq[ipt]->Integral("width");
    theRAA = theRAA / hPPUnfSq[ipt]->Integral("width");
    hRAApt->SetBinContent( ipt, theRAA) ;
    hRAApt->SetBinError( ipt, 0.001);
    
    
    if ( optY==1)  hRAA[ipt]->SetAxisRange(-300,2000,"X");
    else if ( optY==2) hRAA[ipt]->SetAxisRange(0.001,0.239,"X");
    if ( optY==1)    hRAA[ipt]->SetXTitle("m (GeV)");
    else if ( optY==2)    hRAA[ipt]->SetXTitle("m/p_{T}");
    
    hRAA[ipt]->SetNdivisions(505,"X");
    hRAA[ipt]->SetAxisRange( -0.05,1.99,"Y");
    
    hRAA[ipt]->SetYTitle("R_{AA}");
    fixedFontHist(hRAA[ipt],2,2.2,20);

    hRAA[ipt]->Draw();
    drawSys( hRAA[ipt], sysPlus.raa[ipt], kOrange);
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
    drawSys( hPbPbUnfSq[ipt], sysPlus.pbpb[ipt], kRed, 1);
    drawSys( hPPUnfSq[ipt], sysPlus.pp[ipt], 1, 1);
    if ( ipt == lowPtBin ) {
      //      drawText("#bf{#it{ATLAS}}",0.33,0.85,1,20);
      TLegend *leg1 = new TLegend(0.7043845,0.5860943,0.9997715,0.8591246,NULL,"brNDC");
      easyLeg(leg1," ");
      leg1->AddEntry(hPPUnfSq[ipt], "pp","pf"); // #frac{d#sigma}{dp_{T}}","pl");
      leg1->AddEntry(hPbPbUnfSq[ipt], "PbPb","pf");// #frac{dN}{dp_{T}}#frac{1}{T_{AA}}","pl");
      leg1->Draw();
    }
    if ( ipt == lowPtBin ) {
    drawText("#it{pp} 25 pb^{-1}, PbPb 0.49 nb^{-1}",0.35,0.83,1,15);
    //    drawText("PbPb 0.49 nb^{-1}",0.4,0.78,1,15);
    }
    if ( ipt==lowPtBin)  drawBin(xBin,ipt,"GeV",0.35,0.73,1,16);
    else drawBin(xBin,ipt,"GeV",0.35,0.73,1,16);
    gPad->RedrawAxis();
    
  }

  
  c1->Update();
  c1->SaveAs(Form("raaResults/RAA_2d_optX%d_optY%d_icent%d_NominalIter.pdf",optX,optY,icent));

  TCanvas* c2 = new TCanvas("raapt","",400,400);
  if ( icent == 0 ) handsomeTH1(hRAApt,2);
  if ( icent == 3 ) handsomeTH1(hRAApt,4);
  if ( icent == 6 ) handsomeTH1(hRAApt,8);
  hRAApt->SetAxisRange(127,495,"X");
  hRAApt->SetAxisRange(0,1.55,"Y");
  hRAApt->Draw();
  drawCentrality(kPbPb, icent, 0.37,0.83,1,20);
  jumSun(125,1,500,1);
  //  jumSun(125,0.5,500,0.5);
  c2->SaveAs(Form("raa_massIntegrated_icent%d.pdf",icent));
}



void getDATAforRAA(int kSample, int icent, int ix, int nIter, TH1D* hdataRawSq, TH1D* hdataUnfSq) {
  TFile * fin = new TFile(Form("unfSpectra/kSample%d_matrixRwt1_spectraRwt1.root",kSample));
  TH1D* hUnf = (TH1D*)fin->Get(Form("hdataUnf1d_icent%d_ix%d_iter%d",icent,ix,nIter));
  //  TH1D* hRaw = (TH1D*)fin->Get(Form("hdataRaw1d_icent%d_ix%d_iter%d",icent,ix,nIter));

  hdataUnfSq->Reset();
  hdataUnfSq->Add(hUnf);
  //  hdataRawSq->Reset();
  //  hdataRawSq->Add(hRaw);


}


JetSys getFinalSys(int icent, int nVar) {
  int optX = 1;
  int nXbins;  double xBin[30];
  getXbin(nXbins, xBin, optX);

  int lowPtBin = 6;
  int highPtBin = nXbins-1;

  TH1D* hpp[30];
  TH1D* hpbpb[30];
  TH1D* hraa[30];
  
  JetSys ret;
  TFile* fsys = new TFile(Form("sysSpectra/systematics_icent%d.root",icent));
  for ( int ix = lowPtBin ; ix<= highPtBin ; ix++)  {
    if ( nVar == 1)  {
      hpp[ix] = (TH1D*)fsys->Get(Form("sys_finalPlus_pp_ix%d",ix));
      hpbpb[ix] = (TH1D*)fsys->Get(Form("sys_finalPlus_pbpb_ix%d",ix));
      hraa[ix] = (TH1D*)fsys->Get(Form("sys_finalPlus_raa_ix%d",ix));
    }
    else if ( nVar == -1)  {
      hpp[ix] = (TH1D*)fsys->Get(Form("sys_finalMinus_pp_ix%d",ix));
      hpbpb[ix] = (TH1D*)fsys->Get(Form("sys_finalMinus_pbpb_ix%d",ix));
      hraa[ix] = (TH1D*)fsys->Get(Form("sys_finalMinus_raa_ix%d",ix));
    }
    else {
      cout << "No option for nVar = "  << nVar << endl;
    }
    ret.pp[ix] = hpp[ix];
    ret.pbpb[ix] = hpbpb[ix];
    ret.raa[ix] = hraa[ix];
  }
  return ret;
}


void narrowSys( TH1D* hsys, double xlow, double xhigh) { 
  for ( int ii=0 ; ii<=hsys->GetNbinsX() ; ii++) {
    double xVal = hsys->GetBinCenter(ii);
    if ( xVal < xlow )    hsys->SetBinContent(ii,0);
    if ( xVal > xhigh )   hsys->SetBinContent(ii,0);
  }
}



