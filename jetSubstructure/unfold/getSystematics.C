#include "../commonUtility.h"
#include "systematicsTool.h"

void groomHist(TH1D* h1) {
  h1->SetAxisRange(0.001,0.23,"X");
  h1->SetAxisRange(-0.98,0.98,"Y");
  h1->SetXTitle("m/p_{T}");
  h1->SetYTitle("Rel. uncertainty");
  h1->SetNdivisions(505,"X");
  h1->SetNdivisions(505,"Y");
  h1->SetLineWidth(2);
  fixedFontHist(h1,3,3,20);

}

void getSystematics(int icent = 0, bool drawPP = true) {
  int optX = 1;  int optY = 2;
  int nXbins;  double xBin[30];
  getXbin(nXbins, xBin, optX);
  int nYbins ;  double yBin[30] ;
  getYbin(nYbins, yBin, optY);

  int lowPtBin = 6;
  int highPtBin = nXbins-1;
  int nPtPannels = highPtBin-lowPtBin+1;

  vector<int> vIndPlus;
  vector<int> vIndMinus;

  int indexJER = 100;

  int indexJMR0 = 200;
  int indexJMR1 = 201;

  int indexJMS0 = 210;
  int indexJMS1 = 211; // EV
  int indexJMS2 = 213; // herwig 
  
  // int indexJMS3 = 212; // MV

  /*  for ( int i=0 ; i<=21 ; i++)   {
      if (i%2 == 0)  vIndPlus.push_back(i);  // pp JES
      else           vIndMinus.push_back(i);  // pp JES
      }*/
  vIndPlus.push_back(1);  vIndPlus.push_back(3);
  vIndPlus.push_back(5);  vIndPlus.push_back(7);
  vIndPlus.push_back(9);  vIndPlus.push_back(10);
  vIndPlus.push_back(12);  vIndPlus.push_back(14);
  vIndPlus.push_back(16);  vIndPlus.push_back(18);
  vIndPlus.push_back(20); 
  vIndPlus.push_back(102);  vIndPlus.push_back(104);  vIndPlus.push_back(106);

  vIndMinus.push_back(0);  vIndMinus.push_back(2);
  vIndMinus.push_back(4);  vIndMinus.push_back(6);
  vIndMinus.push_back(8);  vIndMinus.push_back(11);
  vIndMinus.push_back(13);  vIndMinus.push_back(15);
  vIndMinus.push_back(17);  vIndMinus.push_back(19);
  vIndMinus.push_back(21);
  vIndMinus.push_back(101);  vIndMinus.push_back(103);  vIndMinus.push_back(105);


  JetSys sysPlus[20];
  JetSys sysMinus[20];
  JetSys sysJer;
  JetSys sysJerInv;

  JetSys sysJms;
  JetSys sysJms1;
  JetSys sysJms2;
  JetSys sysJms3; // Difference in Calibrated and un-calibrated JMS results 

  JetSys sysJmr;
  JetSys sysJmr1;
  JetSys sysJmr2;


  JetSys sysJmsInv;
  JetSys sysJmrInv;
  
  JetSys sysJEStotPlus;
  JetSys sysJEStotMinus;

  JetSys sysUnfPlus;
  JetSys sysUnfMinus;

  JetSys sysFinalPlus;
  JetSys sysFinalMinus;
  
  

  for ( int is =0 ; is <  vIndPlus.size() ; is++) {
    sysPlus[is] = getSystematicsJES(icent, vIndPlus.at(is));
    sysMinus[is] = getSystematicsJES(icent, vIndMinus.at(is));
  }
  sysJer    = getSystematicsJES(icent, indexJER );
  sysJerInv = getSystematicsJES(icent, indexJER, -1 );

  sysJms    = getSystematicsJES(icent, indexJMS0,1, kMergeQuad);
  sysJms1    = getSystematicsJES(icent, indexJMS1 );
  sysJms2    = getSystematicsJES(icent, indexJMS2,1, kMergeQuad, 1); // do smooth
  sysJms3    = getSystematicsJMSCal();
  
  // smooth!! " "
  //    smoothSys3(sysJms2,  lowPtBin, highPtBin);


  addSysInQuad3(sysJms, sysJms1, lowPtBin, highPtBin);
  addSysInQuad3(sysJms, sysJms2, lowPtBin, highPtBin);
  addSysInQuad3(sysJms, sysJms3, lowPtBin, highPtBin);
  

  sysJmr     = getSystematicsJES(icent, indexJMR0 );
  sysJmr1    = getSystematicsJES(icent, indexJMR1 );
  addSysInQuad3(sysJmr, sysJmr1, lowPtBin, highPtBin);
  
  
  sysJmsInv = getSystematicsJES(icent, indexJMS0 );
  resetJetSys(sysJmsInv, lowPtBin, highPtBin) ;
  getInverse(sysJms, sysJmsInv, lowPtBin, highPtBin) ;
  
  sysJmrInv = getSystematicsJES(icent, indexJMR0 );
  resetJetSys(sysJmrInv, lowPtBin, highPtBin) ;
  getInverse(sysJmr, sysJmrInv, lowPtBin, highPtBin) ;
  
  sysUnfPlus = getSystematicsUnf(icent, 1);
  sysUnfMinus = getSystematicsUnf(icent, -1);
  
  // Sort plus nad minus for Unf
  for ( int ix = lowPtBin ; ix<= highPtBin ; ix++)  {
    sortPlusMinus(sysUnfPlus.pp[ix], sysUnfMinus.pp[ix]);
    sortPlusMinus(sysUnfPlus.pbpb[ix], sysUnfMinus.pbpb[ix]);
    sortPlusMinus(sysUnfPlus.raa[ix], sysUnfMinus.raa[ix]);
  }
  // Merge JES :
  for ( int ix = lowPtBin ; ix<= highPtBin ; ix++)  {
    sysJEStotPlus.pp[ix] = (TH1D*)sysPlus[0].pp[ix]->Clone(Form("sys_jes_plus_pp_ix%d",ix));
    sysJEStotPlus.pbpb[ix] = (TH1D*)sysJEStotPlus.pp[ix]->Clone(Form("sys_jes_plus_pbpb_ix%d",ix));
    sysJEStotPlus.raa[ix] = (TH1D*)sysJEStotPlus.pp[ix]->Clone(Form("sys_jes_plus_raa_ix%d",ix));
    sysJEStotMinus.pp[ix] = (TH1D*)sysMinus[0].pp[ix]->Clone(Form("sys_jes_minus_pp_ix%d",ix));
    sysJEStotMinus.pbpb[ix] = (TH1D*)sysJEStotMinus.pp[ix]->Clone(Form("sys_jes_minus_pbpb_ix%d",ix));
    sysJEStotMinus.raa[ix] = (TH1D*)sysJEStotMinus.pp[ix]->Clone(Form("sys_jes_minus_raa_ix%d",ix));
    sysFinalPlus.pp[ix] = (TH1D*)sysJEStotPlus.pp[ix]->Clone(Form("sys_finalPlus_pp_ix%d",ix));
    sysFinalPlus.pbpb[ix] = (TH1D*)sysJEStotPlus.pbpb[ix]->Clone(Form("sys_finalPlus_pbpb_ix%d",ix));
    sysFinalPlus.raa[ix] = (TH1D*)sysJEStotPlus.raa[ix]->Clone(Form("sys_finalPlus_raa_ix%d",ix));
    sysFinalMinus.pp[ix] = (TH1D*)sysJEStotMinus.pp[ix]->Clone(Form("sys_finalMinus_pp_ix%d",ix));
    sysFinalMinus.pbpb[ix] = (TH1D*)sysJEStotMinus.pbpb[ix]->Clone(Form("sys_finalMinus_pbpb_ix%d",ix));
    sysFinalMinus.raa[ix] = (TH1D*)sysJEStotMinus.raa[ix]->Clone(Form("sys_finalMinus_raa_ix%d",ix));
  }


  // Merge JES 
  resetJetSys( sysJEStotPlus, lowPtBin, highPtBin) ;
  resetJetSys( sysJEStotMinus, lowPtBin, highPtBin) ;
  for ( int ind =0 ; ind <  vIndPlus.size() ; ind++) {
    addSysInQuad3(sysJEStotPlus, sysPlus[ind], lowPtBin, highPtBin);
    addSysInQuad3(sysJEStotMinus, sysMinus[ind], lowPtBin, highPtBin);
  }
  
  
  // Merge everything! 
  bool addJES = 1 ; 
  bool addUnf = 1 ;
  bool addJER = 1 ; 
  bool addJMR = 1 ; 
  bool addJMS = 1 ; 

  resetJetSys( sysFinalPlus, lowPtBin, highPtBin) ;
  resetJetSys( sysFinalMinus, lowPtBin, highPtBin) ;

  if ( addJES ) { 
    addSysInQuad3(sysFinalPlus, sysJEStotPlus, lowPtBin, highPtBin) ;
    addSysInQuad3(sysFinalMinus, sysJEStotMinus, lowPtBin, highPtBin) ;
  }
  if ( addUnf) { 
    addSysInQuad3(sysFinalPlus, sysUnfPlus, lowPtBin, highPtBin) ;
    addSysInQuad3(sysFinalMinus, sysUnfMinus, lowPtBin, highPtBin) ;
  }
  if ( addJER ) { 
    addSysInQuad3(sysFinalPlus, sysJer, lowPtBin, highPtBin) ;
    addSysInQuad3(sysFinalMinus, sysJer, lowPtBin, highPtBin) ;
  }
  if ( addJMR ) { 
    addSysInQuad3(sysFinalPlus, sysJmr, lowPtBin, highPtBin) ;
    addSysInQuad3(sysFinalMinus, sysJmr, lowPtBin, highPtBin) ;
  }
  if ( addJMS ) { 
    addSysInQuad3(sysFinalPlus, sysJms, lowPtBin, highPtBin) ;
    addSysInQuad3(sysFinalMinus, sysJms, lowPtBin, highPtBin) ;
  }
  
  int jumSunStyle = 7;
  for ( int ix = lowPtBin ; ix<= highPtBin ; ix++)  {    
    handsomeTH1( sysJms.pp[ix], kOrange+2);
    handsomeTH1( sysJms.pbpb[ix], kOrange+2);
    handsomeTH1( sysJms.raa[ix], kOrange+2);
    handsomeTH1( sysJmsInv.pp[ix], kOrange+2);
    handsomeTH1( sysJmsInv.pbpb[ix], kOrange+2);
    handsomeTH1( sysJmsInv.raa[ix], kOrange+2);
    sysJms.pp[ix]->SetLineStyle(jumSunStyle);
    sysJms.pbpb[ix]->SetLineStyle(jumSunStyle);
    sysJms.raa[ix]->SetLineStyle(jumSunStyle);
    sysJmsInv.pp[ix]->SetLineStyle(jumSunStyle);
    sysJmsInv.pbpb[ix]->SetLineStyle(jumSunStyle);
    sysJmsInv.raa[ix]->SetLineStyle(jumSunStyle);


    handsomeTH1( sysJmr.pp[ix], kRed);
    handsomeTH1( sysJmr.pbpb[ix], kRed);
    handsomeTH1( sysJmr.raa[ix], kRed);
    handsomeTH1( sysJmrInv.pp[ix], kRed);
    handsomeTH1( sysJmrInv.pbpb[ix], kRed);
    handsomeTH1( sysJmrInv.raa[ix], kRed);
    sysJmr.pp[ix]->SetLineStyle(jumSunStyle);
    sysJmr.pbpb[ix]->SetLineStyle(jumSunStyle);
    sysJmr.raa[ix]->SetLineStyle(jumSunStyle);
    sysJmrInv.pp[ix]->SetLineStyle(jumSunStyle);
    sysJmrInv.pbpb[ix]->SetLineStyle(jumSunStyle);
    sysJmrInv.raa[ix]->SetLineStyle(jumSunStyle);

    handsomeTH1( sysJer.pp[ix], kBlue);
    handsomeTH1( sysJer.pbpb[ix], kBlue);
    handsomeTH1( sysJer.raa[ix], kBlue);
    handsomeTH1( sysJerInv.pp[ix], kBlue);
    handsomeTH1( sysJerInv.pbpb[ix], kBlue);
    handsomeTH1( sysJerInv.raa[ix], kBlue);
  }
  
  TCanvas* cPlus = new TCanvas("cPlus","",1200,800);
  makeMultiPanelCanvas(cPlus,nPtPannels+1,3, 0.0, 0.01, 0.3, 0.2, 0.05);
  TLegend *legPlus = new TLegend(0,0.1,0.95,0.95,NULL, "brNDC");
  easyLeg(legPlus,"Uncertainties", 0.07);

  for ( int ix = lowPtBin ; ix<= highPtBin ; ix++)  {
    cPlus->cd(ix - lowPtBin + 1);
    for ( int ind =0 ; ind <  vIndPlus.size() ; ind++) {
      if ( vIndPlus[ind] < 100 )   handsomeTH1(sysPlus[ind].pp[ix],30 + ind);  // pp 
      else                         handsomeTH1(sysPlus[ind].pp[ix], kRed + ind-10);  // pbpb
      groomHist(sysPlus[ind].pp[ix]);
      jumSun(0,0,0.24,0);
      sysPlus[ind].pp[ix]->SetAxisRange(-0.15,0.15,"Y");
      if ( ind == 0 )   sysPlus[ind].pp[ix]->Draw("hist");
      else       sysPlus[ind].pp[ix]->Draw("same hist");
 
      if ( ix==lowPtBin) legPlus->AddEntry(sysPlus[ind].pp[ix], getSysName( vIndPlus[ind] ).Data(),"l" );
    } 
    if ( ix==lowPtBin)  ATLASLabel(0.37,0.87,"Preliminary",0.07,0.25);
    if ( ix==lowPtBin)  drawCentrality(kPP, 0, 0.37,0.8,1,20);
    if ( ix==lowPtBin)  drawText("Plus variation", 0.37,0.7,1,20);
    drawBin(xBin,ix,"GeV",0.3,0.1,1,18);
    
    cPlus->cd(ix - lowPtBin + 1 + nPtPannels );
    for ( int ind =0 ; ind <  vIndPlus.size() ; ind++) {
      if ( vIndPlus[ind] < 100 )   handsomeTH1(sysPlus[ind].pbpb[ix],30 + ind);  // pp 
      else                         handsomeTH1(sysPlus[ind].pbpb[ix], kRed + ind-10);  // pbpb
      groomHist(sysPlus[ind].pbpb[ix]);
      sysPlus[ind].pbpb[ix]->SetYTitle("");
      jumSun(0,0,0.24,0);
      sysPlus[ind].pbpb[ix]->SetAxisRange(-0.15,0.15,"Y");
      if ( ind == 0 )   sysPlus[ind].pbpb[ix]->Draw("hist");
      else       sysPlus[ind].pbpb[ix]->Draw("same hist");
    }
    if ( ix==lowPtBin)  drawCentrality(kPbPb, icent, 0.37,0.83,1,20);
    
    cPlus->cd(ix - lowPtBin + 1 + 2*nPtPannels);
    for ( int ind =0 ; ind <  vIndPlus.size() ; ind++) {
      if ( vIndPlus[ind] < 100 )   handsomeTH1(sysPlus[ind].raa[ix],30 + ind);  // pp
      else                         handsomeTH1(sysPlus[ind].raa[ix], kRed + ind-10);  // pbpb
      groomHist(sysPlus[ind].raa[ix]);
      sysPlus[ind].raa[ix]->SetYTitle("");
      jumSun(0,0,0.24,0);
      sysPlus[ind].raa[ix]->SetAxisRange(-0.15,0.15,"Y");
      if ( ind == 0 )   sysPlus[ind].raa[ix]->Draw("hist");
      else       sysPlus[ind].raa[ix]->Draw("same hist");
    }
    if ( ix==lowPtBin)  drawText("R_{AA}", 0.37,0.83,1,20);
    
  }
  cPlus->SaveAs(Form("pdfsSystematics/cPlus_icent%d.pdf",icent));

  TCanvas* cLeg = new TCanvas("clegend","",300,300);
  legPlus->Draw();
  cLeg->SaveAs(Form("pdfsSystematics/cLeg.pdf"));
  
  
  TCanvas* cMinus = new TCanvas("cMinus","",1200,800);
  makeMultiPanelCanvas(cMinus,nPtPannels,3, 0.0, 0.01, 0.3, 0.2, 0.05);

  for ( int ix = lowPtBin ; ix<= highPtBin ; ix++)  {
    cMinus->cd(ix - lowPtBin + 1);
    for ( int ind =0 ; ind <  vIndMinus.size() ; ind++) {
      if ( vIndPlus[ind] < 100 )   handsomeTH1(sysMinus[ind].pp[ix],30 + ind);  // pp
      else                         handsomeTH1(sysMinus[ind].pp[ix], kRed + ind-10);  // pbpb
      groomHist(sysMinus[ind].pp[ix]);
      jumSun(0,0,0.24,0);
      sysMinus[ind].pp[ix]->SetAxisRange(-0.15,0.15,"Y");
      if ( ind == 0 )   sysMinus[ind].pp[ix]->Draw("hist");
      else       sysMinus[ind].pp[ix]->Draw("same hist");
    } 
    if ( ix==lowPtBin)  ATLASLabel(0.37,0.87,"Preliminary",0.07,0.25);
    if ( ix==lowPtBin)  drawCentrality(kPP, 0, 0.37,0.8,1,20);
    if ( ix==lowPtBin)  drawText("Minus variation", 0.37,0.7,1,20);
    drawBin(xBin,ix,"GeV",0.3,0.1,1,18);
    
    cMinus->cd(ix - lowPtBin + 1 + nPtPannels);
    for ( int ind =0 ; ind <  vIndMinus.size() ; ind++) {
      if ( vIndPlus[ind] < 100 )   handsomeTH1(sysMinus[ind].pbpb[ix],30 + ind);  // pp
      else                         handsomeTH1(sysMinus[ind].pbpb[ix], kRed + ind-10);  // pbpb
      groomHist(sysMinus[ind].pbpb[ix]); 
      jumSun(0,0,0.24,0);
      sysMinus[ind].pbpb[ix]->SetAxisRange(-0.15,0.15,"Y");
      if ( ind == 0 )   sysMinus[ind].pbpb[ix]->Draw("hist");
      else       sysMinus[ind].pbpb[ix]->Draw("same hist");
    }
    if ( ix==lowPtBin)  drawCentrality(kPbPb, icent, 0.37,0.83,1,20);

    cMinus->cd(ix - lowPtBin + 1 + 2*nPtPannels);
    for ( int ind =0 ; ind <  vIndMinus.size() ; ind++) {
      if ( vIndPlus[ind] < 100 )   handsomeTH1(sysMinus[ind].raa[ix],30 + ind);  // pp
      else                         handsomeTH1(sysMinus[ind].raa[ix], kRed + ind-10);  // pbpb
      groomHist(sysMinus[ind].raa[ix]);
      jumSun(0,0,0.24,0);
      sysMinus[ind].raa[ix]->SetAxisRange(-0.15,0.15,"Y");
      if ( ind == 0 )   sysMinus[ind].raa[ix]->Draw("hist");
      else       sysMinus[ind].raa[ix]->Draw("same hist");
    }
    if ( ix==lowPtBin)  drawText("#DeltaR_{AA}", 0.37,0.83,1,20);
  }
  cMinus->SaveAs(Form("pdfsSystematics/cMinus_icent%d.pdf",icent));

  TCanvas* cJer = new TCanvas("cJer","",1200,800);
  makeMultiPanelCanvas(cJer,nPtPannels,3, 0.0, 0.01, 0.3, 0.2, 0.05);

  for ( int ix = lowPtBin ; ix<= highPtBin ; ix++)  {
    cJer->cd(ix - lowPtBin + 1);
    groomHist(sysJer.pp[ix]);
    sysJer.pp[ix]->Draw("hist");
    jumSun(0,0,0.24,0);
    
    if ( ix==lowPtBin)  ATLASLabel(0.37,0.87,"Preliminary",0.075,0.25);
    if ( ix==lowPtBin)  drawCentrality(kPP, 0, 0.37,0.8,1,20);
    if ( ix==lowPtBin)  drawText("JER variation", 0.37,0.7,1,20);
    drawBin(xBin,ix,"GeV",0.3,0.1,1,18);
    
    cJer->cd(ix - lowPtBin + 1 + nPtPannels);
    groomHist(sysJer.pbpb[ix]); 
    sysJer.pbpb[ix]->Draw("hist");
    jumSun(0,0,0.24,0);

    if ( ix==lowPtBin)  drawCentrality(kPbPb, icent, 0.37,0.83,1,20);

    cJer->cd(ix - lowPtBin + 1 + 2*nPtPannels);
    groomHist(sysJer.raa[ix]);
    sysJer.raa[ix]->Draw("hist");
    if ( ix==lowPtBin)  drawText("#DeltaR_{AA}", 0.37,0.83,1,20);
    jumSun(0,0,0.24,0);
    
  }
  cJer->SaveAs(Form("pdfsSystematics/cJER_icent%d.pdf",icent));


  TCanvas* cJesTot = new TCanvas("cJesTot","",1200,800);
  makeMultiPanelCanvas(cJesTot,nPtPannels,3, 0.0, 0.01, 0.3, 0.2, 0.05);

  for ( int ix = lowPtBin ; ix<= highPtBin ; ix++)  {
    cJesTot->cd(ix - lowPtBin + 1);

    sysJEStotMinus.pp[ix]->Scale(-1);
    sysJEStotMinus.pbpb[ix]->Scale(-1);
    sysJEStotMinus.raa[ix]->Scale(-1);

    handsomeTH1(sysJEStotPlus.pp[ix],kGreen+1);
    handsomeTH1(sysJEStotMinus.pp[ix],kGreen+1);
    handsomeTH1(sysJEStotPlus.pbpb[ix],kGreen+1);
    handsomeTH1(sysJEStotMinus.pbpb[ix],kGreen+1);
    handsomeTH1(sysJEStotPlus.raa[ix],kGreen+1);
    handsomeTH1(sysJEStotMinus.raa[ix],kGreen+1);
    //    sysJEStotPlus.pp[ix]->SetFillColor(kAzure);
    //    sysJEStotMinus.pp[ix]->SetFillColor(kAzure);
    //    sysJEStotPlus.pbpb[ix]->SetFillColor(kAzure);
    //    sysJEStotMinus.pbpb[ix]->SetFillColor(kAzure);
    //    sysJEStotPlus.raa[ix]->SetFillColor(kAzure);
    //    sysJEStotMinus.raa[ix]->SetFillColor(kAzure);

    groomHist(sysJEStotPlus.pp[ix]);
    groomHist(sysJEStotMinus.pp[ix]);
    sysJEStotPlus.pp[ix]->Draw("hist");
    sysJEStotMinus.pp[ix]->Draw("hist same");
    jumSun(0,0,0.24,0);
    
    if ( ix==lowPtBin)  ATLASLabel(0.37,0.87,"Preliminary",0.075,0.25);
    if ( ix==lowPtBin)  drawCentrality(kPP, 0, 0.37,0.8,1,20);
    if ( ix==lowPtBin)  drawText("JES variation", 0.37,0.7,1,20);
    drawBin(xBin,ix,"GeV",0.3,0.1,1,18);
    
    cJesTot->cd(ix - lowPtBin + 1 + nPtPannels);
    groomHist(sysJEStotPlus.pbpb[ix]);
    groomHist(sysJEStotMinus.pbpb[ix]);
    sysJEStotPlus.pbpb[ix]->Draw("hist");
    sysJEStotMinus.pbpb[ix]->Draw("hist same");
    jumSun(0,0,0.24,0);
 
    if ( ix==lowPtBin)  drawCentrality(kPbPb, icent, 0.37,0.83,1,20);

    cJesTot->cd(ix - lowPtBin + 1 + 2*nPtPannels);
    groomHist(sysJEStotPlus.raa[ix]);
    groomHist(sysJEStotMinus.raa[ix]);
    sysJEStotPlus.raa[ix]->Draw("hist");
    sysJEStotMinus.raa[ix]->Draw("hist same");
    jumSun(0,0,0.24,0);
    if ( ix==lowPtBin)  drawText("#DeltaR_{AA}", 0.37,0.83,1,20);
    
  }
  cJesTot->SaveAs(Form("pdfsSystematics/cTotJES_icent%d.pdf",icent));



  TCanvas* cUnf = new TCanvas("cUnf","",1200,800);
  makeMultiPanelCanvas(cUnf,nPtPannels,3, 0.0, 0.01, 0.3, 0.2, 0.05);

  for ( int ix = lowPtBin ; ix<= highPtBin ; ix++)  {
    cUnf->cd(ix - lowPtBin + 1);
    //    sysUnfMinus.pp[ix]->Scale(-1);
    //    sysUnfMinus.pbpb[ix]->Scale(-1);
    sysUnfMinus.raa[ix]->Scale(-1);

    handsomeTH1(sysUnfPlus.pp[ix],kMagenta+1);
    handsomeTH1(sysUnfMinus.pp[ix],kMagenta+1);
    handsomeTH1(sysUnfPlus.pbpb[ix],kMagenta+1);
    handsomeTH1(sysUnfMinus.pbpb[ix],kMagenta+1);
    handsomeTH1(sysUnfPlus.raa[ix],kMagenta+1);
    handsomeTH1(sysUnfMinus.raa[ix],kMagenta+1);

    groomHist(sysUnfPlus.pp[ix]);
    groomHist(sysUnfMinus.pp[ix]);
    sysUnfPlus.pp[ix]->Draw("hist");
    sysUnfMinus.pp[ix]->Draw("hist same");
    jumSun(0,0,0.24,0);
    
    if ( ix==lowPtBin)  ATLASLabel(0.37,0.87,"Preliminary",0.075,0.25);
    if ( ix==lowPtBin)  drawCentrality(kPP, 0, 0.37,0.8,1,20);
    if ( ix==lowPtBin)  drawText("Unfolding Uncertainty", 0.37,0.7,1,20);

    drawBin(xBin,ix,"GeV",0.3,0.1,1,18);
    
    cUnf->cd(ix - lowPtBin + 1 + nPtPannels);
    groomHist(sysUnfPlus.pbpb[ix]);
    groomHist(sysUnfMinus.pbpb[ix]);
    sysUnfPlus.pbpb[ix]->Draw("hist");
    sysUnfMinus.pbpb[ix]->Draw("hist same");
    jumSun(0,0,0.24,0);
 
    if ( ix==lowPtBin)  drawCentrality(kPbPb, icent, 0.37,0.83,1,20);

    cUnf->cd(ix - lowPtBin + 1 + 2*nPtPannels);
    groomHist(sysUnfPlus.raa[ix]);
    groomHist(sysUnfMinus.raa[ix]);
    sysUnfPlus.raa[ix]->Draw("hist");
    sysUnfMinus.raa[ix]->Draw("hist same");
    jumSun(0,0,0.24,0);
    if ( ix==lowPtBin)  drawText("#DeltaR_{AA}", 0.37,0.83,1,20);
    
  }
  cUnf->SaveAs(Form("pdfsSystematics/cUnf_icent%d.pdf",icent));



  TCanvas* cFinal;
  if (drawPP){ 
    cFinal = new TCanvas("cFinal","",1200,900);
    makeMultiPanelCanvas(cFinal,nPtPannels,3, 0.0, 0.01, 0.3, 0.23, 0.05);
  }  else {
    cFinal = new TCanvas("cFinal","",1200,645);
    makeMultiPanelCanvas(cFinal,nPtPannels,2, 0.0, 0.01, 0.3, 0.23, 0.05);
  }

  for ( int ix = lowPtBin ; ix<= highPtBin ; ix++)  {
    
    sysFinalMinus.pp[ix]->Scale(-1);
    sysFinalMinus.pbpb[ix]->Scale(-1);
    sysFinalMinus.raa[ix]->Scale(-1);

    handsomeTH1(sysFinalPlus.pp[ix],1);
    handsomeTH1(sysFinalMinus.pp[ix],1);
    handsomeTH1(sysFinalPlus.pbpb[ix],1);
    handsomeTH1(sysFinalMinus.pbpb[ix],1);
    handsomeTH1(sysFinalPlus.raa[ix],1);
    handsomeTH1(sysFinalMinus.raa[ix],1);
    /*    sysFinalPlus.pp[ix]->SetFillColor(kOrange);
    sysFinalMinus.pp[ix]->SetFillColor(kOrange);
    sysFinalPlus.pbpb[ix]->SetFillColor(kOrange);
    sysFinalMinus.pbpb[ix]->SetFillColor(kOrange);
    sysFinalPlus.raa[ix]->SetFillColor(kOrange);
    sysFinalMinus.raa[ix]->SetFillColor(kOrange);  */


    groomHist(sysFinalPlus.pbpb[ix]);
    groomHist(sysFinalMinus.pbpb[ix]);
    groomHist(sysJEStotPlus.pbpb[ix]);
    groomHist(sysJEStotMinus.pbpb[ix]);
    groomHist(sysUnfPlus.pbpb[ix]);
    groomHist(sysUnfMinus.pbpb[ix]);
    groomHist(sysJer.pbpb[ix]);
    groomHist(sysJerInv.pbpb[ix]);
    groomHist(sysJmr.pbpb[ix]);
    groomHist(sysJmrInv.pbpb[ix]);
    groomHist(sysJms.pbpb[ix]);
    groomHist(sysJmsInv.pbpb[ix]);


    groomHist(sysFinalPlus.raa[ix]);
    groomHist(sysFinalMinus.raa[ix]);
    groomHist(sysJEStotPlus.raa[ix]);
    groomHist(sysJEStotMinus.raa[ix]);
    groomHist(sysUnfPlus.raa[ix]);
    groomHist(sysUnfMinus.raa[ix]);
    groomHist(sysJer.raa[ix]);
    groomHist(sysJerInv.raa[ix]);
    groomHist(sysJmr.raa[ix]);
    groomHist(sysJmrInv.raa[ix]);
    groomHist(sysJms.raa[ix]);
    groomHist(sysJmsInv.raa[ix]);

    if ( drawPP )  {
      
      cFinal->cd(ix - lowPtBin + 1)->SetTopMargin(0.02);
      groomHist(sysFinalPlus.pp[ix]);
      groomHist(sysFinalMinus.pp[ix]);
      groomHist(sysJEStotPlus.pp[ix]);
      groomHist(sysJEStotMinus.pp[ix]);
      groomHist(sysUnfPlus.pp[ix]);
      groomHist(sysUnfMinus.pp[ix]);
      groomHist(sysJer.pp[ix]);
      groomHist(sysJerInv.pp[ix]);
      groomHist(sysJmr.pp[ix]);
      groomHist(sysJmrInv.pp[ix]);
      groomHist(sysJms.pp[ix]);
      groomHist(sysJmsInv.pp[ix]);

      groomHist(sysFinalPlus.pbpb[ix]);
      groomHist(sysFinalMinus.pbpb[ix]);
      groomHist(sysJEStotPlus.pbpb[ix]);
      groomHist(sysJEStotMinus.pbpb[ix]);
      groomHist(sysUnfPlus.pbpb[ix]);
      groomHist(sysUnfMinus.pbpb[ix]);
      groomHist(sysJer.pbpb[ix]);
      groomHist(sysJerInv.pbpb[ix]);
      groomHist(sysJmr.pbpb[ix]);
      groomHist(sysJmrInv.pbpb[ix]);
      groomHist(sysJms.pbpb[ix]);
      groomHist(sysJmsInv.pbpb[ix]);
  
      groomHist(sysFinalPlus.raa[ix]);
      groomHist(sysFinalMinus.raa[ix]);
      groomHist(sysJEStotPlus.raa[ix]);
      groomHist(sysJEStotMinus.raa[ix]);
      groomHist(sysUnfPlus.raa[ix]);
      groomHist(sysUnfMinus.raa[ix]);
      groomHist(sysJer.raa[ix]);
      groomHist(sysJerInv.raa[ix]);
      groomHist(sysJmr.raa[ix]);
      groomHist(sysJmrInv.raa[ix]);
      groomHist(sysJms.raa[ix]);
      groomHist(sysJmsInv.raa[ix]);

      
      sysFinalPlus.pp[ix]->Draw("hist");
      sysFinalMinus.pp[ix]->Draw("hist same");
      
      if ( addJES )   { 
	sysJEStotPlus.pp[ix]->Draw("same");
	sysJEStotMinus.pp[ix]->Draw("same");
      }
      if ( addUnf) {
	sysUnfPlus.pp[ix]->Draw("same hist");
	sysUnfMinus.pp[ix]->Draw("same hist");
      }
      if ( addJER) {
	sysJer.pp[ix]->Draw("same hist");
	sysJerInv.pp[ix]->Draw("same hist");
      }
      if ( addJMR) {
	sysJmr.pp[ix]->Draw("same hist");
	sysJmrInv.pp[ix]->Draw("same hist");
      }
      if ( addJMS) {
	sysJms.pp[ix]->Draw("same hist");
	sysJmsInv.pp[ix]->Draw("same hist");
      }
      if ( ix==highPtBin) {
	cout << " final = " <<  sysFinalPlus.pp[ix]->GetBinContent(2) << endl;
	cout << "sysJms.pp[ix] = " << sysJms.pp[ix]->GetBinContent(2) << endl;
	cout << "sysJms.pp[ix] = " << sysJms.pp[ix]->GetBinContent(2) << endl;
	cout <<" sysJer.pp[ix] = " << sysJer.pp[ix]->GetBinContent(2) << endl;
	cout <<" sysJmr.pp[ix] = " << sysJmr.pp[ix]->GetBinContent(2) << endl;
	cout <<" sysUnfPlus.pp[ix] = " << sysUnfPlus.pp[ix]->GetBinContent(2) << endl;
      }

      jumSun(0,0,0.24,0);
    
      if ( ix==lowPtBin) {
	ATLASLabel(0.32,0.86,"Preliminary",0.077,0.27);
	drawCentrality(kPP, 0, 0.37,0.8,1,20);
      }
      drawBinPt(xBin,ix,"GeV",0.12 + (ix==lowPtBin)*0.2,0.1,1,18);
      gPad->RedrawAxis();
      
    }
    
    if (drawPP) 
      cFinal->cd(ix - lowPtBin + 1 + nPtPannels);
    else 
      cFinal->cd(ix - lowPtBin + 1 )->SetTopMargin(0.02);

    groomHist(sysFinalPlus.pbpb[ix]);
    groomHist(sysFinalMinus.pbpb[ix]);
    //    if (drawPP) sysFinalPlus.pbpb[ix]->SetYTitle("");
    sysFinalPlus.pbpb[ix]->Draw("hist");
    sysFinalMinus.pbpb[ix]->Draw("hist same");
    jumSun(0,0,0.24,0);
    
    if ( addJES )   { 
      sysJEStotPlus.pbpb[ix]->Draw("same");
      sysJEStotMinus.pbpb[ix]->Draw("same");
    }
    if ( addUnf) {
      sysUnfPlus.pbpb[ix]->Draw("same hist");
      sysUnfMinus.pbpb[ix]->Draw("same hist");
    }
    if ( addJER) {
      sysJer.pbpb[ix]->Draw("same hist");
      sysJerInv.pbpb[ix]->Draw("same hist");
    }
    if ( addJMR) {
      sysJmr.pbpb[ix]->Draw("same hist");
      sysJmrInv.pbpb[ix]->Draw("same hist");
    }
    if ( addJMS) {
      sysJms.pbpb[ix]->Draw("same hist");
      sysJmsInv.pbpb[ix]->Draw("same hist");
    }

    if ( !drawPP) { 
      drawBinPt(xBin,ix,"GeV",0.12 + (ix==lowPtBin)*0.23,0.1,1,18);
      gPad->RedrawAxis();
    }
    
    
    if ( ix==lowPtBin) {
      if ( drawPP) drawCentrality(kPbPb, icent, 0.37,0.83,1,20);
      else  { 
	drawCentrality(kPbPb, icent, 0.37,0.78,1,20);
        ATLASLabel(0.32,0.86,"Preliminary",0.077,0.27);
      }
    }
gPad->RedrawAxis();



    if ( drawPP)  cFinal->cd(ix - lowPtBin + 1 + 2*nPtPannels);
    else  cFinal->cd(ix - lowPtBin + 1 + nPtPannels);
    
    groomHist(sysFinalPlus.raa[ix]);
    groomHist(sysFinalMinus.raa[ix]);
    
    if (!drawPP)          sysFinalPlus.raa[ix]->GetXaxis()->SetTitleOffset(1.9);
    else          sysFinalPlus.raa[ix]->GetXaxis()->SetTitleOffset(2.7);
    
    if ( drawPP) {
      sysFinalPlus.raa[ix]->GetYaxis()->SetTitleOffset(4.5);
      sysFinalPlus.pp[ix]->GetYaxis()->SetTitleOffset(4.5);
      sysFinalPlus.pbpb[ix]->GetYaxis()->SetTitleOffset(4.5);
    }
    else {
      sysFinalPlus.raa[ix]->GetYaxis()->SetTitleOffset(3);
      sysFinalPlus.pp[ix]->GetYaxis()->SetTitleOffset(3);
      sysFinalPlus.pbpb[ix]->GetYaxis()->SetTitleOffset(3);

    }
    cout << sysFinalPlus.raa[ix]->GetYaxis()->GetTitleOffset() << endl;

    //    sysFinalPlus.raa[ix]->SetYTitle("");
    sysFinalPlus.raa[ix]->Draw("hist");
    sysFinalMinus.raa[ix]->Draw("hist same");

    if ( addJES )   { 
      sysJEStotPlus.raa[ix]->Draw("same");
      sysJEStotMinus.raa[ix]->Draw("same");
    }
    if ( addUnf) {
      sysUnfPlus.raa[ix]->Draw("same hist");
      sysUnfMinus.raa[ix]->Draw("same hist");
    }
    if ( addJER) {
      sysJer.raa[ix]->Draw("same hist");
      sysJerInv.raa[ix]->Draw("same hist");
    }
    if ( addJMR) {
      sysJmr.raa[ix]->Draw("same hist");
      sysJmrInv.raa[ix]->Draw("same hist");
    }
    if ( addJMS) {
      sysJms.raa[ix]->Draw("same hist");
      sysJmsInv.raa[ix]->Draw("same hist");
    }


    jumSun(0,0,0.24,0);
    if ( ix==lowPtBin)  drawText("R_{AA}", 0.37,0.9,1,20);
    gPad->RedrawAxis();

    if ( ix > lowPtBin)  drawPatch(0,0, 0.05,0.22);
    
  }
  if ( drawPP)   cFinal->SaveAs(Form("pdfsSystematics/cFinal_icent%d.pdf",icent));
  else           cFinal->SaveAs(Form("pdfsSystematics/cFinal_icent%d_noPP.pdf",icent));


  TCanvas* cLeg2 = new TCanvas("cleg2","",200,600);
  TLegend* leg1 = new TLegend(0,0.7058065,1,0.95,NULL,"brNDC");
  easyLeg(leg1,"Uncertainties",0.1);
  leg1->AddEntry(sysFinalPlus.pp[lowPtBin],"Total","l");
  if (addUnf) leg1->AddEntry(sysUnfPlus.pp[lowPtBin],"Unfolding","l");
  if (addJES) leg1->AddEntry(sysJEStotPlus.pp[lowPtBin],"JES","l");
  if (addJER) leg1->AddEntry(sysJer.pp[lowPtBin],"JER","l");
  if (addJMS) leg1->AddEntry(sysJms.pp[lowPtBin],"JMS","l");
  if (addJMR) leg1->AddEntry(sysJmr.pp[lowPtBin],"JMR","l");
  leg1->Draw();
  cLeg2->SaveAs("pdfsSystematics/cFinal_legend.pdf");

  TCanvas* cLeg3 = new TCanvas("cleg3","",200,645);
  TLegend* leg2 = new TLegend(0,0.650065,1,1.0,NULL,"brNDC");
  easyLeg(leg2,"Uncertainties",0.1);
  leg2->AddEntry(sysFinalPlus.pp[lowPtBin],"Total","l");
  if (addUnf) leg2->AddEntry(sysUnfPlus.pp[lowPtBin],"Unfolding","l");
  if (addJES) leg2->AddEntry(sysJEStotPlus.pp[lowPtBin],"JES","l");
  if (addJER) leg2->AddEntry(sysJer.pp[lowPtBin],"JER","l");
  if (addJMS) leg2->AddEntry(sysJms.pp[lowPtBin],"JMS","l");
  if (addJMR) leg2->AddEntry(sysJmr.pp[lowPtBin],"JMR","l");
  leg2->Draw();
  cLeg3->SaveAs("pdfsSystematics/cFinal_legend_2.pdf");

  TCanvas* cLeg4 = new TCanvas("cleg4","",200,430);
  TLegend* leg3 = new TLegend(0,0.70065,1,0.96,NULL,"brNDC");
  easyLeg(leg3,"Uncertainties",0.1);
  leg3->AddEntry(sysFinalPlus.pp[lowPtBin],"Total","l");
  if (addUnf) leg3->AddEntry(sysUnfPlus.pp[lowPtBin],"Unfolding","l");
  if (addJES) leg3->AddEntry(sysJEStotPlus.pp[lowPtBin],"JES","l");
  if (addJER) leg3->AddEntry(sysJer.pp[lowPtBin],"JER","l");
  if (addJMS) leg3->AddEntry(sysJms.pp[lowPtBin],"JMS","l");
  if (addJMR) leg3->AddEntry(sysJmr.pp[lowPtBin],"JMR","l");
  leg3->Draw();
  cLeg4->SaveAs("pdfsSystematics/cFinal_legend_3.pdf");


  //Save
  TFile* fout = new TFile(Form("sysSpectra/systematics_icent%d_smoothened.root",icent), "recreate");

  for ( int ix = lowPtBin ; ix<= highPtBin ; ix++)  {
    sysFinalPlus.pp[ix]->Write();
    sysFinalPlus.pbpb[ix]->Write();
    sysFinalPlus.raa[ix]->Write();
    sysFinalMinus.pp[ix]->Write();
    sysFinalMinus.pbpb[ix]->Write();
    sysFinalMinus.raa[ix]->Write();
  }
  fout->Close();
  
}
