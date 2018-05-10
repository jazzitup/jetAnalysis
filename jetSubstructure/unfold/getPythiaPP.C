#include "../TAA.h"
#include "../getSdHists.C"
#include "../ntupleDefinition_v50.h"
#include "../commonUtility.h"
#include "../jzWeight.h"
#include "../commonUtility.h"
#include "../JssUtils.h"
#include "unfoldingUtil.h"
//#include "systematicsTool.h"

struct JetSys {
  TH1D* pp[20];
  TH1D* pbpb[20];
  TH1D* raa[20];
};

void resetJetSys(JetSys js, int lowX, int highX) {
  for ( int ix = lowX ; ix <= highX ; ix++) {
    js.pp[ix]->Reset();
    js.pbpb[ix]->Reset();
    js.raa[ix]->Reset();
  }

}

void makeUnityWithErr( TH1* h) { 
  for ( int ii = 0; ii <= h->GetNbinsX() ; ii++) {
    double err = h->GetBinError(ii);
    double val = h->GetBinContent(ii);
    h->SetBinContent(ii,1);
    h->SetBinError(ii, err/val);
  }
}

JetSys getFinalSys(int icent =0, int nVar=0);

void getMCresults(int kSample=0, int icent=0, int ix=0, int nIter=0,  bool matRwt=1, bool specRwt=0,  TH1D* hmcTruthSq=0, TH1D* hmcRawSq=0, TH1D* hmcUnfSq=0);
void getDATAresults(int kSample=0, int icent=0, int ix=0, int nIter=0,  bool matRwt=1, bool specRwt=0, TH1D* hdataRawSq=0, TH1D* hdataUnfSq=0);
void narrowSys( TH1D* hsys=0, double xlow=0, double xhigh=0);

void getPythiaPP(int kSample= kPP, int icent = 0, bool matRwt=1, int optX=1, int optY=2, bool applyMDJ=false) {
  
  bool specRwtData = 1;
  bool specRwtMc = 0;

  
  int nXbins;
  double xBin[30];
  getXbin(nXbins, xBin, optX);

  int nYbins ;
  double yBin[30] ;
  getYbin(nYbins, yBin, optY);
  TH1D* tempHistYsq;
  if ( optY == 1 ) tempHistYsq = new TH1D("tempHistY",";mass(GeV);",nYbins,yBin);
  if ( optY == 2 ) tempHistYsq = new TH1D("tempHistY",";m/p_{T};",nYbins,yBin);
  
  
  if ( (kSample == kPP) && (icent!=0) ) {
    cout << " pp sample must have cent = 0" << endl;
    return;
  }
  
  int lowPtBin = 6;
  int highPtBin = nXbins-1;
  //int lowPtBin = 7;
  //  int highPtBin = 7;
  int nPtPannels = highPtBin-lowPtBin+1;
  
  const int maxIter = 20;
  vector<int> vIter;  //2 3 4 6 8 10
  vector<int> color;  //2 3 4 6 8 10
  vector<int> mstyle;  //2 3 4 6 8 10
  
  
  JetSys sysPlus;
  JetSys sysMinus;
  sysPlus = getFinalSys(icent, 1);
  sysMinus = getFinalSys(icent, -1);

  //  vIter.push_back(1);   color.push_back (32);   mstyle.push_back(33);
  //  vIter.push_back(2);   color.push_back (kBlue-7);   mstyle.push_back(29);
  //  vIter.push_back(3);   color.push_back (32);
  //  vIter.push_back(4);   color.push_back (40);   mstyle.push_back(22);
  //  vIter.push_back(5);   color.push_back (43);
  vIter.push_back(6);    color.push_back (45);   mstyle.push_back(23);
  //  vIter.push_back(7);   color.push_back (48);
  //  vIter.push_back(8);   color.push_back (47);   mstyle.push_back(24);
  //  vIter.push_back(9);     color.push_back (50);
  //  vIter.push_back(10);   color.push_back (46);   mstyle.push_back(20);
  
  int refId = -1;
  for ( int ii = 0 ; ii< vIter.size() ; ii++) { 
    if ( vIter.at(ii) == getRefIter( kSample, icent) )
      refId = ii; 
  }
  
  //  int refId = vIter.size() -1;
  /*
  vIter.push_back(4);   color.push_back (1);
  vIter.push_back(1);   color.push_back (30);
  vIter.push_back(2);   color.push_back (28);
  vIter.push_back(6);    color.push_back (6);
  vIter.push_back(7);   color.push_back (2);
  vIter.push_back(8);   color.push_back (4);
  vIter.push_back(9);     color.push_back (kBlue+1);
  vIter.push_back(10);   color.push_back (kBlue+2);
  vIter.push_back(11);   color.push_back (kBlue+3);
  vIter.push_back(12);  color.push_back (kBlue+4);
  vIter.push_back(13);  color.push_back (kBlue+5);
  vIter.push_back(14);  color.push_back (kBlue+6);
  vIter.push_back(15);  color.push_back (kBlue+7);
  */

  if ( vIter.size() > maxIter)   {
    cout << "Not enough room in the array" << endl;
    return; 
  }

  TH1D* hmcUnfSq[20][maxIter]; //  pT, iteration
  TH1D* hmcTruthSq[20][maxIter]; 
  TH1D* hmcRawSq[20][maxIter]; 
  TH1D* hmcRatioSq[20][maxIter];

  TH1D* hraioMCtemp[20][maxIter];
  TH1D* hdataUnfSq[30][maxIter]; 
  TH1D* hdataRawSq[30][maxIter]; 
  TH1D* hdataRatioSq[30][maxIter];
  

  
  for ( int ix = lowPtBin ; ix<= highPtBin ; ix++)  { 
    for ( int in = 0 ; in< int(vIter.size()) ; in++)  {//    for (int icent = 1 ; icent<=8 ; icent++)  { 
      hmcUnfSq[ix][in] = (TH1D*)tempHistYsq->Clone(Form("mcUnfSq_ix%d_in%d",ix,in));
      hmcTruthSq[ix][in] = (TH1D*)tempHistYsq->Clone(Form("mcTruthSq_ix%d_in%d",ix,in));
      hmcRawSq[ix][in] = (TH1D*)tempHistYsq->Clone(Form("mcRawSq_ix%d_in%d",ix,in));
      getMCresults(kSample, icent, ix, vIter.at(in), matRwt, specRwtMc , hmcTruthSq[ix][in], hmcRawSq[ix][in], hmcUnfSq[ix][in]);

      hdataUnfSq[ix][in] = (TH1D*)tempHistYsq->Clone(Form("dataUnfSq_ix%d_in%d",ix,in));
      hdataRawSq[ix][in] = (TH1D*)tempHistYsq->Clone(Form("dataRawSq_ix%d_in%d",ix,in));
      getDATAresults(kSample, icent, ix, vIter.at(in), matRwt, specRwtData ,  hdataRawSq[ix][in], hdataUnfSq[ix][in]);
      
      cout << hmcUnfSq[ix][in]->GetName() << " : " << hmcUnfSq[ix][in]->Integral(1, hmcUnfSq[ix][in]->GetNbinsX(), "width") << endl;
      cout << hmcTruthSq[ix][in]->GetName() << " : " <<  hmcTruthSq[ix][in]->Integral(1, hmcTruthSq[ix][in]->GetNbinsX(),"width")  << endl;
    }
  }
  
  
  TCanvas* c2 =  new TCanvas("c2","",700,1000);
  //  makeMultiPanelCanvas(c2,nPtPannels, 2,0,0,0.3); //,0.01, 0.01, 0.2, 0.3, 0.0);
  makeMultiPanelCanvas(c2,2, nPtPannels, 0.0, 0.01, 0.2, 0.25, 0.05);
  
    for ( int ipt = lowPtBin ; ipt<= highPtBin ; ipt++)  {
      c2->cd((ipt - lowPtBin+1)*2 -1);
      c2->cd((ipt - lowPtBin+1)*2-1)->SetRightMargin(.01);
      c2->cd((ipt - lowPtBin+1)*2-1)->SetLeftMargin(.32);
      
      if ( ipt == lowPtBin)
	c2->cd((ipt - lowPtBin+1)*2 -1)->SetTopMargin(0.015);


      narrowSys( sysPlus.pp[ipt], 0, 0.24);
      narrowSys( sysPlus.pbpb[ipt], 0, 0.24);
      narrowSys( sysPlus.raa[ipt], 0, 0.24);
      narrowSys( sysMinus.pp[ipt], 0, 0.24);
      narrowSys( sysMinus.pbpb[ipt], 0, 0.24);
      narrowSys( sysMinus.raa[ipt], 0, 0.24);

      
      // SCALING! 
      CsScalePP(hdataUnfSq[ipt][0]);
      
      double normalization = hdataUnfSq[ipt][0]->Integral("w") / hmcTruthSq[ipt][0]->Integral("w"); 
      hmcTruthSq[ipt][0]->Scale(normalization);
      double maxY = cleverRange(hmcTruthSq[ipt][0],2.,0.000001);
      handsomeTH1(hmcTruthSq[ipt][0],1);
      hmcTruthSq[ipt][0]->SetNdivisions(505,"Y");
      fixedFontHist(hmcTruthSq[ipt][0],2.5,2.5,20);
      hmcTruthSq[ipt][0]->SetAxisRange(0,0.239,"X");
      handsomeTH1(hdataUnfSq[ipt][0],1);
      hmcTruthSq[ipt][0]->GetYaxis()->SetTitleOffset(4.5);
      hmcTruthSq[ipt][0]->SetYTitle("#frac{d#sigma}{d(m/p_{T})} (nb)");
      hmcTruthSq[ipt][0]->SetNdivisions(505,"X");
      hmcTruthSq[ipt][0]->SetAxisRange(0.000001, maxY,"Y");
      if ( ipt == lowPtBin ) 
      hmcTruthSq[ipt][0]->SetAxisRange(0.000001, maxY*1.3,"Y");

      hmcTruthSq[ipt][0]->GetXaxis()->SetTitleOffset(5);
      hmcTruthSq[ipt][0]->Draw("hist");
      drawSysUpDown( hdataUnfSq[ipt][0], sysPlus.pp[ipt], sysMinus.pp[ipt],  kSpring);
      hdataUnfSq[ipt][0]->Draw("same e");
      hmcTruthSq[ipt][0]->Draw("hist same");
      
      drawPatch(0.,0,0.315,0.08);

      if ( ipt < highPtBin) drawBinPt(xBin,ipt,"GeV",0.37, 0.74,1,18);
      else                  drawBinPt(xBin,ipt,"GeV",0.37, 0.82,1,18);
      if ( ipt == lowPtBin)  {
	TLegend* leg = new TLegend(0.37000,0.4417734,0.7211794,0.8397419,NULL,"brNDC");
	easyLeg(leg,"",0.12);
	leg->AddEntry(hdataUnfSq[ipt][0],"pp data","pl");
	leg->AddEntry(hmcTruthSq[ipt][0],"Powheg + Pythia8","l");
	leg->Draw();
	if ( ipt == lowPtBin ) {
	  ATLASLabel(0.37,0.86,"Internal",0.14,0.21);
	}

      }

      c2->cd((ipt - lowPtBin+1)*2);
      c2->cd((ipt - lowPtBin+1)*2)->SetLeftMargin(.15);
      if ( ipt == lowPtBin)
	c2->cd((ipt - lowPtBin+1)*2)->SetTopMargin(0.015);
      
      TH1D* hUnity = (TH1D*)hdataUnfSq[ipt][0]->Clone("hUnity");
      makeUnityWithErr(hUnity);
      hUnity->SetMarkerSize(0);
      hraioMCtemp[ipt][0] = (TH1D*)hmcTruthSq[ipt][0]->Clone(Form("hraioMCtemp_ipt%d",ipt));
      hraioMCtemp[ipt][0]->Divide(hdataUnfSq[ipt][0]);
      hraioMCtemp[ipt][0]->SetYTitle("MC/Data");
      hraioMCtemp[ipt][0]->SetNdivisions(505,"X");
      hraioMCtemp[ipt][0]->SetNdivisions(505,"Y");
      fixedFontHist(hraioMCtemp[ipt][0],2.5,2.5,20);
      handsomeTH1(hraioMCtemp[ipt][0],1);
      hraioMCtemp[ipt][0]->SetLineWidth(1);
      hraioMCtemp[ipt][0]->SetAxisRange(0.1,2.19,"Y");
      hraioMCtemp[ipt][0]->GetYaxis()->SetTitleOffset(3.6);
      hraioMCtemp[ipt][0]->GetXaxis()->SetTitleOffset(5);
      hraioMCtemp[ipt][0]->Draw("hist");
      drawSysUpDown( hUnity, sysPlus.pp[ipt], sysMinus.pp[ipt],  kSpring);
      hUnity->DrawCopy("same");
      hraioMCtemp[ipt][0]->Draw("hist same");
      

      //	else   hdataRatioSq[ipt][in]->Draw("same");
      if ( optY == 2)  jumSun(0,1,0.24,1);
      
      
      if (ipt == lowPtBin)   {
	ATLASLabel(0.21,0.86,"Internal",0.14,0.24);
	drawText("(Powheg+Pythia8)/data", 0.21, 0.72, 1,18);
	//	drawText(Form("reference iter. (%d)",vIter.at(refId)), 0.22, 0.82, 1);
      }
      gPad->RedrawAxis();
    }
    
    //    c2->SaveAs(Form("stabilitiy/data_coll%d_icent%d_matrixRwt%d_spectraRwt%d.pdf",kSample,icent,(int)matRwt, (int)specRwt));
  
  c2->SaveAs("PPPYTHIAfigure_confnote.pdf");
  
}  



void getMCresults(int kSample, int icent, int ix, int nIter, bool matRwt, bool specRwt,  TH1D* hmcTruthSq, TH1D* hmcRawSq, TH1D* hmcUnfSq) {
  TFile * fin = new TFile(Form("unfSpectra/kSample%d_matrixRwt%d_spectraRwt%d.root",kSample, (int)matRwt, (int)specRwt));
  TH1D* hUnf = (TH1D*)fin->Get(Form("hmcUnf1d_icent%d_ix%d_iter%d",icent,ix,nIter));
  TH1D* hTruth = (TH1D*)fin->Get(Form("hmcTruth1d_icent%d_ix%d",icent,ix));
  TH1D* hRaw = (TH1D*)fin->Get(Form("hmcRaw1d_icent%d_ix%d",icent,ix));
  
  hmcTruthSq->Reset();
  hmcTruthSq->Add(hTruth);
  hmcUnfSq->Reset();
  hmcUnfSq->Add(hUnf);
  hmcRawSq->Reset();
  hmcRawSq->Add(hRaw);



}

void getDATAresults(int kSample, int icent, int ix, int nIter,  bool matRwt, bool specRwt, TH1D* hdataRawSq, TH1D* hdataUnfSq) {
  TFile * fin = new TFile(Form("unfSpectra/kSample%d_matrixRwt%d_spectraRwt%d.root",kSample, (int)matRwt, (int)specRwt));
  TH1D* hUnf = (TH1D*)fin->Get(Form("hdataUnf1d_icent%d_ix%d_iter%d",icent,ix,nIter));
  TH1D* hRaw = (TH1D*)fin->Get(Form("hdataRaw1d_icent%d_ix%d",icent,ix));

  hdataUnfSq->Reset();
  hdataUnfSq->Add(hUnf);
  hdataRawSq->Reset();
  hdataRawSq->Add(hRaw);

}


void narrowSys( TH1D* hsys, double xlow, double xhigh) {
  for ( int ii=0 ; ii<=hsys->GetNbinsX() ; ii++) {
    double xVal = hsys->GetBinCenter(ii);
    if ( xVal < xlow )    hsys->SetBinContent(ii,0);
    if ( xVal > xhigh )   hsys->SetBinContent(ii,0);
  }
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

