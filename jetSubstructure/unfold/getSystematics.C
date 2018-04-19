#include "../commonUtility.h"
#include "systematicsTool.h"

void groomHist(TH1D* h1) {
  h1->SetAxisRange(0.001,0.23,"X");
  h1->SetAxisRange(-0.35,0.35,"Y");
  h1->SetXTitle("m/p_{T}");
  h1->SetYTitle("Relative Uncertainty");
  h1->SetNdivisions(505,"X");
  h1->SetNdivisions(505,"Y");
  fixedFontHist(h1,3,3,20);

}

void getSystematics(int icent = 0) {
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
  int indexJMR = 200;
  int indexJMS = 210;
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
  JetSys sysJms;
  JetSys sysJmr;
  
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
  sysJer = getSystematicsJES(icent, indexJER );
  sysJms = getSystematicsJES(icent, indexJMS );
  sysJmr = getSystematicsJES(icent, indexJMR );
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
    sysJEStotPlus.pp[ix]->Reset();
    sysJEStotPlus.pbpb[ix]->Reset();
    sysJEStotPlus.raa[ix]->Reset();
    sysJEStotMinus.pp[ix]->Reset();
    sysJEStotMinus.pbpb[ix]->Reset();
    sysJEStotMinus.raa[ix]->Reset();
  }
  
  for ( int ix = lowPtBin ; ix<= highPtBin ; ix++)  {
    for ( int ind =0 ; ind <  vIndPlus.size() ; ind++) {
      addSysInQuad(sysJEStotPlus.pp[ix], sysPlus[ind].pp[ix]);
      addSysInQuad(sysJEStotPlus.pbpb[ix], sysPlus[ind].pbpb[ix]);
      addSysInQuad(sysJEStotPlus.raa[ix], sysPlus[ind].raa[ix]);
      addSysInQuad(sysJEStotMinus.pp[ix], sysMinus[ind].pp[ix]);
      addSysInQuad(sysJEStotMinus.pbpb[ix], sysMinus[ind].pbpb[ix]);
      addSysInQuad(sysJEStotMinus.raa[ix], sysMinus[ind].raa[ix]);
    }
    bool addJER = 1 ; 
    if ( addJER ) { 
      addSysInQuad(sysJEStotPlus.pp[ix], sysJer.pp[ix]);
      addSysInQuad(sysJEStotPlus.pbpb[ix], sysJer.pbpb[ix]);
      addSysInQuad(sysJEStotPlus.raa[ix], sysJer.raa[ix]);
      addSysInQuad(sysJEStotMinus.pp[ix], sysJer.pp[ix]);
      addSysInQuad(sysJEStotMinus.pbpb[ix], sysJer.pbpb[ix]);
      addSysInQuad(sysJEStotMinus.raa[ix], sysJer.raa[ix]);
    }
    bool addJMR = 1 ; 
    if ( addJMR ) { 
      addSysInQuad(sysJEStotPlus.pp[ix], sysJmr.pp[ix]);
      addSysInQuad(sysJEStotPlus.pbpb[ix], sysJmr.pbpb[ix]);
      addSysInQuad(sysJEStotPlus.raa[ix], sysJmr.raa[ix]);
      addSysInQuad(sysJEStotMinus.pp[ix], sysJmr.pp[ix]);
      addSysInQuad(sysJEStotMinus.pbpb[ix], sysJmr.pbpb[ix]);
      addSysInQuad(sysJEStotMinus.raa[ix], sysJmr.raa[ix]);
    }
    bool addJMS = 1 ; 
    if ( addJMS ) { 
      addSysInQuad(sysJEStotPlus.pp[ix], sysJms.pp[ix]);
      addSysInQuad(sysJEStotPlus.pbpb[ix], sysJms.pbpb[ix]);
      addSysInQuad(sysJEStotPlus.raa[ix], sysJms.raa[ix]);
      addSysInQuad(sysJEStotMinus.pp[ix], sysJms.pp[ix]);
      addSysInQuad(sysJEStotMinus.pbpb[ix], sysJms.pbpb[ix]);
      addSysInQuad(sysJEStotMinus.raa[ix], sysJms.raa[ix]);
    }


  }  

  // Merge Unf into JES
  for ( int ix = lowPtBin ; ix<= highPtBin ; ix++)  {
    sysFinalPlus.pp[ix] = (TH1D*)sysJEStotPlus.pp[ix]->Clone(Form("sys_finalPlus_pp_ix%d",ix));
    sysFinalPlus.pbpb[ix] = (TH1D*)sysJEStotPlus.pbpb[ix]->Clone(Form("sys_finalPlus_pbpb_ix%d",ix));
    sysFinalPlus.raa[ix] = (TH1D*)sysJEStotPlus.raa[ix]->Clone(Form("sys_finalPlus_raa_ix%d",ix));
    sysFinalMinus.pp[ix] = (TH1D*)sysJEStotMinus.pp[ix]->Clone(Form("sys_finalMinus_pp_ix%d",ix));
    sysFinalMinus.pbpb[ix] = (TH1D*)sysJEStotMinus.pbpb[ix]->Clone(Form("sys_finalMinus_pbpb_ix%d",ix));
    sysFinalMinus.raa[ix] = (TH1D*)sysJEStotMinus.raa[ix]->Clone(Form("sys_finalMinus_raa_ix%d",ix));
    addSysInQuad(sysFinalPlus.pp[ix], sysUnfPlus.pp[ix]);
    addSysInQuad(sysFinalPlus.pbpb[ix], sysUnfPlus.pbpb[ix]);
    addSysInQuad(sysFinalPlus.raa[ix], sysUnfPlus.raa[ix]);
    addSysInQuad(sysFinalMinus.pp[ix], sysUnfMinus.pp[ix]);
    addSysInQuad(sysFinalMinus.pbpb[ix], sysUnfMinus.pbpb[ix]);
    addSysInQuad(sysFinalMinus.raa[ix], sysUnfMinus.raa[ix]);
  }
  

  
  TCanvas* cPlus = new TCanvas("cPlus","",1200,800);
  makeMultiPanelCanvas(cPlus,nPtPannels,3, 0.0, 0.01, 0.3, 0.2, 0.05);
  TLegend *legPlus = new TLegend(0,0.1,0.95,0.95,NULL, "brNDC");
  easyLeg(legPlus,"Systematics", 0.07);

  for ( int ix = lowPtBin ; ix<= highPtBin ; ix++)  {
    cPlus->cd(ix - lowPtBin + 1);
    for ( int ind =0 ; ind <  vIndPlus.size() ; ind++) {
      if ( vIndPlus[ind] < 100 )   handsomeTH1(sysPlus[ind].pp[ix],30 + ind);  // pp 
      else                         handsomeTH1(sysPlus[ind].pp[ix], kRed + ind-10);  // pbpb
      groomHist(sysPlus[ind].pp[ix]);
      jumSun(0,0,0.24,0);
      if ( ind == 0 )   sysPlus[ind].pp[ix]->Draw("hist");
      else       sysPlus[ind].pp[ix]->Draw("same hist");
 
      if ( ix==lowPtBin) legPlus->AddEntry(sysPlus[ind].pp[ix], getSysName( vIndPlus[ind] ).Data(),"l" );
    } 
    if ( ix==lowPtBin)  drawCentrality(kPP, 0, 0.37,0.83,1,20);
    if ( ix==lowPtBin)  drawText("Plus variation", 0.37,0.73,1,20);
    drawBin(xBin,ix,"GeV",0.3,0.1,1,18);
    
    cPlus->cd(ix - lowPtBin + 1 + nPtPannels);
    for ( int ind =0 ; ind <  vIndPlus.size() ; ind++) {
      if ( vIndPlus[ind] < 100 )   handsomeTH1(sysPlus[ind].pbpb[ix],30 + ind);  // pp 
      else                         handsomeTH1(sysPlus[ind].pbpb[ix], kRed + ind-10);  // pbpb
      groomHist(sysPlus[ind].pbpb[ix]);
      jumSun(0,0,0.24,0);
      if ( ind == 0 )   sysPlus[ind].pbpb[ix]->Draw("hist");
      else       sysPlus[ind].pbpb[ix]->Draw("same hist");
    }
    if ( ix==lowPtBin)  drawCentrality(kPbPb, icent, 0.37,0.83,1,20);
    
    cPlus->cd(ix - lowPtBin + 1 + 2*nPtPannels);
    for ( int ind =0 ; ind <  vIndPlus.size() ; ind++) {
      if ( vIndPlus[ind] < 100 )   handsomeTH1(sysPlus[ind].raa[ix],30 + ind);  // pp
      else                         handsomeTH1(sysPlus[ind].raa[ix], kRed + ind-10);  // pbpb
      groomHist(sysPlus[ind].raa[ix]);
      jumSun(0,0,0.24,0);
      if ( ind == 0 )   sysPlus[ind].raa[ix]->Draw("hist");
      else       sysPlus[ind].raa[ix]->Draw("same hist");
    }
    if ( ix==lowPtBin)  drawText("#Delta(PbPb/pp)", 0.37,0.83,1,20);
    
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
      if ( ind == 0 )   sysMinus[ind].pp[ix]->Draw("hist");
      else       sysMinus[ind].pp[ix]->Draw("same hist");
    } 
    if ( ix==lowPtBin)  drawCentrality(kPP, 0, 0.37,0.83,1,20);
    if ( ix==lowPtBin)  drawText("Minus variation", 0.37,0.73,1,20);
    drawBin(xBin,ix,"GeV",0.3,0.1,1,18);
    
    cMinus->cd(ix - lowPtBin + 1 + nPtPannels);
    for ( int ind =0 ; ind <  vIndMinus.size() ; ind++) {
      if ( vIndPlus[ind] < 100 )   handsomeTH1(sysMinus[ind].pbpb[ix],30 + ind);  // pp
      else                         handsomeTH1(sysMinus[ind].pbpb[ix], kRed + ind-10);  // pbpb
      groomHist(sysMinus[ind].pbpb[ix]); 
      jumSun(0,0,0.24,0);
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
      if ( ind == 0 )   sysMinus[ind].raa[ix]->Draw("hist");
      else       sysMinus[ind].raa[ix]->Draw("same hist");
    }
    if ( ix==lowPtBin)  drawText("#Delta(PbPb/pp)", 0.37,0.83,1,20);
  }
  cMinus->SaveAs(Form("pdfsSystematics/cMinus_icent%d.pdf",icent));

  TCanvas* cJer = new TCanvas("cJer","",1200,800);
  makeMultiPanelCanvas(cJer,nPtPannels,3, 0.0, 0.01, 0.3, 0.2, 0.05);

  for ( int ix = lowPtBin ; ix<= highPtBin ; ix++)  {
    cJer->cd(ix - lowPtBin + 1);
    handsomeTH1(sysJer.pp[ix],49);
    groomHist(sysJer.pp[ix]);
    sysJer.pp[ix]->Draw("hist");
    jumSun(0,0,0.24,0);
    
    if ( ix==lowPtBin)  drawCentrality(kPP, 0, 0.37,0.83,1,20);
    if ( ix==lowPtBin)  drawText("JER variation", 0.37,0.73,1,20);
    drawBin(xBin,ix,"GeV",0.3,0.1,1,18);
    
    cJer->cd(ix - lowPtBin + 1 + nPtPannels);
    handsomeTH1(sysJer.pbpb[ix],49);
    groomHist(sysJer.pbpb[ix]); 
    sysJer.pbpb[ix]->Draw("hist");
    jumSun(0,0,0.24,0);

    if ( ix==lowPtBin)  drawCentrality(kPbPb, icent, 0.37,0.83,1,20);

    cJer->cd(ix - lowPtBin + 1 + 2*nPtPannels);
    handsomeTH1(sysJer.raa[ix],49);
    groomHist(sysJer.raa[ix]);
    sysJer.raa[ix]->Draw("hist");
    if ( ix==lowPtBin)  drawText("#Delta(PbPb/pp)", 0.37,0.83,1,20);
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

    handsomeTH1(sysJEStotPlus.pp[ix],kAzure+1);
    handsomeTH1(sysJEStotMinus.pp[ix],kAzure+1);
    handsomeTH1(sysJEStotPlus.pbpb[ix],kAzure+1);
    handsomeTH1(sysJEStotMinus.pbpb[ix],kAzure+1);
    handsomeTH1(sysJEStotPlus.raa[ix],kAzure+1);
    handsomeTH1(sysJEStotMinus.raa[ix],kAzure+1);
    sysJEStotPlus.pp[ix]->SetFillColor(kAzure);
    sysJEStotMinus.pp[ix]->SetFillColor(kAzure);
    sysJEStotPlus.pbpb[ix]->SetFillColor(kAzure);
    sysJEStotMinus.pbpb[ix]->SetFillColor(kAzure);
    sysJEStotPlus.raa[ix]->SetFillColor(kAzure);
    sysJEStotMinus.raa[ix]->SetFillColor(kAzure);

    groomHist(sysJEStotPlus.pp[ix]);
    groomHist(sysJEStotMinus.pp[ix]);
    sysJEStotPlus.pp[ix]->Draw("hist");
    sysJEStotMinus.pp[ix]->Draw("hist same");
    jumSun(0,0,0.24,0);
    
    if ( ix==lowPtBin)  drawCentrality(kPP, 0, 0.37,0.83,1,20);
    if ( ix==lowPtBin)  drawText("JES total", 0.37,0.73,1,20);
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
    if ( ix==lowPtBin)  drawText("#Delta(PbPb/pp)", 0.37,0.83,1,20);
    
  }
  cJesTot->SaveAs(Form("pdfsSystematics/cTotJES_icent%d.pdf",icent));



  TCanvas* cUnf = new TCanvas("cUnf","",1200,800);
  makeMultiPanelCanvas(cUnf,nPtPannels,3, 0.0, 0.01, 0.3, 0.2, 0.05);

  for ( int ix = lowPtBin ; ix<= highPtBin ; ix++)  {
    cUnf->cd(ix - lowPtBin + 1);
    //    sysUnfMinus.pp[ix]->Scale(-1);
    //    sysUnfMinus.pbpb[ix]->Scale(-1);
    sysUnfMinus.raa[ix]->Scale(-1);

    handsomeTH1(sysUnfPlus.pp[ix],kYellow+1);
    handsomeTH1(sysUnfMinus.pp[ix],kYellow+1);
    handsomeTH1(sysUnfPlus.pbpb[ix],kYellow+1);
    handsomeTH1(sysUnfMinus.pbpb[ix],kYellow+1);
    handsomeTH1(sysUnfPlus.raa[ix],kYellow+1);
    handsomeTH1(sysUnfMinus.raa[ix],kYellow+1);
    sysUnfPlus.pp[ix]->SetFillColor(kYellow);
    sysUnfMinus.pp[ix]->SetFillColor(kYellow);
    sysUnfPlus.pbpb[ix]->SetFillColor(kYellow);
    sysUnfMinus.pbpb[ix]->SetFillColor(kYellow);
    sysUnfPlus.raa[ix]->SetFillColor(kYellow);
    sysUnfMinus.raa[ix]->SetFillColor(kYellow);

    groomHist(sysUnfPlus.pp[ix]);
    groomHist(sysUnfMinus.pp[ix]);
    sysUnfPlus.pp[ix]->Draw("hist");
    sysUnfMinus.pp[ix]->Draw("hist same");
    jumSun(0,0,0.24,0);
    
    if ( ix==lowPtBin)  drawCentrality(kPP, 0, 0.37,0.83,1,20);
    if ( ix==lowPtBin)  drawText("Unfolding Unc.", 0.37,0.73,1,20);
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
    if ( ix==lowPtBin)  drawText("#Delta(PbPb/pp)", 0.37,0.83,1,20);
    
  }
  cUnf->SaveAs(Form("pdfsSystematics/cUnf_icent%d.pdf",icent));



  TCanvas* cFinal = new TCanvas("cFinal","",1200,800);
  makeMultiPanelCanvas(cFinal,nPtPannels,3, 0.0, 0.01, 0.3, 0.2, 0.05);

  for ( int ix = lowPtBin ; ix<= highPtBin ; ix++)  {
    cFinal->cd(ix - lowPtBin + 1);
    sysFinalMinus.pp[ix]->Scale(-1);
    sysFinalMinus.pbpb[ix]->Scale(-1);
    sysFinalMinus.raa[ix]->Scale(-1);

    handsomeTH1(sysFinalPlus.pp[ix],kGreen-7+1);
    handsomeTH1(sysFinalMinus.pp[ix],kGreen-7+1);
    handsomeTH1(sysFinalPlus.pbpb[ix],kGreen-7+1);
    handsomeTH1(sysFinalMinus.pbpb[ix],kGreen-7+1);
    handsomeTH1(sysFinalPlus.raa[ix],kGreen-7+1);
    handsomeTH1(sysFinalMinus.raa[ix],kGreen-7+1);
    sysFinalPlus.pp[ix]->SetFillColor(kGreen-7);
    sysFinalMinus.pp[ix]->SetFillColor(kGreen-7);
    sysFinalPlus.pbpb[ix]->SetFillColor(kGreen-7);
    sysFinalMinus.pbpb[ix]->SetFillColor(kGreen-7);
    sysFinalPlus.raa[ix]->SetFillColor(kGreen-7);
    sysFinalMinus.raa[ix]->SetFillColor(kGreen-7);

    groomHist(sysFinalPlus.pp[ix]);
    groomHist(sysFinalMinus.pp[ix]);
    sysFinalPlus.pp[ix]->Draw("hist");
    sysFinalMinus.pp[ix]->Draw("hist same");
    jumSun(0,0,0.24,0);
    
    if ( ix==lowPtBin)  drawCentrality(kPP, 0, 0.37,0.83,1,20);
    if ( ix==lowPtBin)  drawText("Unf+JES Unc.", 0.37,0.73,1,20);
    drawBin(xBin,ix,"GeV",0.3,0.1,1,18);
    gPad->RedrawAxis();

    cFinal->cd(ix - lowPtBin + 1 + nPtPannels);
    groomHist(sysFinalPlus.pbpb[ix]);
    groomHist(sysFinalMinus.pbpb[ix]);
    sysFinalPlus.pbpb[ix]->Draw("hist");
    sysFinalMinus.pbpb[ix]->Draw("hist same");
    jumSun(0,0,0.24,0);
 
    if ( ix==lowPtBin)  drawCentrality(kPbPb, icent, 0.37,0.83,1,20);
    gPad->RedrawAxis();

    cFinal->cd(ix - lowPtBin + 1 + 2*nPtPannels);
    groomHist(sysFinalPlus.raa[ix]);
    groomHist(sysFinalMinus.raa[ix]);
    sysFinalPlus.raa[ix]->Draw("hist");
    sysFinalMinus.raa[ix]->Draw("hist same");
    jumSun(0,0,0.24,0);
    if ( ix==lowPtBin)  drawText("#Delta(PbPb/pp)", 0.37,0.83,1,20);
    gPad->RedrawAxis();
    
  }
  cFinal->SaveAs(Form("pdfsSystematics/cFinal_icent%d.pdf",icent));
  
  //Save
  TFile* fout = new TFile(Form("sysSpectra/systematics_icent%d.root",icent), "recreate");

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
