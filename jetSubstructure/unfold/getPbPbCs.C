
#include "../TAA.h"
#include "systematicsTool.h"

void getDATAforRAA(int kSample=0, int icent=0, int ix=0, int nIter=0,  TH1D* hdataUnfSq=0);
JetSys getFinalSys(int icent =0, int nVar=0);  
void narrowSys( TH1D* hsys=0, double xlow=0, double xhigh=0);


void getPbPbCs(int optX=1, int optY=2 ) {

  int nIterPP = getRefIter(0,0);
  int nIterAA = nIterPP; 
  
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

  
  int vCent[3] = {0,3,6};

  TH1D* hPPUnfSq[30][4]; // 
  TH1D* hPbPbUnfSq[30][4]; // 
  
  JetSys sysPlus[4];
  JetSys sysMinus[4];
  const int nCols = 3; 
  for ( int ii = 0 ; ii < nCols ; ii++) { 
    sysPlus[ii] = getFinalSys( vCent[ii] , 1);
    sysMinus[ii] = getFinalSys( vCent[ii] , -1);
  }
  
  TH1D* hRAA[30][4]; 
  
  for ( int ix = lowPtBin ; ix<= highPtBin ; ix++)  {
  }
  
  TCanvas *c1 = new TCanvas("c1", "",4,45,1050,1200);
  makeMultiPanelCanvas(c1,nCols, nPtPannels, 0.0, 0.01, 0.15, 0.25, 0.05);
  //c1->Divide(nPtPannels, 2);
  
  for ( int ii = 0 ; ii < nCols ; ii++) 	{ 
    for ( int ipt = lowPtBin ; ipt<= highPtBin ; ipt++)  {
      
      if (   (ipt == highPtBin) && ( vCent[ii] >= 5) )  continue;
      
      hPPUnfSq[ipt][ii] = (TH1D*)tempHistYsq->Clone(Form("hPPUnfSq_ipt%d",ipt));
      hPbPbUnfSq[ipt][ii] = (TH1D*)tempHistYsq->Clone(Form("hPbPbUnfSq_ipt%d",ipt));
      getDATAforRAA(kPP,   0, ipt, nIterPP,   hPPUnfSq[ipt][ii]);
      getDATAforRAA(kPbPb, vCent[ii], ipt, nIterAA, hPbPbUnfSq[ipt][ii]);
      
      narrowSys( sysPlus[ii].pp[ipt], 0, 0.24);
      narrowSys( sysPlus[ii].pbpb[ipt], 0, 0.24);
      narrowSys( sysPlus[ii].raa[ipt], 0, 0.24);
      narrowSys( sysMinus[ii].pp[ipt], 0, 0.24);
      narrowSys( sysMinus[ii].pbpb[ipt], 0, 0.24);
      narrowSys( sysMinus[ii].raa[ipt], 0, 0.24);

      CsScalePP(hPPUnfSq[ipt][ii]);
      CsScalePbPb(hPbPbUnfSq[ipt][ii], vCent[ii] );
      
      hRAA[ipt][ii] = (TH1D*)hPbPbUnfSq[ipt][ii]->Clone(Form("hraa_ipt%d_ii%d",ipt,ii));
      hRAA[ipt][ii]->Divide(hPPUnfSq[ipt][ii]);
      
    }
  }
  
  for ( int ii = 0 ; ii < nCols ; ii++)   {
    for ( int ipt = lowPtBin ; ipt<= highPtBin ; ipt++)  {
      c1->cd(ii+1+ (ipt-lowPtBin)*nCols);

      if ( ipt == lowPtBin ) 
	c1->cd(ii+1+ (ipt-lowPtBin)*nCols)->SetTopMargin(0.03);

      c1->cd(ii+1+ (ipt-lowPtBin)*nCols)->SetRightMargin(0.01);
      if ( ii == 0) {
        c1->cd(ii+1+ (ipt-lowPtBin)*nCols)->SetLeftMargin(0.28);
        c1->cd(ii+1+ (ipt-lowPtBin)*nCols)->SetRightMargin(0.05);
      }
      else if ( ii == 1) 
        c1->cd(ii+1+ (ipt-lowPtBin)*nCols)->SetLeftMargin(0.23);
      else if ( ii == 2) 
        c1->cd(ii+1+ (ipt-lowPtBin)*nCols)->SetLeftMargin(0.25);

      //      if ( ipt != lowPtBin) 
      //	c1->cd(ii+1+ (ipt-lowPtBin)*nCols)->SetTopMargin(0.15);
      
      if (   (ipt == highPtBin) && ( vCent[ii] >= 5) )  {
        c1->cd(ii+1+ (ipt-lowPtBin)*nCols)->SetBottomMargin(0.99999);
	TH1D* dummyHist = (TH1D*)hPbPbUnfSq[ipt][ii-1]->Clone("dummyhist");
        dummyHist->Reset();
        dummyHist->SetAxisRange(2.1,2.4,"Y");
        dummyHist->GetYaxis()->SetLabelColor(0);
        dummyHist->SetYTitle("");
        dummyHist->DrawCopy();
        continue;

      }
      
      //      hPbPbUnfSq[ipt][ii]->SetAxisRange(0.001,0.239,"X");
      //      hPbPbUnfSq[ipt][ii]->SetXTitle("m^{jet}/p_{T}^{jet}");
      //      hPbPbUnfSq[ipt][ii]->SetYTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
      handsomeTH1(hPPUnfSq[ipt][ii],1);
      hPPUnfSq[ipt][ii]->SetMarkerStyle(24);
      handsomeTH1(hPbPbUnfSq[ipt][ii],1);
      //    scaleInt(hPPUnfSq[ipt][ii]);
      //    scaleInt(hPbPbUnfSq[ipt][ii]);

      // CS -> dN/dm
      hPbPbUnfSq[ipt][ii]->Scale( getTaa(vCent[ii]) / 1000.);

      //      if ( ii==2)   {
      //	hPbPbUnfSq[ipt][ii]->Scale(100);
      //      }
      TGaxis::SetMaxDigits(8);

      hPbPbUnfSq[ipt][ii]->SetYTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{d(m/p_{T})}");

      if ( (ipt == lowPtBin)) {
	hPbPbUnfSq[ipt][ii]->Scale(1000);
	hPbPbUnfSq[ipt][ii]->SetYTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{d(m/p_{T})} #times10^{3}");
      }
      else if ( (ipt == lowPtBin+1)) {
	hPbPbUnfSq[ipt][ii]->Scale(10000);
	hPbPbUnfSq[ipt][ii]->SetYTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{d(m/p_{T})} #times10^{4}");
      }
      else if ( (ipt == lowPtBin+2)) {
	hPbPbUnfSq[ipt][ii]->Scale(100000);
	hPbPbUnfSq[ipt][ii]->SetYTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{d(m/p_{T})} #times10^{5}");
      }
      else if ( (ipt == lowPtBin+3)) {
	hPbPbUnfSq[ipt][ii]->Scale(100000);
	hPbPbUnfSq[ipt][ii]->SetYTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{d(m/p_{T})} #times10^{5}");
      }
      else  {
	hPbPbUnfSq[ipt][ii]->Scale(1000000);
	hPbPbUnfSq[ipt][ii]->SetYTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{d(m/p_{T})} #times10^{6}");
      } 
      

      //      else if ( ipt > lowPtBin+3)    {
      //	hPbPbUnfSq[ipt][ii]->Scale(1000000);
      //	hPbPbUnfSq[ipt][ii]->SetYTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{d(m/p_{T})} #times10^{6}");
      //      }

      double maxY = cleverRange(hPbPbUnfSq[ipt][ii],2,0.000001);
      hPbPbUnfSq[ipt][ii]->SetAxisRange(0, 0.2399,"X");
      hPbPbUnfSq[ipt][ii]->SetAxisRange(0.000000, maxY,"Y");
      if ( (ipt == lowPtBin) && (ii==0) )
	hPbPbUnfSq[ipt][ii]->SetAxisRange(0.000000, maxY*1.1,"Y");
      hPbPbUnfSq[ipt][ii]->SetNdivisions(505,"X");
      hPbPbUnfSq[ipt][ii]->SetNdivisions(505,"Y");
      hPbPbUnfSq[ipt][ii]->GetYaxis()->SetDrawOption("G");
      fixedFontHist(hPbPbUnfSq[ipt][ii],2.5,2.5,20);
      hPbPbUnfSq[ipt][ii]->GetXaxis()->SetTitleOffset(5.5);
      hPbPbUnfSq[ipt][ii]->GetYaxis()->SetTitleSize(17);
      if ( ii == 0 ) hPbPbUnfSq[ipt][ii]->GetYaxis()->SetTitleOffset(6);
      if ( ii == 1 ) hPbPbUnfSq[ipt][ii]->GetYaxis()->SetTitleOffset(6);
      if ( ii == 2 ) hPbPbUnfSq[ipt][ii]->GetYaxis()->SetTitleOffset(6);
      hPbPbUnfSq[ipt][ii]->Draw();
      drawSysUpDown( hPbPbUnfSq[ipt][ii], sysPlus[ii].pbpb[ipt],  sysMinus[ii].pbpb[ipt], kCyan+1);
      hPbPbUnfSq[ipt][ii]->Draw("same");
      
      if ( ii==0)   drawPatch(0,0,0.28,0.06);
      if ( ii==1)   drawPatch(0,0,0.22,0.06);
      else    drawPatch(0,0,0.25,0.06);

      if ( (ipt==highPtBin) && (ii==0) ) 
	drawPatch(0,0.95,0.8,1);
      if ( (ipt==highPtBin-1) && (ii==2) ) 
	drawPatch(0,0.95,0.8,1);


      if  (ipt == lowPtBin ) { 
	if ( ii == 0 ) { 
	  ATLASLabel(0.31,0.86,"Preliminary",0.12,0.21);
	  drawText("Pb+Pb #sqrt{#font[12]{s_{NN}}} = 5.02 TeV, 0.49 nb^{-1}",0.31,0.76,1,14);
	}
	if ( ii == 1 ) 
	  ATLASLabel(0.26,0.86,"Preliminary",0.12,0.243);
	if ( ii == 2 ) 
	  ATLASLabel(0.29,0.86,"Preliminary",0.12,0.235);

      }
      if (ipt == lowPtBin ) {
	if ( ii==0) 
	  drawCentrality(kPbPb, vCent[ii], 0.31,0.64,1,18);
	if ( ii==1) 
	  drawCentrality(kPbPb, vCent[ii], 0.26,0.73,1,18);
	if ( ii==2) 
	  drawCentrality(kPbPb, vCent[ii], 0.29,0.73,1,18);

      }
      if ( ii < 1000 ) {
	if ( ( ii==2 ) && ( ipt == highPtBin-1) ) {} 
	else if ( (ipt == lowPtBin) && ( (vCent[ii] ==3)||( vCent[ii]==6) ))  
	  drawBinPt(xBin,ipt,"GeV", 0.31 ,0.6,1,16);
	else if (ipt == lowPtBin )
          drawBinPt(xBin,ipt,"GeV", 0.31 ,0.55,1,16);
        else if (ipt != highPtBin )
          drawBinPt(xBin,ipt,"GeV", 0.31 ,0.78,1,16);
        else if (ipt == highPtBin )
          drawBinPt(xBin,ipt,"GeV", 0.31 ,0.85,1,16);
      }
      if ( ii==2 ) {
        if ( ipt == highPtBin-1)
          drawBinPt2(xBin,ipt,"GeV", 0.31 ,0.8,1,16);
      }
      gPad->RedrawAxis();
      //      if ( (ii==0) && (ipt > lowPtBin) )
      //	drawPatch(0.,0.955, 0.5, 1);
    }}
  // lumi uncertainty 
  // double lumiUnc = getLumiRelErr(icent);
  // drawErrorBox( 0, 1-lumiUnc, 0.025, 1+lumiUnc, 1);

  c1->SaveAs("PbPbfigure_confnote.pdf");
  
}



void getDATAforRAA(int kSample, int icent, int ix, int nIter, TH1D* hdataUnfSq) {
  if ( icent <=5) { 
    TFile * fin = new TFile(Form("unfSpectra/kSample%d_matrixRwt1_spectraRwt1.root",kSample));
    TH1D* hUnf = (TH1D*)fin->Get(Form("hdataUnf1d_icent%d_ix%d_iter%d",icent,ix,nIter));
    hdataUnfSq->Reset();
    hdataUnfSq->Add(hUnf);
  }
  else { 
    TFile * fin = new TFile(Form("../unfoldPeriBin/unfSpectra/kSample%d_matrixRwt1_spectraRwt1.root",kSample));
    TH1D* hUnf = (TH1D*)fin->Get(Form("hdataUnf1d_icent%d_ix%d_iter%d",icent,ix,nIter));
    hdataUnfSq->Reset();
    hdataUnfSq->Add(hUnf);
  }
  
}


JetSys getFinalSys(int icent, int nVar) {
  int optX = 1;
  int nXbins;  double xBin[30];
  getXbin(nXbins, xBin, optX);

  int lowPtBin = 6;
  int highPtBin = nXbins-1;
  if ( icent >= 5) 
    int highPtBin = nXbins-2;
  

  TH1D* hpp[30];
  TH1D* hpbpb[30];
  TH1D* hraa[30];
  
  JetSys ret;
  TFile* fsys;
  if ( icent < 5)   fsys = new TFile(Form("sysSpectra/systematics_icent%d_smoothened.root",icent));
  else              fsys = new TFile(Form("../unfoldPeriBin/sysSpectra/systematics_icent%d_smoothened.root",icent));

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



