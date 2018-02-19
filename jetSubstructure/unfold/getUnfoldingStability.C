#include "../getSdHists.C"
#include "../ntupleDefinition.h"
#include "../commonUtility.h"
#include "../jzWeight.h"
#include "../commonUtility.h"
#include "../JssUtils.h"
#include "unfoldingUtil.h"

void getMCresults(int kSample=0, int icent=0, int ix=0, int nIter=0,  TH1D* hmcTruthSq=0, TH1D* hmcRawSq=0, TH1D* hmcUnfSq=0);
void getDATAresults(int kSample=0, int icent=0, int ix=0, int nIter=0, TH1D* hdataRawSq=0, TH1D* hdataUnfSq=0);

void getUnfoldingStability(int kSample= kPP, int icent = 0, int optX=1, int optY=2) {
  
  bool doMC = false; 
  bool doDATA = false; 

  int nXbins;
  double xBin[30];
  getXbin(nXbins, xBin, optX);

  int nYbins ;
  double yBin[30] ;
  double yBinSqrt[30] ;
  getYbin(nYbins, yBin, yBinSqrt, optY);
  TH1D* tempHistYsq;
  if ( optY == 1 ) tempHistYsq = new TH1D("tempHistY",";mass(GeV);",nYbins,yBinSqrt);
  if ( optY == 2 ) tempHistYsq = new TH1D("tempHistY",";m/p_{T};",nYbins,yBinSqrt);
  
  
  if ( (kSample == kPP) && (icent!=0) ) {
    cout << " pp sample must have cent = 0" << endl;
    return;
  }
  
  int lowPtBin = 6;
  int highPtBin = 11;
  int nPtPannels = highPtBin-lowPtBin+1;

  vector<int> vIter;  //2 3 4 6 8 10
  vIter.push_back (1);
  vIter.push_back (2);
  vIter.push_back (4);
  vIter.push_back (6);
  vIter.push_back (8);
  
  vector<int> color;  //2 3 4 6 8 10
  color.push_back (1);
  color.push_back (2);
  color.push_back (4);
  color.push_back (6);
  color.push_back (8);
  color.push_back (9);
  color.push_back (30);
  color.push_back (28);

  
  

  TH1D* hmcUnfSq[20][10]; //  pT, iteration
  TH1D* hmcTruthSq[20][10]; 
  TH1D* hmcRawSq[20][10]; 
  TH1D* hmcRatioSq[20][10];

  TH1D* hdataUnfSq[30][10]; 
  TH1D* hdataRawSq[30][10]; 
  TH1D* hdataRatioSq[30][10];
  

  
  for ( int ix = lowPtBin ; ix<= highPtBin ; ix++)  { 
    for ( int in = 0 ; in< int(vIter.size()) ; in++)  {//    for (int icent = 1 ; icent<=8 ; icent++)  { 
      hmcUnfSq[ix][in] = (TH1D*)tempHistYsq->Clone(Form("mcUnfSq_ix%d_in%d",ix,in));
      hmcTruthSq[ix][in] = (TH1D*)tempHistYsq->Clone(Form("mcTruthSq_ix%d_in%d",ix,in));
      hmcRawSq[ix][in] = (TH1D*)tempHistYsq->Clone(Form("mcRawSq_ix%d_in%d",ix,in));

      hdataUnfSq[ix][in] = (TH1D*)tempHistYsq->Clone(Form("dataUnfSq_ix%d_in%d",ix,in));
      hdataRawSq[ix][in] = (TH1D*)tempHistYsq->Clone(Form("dataRawSq_ix%d_in%d",ix,in));


      getMCresults(kSample, icent, ix, vIter.at(in), hmcTruthSq[ix][in], hmcRawSq[ix][in], hmcUnfSq[ix][in]);
      getDATAresults(kSample, icent, ix, vIter.at(in),  hdataRawSq[ix][in], hdataUnfSq[ix][in]);
    }
  }
  
  
  TCanvas* c1=  new TCanvas("c1","",1200,550);
  makeEfficiencyCanvas(c1,nPtPannels, 0.05, 0.01, 0.1, 0.3, 0.01);
  
  for ( int ipt = lowPtBin ; ipt<= highPtBin ; ipt++)  {
    c1->cd(ipt - lowPtBin + 1);
    
    for (int in = 0; in < int(vIter.size()) ; in++)  {
      if ( optY==1)  hmcTruthSq[ipt][in]->SetAxisRange(-300,2000,"X");
      else if ( optY==2) hmcTruthSq[ipt][in]->SetAxisRange(0.001,0.2999,"X");
      if ( optY==1)    hmcTruthSq[ipt][in]->SetXTitle("m^{2} GeV^{2}");
      else if ( optY==2)    hmcTruthSq[ipt][in]->SetXTitle("m/p_{T}");
      if ( hmcTruthSq[ipt][in]->Integral()>0) cleverRangeLog(hmcTruthSq[ipt][in],100,0.000001);
      hmcTruthSq[ipt][in]->SetYTitle("Entries");
      handsomeTH1(hmcTruthSq[ipt][in],1);
      handsomeTH1(hmcRawSq[ipt][in],1);
      handsomeTH1(hmcUnfSq[ipt][in],in+2);
      
      
      if ( in == 0 )  {
	hmcTruthSq[ipt][in]->SetLineStyle(2);
	hmcTruthSq[ipt][in]->Draw("hist");
	hmcRawSq[ipt][in]->Draw("hist same");
      }
      hmcUnfSq[ipt][in]->Draw("same e");
      
      drawBin(xBin,ipt,"GeV",0.3,0.78,1,20);
      gPad->SetLogy();
      
    }
    
    if ( ipt == lowPtBin ) {
      drawCentrality(kSample, icent, 0.45,0.86,1,24);
      TLegend *leg1 = new  TLegend(0.2396099,0.1195233,0.7575544,0.3318368,NULL,"brNDC");
      easyLeg(leg1,"MC",0.08);
      leg1->AddEntry(hmcTruthSq[ipt][0], "Truth","l");
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
    
    c1->cd(ipt - lowPtBin + 1 + nPtPannels);
    for (int in = 0; in < int(vIter.size()) ; in++)  {
      hmcRatioSq[ipt][in] = (TH1D*)hmcUnfSq[ipt][in]->Clone(Form("mcRatioSq_ix%d_in%d",ipt,in));
      hmcRatioSq[ipt][in]->Divide(hmcTruthSq[ipt][in]);
      hmcRatioSq[ipt][in]->SetAxisRange(.5,1.5,"Y");
      hmcRatioSq[ipt][in]->SetAxisRange(0.001,0.299,"X");
      hmcRatioSq[ipt][in]->SetYTitle("Unfolded/Truth");
      hmcRatioSq[ipt][in]->SetNdivisions(505,"X");
      if ( in==0)  hmcRatioSq[ipt][in]->Draw();
      else  hmcRatioSq[ipt][in]->Draw("same");
      if ( optY == 2)  jumSun(0,1,0.3,1);
    }
  }
  c1->SaveAs(Form("stabilitiy/mc_coll%d_icent%d.pdf",kSample,icent));
  c1->SaveAs(Form("stabilitiy/mc_coll%d_icent%d.png",kSample,icent));
  
  
  TCanvas* c2 =  new TCanvas("c2","",1200,550);
  //  c2->Divide((nPtBinDraw+1)/2,2);
  makeEfficiencyCanvas(c2,nPtPannels, 0.05, 0.01, 0.1, 0.3, 0.01);

  for ( int ipt = lowPtBin ; ipt<= highPtBin ; ipt++)  {
    c2->cd(ipt - lowPtBin + 1);

    for (int in = 0; in < int(vIter.size()) ; in++)  {
      if ( optY==1)  hdataRawSq[ipt][in]->SetAxisRange(-300,2000,"X");
      else if ( optY==2) hdataRawSq[ipt][in]->SetAxisRange(0.001,0.2999,"X");
      if ( optY==1)    hdataRawSq[ipt][in]->SetXTitle("m^{2} GeV^{2}");
      else if ( optY==2)    hdataRawSq[ipt][in]->SetXTitle("m/p_{T}");
      if ( hdataRawSq[ipt][in]->Integral()>0) cleverRangeLog(hdataRawSq[ipt][in],100,0.000001);
      hdataRawSq[ipt][in]->SetYTitle("Entries");
      handsomeTH1(hdataRawSq[ipt][in],1);
      handsomeTH1(hdataUnfSq[ipt][in],in+2);
      
      if ( in == 0 )  {
        hdataRawSq[ipt][in]->Draw("hist");
      }
      hdataUnfSq[ipt][in]->Draw("same e");

      if ( ipt==lowPtBin)  drawCentrality(kSample, icent, 0.45,0.86,1,24);
      drawBin(xBin,ipt,"GeV",0.3,0.78,1,20);
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
      hdataRatioSq[ipt][in]->SetYTitle("Ratio to 1st iter.");
      hdataRatioSq[ipt][in]->SetNdivisions(505,"X");
      if ( drawFirst)  { 	hdataRatioSq[ipt][in]->Draw();
	drawFirst=false;  
      }
      else   hdataRatioSq[ipt][in]->Draw("same");
      if ( optY == 2)  jumSun(0,1,0.3,1);
    }
  }
  c2->SaveAs(Form("stabilitiy/data_coll%d_icent%d.pdf",kSample,icent));
  c2->SaveAs(Form("stabilitiy/data_coll%d_icent%d.png",kSample,icent));
  
  
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



void getMCresults(int kSample, int icent, int ix, int nIter,  TH1D* hmcTruthSq, TH1D* hmcRawSq, TH1D* hmcUnfSq) {
  TFile * fin = new TFile(Form("unfSpectra/kSample%d_matrixRwt1_spectraRwt1_iter%d.root",kSample,nIter));
  TH1D* hUnf = (TH1D*)fin->Get(Form("hmcUnfSq_icent%d_ix%d",icent,ix));
  TH1D* hTruth = (TH1D*)fin->Get(Form("hmcTruthSq_icent%d_ix%d",icent,ix));
  TH1D* hRaw = (TH1D*)fin->Get(Form("hmcRawSq_icent%d_ix%d",icent,ix));
  
  hmcTruthSq->Reset();
  hmcTruthSq->Add(hTruth);
  hmcUnfSq->Reset();
  hmcUnfSq->Add(hUnf);
  hmcRawSq->Reset();
  hmcRawSq->Add(hRaw);
}

void getDATAresults(int kSample, int icent, int ix, int nIter, TH1D* hdataRawSq, TH1D* hdataUnfSq) {
  TFile * fin = new TFile(Form("unfSpectra/kSample%d_matrixRwt1_spectraRwt0_iter%d.root",kSample,nIter));
  TH1D* hUnf = (TH1D*)fin->Get(Form("hdataUnfSq_icent%d_ix%d",icent,ix));
  TH1D* hRaw = (TH1D*)fin->Get(Form("hdataRawSq_icent%d_ix%d",icent,ix));

  hdataUnfSq->Reset();
  hdataUnfSq->Add(hUnf);
  hdataRawSq->Reset();
  hdataRawSq->Add(hRaw);


}

