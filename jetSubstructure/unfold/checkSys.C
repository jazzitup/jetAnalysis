#include "../getSdHists.C"
#include "../ntupleDefinition.h"
#include "../commonUtility.h"
#include "../jzWeight.h"
#include "../commonUtility.h"
#include "../JssUtils.h"
#include "unfoldingUtil.h"

void groomHist(TH1D* h1) {
  h1->SetAxisRange(0.001,0.23,"X");
  h1->SetAxisRange(-0.55,0.55,"Y");
  h1->SetXTitle("m/p_{T}");
  h1->SetYTitle("Unc.");
  h1->SetNdivisions(505,"X");
  h1->SetNdivisions(505,"Y");
  fixedFontHist(h1,3,3,20);
  h1->GetXaxis()->SetTitleOffset(5);
  h1->GetYaxis()->SetTitleOffset(5);
}

struct JetSys {
  TH1D* pp[20];
  TH1D* pbpb[20];
  TH1D* raa[20];
};

void getDATAresults(int kSample=0, int icent=0, int ix=0, TH1D* hdataUnfSq=0, TString dir="", int nSys=-1);
TString getSysName(int nSys = -1);
TH1D* getSysJES(int kSample= kPP, int icent = 0, int ix=7, int nSys=-1);
void addSysInQuad(TH1D* sysTot=0, TH1D* sys1=0);


void checkSys(int nSys=200) { 

  int optX =1 ;
  int optY =2 ;

  int nXbins;
  double xBin[30];
  getXbin(nXbins, xBin, optX);

  int nYbins ;
  double yBin[30] ;
  getYbin(nYbins, yBin, optY);


  int lowPtBin = 6;
  int highPtBin = nXbins-1;

  int nPtPannels = highPtBin-lowPtBin+1;

  TH1D* hSysApp[30];
  TH1D* hSysApbpb[30][8]; // pt, centrality

  for ( int ix = lowPtBin ; ix<= highPtBin ; ix++)  {
    hSysApp[ix]   = getSysJES(kPP,     0  , ix, nSys);
    for ( int icent=0; icent<=6 ; icent++) { 
      hSysApbpb[ix][icent] = getSysJES(kPbPb, icent, ix, nSys);
    }
    
  }
  
  bool savePic = 1; 
  
  TCanvas* cA;    
  if (savePic) { 
    cA =  new TCanvas(Form("sysJES"),"",960,900);
    makeMultiPanelCanvas(cA,nPtPannels,8,.01, .01,0.45,0.45);
  }
  for ( int ix = lowPtBin ; ix<= highPtBin ; ix++)  {
    if (savePic)    cA->cd(ix - lowPtBin + 1);
    handsomeTH1(hSysApp[ix],1);
    groomHist(hSysApp[ix]); 
    hSysApp[ix]->Draw("");
    if ( ix == lowPtBin)  ATLASLabel(0.5,0.8,"Internal",0.15,0.2);
    if ( ix == lowPtBin+1)  drawCentrality(kPP, 0, 0.1,0.8,1,20);
    if ( ix== lowPtBin) drawBin(xBin,ix,"GeV",0.5,0.15,1,16);
    else drawBin(xBin,ix,"GeV",0.25 - 0.15,0.15,1,16);
    jumSun(0,0,0.24,0);
    
    for ( int icent=0; icent<=6 ; icent++) {
      cA->cd(ix - lowPtBin + 1 + nPtPannels*(7-icent));
      handsomeTH1(hSysApbpb[ix][icent],1);
      groomHist(hSysApbpb[ix][icent]); 
      hSysApbpb[ix][icent]->Draw("");
      if ( ix == lowPtBin+1)  drawCentrality(kPbPb, icent, 0.1,0.8,1,20);
      jumSun(0,0,0.24,0);
    }

    //    if ( ix == lowPtBin) {
    //      TLegend *leg1 = new TLegend(0.2355436,0.2339862,0.758156,0.4051428,NULL,"brNDC");
    //      easyLeg(leg1,"(mass varied)/default" ,0.07);
    //      leg1->AddEntry(hSysApp[ix],"pp","l");
    //      leg1->AddEntry(hSysApbpb[ix],"PbPb","l");
    //      leg1->Draw();
    //    }

  }
  if (savePic)  cA->SaveAs(Form("pdfsSystematics/sysJES_nSys%d.pdf",nSys));

  //  return ret;
}





TH1D* getSysJES(int kSample, int icent , int ix, int nSys) {
  
  TString sRef = "reweight00";
  int optX = 1;
  int optY = 2;
  
  int nXbins;
  double xBin[30];
  getXbin(nXbins, xBin, optX);

  int nYbins ;
  double yBin[30] ;
  getYbin(nYbins, yBin, optY);

  TH1D* hRef = new TH1D("hRef","",nYbins,yBin);
  TH1D* h2 = (TH1D*)hRef->Clone("h2");

  getDATAresults( kSample, icent, ix, hRef, sRef,    -1);
  getDATAresults( kSample, icent, ix, h2,   "sys", nSys);
  
  TH1D* ret = (TH1D*)h2->Clone(Form("kSample%d_icent%d_ix%d_nSys%d",kSample,icent,ix, nSys));
  ret->Add(hRef,-1);
  ret->Divide(hRef);

  delete hRef;
  delete h2;
  return ret;

}

void getDATAresults(int kSample, int icent, int ix, TH1D* hdataUnfSq, TString dir, int nSys) {
  
  bool matRwt = 1; 
  bool specRwt = 1;
  int nIter = getRefIter( kSample, icent);
  TFile * fin;
  cout << "==== "<< endl;
  cout << " dir = " << dir <<endl;
  cout << " nSys = " << nSys <<endl;

  if ( nSys < 0)   fin = new TFile(Form("unfSpectra/%s/kSample%d_matrixRwt%d_spectraRwt%d.root",dir.Data(),kSample, (int)matRwt, (int)specRwt));
  else    fin = new TFile(Form("unfSpectra/sys/kSample%d_matrixRwt%d_spectraRwt%d_sys%d.root",kSample, (int)matRwt, (int)specRwt, nSys) );
  TH1D* hUnf = (TH1D*)fin->Get(Form("hdataUnf1d_icent%d_ix%d_iter%d",icent,ix,nIter));
  cout << "==== "<< endl;
  
  hdataUnfSq->Reset();
  hdataUnfSq->Add(hUnf);

}


TString getSysName(int nSys ) { 
  if      ( nSys == 0 )      return "Eta Intercal. model";
  else if ( nSys == 1 )      return "Eta Intercal. model";
  else if ( nSys == 2 )     return "Eta InterCal. Stat.";
  else if ( nSys == 3 )     return "Eta InterCal. Stat.";
  else if ( nSys == 4 )     return "Punch through";
  else if ( nSys == 5 )     return "Punch through";
  else if ( nSys == 6 )     return "Effecive NP1";
  else if ( nSys == 7 )     return "Effecive NP1";
  else if ( nSys == 8 )     return "Effecive NP2";
  else if ( nSys == 9 )     return "Effecive NP2";
  else if ( nSys == 10 )     return "Effecive NP3";
  else if ( nSys == 11 )     return "Effecive NP3";
  else if ( nSys == 12 )     return "Effecive NP4";
  else if ( nSys == 13 )     return "Effecive NP4";
  else if ( nSys == 14 )     return "Effecive NP5";
  else if ( nSys == 15 )     return "Effecive NP5";
  else if ( nSys == 16 )     return "Eff. NP6reset";
  else if ( nSys == 17 )     return "Eff. NP6reset";
  else if ( nSys == 18 )     return "Inter. NonClosure";
  else if ( nSys == 19 )     return "Inter. NonClosure";
  else if ( nSys == 20 )     return "HighPt Sin. par.";
  else if ( nSys == 21 )     return "HighPt Sin. par.";

  else if ( nSys == 100 )     return "JER";   //1
  else if ( nSys == 101 )     return "HI intrinsic_1";   // 6
  else if ( nSys == 102 )     return "HI intrinsic_1"; // 7
  else if ( nSys == 103 )     return "HI intrinsic_2"; // 8
  else if ( nSys == 104 )     return "HI intrinsic_2"; // 9
  else if ( nSys == 105 )     return "HI Centrality"; // 16
  else if ( nSys == 106 )     return "HI Centrality"; // 17

  return ".";
  
}


void addSysInQuad(TH1D* sysTot, TH1D* sys1) {
  if ( sysTot->GetNbinsX() != sys1->GetNbinsX() ) {
    cout << " Uncompatible histograms!!" << endl;
    return;
  }

  int nBins = sysTot->GetNbinsX();
  for ( int ii=0 ; ii<=nBins ; ii++) {
    double yTot = sysTot->GetBinContent(ii);
    double y1 = sys1->GetBinContent(ii);
    double newYTot = sqrt( yTot*yTot + y1*y1) ;
    sysTot->SetBinContent(ii, newYTot);
  }
}
