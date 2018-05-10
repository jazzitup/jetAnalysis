#include <iostream>
using std::cout;
using std::endl;

#include "TRandom.h"
#include "TH1D.h"
#include "../getSdHists.C"
#include "../ntupleDefinition_v50.h"
#include "../commonUtility.h"
#include "../jzWeight.h"
#include "unfoldingUtil.h"
#include "../JssUtils.h"
#include <TPaletteAxis.h>

double statUsed = 0.01;

int lowPtBin = 1;  int highPtBin = 13;

int nPtPannels = highPtBin-lowPtBin+1;

void getMeanPt(int kSample=kPP, int icent=0, TH1D* hMean=0);


void getMCJmr(int kSample=kPP, int icent=0,  TH2D* hmc=0);

double findPeak(TF1* f, double low =2,double high = 4 ) {
  double v1 = f->GetParameter(1);
  double v2 = f->GetParameter(2);
  // Peak = ([1] - 0.22278) 
  // https://root.cern.ch/root/html528/TMath.html#TMath:Landau
  return (v1-0.22278);
}
/*  double step = 0.001;
  double maxY =  -10000;
  double peakPosition  = 0;
  for ( double xx = low ; xx<= high ; xx = xx+step){ 
    double yy = f->Eval(xx);
    if ( yy > maxY)  {
      maxY  = yy; 
      peakPosition = xx;
    }
  }
  return peakPosition;
*/


double errPeak(TF1* f) { 
  double v1 = f->GetParameter(1);
  double v2 = f->GetParameter(2);
  double e1 = f->GetParError(1);
  //  double e2 = f->GetParError(2);
  // Peak = ([1] - 0.22278)* [2]
  // https://root.cern.ch/root/html528/TMath.html#TMath:Landau
  //  double ec1 =  (v1-0.22278)*e2  ;
  //  double ec2 =  e1 * v2 ; 
  return e1; 
}

void getJMR(int kSample = kPbPb, int icent=0) {   // opt1 : mass,   opt2 : m/pT  
  TH1::SetDefaultSumw2();

  int optX = 1;    int optY = 2;  

  //  int nXbins;
  //  double xBin[30];
  //  getXbin(nXbins, xBin, optX);
  //  int lowPtBin = 6;
  //  int highPtBin = 11;
  //  int nPtPannels = highPtBin-lowPtBin+1;
  int nXbins = 7;
  double xBin[30] = { 120,140,160,180,210,250,350,800}; 
  int lowPtBin = 1;
  int highPtBin = 7;
  

  int nPtPannels = highPtBin-lowPtBin+1;


  int nYbins ;
  double yBin[30] ;
  getYbin(nYbins, yBin, optY);

  int nRbins = 60;
  TH2D* hTemp = new TH2D("rTemp","", nRbins, -0.5,2.5, nXbins, xBin);
  TH1D* hJms = new TH1D(Form("hJms_kSample%d_icent%d",kSample,icent),";p_{T} (GeV/c);JMS;",nXbins, xBin);
  TH1D* hJmr = new TH1D(Form("hJmr_kSample%d_icent%d",kSample,icent),";p_{T} (GeV/c);JMR;",nXbins, xBin);
  
  // MC 
  TH2D* hmc = (TH2D*)hTemp->Clone(Form("hmc_kSample%d_icent%d",kSample,icent));
  TH1D* h1mc[20];

  getMCJmr   ( kSample, icent, hmc);
  

  //  TCanvas* c1 = new TCanvas("c1","",400,400);
  //  TH1D* hMeanPt = new TH1D("hmeanpt","",nXbins,xBin);
  //  getMeanPt(kSample,icent,hMeanPt);
  //  hMeanPt->DrawCopy();

  TCanvas* c2 =  new TCanvas("c2","",1200,400);
  makeMultiPanelCanvas(c2,nPtPannels, 1, 0.0, 0.01, 0.3, 0.2, 0.05);
  for ( int ix = lowPtBin ; ix<= highPtBin ; ix++) {
    c2->cd(ix - lowPtBin + 1);
    h1mc[ix] = (TH1D*)hmc->ProjectionX(Form("h1mc_ipt%d",ix),ix,ix);
    scaleInt(h1mc[ix]);
    handsomeTH1(h1mc[ix],1);
    cleverRange(h1mc[ix],2.);

    TF1 *f1mc = new TF1(Form("fitH1mc_ix%d",ix),"[0] * TMath::Gaus(x,[1],[2])",0.6,1.3);
    f1mc->SetParameter(0,2);
    f1mc->SetParameter(1,1);
    f1mc->SetParameter(2,0.3);
    
    h1mc[ix]->Fit(f1mc->GetName(),"","",0.5,1.3);
    //h1mc[ix]->GetFunction(f1mc->GetName())->SetLineColor(1);
    h1mc[ix]->SetXTitle("(m/p_{T})^{Reco}/(m/p_{T})^{Truth}");
    h1mc[ix]->SetTitleSize(0.085);
    h1mc[ix]->Draw();
    
    if ( ix== lowPtBin)    drawCentrality(kSample, icent, 0.40,0.86,1,24);
    drawBin(xBin,ix,"GeV",0.4,0.79,49,16);
    
    hJms->SetBinContent(ix, fabs(f1mc->GetParameter(1)));
    hJms->SetBinError(ix, f1mc->GetParError(1));
    hJmr->SetBinContent(ix, fabs(f1mc->GetParameter(2)));
    hJmr->SetBinError(ix, f1mc->GetParError(2));
    handsomeTH1(hJmr,4);

    
  }
  c2->SaveAs(Form("pdfsJMR/JMSdist_kSample%d_cent%d.pdf",kSample,icent));

  TCanvas* c3 = new TCanvas("c3","",500,500);
  hJms->SetAxisRange(0,2,"Y");
  //  TF1* f1 = new TF1("f1","[0] +x*[1]",xBin[0], xBin[nXbins]);   // for jms
  TF1* f1 = new TF1("f1","[0] +log(x)*[1]",xBin[0], xBin[nXbins]);   // for jms
  TF1* f2 = new TF1("f2","[0] +x*[1]",xBin[0], xBin[nXbins]);
  cout << " ==== JMS function  === [0] + log(x)*[1] =====" << endl;
  hJms->Fit("f1");   
  cout << " =*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=" << endl;

  hJmr->Fit("f2");
  hJmr->GetFunction("f2")->SetLineColor(4);
  hJms->Draw();
  hJmr->Draw("same");
  jumSun(xBin[0],1, xBin[nXbins],1);
  float theConst1 = hJmr->GetFunction("f2")->GetParameter(0);
  float theConst2 = hJmr->GetFunction("f2")->GetParameter(1);
  drawCentrality(kSample, icent, 0.20,0.86,1,24);
  drawText(Form("JMR = %.2f - %.6f*p_{T}", theConst1, -theConst2), 0.2,0.3,4,24);
  c3->SaveAs(Form("pdfsJMR/JMR_kSample%d_cent%d.pdf",kSample,icent));  
}


void getMCJmr(int kSample, int icent, TH2D* hmc) { 
  
  TH1::SetDefaultSumw2();
  hmc->Reset();

  TString jz2;
  TString jz3;
  TString jz4;
  if ( kSample == kPbPb ) {
    jz2 = "jetSubstructure_MC_HION9_pbpb_v50_jz2_april11.root";
    jz3 = "jetSubstructure_MC_HION9_pbpb_v50_jz3_april11.root";
    jz4 = "jetSubstructure_MC_HION9_pbpb_v50_jz4_april11.root";
  }
  else if ( kSample == kPP ) {
    jz2 = "jetSubstructure_MC_HION9_pp_v50_jz2_april11.root";
    jz3 = "jetSubstructure_MC_HION9_pp_v50_jz3_april11.root";
    jz4 = "jetSubstructure_MC_HION9_pp_v50_jz4_april11.root";
  }
  
  
  TH1D* hFcalReweight;
  if ( kSample == kPbPb ) {
    TFile* fcal = new TFile("reweightFactors/FCal_HP_v_MB_weights.root");
    hFcalReweight = (TH1D*)fcal->Get("FCal_HP_v_MBOV_weights");
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

  for ( int ijz =2 ; ijz<=4 ; ijz++) {
    TTree* tr;
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
      if ( i > tr->GetEntries() * statUsed ) break;
      if (i%2==0)  continue;

      tr->GetEntry(i);

      if ( ! passEvent(myJetMc, icent, true) )        continue;
      
      double mpt =  myJetMc.recoMass / myJetMc.recoPt ;
      double recoMass = myJetMc.recoMass ;
      //      if (!( (recoMass>-100) && (recoMass<21)  ) )
      //	continue;
      
      double recoPt = myJetMc.recoPt;
      double theR = (myJetMc.recoMass/myJetMc.recoPt) / (myJetMc.genMass/myJetMc.genPt);
      
      double fcalWeight = 1.0;
      if ( kSample==kPbPb) {
	fcalWeight = hFcalReweight->GetBinContent(hFcalReweight->GetXaxis()->FindBin(myJetMc.fcalet));
        //      cout <<" fcal, weight = "<<myJetMc.fcalet<<", "<<fcalWeight<<endl;
      }
      hmc->Fill(theR, recoPt, myJetMc.weight * jzNorm * fcalWeight);
      
    }
  }
  
}



void getMeanPt(int kSample, int icent, TH1D* hMean){
  TH1::SetDefaultSumw2();
  TString fname;
  if ( kSample == kPbPb ) {
    fname = "jetSubstructure_data_HION9_v50_r4_pbpb_apr11.root";
  }
  else if ( kSample == kPP) {
    fname = "jetSubstructure_data_HION9_v50_r4_pp_apr11.root";
  }

  TH1D* htempPt = (TH1D*)hMean->Clone("htempPt");
  TH1D* htempN = (TH1D*)hMean->Clone("htempN");
  htempPt->Reset();
  htempN->Reset();

  TFile* fData = new TFile(Form("../ntuples/%s",fname.Data()));
  TTree* tr = (TTree*)fData->Get("tr");
  jetSubStr myJet;
  TBranch       *b_myJet;
  tr->SetBranchAddress("jets", &(myJet.cent), &b_myJet);

  if ( kSample == kPP )  cout << " pp " ;
  else if ( kSample == kPbPb) cout << " PbPb " ;
  cout << "data entries = " << tr->GetEntries() << endl;

  for (Int_t i= 0; i<tr->GetEntries() ; i++) {
    tr->GetEntry(i);
    if ( i > tr->GetEntries() * statUsed) break;
    if ( ! passEvent(myJet, icent, false) )       continue;

    double mpt = myJet.recoMass / myJet.recoPt;

    htempPt->Fill(myJet.recoPt, myJet.recoPt);
    htempN->Fill(myJet.recoPt);
  }

  htempPt->Divide(htempN);
  hMean->Reset();
  hMean->Add(htempPt);
}

