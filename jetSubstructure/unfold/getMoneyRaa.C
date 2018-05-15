#include "../TAA.h"
#include "systematicsTool.h"

void getDATAforRAA(int kSample=0, int icent=0, int ix=0, int nIter=0,  TH1D* hdataUnfSq=0);
JetSys getFinalSys(int icent =0, int nVar=0);  
void narrowSys( TH1D* hsys=0, double xlow=0, double xhigh=0);


void getMoneyRaa(int optX=1, int optY=2 ) {

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
  if ( optY == 2 ) tempHistYsq = new TH1D("tempHistY",";m^{jet}/p_{T}^{jet};",nYbins,yBin);


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
  
  TCanvas *c1 = new TCanvas("c1", "",4,45,900,1200);
  //  makeMultiPanelCanvas(c1,nPtPannels, nCols, 0.0, 0.01, 0.35, 0.25, 0.05);
  makeMultiPanelCanvas(c1,nCols, nPtPannels, 0.0, 0.01, 0.2, 0.25, 0.05);
  //c1->Divide(nPtPannels, 2);
  
  for ( int ii = 0 ; ii < nCols ; ii++) 	{ 
    for ( int ipt = lowPtBin ; ipt<= highPtBin ; ipt++)  {
      
      if (   (ipt == highPtBin) && ( vCent[ii] >= 5) )  continue;
      
      hPPUnfSq[ipt][ii] = (TH1D*)tempHistYsq->Clone(Form("hPPUnfSq_ipt%d",ipt));
      hPbPbUnfSq[ipt][ii] = (TH1D*)tempHistYsq->Clone(Form("hPbPbUnfSq_ipt%d",ipt));
      getDATAforRAA(kPP,   vCent[ii], ipt, nIterPP,   hPPUnfSq[ipt][ii]);
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

      if ( ipt == lowPtBin) 
	c1->cd(ii+1+ (ipt-lowPtBin)*nCols)->SetTopMargin(0.02);
      
      c1->cd(ii+1+ (ipt-lowPtBin)*nCols)->SetRightMargin(0.01);
      if ( ii == 0)     
	c1->cd(ii+1+ (ipt-lowPtBin)*nCols)->SetLeftMargin(0.32);
      else 
	c1->cd(ii+1+ (ipt-lowPtBin)*nCols)->SetLeftMargin(0.15);
      
      if (   (ipt == highPtBin) && ( vCent[ii] >= 5) )  { 
	c1->cd(ii+1+ (ipt-lowPtBin)*nCols)->SetBottomMargin(0.99999);
	
	TH1D* dummyHist = (TH1D*)hRAA[ipt][ii-1]->Clone("dummyhist");
	dummyHist->Reset();
	dummyHist->SetAxisRange(2.1,2.4,"Y");
	dummyHist->GetYaxis()->SetLabelColor(0);
	dummyHist->DrawCopy();
	//	drawPatch(0,0.8,0.133,1.0);
	continue;
	
      }
      
      // CS -> dN/dm
      hPbPbUnfSq[ipt][ii]->Scale( getTaa(vCent[ii]) / 1000.);

      if ( ii==2)   {
	hPbPbUnfSq[ipt][ii]->Scale(100);
      }

      hRAA[ipt][ii]->SetAxisRange(0, 0.2399,"X");
      hRAA[ipt][ii]->SetAxisRange(0.01, 2.19,"Y");
      hRAA[ipt][ii]->SetNdivisions(505,"X");
      hRAA[ipt][ii]->SetNdivisions(505,"Y");
      fixedFontHist(hRAA[ipt][ii],2.5,2.5,20);
      hRAA[ipt][ii]->GetXaxis()->SetTitleOffset(5.5);
      hRAA[ipt][ii]->SetYTitle("R_{AA}");
      if ( ii>0)       hRAA[ipt][ii]->SetYTitle("");
      hRAA[ipt][ii]->GetYaxis()->SetTitleSize(17);
      hRAA[ipt][ii]->GetYaxis()->SetTitleOffset(5);
      hRAA[ipt][ii]->Draw();
      drawSysUpDown( hRAA[ipt][ii], sysPlus[ii].raa[ipt],  sysMinus[ii].raa[ipt], kOrange);
      // lumi uncertainty
      double lumiUnc = getLumiRelErr(vCent[ii]);
      drawErrorBox( 0, 1-lumiUnc, 0.025, 1+lumiUnc, 1);
      hRAA[ipt][ii]->Draw("same");
      
      
      if (ipt == lowPtBin ) {  
	if ( ii == 0 ) 
	  ATLASLabel(0.39,0.86,"Internal",0.12,0.20);
	if ( ii == 1 ) 
	  ATLASLabel(0.245,0.86,"Internal",0.12,0.25);
	if ( ii == 2 ) 
	  ATLASLabel(0.245,0.86,"Internal",0.12,0.24);


      }
      if (ipt == lowPtBin ) {
	if ( ii == 0 ) drawCentrality(kPbPb, vCent[ii], 0.39,0.73,1,20);
	if ( ii == 1 ) drawCentrality(kPbPb, vCent[ii], 0.245,0.73,1,20);
	if ( ii == 2 ) drawCentrality(kPbPb, vCent[ii], 0.245,0.73,1,20);
      }
      
      if ( ii == 0 ) {
	if (ipt < highPtBin )	
	  drawBinPt(xBin,ipt,"GeV", 0.39 ,0.58,1,18);
	if (ipt == highPtBin )
	  drawBinPt(xBin,ipt,"GeV", 0.39 ,0.68,1,18);
      }
      if ( ii==2 ) { 
	if ( ipt == highPtBin-1)
	  drawBinPt2(xBin,ipt,"GeV", 0.4 ,0.8,1,18);
      }
      jumSun(0,1,0.24,1);
      gPad->RedrawAxis();
      
      //      if ( (ii==0) && (ipt > lowPtBin) )
      //	drawPatch(0.,0.955, 0.5, 1);
    }}
  // lumi uncertainty 
  // double lumiUnc = getLumiRelErr(icent);
  // drawErrorBox( 0, 1-lumiUnc, 0.025, 1+lumiUnc, 1);
  
  c1->SaveAs("raaFigure_confNote.pdf");
}



void getDATAforRAA(int kSample, int icent, int ix, int nIter, TH1D* hdataUnfSq) {
  if ( icent <=4) { 
    TFile * fin = new TFile(Form("unfSpectra/kSample%d_matrixRwt1_spectraRwt1.root",kSample));
    if ( kSample == kPP )
      icent = 0 ;
    TH1D* hUnf = (TH1D*)fin->Get(Form("hdataUnf1d_icent%d_ix%d_iter%d",icent,ix,nIter));
    hdataUnfSq->Reset();
    hdataUnfSq->Add(hUnf);
  }
  else { 
    TFile * fin = new TFile(Form("../unfoldPeriBin/unfSpectra/kSample%d_matrixRwt1_spectraRwt1.root",kSample));
    if ( kSample == kPP )
      icent = 0 ;
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
  if ( icent < 5)   fsys = new TFile(Form("sysSpectra/systematics_icent%d.root",icent));
  else              fsys = new TFile(Form("../unfoldPeriBin/sysSpectra/systematics_icent%d.root",icent));

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



