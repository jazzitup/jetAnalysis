
#if !(defined(__CINT__) || defined(__CLING__)) || defined(__ACLIC__)
#include <iostream>
using std::cout;
using std::endl;

#include "TRandom.h"
#include "TH1D.h"
#include "TH2D.h"


#include "../getSdHists.C"
#include "../ntupleDefinition.h"
//#include "../ntupleDefinition_v50.h"
#include "../commonUtility.h"
#include "../jzWeight.h"
#endif

//==============================================================================
// Global definitions
//==============================================================================

#include "../JssUtils.h"
#include <TPaletteAxis.h>
#include "unfoldingUtil.h"
#include <TGraphErrors.h>

double fracStst=001;

int lowPtBin = 5;

bool doCal=true;

void getDist( int kSample = kPP, int icent = 0, int optX=1, int optY=2, TH2D* hJMS=0, TH2D* hJMR=0, TH2D* hJES=0, TH2D* hJER=0, bool doReweight = true);

void getJMS(int kSample = kPP, int icent=0, int optX =1, int optY=2, bool doReweight=false) {
  TH1::SetDefaultSumw2();
  int nXbins;
  double xBin[30];
  getXbin(nXbins, xBin, optX);
  cout << " nXbins = " << nXbins << endl; 
  cout << " xBin = " << xBin[0] << ",   " << xBin[1] << ",   " <<xBin[2] << ", ..." <<endl;
  
  int highPtBin = nXbins-1;
  
  int vColor[20] = {20,30,31,38,40,41,43,44,46,6,4};

  int nYbins ;
  double yBin[30] ;
  getYbin(nYbins, yBin, optY);
  
  /*  nYbins = 8;
  yBin[0] = 0;
  yBin[1] = 0.01;
  yBin[2] = 0.02;
  yBin[3] = 0.04;
  yBin[4] = 0.07;
  yBin[5] = 0.1;
  yBin[6] = 0.15;
  yBin[7] = 0.24;
  */


  TH2D* hJMS = new TH2D("hJMS",";p_{T} (GeV) ; m/p_{T}", nXbins, xBin, nYbins, yBin);
  TH2D* hJMR = (TH2D*)hJMS->Clone("hJMR");
  TH2D* hJES = (TH2D*)hJMS->Clone("hJES");
  TH2D* hJER = (TH2D*)hJMS->Clone("hJER");
  
  getDist(kSample, icent, optX, optY, hJMS, hJMR, hJES, hJER, doReweight);

  
  TCanvas* c01 = new TCanvas("c01", "",800,400);
  c01->Divide(2,1);
  c01->cd(1);
  hJMS->Draw("colz");
  c01->cd(2);
  hJMR->Draw("colz");

  TCanvas* c2 = new TCanvas("c2", "",500,500);
  TLegend *leg1 = new TLegend(0.5903614,0.4810526,0.9698795,0.7484211,NULL,"brNDC");
  easyLeg(leg1,"Jet p_{T}");
  
  TF1* f1[30];
  TGraphErrors* gr[30];  
  double Rx[20];
  double Ry[20];
  double RxErr[20];
  double RyErr[20];
 
  for ( int ix = lowPtBin ; ix<=highPtBin ; ix++) { 
    TH1D* hs = (TH1D*)hJMS->ProjectionY(Form("hm_ix%d",ix),ix,ix);
    handsomeTH1(hs,vColor[ix-lowPtBin]);
    hs->SetXTitle("(m/p_{T})^{Truth}");
    hs->SetYTitle("(m/p_{T})^{Reco}/(m/p_{T})^{Truth}");
    hs->SetAxisRange(0.001,0.239,"X");
    hs->SetAxisRange(0,5,"Y");
    hs->SetNdivisions(505,"X");
    hs->SetNdivisions(505,"Y");
    if ( ix == lowPtBin) hs->Draw();
    else hs->Draw("same");
    

    for ( int im = 1 ; im <= hs->GetNbinsX() ; im++) {  
      Rx[im-1] = hs->GetBinCenter(im) * hs->GetBinContent(im);
      RxErr[im-1] = 0.0001;
      Ry[im-1] = hs->GetBinContent(im);
      RyErr[im-1] = hs->GetBinError(im);
    }
    gr[ix] = new TGraphErrors(hs->GetNbinsX(), Rx,Ry,RxErr,RyErr);
    handsomeTG1(gr[ix],vColor[ix-lowPtBin]);

    leg1->AddEntry(hs, textBin(xBin,ix,"GeV").Data(),"pl" );
  }
  jumSun(0,1,0.24,1);
  drawCentrality(kSample, icent, 0.2,0.85,1,25);
    if ( !doCal )
      drawText("Before Calibration",0.2,0.77,4,22);
    else 
      drawText("After mass Calibration",0.2,0.77,4,22);


  //  drawText("<m/p_{T}]>", 0.2,0.78,1,25);
  leg1->Draw();
  c2->SaveAs(Form("jms/jms_kSample%d_icent%d.pdf",kSample,icent));
  
  TCanvas* c4 = new TCanvas("c4","",500,500);
  TH1D* htemp = new TH1D("htemp",";m/p_{T} * R;R",100,0,0.3);
  htemp->SetAxisRange(0,5.2,"Y");
  htemp->Draw();
  for ( int ix = lowPtBin ; ix<=highPtBin ; ix++) {
    gr[ix]->Draw("same p");

    //    f1[ix] = new TF1(Form("f1_kSample%d_icent%d_ix%d",kSample,icent,ix),"[0] + [1]*x + [2]*x*x + [3]*x*x*x + [4]*x*x*x*x",0.01,0.24);
    f1[ix] = new TF1(Form("f1_kSample%d_icent%d_ix%d",kSample,icent,ix),"[0] + [1]*x + [2]*x*x + [3]*x*x*x + [4]*x*x*x*x + [5]*x*x*x*x*x",0.01,0.24);
    f1[ix]->SetParameter(0,8.5);
    f1[ix]->SetParameter(1,-170);
    f1[ix]->SetParameter(2,1372);
    f1[ix]->SetParameter(3,-4950);
    f1[ix]->SetParameter(4,6769);
    f1[ix]->SetParameter(5,-630);
    

    gr[ix]->Fit(f1[ix],"ll");
    gr[ix]->GetFunction(f1[ix]->GetName())->SetLineColor(vColor[ix-lowPtBin]);
    
  }  
  if ( !doCal)    
    c4->SaveAs(Form("numericalInversion_ksample%d_icent%d.pdf",kSample,icent));
  //  if ( !doCal ) {
  TFile* fout = new TFile(Form("fJMScalibration_kSample%d_icent%d_afterCal.root",kSample,icent), "recreate");
  for ( int ix = lowPtBin ; ix<=highPtBin ; ix++)  {
    f1[ix]->Write();
  }
  fout->Close();
  //  }
  
  c2->SaveAs(Form("JMS_vs_truthpT_ksample%d_icent%d_doCal%d.pdf",kSample,icent,(int)doCal));
  
  return;
  
  TCanvas* c3 = new TCanvas("c3", "",500,500);
  TLegend *leg2 = new TLegend(0.5061446,0.6142105,0.9599598,0.915789,NULL,"brNDC");
  easyLeg(leg2,"Jet p_{T}");
  
  for ( int ix = lowPtBin ; ix<=highPtBin ; ix++) { 
    TH1D* hr = (TH1D*)hJMR->ProjectionY(Form("hr_ix%d",ix),ix,ix);
    handsomeTH1(hr,vColor[ix-lowPtBin]);
    hr->SetXTitle("(m/p_{T})^{Truth}");
    hr->SetYTitle("Resolution");
    hr->SetAxisRange(0.001,0.239,"X");
    hr->SetAxisRange(0,0.1,"Y");
    hr->SetNdivisions(505,"X");
    hr->SetNdivisions(505,"Y");
    if ( ix == lowPtBin) hr->Draw();
    else hr->Draw("same");
    leg2->AddEntry(hr, textBin(xBin,ix,"GeV").Data(),"pl" );
  }
  

  //  jumSun(0,0,0.36,0);
  drawCentrality(kSample, icent, 0.2,0.85,1,25);
  drawText("#sigma[m/p_{T}]", 0.2,0.78,1,25);
  leg2->Draw();
  c3->SaveAs(Form("jms/jmr_kSample%d_icent%d.pdf",kSample,icent));



  TCanvas* c2s = new TCanvas("c2s", "",500,500);
  TLegend *leg1s = new TLegend(0.5061446,0.6142105,0.9599598,0.915789,NULL,"brNDC");
  easyLeg(leg1s,"Jet p_{T}");


  for ( int ix = lowPtBin+1 ; ix<=highPtBin ; ix++) { 
    TH1D* hs = (TH1D*)hJES->ProjectionY(Form("hs_ix%d",ix),ix,ix);
    handsomeTH1(hs,vColor[ix-lowPtBin]);
    hs->SetXTitle("(m/p_{T})^{Truth}");
    hs->SetYTitle("JES");
    hs->SetAxisRange(0.001,0.239,"X");
    hs->SetAxisRange(0.8,1.4,"Y");
    hs->SetNdivisions(505,"X");
    hs->SetNdivisions(505,"Y");
    if ( ix == lowPtBin+1) hs->Draw();
    else hs->Draw("same");
    leg1s->AddEntry(hs, textBin(xBin,ix,"GeV").Data(),"pl" );
  }
  jumSun(0,1,0.36,1);
  drawCentrality(kSample, icent, 0.2,0.85,1,25);
  drawText("<p_{T}^{Reco}/p_{T}^{Truth}]>", 0.2,0.78,1,25);
  leg1s->Draw();
 
  c2s->SaveAs(Form("jms/jes_kSample%d_icent%d.pdf",kSample,icent));


  TCanvas* c3a = new TCanvas("c3a", "",500,500);

  for ( int ix = lowPtBin+1 ; ix<=highPtBin ; ix++) { 
    TH1D* hr = (TH1D*)hJER->ProjectionY(Form("hr_ix%d",ix),ix,ix);
    handsomeTH1(hr,vColor[ix-lowPtBin]);
    hr->SetXTitle("(m/p_{T})^{Truth}");
    hr->SetYTitle("JER");
    hr->SetAxisRange(0.001,0.239,"X");
    hr->SetAxisRange(0,0.3,"Y");
    hr->SetNdivisions(505,"X");
    hr->SetNdivisions(505,"Y");
    if ( ix == lowPtBin+1) hr->Draw();
    else hr->Draw("same");
  }
  drawCentrality(kSample, icent, 0.2,0.85,1,25);
  drawText("#sigma[p_{T}^{Reco}/p_{T}^{Truth}]", 0.2,0.78,1,25);
  leg1s->Draw();
  c3a->SaveAs(Form("jms/jer_kSample%d_icent%d.pdf",kSample,icent));

}

void getDist( int kSample, int icent, int optX, int optY, TH2D* hJMS, TH2D* hJMR, TH2D* hJES, TH2D* hJER, bool doReweight ) { 
  
  double radius = 0.4;
  
  TH1::SetDefaultSumw2();
  TString jz2;
  TString jz3;
  TString jz4;
  if ( kSample == kPbPb ) {
    if ( radius==0.4 ) {
      // v50
      //      jz2 = "jetSubstructure_MC_HION9_pbpb_v50_jz2.root";
      //      jz3 = "jetSubstructure_MC_HION9_pbpb_v50_jz3.root";
      //      jz4 = "jetSubstructure_MC_HION9_pbpb_v50_jz4.root";
      jz2 = "jetSubstructure_pbpbMC_HION9_jz2_v51_april124.root";
      jz3 = "jetSubstructure_pbpbMC_HION9_jz3_v51_april124.root";
      jz4 = "jetSubstructure_pbpbMC_HION9_jz4_v51_april124.root";

    }
  }
  else if ( kSample == kPP ) {
    if ( radius==0.4 ) {
      //  jz2 = "jetSubstructure_MC_HION9_pp_v50_jz2.root";
      //      jz3 = "jetSubstructure_MC_HION9_pp_v50_jz3.root";
      //      jz4 = "jetSubstructure_MC_HION9_pp_v50_jz4.root";
      jz2 = "jetSubstructure_ppMC_HION9_jz2_v52_april124.root";
      jz3 = "jetSubstructure_ppMC_HION9_jz3_v52_april124.root";
      jz4 = "jetSubstructure_ppMC_HION9_jz4_v52_april124.root";
    }
  }
  
  TH1D* hFcalReweight;
  if ( kSample == kPbPb ) {
    //    TFile* fcal = new TFile("reweightFactors/FCal_HP_v_MB_weights.root");
    //    hFcalReweight = (TH1D*)fcal->Get("FCal_HP_v_MBOV_weights");
  }
  
  
  TH2D* hReweight;
  if ( doReweight ) {
    hReweight = getRewTable(kSample, icent);
  }
  
  
  jetSubStr  myJetMc;
  TBranch  *b_myJetSubMc;
  
  cout << " Setting tree branch address..." << endl;
  TFile* fjz2 = new TFile(Form("../ntuples/%s",jz2.Data()));
  TTree* tr2 = (TTree*)fjz2->Get("tr");
  tr2->SetBranchAddress("jets", &(myJetMc.cent), &b_myJetSubMc);
  
  
  TFile* fjz3 = new TFile(Form("../ntuples/%s",jz3.Data()));
  TTree* tr3 = (TTree*)fjz3->Get("tr");
  tr3->SetBranchAddress("jets", &(myJetMc.cent), &b_myJetSubMc);

  TFile* fjz4 = new TFile(Form("../ntuples/%s",jz4.Data()));
  TTree* tr4 = (TTree*)fjz4->Get("tr");
  tr4->SetBranchAddress("jets", &(myJetMc.cent), &b_myJetSubMc);

  int nXbins;
  double xBin[30];
  getXbin(nXbins, xBin, optX);

  int highPtBin = nXbins-1;

  int nYbins ;
  double yBin[30] ;
  getYbin(nYbins, yBin, optY);

  TH1D* xBinTemp = new TH1D("xBinTemp","", nXbins, xBin);
  TH1D* yBinTemp = new TH1D("yBinTemp","", nYbins, yBin);
  
  

  TH1D* hDist[20][20]; // gen pT  // gen m/pT
  TH1D* hDistJes[20][20]; // gen pT  // gen m/pT
  for ( int ix = 0 ; ix <= nXbins+1   ;  ix++) {
    for ( int iy = 0 ; iy <= nYbins+1 ; iy++) {
      hDist[ix][iy] = new TH1D(Form("hDist_ix%d_iy%d",ix,iy),";(m/p_{T})^{Reco} - (m/p_{T})^{Truth};", 100,-3,10);
      hDistJes[ix][iy] = new TH1D(Form("hDistJes_ix%d_iy%d",ix,iy),";p_{T}^{Reco}/p_{T}^{Truth};", 100,0,2);
    }
  }

  TFile* fin = new TFile(Form("fJMScalibration_kSample%d_icent%d_num.root",kSample,icent));
  TF1* fjmscal[30];
  if ( doCal) {  
    for ( int ix = lowPtBin ; ix<=highPtBin ; ix++) { 
      fjmscal[ix] = (TF1*)fin->Get(Form("f1_kSample%d_icent%d_ix%d",kSample,icent,ix));
    }
  }
  
  for ( int ijz =2 ; ijz<=4 ; ijz++) { 
    TTree* tr;
    TH2D* hRecoEntries;
    double jzNorm=0;
    if ( ijz==2)  {
      tr = tr2;   
      jzNorm = hi9EvtWgtJZ2; 
    }
    else if ( ijz==3)  {
      tr = tr3;   
      jzNorm = hi9EvtWgtJZ3; 
    }
    else if ( ijz==4)  {
      tr = tr4;   
      jzNorm = hi9EvtWgtJZ4; 
    }
    cout << "Scanning JZ"<<ijz<<" file.  Total events = " << tr->GetEntries() << endl;
    
    for (Int_t i= 0; i<tr->GetEntries() ; i++) {
      if ( i > tr->GetEntries() * fracStst ) continue;
      tr->GetEntry(i);
      
      if ( passJesEvent(myJetMc, icent) == false ) // true = isMC
	continue;
      
      double recoVarX, truthVarX;
      getXvalues( recoVarX, truthVarX, myJetMc, optX);
      
      double recoVarY, truthVarY;
      getYvalues( recoVarY, truthVarY, myJetMc, optY);
      
      double fcalWeight = 1.0; 
      if ( kSample==kPbPb) {
	//	fcalWeight = hFcalReweight->GetBinContent(hFcalReweight->GetXaxis()->FindBin(myJetMc.fcalet));
      }
      
      // Data/MC reweighting factors 
      double rewFact = 1; 
      if ( doReweight) { 
	//	  int rewBin = hReweight->FindBin(myJetMc.recoPt, myJetMc.recoMass);
	int rewBin = hReweight->FindBin(myJetMc.recoPt, myJetMc.recoMass/myJetMc.recoPt);
	rewFact = hReweight->GetBinContent(rewBin);
      }
      
      int xx = xBinTemp->FindBin( truthVarX);
      
      int yy = yBinTemp->FindBin( truthVarY);
      //int yy = yBinTemp->FindBin( recoVarY);
      
      double calFac = 1;
      if (  ( xx <= highPtBin  ) && ( xx>=lowPtBin) ) { 
	if ( doCal) {
	  if ( recoVarY < 0 ) 
	    calFac = fjmscal[xx]->Eval(0);
	  else if ( recoVarY > 0.25 ) 
	    calFac = fjmscal[xx]->Eval(0.25);
	  else 
	    calFac = fjmscal[xx]->Eval(recoVarY);

	  recoVarY = recoVarY / calFac;
	}
      }
      hDist[xx][yy]->Fill(recoVarY/truthVarY);
      hDistJes[xx][yy]->Fill( myJetMc.recoPt / myJetMc.genPt );
    }
    
  }
  
  for ( int ix = 1 ; ix <= nXbins ; ix++) {
    for ( int iy = 1 ; iy <= nYbins ; iy++)  {
      double theMean = hDist[ix][iy]->GetBinCenter( hDist[ix][iy]->GetMaximumBin() );
      double theRms = hDist[ix][iy]->GetRMS();

      hDist[ix][iy]->Fit("gaus", "","",theMean - 1*theRms, theMean + .5*theRms);
      //      hDist[ix][iy]->Fit("gaus");
      if ( hDist[ix][iy]->GetFunction("gaus") == NULL ) {
	hJMS->SetBinContent(ix,iy,-100);
	hJMS->SetBinError(ix,iy,-100);
	hJMR->SetBinContent(ix,iy,-100);
	hJMR->SetBinError(ix,iy,-100);
      }
      else {
	float theJMS = hDist[ix][iy]->GetFunction("gaus")->GetParameter(1);
	float theJMSerr = hDist[ix][iy]->GetFunction("gaus")->GetParError(1);
	float theJMR = hDist[ix][iy]->GetFunction("gaus")->GetParameter(2);
	float theJMRerr = hDist[ix][iy]->GetFunction("gaus")->GetParError(2);
	hJMS->SetBinContent(ix,iy,theJMS);
	hJMS->SetBinError(ix,iy,theJMSerr);
	hJMR->SetBinContent(ix,iy,theJMR);
	hJMR->SetBinError(ix,iy,theJMRerr);
      }
    }
  }
  
  for ( int ix = 1 ; ix <= nXbins ; ix++) {
    for ( int iy = 1 ; iy <= nYbins ; iy++)  {
      hDistJes[ix][iy]->Fit("gaus");
      if ( hDistJes[ix][iy]->GetFunction("gaus") == NULL ) {
        hJES->SetBinContent(ix,iy,-100);
        hJES->SetBinError(ix,iy,-100);
        hJER->SetBinContent(ix,iy,-100);
        hJER->SetBinError(ix,iy,-100);
      }
      else {
        float theJMS = hDistJes[ix][iy]->GetFunction("gaus")->GetParameter(1);
        float theJMSerr = hDistJes[ix][iy]->GetFunction("gaus")->GetParError(1);
        float theJMR = hDistJes[ix][iy]->GetFunction("gaus")->GetParameter(2);
        float theJMRerr = hDistJes[ix][iy]->GetFunction("gaus")->GetParError(2);
        hJES->SetBinContent(ix,iy,theJMS);
        hJES->SetBinError(ix,iy,theJMSerr);
        hJER->SetBinContent(ix,iy,theJMR);
        hJER->SetBinError(ix,iy,theJMRerr);
      }
    }
  }

  TFile* foutJMS = new TFile(Form("jms/jms_kSample%d_icent%d_doReweight%d.root",kSample,icent,doReweight),"recreate");
  for ( int ix = 1 ; ix <= nXbins ; ix++) {
    for ( int iy = 1 ; iy <= nYbins ; iy++)  {
      hDist[ix][iy]->Write();
      hDistJes[ix][iy]->Write();
    }
  }
  
  
}
 
