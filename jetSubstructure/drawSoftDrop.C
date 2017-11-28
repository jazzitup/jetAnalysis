#include "getSdHists.C"
/*
  TH1D* hEffDphi[10];
  TH1D* hEffDrap[10];
*/
void drawSoftDrop(float coneR=1.0, float trkPtCut=1, float sdPtCut=1, float thetaCut =0., int numEvents =  1000000, int ptLow=150, int ptHigh=250, float version = 3.1) {
  //  TString fnamePP = "ntuples/jetSubstructure_pythia_r1.0_cs_ptCut1_sdPtCut2_jz3_v3.1.root"; // 
  //  TString fnameAA = "ntuples/jetSubstructure_himix_r1.0_cs_ptCut1_sdPtCut2_jz3_v3.1.root"; //
  //  TString prefix = "testDir";
  TString fnamePP = Form("ntuples/jetSubstructure_pythia_r%.1f_cs_ptCut%.1f_sdPtCut%.1f_jz3_v3.1.root",coneR, trkPtCut, sdPtCut, version) ;
  TString fnameAA = Form("ntuples/jetSubstructure_himix_r%.1f_cs_ptCut%.1f_sdPtCut%.1f_jz3_v3.1.root",coneR, trkPtCut, sdPtCut, version) ;
  TString prefix = Form("r%.1f_trkPtCut%.1f_sdPtCut%.1f_theta%.1f_v%.2f",coneR,trkPtCut,sdPtCut, thetaCut,version);
  cout <<" prefix = " << prefix << endl;
  TString ptCut = Form("dr>0 && genPt>%d && genPt<%d  ",ptLow, ptHigh) ;     // dr>0  : Gen Matching
  TString recoPtCut = Form("dr>0 && pt>%d && pt<%d ",ptLow, ptHigh) ; 

  sdVariable pp = getSdHists("pp", fnamePP, 0, ptCut,thetaCut, numEvents );
  
  sdVariable aa[7];
  sdVariable aaR[7];  // reco pt cut is applied
  
  for ( int icent = 0 ; icent<=6 ; icent++) {
    aa[icent] = getSdHists(Form("pbpb%d",icent),fnameAA , icent, ptCut, thetaCut, numEvents ) ;
    aaR[icent] = getSdHists(Form("pbpbR%d",icent),fnameAA , icent, recoPtCut, thetaCut, numEvents ) ;
  }
  
  // Calorimeter subjets
  TCanvas* c2=  new TCanvas("c2","",1200,450);
  makeEfficiencyCanvas(c2,4);
  c2->cd(1);
  scaleInt(pp.hGenTheta,1);
  scaleInt(pp.hRecoTheta,1);
  handsomeTH1(pp.hGenTheta,1);
  handsomeTH1(pp.hRecoTheta,1);
  pp.hGenTheta->SetXTitle("#theta between subjets");
  cleverRange(pp.hGenTheta,100,0.001);
  pp.hGenTheta->DrawCopy("hist");
  pp.hRecoTheta->DrawCopy("e same");
  gPad->SetLogy();
  TLegend *leg2 = new TLegend(0.4124564,0.5044259,0.9992266,0.7484586,NULL,"brNDC");
  easyLeg(leg2,"Full subjets");
  leg2->AddEntry(pp.hGenTheta,"Truth sub-jet","l");
  leg2->AddEntry(pp.hRecoTheta,"Calo sub-jet","pl");
  leg2->Draw();
  drawText("pp MC", 0.4, 0.8,1,20);
  drawText(Form("p_{T}^{jet}: %d - %d GeV,   |#eta^{jet}| < 1.2",ptLow,ptHigh),0.3,0.9,1,15);
  //  drawText("p_{T}^{track} > 4 GeV/c",0.35,0.7,1,15);
  
  c2->cd(5);
  TH1D* grRatio = (TH1D*)pp.hRecoTheta->Clone("grRatio");
  grRatio->Divide(pp.hGenTheta);
  grRatio->SetAxisRange(0,2.2,"Y");
  grRatio->SetYTitle("Reco/Truth");
  grRatio->SetXTitle("#theta between subjets");
  fixedFontHist(grRatio,2.5,1.5);
  grRatio->SetNdivisions(505,"X");
  grRatio->SetNdivisions(505,"Y");
  grRatio->DrawCopy();
  jumSun(0,1,1,1);
  
  
  c2->cd(2);
  scaleInt(aa[6].hGenTheta);
  scaleInt(aa[6].hRecoTheta);
  handsomeTH1(aa[6].hGenTheta,2);
  handsomeTH1(aa[6].hRecoTheta,2);
  aa[6].hGenTheta->SetXTitle("#theta between subjets");
  cleverRange(aa[6].hGenTheta,100,0.001);
  aa[6].hGenTheta->DrawCopy("hist");
  aa[6].hRecoTheta->DrawCopy("e same");
  drawText("PbPb 60-80%", 0.3, 0.8,1,20);
  //  TLegend *leg3= new TLegend(0.3062558,0.452381,0.9990587,0.7163265,NULL,"brNDC");
  //  easyLeg(leg3,"PbPb MC");
  //  leg3->AddEntry(aa[6].hGenTheta,"Truth particles","l");
  //  leg3->AddEntry(aa[6].hRecoTheta,"Reco tower","pl");
  //  leg3->Draw();
  gPad->SetLogy();
  c2->cd(6);
  grRatio = (TH1D*)aa[6].hRecoTheta->Clone("grRatio");
  grRatio->Divide(aa[6].hGenTheta);
  grRatio->SetAxisRange(0,2.2,"Y");
  grRatio->SetYTitle("Reco/Truth");
  grRatio->SetXTitle("#theta between subjets");
  fixedFontHist(grRatio,2.5,1.5);
  grRatio->SetNdivisions(505,"X");
  grRatio->SetNdivisions(505,"Y");
  grRatio->DrawCopy();
  jumSun(0,1,1,1);

  c2->cd(3);
  scaleInt(aa[3].hGenTheta);
  scaleInt(aa[3].hRecoTheta);
  handsomeTH1(aa[3].hGenTheta,2,1,20);
  handsomeTH1(aa[3].hRecoTheta,2,1,20);
  aa[3].hRecoTheta->SetXTitle("#theta between subjets");
  cleverRange(aa[3].hRecoTheta,100,0.001);
  aa[3].hRecoTheta->DrawCopy("e");
  aa[3].hGenTheta->DrawCopy("same hist");
  drawText("30-40%", 0.3, 0.8,1,20);
  gPad->SetLogy();
  c2->cd(7);
  grRatio = (TH1D*)aa[3].hRecoTheta->Clone("grRatio");
  grRatio->Divide(aa[3].hGenTheta);
  grRatio->SetAxisRange(0,2.2,"Y");
  grRatio->SetYTitle("Reco/Truth");
  grRatio->SetXTitle("#theta between subjets");
  fixedFontHist(grRatio,2.5,1.5);
  grRatio->SetNdivisions(505,"X");
  grRatio->SetNdivisions(505,"Y");
  grRatio->DrawCopy();
  jumSun(0,1,1,1);

  c2->cd(4);
  scaleInt(aa[0].hGenTheta);
  scaleInt(aa[0].hRecoTheta);
  handsomeTH1(aa[0].hGenTheta,2);
  handsomeTH1(aa[0].hRecoTheta,2);
  aa[0].hRecoTheta->SetXTitle("#theta between subjets");
  cleverRange(aa[0].hRecoTheta,100,0.001);
  aa[0].hRecoTheta->DrawCopy("e");
  aa[0].hGenTheta->DrawCopy("same hist");
  drawText("0-10%", 0.3, 0.8,1,20);
  gPad->SetLogy();
  c2->cd(8);
  grRatio = (TH1D*)aa[0].hRecoTheta->Clone("grRatio");
  grRatio->Divide(aa[0].hGenTheta);
  grRatio->SetAxisRange(0,2.2,"Y");
  grRatio->SetYTitle("Reco/Truth");
  grRatio->SetXTitle("#theta between subjets");
  fixedFontHist(grRatio,2.5,1.5);
  grRatio->SetNdivisions(505,"X");
  grRatio->SetNdivisions(505,"Y");
  grRatio->DrawCopy();
  jumSun(0,1,1,1);


  // theta vs charged theta
  TCanvas* c3=  new TCanvas("c3","",1200,450);
  makeEfficiencyCanvas(c3,4);
  c3->cd(1);
  handsomeTH1(pp.hGenChTheta,1);
  handsomeTH1(pp.hRecoChTheta,1);
  pp.hGenChTheta->SetXTitle("#theta between subjets");
  scaleInt(pp.hGenChTheta);
  scaleInt(pp.hRecoChTheta);
  cleverRange(pp.hGenChTheta,100,0.0001);
  pp.hGenChTheta->DrawCopy("hist");
  pp.hRecoChTheta->DrawCopy("e same");
  gPad->SetLogy();

  TLegend *leg4= new TLegend(0.5555711,0.05819241,0.9992266,0.3022251,NULL,"brNDC");
  easyLeg(leg4,"Charged sub-jet");
  leg4->AddEntry(pp.hGenChTheta,"Truth","l");
  leg4->AddEntry(pp.hGenChTheta,"Reco");
  leg4->Draw();
  drawText(Form("p_{T}^{jet}: %d - %d GeV,   |#eta^{jet}| < 1.2",ptLow,ptHigh),0.35,0.8,1,15);
  drawText("pp MC",0.35,0.7,1,15);  
  //drawText("p_{T}^{track} > 4 GeV/c",0.35,0.7,1,15);

  c3->cd(5);
  TH1D* ppRatio = (TH1D*)pp.hRecoChTheta->Clone("ppRatio");
  ppRatio->Divide(pp.hGenChTheta);
  ppRatio->SetAxisRange(0,2.2,"Y");
  ppRatio->SetYTitle("Reco/Truth");
  ppRatio->SetXTitle("#theta between subjets");
  fixedFontHist(ppRatio,2.5,1.5);
  ppRatio->SetNdivisions(505,"X");
  ppRatio->SetNdivisions(505,"Y");
  ppRatio->DrawCopy();
  jumSun(0,1,1,1);
  
  c3->cd(2);
  handsomeTH1(aa[6].hGenChTheta,2,1,24);
  handsomeTH1(aa[6].hRecoChTheta,2,1,24);
  aa[6].hGenChTheta->SetXTitle("#theta between subjets");
  //  cleverRange(aa[6].hGenChTheta);
  scaleInt(aa[6].hGenChTheta);
  scaleInt(aa[6].hRecoChTheta);
  cleverRange(aa[6].hGenChTheta,100,0.0001);
  aa[6].hGenChTheta->DrawCopy("hist");
  aa[6].hRecoChTheta->DrawCopy("e same");
  drawText("PbPb MC 60-80%", 0.3, 0.8,1,20);
  //  TLegend *leg31= new TLegend(0.3062558,0.452381,0.9990587,0.7163265,NULL,"brNDC");
  //  easyLeg(leg31,"PbPb MC, p_{T}^{constituent} > 4 GeV/c");
  //  leg31->AddEntry(aa[6].hGenChTheta, "Truth Charged Subjet");
  //  leg31->AddEntry(aa[6].hRecoChTheta, "Reco Charged Subjet");
  //  leg31->Draw();
  gPad->SetLogy();

  c3->cd(6);
  TH1D* rat = (TH1D*)aa[6].hRecoChTheta->Clone("rat");
  rat->Divide(aa[6].hGenChTheta);
  rat->SetAxisRange(0,2.3,"Y");
  rat->SetYTitle("Reco/Truth");
  fixedFontHist(rat,2.5,1.5);
  rat->SetNdivisions(505,"X");
  rat->SetNdivisions(505,"Y");
  rat->DrawCopy();
  jumSun(0,1,1,1);

  c3->cd(3);
  handsomeTH1(aa[3].hGenChTheta,2,1,20);
  handsomeTH1(aa[3].hRecoChTheta,2,1,20);
  aa[3].hGenChTheta->SetXTitle("#theta between subjets");
  //  cleverRange(aa[3].hGenChTheta);
  scaleInt(aa[3].hGenChTheta);
  scaleInt(aa[3].hRecoChTheta);
  cleverRange(aa[3].hGenChTheta,100,0.0001);
  aa[3].hGenChTheta->DrawCopy("hist");
  aa[3].hRecoChTheta->DrawCopy("e same");
  drawText("30-40%", 0.3, 0.8,1,20);
  gPad->SetLogy();
  c3->cd(7);
  rat = (TH1D*)aa[3].hRecoChTheta->Clone("rat");
  rat->Divide(aa[3].hGenChTheta);
  rat->SetAxisRange(0,2.3,"Y");
  rat->SetYTitle("Reco/Truth");
  fixedFontHist(rat,2.5,1.5);
  rat->SetNdivisions(505,"X");
  rat->SetNdivisions(505,"Y");
  rat->DrawCopy();
  jumSun(0,1,1,1);

  c3->cd(4);
  handsomeTH1(aa[0].hGenChTheta,2);
  handsomeTH1(aa[0].hRecoChTheta,2);
  aa[0].hGenChTheta->SetXTitle("#theta between subjets");
  //  cleverRange(aa[0].hGenChTheta);
  scaleInt(aa[0].hGenChTheta);
  scaleInt(aa[0].hRecoChTheta);
  cleverRange(aa[0].hGenChTheta,100,0.0001);
  aa[0].hGenChTheta->DrawCopy("hist");
  aa[0].hRecoChTheta->DrawCopy("e same");
  drawText("0-10%", 0.3, 0.8,1,20);
  gPad->SetLogy();

  c3->cd(8);
  rat = (TH1D*)aa[0].hRecoChTheta->Clone("rat");
  rat->Divide(aa[0].hGenChTheta);
  rat->SetAxisRange(0,2.3,"Y");
  rat->SetYTitle("Reco/Truth");
  fixedFontHist(rat,2.5,1.5);
  rat->SetNdivisions(505,"X");
  rat->SetNdivisions(505,"Y");
  rat->DrawCopy();
  jumSun(0,1,1,1);

  
  // theta vs ch theta
  // theta vs charged theta
  TCanvas* c4=  new TCanvas("c4","",700,450);
  makeEfficiencyCanvas(c4,1);
  c4->cd(1);
  //  c4->Divide(1,2);
  /*  TPad *pad1 = new TPad("pad1", "The pad 80% of the height",0.0,0.2,1.0,1.0);
  TPad *pad2 = new TPad("pad2", "The pad 20% of the height",0.0,0.0,1.0,0.2);
  c4->cd();
  pad1->Draw();
  pad2->Draw();
  pad1->cd();*/
  scaleInt(pp.hGenChTheta);
  scaleInt(pp.hGenTheta);
  cleverRange(pp.hGenChTheta,100,0.0001);
  handsomeTH1(pp.hGenChTheta,1);
  handsomeTH1(pp.hGenTheta,1);
  pp.hGenTheta->DrawCopy("hist");
  pp.hGenChTheta->DrawCopy("e same");
  gPad->SetLogy();
  TLegend* leg5 = new TLegend(0.5036546,0.3894737,0.9,0.6347368,NULL,"brNDC");
  easyLeg(leg5,"pp (pT > 1 GeV)");
  leg5->AddEntry(pp.hGenTheta, "Ntrl + Cha'd particles, w/o p_{T} cut","l");
  leg5->AddEntry(pp.hGenChTheta, "Charged only, w/ p_{T} cut");
  leg5->Draw();
  drawText(Form("p_{T}^{jet}: %d - %d GeV,   |#eta^{jet}| < 1.2",ptLow,ptHigh),0.5,0.8,1,15);
  //  drawText("constituent p_{T} > 4 GeV/c",0.5,0.7,1,15);

  c4->cd(2);
  ppRatio = (TH1D*)pp.hGenChTheta->Clone("ppRatio");
  ppRatio->Divide(pp.hGenTheta);
  ppRatio->SetAxisRange(0,2.3,"Y");
  ppRatio->SetYTitle("Ratio");
  fixedFontHist(ppRatio,2.5,1.5);
  ppRatio->SetNdivisions(505,"X");
  ppRatio->SetNdivisions(505,"Y");
  ppRatio->DrawCopy();
  jumSun(0,1,1,1);  
  
  
  // Bin migration effect?

  TCanvas* c5=  new TCanvas("c5","",1000,450);
  makeEfficiencyCanvas(c5,3);

  c5->cd(1);
  handsomeTH1(aa[6].hRecoChTheta,2);
  handsomeTH1(aaR[6].hRecoChTheta,2);
  aa[6].hRecoChTheta->SetXTitle("#theta of Reco'ed Ch. subjets");
  scaleInt(aa[6].hRecoChTheta);
  scaleInt(aaR[6].hRecoChTheta);
  
  fixedFontHist(aa[6].hRecoChTheta,2.5,1.5);
  aa[6].hRecoChTheta->SetNdivisions(505,"X");
  aa[6].hRecoChTheta->SetNdivisions(505,"Y");

  aa[6].hRecoChTheta->DrawCopy("hist");
  aaR[6].hRecoChTheta->DrawCopy("same");
  drawText("60-80%", 0.3, 0.8,1,25);
  TLegend *leg30= new TLegend(0.4062558,0.402381,0.9990587,0.6163265,NULL,"brNDC");
  easyLeg(leg30,Form("%d < p_{T}^{jet} < %d GeV/c cut by",ptLow, ptHigh));
  leg30->AddEntry(aa[6].hRecoChTheta,"Truth","l");
  leg30->AddEntry(aaR[6].hRecoChTheta,"Reco Jet");
  leg30->Draw();
  gPad->SetLogy();

  c5->cd(4);
  rat = (TH1D*)aaR[6].hRecoChTheta->Clone("rat");
  rat->Divide(aa[6].hRecoChTheta);
  rat->SetAxisRange(0,2.2,"Y");
  rat->SetYTitle("ratio");
  fixedFontHist(rat,2.5,1.5);
  rat->SetNdivisions(505,"X");
  rat->SetNdivisions(505,"Y");
  rat->DrawCopy();

  jumSun(0,1,1,1);

  c5->cd(2);
  handsomeTH1(aa[3].hRecoChTheta,2);
  handsomeTH1(aaR[3].hRecoChTheta,2);
  aa[3].hRecoChTheta->SetXTitle("#theta between subjets");
  scaleInt(aa[3].hRecoChTheta);
  scaleInt(aaR[3].hRecoChTheta);
  aa[3].hRecoChTheta->DrawCopy("hist");
  aaR[3].hRecoChTheta->DrawCopy("same");
  drawText("30-40%", 0.3, 0.8,1,25);
  gPad->SetLogy();

  c5->cd(5);
  rat = (TH1D*)aaR[3].hRecoChTheta->Clone("rat");
  rat->Divide(aa[3].hRecoChTheta);
  rat->SetAxisRange(0,2.3,"Y");
  rat->SetYTitle("[Reco cut] / [Truth cut]");
  fixedFontHist(rat,2.5,1.5);
  rat->SetNdivisions(505,"X");
  rat->SetNdivisions(505,"Y");
  rat->DrawCopy();
  rat->DrawCopy();
  jumSun(0,1,1,1);


  c5->cd(3);
  handsomeTH1(aa[0].hRecoChTheta,2);
  handsomeTH1(aaR[0].hRecoChTheta,2);
  aa[0].hRecoChTheta->SetXTitle("#theta between subjets");
  scaleInt(aa[0].hRecoChTheta);
  scaleInt(aaR[0].hRecoChTheta);
  aa[0].hRecoChTheta->DrawCopy("hist");
  aaR[0].hRecoChTheta->DrawCopy("same");
  drawText("0-10%", 0.3, 0.8,1,25);
  gPad->SetLogy();

  c5->cd(6);
  rat = (TH1D*)aaR[0].hRecoChTheta->Clone("rat");
  rat->Divide(aa[0].hRecoChTheta);
  rat->SetAxisRange(0,2.3,"Y");
  rat->SetYTitle("[Reco cut] / [Truth cut]");
  fixedFontHist(rat,2.5,1.5);
  rat->SetNdivisions(505,"X");
  rat->SetNdivisions(505,"Y");
  rat->DrawCopy();
  rat->DrawCopy();
  jumSun(0,1,1,1);
  


  // z_{g}
  TCanvas* c6=  new TCanvas("c6","",1200,450);
  makeEfficiencyCanvas(c6,4);
  c6->cd(1);
  handsomeTH1(pp.hGenChZg,1);
  handsomeTH1(pp.hRecoChZg,1);
  pp.hGenChZg->SetXTitle("z_{g} = min(p_{T}^{1},p_{T}^{2})/(p_{T}^{1}+p_{T}^{2})");
  cleverRange(pp.hGenChZg,1.6);
  pp.hGenChZg->SetNdivisions(505);
  pp.hGenChZg->DrawCopy("hist");
  pp.hRecoChZg->DrawCopy("e same");

  TLegend *leg6 = new TLegend(0.600721,0.44639532,0.9972388,0.9716563,NULL,"brNDC");
  easyLeg(leg6,"Charged subjets");
  leg6->AddEntry(pp.hGenChZg,"Truth Tracks","l");
  leg6->AddEntry(pp.hRecoChZg,"Reco Tracks","pl");
  leg6->Draw();
  drawText(Form("p_{T}^{jet}: %d - %d GeV,   |#eta^{jet}| < 1.2",ptLow,ptHigh),0.35,0.87,1,15);
  //  drawText("p_{T}^{track} > 8 GeV",0.35,0.83,1,15);
  drawText(Form("#Delta#theta > %.1f",(float)thetaCut),0.35,0.74,2,20);
  
  c6->cd(5);
  TH1D* ratioChZg = (TH1D*)pp.hRecoChZg->Clone("ratioChZg");
  ratioChZg->Divide(pp.hGenChZg);
  ratioChZg->SetAxisRange(0,2.3,"Y");
  ratioChZg->SetXTitle("Charged z_{g}");
  ratioChZg->SetYTitle("Reco/Truth");
  fixedFontHist(ratioChZg,2.5,1.5);
  ratioChZg->SetNdivisions(505,"X");
  ratioChZg->SetNdivisions(505,"Y");
  ratioChZg->DrawCopy();
  jumSun(0,1,0.6,1);
  

  c6->cd(2);
  handsomeTH1(aa[6].hGenChZg,2);
  handsomeTH1(aa[6].hRecoChZg,2);
  aa[6].hGenChZg->SetXTitle("z_{g} = min(p_{T}^{1},p_{T}^{2})/(p_{T}^{1}+p_{T}^{2})");
  cleverRange(aa[6].hGenChZg,1.6);
  aa[6].hGenChZg->SetNdivisions(505);
  aa[6].hGenChZg->DrawCopy("hist");
  aa[6].hRecoChZg->DrawCopy("e same");
  drawText("60-80%", 0.6, 0.8,1,25);
  //  leg6->Draw();

  c6->cd(6);
  ratioChZg = (TH1D*)aa[6].hRecoChZg->Clone("ratioChZg");
  ratioChZg->Divide(aa[6].hGenChZg);
  ratioChZg->SetAxisRange(0,2.3,"Y");
  ratioChZg->SetXTitle("Charged z_{g}");
  fixedFontHist(ratioChZg,2.5,1.5);
  ratioChZg->SetNdivisions(505,"X");
  ratioChZg->SetNdivisions(505,"Y");
  ratioChZg->DrawCopy();
  jumSun(0,1,0.6,1);

  c6->cd(3);
  handsomeTH1(aa[3].hGenChZg,2);
  handsomeTH1(aa[3].hRecoChZg,2);
  aa[3].hGenChZg->SetXTitle("z_{g} = min(p_{T}^{1},p_{T}^{2})/(p_{T}^{1}+p_{T}^{2})");
  cleverRange(aa[3].hGenChZg,1.6);
  aa[3].hGenChZg->SetNdivisions(505);
  aa[3].hGenChZg->DrawCopy("hist");
  aa[3].hRecoChZg->DrawCopy("e same");
  drawText("30-40%", 0.6, 0.8,1,25);

  c6->cd(7);
  ratioChZg = (TH1D*)aa[3].hRecoChZg->Clone("ratioChZg");
  ratioChZg->Divide(aa[3].hGenChZg);
  ratioChZg->SetAxisRange(0,2.3,"Y");
  ratioChZg->SetXTitle("Charged z_{g}");
  fixedFontHist(ratioChZg,2.5,1.5);
  ratioChZg->SetNdivisions(505,"X");
  ratioChZg->SetNdivisions(505,"Y");
  ratioChZg->DrawCopy();
  jumSun(0,1,0.6,1);

  c6->cd(4);
  handsomeTH1(aa[0].hGenChZg,2);
  handsomeTH1(aa[0].hRecoChZg,2);
  aa[0].hGenChZg->SetXTitle("z_{g} = min(p_{T}^{1},p_{T}^{2})/(p_{T}^{1}+p_{T}^{2})");
  cleverRange(aa[0].hGenChZg,1.6);
  aa[0].hGenChZg->SetNdivisions(505);
  aa[0].hGenChZg->DrawCopy("hist");
  aa[0].hRecoChZg->DrawCopy("e same");
  drawText("0-10%", 0.6, 0.8,1,25);

  c6->cd(8);
  ratioChZg = (TH1D*)aa[0].hRecoChZg->Clone("ratioChZg");
  ratioChZg->Divide(aa[0].hGenChZg);
  ratioChZg->SetAxisRange(0,2.3,"Y");
  ratioChZg->SetXTitle("Charged z_{g}");
  fixedFontHist(ratioChZg,2.5,1.5);
  ratioChZg->SetNdivisions(505,"X");
  ratioChZg->SetNdivisions(505,"Y");
  ratioChZg->DrawCopy();
  jumSun(0,1,0.6,1);




  ///////////////////////  
  // Mass distribution //
  ///////////////////////
  TCanvas* c7=  new TCanvas("c7","",1200,450);
  makeEfficiencyCanvas(c7,4);
  c7->cd(1);
  handsomeTH1(pp.hGenChSdM,1);
  handsomeTH1(pp.hRecoChSdM,1);
  pp.hGenChSdM->SetXTitle("SoftDrop Ch'd Mass (GeV)");
  scaleInt(pp.hGenChSdM);
  scaleInt(pp.hRecoChSdM);
  cleverRange(pp.hGenChSdM,10,0.0001);
  pp.hGenChSdM->DrawCopy("hist");
  pp.hRecoChSdM->DrawCopy("e same");

  TLegend *leg7= new TLegend(0.556546,0.3894737,1,0.7347368,NULL,"brNDC");
  easyLeg(leg7,"Chg'd sub-jet");
  leg7->AddEntry(pp.hGenChSdM, "Truth chg'd particles","l");
  leg7->AddEntry(pp.hRecoChSdM, "Reco tracks");
  leg7->Draw();
  drawText("pp (pT>1 GeV )", 0.35, 0.9, 1, 20);
  drawText(Form("p_{T}^{jet}: %d - %d GeV,   |#eta^{jet}| < 1.2",ptLow,ptHigh),0.35,0.8,1,15);
  //  drawText("p_{T}^{track} > 4 GeV/c",0.35,0.7,1,15);
  gPad->SetLogy();
  c7->cd(5);
  TH1D* ppRatioChM = (TH1D*)pp.hRecoChSdM->Clone("ppRatioChM");
  ppRatioChM->Divide(pp.hGenChSdM);
  ppRatioChM->SetAxisRange(0,2.3,"Y");
  ppRatioChM->SetXTitle("Charged SoftDrop Mass (GeV)");
  ppRatioChM->SetYTitle("Reco/Truth");
  fixedFontHist(ppRatioChM,2.5,1.5);
  ppRatioChM->SetNdivisions(505,"X");
  ppRatioChM->SetNdivisions(505,"Y");
  ppRatioChM->DrawCopy();
  jumSun(0,1,100,1);
  
  //  TCanvas* c7=  new TCanvas("c7","",1000,450);
  //  makeEfficiencyCanvas(c7,3);
  c7->cd(2);
  handsomeTH1(aa[6].hGenChSdM,2,1,24);
  handsomeTH1(aa[6].hRecoChSdM,2,1,24);
  aa[6].hGenChSdM->SetXTitle("SoftDrop Ch'ed Mass (GeV)");
  cleverRange(aa[6].hGenChSdM,100,1000);
  scaleInt(aa[6].hGenChSdM);
  scaleInt(aa[6].hRecoChSdM);
  cleverRange(aa[6].hGenChSdM,10,0.0001);
  aa[6].hGenChSdM->DrawCopy("hist");
  aa[6].hRecoChSdM->DrawCopy("e same");
  drawText("PbPb MC 60-80%", 0.3, 0.8,1,20);
  //  TLegend *leg71= new TLegend(0.3062558,0.452381,0.9990587,0.7163265,NULL,"brNDC");
  //  easyLeg(leg71,"PbPb MC, p_{T}^{constituent} > 4 GeV/c");
  //  leg71->AddEntry(aa[6].hGenChSdM, "Truth chg'd particles","l");
  //  leg71->AddEntry(aa[6].hRecoChSdM, "Reco tracks");
  //  leg71->Draw();
    gPad->SetLogy();
  
  c7->cd(6);
  TH1D* ratChM = (TH1D*)aa[6].hRecoChSdM->Clone("ratChM");
  ratChM->Divide(aa[6].hGenChSdM);
  ratChM->SetAxisRange(0,2.3,"Y");
  ratChM->SetYTitle("Reco/Truth");
  fixedFontHist(ratChM,2.5,1.5);
  ratChM->SetNdivisions(505,"X");
  ratChM->SetNdivisions(505,"Y");
  ratChM->DrawCopy();
  jumSun(0,1,100,1);

  c7->cd(3);
  handsomeTH1(aa[3].hGenChSdM,2,1,20);
  handsomeTH1(aa[3].hRecoChSdM,2,1,20);
  aa[3].hGenChSdM->SetXTitle("SoftDrop Mass (GeV)");
  cleverRange(aa[3].hGenChSdM,100,1000);
  scaleInt(aa[3].hGenChSdM);
  scaleInt(aa[3].hRecoChSdM);
  cleverRange(aa[3].hGenChSdM,10,0.0001);
  aa[3].hGenChSdM->DrawCopy("hist");
  aa[3].hRecoChSdM->DrawCopy("e same");
  drawText("30-40%", 0.3, 0.8,1,20);
  gPad->SetLogy();

  c7->cd(7);
  ratChM = (TH1D*)aa[3].hRecoChSdM->Clone("ratChM");
  ratChM->Divide(aa[3].hGenChSdM);
  ratChM->SetAxisRange(0,2.3,"Y");
  ratChM->SetYTitle("Reco/Truth");
  fixedFontHist(ratChM,2.5,1.5);
  ratChM->SetNdivisions(505,"X");
  ratChM->SetNdivisions(505,"Y");
  ratChM->DrawCopy();
  jumSun(0,1,100,1);


  c7->cd(4);
  handsomeTH1(aa[0].hGenChSdM,2);
  handsomeTH1(aa[0].hRecoChSdM,2);
  aa[0].hGenChSdM->SetXTitle("SoftDrop Mass (GeV)");
  cleverRange(aa[0].hGenChSdM,100,1000);
  scaleInt(aa[0].hGenChSdM);
  scaleInt(aa[0].hRecoChSdM);
  cleverRange(aa[0].hGenChSdM,10,0.0001);
  aa[0].hGenChSdM->DrawCopy("hist");
  aa[0].hRecoChSdM->DrawCopy("e same");
  drawText("0-10%", 0.3, 0.8,1,20);
  drawText(Form("#Delta#theta > %.1f",(float)thetaCut),0.35,0.65,2,20);
  gPad->SetLogy();

  c7->cd(8);
  ratChM = (TH1D*)aa[0].hRecoChSdM->Clone("ratChM");
  ratChM->Divide(aa[0].hGenChSdM);
  ratChM->SetAxisRange(0,2.3,"Y");
  ratChM->SetYTitle("Reco/Truth");
  fixedFontHist(ratChM,2.5,1.5);
  ratChM->SetNdivisions(505,"X");
  ratChM->SetNdivisions(505,"Y");
  ratChM->DrawCopy();
  jumSun(0,1,100,1);
  

  TCanvas* c8=  new TCanvas("c8","",1200,450);
  makeEfficiencyCanvas(c8,4);
  c8->cd(1);
  handsomeTH1(pp.hGenSdM,1);
  handsomeTH1(pp.hRecoSdM,1);
  pp.hGenSdM->SetXTitle("SoftDrop Mass (GeV)");
  scaleInt(pp.hGenSdM);
  scaleInt(pp.hRecoSdM);
  cleverRange(pp.hGenSdM,100,0.0001);
  pp.hGenSdM->DrawCopy("hist");
  pp.hRecoSdM->DrawCopy("e same");
  gPad->SetLogy();

  TLegend *leg8= new TLegend(0.556546,0.5894737,1,0.8307368,NULL,"brNDC");
  easyLeg(leg8,"Full subjet");
  leg8->AddEntry(pp.hGenSdM, "Truth","l"); 
  leg8->AddEntry(pp.hRecoSdM, "Calo Jet");
  leg8->Draw();
  drawText(Form("p_{T}^{jet}: %d - %d GeV,   |#eta^{jet}| < 1.2",ptLow,ptHigh),0.55,0.9,1,15);
  //  drawText("p_{T}^{track} > 4 GeV/c",0.55,0.7,1,15);

  c8->cd(5);
  TH1D* ppRatioM = (TH1D*)pp.hRecoSdM->Clone("ppRatioM");
  ppRatioM->Divide(pp.hGenSdM);
  ppRatioM->SetAxisRange(0,2.3,"Y");
  ppRatioM->SetXTitle("Soft Drop Mass (GeV)");
  ppRatioM->SetYTitle("Reco/Truth");
  fixedFontHist(ppRatioM,2.5,1.5);
  ppRatioM->SetNdivisions(505,"X");
  ppRatioM->SetNdivisions(505,"Y");
  ppRatioM->DrawCopy();
  jumSun(0,1,100,1);
  
  c8->cd(2);
  handsomeTH1(aa[6].hGenSdM,2,1,24);
  handsomeTH1(aa[6].hRecoSdM,2,1,24);
  aa[6].hGenSdM->SetXTitle("SoftDrop Mass (GeV)");
  cleverRange(aa[6].hGenSdM,100,10000);
  scaleInt(aa[6].hGenSdM);
  scaleInt(aa[6].hRecoSdM);
  cleverRange(aa[6].hGenSdM,100,0.0001);
  aa[6].hGenSdM->DrawCopy("hist");
  aa[6].hRecoSdM->DrawCopy("e same");
  gPad->SetLogy();
  drawText("PbPb 60-80%", 0.3, 0.8,1,25);
  
  c8->cd(6);
  TH1D* ratM = (TH1D*)aa[6].hRecoSdM->Clone("ratM");
  ratM->Divide(aa[6].hGenSdM);
  ratM->SetAxisRange(0,2.3,"Y");
  ratM->SetXTitle("SoftDrop Mass (GeV)");
  ratM->SetYTitle("Reco/Truth");
  fixedFontHist(ratM,2.5,1.5);
  ratM->SetNdivisions(505,"X");
  ratM->SetNdivisions(505,"Y");
  ratM->DrawCopy();
  jumSun(0,1,100,1);

  c8->cd(3);
  handsomeTH1(aa[3].hGenSdM,2,1,20);
  handsomeTH1(aa[3].hRecoSdM,2,1,20);
  aa[3].hGenSdM->SetXTitle("SoftDrop Mass (GeV)");
  cleverRange(aa[3].hGenSdM,100,10000);
  scaleInt(aa[3].hGenSdM);
  scaleInt(aa[3].hRecoSdM);
  cleverRange(aa[3].hGenSdM,100,0.0001);
  aa[3].hGenSdM->DrawCopy("hist");
  aa[3].hRecoSdM->DrawCopy("e same");
  drawText("30-40%", 0.3, 0.8,1,25);
  gPad->SetLogy();
  c8->cd(7);
  ratM = (TH1D*)aa[3].hRecoSdM->Clone("ratM");
  ratM->Divide(aa[3].hGenSdM);
  ratM->SetAxisRange(0,2.3,"Y");
  ratM->SetXTitle("SoftDrop Mass (GeV)");
  ratM->SetYTitle("Reco/Truth");
  fixedFontHist(ratM,2.5,1.5);
  ratM->SetNdivisions(505,"X");
  ratM->SetNdivisions(505,"Y");
  ratM->DrawCopy();
  jumSun(0,1,100,1);

  
  c8->cd(4);
  handsomeTH1(aa[0].hGenSdM,2);
  handsomeTH1(aa[0].hRecoSdM,2);
  aa[0].hGenSdM->SetXTitle("SoftDrop Mass (GeV)");
  cleverRange(aa[0].hGenSdM,100,10000);
  scaleInt(aa[0].hGenSdM);
  scaleInt(aa[0].hRecoSdM);
  cleverRange(aa[0].hGenSdM,100,0.0001);
  aa[0].hGenSdM->DrawCopy("hist");
  aa[0].hRecoSdM->DrawCopy("e same");
  gPad->SetLogy();
  drawText("0-10%", 0.3, 0.8,1,25);
  c8->cd(8);
  ratM = (TH1D*)aa[0].hRecoSdM->Clone("ratM");
  ratM->Divide(aa[0].hGenSdM);
  ratM->SetAxisRange(0,2.3,"Y");
  ratM->SetXTitle("SoftDrop Mass (GeV)");
  ratM->SetYTitle("Reco/Truth");
  fixedFontHist(ratM,2.5,1.5);
  ratM->SetNdivisions(505,"X");
  ratM->SetNdivisions(505,"Y");
  ratM->DrawCopy();
  jumSun(0,1,100,1);

  

  TCanvas* c9=  new TCanvas("c9","",1200,450);
  makeEfficiencyCanvas(c9,4);
  c9->cd(1);
  handsomeTH1(pp.hGenZg,1);
  handsomeTH1(pp.hRecoZg,1);
  pp.hGenZg->SetXTitle("z_{g} = min(p_{T}^{1},p_{T}^{2})/(p_{T}^{1}+p_{T}^{2})");
  cleverRange(pp.hGenZg,1.8);
  pp.hGenZg->SetNdivisions(505);
  pp.hGenZg->DrawCopy("hist");
  pp.hRecoZg->DrawCopy("e same");

  TLegend *leg9 = new TLegend(0.5011875,0.4481107,0.9992266,0.6733716,NULL,"brNDC");
  easyLeg(leg9,"Full subjets");
  leg9->AddEntry(pp.hGenZg,"Truth Jet","l");
  leg9->AddEntry(pp.hRecoZg,"Calo Jet","pl");
  leg9->Draw();
  drawText(Form("p_{T}^{jet}: %d - %d GeV,   |#eta^{jet}| < 1.2",ptLow,ptHigh),0.35,0.87,1,15);
  //  drawText("p_{T}^{track} > 8 GeV",0.35,0.83,1,15);
  drawText(Form("#Delta#theta > %.1f",(float)thetaCut),0.35,0.74,2,20);
  
  c9->cd(5);
  TH1D* ratioZg = (TH1D*)pp.hRecoZg->Clone("ratioZg");
  ratioZg->Divide(pp.hGenZg);
  ratioZg->SetAxisRange(0,2.3,"Y");
  ratioZg->SetXTitle("z_{g}");
  ratioZg->SetYTitle("Reco/Truth");
  fixedFontHist(ratioZg,2.5,1.5);
  ratioZg->SetNdivisions(505,"X");
  ratioZg->SetNdivisions(505,"Y");
  ratioZg->DrawCopy();
  jumSun(0,1,0.6,1);
  

  c9->cd(2);
  handsomeTH1(aa[6].hGenZg,2);
  handsomeTH1(aa[6].hRecoZg,2);
  aa[6].hGenZg->SetXTitle("z_{g} = min(p_{T}^{1},p_{T}^{2})/(p_{T}^{1}+p_{T}^{2})");
  cleverRange(aa[6].hGenZg,1.8);
  aa[6].hGenZg->SetNdivisions(505);
  aa[6].hGenZg->DrawCopy("hist");
  aa[6].hRecoZg->DrawCopy("e same");
  drawText("60-80%", 0.6, 0.8,1,25);
  //  leg9->Draw();

  c9->cd(6);
  ratioZg = (TH1D*)aa[6].hRecoZg->Clone("ratioZg");
  ratioZg->Divide(aa[6].hGenZg);
  ratioZg->SetAxisRange(0,2.3,"Y");
  ratioZg->SetXTitle("z_{g}");
  fixedFontHist(ratioZg,2.5,1.5);
  ratioZg->SetNdivisions(505,"X");
  ratioZg->SetNdivisions(505,"Y");
  ratioZg->DrawCopy();
  jumSun(0,1,0.6,1);

  c9->cd(3);
  handsomeTH1(aa[3].hGenZg,2);
  handsomeTH1(aa[3].hRecoZg,2);
  aa[3].hGenZg->SetXTitle("z_{g} = min(p_{T}^{1},p_{T}^{2})/(p_{T}^{1}+p_{T}^{2})");
  cleverRange(aa[3].hGenZg,1.8);
  aa[3].hGenZg->SetNdivisions(505);
  aa[3].hGenZg->DrawCopy("hist");
  aa[3].hRecoZg->DrawCopy("e same");
  drawText("30-40%", 0.6, 0.8,1,25);

  c9->cd(7);
  ratioZg = (TH1D*)aa[3].hRecoZg->Clone("ratioZg");
  ratioZg->Divide(aa[3].hGenZg);
  ratioZg->SetAxisRange(0,2.3,"Y");
  ratioZg->SetXTitle("z_{g}");
  fixedFontHist(ratioZg,2.5,1.5);
  ratioZg->SetNdivisions(505,"X");
  ratioZg->SetNdivisions(505,"Y");
  ratioZg->DrawCopy();
  jumSun(0,1,0.6,1);

  c9->cd(4);
  handsomeTH1(aa[0].hGenZg,2);
  handsomeTH1(aa[0].hRecoZg,2);
  aa[0].hGenZg->SetXTitle("z_{g} = min(p_{T}^{1},p_{T}^{2})/(p_{T}^{1}+p_{T}^{2})");
  cleverRange(aa[0].hGenZg,1.8);
  aa[0].hGenZg->SetNdivisions(505);
  aa[0].hGenZg->DrawCopy("hist");
  aa[0].hRecoZg->DrawCopy("e same");
  drawText("0-10%", 0.6, 0.8,1,25);

  c9->cd(8);
  ratioZg = (TH1D*)aa[0].hRecoZg->Clone("ratioZg");
  ratioZg->Divide(aa[0].hGenZg);
  ratioZg->SetAxisRange(0,2.3,"Y");
  ratioZg->SetXTitle("z_{g}");
  fixedFontHist(ratioZg,2.5,1.5);
  ratioZg->SetNdivisions(505,"X");
  ratioZg->SetNdivisions(505,"Y");
  ratioZg->DrawCopy();
  jumSun(0,1,0.6,1);


  c4->SaveAs(prefix+"/validation1.pdf");
  c5->SaveAs(prefix+"/validation2.pdf");
  c3->SaveAs(prefix+"/theta_ch.pdf");
  c6->SaveAs(prefix+"/zg_ch.pdf");
  c7->SaveAs(prefix+"/sdmass_ch.pdf");
  c9->SaveAs(prefix+"/zg_full.pdf");

  /*
    c2->SaveAs(prefix+"/theta_full.pdf");
    c3->SaveAs(prefix+"/theta_ch.pdf");
    c6->SaveAs(prefix+"/zg_ch.pdf");
    c7->SaveAs(prefix+"/sdmass_ch.pdf");
    c8->SaveAs(prefix+"/sdmass_full.pdf");
    
    c4->SaveAs(prefix+"/validation1.png");
    c5->SaveAs(prefix+"/validation2.png");
    c2->SaveAs(prefix+"/theta_full.png");
    c9->SaveAs(prefix+"/zg_full.png");
    c8->SaveAs(prefix+"/sdmass_full.png");
  */


}





