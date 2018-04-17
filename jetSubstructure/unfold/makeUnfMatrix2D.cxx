
#if !(defined(__CINT__) || defined(__CLING__)) || defined(__ACLIC__)
#include <iostream>
using std::cout;
using std::endl;

#include <TRandom3.h>
#include "TH1D.h"
#include "TH2D.h"

#include "RooUnfoldResponse.h"
#include "RooUnfoldBayes.h"
//#include "RooUnfoldSvd.h"
//#include "RooUnfoldTUnfold.h"

#include "../getSdHists.C"
//#include "../ntupleDefinition.h"
#include "../ntupleDefinition_v50.h"   
#include "../commonUtility.h"
#include "../jzWeight.h"
#endif

//==============================================================================
// Global definitions
//==============================================================================

#include "../JssUtils.h"
#include <TPaletteAxis.h>
#include "unfoldingUtil.h"


double fracStst=0001;

bool useFullMC = false;

RooUnfoldResponse* getResponse( int kSample = kPP, int icent = 0, int optX=1, int optY=2, TH2D* hTruth=0, TH2D* hReco=0, TH2D* respX=0, TH2D* respY=0, double radius =0.4,bool doReweight = true, int nSys = -1);

void makeUnfMatrix2D(int kSample = kPbPb, int optX =1, int optY=2, double radius= 0.4, bool doReweight=true, int nSys=-1) {
  
  if ( nSys < 0 )  
    cout << "Nominal mode " << endl;
  else if ( (nSys >= 0 ) && ( nSys <= 21 ) )
    cout << "pp intrinsic JES sys mode" << endl;
  else if ( (nSys >= 100 ) && ( nSys <= 106 ) )
    cout << "HI JES/JMR sys mode" << endl;
  else if ( (nSys >= 200 ) && ( nSys <= 250 ) ) 
    cout << "HI JMS/JMR sys mode" << endl;
  else {
    cout << "Invald nSys option : " << nSys << endl;
    return ;
  }
  
  TH1::SetDefaultSumw2();
  int nXbins;
  double xBin[30];
  getXbin(nXbins, xBin, optX);
  cout << " nXbins = " << nXbins << endl; 
  cout << " xBin = " << xBin[0] << ",   " << xBin[1] << ",   " <<xBin[2] << ", ..." <<endl;
  
  int nYbins ;
  double yBin[30] ;
  getYbin(nYbins, yBin, optY);
  
  TH2D* hTruthTemp = new TH2D("hTruth","",nXbins,xBin,nYbins,yBin);
  TH2D* hRecoTemp = (TH2D*)hTruthTemp->Clone("hReco");
  RooUnfoldResponse* res[7];
  
  TH2D* hTruth[7];
  TH2D* hReco[7];
  TH2D* hResultMc[7];
  
  TH2D* hMatrix[7]; // 4-d matrix unrolled to 2-d
  
  TH2D* hResX[7]; // response matrix for pT ( mass integrated)
  TH2D* hResY[7]; // response matrix for mass ( pT integrated)
  TH2D* h2dtempM = new TH2D("h2dtemp",";Truth m/p_{T};Reco m/p_{T}",100,-0.5,0.5,100,-0.5,0.5);
  

  
  for ( int i=0 ; i<=6; i++) {
    int icent = i;
    if ( !selectedCent(icent))       continue;
    if ( (kSample == kPP) && ( icent != 0 ) )      continue;

    hTruth[i] = (TH2D*)hTruthTemp->Clone(Form("%s_icent%d",hTruthTemp->GetName(),i));
    hReco[i] = (TH2D*)hRecoTemp->Clone(Form("%s_icent%d",hRecoTemp->GetName(),i));
    hTruth[i]->Reset();
    hReco[i]->Reset();
    
    hResX[i] = new TH2D(Form("hResPt_icent%d",icent), ";Truth p_{T} (GeV/c);Reco p_{T} (GeV/c)",nXbins,xBin,nXbins,xBin);
    hResY[i] = new TH2D(Form("hResM_icent%d",icent), ";Truth m/p_{T};Reco m/p_{T}",nYbins,yBin,nYbins,yBin);

    res[i] = getResponse(kSample, i, optX, optY, hTruth[i], hReco[i], hResX[i], hResY[i], radius,doReweight, nSys);

    TCanvas* c01 = new TCanvas("c01", "",600,500);
    hMatrix[i] = (TH2D*)res[i]->Hresponse();
    hMatrix[i]->SetXTitle("Bin # of reco (p_{T}, m/p_{T})");
    hMatrix[i]->SetYTitle("Bin # of truth (p_{T}, m/p_{T})");
    hMatrix[i]->SetTitle("MC Response matrix");
    c01->SetRightMargin(0.2);
    hMatrix[i]->Draw("colz");
    c01->SaveAs(Form("pdfs/correlation_2dUnf_coll%d_cent%d_radius0%d_doReweight%d.pdf",kSample,i,(int)(radius*10.),doReweight));
    TCanvas* c02 = new TCanvas("c02","",1000,500);
    c02->Divide(2,1);
    c02->cd(1);
    hResX[i]->SetNdivisions(505,"X");
    hResX[i]->Draw("colz");
    c02->cd(1)->SetRightMargin(0.2);
    gPad->SetLogz();
    c02->cd(2);
    h2dtempM->SetNdivisions(505,"X");
    h2dtempM->Draw();
    hResY[i]->Draw("colz same");
    c02->cd(2)->SetRightMargin(0.2);
    gPad->SetLogz();
    c02->SaveAs(Form("pdfs/PtMassResp_coll%d_cent%d_radius%.1f_doReweight%d.pdf",kSample,i,(float)radius,doReweight));
    
  }
  
  TString foutname ;
  if ( nSys < 0 )   
    foutname = Form("spectraFiles/unfoldingMatrix2D_coll%d_optX%d_optY%d_radius%.1f_doReweight%d.root",kSample,optX,optY,(float)radius,(int)doReweight);
  else 
    foutname = Form("spectraFiles/sys/unfoldingMatrix2D_coll%d_optX%d_optY%d_radius%.1f_doReweight%d_sys%d.root",kSample,optX,optY,(float)radius,(int)doReweight,nSys);

  TFile* fout = new TFile(foutname.Data(),"update");
  for ( int i=0 ; i<=6; i++) {
    int icent = i;
    if ( !selectedCent(icent))      continue;
    if ( (kSample == kPP) && ( icent !=0 ) )      continue;
    res[i]->Write("",TObject::kOverwrite);
    hMatrix[i]->Write("",TObject::kOverwrite);
    hReco[i]->Write("",TObject::kOverwrite);
    hTruth[i]->Write("",TObject::kOverwrite);

  }
  fout->Close();
}

RooUnfoldResponse* getResponse(int kSample,  int icent,  int optX, int optY, TH2D* hTruth, TH2D* hReco, TH2D* respX, TH2D* respY, double radius, bool doReweight, int nSys)
{
  
  TRandom3 genRandom;
  genRandom.SetSeed(200);

  
  TH1::SetDefaultSumw2();
  TString jz2;
  TString jz3;
  TString jz4;
  if ( kSample == kPbPb ) {
    if ( radius==0.4 ) {
      if ( (nSys>=0) && (nSys<200) ) {
	jz2 = jz2PbPbStringSys;
        jz3 = jz3PbPbStringSys;
        jz4 = jz4PbPbStringSys;
      }
      else { 
	jz2 = jz2PbPbString;
	jz3 = jz3PbPbString;
	jz4 = jz4PbPbString;
      }
    }
  }
  else if ( kSample == kPP ) {
    if ( radius==0.4 ) {
      if ( (nSys>=0) && (nSys<200) ) {
	jz2 = jz2PPStringSys;
        jz3 = jz3PPStringSys;
        jz4 = jz4PPStringSys;
      }
      else {
        jz2 = jz2PPString;
        jz3 = jz3PPString;
        jz4 = jz4PPString;
      }
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
  
  TFile* checkEntries = new TFile(Form("checkEntry/entries_kSample%d_icent%d_optX%d_optY%d.root",kSample,icent,optX,optY));
  TH2D* recoEntries_jz2 = (TH2D*)checkEntries->Get("reco_jz2");
  TH2D* recoEntries_jz3 = (TH2D*)checkEntries->Get("reco_jz3");
  TH2D* recoEntries_jz4 = (TH2D*)checkEntries->Get("reco_jz4");
  
  jetSubStr  myJetMc;
  TBranch  *b_myJetSubMc;

  float ptSys;
  TBranch *b_ptSys;
  TString jetSysName = getPtSysName(nSys);
  
  cout << " Setting tree branch address..." << endl;
  TFile* fjz2 = new TFile(Form("../ntuples/%s",jz2.Data()));
  TTree* tr2 = (TTree*)fjz2->Get("tr");
  tr2->SetBranchAddress("jets", &(myJetMc.cent), &b_myJetSubMc);
  if ( (nSys>=0) && (nSys<200) )
    tr2->SetBranchAddress(jetSysName.Data(), &ptSys, &b_ptSys);
  
  
  TFile* fjz3 = new TFile(Form("../ntuples/%s",jz3.Data()));
  TTree* tr3 = (TTree*)fjz3->Get("tr");
  tr3->SetBranchAddress("jets", &(myJetMc.cent), &b_myJetSubMc);
  if ( (nSys>=0) && (nSys<200) )
    tr3->SetBranchAddress(jetSysName.Data(), &ptSys, &b_ptSys);

  TFile* fjz4 = new TFile(Form("../ntuples/%s",jz4.Data()));
  TTree* tr4 = (TTree*)fjz4->Get("tr");
  tr4->SetBranchAddress("jets", &(myJetMc.cent), &b_myJetSubMc);
  if ( (nSys>=0) && (nSys<200) )  
    tr4->SetBranchAddress(jetSysName.Data(), &ptSys, &b_ptSys);

  int nXbins;
  double xBin[30];
  getXbin(nXbins, xBin, optX);

  int nYbins ;
  double yBin[30] ;
  getYbin(nYbins, yBin, optY);

  TH1D* xBinTemp = new TH1D("xBinTemp","", nXbins, xBin);
  
  
  TH1D* hJMS[15][10]; // centrality // gen pT  // gen m/pT

  //  TH1D* htempres = new TH1D("htempres","",100,-1,2.5);
  
  RooUnfoldResponse* res;
  res = new RooUnfoldResponse( hReco, hTruth );
  res->SetName(Form("responseMatrix_icent%d",icent));
    
  for ( int ijz =2 ; ijz<=4 ; ijz++) { 
    TTree* tr;
    TH2D* hRecoEntries;
    double jzNorm=0;
    if ( ijz==2)  {
      tr = tr2;   
      jzNorm = hi9EvtWgtJZ2; 
      hRecoEntries = recoEntries_jz2;
      }
    else if ( ijz==3)  {
      tr = tr3;   
      jzNorm = hi9EvtWgtJZ3; 
      hRecoEntries = recoEntries_jz3;
    }
      else if ( ijz==4)  {
	tr = tr4;   
	jzNorm = hi9EvtWgtJZ4; 
	hRecoEntries = recoEntries_jz4;
      }
      cout << "Scanning JZ"<<ijz<<" file.  Total events = " << tr->GetEntries() << endl;
      
      for (Int_t i= 0; i<tr->GetEntries() ; i++) {
	if ( i > tr->GetEntries() * fracStst ) continue;
	tr->GetEntry(i);
	
	if ( (!useFullMC) && (i%2 == 0) )
	  continue;
	
	
	//	if ( ! passEvent(myJetMc, icent, true) ) // isMC = true
	//	  continue;
	//	cout <<" ratio = " << myJetMc.recoPt / ptSys << endl;

	double recoVarX, truthVarX;
	getXvalues( recoVarX, truthVarX, myJetMc, optX);
	
	double recoVarY, truthVarY;
	getYvalues( recoVarY, truthVarY, myJetMc, optY);
	
	double relDev=0;
	if ( (nSys>=0) && (nSys<200) )   {
	  double extraPtScale = ptSys / myJetMc.recoPt ; 
	  recoVarX = recoVarX * extraPtScale ; //pt 
	  myJetMc.recoPt = ptSys;  // New pT!!! 
	  myJetMc.recoMass = myJetMc.recoMass * extraPtScale ; // new mass so that m/pT is invariant.  This step is necessary for reweighitng (pT, m/pT)
	}
	else if (nSys==200) { // JMR 
	  // smear by 20% the recoY 
	  double deviation = recoVarY - truthVarY;
	  recoVarY = recoVarY + deviation*0.2;
	  relDev = deviation / truthVarY;
	}	
	else if (nSys==210) { // JMS
	  recoVarY = recoVarY * ( 0.99 - 0.04*(recoVarX-120.)/480.);
	}
	
	if ( passEvent(myJetMc, icent, true) == false ) // true = isMC
	  continue;
	
	//	recoVarY = recoVarY * 0.96;  // systematics!!
	//	recoVarY = recoVarY * ( 0.99 - 0.05 * (recoVarX-125)/250) ;

	double fcalWeight = 1.0; 
	if ( kSample==kPbPb) {
	  //	fcalWeight = hFcalReweight->GetBinContent(hFcalReweight->GetXaxis()->FindBin(myJetMc.fcalet));
	}
	
	// Data/MC reweighting factors 
	double rewFact = 1; 
	if ( doReweight) { 
	  int rewBin = hReweight->FindBin(myJetMc.recoPt, myJetMc.recoMass/myJetMc.recoPt);
	  rewFact = hReweight->GetBinContent(rewBin);
	}
	
	//	if ( passGenEvent(myJetMc, icent) )
	//	if ( passRecoEvent(myJetMc, icent) )
	hTruth->Fill(truthVarX, truthVarY, myJetMc.weight * rewFact * jzNorm * fcalWeight);
	hReco->Fill(recoVarX, recoVarY, myJetMc.weight * rewFact * jzNorm * fcalWeight);

	res->Fill(  recoVarX, recoVarY, truthVarX, truthVarY, myJetMc.weight * rewFact * jzNorm * fcalWeight);

	respX->Fill( truthVarX, recoVarX,  myJetMc.weight * rewFact * jzNorm* fcalWeight);
	respY->Fill( truthVarY, recoVarY,  myJetMc.weight * rewFact * jzNorm* fcalWeight);
	
	//	htempres->Fill( relDev, myJetMc.weight * rewFact * jzNorm* fcalWeight);
	
	
      }
      
  }

  //  TCanvas* c00 = new TCanvas("c00","",500,500);
  //  htempres->Draw();
  //  c00->SaveAs("c00.pdf");
  
  return res;
}


#ifndef __CINT__
int main () { makeUnfMatrix2D(); return 0; }  // Main program when run stand-alone
#endif


