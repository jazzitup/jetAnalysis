#include "unfoldingUtils.h"



void getRAA(int icent=0, int optY=2, int nIter = 4) {
  //  double ptBin[9]= {100, 126, 158, 200, 251, 316, 398, 501, 800};
  //  double ptBin[9]= {110, 136, 150, 168, 200, 251, 398, 501, 800};
  //  const int nPtBin = 7;
  //  double ptBin[nPtBin+1] = {158, 200, 251, 316, 398, 501, 800};
  //  double ptBin[nPtBin+1] = {126, 158, 200, 251, 316, 398, 501, 800};
  
  const int nPtBin = 12;
  double ptBin[nPtBin+1]={63.096, 82., 100.000, 125.892,  158.488,  199.525,  251.186,  316.224,  398.101,  500.,  630.944,  794.308, 999.970};
  double RAA0[nPtBin+1] = {0  ,  0 ,  0,       0,      0.499,   0.520,   0.556,   0.577,  0.579,  0.609,  0.594,  0.581,  0.604 }; 
  double RAA0Err[nPtBin+1]={0  , 0 ,  0,       0,      0.014,   0.013,   0.014,   0.017,  0.018,  0.020,  0.020,  0.019,  0.024 }; 
  int lowPtBin = 4;
  int highPtBin = 10;
  int nPtBinDraw = highPtBin - lowPtBin + 1;

  TH1D* hmass[20][6][10]; // pt, kSample, centrality
  for ( int ipt = lowPtBin ; ipt<= highPtBin ; ipt++)  { 
    // pp 
    hmass[ipt][kPP][0] = getHisto(kPP, ipt,0,nIter,optY);
    // Pb Pb
    hmass[ipt][kPbPb][icent] = getHisto(kPbPb, ipt,icent,nIter,optY);
  }
  
  TCanvas* c1=  new TCanvas("c4","",1200,800);
  //  c1->Divide((nPtBinDraw+1)/2,2);
  makeMultiPanelCanvas(c1,(nPtBinDraw+1)/2,2);
  for ( int ipt = lowPtBin ; ipt<= highPtBin ; ipt++)  {
    
    c1->cd(ipt - lowPtBin + 1);
    TH1D* hpp = hmass[ipt][kPP][0] ; 
    cout << "pp integral (must be 1) = " << hpp->Integral("width") << endl;
    TH1D* haa ; 
    haa = hmass[ipt][kPbPb][icent];
    cout << "aa integral (must be 1) = " << haa->Integral("width") << endl;

    haa->Divide(hpp);
    haa->Scale(RAA0[ipt]);
    handsomeTH1(haa,1);
    haa->SetAxisRange(0,1.3,"Y");
    haa->SetAxisRange(0,0.25,"X");
    haa->SetXTitle("m/p_{T}");
    haa->Draw("");
    jumSun(0,1,0.3,1);
    
    drawErrorBox(0,1 - RAA0Err[ipt],0.03, 1 + RAA0Err[ipt],kRed ) ;
    
    if ( ipt==lowPtBin)  drawCentrality(kPbPb, icent, 0.25,0.85,1,22);
    drawBin(ptBin,ipt,"GeV",0.5,0.85,1,22);
    if ( ipt==lowPtBin)  drawText(Form("Iteration: %d",nIter),0.5,0.6,4,22);

    
  }
  c1->SaveAs(Form("RAA_iter%d.pdf",nIter));
  
}
/*
  if ( optY==1)  hRawMC[ipt][in]->SetAxisRange(-300,2000,"X");
    else if ( optY==2) hRawMC[ipt][in]->SetAxisRange(-0.02,0.08,"X");
    if ( optY==1)    hRawMC[ipt][in]->SetXTitle("m^{2} GeV^{2}");
    else if ( optY==2)    hRawMC[ipt][in]->SetXTitle("(m/p_{T})^{2})");
    if ( hRawMC[ipt][in]->Integral()>0) cleverRange(hRawMC[ipt][in],1.5);
    hRawMC[ipt][in]->SetYTitle("Entries (arbitraty unit)");
    hRawMC[ipt][in]->Draw("hist");
    hRawData[ipt][in]->Draw("same e");

    if ( ipt==lowPtBin)  drawCentrality(kSample, icent, 0.45,0.86,1,24);
    //    drawText(Form("%dth iteration / 4th",vIter[in]),0.45,0.7,2,14);
    drawBin(ptBin,ipt,"GeV",0.3,0.78,1,20);

  }
  c1->SaveAs(Form("pdfs/mcVsData_coll%d_icent%d.pdf",kSample,icent));



  for ( int in = 1 ; in< vIter.size() ; in++)  {//    for (int icent = 1 ; icent<=8 ; icent++)  { 
    TCanvas* c2=  new TCanvas(Form("c2_%d",in),"",1200,800);
    //    c2->Divide((nPtBinDraw+1)/2,2);
    makeMultiPanelCanvas(c2,(nPtBinDraw+1)/2,2);
    for ( int ipt = lowPtBin ; ipt<=highPtBin ; ipt++)  {
      c2->cd(ipt - lowPtBin +1);
      hmass[ipt][in]->Divide(hmass[ipt][0]);
      hmass[ipt][in]->SetAxisRange(0,3,"Y");
      hmass[ipt][in]->SetYTitle("Ratio");
      if ( optY==1)  hmass[ipt][in]->SetAxisRange(0,100,"X");
      else if ( optY==2) hmass[ipt][in]->SetAxisRange(0,0.27,"X");
      if ( optY==1)    hmass[ipt][in]->SetXTitle("m (GeV)");
      else if ( optY==2)    hmass[ipt][in]->SetXTitle("m/p_{T}");


      hmass[ipt][in]->Draw("e");
      if ( optY==1) jumSun(0,1,100,1);
      else if ( optY==2) jumSun(0,1,0.27,1);
      
      if ( ipt==lowPtBin)  drawCentrality(kSample, icent, 0.45,0.85,1,24);
      drawBin(ptBin,ipt,"GeV",0.45,0.76,1,18);
      drawText(Form("%dth iteration / 2nd",vIter[in]),0.45,0.65,2,16);
      
    }
    c2->SaveAs(Form("pdfs/unfoldingStability_coll%d_icent%d_nIter%d.pdf",kSample,icent,vIter[in]));
    
    
  }
  
}
*/
