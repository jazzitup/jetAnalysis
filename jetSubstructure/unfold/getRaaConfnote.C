#include "../TAA.h"
#include "systematicsTool.h"

void getDATAforRAA(int kSample=0, int icent=0, int ix=0, int nIter=0,  TH1D* hdataUnfSq=0);
JetSys getFinalSys(int icent =0, int nVar=0);  
void narrowSys( TH1D* hsys=0, double xlow=0, double xhigh=0);


void getRaaConfnote(int optX=1, int optY=2 ) {

  int nIterPP = getRefIter(0,0);
  int nIterAA = nIterPP; 
  
  int nXbins;
  double xBin[30];
  getXbin(nXbins, xBin, optX);
  TH1D* tempHistPt = new TH1D("tempHistPt",";p_{T} (GeV/c);",nXbins,xBin);
  double xBin2[30] = {20,40,63.096, 82., 100.000, 125.892,  158.488,  199.525,  251.186,  316.224,  500.};
  TH1D* tempHistPt2 = new TH1D("tempHistPt",";p_{T} (GeV/c);",10,xBin2);  

  int nYbins ;
  double yBin[30] ;
  getYbin(nYbins, yBin, optY);
  TH1D* tempHistYsq;
  if ( optY == 1 ) tempHistYsq = new TH1D("tempHistY",";mass(GeV);",nYbins,yBin);
  if ( optY == 2 ) tempHistYsq = new TH1D("tempHistY",";m/p_{T};",nYbins,yBin);


  int lowPtBin = 6;
  int highPtBin = 11;
  int nPtPannels = highPtBin-lowPtBin+1;

  int lowMptBin = 2;
  int highMptBin = 8;
  int nMptPannels = highMptBin-lowMptBin+1;


  

  
  int vCent[3] = {0,3,6};

  TH1D* hPPUnfSq[30][4]; // 
  TH1D* hPbPbUnfSq[30][4]; // 
  
  TH1D* hRAA[30][4];
  
  JetSys sysPlus[4];
  JetSys sysMinus[4];
  const int nCols = 3; 
  for ( int ii = 0 ; ii < nCols ; ii++) { 
    sysPlus[ii] = getFinalSys( vCent[ii] , 1);
    sysMinus[ii] = getFinalSys( vCent[ii] , -1);
  }

  JetSys sysPlusM[4];
  JetSys sysMinusM[4];

  for ( int ii = 0 ; ii < nCols ; ii++) { 
    for ( int im = lowMptBin ; im<=highMptBin; im++) {

      TH1D* temphist = tempHistPt;
      if  ( vCent[ii] >= 5)  temphist = tempHistPt2;

      sysPlusM[ii].pp[im] =  (TH1D*)temphist->Clone(Form("sysPlusM_im%d_ii%d_pp",im,ii));	  
      sysMinusM[ii].pp[im] =  (TH1D*)temphist->Clone(Form("sysMinusM_im%d_ii%d_pp",im,ii));	  
      sysPlusM[ii].pbpb[im] =  (TH1D*)temphist->Clone(Form("sysPlusM_im%d_ii%d_pbpb",im,ii));	  
      sysMinusM[ii].pbpb[im] =  (TH1D*)temphist->Clone(Form("sysMinusM_im%d_ii%d_pbpb",im,ii));	  
      sysPlusM[ii].raa[im] =  (TH1D*)temphist->Clone(Form("sysPlusM_im%d_ii%d_raa",im,ii));	  
      sysMinusM[ii].raa[im] =  (TH1D*)temphist->Clone(Form("sysMinusM_im%d_ii%d_raa",im,ii));	  
      
      for ( int ipt = lowPtBin ; ipt<= highPtBin ; ipt++)  {
	if (   (ipt == highPtBin) && ( vCent[ii] >= 5) )  continue;
	cout << " ipt, ii, im = " << ipt <<", " << ii<<", " << im << endl;
	sysPlusM[ii].pp[im]->SetBinContent( ipt,   sysPlus[ii].pp[ipt]->GetBinContent(im));
	sysMinusM[ii].pp[im]->SetBinContent( ipt,   sysMinus[ii].pp[ipt]->GetBinContent(im));
	sysPlusM[ii].pbpb[im]->SetBinContent( ipt,   sysPlus[ii].pbpb[ipt]->GetBinContent(im));
	sysMinusM[ii].pbpb[im]->SetBinContent( ipt,   sysMinus[ii].pbpb[ipt]->GetBinContent(im));
	sysPlusM[ii].raa[im]->SetBinContent( ipt,   sysPlus[ii].raa[ipt]->GetBinContent(im));
	sysMinusM[ii].raa[im]->SetBinContent( ipt,   sysMinus[ii].raa[ipt]->GetBinContent(im));
      }
    }	
  }
  
  

  

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
      hPPUnfSq[ipt][ii]->Scale(0.001);
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
      if ( ipt == lowPtBin+1) {
        if ( vCent[ii]==0) {
	  drawText("#it{pp} #sqrt{#font[12]{s}} = 5.02 TeV, 25 pb^{-1}", 0.37, 0.89,1,15);
	  drawText("Pb+Pb #sqrt{#font[12]{s_{NN}}} = 5.02 TeV, 0.49 nb^{-1}",0.37,.78,1,15);
	}
      }
      if ( ii == 0 ) {
	if (ipt == lowPtBin )
	  drawBinPt(xBin,ipt,"GeV", 0.39 ,0.58,1,18);
	else if (ipt == lowPtBin+1 )
	  drawBinPt(xBin,ipt,"GeV", 0.39 ,0.63,1,18);
	else if  (ipt == highPtBin )
	  drawBinPt(xBin,ipt,"GeV", 0.39 ,0.88,1,18);
	else 
	  drawBinPt(xBin,ipt,"GeV", 0.39 ,0.85,1,18);


      }
      if ( ii == 1 ) {
	if  ( ipt == lowPtBin)
	  drawBinPt(xBin,ipt,"GeV", 0.2 ,0.58,1,18);
	else if  (ipt == highPtBin )
	  drawBinPt(xBin,ipt,"GeV", 0.2 ,0.88,1,18);
	else 
	  drawBinPt(xBin,ipt,"GeV", 0.2 ,0.85,1,18);
      }
      
if ( ii==2 ) { 
	if ( ipt == highPtBin-1)
	  drawBinPt2(xBin,ipt,"GeV", 0.3 ,0.8,1,18);
	else if ( ipt == lowPtBin)
	  drawBinPt(xBin,ipt,"GeV", 0.2 ,0.58,1,18);
	else 
	  drawBinPt(xBin,ipt,"GeV", 0.2 ,0.85,1,18);

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

  TCanvas *c2 = new TCanvas("c2", "",450,450);
  int theBin = lowPtBin;
  TH1D* htemp2 = (TH1D*)hRAA[theBin][0]->Clone("htemp2");
  htemp2->Reset();
  htemp2->SetAxisRange(0,1.81,"Y");
  fixedFontHist(htemp2,1.3,1.3,20);
  //  htemp2->GetXaxis()->SetTitleOffset(1.3);
  //  htemp2->GetYaxis()->SetTitleOffset(1.3);

  htemp2->SetXTitle("m/p_{T}");
  htemp2->SetYTitle("R_{AA}");
  htemp2->Draw();
  hRAA[theBin][0]->Draw("same");
  hRAA[theBin][0]->SetFillColor(kOrange);
  hRAA[theBin][1]->SetFillColor(kSpring-1);
  hRAA[theBin][2]->SetFillColor(kAzure-4);
  drawSysUpDown( hRAA[theBin][0], sysPlus[0].raa[theBin],  sysMinus[0].raa[theBin], kOrange);
  drawSysUpDown( hRAA[theBin][1], sysPlus[1].raa[theBin],  sysMinus[1].raa[theBin], kSpring-1);
  drawSysUpDown( hRAA[theBin][2], sysPlus[2].raa[theBin],  sysMinus[2].raa[theBin], kAzure-4);
  // lumi uncertainty
  drawErrorBox( 0.23, 1-0.054, 0.24, 1+0.054, 1);
  drawErrorBox( 0.22, 1-getTaaRelErr(0), 0.23, 1+getTaaRelErr(0), kOrange);
  drawErrorBox( 0.21, 1-getTaaRelErr(1), 0.22, 1+getTaaRelErr(1), kGreen+1);
  drawErrorBox( 0.20, 1-getTaaRelErr(2), 0.21, 1+getTaaRelErr(2), kBlue+1);
  hRAA[theBin][0]->Draw("same");
  hRAA[theBin][1]->Draw("same");
  hRAA[theBin][2]->Draw("same");
  jumSun(0,1,0.24,1);
  gPad->RedrawAxis();
  //  drawBinPt(xBin,theBin,"GeV", 0.55 ,0.88,1,18);

  TLegend *leg1 = new TLegend(0.4397321,0.7035294,0.9397321,0.9082353,NULL,"brNDC");
  easyLeg(leg1,"126 < p_{T} < 158 GeV/c");

  leg1->AddEntry(hRAA[theBin][2], "60% - 80%","pf");
  leg1->AddEntry(hRAA[theBin][1], "30% - 40%","pf");
  leg1->AddEntry(hRAA[theBin][0], " 0% - 10%","pf");
  leg1->Draw();
  //  ATLASLabel(0.33,0.86,"Internal",0.09,0.25);
  c2->SaveAs("raa_126-158GeV.pdf");

  TH1D* hRAAmpt[30][4];  // [m/pt bins][centrality]
  
  TCanvas *c3 = new TCanvas("c3", "",4,45,900,1200);
  //  makeMultiPanelCanvas(c3,nPtPannels, nCols, 0.0, 0.01, 0.35, 0.25, 0.05);
  makeMultiPanelCanvas(c3,nCols, nMptPannels, 0.0, 0.01, 0.2, 0.25, 0.05);
  //c3->Divide(nPtPannels, 2);
  
  for ( int ii = 0 ; ii < nCols ; ii++)   {
    for ( int im = lowMptBin ; im<=highMptBin; im++) { 
      TH1D* temphist = tempHistPt;
      if  ( vCent[ii] >= 5)  temphist = tempHistPt2;
    
      hRAAmpt[im][ii] = (TH1D*)temphist->Clone(Form("hRAAmpt_im%d_ii%d",im,ii));
      hRAAmpt[im][ii]->SetAxisRange(0,2.4,"Y");
      hRAAmpt[im][ii]->SetAxisRange(126,490,"X");
      for ( int ipt = lowPtBin ; ipt<= highPtBin ; ipt++)  {
	if (   (ipt == highPtBin) && ( vCent[ii] >= 5) )  continue;
	hRAAmpt[im][ii]->SetBinContent(ipt, hRAA[ipt][ii]->GetBinContent(im) );
	hRAAmpt[im][ii]->SetBinError(ipt, hRAA[ipt][ii]->GetBinError(im) );
      }    
      
      c3->cd(ii+1+ (im-lowMptBin)*nCols);
      
      if ( im == lowMptBin)
	c3->cd(ii+1+ (im-lowMptBin)*nCols)->SetTopMargin(0.02);
      
      c3->cd(ii+1+ (im-lowMptBin)*nCols)->SetRightMargin(0.01);
      if ( ii == 0)
	c3->cd(ii+1+ (im-lowMptBin)*nCols)->SetLeftMargin(0.32);
      else
	c3->cd(ii+1+ (im-lowMptBin)*nCols)->SetLeftMargin(0.15);


      fixedFontHist(hRAAmpt[im][ii],2.5,2.5,20);
      hRAAmpt[im][ii]->SetNdivisions(505,"X");
      hRAAmpt[im][ii]->SetNdivisions(505,"Y");
      hRAAmpt[im][ii]->SetYTitle("R_{AA}");
      hRAAmpt[im][ii]->GetXaxis()->SetTitleOffset(5.5);
      hRAAmpt[im][ii]->GetYaxis()->SetTitleOffset(3.4);
      hRAAmpt[im][ii]->SetAxisRange(0.01,2.25,"Y");
      
      hRAAmpt[im][ii]->Draw();
      drawSysUpDown( hRAAmpt[im][ii], sysPlusM[ii].raa[im],  sysMinusM[ii].raa[im], kOrange);
      hRAAmpt[im][ii]->Draw("same");

      if (im == lowMptBin ) {
        if ( ii == 0 ) drawCentrality(kPbPb, vCent[ii], 0.39,0.73,1,20);
        if ( ii == 1 ) drawCentrality(kPbPb, vCent[ii], 0.245,0.73,1,20);
        if ( ii == 2 ) drawCentrality(kPbPb, vCent[ii], 0.245,0.73,1,20);
      }

      if ( ii < 10 ) {

	if (im == lowMptBin )
	  drawBinMpt(yBin,im,"", 0.39 -(ii>0)*0.14,0.58,1,18);
        else if (im < highMptBin )
	  drawBinMpt(yBin,im,"", 0.39 -(ii>0)*0.14,0.65,1,18);
        else if (im == highMptBin )
          drawBinMpt(yBin,im,"", 0.39  -(ii>0)*0.14,0.78,1,18);
      }

      if ( im == lowMptBin+1) {
	if ( vCent[ii] ==0 ){ 
	  drawText("#it{pp} #sqrt{#font[12]{s}} = 5.02 TeV, 25 pb^{-1}", 0.37, 0.89,1,15);
	  drawText("Pb+Pb #sqrt{#font[12]{s_{NN}}} = 5.02 TeV, 0.49 nb^{-1}",0.37,.78,1,15);
	}
      }
      if (im == lowMptBin ) {
        if ( ii == 0 )
          ATLASLabel(0.39,0.86,"Internal",0.12,0.16);
        if ( ii == 1 )
          ATLASLabel(0.245,0.86,"Internal",0.12,0.2);
	if ( ii == 2 )
          ATLASLabel(0.245,0.86,"Internal",0.12,0.2);
      }
      double lumiUnc = getLumiRelErr(vCent[ii]);
      drawErrorBox( 125, 1-lumiUnc, 150, 1+lumiUnc, 1);      
      jumSun(125,1,500,1);
      gPad->RedrawAxis();

      if (  im == highMptBin ) 
	drawPatch(0.9,0,1,0.23);
    }
  }
  
  //  drawSysUpDown( hRAA[ipt][ii], sysPlus[ii].raa[ipt],  sysMinus[ii].raa[ipt], kOrange);
  c3->SaveAs("raaFigure_mpt.pdf");

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



