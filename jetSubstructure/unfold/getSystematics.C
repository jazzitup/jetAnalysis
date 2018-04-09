#include "../commonUtility.h"
#include "systematicsTool.h"

void groomHist(TH1D* h1) {
  h1->SetAxisRange(0.001,0.23,"X");
  h1->SetAxisRange(-0.55,0.55,"Y");
  h1->SetXTitle("m/p_{T}");
  h1->SetYTitle("Uncertainty (Relative)");
  h1->SetNdivisions(505,"X");
  h1->SetNdivisions(505,"Y");
  fixedFontHist(h1,1.2,1.4,20);
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
  for ( int i=0 ; i<=21 ; i++)   {
    if (i%2 == 0)  vIndPlus.push_back(i);  // pp JES
    else           vIndMinus.push_back(i);  // pp JES
  }
  for ( int i=101 ; i<=106 ; i++){
    if (i%2 == 1)  vIndPlus.push_back(i);  // pp JES
    else           vIndMinus.push_back(i);  // pp JES
  }

  JetSys sysPlus[20];
  JetSys sysMinus[20];
  JetSys sysJer;
  for ( int is =0 ; is <  vIndPlus.size() ; is++) {
    sysPlus[is] = getSystematicsJES(icent, vIndPlus.at(is));
    sysMinus[is] = getSystematicsJES(icent, vIndMinus.at(is));
  }
  sysJer = getSystematicsJES(icent, indexJER );

  TCanvas* cPlus = new TCanvas("cPlus","",1200,800);
  makeMultiPanelCanvas(cPlus,nPtPannels,3, 0.0, 0.01, 0.3, 0.2, 0.05);
  TLegend *legPlus = new TLegend(-0.005286785,0.1525575,1,1.001334,NULL,"brNDC");
  easyLeg(legPlus,"Systematics", 0.07);

  for ( int ix = lowPtBin ; ix<= highPtBin ; ix++)  {
    cPlus->cd(ix - lowPtBin + 1);
    for ( int ind =0 ; ind <  vIndPlus.size() ; ind++) {
      handsomeTH1(sysPlus[ind].pp[ix],30 + ind);
      groomHist(sysPlus[ind].pp[ix]);
      jumSun(0,0,0.24,0);
      if ( ind == 0 )   sysPlus[ind].pp[ix]->Draw("hist");
      else       sysPlus[ind].pp[ix]->Draw("same hist");
 
      if ( ix==lowPtBin) legPlus->AddEntry(sysPlus[ind].pp[ix], getSysName( vIndPlus[ind] ).Data(),"l" );
      if ( ix==lowPtBin)  drawCentrality(kPP, 0, 0.37,0.83,1,20);
      if ( ix==lowPtBin)  drawText("Plus variation", 0.37,0.73,1,20);
    } 
    cPlus->cd(ix - lowPtBin + 1 + nPtPannels);
    for ( int ind =0 ; ind <  vIndPlus.size() ; ind++) {
      handsomeTH1(sysPlus[ind].pbpb[ix],30 + ind);
      groomHist(sysPlus[ind].pbpb[ix]); 
      jumSun(0,0,0.24,0);
      if ( ind == 0 )   sysPlus[ind].pbpb[ix]->Draw("hist");
      else       sysPlus[ind].pbpb[ix]->Draw("same hist");

      if ( ix==lowPtBin)  drawCentrality(kPbPb, icent, 0.37,0.83,1,20);
    }
    
  }
  TCanvas* cLeg = new TCanvas("clegend","",200,400);
  legPlus->Draw();
  

  TCanvas* cMinus = new TCanvas("cMinus","",1218,309);
  makeMultiPanelCanvas(cMinus,nPtPannels+1,1, 0.0, 0.01, 0.3, 0.2, 0.05);
  TLegend *legMinus = new TLegend(-0.005286785,0.1525575,1,1.001334,NULL,"brNDC");
  easyLeg(legMinus,"sys (-)", 0.07);

  for ( int ix = lowPtBin ; ix<= highPtBin ; ix++)  {
    cMinus->cd(ix - lowPtBin + 1);
    for ( int ind =0 ; ind <  vIndMinus.size() ; ind++) {
      handsomeTH1(sysMinus[ind].pp[ix],30 + ind);
      sysMinus[ind].pp[ix]->SetAxisRange(0.001,0.23,"X");
      sysMinus[ind].pp[ix]->SetAxisRange(-0.55,0.55,"Y");
      sysMinus[ind].pp[ix]->SetXTitle("m/p_{T}");
      sysMinus[ind].pp[ix]->SetYTitle("Uncertainty (Relative)");
      sysMinus[ind].pp[ix]->SetNdivisions(505,"X");
      sysMinus[ind].pp[ix]->SetNdivisions(505,"Y");
      fixedFontHist(sysMinus[ind].pp[ix],1.2,1.4,20);
      jumSun(0,0,0.24,0);
      if ( ind == 0 )   sysMinus[ind].pp[ix]->Draw("hist");
      else       sysMinus[ind].pp[ix]->Draw("same hist");
 
      if ( ix==lowPtBin) legMinus->AddEntry(sysMinus[ind].pp[ix], getSysName( vIndMinus[ind] ).Data(),"l" );
    } 
  }
  cMinus->cd(nPtPannels+1);
  legMinus->Draw();
  
  

}
