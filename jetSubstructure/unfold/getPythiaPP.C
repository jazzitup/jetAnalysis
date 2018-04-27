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

JetSys getFinalSys(int icent =0, int nVar=0);

void getMCresults(int kSample=0, int icent=0, int ix=0, int nIter=0,  bool matRwt=1, bool specRwt=0,  TH1D* hmcTruthSq=0, TH1D* hmcRawSq=0, TH1D* hmcUnfSq=0);
void getDATAresults(int kSample=0, int icent=0, int ix=0, int nIter=0,  bool matRwt=1, bool specRwt=0, TH1D* hdataRawSq=0, TH1D* hdataUnfSq=0);
void narrowSys( TH1D* hsys=0, double xlow=0, double xhigh=0);

void comparePythiaData(int kSample= kPP, int icent = 0, bool matRwt=1, int optX=1, int optY=2, bool applyMDJ=false) {
  
  bool specRwtData = 1;
  bool specRwtMc = 0;

  bool doDATA = true; 
  
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

      if ( doDATA) { 
	hdataUnfSq[ix][in] = (TH1D*)tempHistYsq->Clone(Form("dataUnfSq_ix%d_in%d",ix,in));
	hdataRawSq[ix][in] = (TH1D*)tempHistYsq->Clone(Form("dataRawSq_ix%d_in%d",ix,in));
	getDATAresults(kSample, icent, ix, vIter.at(in), matRwt, specRwtData ,  hdataRawSq[ix][in], hdataUnfSq[ix][in]);
      }  
      cout << hmcUnfSq[ix][in]->GetName() << " : " << hmcUnfSq[ix][in]->Integral(1, hmcUnfSq[ix][in]->GetNbinsX(), "width") << endl;
      cout << hmcTruthSq[ix][in]->GetName() << " : " <<  hmcTruthSq[ix][in]->Integral(1, hmcTruthSq[ix][in]->GetNbinsX(),"width")  << endl;
    }
  }
  
  
  if (doDATA) {
    TCanvas* c2 =  new TCanvas("c2","",1200,550);
    //  c2->Divide((nPtBinDraw+1)/2,2);
    //    makeEfficiencyCanvas(c2,nPtPannels+1, 0.02, 0.01, 0.2, 0.3, 0.01);
    makeMultiPanelCanvas(c2,nPtPannels, 2,0.02, 0.01, 0.2, 0.3, 0.01);
    
    /*    c2->cd(lowPtBin+1);
    TLegend *leg1 = new TLegend(0.002212389,0.001490066,0.9977876,1,NULL,"brNDC");
    easyLeg(leg1,"Data",0.12);
    //    leg1->AddEntry( hdataRawSq[lowPtBin][0], "Raw","l");
    
    for (int in = 0; in < int(vIter.size()) ; in++)  {
      if ( vIter[in] == 1 ) leg1->AddEntry(hdataUnfSq[lowPtBin][in], Form("%dst iter.",vIter[in]));
      else if ( vIter[in] == 2 ) leg1->AddEntry(hdataUnfSq[lowPtBin][in], Form("%dnd iter.",vIter[in]));
      else if ( vIter[in] == 3 ) leg1->AddEntry(hdataUnfSq[lowPtBin][in], Form("%drd iter.",vIter[in]));
      else  leg1->AddEntry(hdataUnfSq[lowPtBin][in], Form("%dth iter.",vIter[in]));
    }
    leg1->AddEntry( hmcTruthSq[lowPtBin][0], "PYTHIA Truth","l");
    leg1->Draw();
    */

    for ( int ipt = lowPtBin ; ipt<= highPtBin ; ipt++)  {
      c2->cd(ipt - lowPtBin+1);
      
      scaleInt(hmcTruthSq[ipt][0]);
      cleverRange(hmcTruthSq[ipt][0],2);
      hmcTruthSq[ipt][0]->SetAxisRange(0,0.239,"X");
      
      if ( optY==1) hdataRawSq[ipt][0]->SetAxisRange(0.00,100,"X");
      else if ( optY==2) hdataRawSq[ipt][0]->SetAxisRange(0.001,0.23999,"X");
      if ( optY==1)    hdataRawSq[ipt][0]->SetXTitle("m^{2} GeV^{2}");
      else if ( optY==2)    hdataRawSq[ipt][0]->SetXTitle("m/p_{T}");
      if ( hdataRawSq[ipt][0]->Integral()>0) cleverRangeLog(hdataRawSq[ipt][0],100,0.00001);
      hdataRawSq[ipt][0]->SetYTitle("Entries");
      handsomeTH1(hdataRawSq[ipt][0],1);
      handsomeTH1(hdataUnfSq[ipt][0],2);
      
      scaleInt(hdataUnfSq[ipt][0]);

      hmcTruthSq[ipt][0]->Draw("hist");
      drawSysUpDown( hdataUnfSq[ipt][0], sysPlus.pp[ipt], sysMinus.pp[ipt],  kOrange);
      hdataUnfSq[ipt][0]->Draw("same e");
      hmcTruthSq[ipt][0]->Draw("hist same");
      
      drawBin(xBin,ipt,"GeV",0.35 + (0.05* (ipt==lowPtBin)), 0.81,1,20);
      if ( ipt == lowPtBin)  {
	TLegend *leg = new TLegend(0.2388782,0.5308459,0.7592913,0.9024531,NULL,"brNDC");
	easyLeg(leg,"",0.08);
	leg->AddEntry(hdataUnfSq[ipt][0],"Data","pl");
	leg->AddEntry(hmcTruthSq[ipt][0],"PYTHIA","l");
	leg->Draw();
	if ( ipt == lowPtBin ) {
	  drawCentrality(kSample, icent, 0.25,0.83,1,24);
	  ATLASLabel(0.25,0.9,"Internal",0.085,0.28);
	}
      }

      c2->cd(ipt - lowPtBin + 1 + nPtPannels);
      
      TH1D* hUnity = (TH1D*)hmcTruthSq[ipt][0]->Clone("hUnity");
      for ( int i=1 ; i<=hUnity->GetNbinsX() ; i++){  
	hUnity->SetBinContent(i,1);
      }


      hraioMCtemp[ipt][0] = (TH1D*)hmcTruthSq[ipt][0]->Clone(Form("hraioMCtemp_ipt%d",ipt));
      hraioMCtemp[ipt][0]->Divide(hdataUnfSq[ipt][0]);
      hraioMCtemp[ipt][0]->SetYTitle("Ratio");
      hraioMCtemp[ipt][0]->SetNdivisions(505,"X");
      hraioMCtemp[ipt][0]->SetNdivisions(505,"Y");
      fixedFontHist(hraioMCtemp[ipt][0],2.5,2.5,20);
      handsomeTH1(hraioMCtemp[ipt][0],1);
      hraioMCtemp[ipt][0]->SetLineWidth(1);
      hraioMCtemp[ipt][0]->SetAxisRange(0.,2.2,"Y");
      hraioMCtemp[ipt][0]->Draw("hist");
      drawSysUpDown( hUnity, sysPlus.pp[ipt], sysMinus.pp[ipt],  kOrange);
      hraioMCtemp[ipt][0]->Draw("hist same");
      

      //	else   hdataRatioSq[ipt][in]->Draw("same");
      if ( optY == 2)  jumSun(0,1,0.3,1);
      
      
      if (ipt == lowPtBin)   {
	drawText("PYTHIA/data", 0.25, 0.9, 1);
	//	drawText(Form("reference iter. (%d)",vIter.at(refId)), 0.22, 0.82, 1);
      }
      gPad->RedrawAxis();
    }
    
    //    c2->SaveAs(Form("stabilitiy/data_coll%d_icent%d_matrixRwt%d_spectraRwt%d.pdf",kSample,icent,(int)matRwt, (int)specRwt));
    c2->Modified();
    //    c2->SaveAs(Form("stabilitiy/data_coll%d_icent%d_matrixRwt%d_spectraRwt%d.pdf",kSample,icent,(int)matRwt, (int)specRwt));
  }

}  

/*
  TCanvas* c11=  new TCanvas("c11","",1200,800);
  //  c11->Divide((nPtBinDraw+1)/2,2);
  makeMultiPanelCanvas(c11,(nPtBinDraw+1)/2,2);
  for ( int ipt = lowPtBin ; ipt<= highPtBin ; ipt++)  {
    c11->cd(ipt - lowPtBin +1);
    int lowestBin = findLowerBoundBin( theRatio[ipt],4,9);
    double scaleFact = theRatio[ipt]->GetBinContent(lowestBin) ;
    theRatio[ipt]->Scale(1./scaleFact);
    theRatio[ipt]->SetAxisRange(0,9,"Y");
    theRatio[ipt]->Draw();
    jumSun(-0.02,1,0.09,1);
    if ( ipt==lowPtBin)  drawCentrality(kSample, icent, 0.45,0.86,1,24);
    //    drawText(Form("%dth iteration / 4th",vIter[in]),0.45,0.7,2,14);
    drawBin(ptBin,ipt,"GeV",0.3,0.78,1,20);
  }
  c11->SaveAs(Form("pdfs/mcVsData_coll%d_icent%d_ratio.pdf",kSample,icent));
  c11->SaveAs(Form("pdfs/mcVsData_coll%d_icent%d_ratio.png",kSample,icent));
  
  TH1D* hRatio[20][10];  // ipt, iteration
  
  for ( int in = 1 ; in< vIter.size() ; in++)  {//    for (int icent = 1 ; icent<=8 ; icent++)  { 
    TCanvas* c2=  new TCanvas(Form("c2_%d",in),"",1200,800);
    //    c2->Divide((nPtBinDraw+1)/2,2);
    makeMultiPanelCanvas(c2,(nPtBinDraw+1)/2,2);
    for ( int ipt = lowPtBin ; ipt<=highPtBin ; ipt++)  {
      c2->cd(ipt - lowPtBin +1);
      hmass[ipt][in]->Divide(hmass[ipt][0]);
      hmass[ipt][in]->SetAxisRange(0,3,"Y");
      hmass[ipt][in]->SetYTitle("Ratio");
      if ( optY==1)  hmass[ipt][in]->SetAxisRange(0,30,"X");
      else if ( optY==2) hmass[ipt][in]->SetAxisRange(0,0.27,"X");
      if ( optY==1)    hmass[ipt][in]->SetXTitle("m (GeV)");
      else if ( optY==2)    hmass[ipt][in]->SetXTitle("m/p_{T}");


      hmass[ipt][in]->Draw("e");
      if ( optY==1) jumSun(0,1,100,1);
      else if ( optY==2) jumSun(0,1,0.27,1);
      
      if ( ipt==lowPtBin)  drawCentrality(kSample, icent, 0.45,0.85,1,24);
      drawBin(ptBin,ipt,"GeV",0.45,0.76,1,18);
      drawText(Form("%dth iteration / 4th",vIter[in]),0.45,0.65,2,16);
      hRatio[ipt][in]  = (TH1D*)hmass[ipt][in]->Clone(Form("hmass_ipt%d_in%d",ipt,in));
      
    }
    c2->SaveAs(Form("pdfs/unfoldingStability_coll%d_icent%d_nIter%d.pdf",kSample,icent,vIter[in]));
  }
  TCanvas* cOverlay=  new TCanvas("cOverlay","",1200,800);
  makeMultiPanelCanvas(cOverlay,(nPtBinDraw+1)/2,2);
  for ( int ipt = lowPtBin ; ipt<=highPtBin ; ipt++)  {
    cOverlay->cd(ipt - lowPtBin +1);
    TLegend *leg = new TLegend(0.2758281,0.0008063921,0.9970038,0.3762096,NULL,"brNDC");
    easyLeg(leg,Form("Ratio to %dth iteration",vIter[0]));
    for ( int in = 1 ; in< vIter.size() ; in++)  {  
      handsomeTH1(hRatio[ipt][in], in);
      hRatio[ipt][in]->SetAxisRange(0.5,1.5,"Y");
      if ( in ==1 ) hRatio[ipt][in]->Draw();
      else hRatio[ipt][in]->Draw("same");
      if ( optY==1) jumSun(0,1,100,1);
      else if ( optY==2) jumSun(0,1,0.27,1);
      
      if ( ipt==lowPtBin)  drawCentrality(kSample, icent, 0.45,0.88,1,24);
      drawBin(ptBin,ipt,"GeV",0.45,0.80,1,18);
      leg->AddEntry(hRatio[ipt][in], Form("Iter. %d",vIter[in])); 
    }
    if ( ipt == lowPtBin)  leg->Draw();
  }
  cOverlay->SaveAs(Form("pdfs/unfoldingStability_coll%d_icent%d_Overlay.pdf",kSample,icent));
  cOverlay->SaveAs(Form("pdfs/unfoldingStability_coll%d_icent%d_Overlay.png",kSample,icent));
}
  */



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

