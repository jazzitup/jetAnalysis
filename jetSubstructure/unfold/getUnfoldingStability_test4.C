#include "../JssUtils.h"


double minPt = 100;
double minPtMcTruth = 20;
TString prefix = ""; //Form("ptCut_%d_%d",(int)minPt,(int)minPtMcTruth);


int findLowerBoundBin( TH1* h, int r1=1, int r2=-1 ) {
  if  (r2 == -1 ) 
    r2 = h->GetNbinsX();
  
  double cand = 0;
  int ret = 1;
  for ( int i = r1 ; i<= r2 ; i++) {
    if ( i==r1 ) cand = h->GetBinContent(i);
    double val = h->GetBinContent(i);
    if ( val ==0 ) continue;
    if ( TMath::IsNaN( val) ) continue;

    if ( val < cand) {
      ret = i;
      cand = val;
    }

  }
  cout << "findLowerBoundBin returns " << ret << endl;
  return ret;
}

void getUnfoldingStability_test4(int kSample= kPP, int icent = 0, int optY=8) {
  //  double ptBin[9]= {100, 126, 158, 200, 251, 316, 398, 501, 800};
  //  double ptBin[9]= {110, 136, 150, 168, 200, 251, 398, 501, 800};
  //  const int nPtBin = 7;
  //  double ptBin[nPtBin+1] = {158, 200, 251, 316, 398, 501, 800};
  //  double ptBin[nPtBin+1] = {126, 158, 200, 251, 316, 398, 501, 800};
  if ( (kSample == kPP) && (icent!=0) ) {
    cout << " pp sample must have cent = 0" << endl;
    return;
  }
  

  const int nPtBin = 12;
  double ptBin[13]={63.096, 82., 100.000, 125.892,  158.488,  199.525,  251.186,  316.224,  398.101,  500.,  630.944,  794.308, 999.970};
  //  int lowPtBin = 1;
  //  int highPtBin = 2;
  int lowPtBin = 4;
  int highPtBin = 10;
  int nPtBinDraw = highPtBin - lowPtBin + 1;
  
  vector<int> vIter;  //2 3 4 6 8 10
  vIter.push_back (1);
  vIter.push_back (1);
  vIter.push_back (3);
  vIter.push_back (5);
  //  vIter.push_back (7);

  //  vIter.push_back (8);
  //  vIter.push_back (16);
  //  vIter.push_back (10);
  //  vIter.push_back (8);
  //  vIter.push_back (12);
  //  vIter.push_back (14);
  //  vIter.push_back (20);
  //  vIter.push_back (30);
  //  vIter.push_back (50);
  //  vIter.push_back (100);
  //  vIter.push_back (200);
  //  vIter.push_back (1000);

  TH1D* hmass[20][20]; // pt, iteration
  TH1D* hRawMC[20][20]; // pt, iteration
  TH1D* hRawData[20][20]; // pt, iteration
  for ( int ipt = lowPtBin ; ipt<= highPtBin ; ipt++)  { 
    for ( int in = 0 ; in< vIter.size() ; in++)  {//    for (int icent = 1 ; icent<=8 ; icent++)  { 
      if ( in == 0 ) {
	hmass[ipt][in] = getInitial_test4(kSample, ipt,icent,vIter[in],optY);
      }
      else { 
	hmass[ipt][in] = getFinal_test4(kSample, ipt,icent,vIter[in],optY);
      }
      hRawMC[ipt][in] = getMCRaw_test4(kSample, ipt,icent,vIter[in],optY);
      hRawData[ipt][in] = getDataRaw_test4(kSample, ipt,icent,vIter[in],optY);
    }
  }
  TCanvas* c1=  new TCanvas("c4","",1200,800);
  //  c1->Divide((nPtBinDraw+1)/2,2);
  makeMultiPanelCanvas(c1,(nPtBinDraw+1)/2,2);
  TH1D* theRatio[20] ;
  for ( int ipt = lowPtBin ; ipt<= highPtBin ; ipt++)  {
    int in = 0;
    c1->cd(ipt - lowPtBin + 1);
    scaleInt(hRawMC[ipt][in]) ; 
    scaleInt(hRawData[ipt][in]) ; 
    if ( optY==1)  hRawMC[ipt][in]->SetAxisRange(-300,2000,"X");
    else if ( optY==2) hRawMC[ipt][in]->SetAxisRange(-0.02,0.08,"X");
    if ( optY==1)    hRawMC[ipt][in]->SetXTitle("m^{2} GeV^{2}");
    else if ( optY==2)    hRawMC[ipt][in]->SetXTitle("(m/p_{T})^{2})");
    if ( hRawMC[ipt][in]->Integral()>0) cleverRange(hRawMC[ipt][in],1.5);
    hRawMC[ipt][in]->SetYTitle("Entries (arbitraty unit)");
    cleverRangeLog(hRawMC[ipt][in],15);
    hRawMC[ipt][in]->Draw("hist");
    hRawData[ipt][in]->Draw("same e");
    if ( ipt==lowPtBin)  drawCentrality(kSample, icent, 0.45,0.86,1,24);
    //    drawText(Form("%dth iteration / 4th",vIter[in]),0.45,0.7,2,14);
    drawBin(ptBin,ipt,"GeV",0.3,0.78,1,20);
    gPad->SetLogy();
    
    theRatio[ipt] = (TH1D*)hRawData[ipt][in]->Clone(Form("dataovermc_ipt%d",ipt));
    theRatio[ipt]->Divide(hRawMC[ipt][in]);
  }
  c1->SaveAs(Form("pdfs/mcVsData_coll%d_icent%d.pdf",kSample,icent));
  
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
      drawText(Form("%dth iter. / MC Truth",vIter[in]),0.45,0.65,2,16);
      hRatio[ipt][in]  = (TH1D*)hmass[ipt][in]->Clone(Form("hmass_ipt%d_in%d",ipt,in));
      
    }
    c2->SaveAs(Form("pdfs/unfoldingStability_coll%d_icent%d_nIter%d.pdf",kSample,icent,vIter[in]));
  }
  TCanvas* cOverlay=  new TCanvas("cOverlay","",1200,800);
  makeMultiPanelCanvas(cOverlay,(nPtBinDraw+1)/2,2);
  for ( int ipt = lowPtBin ; ipt<=highPtBin ; ipt++)  {
    cOverlay->cd(ipt - lowPtBin +1);
    TLegend *leg = new TLegend(0.2758281,0.0008063921,0.9970038,0.3762096,NULL,"brNDC");
    easyLeg(leg,"Ratio to MC Truth");
    for ( int in = 1 ; in< vIter.size() ; in++)  {  
      handsomeTH1(hRatio[ipt][in], in);
      hRatio[ipt][in]->SetAxisRange(0.,1.5,"Y");
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
