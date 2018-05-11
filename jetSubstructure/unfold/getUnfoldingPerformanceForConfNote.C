#include "../getSdHists.C"
#include "../ntupleDefinition.h"
#include "../commonUtility.h"
#include "../jzWeight.h"
#include "../commonUtility.h"
#include "../JssUtils.h"
#include "unfoldingUtil.h"

void getMCresults(int kSample=0, int icent=0, int ix=0, int nIter=0,  bool matRwt=1, bool specRwt=0,  TH1D* hmcTruth1d=0, TH1D* hmcRaw1d=0, TH1D* hmcUnf1d=0);
void getDATAresults(int kSample=0, int icent=0, int ix=0, int nIter=0,  bool matRwt=1, bool specRwt=0, TH1D* hdataRaw1d=0, TH1D* hdataUnf1d=0);

void getUnfoldingPerformanceForConfNote(int kSample= kPP, int icent = 0, bool matRwt=1, bool specRwt=1, int optX=1, int optY=2, bool applyMDJ=false) {
  
  bool doDATA = true; 

  int nXbins;
  double xBin[30];
  getXbin(nXbins, xBin, optX);

  int nYbins ;
  double yBin[30] ;
  getYbin(nYbins, yBin, optY);
  TH1D* tempHistY;
  if ( optY == 1 ) tempHistY = new TH1D("tempHistY",";mass(GeV);",nYbins,yBin);
  if ( optY == 2 ) tempHistY = new TH1D("tempHistY",";m/p_{T};",nYbins,yBin);
  
  
  if ( (kSample == kPP) && (icent!=0) ) {
    cout << " pp sample must have cent = 0" << endl;
    return;
  }
  
  //  int lowPtBin = 6;
  //  int highPtBin = nXbins-2;
  int lowPtBin = 6;
  int highPtBin = 6;
  int nPtPannels = highPtBin-lowPtBin+1;

  const int maxIter = 50;
  vector<int> vIter;  //2 3 4 6 8 10
  vector<int> color;  //2 3 4 6 8 10

  vIter.push_back(6);   color.push_back (1);

  int refIt = vIter.size() -1;
  

  if ( vIter.size() > maxIter)   {
    cout << "Not enough room in the array" << endl;
    return; 
  }

  TH1D* hmcUnf1d[20][maxIter]; //  pT, iteration
  TH1D* hmcTruth1d[20][maxIter]; 
  TH1D* hmcRaw1d[20][maxIter]; 
  TH1D* hmcRatio1d[20][maxIter];

  TH1D* hdataUnf1d[30][maxIter]; 
  TH1D* hdataRaw1d[30][maxIter]; 
  TH1D* hdataRatio1d[30][maxIter];
  

  
  for ( int ix = lowPtBin ; ix<= highPtBin ; ix++)  { 
    for ( int in = 0 ; in< int(vIter.size()) ; in++)  {//    for (int icent = 1 ; icent<=8 ; icent++)  { 
      hmcUnf1d[ix][in] = (TH1D*)tempHistY->Clone(Form("mcUnf1d_ix%d_in%d",ix,in));
      hmcTruth1d[ix][in] = (TH1D*)tempHistY->Clone(Form("mcTruth1d_ix%d_in%d",ix,in));
      hmcRaw1d[ix][in] = (TH1D*)tempHistY->Clone(Form("mcRaw1d_ix%d_in%d",ix,in));
      getMCresults(kSample, icent, ix, vIter.at(in), matRwt, specRwt , hmcTruth1d[ix][in], hmcRaw1d[ix][in], hmcUnf1d[ix][in]);

      if ( doDATA) { 
	hdataUnf1d[ix][in] = (TH1D*)tempHistY->Clone(Form("dataUnf1d_ix%d_in%d",ix,in));
	hdataRaw1d[ix][in] = (TH1D*)tempHistY->Clone(Form("dataRaw1d_ix%d_in%d",ix,in));
	getDATAresults(kSample, icent, ix, vIter.at(in), matRwt, specRwt ,  hdataRaw1d[ix][in], hdataUnf1d[ix][in]);
      }  
      cout << hmcUnf1d[ix][in]->GetName() << " : " << hmcUnf1d[ix][in]->Integral(1, hmcUnf1d[ix][in]->GetNbinsX(), "width") << endl;
      cout << hmcTruth1d[ix][in]->GetName() << " : " <<  hmcTruth1d[ix][in]->Integral(1, hmcTruth1d[ix][in]->GetNbinsX(),"width")  << endl;
    }
  }
  
  
  TCanvas* c1=  new TCanvas("c1","",500,500);
  //  makeEfficiencyCanvas(c1,nPtPannels, 0.05, 0.01, 0.1, 0.3, 0.01);
  
  for ( int ipt = lowPtBin ; ipt<= highPtBin ; ipt++)  {
    c1->cd(ipt - lowPtBin + 1);
    
    for (int in = 0; in < int(vIter.size()) ; in++)  {

      hmcTruth1d[ipt][in]->SetAxisRange(0.001,0.2999,"X");
      hmcTruth1d[ipt][in]->SetXTitle("m/p_{T}");
      
      if ( hmcTruth1d[ipt][in]->Integral()>0) cleverRangeLog(hmcTruth1d[ipt][in],100,0.000002);
      hmcTruth1d[ipt][in]->SetYTitle("Entries");
      handsomeTH1(hmcTruth1d[ipt][in],1);
      handsomeTH1(hmcRaw1d[ipt][in],1);
      handsomeTH1(hmcUnf1d[ipt][in],color[in]);
      
      fixedFontHist(hmcTruth1d[ipt][in],2,2,20);
      if ( in == 0 )  {
	hmcTruth1d[ipt][in]->SetLineStyle(2);
	hmcTruth1d[ipt][in]->Draw("hist");
	hmcRaw1d[ipt][in]->Draw("hist same");
      }
      hmcUnf1d[ipt][in]->Draw("same e");
      
      gPad->SetLogy();
    }
    drawBinPt(xBin,ipt,"GeV",0.20,0.78,1,16);
  
    if ( ipt == lowPtBin ) {
      drawCentrality(kSample, icent, 0.20,0.86,1,24);
      if ( ipt == lowPtBin ) {
	TLegend *leg1 = new TLegend(0.6222575,0.7273776,1,0.9378835,NULL,"brNDC");
        easyLeg(leg1,"MC");
	leg1->AddEntry(hmcTruth1d[ipt][0], "Truth","l");
	leg1->AddEntry(hmcRaw1d[ipt][0], "Raw","l");
        leg1->Draw();
      }
    }
    if ( (nPtPannels ==1 ) || ( ipt == lowPtBin+1 ) ) {
      /*      TLegend * leg1 = new TLegend(0.2067083,0.0631472,0.6655156,0.6348713,NULL,"brNDC");
      //      easyLeg(leg1,"Unfolded",0.06);
      easyLeg(leg1,"Unfolded");
      for (int in = 0; in < int(vIter.size()) ; in++)  {
	if ( vIter[in] == 1 ) leg1->AddEntry(hmcUnf1d[ipt][in], Form("%dst iter.",vIter[in]));
	else if ( vIter[in] == 2 ) leg1->AddEntry(hmcUnf1d[ipt][in], Form("%dnd iter.",vIter[in]));
	else  leg1->AddEntry(hmcUnf1d[ipt][in], Form("%dth iter.",vIter[in]));
      }
      leg1->Draw();*/
    }
    TLegend* leg2 = new TLegend(0.2060963,0.02083363,0.8352797,0.2113352,NULL,"brNDC");
    easyLeg(leg2,"N_{Unf.} - N_{Truth}",0.13);
    for (int in = 0; in < int(vIter.size()) ; in++)  {
    
      double mig = hmcUnf1d[ipt][in]->Integral(1, hmcUnf1d[ipt][in]->GetNbinsX(), "width") -  hmcTruth1d[ipt][in]->Integral(1, hmcTruth1d[ipt][in]->GetNbinsX(),"width" ) ;
      leg2->AddEntry(hmcUnf1d[ipt][in],Form("%.3f",(float)mig));
    }

}
  

  c1->SaveAs(Form("stabilitiy/mc_coll%d_icent%d_matrixRwt%d_spectraRwt%d_confNote.pdf",kSample,icent,(int)matRwt, (int)specRwt));
  
  
  if (doDATA) {
    TCanvas* c2 =  new TCanvas("c2","",500,500);
    //  c2->Divide((nPtBinDraw+1)/2,2);
    //    makeEfficiencyCanvas(c2,nPtPannels, 0.05, 0.01, 0.1, 0.3, 0.01);
    
    for ( int ipt = lowPtBin ; ipt<= highPtBin ; ipt++)  {
      c2->cd(ipt - lowPtBin + 1);
      
      for (int in = 0; in < int(vIter.size()) ; in++)  {
	hdataRaw1d[ipt][in]->SetAxisRange(0.001,0.2999,"X");
	hdataRaw1d[ipt][in]->SetXTitle("m/p_{T}");

	if ( hdataRaw1d[ipt][in]->Integral()>0) cleverRangeLog(hdataRaw1d[ipt][in],100,0.000001);
	hdataRaw1d[ipt][in]->SetYTitle("Entries");
	handsomeTH1(hdataRaw1d[ipt][in],1);
	handsomeTH1(hdataUnf1d[ipt][in],color[in]);

	//	hdataUnf1d[ipt][in]->SetMarkerSize(0);

	hdataRaw1d[ipt][in]->SetNdivisions(505,"X");
        hdataRaw1d[ipt][in]->SetTitleSize(.12,"X");
        hdataRaw1d[ipt][in]->SetTitleSize(0.07,"Y");
	fixedFontHist(hdataRaw1d[ipt][in],2,2,25);
        hdataRaw1d[ipt][in]->GetXaxis()->SetTitleOffset(1.2);
        hdataRaw1d[ipt][in]->GetYaxis()->SetTitleOffset(1.2);
	
	if ( in == 0 )  {
	  hdataRaw1d[ipt][in]->Draw("hist");
	}
	hdataUnf1d[ipt][in]->Draw("same e");
     
	//	if ( ipt==lowPtBin+1)  drawText(Form("Iteration: %d"iter), 0.45,0.86,1,24);
	
      }
      gPad->SetLogy();
      
      if ( ipt == lowPtBin ) {
	TLegend *leg1 = new TLegend(0.6222575,0.7273776,1,0.9378835,NULL,"brNDC");
	easyLeg(leg1,"");
	leg1->AddEntry(hmcRaw1d[ipt][0], "Reco","l");
	leg1->AddEntry(hdataUnf1d[ipt][0], "Unfolded","pl");
	leg1->Draw();
      }
      
      if ( (nPtPannels ==1 ) || ( ipt == lowPtBin+1 ) ) {
	ATLASLabel(0.2,0.88,"Internal",0.05,0.16);
	drawCentrality(kSample, icent, 0.2,0.82,1,24);
	drawBinPt(xBin,ipt,"GeV",0.20,0.75,1,18);
	TLegend *leg1 = new TLegend(0.1372267,0.04771138,0.6589362,0.4161378,NULL,"brNDC");
	easyLeg(leg1,"Unfolded",0.08);
	for (int in = 0; in < int(vIter.size()) ; in++)  {
	  if ( vIter[in] == 1 ) leg1->AddEntry(hmcUnf1d[ipt][in], Form("%dst iter.",vIter[in]));
	  else if ( vIter[in] == 2 ) leg1->AddEntry(hmcUnf1d[ipt][in], Form("%dnd iter.",vIter[in]));
	else  leg1->AddEntry(hmcUnf1d[ipt][in], Form("%dth iter.",vIter[in]));
	}
	//      leg1->Draw();
      }
    }
    
    c2->SaveAs(Form("stabilitiy/data_coll%d_icent%d_matrixRwt%d_spectraRwt%d_confNote.pdf",kSample,icent,(int)matRwt, (int)specRwt));
    
  }
  
  TCanvas* labelCanvas =  new TCanvas("tlegend","",497,54,228,327); 
  TLegend* leg1 = new TLegend(0.1372267,0.04771138,1.0589362,0.9561378,NULL,"brNDC");
  easyLeg(leg1,"Unfolded",0.08);
  for (int in = 0; in < int(vIter.size()) ; in++)  {
    if ( vIter[in] == 1 ) leg1->AddEntry(hmcUnf1d[lowPtBin][in], Form("%dst iter.",vIter[in]));
    else if ( vIter[in] == 2 ) leg1->AddEntry(hmcUnf1d[lowPtBin][in], Form("%dnd iter.",vIter[in]));
    else  leg1->AddEntry(hmcUnf1d[lowPtBin][in], Form("%dth iter.",vIter[in]));
  }
  leg1->Draw();
  labelCanvas->SaveAs("stabilitiy/iterationLabel.pdf");
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
  c11->SaveAs(Form("pdfs/mcVsData_coll%d_icent%d_ratio_singlePt.pdf",kSample,icent));
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
    c2->SaveAs(Form("pdfs/unfoldingStability_coll%d_icent%d_nIter%d_singlePt.pdf",kSample,icent,vIter[in]));
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
  cOverlay->SaveAs(Form("pdfs/unfoldingStability_coll%d_icent%d_Overlay_singlePt.pdf",kSample,icent));
  cOverlay->SaveAs(Form("pdfs/unfoldingStability_coll%d_icent%d_Overlay.png",kSample,icent));
}
  */



void getMCresults(int kSample, int icent, int ix, int nIter, bool matRwt, bool specRwt,  TH1D* hmcTruth1d, TH1D* hmcRaw1d, TH1D* hmcUnf1d) {
  TFile * fin = new TFile(Form("unfSpectra/kSample%d_matrixRwt%d_spectraRwt%d.root",kSample, (int)matRwt, (int)specRwt));
  TH1D* hUnf = (TH1D*)fin->Get(Form("hmcUnf1d_icent%d_ix%d_iter%d",icent,ix,nIter));
  TH1D* hTruth = (TH1D*)fin->Get(Form("hmcTruth1d_icent%d_ix%d",icent,ix));
  TH1D* hRaw = (TH1D*)fin->Get(Form("hmcRaw1d_icent%d_ix%d",icent,ix));
  
  hmcTruth1d->Reset();
  hmcTruth1d->Add(hTruth);
  hmcUnf1d->Reset();
  hmcUnf1d->Add(hUnf);
  hmcRaw1d->Reset();
  hmcRaw1d->Add(hRaw);


}

void getDATAresults(int kSample, int icent, int ix, int nIter,  bool matRwt, bool specRwt, TH1D* hdataRaw1d, TH1D* hdataUnf1d) {
  TFile * fin = new TFile(Form("unfSpectra/kSample%d_matrixRwt%d_spectraRwt%d.root",kSample, (int)matRwt, (int)specRwt));
  TH1D* hUnf = (TH1D*)fin->Get(Form("hdataUnf1d_icent%d_ix%d_iter%d",icent,ix,nIter));
  TH1D* hRaw = (TH1D*)fin->Get(Form("hdataRaw1d_icent%d_ix%d",icent,ix));

  hdataUnf1d->Reset();
  hdataUnf1d->Add(hUnf);
  hdataRaw1d->Reset();
  hdataRaw1d->Add(hRaw);

}

