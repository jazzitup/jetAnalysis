#include "../getSdHists.C"
#include "../ntupleDefinition_v50.h"
#include "../commonUtility.h"
#include "../jzWeight.h"
#include "../JssUtils.h"
#include "unfoldingUtil.h"

int kMergeCancel = 1;
int kMergeQuad = 2;
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

class RtrkProvider {
 public:
  TF1* fpp[6];
  TF1* fpbpbCentral[6];
  TF1* fHerwig[6];

  void Setup(int _ksample, int _icent);
  double getR(jetSubStr myJet);
  double getRPyHer(jetSubStr myJet);
 private:
  int kSample;
  int icent;
  
};

void RtrkProvider::Setup (int _kSample, int _icent) { 
  //  TFile* fpp = new TFile(Form("R_trk/Rtrk_kSample%d_cent%d.root",_kSample, _icent));
  TFile* filepp = new TFile("R_trk/Rtrk_kSample0_cent0.root");
  for ( int im = 1 ; im<=4 ; im++) { 
    fpp[im] = (TF1*)filepp->Get(Form("rtrk_im%d",im));
  }
  TFile* filepbpbCent = new TFile("R_trk/Rtrk_kSample1_cent0.root");
  for ( int im = 1 ; im<=4 ; im++) { 
    fpbpbCentral[im] = (TF1*)filepbpbCent->Get(Form("rtrk_im%d",im));
  }
  TFile* fileHerwig = new TFile("R_trk/Rtrk_PYTHIA_herwig.root");
  for ( int im = 1 ; im<=4 ; im++) { 
    fHerwig[im] = (TF1*)fileHerwig->Get(Form("rtrk_im%d",im));
  }
  
  kSample = _kSample;
  icent = _icent;
  
}

double RtrkProvider::getR(jetSubStr myJet) {
  int im =  findMbin(myJet.recoMass / myJet.recoPt );
  double rPP = fpp[im]->Eval(myJet.recoPt);
  double rPbPbCent = fpbpbCentral[im]->Eval(myJet.recoPt);
  if ( kSample == kPP)  return rPP;
  else { 
    return   ( rPbPbCent* (7-icent) + rPP * (icent) ) / 7; 
  }
}

double RtrkProvider::getRPyHer(jetSubStr myJet) {
  int im =  findMbin(myJet.recoMass / myJet.recoPt );
  double theR = fHerwig[im]->Eval(myJet.recoPt);
  return theR;
}


JetSys jsDummy;

void getDATAresults(int kSample=0, int icent=0, int ix=0, TH1D* hdataUnfSq=0, TString dir="", int nSys=-1);
TString getSysName(int nSys = -1);
TH1D* getSysA(int kSample= kPP, int icent = 0, int ix=7, TString s1 ="reweight00", TString s2="reweight00varP50percent" ); 
TH1D* getSysJES(int kSample= kPP, int icent = 0, int ix=7, int nSys=-1);
JetSys getSystematicsJES(int icent = 0, int nSys=1, double theScale=1, int mergeOpt=kMergeCancel);
JetSys getSystematicsUnf(int icent = 0, int nSys=1);
JetSys getSystematicsJMSCal();
void getInverse(JetSys inputSys=jsDummy, JetSys outputSys=jsDummy,  int lowX=0, int highX=0);
void addSysInQuad(TH1D* sysTot=0, TH1D* sys1=0);
void addSysInQuad3(JetSys jstot=jsDummy, JetSys js1=jsDummy, int lowX=0, int highX=0); 
void mirrorJS(JetSys js1=jsDummy, JetSys js2=jsDummy, int lowX=0, int highX=0);

void sortPlusMinus(TH1D* hp=0, TH1D* hm=0);


JetSys getSystematicsJMSCal() {
  int nSys=210;

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
  TH1D* hSysApbpb[30];
  TH1D* hSysAraa[30];

  for ( int ix = lowPtBin ; ix<= highPtBin ; ix++)  {
    hSysApp[ix] = getSysJES(kPP, 0  , ix,  nSys);
    hSysApbpb[ix] = getSysJES(kPbPb, 0, ix, nSys);
    hSysAraa[ix] = (TH1D*)hSysApbpb[ix]->Clone(Form("sysRaa_%s",hSysApbpb[ix]->GetName()) );

    hSysAraa[ix]->Reset();
    hSysApp[ix]->Reset();
    hSysApbpb[ix]->Reset();

    for ( int xx = 1 ; xx<= hSysApbpb[ix]->GetNbinsX() ; xx++) {
      double theUnc = 0;
      if ( xx ==2 ) {
	if ( ix <= lowPtBin+1 ) theUnc = 0.05;
	else theUnc = 0.08;
      }
      else  {
	theUnc = 0.01;
      }
      
      hSysApp[ix]->SetBinContent(xx,theUnc);
      hSysApbpb[ix]->SetBinContent(xx,theUnc);
      hSysAraa[ix]->SetBinContent(xx, theUnc*sqrt(2));
    }
  } 
  JetSys ret;
  for ( int ix = lowPtBin ; ix<= highPtBin ; ix++)  {
    ret.pp[ix]   =  hSysApp[ix];
    ret.pbpb[ix] =  hSysApbpb[ix];
    ret.raa[ix]  = hSysAraa[ix];
  }
  
  return ret;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

JetSys getSystematicsJES(int icent, int nSys, double theScale, int mergeOpt) {
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
  TH1D* hSysApbpb[30];
  TH1D* hSysAraa[30];

  for ( int ix = lowPtBin ; ix<= highPtBin ; ix++)  {
    hSysApp[ix] = getSysJES(kPP, 0  , ix,  nSys);
    hSysApbpb[ix] = getSysJES(kPbPb, icent, ix, nSys);
    
    hSysAraa[ix] = (TH1D*)hSysApbpb[ix]->Clone(Form("sysRaa_%s",hSysApbpb[ix]->GetName()) );
    hSysAraa[ix]->Reset();
    for ( int xx = 1 ; xx<= hSysApbpb[ix]->GetNbinsX() ; xx++) {
      double y1 = hSysApbpb[ix]->GetBinContent(xx);
      double y2 = hSysApp[ix]->GetBinContent(xx);
      //      if ( nSys == 210)   hSysAraa[ix]->SetBinContent(xx,  sqrt( y1*y1 + y2*y2) ) ;
      if ( mergeOpt == kMergeCancel )  
	hSysAraa[ix]->SetBinContent(xx,  (y1+1.)/(y2+1.)-1);
      if ( mergeOpt == kMergeQuad )   
	hSysAraa[ix]->SetBinContent(xx,  sqrt( y1*y1 + y2*y2));
    }
  }

  bool savePic = 0; 
  
  TCanvas* cA;    
  if (savePic) { 
    cA =  new TCanvas(Form("sysJES_icent%d_nSys%d",icent,nSys),"",800,400);
    makeMultiPanelCanvas(cA,nPtPannels,1);
  }
  for ( int ix = lowPtBin ; ix<= highPtBin ; ix++)  {
    if (savePic)    cA->cd(ix - lowPtBin + 1);
    handsomeTH1(hSysApp[ix],1);
    handsomeTH1(hSysApbpb[ix],2);
    hSysApp[ix]->SetAxisRange(0.001,0.23,"X");
    hSysApp[ix]->SetAxisRange(-0.55,0.55,"Y");
    hSysApp[ix]->SetXTitle("m/p_{T}");
    hSysApp[ix]->SetYTitle("Uncertainty (Relative)");
    hSysApp[ix]->SetNdivisions(505,"X");
    hSysApp[ix]->SetNdivisions(505,"Y");
    fixedFontHist(hSysApp[ix],1.2,1.4,20);
    hSysApp[ix]->Draw("hist" );
    hSysApbpb[ix]->Draw("same hist");
    jumSun(0,0,0.24,0);


    if ( ix == lowPtBin) {
      drawCentrality(kPbPb, icent, 0.25,0.88,1,20);
      TLegend *leg1 = new TLegend(0.2355436,0.2339862,0.758156,0.4051428,NULL,"brNDC");
      TString sysTxt = getSysName(nSys);
      easyLeg(leg1,sysTxt.Data(),0.07);
      //easyLeg(leg1,"ss",0.07);

      leg1->AddEntry(hSysApp[ix],"pp","l");
      leg1->AddEntry(hSysApbpb[ix],"PbPb","l");
      leg1->Draw();
    }
    drawBin(xBin,ix,"GeV",0.25,0.80,1,20);

  }
  if (savePic)  cA->SaveAs(Form("pdfsSystematics/sysJES_icent%d_nSys%d.pdf",icent,nSys));
  
  JetSys ret;
  for ( int ix = lowPtBin ; ix<= highPtBin ; ix++)  {
    if ( theScale != 1) { 
      hSysApp[ix]->Scale(theScale);
      hSysApbpb[ix]->Scale(theScale);
      hSysAraa[ix]->Scale(theScale);
    }

    ret.pp[ix]   =  hSysApp[ix];
    ret.pbpb[ix] =  hSysApbpb[ix];
    ret.raa[ix]  = hSysAraa[ix];
  }

  return ret;
}




JetSys getSystematicsUnf(int icent, int nVar ) {
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
  TH1D* hSysApbpb[30];
  TH1D* hSysAraa[30];

  for ( int ix = lowPtBin ; ix<= highPtBin ; ix++)  {
    //TH1D* getSysA(int kSample, int icent, int ix, TString sReference , TString s2)   { 
    TString varString = "-";  
    if ( nVar == 1 ) varString = "reweight00varP50percent";
    if ( nVar == -1 ) varString = "reweight00varM50percent";
    hSysApp[ix] = getSysA(kPP, 0  , ix,  "reweight00", varString);
    hSysApbpb[ix] = getSysA(kPbPb, icent, ix, "reweight00", varString);
    
    hSysAraa[ix] = (TH1D*)hSysApbpb[ix]->Clone(Form("sysRaa_%s",hSysApbpb[ix]->GetName()) );
    addSysInQuad( hSysAraa[ix], hSysApp[ix] ) ;
  }
  
  bool savePic = 1; 
  
  TCanvas* cA;    
  if (savePic) { 
    cA =  new TCanvas(Form("sysUnf_icent%d_nVar%d",icent,nVar),"",800,400);
    makeMultiPanelCanvas(cA,nPtPannels,1);
  }
  for ( int ix = lowPtBin ; ix<= highPtBin ; ix++)  {
    if (savePic)    cA->cd(ix - lowPtBin + 1);
    handsomeTH1(hSysApp[ix],1);
    handsomeTH1(hSysApbpb[ix],2);
    hSysApp[ix]->SetAxisRange(0.001,0.23,"X");
    hSysApp[ix]->SetAxisRange(-0.55,0.55,"Y");
    hSysApp[ix]->SetXTitle("m/p_{T}");
    hSysApp[ix]->SetYTitle("Uncertainty (Relative)");
    hSysApp[ix]->SetNdivisions(505,"X");
    hSysApp[ix]->SetNdivisions(505,"Y");
    fixedFontHist(hSysApp[ix],1.2,1.4,20);
    hSysApp[ix]->Draw("hist" );
    hSysApbpb[ix]->Draw("same hist");
    jumSun(0,0,0.24,0);


    if ( ix == lowPtBin) {
      drawCentrality(kPbPb, icent, 0.25,0.88,1,20);
      TLegend *leg1 = new TLegend(0.2355436,0.2339862,0.758156,0.4051428,NULL,"brNDC");
      TString sysTxt = Form("Varied by %d %%", nVar*50);
      easyLeg(leg1,sysTxt.Data(),0.07);
      //easyLeg(leg1,"ss",0.07);

      leg1->AddEntry(hSysApp[ix],"pp","l");
      leg1->AddEntry(hSysApbpb[ix],"PbPb","l");
      leg1->Draw();
    }
    drawBin(xBin,ix,"GeV",0.25,0.80,1,20);
    
  }
  if (savePic)  cA->SaveAs(Form("pdfsSystematics/sysUnf_icent%d_nVar%d.pdf",icent,nVar));
  
  JetSys ret;
  for ( int ix = lowPtBin ; ix<= highPtBin ; ix++)  {
    ret.pp[ix]   =  hSysApp[ix];
    ret.pbpb[ix] =  hSysApbpb[ix];
    ret.raa[ix]  = hSysAraa[ix];
  }

  return ret;
}




TH1D* getSysA(int kSample, int icent, int ix, TString s1 , TString s2)   {
  
  int optX = 1; 
  int optY = 2;

  int nXbins;
  double xBin[30];
  getXbin(nXbins, xBin, optX);

  int nYbins ;
  double yBin[30] ;
  getYbin(nYbins, yBin, optY);

  TH1D* h1 = new TH1D("h1","",nYbins,yBin);
  TH1D* h2 = (TH1D*)h1->Clone("h2");
  
  getDATAresults( kSample, icent, ix, h1, s1, -1);
  getDATAresults( kSample, icent, ix, h2, s2, -1);
  
  TH1D* ret = (TH1D*)h2->Clone(Form("sysUnf_kSample%d_icent%d_ix%d_%s_%s",kSample,icent,ix,s1.Data(), s2.Data()) );
  ret->Add(h1,-1);
  ret->Divide(h1);

  return ret;

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

  getDATAresults( kSample, icent, ix, hRef, sRef);
  getDATAresults( kSample, icent, ix, h2, "syssys", nSys);
  
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
  if ( nSys < 0)   fin = new TFile(Form("unfSpectra/%s/kSample%d_matrixRwt%d_spectraRwt%d.root",dir.Data(),kSample, (int)matRwt, (int)specRwt));
  else    fin = new TFile(Form("unfSpectra/sys/kSample%d_matrixRwt%d_spectraRwt%d_sys%d.root",kSample, (int)matRwt, (int)specRwt, nSys) );
  TH1D* hUnf = (TH1D*)fin->Get(Form("hdataUnf1d_icent%d_ix%d_iter%d",icent,ix,nIter));
  
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
    cout << " Incompatible histograms!!" << endl;
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


void sortPlusMinus(TH1D* hp, TH1D* hm) {
  if ( hp->GetNbinsX() != hm->GetNbinsX() ) {
    cout << " Uncompatible histograms!!" << endl;
    return;
  }

  int nBins = hp->GetNbinsX();
  for ( int ii=0 ; ii<=nBins ; ii++) {
    double y1 = hp->GetBinContent(ii);
    double y2 = hm->GetBinContent(ii);
    if ( y1 > y2 )  {
      hp->SetBinContent( ii, y1);
      hm->SetBinContent( ii, y2);
    }
    else  {
      hp->SetBinContent( ii, y2);
      hm->SetBinContent( ii, y1);
    }
  }
}

double getJMRsigma(int kSample=0, int icent=0, double jetPt=0) { 
  // These values can be obtained from getJMR.C macro
  double p0, p1;
  if ( kSample == kPP) {
    p0 = 0.23 ;
    p1 = -0.000009;
  }
  else if ( kSample == kPbPb) {
    if ( icent ==0) {
      p0 = 0.29;      
      p1 = -0.000046;
    }
    if ( icent ==1) {
      p0 = 0.28;      
      p1 = -0.000041;
    }
    if ( icent ==2) {
      p0 = 0.27 ;      
      p1 = -0.000028;
    }
    if ( icent ==3) {
      p0 = 0.26;      
      p1 = -0.000027;
    }
    if ( icent ==4) {
      p0 = 0.25;      
      p1 = -0.000023;
    }
    if ( icent ==5) {
      p0 = 0.24 ;      
      p1 = -0.000014;
    }
    if ( icent ==6) {
      p0 = 0.24;      
      p1 = -0.000011;
    }
  }
  
  return p0  + p1 * jetPt;
}

double getJMSscale(int kSample=0, int icent=0, double jetPt=0) { 
  // These values can be obtained from getJMR.C macro
  double p0, p1;
  if ( kSample == kPP) {
    p0 = 5.64677e-01   ;
    p1 = 9.77777e-02  ;
  }
  else if ( kSample == kPbPb) {
    if ( icent ==0) {
      p0=  8.68347e-01;
      p1=  4.98060e-02;
    }
    if ( icent ==1) {
      p0 = 7.72952e-01   ;
      p1 = 6.42673e-02   ;
    }
    if ( icent ==2) {
      p0 = 7.05166e-01   ;
      p1 = 7.41717e-02   ;
    }
    if ( icent ==3) {
      p0 = 6.41878e-01   ;
      p1 = 8.43167e-02   ;
    }
    if ( icent ==4) {
      p0 = 6.08245e-01   ;
      p1 = 8.93995e-02   ;
    }
    if ( icent ==5) {
      p0 = 5.85829e-01   ;
      p1 = 9.26819e-02    ;
    }
    if ( icent ==6) {
      p0 =  5.61321e-01   ;
      p1 =  9.70274e-02   ;
    }
  }
  
  return p0  + p1 * log(jetPt);
}


double getRtrk(int kSample=0, int icent=0, double jetPt=0) {
  // These values can be obtained from getJMR.C macro
  double p0, p1, p2;
  if ( kSample == kPP) {
    //    p0 = 8.41757e-01; p1 = 8.26199e-02 ; p2 = -1.05534e-02;
    p0 = 4.40588e-01; p1 = 2.41911e-01 ; p2 = -2.63250e-02;
  }
  else if ( kSample == kPbPb) {
    if ( icent ==0) {
      p0 = -4.56321e-01  ; p1 =  5.55171e-01 ;  p2 = -5.26155e-02 ;   
    }
    if ( icent ==1) {
      p0 = 2.00967e-01  ; p1 =   3.00164e-01;  p2 =  -2.83054e-02 ;   
    }
    if ( icent ==2) {
      p0= -0.5207;  p1 =  5.86584e-01; p2 = -5.68520e-02;
    }
    if ( icent ==3) {
      p0= 7.95068e-01; p1=  8.19498e-02; p2 =  -8.89938e-03;
    }
    if ( icent ==4) {
    p0 = 2.00140e+00;     p1 = -3.79735e-01;    p2 =3.51096e-02;
    }
    if ( icent ==5) {
      p0 = -1.52238e+00; p1 =   9.68029e-01 ; p2 =   -9.34660e-02;
    }
    if ( icent ==6) {
      p0 = -1.48588e+00; p1 =  1.00748e+00 ; p2 = -1.02264e-01;
    }
  }
  
  return p0  + p1 * log(jetPt) + p2 * log(jetPt)* log(jetPt);
}

double getRtrkHerwig(int kSample=0, int icent=0, double jetPt=0) {
  double p0, p1, p2;
  p0 =  1.26920e+00;
  p1 =  -5.59201e-02;
  p2 =  2.73860e-05;
  return p0  + p1 * log(jetPt) + p2 * log(jetPt)* log(jetPt);
}

void addSysInQuad3(JetSys jstot, JetSys js1, int lowX, int highX) { 
  for ( int ix=lowX ; ix<=highX ; ix++) {
    addSysInQuad(jstot.pp[ix], js1.pp[ix]);
    addSysInQuad(jstot.pbpb[ix], js1.pbpb[ix]);
    addSysInQuad(jstot.raa[ix], js1.raa[ix]);
  }

}

void getInverse(JetSys inputSys, JetSys outputSys,  int lowX, int highX) {
  for ( int ix=lowX ; ix<=highX ; ix++) {
    outputSys.pp[ix]->Reset();
    outputSys.pp[ix]->Add(inputSys.pp[ix], -1);
    outputSys.pbpb[ix]->Reset();
    outputSys.pbpb[ix]->Add(inputSys.pbpb[ix], -1);
    outputSys.raa[ix]->Reset();
    outputSys.raa[ix]->Add(inputSys.raa[ix], -1);
  }
}


double getJmrUnc(int kSample=0, int icent=0, double jetPt = 0) { 

  double pedestal = 0.2;
  double diffEmTopoHI = 0.06 + 0.06* ((jetPt-300.)/150.) * ((jetPt-300.)/150.) ;
  //  return  sqrt ( diffEmTopoHI*diffEmTopoHI + pedestal*pedestal) ;
  return  diffEmTopoHI + pedestal ;
}

double getJmrUncHI(int kSample=0, int icent=0, double jetPt = 0) { 
  
  double hiComp = 0;
  if (kSample == kPbPb) { 
    if (icent ==0)     hiComp = 0.06/0.29;
    if (icent ==1)     hiComp = 0.05/0.28;
    if (icent ==2)     hiComp = 0.04/0.27;
    if (icent ==3)     hiComp = 0.03/0.26;
    if (icent ==4)     hiComp = 0.02/0.25;
    if (icent ==5)     hiComp = 0.01/0.24;
    if (icent ==6)     hiComp = 0.01/0.23;
  }
  return  hiComp;
}
