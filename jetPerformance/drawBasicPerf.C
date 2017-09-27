//Create a 2-D histogram from an image.

//      TH3D(Form("h_truth_jet_cent%i",i),Form("h_truth_jet_cent%i",i),jetPtBinsN, jetPtBins,etaBinsN, etaBins, phiBinsN, phiBins);

#include "commonUtility.h"
#include <vector>

struct Jes {
  TH1D* hScale[10];
  TH1D* hRes[10];
} ;


Jes drawBasicPerf(int radius=10, int cent=0)
{
  TH1::SetDefaultSumw2();
  TFile* inf[10];
  TH3D* hresp[10];
  TH3D* htruth[10];
  TH3D* hgmt[10]; // Truth match to reco
  TH1D* hEvtCnt[10];
  double nEvent[10];
  double jzCs[10];
  double jzFiltEff[10];
  double jzWgt[10];
  double ptBin[20];
  double etaBin[20];

  Jes ret;
  
  // eta binning : 
  int etaPosL[6] = {0, 51, 54, 59, 63, 72};   // 0 - 0.3 - 0.8 - 1.2 - 2.1 - 2.8
  int etaPosH[6] = {0, 53, 58, 62, 71, 78};
  int etaNegL[6] = {0, 48, 43, 39, 30, 23};   // 0 - 0.3 - 0.8 - 1.2 - 2.1 - 2.8
  int etaNegH[6] = {0, 50, 47, 42, 38, 29};
  
  TH1D* hRatioPtEtaJz[20][10][10];   // rapidity bins.  16 pt bins and 2 rapidity bins and X jz bins
  TH1D* hScale[10]; // in rapidity bins
  TH1D* hRes[10]; // in rapidity bins
  
  TH1D* hPt_EtaJz[10][10];
  TH1D* hPtGen[10];  // jz bin.   Phi rapidity integrated

  TH1D* hPtGenEtaJz[20][10];  // eta, jz bin.   gen matched to reco 
  TH1D* hPtGmtEtaJz[20][10];  // jz bin.   gen matched to reco 
  TH1D* hPtEffEtaJz[20][10];  // jz bin.   gen matched to reco 
  
  TH1D* hPtGenCum[6];  // jz bin.   Phi rapidity integrated
  
  for ( int i=2 ; i<=4 ; i++) {    // jz
    
    TString infName="";
    if ( radius == 10 ) {  
      if (i==2)        {  infName ="histograms/R10_indexCali1_noRecGen_jz2.root";  jzCs[i] = 1.7053000E+7; jzFiltEff[i] = 1.2948E-04; }
      else if (i==3)   {  infName ="histograms/R10_indexCali1_noRecGen_jz3.root";  jzCs[i] = 5.7613E+05  ; jzFiltEff[i] = 4.2129E-05; }
      else if (i==4)   {  infName ="histograms/R10_indexCali1_noRecGen_jz4.root";  jzCs[i] = 4.1522E+04  ; jzFiltEff[i] = 2.8563E-06; }
    }
    else if ( radius == 4 ) {  
      if (i==2)        {  infName ="histograms/R4_indexCali1_noRecGen_jz2.root";  jzCs[i] = 1.7053000E+7; jzFiltEff[i] = 1.2948E-04; }
      else if (i==3)   {  infName ="histograms/R4_indexCali1_noRecGen_jz3.root";  jzCs[i] = 5.7613E+05  ; jzFiltEff[i] = 4.2129E-05; }
      else if (i==4)   {  infName ="histograms/R4_indexCali1_noRecGen_jz4.root";  jzCs[i] = 4.1522E+04  ; jzFiltEff[i] = 2.8563E-06; }
    }



    
    inf[i] = new TFile(infName.Data());
    hEvtCnt[i] = (TH1D*)inf[i]->Get("EventLoop_EventCount");
    nEvent[i] = hEvtCnt[i]->GetBinContent(1);
    
    //jzWgt[i] = jzCs[i] * jzFiltEff[i] / nEvent[i];
    jzWgt[i] = jzFiltEff[i] / nEvent[i];
    //jzWgt[i] = 1 / nEvent[i];
    
    cout << "For JZ" << i<<" sample: "<< endl;
    cout << "MC crossSec = " << jzCs[i]<<endl;
    cout << "Filter eff. = " << jzFiltEff[i]<<endl;
    cout << "event count = " << nEvent[i]<<endl;
    cout << "Weight = CS. * Filter Eff.  / event Count = " << jzWgt[i] << endl;


    hresp[i] = (TH3D*)inf[i]->Get(Form("h_resp_cent%d",cent));
    
    // GEN pT spectra 
    htruth[i] = (TH3D*)inf[i]->Get(Form("h_truth_jet_cent%d",cent));
    hPtGen[i] = (TH1D*)htruth[i]->ProjectionX(Form("hPtGen_ijz%d",i));
    hgmt[i]   = (TH3D*)inf[i]->Get(Form("h_truth_jet_cent%d_matched",cent));
    
    
    for ( int ieta = 1 ; ieta <= 5 ; ieta++) { 
      for ( int ipt = 1; ipt<=16 ; ipt++) { 
 	hRatioPtEtaJz[ipt][ieta][i] =     (TH1D*)hresp[i]->ProjectionY(Form("hRatioPtEtaJz_ipt%d_ieta%dp_ijz%d",ipt,ieta,i),ipt,ipt,etaPosL[ieta], etaPosH[ieta]);
	hRatioPtEtaJz[ipt][ieta][i]->Add( (TH1D*)hresp[i]->ProjectionY(Form("hRatioPtEtaJz_ipt%d_ieat%dm_ijz%d",ipt,ieta,i),ipt,ipt,etaNegL[ieta], etaNegH[ieta]) );
      }
      
      hPtGenEtaJz[ieta][i] =     (TH1D*)htruth[i]->ProjectionX(Form("hPtGen_ieta%dp_ijz%d",ieta,i), etaPosL[ieta], etaPosH[ieta] );
      hPtGenEtaJz[ieta][i]->Add( (TH1D*)htruth[i]->ProjectionX(Form("hPtGen_ieta%dm_ijz%d",ieta,i), etaNegL[ieta], etaNegH[ieta] ) ) ;
      hPtGmtEtaJz[ieta][i] =       (TH1D*)hgmt[i]->ProjectionX(Form("hPtGmt_ieta%dp_ijz%d",ieta,i), etaPosL[ieta], etaPosH[ieta] );
      hPtGmtEtaJz[ieta][i]->Add(   (TH1D*)hgmt[i]->ProjectionX(Form("hPtGmt_ieta%dm_ijz%d",ieta,i), etaNegL[ieta], etaNegH[ieta] ) ) ;
    }
    
  }
  
  TH1D* hTempEta = (TH1D*)htruth[2]->ProjectionY("tempForEtaBin");
  for ( int ieta = 1; ieta<= hTempEta->GetNbinsX() + 1 ; ieta++) { 
    etaBin[ieta] = (double)hTempEta->GetBinLowEdge(ieta);    cout <<" "<< etaBin[ieta];
  }
  
  

  // hPtGen 
  bool flag1 = true;
  for ( int ijz = 2 ; ijz<=4; ijz++) {
    if ( flag1==1) {
      hPtGen[0] = (TH1D*)hPtGen[ijz]->Clone("hPtGen_intJz");  
      hPtGen[0]->Reset();
      
      for ( int ieta=1; ieta<=5; ieta++) { 
	hPtGenEtaJz[ieta][0] = (TH1D*)hPtGenEtaJz[ieta][ijz]->Clone("hPtGenEta_intJz");
	hPtGenEtaJz[ieta][0]->Reset();
	hPtGmtEtaJz[ieta][0] = (TH1D*)hPtGmtEtaJz[ieta][ijz]->Clone("hPtGmtEta_intJz");
	hPtGmtEtaJz[ieta][0]->Reset();
      }
      
      flag1=0;
    }
    hPtGen[0]->Add(hPtGen[ijz],jzWgt[ijz]);
    hPtGenCum[ijz] = (TH1D*)hPtGen[0]->Clone(Form("hPtGenCum_ijz%d",ijz));

    for ( int ieta=1; ieta<=5; ieta++) {
      hPtGenEtaJz[ieta][0]->Add(   hPtGenEtaJz[ieta][ijz], jzWgt[ijz] );
      hPtGmtEtaJz[ieta][0]->Add(   hPtGmtEtaJz[ieta][ijz], jzWgt[ijz] );
    }
  }
  

  TCanvas* c100 = new TCanvas("c100","",500,500);
  hPtGen[0]->SetXTitle("p_{T}^{Truth}");
  hPtGen[0]->SetYTitle("dN/dp_{T}");
  hPtGen[0]->SetAxisRange(1E-6,1E4,"Y");
  handsomeTH1(hPtGen[0],1);
  hPtGen[0]->SetTitle("");
  hPtGen[0]->Draw();
  for ( int ijz = 4 ; ijz>=2; ijz--) {
    handsomeTH1(hPtGenCum[ijz],ijz);
    hPtGenCum[ijz]->SetFillColor(ijz);
    hPtGenCum[ijz]->Draw("same hist");
  }
  hPtGen[0]->Draw("same");
  gPad->SetLogy();

  TLegend *leg100= new TLegend(0.5281124,0.7115789,0.9277108,0.9031579,NULL,"brNDC");
  easyLeg(leg100,"p_{T} of MC truth jet");
  for ( int ijz = 2 ; ijz<=4; ijz++) {
    leg100->AddEntry(hPtGenCum[ijz],Form("JZ%d",ijz));
  }
  leg100->Draw();
  
  TCanvas* c101 = new TCanvas("c101","",800,500);
  c101->Divide(3,2);
  for ( int ieta = 1 ; ieta<=5 ; ieta++) {
    c101->cd(ieta+1);
    handsomeTH1(hPtGmtEtaJz[ieta][0],1);
    hPtGmtEtaJz[ieta][0]->SetYTitle("dN/dp_{T}");
    hPtGmtEtaJz[ieta][0]->SetXTitle("p_{T} (GeV)");
    hPtGmtEtaJz[ieta][0]->SetAxisRange(1E-6,1E4,"Y");
    hPtGmtEtaJz[ieta][0]->SetTitle("");
    hPtGmtEtaJz[ieta][0]->Draw();
    hPtGenEtaJz[ieta][0]->Draw("hist same");
    gPad->SetLogy();
    
    float etaL = hTempEta->GetBinLowEdge(etaPosL[ieta]+0.0001);
    float etaH = hTempEta->GetBinLowEdge(etaPosH[ieta]+1.0001);
    drawText(Form("%.1f < |#eta| < %.1f",etaL,etaH), 0.5,0.8);
  }
  c101->cd(1) ;
  TLegend *leg101= new TLegend(0.0,0.3115789,1,0.6031579,NULL,"brNDC");
  easyLeg(leg101,"p_{T} spectra of truth jets (R=1.0)");
  leg101->AddEntry(hPtGenEtaJz[1][0],"All","pl");
  leg101->AddEntry(hPtGenEtaJz[1][0],"matched to Reco","l");
  leg101->Draw();
  

  //  return;
  
  TCanvas* c102 = new TCanvas("c102","",500,500);
  TH1D* hPtEffEta[10];
  TLegend *leg102= new TLegend(0.373494,0.2831579,0.8453815,0.5421053,NULL,"brNDC");
  easyLeg(leg102,"Jet Reco. Eff. (R=1.0)");
  for ( int ieta = 1 ; ieta<=5 ; ieta++) {
    hPtEffEta[ieta] = (TH1D*)hPtGmtEtaJz[ieta][0]->Clone(Form("hptetaeta_ieta%d",ieta));
    hPtEffEta[ieta]->Divide(hPtGenEtaJz[ieta][0]);
    handsomeTH1(hPtEffEta[ieta],kRed+ieta-1);
    hPtEffEta[ieta]->SetYTitle("dN/dp_{T}");
    hPtEffEta[ieta]->SetXTitle("p_{T} (GeV)");
    hPtEffEta[ieta]->SetTitle("");
    hPtEffEta[ieta]->SetAxisRange(0,1.5,"Y");
    if ( ieta ==1 ) hPtEffEta[ieta]->Draw();
    else hPtEffEta[ieta]->Draw("same");
    jumSun(0,1,500,1);

    float etaL = hTempEta->GetBinLowEdge(etaPosL[ieta]+0.0001);
    float etaH = hTempEta->GetBinLowEdge(etaPosH[ieta]+1.0001);
    leg102->AddEntry(hPtEffEta[ieta], Form("%.1f < |#eta| < %.1f",etaL,etaH) );
    
  }
  leg102->Draw();
  gPad->SetLogx();
  jumSun(150,0,150,1.5);
  // Fill hRatioPtEtaJz histograms
  TH1D* hTempPt = (TH1D*)hresp[2]->ProjectionX("tempForPtBin");
  cout <<" pt bin: ";
  for ( int ipt = 1; ipt<= hTempPt->GetNbinsX() + 1 ; ipt++) { 
    ptBin[ipt] = (double)hTempPt->GetBinLowEdge(ipt);     cout <<" "<< ptBin[ipt]  ; ptBin[ipt];
  }


  
  for ( int ieta = 1 ; ieta <=5 ; ieta++) { 
    for ( int ipt = 1; ipt<=16 ; ipt++) {
      hRatioPtEtaJz[ipt][ieta][0] = (TH1D*)hRatioPtEtaJz[ipt][ieta][2]->Clone(Form("hRatioPtEtaJz_ipt%d_iy1_IntJz",ipt));
      hRatioPtEtaJz[ipt][ieta][0]->Reset();
      for ( int ijz=2 ; ijz<=4 ; ijz++) {
	hRatioPtEtaJz[ipt][ieta][0]->Add(hRatioPtEtaJz[ipt][ieta][ijz], jzWgt[ijz]);
      }
    }
  }

  
  
  
  for ( int ieta = 1 ; ieta <=5 ; ieta++) {
    hScale[ieta] = (TH1D*)hTempPt->Clone(Form("hScale_ieta%d",ieta));
    hScale[ieta]->Reset();
    hRes[ieta] = (TH1D*)hTempPt->Clone(Form("hRes_ieta%d",ieta));
    hRes[ieta]->Reset();
  }
  
  int colorList[6] = {0,1,2,4,7,8};

  
  for ( int ieta = 1 ; ieta<=5 ; ieta++) { 
    TCanvas* c1 = new TCanvas(Form("c1_ieta%d",ieta),"",1200,800);
    c1->Divide(4,3);
    for ( int ipt = 3 ; ipt<=13 ; ipt++) {
      c1->cd(ipt-1);
      scaleInt(hRatioPtEtaJz[ipt][ieta][0]);
      cleverRange(hRatioPtEtaJz[ipt][ieta][0],1.5,0.0001);
      //      hRatioPtEtaJz[ipt][ieta][0]->SetAxisRange(0.00001,1,"Y");
      hRatioPtEtaJz[ipt][ieta][0]->SetAxisRange(-.5,.5,"X");
      hRatioPtEtaJz[ipt][ieta][0]->Draw();
      float mm = hRatioPtEtaJz[ipt][ieta][0]->GetMean();
      float rr = hRatioPtEtaJz[ipt][ieta][0]->GetRMS();
      TF1 *g = new TF1("g","gaus",-1,1);
      hRatioPtEtaJz[ipt][ieta][0]->Fit(g,"","", mm-rr*3, mm+rr*3);
      drawText(Form("%d < p_{T} < %d GeV",  (int)ptBin[ipt], (int)ptBin[ipt+1]),0.2,0.8,1,18);

      
      hScale[ieta]->SetBinContent(ipt,  g->GetParameter(1));
      hScale[ieta]->SetBinError(ipt,  g->GetParError(1));
      hRes[ieta]->SetBinContent(ipt,  g->GetParameter(2));
      hRes[ieta]->SetBinError(ipt,  g->GetParError(2));

      //      gPad->SetLogy();
    }
    c1->cd(1);
    float etaL = hTempEta->GetBinLowEdge(etaPosL[ieta]+0.0001);
    float etaH = hTempEta->GetBinLowEdge(etaPosH[ieta]+1.0001);
    drawText(Form("%.1f < |#eta| < %.1f",etaL,etaH), 0.2,0.5,2,30);
    c1->SaveAs(Form("energyScale_ieta%d_R%d.png",ieta,radius));
    //    jumSun(0.01,100,
  }

  
  TCanvas* c0 = new TCanvas("c0","",1200,600);
  c0->Divide(2,1);
  c0->cd(1);
  
  TLegend *leg= new TLegend(0.45, 0.523, 0.85, 0.893);
  easyLeg(leg,"p_{T} scale");
  for ( int ieta = 1 ; ieta <=5 ; ieta++) {
    handsomeTH1(hScale[ieta],kRed+ieta-1);
    hScale[ieta]->SetXTitle("Truth p_{T} of jet (GeV)");
    hScale[ieta]->SetYTitle("Energy Scale");
    hScale[ieta]->SetTitle("");
    hScale[ieta]->SetAxisRange(-0.15,0.15,"Y");
    if ( ieta ==1 ) hScale[ieta]->Draw();
    else hScale[ieta]->Draw("same");
    if ( ieta==1)    leg->AddEntry(hScale[ieta], "|eta|< 0.3");
    if ( ieta==2)    leg->AddEntry(hScale[ieta], "0.3 <|eta|< 0.8");
    if ( ieta==3)    leg->AddEntry(hScale[ieta], "0.8 <|eta|< 1.2");
    if ( ieta==4)    leg->AddEntry(hScale[ieta], "1.2 <|eta|< 2.1");
    if ( ieta==5)    leg->AddEntry(hScale[ieta], "2.1 <|eta|< 2.8");

  }
  leg->Draw();
  jumSun(0,0,ptBin[17],0);
  jumSun(150,-.15,150,.15);
  gPad->SetLogx();

  c0->cd(2);
  
  TLegend *leg1= (TLegend*)leg->Clone("leg1");
  easyLeg(leg1,"p_{T} resolution");
  for ( int ieta = 1 ; ieta <=5 ; ieta++) {
    handsomeTH1(hRes[ieta],kRed+ieta-1);
    hRes[ieta]->SetXTitle("Truth p_{T} of jet (GeV)");
    hRes[ieta]->SetYTitle("Resolution");
    hRes[ieta]->SetTitle("");
    hRes[ieta]->SetAxisRange(0,0.4,"Y");
    if ( ieta ==1 ) hRes[ieta]->Draw();
    else hRes[ieta]->Draw("same");

    TF1 *f1 = new TF1("f1","[0] + [1]/sqrt(x) + [2]/x",50,500);
    //    hRes[ieta]->Fit(f1);
  }
  leg1->Draw();
  gPad->SetLogx();
  jumSun(0,0,ptBin[17],0);
  jumSun(150,0,150,0.4);
  

  /////////////////////////////////////////////////    /////////////////////////////////////////////////    /////////////////////////////////////////////////  
  TFile* fout = new TFile("fout.root","recreate");

  for ( int ipt = 1 ; ipt<=16 ; ipt++) {
    hRatioPtEtaJz[ipt][1][0]->Write() ; 
  }
  fout->Close();

  for ( int ieta = 1 ; ieta <= 5 ; ieta++) {
    ret.hScale[ieta] = hScale[ieta];
    ret.hRes[ieta] = hRes[ieta];
  }

  return ret;
  
}
