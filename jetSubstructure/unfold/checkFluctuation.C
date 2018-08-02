#include "../getSdHists.C"
#include "../ntupleDefinition.h"
#include "../commonUtility.h"
#include "../jzWeight.h"
#include "../commonUtility.h"
#include "../JssUtils.h"
#include "unfoldingUtil.h"

struct valErr {
  double val;
  double err;
};

//void getMCresults(int kSample=0, int icent=0, int ix=0, int nIter=0,  bool matRwt=1, bool specRwt=0,  TH1D* hmcTruthSq=0, TH1D* hmcRawSq=0, TH1D* hmcUnfSq=0);

int optX=1;
int optY=2;

valErr  getDATApoint(int kSample=0, int icent=0, int etaBin=0, int ix=0, int nIter=0,  bool matRwt=1, bool specRwt=0, int massBin = 2);

void checkFluctuation(int kSample= kPP,  int icent = 0, int etaBin=0, int massBin = 5){
  
  bool matRwt=1; bool specRwt=1; 

  const int nIter = 25;
  
  int nXbins;
  double xBin[30];
  getXbin(nXbins, xBin, optX);
  
  int nYbins ;
  double yBin[30] ;
  getYbin(nYbins, yBin, optY);

  if ( (kSample == kPP) && (icent!=0) ) {
    cout << " pp sample must have cent = 0" << endl;
    return;
  }
  
  int lowPtBin = 6;
  int highPtBin = nXbins-1;
  int nPtPannels = highPtBin-lowPtBin+1;

  TH1D* hStat[30];
  TH1D* hDevi[30];
  for ( int ix = lowPtBin ; ix<= highPtBin ; ix++)  { 
    hStat[ix] = new TH1D(Form("hstat_ix%d",ix),";Numberof iteration;Relative uncertainty",29,0.5,29.5);
    hDevi[ix] = (TH1D*)hStat[ix]->Clone(Form("hdevi_ix%d",ix));
  }

  
  TCanvas* c1=  new TCanvas("c1","",1400,400);
  c1->Divide(nPtPannels,1,0,0);
  
  for ( int ipt = lowPtBin ; ipt<= highPtBin ; ipt++)  {

    c1->cd(ipt - lowPtBin + 1);
    
    vector<valErr> vPair;
    valErr nullVal;   nullVal.val = 0 ;  nullVal.err = 0 ;
    vPair.push_back(nullVal);
    
    for (int in = 1; in <= nIter+1 ; in++) {
      vPair.push_back( getDATApoint(kSample, icent, etaBin, ipt, in, matRwt, specRwt, massBin) ) ; 
    }
    for (int in = 2; in <= nIter ; in++) {
      hStat[ipt]->SetBinContent( in, vPair.at(in).err / vPair.at(in).val) ;
      hDevi[ipt]->SetBinContent( in, fabs(vPair.at(in-1).val - vPair.at(in).val)/vPair.at(in).val ) ;
      hStat[ipt]->SetBinError( in, 0.0000001);
      hDevi[ipt]->SetBinError( in, 0.0000001);
    }    
    handsomeTH1(hStat[ipt],4,1,26);
    handsomeTH1(hDevi[ipt],2,1,32);

    //    int fScale = 5;
    //    if ( ipt > lowPtBin + 2)  hStat[ipt]->Scale(1./fScale);
    if ( icent <=3)  hStat[ipt]->SetAxisRange(-0.01,0.03,"Y");
    else if ( icent ==4)  hStat[ipt]->SetAxisRange(-0.50,1.21,"Y");
    else if ( icent ==5)  hStat[ipt]->SetAxisRange(-0.50,1.21,"Y");
    else if ( icent ==6)  hStat[ipt]->SetAxisRange(-1.0,5.1,"Y");
    hStat[ipt]->Draw();
    hDevi[ipt]->Draw("same");


    if ( ipt == lowPtBin ) {
      drawCentrality(kSample, icent, 0.38,0.86,1,24);
      TLegend *leg1 = new TLegend(0.3830109,0.5370667,0.9199772,0.74624,NULL,"brNDC");
      easyLeg(leg1,Form("%.2f < m/p_{T} < %.2f",(float)yBin[massBin-1], (float)yBin[massBin]),0.07);
      leg1->AddEntry(hStat[ipt], "Stat. uncertainty","p");
      leg1->AddEntry(hDevi[ipt], "|y_{N} - y_{N-1}| / y_{N}","p");
      leg1->Draw();
      ATLASLabel(0.2,0.93,"Internal",0.08,0.28);
    }
    drawBin(xBin,ipt,"GeV",0.33 + (0.05* (ipt==lowPtBin)), 0.78,1,20);
    //    if ( ipt > lowPtBin + 2) 
      //      drawText(Form("Stat. Unc scaled by 1/%d",fScale), 0.16 + (0.05* (ipt==lowPtBin)), 0.3,1,16);
    jumSun(0,0,49,0);
  }
  c1->SaveAs(Form("choiceIter/data_coll%d_icent%d_matrixRwt%d_spectraRwt%d_massBin%d.pdf",kSample,icent,(int)matRwt, (int)specRwt,massBin));
}

valErr getDATApoint(int kSample, int icent, int etaBin, int ix, int nIter,  bool matRwt, bool specRwt, int massBin) {
  TFile * fin = new TFile(Form("unfSpectra/kSample%d_etaBin%d_matrixRwt%d_spectraRwt%d_optX%d_optY%d.root",kSample, etaBin, (int)matRwt, (int)specRwt, optX, optY));
  TH1D* hUnf = (TH1D*)fin->Get(Form("hdataUnf1d_icent%d_ix%d_iter%d",icent,ix,nIter));
  valErr ret ; 
  ret.val = hUnf->GetBinContent( massBin );
  ret.err = hUnf->GetBinError( massBin);
  return ret;
}

