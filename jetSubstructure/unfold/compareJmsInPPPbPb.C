#include <iostream>
using std::cout;
using std::endl;

#include "TRandom.h"
#include "TH1D.h"
#include "../getSdHists.C"
#include "../ntupleDefinition_v50.h"
#include "../commonUtility.h"
#include "../jzWeight.h"
#include "unfoldingUtil.h"
#include "../JssUtils.h"
#include <TPaletteAxis.h>
#include <TCut.h>
double statUsed = 0001;



void compareJmsInPPPbPb(  int icent = 0,   int kOpt=1, int optX = 1,   int optY =2 ) { 

  
  int nXbins;
  double xBin[30];
  getXbin(nXbins, xBin, optX);

  int lowPtBin = 4;
  int highPtBin = nXbins-1;

  int nYbins ;
  double yBin[30] ;
  getYbin(nYbins, yBin, optY);
  
  TH1::SetDefaultSumw2();
  TH1D* hDistJes0[20][20];
  TH1D* hDistJes1[20][20];
  TH1D* hDistJes0fit[20][20];
  TH1D* hDistJes1fit[20][20];

  TH1D* hJMS0[20];
  TH1D* hJMS1[20];
  TH1D* hJMR0[20];
  TH1D* hJMR1[20];

  
  TFile* fmc0 = new TFile(Form("jmsCalib/jms_kSample0_icent%d_optX%d_optY%d.root",icent,optX,optY));
  for ( int ix = 1 ; ix <= nXbins ; ix++) {
    for ( int iy = 1 ; iy <= nYbins ; iy++)  {
      hDistJes0[ix][iy] = (TH1D*)fmc0->Get(Form("hDistJes_ix%d_iy%d",ix,iy));
      hDistJes0[ix][iy]->SetXTitle("[m/p_{T}]_{Reco}^{2} / [m/p_{T}]_{Truth}^{2}");
      scaleInt(hDistJes0[ix][iy]);
    }
  }

  TFile* fmc1 = new TFile(Form("jmsCalib/jms_kSample1_icent%d_optX%d_optY%d.root",icent,optX,optY));
  for ( int ix = 1 ; ix <= nXbins ; ix++) {
    for ( int iy = 1 ; iy <= nYbins ; iy++)  {
      hDistJes1[ix][iy] = (TH1D*)fmc1->Get(Form("hDistJes_ix%d_iy%d",ix,iy));
      hDistJes1[ix][iy]->SetXTitle("[m/p_{T}]_{Reco}^{2} / [m/p_{T}]_{Truth}^{2}");
      scaleInt(hDistJes1[ix][iy]);
    }
  }
  
  for ( int ix = 5 ; ix <= nXbins ; ix++) {
    TCanvas* cDist = new TCanvas("cDist","",1200,500);
    cDist->Divide(4,2);

    hJMS0[ix] = new TH1D(Form("hJMS0_ix%d",ix),";[m/p_{T}]_{Truth}; < [m/p_{T}]_{Reco}^{2} / [m/p_{T}]_{Truth}^{2} >",nYbins, yBin);
    hJMS1[ix] = (TH1D*)hJMS0[ix]->Clone(Form("hJMS1_ix%d",ix));

    for ( int iy = 2 ; iy <= nYbins ; iy++)  {
      cDist->cd(iy-1);
      if (kOpt==1) {
	hDistJes0[ix][iy]->GetFunction("gaus")->SetBit(TF1::kNotDraw);
	hDistJes1[ix][iy]->GetFunction("gaus")->SetBit(TF1::kNotDraw);
	
	float mean =  hDistJes0[ix][iy]->GetFunction("gaus")->GetParameter(1) ;
	float meanErr = hDistJes0[ix][iy]->GetFunction("gaus")->GetParError(1);
	hJMS0[ix]->SetBinContent(iy,mean);
	hJMS0[ix]->SetBinError(iy,meanErr);
	
	mean =  hDistJes1[ix][iy]->GetFunction("gaus")->GetParameter(1) ;
	meanErr = hDistJes1[ix][iy]->GetFunction("gaus")->GetParError(1);
	hJMS1[ix]->SetBinContent(iy,mean);
	hJMS1[ix]->SetBinError(iy,meanErr);

      }

      cleverRange(hDistJes0[ix][iy],1.5);
      
      handsomeTH1(hDistJes0[ix][iy],1);
      handsomeTH1(hDistJes1[ix][iy],2);
      if ( kOpt==1) {
	hDistJes0[ix][iy]->Draw("");
	hDistJes1[ix][iy]->Draw("same");
      }
      else { 
	handsomeTH1(hDistJes0[ix][iy],0);
	//	hDistJes0[ix][iy]->Draw();
	hDistJes0fit[ix][iy] = (TH1D*)hDistJes0[ix][iy]->GetFunction("gaus")->GetHistogram();
	hDistJes1fit[ix][iy] = (TH1D*)hDistJes1[ix][iy]->GetFunction("gaus")->GetHistogram();
	scaleInt(hDistJes0fit[ix][iy]);
	scaleInt(hDistJes1fit[ix][iy]);
	handsomeTH1(hDistJes0fit[ix][iy],1);
	handsomeTH1(hDistJes1fit[ix][iy],2);
	cleverRange(hDistJes0fit[ix][iy],1.5);
	hDistJes0fit[ix][iy]->SetXTitle("[m/p_{T}]_{Reco}^{2} / [m/p_{T}]_{Truth}^{2}");
	hDistJes0fit[ix][iy]->Draw();
	hDistJes1fit[ix][iy]->Draw("same");
      }
      drawBinPt(xBin,ix,"GeV", 0.35 ,0.88,1,18);
      drawBinMpt(yBin,iy,"", 0.35 ,0.8,1,18);
      if ( iy==2)  drawText("pp",0.6,0.65,1,15);
      if ( iy==2)  drawCentrality(kPbPb,icent,0.6,0.56,2,15);
    }
    cDist->SaveAs(Form("jmsCalib/pp_vs_pbpb_m2scale_pt%d_icent%d_opt%d.png",ix,icent,kOpt));
  }
  
  TCanvas* cjms = new TCanvas("cjms","",1000,600);
  int pt1 = 5;
  int pt2 = 11;
  cjms->Divide(2,2);
  cjms->cd(1);
  cleverRange(hJMS0[pt1],1.5);
  handsomeTH1(hJMS0[pt1],1);
  handsomeTH1(hJMS1[pt1],2);
  hJMS0[pt1]->SetAxisRange(0.0001,0.3,"X");
  hJMS0[pt1]->DrawCopy("hist");
  hJMS1[pt1]->DrawCopy("same e");
  drawBinPt(xBin,pt1,"GeV", 0.5 ,0.88,1,18);
  drawText("pp",0.5,0.75,1,18);
  drawCentrality(kPbPb,icent,0.5,0.68,2,18);

  cjms->cd(3);
  hJMS1[pt1]->Divide(hJMS0[pt1]);
  hJMS1[pt1]->SetAxisRange(0.5,1.5,"Y");
  hJMS1[pt1]->SetAxisRange(0.0001,0.3,"X");
  hJMS1[pt1]->SetYTitle("PbPb/pp");
  hJMS1[pt1]->Draw();
  onSun(0,1,0.35,1);

  cjms->cd(2);
  cleverRange(hJMS0[pt2],1.5);
  handsomeTH1(hJMS0[pt2],1);
  handsomeTH1(hJMS1[pt2],2);
  hJMS0[pt2]->SetAxisRange(0.0001,0.3,"X");
  hJMS0[pt2]->DrawCopy("hist");
  hJMS1[pt2]->DrawCopy("same e");
  drawBinPt(xBin,pt2,"GeV", 0.35 ,0.88,1,18);

  cjms->cd(4);
  hJMS1[pt2]->Divide(hJMS0[pt2]);
  hJMS1[pt2]->SetAxisRange(0.5,1.5,"Y");
  hJMS1[pt2]->SetAxisRange(0.0001,0.3,"X");
  hJMS1[pt2]->SetYTitle("PbPb/pp");
  hJMS1[pt2]->Draw();
  onSun(0,1,0.35,1);

  cjms->SaveAs(Form("jmsCalib/pp_vs_pbpb_Summary_m2scale_icent%d.png",icent));

}
