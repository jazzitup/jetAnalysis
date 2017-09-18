//Create a 2-D histogram from an image.
//Author: Olivier Couet

#include "commonUtility.h"
#include <vector>

void drawBasicPerf()
{
  TH1::SetDefaultSumw2();
  TFile* inf[10];
  TH3D* hresp[10];
  TH1D* hEvtCnt[10];
  double nEvent[10];
  double jzCs[10];
  double jzFiltEff[10];
  double jzWgt[10];
  TH1D* hPtRatio[20][10][10];   // rapidity bins.  16 pt bins and 2 rapidity bins and X jz bins
  TH1D* hPt[10][10];   // rapidity bins. rapidity bins and X jz bins
  
  TH1D* hScale[10]; // rapidity bins
  TH1D* hRes[10]; // rapidity bins

  float ptBin[20];

  int jzBegin = 2 ; 
  for ( int i=2 ; i<=4 ; i++) { 
    //  for ( int i=2 ; i<=4 ; i++) { 
    
    TString infName="";
    if (i==2)        {  infName ="histograms/jz2.root";  jzCs[i] = 1.7053000E+7; jzFiltEff[i] = 1.2948E-04; }
    else if (i==3)   {  infName ="histograms/jz3.root";  jzCs[i] = 5.7613E+05  ; jzFiltEff[i] = 4.2129E-05; }
    else if (i==4)   {  infName ="histograms/jz4.root";  jzCs[i] = 4.1522E+04  ; jzFiltEff[i] = 2.8563E-06; }
    
    inf[i] = new TFile(infName.Data());
    hEvtCnt[i] = (TH1D*)inf[i]->Get("EventLoop_EventCount");
    nEvent[i] = hEvtCnt[i]->GetBinContent(1);
    jzWgt[i] = jzCs[i] * jzFiltEff[i] / nEvent[i];
    hresp[i] = (TH3D*)inf[i]->Get("h_resp_cent1");

    for ( int ipt = 1; ipt<=16 ; ipt++) { 
    // 0 - 0.3  0.8 1.2 .2.1, 2.8
      hPtRatio[ipt][1][i] = (TH1D*)hresp[i]->ProjectionY(Form("hPtRatio_ipt%d_iy1_ijz%d",ipt,i),ipt,ipt,47,52);
      hPtRatio[ipt][2][i] = (TH1D*)hresp[i]->ProjectionY(Form("hPtRatio_ipt%d_iy2_ijz%d",ipt,i),ipt,ipt,53,57);
      hPtRatio[ipt][3][i] = (TH1D*)hresp[i]->ProjectionY(Form("hPtRatio_ipt%d_iy3_ijz%d",ipt,i),ipt,ipt,58,61);
      hPtRatio[ipt][4][i] = (TH1D*)hresp[i]->ProjectionY(Form("hPtRatio_ipt%d_iy4_ijz%d",ipt,i),ipt,ipt,62,70);
      hPtRatio[ipt][5][i] = (TH1D*)hresp[i]->ProjectionY(Form("hPtRatio_ipt%d_iy5_ijz%d",ipt,i),ipt,ipt,71,77);

      hPtRatio[ipt][2][i]->Add( (TH1D*)hresp[i]->ProjectionY(Form("hPtRatio_ipt%d_iy2-y_ijz%d",ipt,i),ipt,ipt,42,46) );
      hPtRatio[ipt][3][i]->Add( (TH1D*)hresp[i]->ProjectionY(Form("hPtRatio_ipt%d_iy3-y_ijz%d",ipt,i),ipt,ipt,38,41) );
      hPtRatio[ipt][4][i]->Add( (TH1D*)hresp[i]->ProjectionY(Form("hPtRatio_ipt%d_iy4-y_ijz%d",ipt,i),ipt,ipt,29,37) );
      hPtRatio[ipt][5][i]->Add( (TH1D*)hresp[i]->ProjectionY(Form("hPtRatio_ipt%d_iy5-y_ijz%d",ipt,i),ipt,ipt,22,28) );
    }
  }

  // pt binning 
  TH1D* hTempPt = (TH1D*)hresp[2]->ProjectionX("tempForPtBin");
  for ( int ipt = 1; ipt<=17 ; ipt++) { 
    ptBin[ipt] = hTempPt->GetBinLowEdge(ipt);
  }
  
  for ( int ieta = 1 ; ieta <=5 ; ieta++) { 
    for ( int ipt = 1; ipt<=16 ; ipt++) {
      hPtRatio[ipt][ieta][0] = (TH1D*)hPtRatio[ipt][ieta][2]->Clone(Form("hPtRatio_ipt%d_iy1_IntJz",ipt));
      hPtRatio[ipt][ieta][0]->Reset();
      for ( int i=2 ; i<=4 ; i++) {
	hPtRatio[ipt][ieta][0]->Add(hPtRatio[ipt][ieta][i], jzWgt[i]);
      }
    }
    
  }


  for ( int ieta = 1 ; ieta <=5 ; ieta++) {
    hScale[ieta] = (TH1D*)hTempPt->Clone(Form("hScale_ieta%d",ieta));
    hScale[ieta]->Reset();
    hRes[ieta] = (TH1D*)hTempPt->Clone(Form("hRes_ieta%d",ieta));
    hRes[ieta]->Reset();
    for ( int ipt = 1; ipt<=16 ; ipt++) { 
      hScale[ieta]->SetBinContent(ipt,  hPtRatio[ipt][ieta][0]->GetMean() ) ;
      hScale[ieta]->SetBinError  (ipt,  hPtRatio[ipt][ieta][0]->GetMeanError() ) ;
      hRes[ieta]->SetBinContent  (ipt,  hPtRatio[ipt][ieta][0]->GetRMS() ) ;
      hRes[ieta]->SetBinError    (ipt,  hPtRatio[ipt][ieta][0]->GetRMSError() ) ;
    }
  }
  
  int colorList[6] = {0,1,2,4,7,8};
  
  TCanvas* c0 = new TCanvas("c0","",1200,600);
  c0->Divide(2,1);
  c0->cd(1);
  
  TLegend *leg= new TLegend(0.45, 0.523, 0.85, 0.893);
  leg->SetHeader("pT scale");
  for ( int ieta = 1 ; ieta <=5 ; ieta++) {
    handsomeTH1(hScale[ieta],kRed+ieta-1);
    hScale[ieta]->SetXTitle("Truth p_{T} of jet (GeV)");
    hScale[ieta]->SetYTitle("Energy Scale");
    hScale[ieta]->SetAxisRange(-0.5,1,"Y");
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

  c0->cd(2);
  
  TLegend *leg1= (TLegend*)leg->Clone("leg1");
  leg1->SetHeader("pT resolution");
  for ( int ieta = 1 ; ieta <=5 ; ieta++) {
    handsomeTH1(hRes[ieta],kRed+ieta-1);
    hRes[ieta]->SetXTitle("Truth p_{T} of jet (GeV)");
    hRes[ieta]->SetYTitle("Resolution");
    hRes[ieta]->SetAxisRange(0,0.4,"Y");
    if ( ieta ==1 ) hRes[ieta]->Draw();
    else hRes[ieta]->Draw("same");
  }
  leg1->Draw();
  jumSun(0,0,ptBin[17],0);
  

  /////////////////////////////////////////////////    /////////////////////////////////////////////////    /////////////////////////////////////////////////  
  
  
  TCanvas* c1 = new TCanvas("c1","",1200,1200);
  c1->Divide(4,4);
  for ( int ipt = 1 ; ipt<=16 ; ipt++) {
    c1->cd(ipt);
    cleverRange(hPtRatio[ipt][1][0],1.5,0);
    hPtRatio[ipt][1][0]->Draw();
    float theMean =     hPtRatio[ipt][1][0]->GetMean();
    drawText(Form("%d < p_{T} < %d GeV",  (int)ptBin[ipt], (int)ptBin[ipt+1]),0.2,0.8,1,18);
    drawText(Form("Mean = %.2f", theMean),0.2, 0.7,4,18);
  }
  c1->cd(1);
  drawText("|#eta|<0.3", 0.2, 0.5,2,30);

  TCanvas* c2 = new TCanvas("c2","",1200,1200);
  c2->Divide(4,4);
  for ( int ipt = 1 ; ipt<=16 ; ipt++) {
    c2->cd(ipt);
    cleverRange(hPtRatio[ipt][2][0],1.5,0);
    hPtRatio[ipt][2][0]->Draw();
    float theMean =     hPtRatio[ipt][2][0]->GetMean();
    drawText(Form("%d < p_{T} < %d GeV",  (int)ptBin[ipt], (int)ptBin[ipt+1]),0.2,0.8,1,18);
    drawText(Form("Mean = %.2f", theMean),0.2, 0.7,4,18);
  }
  c2->cd(1);
  drawText("0.3<|#eta|<0.8", 0.2, 0.5,2,30);

  TCanvas* c3 = new TCanvas("c3","",1200,1200);
  c3->Divide(4,4);
  for ( int ipt = 1 ; ipt<=16 ; ipt++) {
    c3->cd(ipt);
    cleverRange(hPtRatio[ipt][3][0],1.5,0);
    hPtRatio[ipt][3][0]->Draw();
    float theMean =     hPtRatio[ipt][3][0]->GetMean();
    drawText(Form("%d < p_{T} < %d GeV",  (int)ptBin[ipt], (int)ptBin[ipt+1]),0.2,0.8,1,18);
    drawText(Form("Mean = %.2f", theMean),0.2, 0.7,4,18);
  }
  c3->cd(1);
  drawText("0.8<|#eta|<1.2", 0.2, 0.5,2,30);


 
  TCanvas* c4 = new TCanvas("c4","",1200,1200);
  c4->Divide(4,4);
  for ( int ipt = 1 ; ipt<=16 ; ipt++) {
    c4->cd(ipt);
    cleverRange(hPtRatio[ipt][4][0],1.5,0);
    hPtRatio[ipt][4][0]->Draw();
    float theMean =     hPtRatio[ipt][4][0]->GetMean();
    drawText(Form("%d < p_{T} < %d GeV",  (int)ptBin[ipt], (int)ptBin[ipt+1]),0.2,0.8,1,18);
    drawText(Form("Mean = %.2f", theMean),0.2, 0.7,4,18);
  }
  c4->cd(1);
  drawText("1.2<|#eta|<2.1", 0.2, 0.5,2,30);



  TCanvas* c5 = new TCanvas("c5","",1200,1200);
  c5->Divide(4,4);
  for ( int ipt = 1 ; ipt<=16 ; ipt++) {
    c5->cd(ipt);
    cleverRange(hPtRatio[ipt][5][0],1.5,0);
    hPtRatio[ipt][5][0]->Draw();
    float theMean =     hPtRatio[ipt][5][0]->GetMean();
    drawText(Form("%d < p_{T} < %d GeV",  (int)ptBin[ipt], (int)ptBin[ipt+1]),0.2,0.8,1,18);
    drawText(Form("Mean = %.2f", theMean),0.2, 0.7,4,18);
  }
  c5->cd(1);
  drawText("2.1<|#eta|<2.8", 0.2, 0.5,2,30);
  
  TFile* fout = new TFile("fout.root","recreate");

  for ( int ipt = 1 ; ipt<=16 ; ipt++) {
    hPtRatio[ipt][1][0]->Write() ; 
  }
  fout->Close();
    
  
}
