double fracStst=1;
bool doCal=0;

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


struct valErr {
  double val;
  double err;
};


valErr getMeanValue(TH1D* h1, double x1, double x2) {
  valErr ret;
  
  TH1D* htemp = (TH1D*)h1->Clone("htemp");

  int ix1 = htemp->FindBin(x1);
  int ix2 = htemp->FindBin(x2);
  
  for ( int ix = 0 ; ix<= htemp->GetNbinsX() ; ix++) { 
    
    if ( (ix >= ix1) && ( ix<ix2) )  continue;
    
    htemp->SetBinContent(ix,0);
    htemp->SetBinError(ix,0);
  }
  ret.val = htemp->GetMean();
  ret.err = htemp->GetMeanError();
  cout << "Range = " << x1 <<" ~ " << x2 << endl;
  cout << "Mean  = " << ret.val << endl;
  cout << "Integral  = " << htemp->Integral() << endl;

  delete htemp;
  return ret;
}

bool doReweight = false; 


void getDist( int kSample = kPP, int icent = 0, int etaBin=0, int optX=-1, int optY=-1, TH2D* hJMS=0, TH2D* hJMR=0, TH2D* hFineMpt2=0);

void getJmsCalibration(int kSample = kPP, int icent=0, int etaBin=1) { 

  int optX = 0;
  if ( etaBin == 0 )  optX = 210;
  else if ( etaBin == 1 )  optX = 211;
  else if ( etaBin == 2 )  optX = 212;

  int optY=21;
  
  TH1::SetDefaultSumw2();
  int vColor[20] =   {1, 2, 38,40,41,4,44,46,6,48};
  int vStyle[20] =   {20,21,25,23,29,33,28,47,43};
  
  
  int nXbins;
  double xBin[30];
  getXbin(nXbins, xBin, optX);
  cout << " nXbins = " << nXbins << endl; 
  cout << " xBin = " << xBin[0] << ",   " << xBin[1] << ",   " <<xBin[2] << ", ..." <<endl;

  TH1D* xBinTemp = new TH1D("xBinTemp","", nXbins, xBin);

  int lowPtBin = 1;
  int highPtBin = nXbins;
  
  int nYbins ;
  double yBin[30] ;  // m/pT
  double yBin2[30] ;  // m/pT square 
  double yBinMt[30] ; // mT/pT square 
  getYbin(nYbins, yBin, optY);
  for ( int i=0 ; i<=nYbins ;i++) {
    if ( yBin[i] > 0 ) 
      yBinMt[i] = yBin[i]*yBin[i] + 1;
    else   
      yBinMt[i] = -yBin[i]*yBin[i] + 1;
    
    yBin2[i] = yBinMt[i] -1;
  }
  cout << " m/pT bin : " << endl;
  for ( int i=0 ; i<= nYbins ; i++) {
    cout << yBin[i] <<",  ";
  }
  cout << endl;


  cout << " mT bin : " << endl;
  for ( int i=0 ; i<= nYbins ; i++) {
    cout << yBinMt[i] <<",  ";
  }
  cout << endl;
  
  
  TH2D* hJMS = new TH2D("hJMS",";p_{T} (GeV) ; (m/p_{T})^{2}", nXbins, xBin, nYbins, yBin2);
  
  TH2D* hJMR = (TH2D*)hJMS->Clone("hJMR");
  TH2D* hFineMpt2 = new TH2D("hFineMpt2",";p_{T} (GeV); (m/p_{T})^{2}",nXbins, xBin, 2000,0,0.5);

  TH1D* htempMpt2 = new TH1D("htempMpt2","", nYbins, yBin2); 
  
  
  getDist(kSample, icent, etaBin, optX, optY, hJMS, hJMR, hFineMpt2);
  
  
  TCanvas* c01 = new TCanvas("c01", "",800,400);
  c01->Divide(2,1);
  c01->cd(1);
  hJMS->Draw("colz");
  c01->cd(2);
  hJMR->Draw("colz");

  TCanvas* c2s = new TCanvas("c2s", "",500,500);
  TLegend *leg1s = new TLegend(0.5061446,0.6142105,0.9599598,0.915789,NULL,"brNDC");
  easyLeg(leg1s,"Jet p_{T}");
  
  TF1* f1[20];
  TF1* f1Inv[20];
  TGraphErrors* gr[30];
  TGraphErrors* grInv[30];
  double Rx[20];
  double Ry[20];
  double RxErr[20];
  double RyErr[20];

  double RyInv[20];
  double RyInvErr[20];

  for ( int ix = lowPtBin ; ix<=highPtBin ; ix++) { 
    TH1D* hs = (TH1D*)hJMS->ProjectionY(Form("hs_ix%d",ix),ix,ix);
    handsomeTH1(hs,vColor[ix-lowPtBin]);
    hs->SetXTitle("[m_{T}/p_{T}]^{2}_{Truth}");
    hs->SetYTitle("Res. of [m_{T}/p_{T}]^{2}");
    hs->SetAxisRange(0.001,0.12,"X");
    hs->SetAxisRange(0.,10,"Y");
    hs->SetNdivisions(505,"X");
    hs->SetNdivisions(505,"Y");
    if ( ix == lowPtBin) hs->Draw();
    else hs->Draw("same");

    TH1D* hFineMpt21d = (TH1D*)hFineMpt2->ProjectionY(Form("_%d",ix),ix,ix);
    int nPoints=0;
    for ( int im = 1 ; im <= hs->GetNbinsX() ; im++) {
      //      cout << " ix = " << ix << endl;
      //      cout << " xBin[ix] = " << xBin[ix] << " GeV " << endl;
      valErr meanPair = getMeanValue(hFineMpt21d, htempMpt2->GetBinLowEdge(im), htempMpt2->GetBinLowEdge(im+1) );
      if ( meanPair.val == 0 )   { 
	cout << "no entries" << endl;
	continue;
      }

      Rx[nPoints] = meanPair.val * hs->GetBinContent(im);
      RxErr[nPoints] = meanPair.err * hs->GetBinContent(im);
      Ry[nPoints] = hs->GetBinContent(im);
      RyErr[nPoints] = hs->GetBinError(im);

      RyInv[nPoints] = 1./Ry[nPoints];
      RyInvErr[nPoints] = RyInv[nPoints] * ( RyErr[nPoints] / Ry[nPoints] ) ;
      
      nPoints++;
    }
    gr[ix] = new TGraphErrors(nPoints, Rx,Ry,RxErr,RyErr);
    grInv[ix] = new TGraphErrors(nPoints, Rx,RyInv,RxErr,RyInvErr);
    handsomeTG1(gr[ix],vColor[ix-lowPtBin]);
    handsomeTG1(grInv[ix],vColor[ix-lowPtBin]);

    leg1s->AddEntry(gr[ix], textBin2(xBin,ix,"GeV").Data(),"pl" );
  }
  jumSun(0,1,0.36,1);
  drawCentrality(kSample, icent, 0.2,0.85,1,25);
  //  drawText("<p_{T}^{Reco}/p_{T}^{Truth}>", 0.2,0.78,1,25);
  leg1s->Draw();
  
  c2s->SaveAs(Form("jmsCalib/jms_kSample%d_icent%d_optX%d_optY%d_etaBin%d.pdf",kSample,icent,optX, optY, etaBin));
  TLegend *leg2 = new TLegend(0.4673663,0.5040816,0.8668024,0.9040816,NULL,"brNDC");
  easyLeg(leg2,"Jet p_T^{Reco}");
  
  TCanvas* c4 = new TCanvas("c4","",1000,500);
  c4->Divide(2,1);
  c4->cd(1);
  TH1D* htemp = new TH1D("htemp",";[m/p_{T}]^{2} * R;R",1000,0,0.15);
  htemp->SetAxisRange(0,10,"Y");
  htemp->DrawCopy();
  for ( int ix = lowPtBin ; ix<=highPtBin ; ix++) {
    gr[ix]->Draw("same p");
    leg2->AddEntry(gr[ix], textBin2(xBin,ix,"GeV").Data(),"pl" );
    
    f1[ix] = new TF1(Form("f1_kSample%d_icent%d_ix%d",kSample,icent,ix),"[0] + [1]*log(x+1) + [2]*pow(log(x+1),2) +  [3]*pow(log(x+1),3) + [4]*pow(log(x+1),4)",0.1,2);
    f1[ix]->SetParameter(0,1);
    
    if ( !doCal) { 
      gr[ix]->Fit(f1[ix],"M","",0,0.08);
      if ( gr[ix]->GetFunction(f1[ix]->GetName()) != NULL)
	gr[ix]->GetFunction(f1[ix]->GetName())->SetLineColor(vColor[ix-lowPtBin]);
    }
    
  }
  
  c4->cd(2);
  htemp->SetAxisRange(0,3.2,"Y");
  htemp->SetYTitle("1/R");
  htemp->DrawCopy();
  for ( int ix = lowPtBin ; ix<=highPtBin ; ix++) {
    grInv[ix]->Draw("same p");

    f1Inv[ix] = new TF1(Form("fInv_kSample%d_icent%d_ix%d",kSample,icent,ix),"TMath::Erf((x-[0])/[1])*[2] +[3]",0,0.08);
    f1Inv[ix]->SetParameter(0,0.01);
    f1Inv[ix]->SetParameter(1,0.001);
    f1Inv[ix]->SetParameter(2,1);
    //    f1[ix]->SetParameter(3,1.2);
    if ( !doCal) {
      grInv[ix]->Fit(f1Inv[ix],"M","",0,0.08);
      if ( grInv[ix]->GetFunction(f1Inv[ix]->GetName()) != NULL)
        grInv[ix]->GetFunction(f1Inv[ix]->GetName())->SetLineColor(vColor[ix-lowPtBin]);
    }
    
    //    grInv[ix]->Fit
    
  }
  leg2->Draw();
  
  
  if ( !doCal) {

    TFile* foutJMS = new TFile(Form("jmsCalib/jmsCorrectionFactor_kSample%d_icent%d_etaBin%d.root",kSample,icent,etaBin),"recreate");
    for ( int ix = 1 ; ix<=nXbins ; ix++) {
      if ( gr[ix]->GetFunction(f1[ix]->GetName()) != NULL) 
	gr[ix]->GetFunction(f1[ix]->GetName())->Write();

      if ( grInv[ix]->GetFunction(f1Inv[ix]->GetName()) != NULL)
	grInv[ix]->GetFunction(f1Inv[ix]->GetName())->Write();

    }
    xBinTemp->Write();

    foutJMS->Close();
  }
  
  // m/pT^2 scale and resolution 

  TCanvas* c3a = new TCanvas("c3a", "",500,500);

  for ( int ix = lowPtBin ; ix<=highPtBin ; ix++) { 
    TH1D* hr = (TH1D*)hJMS->ProjectionY(Form("hjms_ix%d",ix),ix,ix);
    handsomeTH1(hr,vColor[ix-lowPtBin]);
    hr->SetXTitle("[(m/p_{T})^{2}]_{Truth}");
    hr->SetYTitle("Scale of [(m/p_{T})^{2}]");
    hr->SetAxisRange(0.0035,0.14,"X");
    hr->SetAxisRange(0,4.5,"Y");
    hr->SetNdivisions(505,"X");
    hr->SetNdivisions(505,"Y");
    if ( ix == lowPtBin) hr->Draw();
    else hr->Draw("same");
  }
  drawCentrality(kSample, icent, 0.2,0.85,1,25);
  //  drawText("#sigma[p_{T}^{Reco}/p_{T}^{Truth}]", 0.2,0.78,1,25);
  //  leg1s->Draw();
  gPad->SetLogx();

  c3a->SaveAs(Form("jmsCalib/jms_mpt2_kSample%d_icent%d-etaBin%d.pdf",kSample,icent,etaBin));



  TCanvas* c3b = new TCanvas("c3b", "",500,500);

  for ( int ix = lowPtBin ; ix<=highPtBin ; ix++) { 
    TH1D* hr = (TH1D*)hJMR->ProjectionY(Form("hr_ix%d",ix),ix,ix);
    handsomeTH1(hr,vColor[ix-lowPtBin]);
    hr->SetXTitle("[(m/p_{T})^{2}]_{Truth}");
    hr->SetYTitle("Resoultion of [(m/p_{T})^{2}]");
    hr->SetAxisRange(0.0035,0.14,"X");
    hr->SetAxisRange(0,3.5,"Y");
    hr->SetNdivisions(505,"X");
    hr->SetNdivisions(505,"Y");
    if ( ix == lowPtBin) hr->Draw();
    else hr->Draw("same");
  }
  drawCentrality(kSample, icent, 0.2,0.85,1,25);
  //  leg1s->Draw();
  gPad->SetLogx();
  c3b->SaveAs(Form("jmsCalib/jmr_mpt2_kSample%d_icent%d-etaBin%d.pdf",kSample,icent,etaBin));

  //  if ( !doCal )
  //    drawText("Before calibration",0.2,0.77,4,22);
  //  else 
  //    drawText("After calibration",0.2,0.77,4,22);
}

void getDist( int kSample, int icent, int etaBin, int optX, int optY, TH2D* hJMS, TH2D* hJMR, TH2D* hFineMpt2 ) { 
  
  
  TH1::SetDefaultSumw2();
  TString jz2;
  TString jz3;
  TString jz4;
  if ( kSample == kPbPb ) {
    jz2 = "jetSubstructure_pbpbMC_HION9_jz2_v51_april124.root";
    jz3 = "jetSubstructure_pbpbMC_HION9_jz3_v51_april124.root";
    jz4 = "jetSubstructure_pbpbMC_HION9_jz4_v51_april124.root";
  }
  else if ( kSample == kPP ) {
    jz2 = "jetSubstructure_ppMC_HION9_jz2_v52_april124.root";
    jz3 = "jetSubstructure_ppMC_HION9_jz3_v52_april124.root";
    jz4 = "jetSubstructure_ppMC_HION9_jz4_v52_april124.root";
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

  int nYbins ;
  double yBin[30];
  getYbin(nYbins, yBin, optY);


  TH1D* xBinTemp = new TH1D("xBinTemp","", nXbins, xBin);
  TH1D* yBinTemp = new TH1D("yBinTemp","", nYbins, yBin);
  
  TH1D* hDistJms2[20][20]; // reco pT  // gen m/pT
  //  TH1D* hDistJmts[20][20]; // reco pT  // gen m/pT
  TH1D* hDistMpt2[20][20]; // reco pT  // gen m/pT
  for ( int ix = 0 ; ix <= nXbins+1   ;  ix++) {
    for ( int iy = 0 ; iy <= nYbins+1 ; iy++) {
      
      int theNbins = 120;  float t1 = 0.95;  float t2 = 1.02;
      if ( iy<=2 ) 	  theNbins = 120; 
      else if ( iy<=4 )   theNbins = 60;  
      else    	          theNbins = 30;  
      
      hDistMpt2[ix][iy] = new TH1D(Form("hDistMpt2_ix%d_iy%d",ix,iy),";[m/p_{T}]^2_{Reco};", 100,0.9,1.1);
      //      hDistJmts[ix][iy] = new TH1D(Form("hDistJmts_ix%d_iy%d",ix,iy),";[m/p_{T}]^2_{Reco} / [m/p_{T}]^2_{Truth};", theNbins, t1, t2);

      if ( iy<=2 )   hDistJms2[ix][iy] = new TH1D(Form("hDistJms_ix%d_iy%d",ix,iy),";[m/p_{T}]^2_{Reco} / [m/p_{T}]^2_{Truth};", 30, -3,13);
      else if ( iy<=5 )   hDistJms2[ix][iy] = new TH1D(Form("hDistJms_ix%d_iy%d",ix,iy),";[m/p_{T}]^2_{Reco} / [m/p_{T}]^2_{Truth};", 50, -1,4);
      else if ( iy<=7)  hDistJms2[ix][iy] = new TH1D(Form("hDistJms_ix%d_iy%d",ix,iy),";[m/p_{T}]^2_{Reco} / [m/p_{T}]^2_{Truth};", 50, 0,2);
      else   hDistJms2[ix][iy] = new TH1D(Form("hDistJms_ix%d_iy%d",ix,iy),";[m/p_{T}]^2_{Reco} / [m/p_{T}]^2_{Truth};", 50, -0,2);
      
      
    }
  }

  TF1* fjmscal[30];
  TF1* fjmscalInv[30];
  if ( doCal) {  
    TFile* fin = new TFile(Form("jmsCalib/jmsCorrectionFactor_kSample0_icent%d_etaBin%d.root", icent,etaBin));
    for ( int ix = 1  ; ix<=nXbins ; ix++) { 
      fjmscalInv[ix] = (TF1*)fin->Get(Form("fInv_kSample0_icent0_ix%d",ix));
    }
  }
  
  for ( int ijz =2 ; ijz<=4 ; ijz++) { 
    TTree* tr;
    TH2D* hRecoEntries;
    double jzNorm=0;
    if ( ijz==2)  {
      tr = tr2;          jzNorm = hi9EvtWgtJZ2; 
    }
    else if ( ijz==3)  {
      tr = tr3;          jzNorm = hi9EvtWgtJZ3; 
    }
    else if ( ijz==4)  {
      tr = tr4;          jzNorm = hi9EvtWgtJZ4; 
    }
    cout << "Scanning JZ"<<ijz<<" file.  Total events = " << tr->GetEntries() << endl;
    
    for (Int_t i= 0; i<tr->GetEntries() ; i++) {
      if ( i > tr->GetEntries() * fracStst ) continue;
      tr->GetEntry(i);
      
      if ( passJesEvent(myJetMc, icent) == false ) // true = isMC
	continue;
      
      if ( !passEtaCut(myJetMc, etaBin) )
        continue;

      double recoPt = myJetMc.recoPt ; 
      double genPt = myJetMc.genPt; ;
                 
      double genMpt2 =  pow(myJetMc.genMass/myJetMc.genPt, 2);
      double recoMpt2 = pow(myJetMc.recoMass/myJetMc.recoPt, 2);
      if ( myJetMc.recoMass < 0) recoMpt2 = -recoMpt2;
      
      double calVal = recoMpt2/genMpt2;
   
      int xx = xBinTemp->FindBin( recoPt);
      int yy = yBinTemp->FindBin( myJetMc.genMass / myJetMc.genPt);
      
      double calFac = 1;
      if (  ( xx <= nXbins  ) && ( xx>=1) ) { 
	if ( doCal) {
	  cout << "  Stopped" << endl;
	  return;
	  if ( calVal+1 < 1.003 )
	    calFac = fjmscal[xx]->Eval(1.003);
	  else if ( calVal+1 > 1.03 )
	    calFac = fjmscal[xx]->Eval(1.03);
	  else 
	    calFac = fjmscal[xx]->Eval(calVal+1);
	  
	  calVal = (calVal+1) / calFac -1 ;
	}
      }
      //      cout << " calFac = " << calFac << endl;
      //      cout << " calVal = " << calVal << endl;
      float theWeight = myJetMc.weight * jzNorm;
      hDistJms2[xx][yy]->Fill(calVal, theWeight);
      hFineMpt2->Fill( recoPt, genMpt2, theWeight) ;
      hDistMpt2[xx][yy]->Fill( recoMpt2, theWeight );
      
    }
    
  }
  
  for ( int ix = 1 ; ix <= nXbins ; ix++) {
    for ( int iy = 1 ; iy <= nYbins ; iy++)  {

      int peakBin  = hDistJms2[ix][iy]->GetMaximumBin();
      double peak =  hDistJms2[ix][iy]->GetBinCenter(peakBin);
      double sigma = hDistJms2[ix][iy]->GetRMS();
      cout << " entries : " << hDistJms2[ix][iy]->GetEntries() << endl;
      hDistJms2[ix][iy]->Fit("gaus","Q","",peak-sigma*1,peak+sigma*1);
      if ( hDistJms2[ix][iy]->GetFunction("gaus") == NULL ) {
	cout << "*error**************************" << endl;
	cout << "There is no gaussian fit stored!" << endl << endl << endl;
	cout << "********************************" << endl;
      }
      else {
	cout << "gaussian fit exists" << endl;
	float theReco =  hDistJms2[ix][iy]->GetFunction("gaus")->GetParameter(1) ;
	float theRecoErr = hDistJms2[ix][iy]->GetFunction("gaus")->GetParError(1);
	float theJMS = hDistJms2[ix][iy]->GetFunction("gaus")->GetParameter(1);
	float theJMSerr = hDistJms2[ix][iy]->GetFunction("gaus")->GetParError(1);
	float theJMR = hDistJms2[ix][iy]->GetFunction("gaus")->GetParameter(2);
	float theJMRerr = hDistJms2[ix][iy]->GetFunction("gaus")->GetParError(2);
	// fill square root of it. 

	hJMS->SetBinContent(ix,iy,theReco);
	hJMS->SetBinError(ix,iy,theRecoErr);
	hJMR->SetBinContent(ix,iy,theJMR);
	hJMR->SetBinError(ix,iy,theJMRerr);
      }
    }
  }
  
  for ( int ix = 1 ; ix <= nXbins ; ix++) {
    TCanvas* cDist = new TCanvas(Form("cDist_%d",ix),"",1200,500);
    cDist->Divide(5,2);
    for ( int iy = 1 ; iy <= nYbins ; iy++)  {
      cDist->cd(iy);
      cleverRange(hDistJms2[ix][iy],1.5,0.00000001);
      hDistJms2[ix][iy]->Draw();
      drawBinPt(xBin,ix,"GeV", 0.25 ,0.88,1,18);
      drawBinMpt(yBin,iy,"", 0.25 ,0.8,1,18);
    }
    cDist->SaveAs(Form("jmsCalib/mtpt2scale_pt%d_kSample%d_etaBin%d_optX%d_optY%d.png",ix,kSample,etaBin,optX,optY));
  }

  TCanvas* cDistMpt = new TCanvas("cDistMpt","",1200,500);
  cDistMpt->Divide(5,2);
  for ( int ix = 1 ; ix <= nXbins ; ix++) {
    for ( int iy = 1 ; iy <= nYbins ; iy++)  {
      cDistMpt->cd(iy);
      hDistMpt2[ix][iy]->Draw();
      drawBinPt(xBin,ix,"GeV", 0.25 ,0.88,1,18);
      drawBinMpt2(yBin,iy,"",  0.25 ,0.8, 1,18);
    }
    cDistMpt->SaveAs(Form("jmsCalib/SimpleMpt2Dist_pt%d_kSample%d_etaBin%d_optX%d_optY%d.png",ix,kSample,etaBin,optX,optY));
  }
  
  
  TFile* foutJMS = new TFile(Form("jmsCalib/jms_kSample%d_icent%d_etaBin%d_optX%d_optY%d.root",kSample,icent,etaBin,optX,optY),"recreate");
  for ( int ix = 1 ; ix <= nXbins ; ix++) {
    for ( int iy = 1 ; iy <= nYbins ; iy++)  {
      //      hDist[ix][iy]->Write();
      hDistJms2[ix][iy]->Write();
      hDistMpt2[ix][iy]->Write();
    }
  }
  hFineMpt2->Write();
  foutJMS->Close();
  
}
 
