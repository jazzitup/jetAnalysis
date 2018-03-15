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

valErr  getDATApoint(int kSample=0, int icent=0, int ix=0, int nIter=0,  bool matRwt=1, bool specRwt=0, double massVal=-100);

void checkFluctuation(int kSample= kPP,  int icent = 0, bool matRwt=1, bool specRwt=0, int optX=1, int optY=2, double massVal=0.1){ 
  
  const int nIter = 40;
  
  int nXbins;
  double xBin[30];
  getXbin(nXbins, xBin, optX);
  
  int nYbins ;
  double yBin[30] ;
  double yBinSqrt[30] ;
  getYbin(nYbins, yBin, yBinSqrt, optY);

  if ( (kSample == kPP) && (icent!=0) ) {
    cout << " pp sample must have cent = 0" << endl;
    return;
  }
  
  int lowPtBin = 6;
  int highPtBin = nXbins-2;
  int nPtPannels = highPtBin-lowPtBin+1;

  TH1D* hStat[30];
  TH1D* hDevi[30];
  for ( int ix = lowPtBin ; ix<= highPtBin ; ix++)  { 
    hStat[ix] = new TH1D(Form("hstat_ix%d",ix),";Numberof iteration;Relative uncertainty",49,0.5,49.1);
    hDevi[ix] = (TH1D*)hStat[ix]->Clone(Form("hdevi_ix%d",ix));
  }

  
  TCanvas* c1=  new TCanvas("c1","",1400,400);
  c1->Divide(nPtPannels,1,0,0);
  
  for ( int ipt = lowPtBin ; ipt<= highPtBin ; ipt++)  {

    c1->cd(ipt - lowPtBin + 1);
    
    vector<valErr> vPair;
    valErr nullVal;   nullVal.val = 0 ;  nullVal.err = 0 ;
    vPair.push_back(nullVal);
    
    for (int in = 1; in <= nIter ; in++) {
      vPair.push_back( getDATApoint(kSample, icent, ipt, in, matRwt, specRwt, massVal) ) ; 
    }
    for (int in = 1; in <= nIter ; in++) {
      hStat[ipt]->SetBinContent( in, vPair.at(in).err / vPair.at(in).val) ;
      hDevi[ipt]->SetBinContent( in, (vPair.at(in).val - vPair.at(in-1).val)/vPair.at(in).val ) ;
      hStat[ipt]->SetBinError( in, 0.0000001);
      hDevi[ipt]->SetBinError( in, 0.0000001);
    }    
    handsomeTH1(hStat[ipt],4,1,24);
    handsomeTH1(hDevi[ipt],2,1,24);

    int fScale = 5;
    if ( ipt > lowPtBin + 2)  hStat[ipt]->Scale(1./fScale);
    hStat[ipt]->SetAxisRange(-0.05,0.05,"Y");
    hStat[ipt]->Draw();
    hDevi[ipt]->Draw("same");


    if ( ipt == lowPtBin ) {
      drawCentrality(kSample, icent, 0.25,0.86,1,24);
      TLegend *leg1 = new TLegend(0.2386514,0.2288023,0.7574586,0.4411159,NULL,"brNDC");
      easyLeg(leg1,Form("m/p_{T} = %.2f point",massVal));
      leg1->AddEntry(hStat[ipt], "Stat. uncertainty","p");
      leg1->AddEntry(hDevi[ipt], "(y_{N+1} - y_{N}) / y_{N}","p");
      leg1->Draw();
    }
    drawBin(xBin,ipt,"GeV",0.16 + (0.05* (ipt==lowPtBin)), 0.78,1,16);
    if ( ipt > lowPtBin + 2) 
      drawText(Form("Stat. Unc scaled by 1/%d",fScale), 0.16 + (0.05* (ipt==lowPtBin)), 0.3,1,16);
    jumSun(0,0,49,0);
  }
  c1->SaveAs(Form("choiceIter/data_coll%d_icent%d_matrixRwt%d_spectraRwt%d.png",kSample,icent,(int)matRwt, (int)specRwt));
}

/*
  if ( in == 0 )  {
	hmcTruthSq[ipt][in]->SetLineStyle(2);
	hmcTruthSq[ipt][in]->Draw("hist");
	hmcRawSq[ipt][in]->Draw("hist same");
      }
      hmcUnfSq[ipt][in]->Draw("same e");
      
      gPad->SetLogy();
    }
    drawBin(xBin,ipt,"GeV",0.16 + (0.05* (ipt==lowPtBin)), 0.78,1,16);
  
    if ( ipt == lowPtBin ) {
      TLegend *leg1 = new TLegend(0.2386514,0.2288023,0.7574586,0.4411159,NULL,"brNDC");
      easyLeg(leg1,"MC",0.13);
      leg1->AddEntry(hmcTruthSq[ipt][0], "Truth","l");
      leg1->AddEntry(hmcRawSq[ipt][0], "Raw (Reco)","l");
      leg1->Draw();
    }
    
    if ( ipt == lowPtBin+1 ) {
      TLegend * leg1 = new TLegend(0.1467083,0.0631472,0.6655156,0.4348713,NULL,"brNDC");
      easyLeg(leg1,"Unfolded",0.10);
      for (int in = 0; in < int(vIter.size()) ; in++)  {
	if ( vIter[in] == 1 ) leg1->AddEntry(hmcUnfSq[ipt][in], Form("%dst iter.",vIter[in]));
	else if ( vIter[in] == 2 ) leg1->AddEntry(hmcUnfSq[ipt][in], Form("%dnd iter.",vIter[in]));
	else  leg1->AddEntry(hmcUnfSq[ipt][in], Form("%dth iter.",vIter[in]));
      }
      leg1->Draw();
    }
    TLegend* leg2 = new TLegend(0.2060963,0.02083363,0.8352797,0.2113352,NULL,"brNDC");
    easyLeg(leg2,"N_{Unf.} - N_{Truth}",0.13);
    for (int in = 0; in < int(vIter.size()) ; in++)  {
    
      double mig = hmcUnfSq[ipt][in]->Integral(1, hmcUnfSq[ipt][in]->GetNbinsX(), "width") -  hmcTruthSq[ipt][in]->Integral(1, hmcTruthSq[ipt][in]->GetNbinsX(),"width" ) ;
      leg2->AddEntry(hmcUnfSq[ipt][in],Form("%.3f",(float)mig));
    }
    //    leg2->Draw();

    c1->cd(ipt - lowPtBin + 1 + nPtPannels);
    for (int in = 0; in < int(vIter.size()) ; in++)  {
      hmcRatioSq[ipt][in] = (TH1D*)hmcUnfSq[ipt][in]->Clone(Form("mcRatioSq_ix%d_in%d",ipt,in));
      hmcRatioSq[ipt][in]->Divide(hmcTruthSq[ipt][in]);
      hmcRatioSq[ipt][in]->SetAxisRange(.5,1.5,"Y");
      hmcRatioSq[ipt][in]->SetAxisRange(0.001,0.299,"X");
      if ( optY==1) hmcRatioSq[ipt][in]->SetAxisRange(0.00,100,"X");
      hmcRatioSq[ipt][in]->SetYTitle("Unfolded/Truth");
      hmcRatioSq[ipt][in]->SetNdivisions(505,"X");
      hmcRatioSq[ipt][in]->SetTitleSize(.15,"X");
      hmcRatioSq[ipt][in]->SetTitleSize(0.1,"Y");
      hmcRatioSq[ipt][in]->SetTitleOffset(.5,"X");
      hmcRatioSq[ipt][in]->SetTitleOffset(.7,"Y");
      
      if ( in==0)  hmcRatioSq[ipt][in]->Draw();
      else  hmcRatioSq[ipt][in]->Draw("same");
      if ( optY == 2)  jumSun(0,1,0.3,1);
      
    }
    
  

}
  
  c1->SaveAs(Form("stabilitiy/mc_coll%d_icent%d_matrixRwt%d_spectraRwt%d.pdf",kSample,icent,(int)matRwt, (int)specRwt));
  c1->SaveAs(Form("stabilitiy/mc_coll%d_icent%d_matrixRwt%d_spectraRwt%d.png",kSample,icent,(int)matRwt, (int)specRwt));
  
  
  if (doDATA) {
    TCanvas* c2 =  new TCanvas("c2","",1200,550);
    //  c2->Divide((nPtBinDraw+1)/2,2);
    makeEfficiencyCanvas(c2,nPtPannels, 0.05, 0.01, 0.1, 0.3, 0.01);
    
    for ( int ipt = lowPtBin ; ipt<= highPtBin ; ipt++)  {
      c2->cd(ipt - lowPtBin + 1);
      
      for (int in = 0; in < int(vIter.size()) ; in++)  {
	if ( optY==1) hdataRawSq[ipt][in]->SetAxisRange(0.00,100,"X");
	else if ( optY==2) hdataRawSq[ipt][in]->SetAxisRange(0.001,0.2999,"X");
	if ( optY==1)    hdataRawSq[ipt][in]->SetXTitle("m^{2} GeV^{2}");
	else if ( optY==2)    hdataRawSq[ipt][in]->SetXTitle("m/p_{T}");
	if ( hdataRawSq[ipt][in]->Integral()>0) cleverRangeLog(hdataRawSq[ipt][in],100,0.000001);
	hdataRawSq[ipt][in]->SetYTitle("Entries");
	handsomeTH1(hdataRawSq[ipt][in],1);
	handsomeTH1(hdataUnfSq[ipt][in],color[in]);
	
	if ( in == 0 )  {
	  hdataRawSq[ipt][in]->Draw("hist");
	}
	hdataUnfSq[ipt][in]->Draw("same e");
	
	if ( ipt==lowPtBin)  drawCentrality(kSample, icent, 0.45,0.86,1,24);
	//	if ( ipt==lowPtBin+1)  drawText(Form("Iteration: %d"iter), 0.45,0.86,1,24);
	drawBin(xBin,ipt,"GeV",0.2,0.78,1,18);
	gPad->SetLogy();
	
      }
      
      if ( ipt == lowPtBin ) {
	drawCentrality(kSample, icent, 0.45,0.86,1,24);
	TLegend *leg1 = new  TLegend(0.2396099,0.1195233,0.7575544,0.3318368,NULL,"brNDC");
	easyLeg(leg1,"Data",0.08);
	leg1->AddEntry(hmcRawSq[ipt][0], "Reco","l");
	leg1->Draw();
      }
      
      if ( ipt == lowPtBin+1 ) {
	drawCentrality(kSample, icent, 0.45,0.86,1,24);
	TLegend *leg1 = new TLegend(0.1372267,0.04771138,0.6589362,0.4161378,NULL,"brNDC");
	easyLeg(leg1,"Unfolded",0.08);
	for (int in = 0; in < int(vIter.size()) ; in++)  {
	  if ( vIter[in] == 1 ) leg1->AddEntry(hmcUnfSq[ipt][in], Form("%dst iter.",vIter[in]));
	  else if ( vIter[in] == 2 ) leg1->AddEntry(hmcUnfSq[ipt][in], Form("%dnd iter.",vIter[in]));
	else  leg1->AddEntry(hmcUnfSq[ipt][in], Form("%dth iter.",vIter[in]));
	}
      leg1->Draw();
      }
      
      
      c2->cd(ipt - lowPtBin + 1 + nPtPannels);
      bool drawFirst=true; 
      for (int in = 1; in < int(vIter.size()) ; in++)  {
	hdataRatioSq[ipt][in] = (TH1D*)hdataUnfSq[ipt][in]->Clone(Form("dataRatioSq_ix%d_in%d",ipt,in));
	hdataRatioSq[ipt][in]->Divide(hdataUnfSq[ipt][0]);
	hdataRatioSq[ipt][in]->SetAxisRange(0.5,1.5,"Y");
	hdataRatioSq[ipt][in]->SetAxisRange(0.001,0.299,"X");
	if ( optY==1)  hdataRatioSq[ipt][in]->SetAxisRange(0.00,100,"X");
	hdataRatioSq[ipt][in]->SetYTitle("Ratio to 4th iter.");
	hdataRatioSq[ipt][in]->SetNdivisions(505,"X");
	if ( drawFirst)  { 	hdataRatioSq[ipt][in]->Draw();
	  drawFirst=false;  
	}
	else   hdataRatioSq[ipt][in]->Draw("same");
	if ( optY == 2)  jumSun(0,1,0.3,1);
      }
    }
    c2->SaveAs(Form("stabilitiy/data_coll%d_icent%d_matrixRwt%d_spectraRwt%d.pdf",kSample,icent,(int)matRwt, (int)specRwt));
    c2->SaveAs(Form("stabilitiy/data_coll%d_icent%d_matrixRwt%d_spectraRwt%d.png",kSample,icent,(int)matRwt, (int)specRwt));
  }
  
}  



void getMCresults(int kSample, int icent, int ix, int nIter, bool matRwt, bool specRwt,  TH1D* hmcTruthSq, TH1D* hmcRawSq, TH1D* hmcUnfSq) {
  TFile * fin = new TFile(Form("unfSpectra/kSample%d_matrixRwt%d_spectraRwt%d.root",kSample, (int)matRwt, (int)specRwt));
  TH1D* hUnf = (TH1D*)fin->Get(Form("hmcUnfSq_icent%d_ix%d_iter%d",icent,ix,nIter));
  TH1D* hTruth = (TH1D*)fin->Get(Form("hmcTruthSq_icent%d_ix%d",icent,ix));
  TH1D* hRaw = (TH1D*)fin->Get(Form("hmcRawSq_icent%d_ix%d",icent,ix));
  
  hmcTruthSq->Reset();
  hmcTruthSq->Add(hTruth);
  hmcUnfSq->Reset();
  hmcUnfSq->Add(hUnf);
  hmcRawSq->Reset();
  hmcRawSq->Add(hRaw);
}

  */

valErr getDATApoint(int kSample, int icent, int ix, int nIter,  bool matRwt, bool specRwt, double massVal) {
  TFile * fin = new TFile(Form("unfSpectra/kSample%d_matrixRwt%d_spectraRwt%d.root",kSample, (int)matRwt, (int)specRwt));
  TH1D* hUnf = (TH1D*)fin->Get(Form("hdataUnfSq_icent%d_ix%d_iter%d",icent,ix,nIter));
  valErr ret ; 
  ret.val = hUnf->GetBinContent( hUnf->FindBin( massVal ) );
  ret.err = hUnf->GetBinError( hUnf->FindBin( massVal ) );
  return ret;
}

