#include "getSdHists.C"
/*
  TH1D* hEffDphi[10];
  TH1D* hEffDrap[10];
*/
void drawSoftDrop(int ptLow=150, int ptHigh=250, float thetaCut = 0., int numEvents = 10000 ){
  
  TString fnamePP = "ntuples/jetSubstructure_pythia_r1.0_ptCut6_jz3_v1.9.root";
  TString fnameAA = "ntuples/jetSubstructure_himix_r1.0_ptCut6_jz3_v1.9.root";
  
  TString ptCut = Form("genPt>%d && genPt<%d  ",ptLow, ptHigh) ; 
  TString recoPtCut = Form("pt>%d && pt<%d ",ptLow, ptHigh) ; 

  sdVariable pp = getSdHists("pp", fnamePP, 0, ptCut,thetaCut, numEvents );
  
  sdVariable aa[7];
  sdVariable aaR[7];  // reco pt cut is applied
  
  for ( int icent = 0 ; icent<=6 ; icent++) {
    aa[icent] = getSdHists(Form("pbpb%d",icent),fnameAA , icent, ptCut, thetaCut, numEvents ) ;
    aaR[icent] = getSdHists(Form("pbpbR%d",icent),fnameAA , icent, recoPtCut, thetaCut, numEvents ) ;
  }
  TCanvas* c1=  new TCanvas("c100","",1000,500);
  c1->Divide(2,1);
  c1->cd(1);
  handsomeTH1(pp.hEffDphi,1);
  handsomeTH1(aa[6].hEffDphi,2,1,24);
  handsomeTH1(aa[0].hEffDphi,2);
  pp.hEffDphi->SetXTitle("#Delta#phi of track-jet");
  pp.hEffDphi->SetYTitle("Efficiency");
  pp.hEffDphi->SetAxisRange(0,1.2,"Y");
  pp.hEffDphi->SetNdivisions(505);
  pp.hEffDphi->DrawCopy("hist");
  aa[6].hEffDphi->DrawCopy("same e"); 
  aa[0].hEffDphi->DrawCopy("same e"); 
  TLegend *leg1= new TLegend(0.2672428,0.2089151,0.9999582,0.4709989,NULL,"brNDC");
  easyLeg(leg1,"Tracks in #DeltaR <1.0 cone");
  leg1->AddEntry( pp.hEffDphi, "PYTHIA","l");
  leg1->AddEntry( aa[6].hEffDphi, "+ PbPb 60-80%","p");
  leg1->AddEntry( aa[0].hEffDphi, "+ PbPb 0-10%","p");
  leg1->Draw();
  c1->cd(2);
  handsomeTH1(pp.hEffDrap,1);
  handsomeTH1(aa[6].hEffDrap,2,1,24);
  handsomeTH1(aa[0].hEffDrap,2);
  pp.hEffDrap->SetXTitle("#Deltay of track-jet");
  pp.hEffDrap->SetYTitle("Efficiency");
  pp.hEffDrap->SetAxisRange(0,1.2,"Y");
  pp.hEffDrap->SetNdivisions(505);
  pp.hEffDrap->DrawCopy("hist");
  aa[6].hEffDrap->DrawCopy("same e"); 
  aa[0].hEffDrap->DrawCopy("same e"); 
  c1->SaveAs("figures/c1.pdf");
  
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

  c2->SaveAs("figures/c2.pdf");

  // theta vs charged theta
  TCanvas* c3=  new TCanvas("c3","",1200,450);
  makeEfficiencyCanvas(c3,4);
  c3->cd(1);
  handsomeTH1(pp.hGenChTheta,1);
  handsomeTH1(pp.hRecoChTheta,1);
  pp.hGenChTheta->SetXTitle("#theta between subjets");
  pp.hGenChTheta->DrawCopy("hist");
  pp.hRecoChTheta->DrawCopy("e same");
  gPad->SetLogy();

  TLegend *leg4= new TLegend(0.556546,0.3894737,1,0.6347368,NULL,"brNDC");
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
  c3->SaveAs("figures/c3.pdf");

  
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
  handsomeTH1(pp.hGenChTheta,1);
  handsomeTH1(pp.hGenTheta,1);
  pp.hGenTheta->DrawCopy("hist");
  pp.hGenChTheta->DrawCopy("e same");
  gPad->SetLogy();
  TLegend* leg5 = new TLegend(0.5036546,0.3894737,0.9,0.6347368,NULL,"brNDC");
  easyLeg(leg5,"pp MC Truth");
  leg5->AddEntry(pp.hGenTheta, "Ntrl + Cha'd particles","l");
  leg5->AddEntry(pp.hGenChTheta, "Chg'd only");
  leg5->Draw();
  drawText(Form("p_{T}^{jet}: %d - %d GeV,   |#eta^{jet}| < 1.2",ptLow,ptHigh),0.5,0.8,1,15);
  drawText("constituent p_{T} > 4 GeV/c",0.5,0.7,1,15);

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
  
  c4->SaveAs("figures/c4.pdf");
  
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
  
  c5->SaveAs("figures/c5.pdf");


  // z_{g}
  // theta vs charged theta
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

  TLegend *leg6 = new TLegend(0.559598,0.4073333,0.9572864,0.7033333,NULL,"brNDC");
  easyLeg(leg6,"Charged subjets");
  leg6->AddEntry(pp.hGenChZg,"Truth Tracks","l");
  leg6->AddEntry(pp.hRecoChZg,"Reco Tracks","pl");
  leg6->Draw();
  drawText(Form("p_{T}^{jet}: %d - %d GeV,   |#eta^{jet}| < 1.2",ptLow,ptHigh),0.35,0.87,1,15);
  drawText("p_{T}^{track} > 8 GeV",0.35,0.83,1,15);
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

  c6->SaveAs("figures/c6.pdf");

  ///////////////////////  
  // Mass distribution //
  ///////////////////////
  TCanvas* c7=  new TCanvas("c7","",1200,450);
  makeEfficiencyCanvas(c7,4);
  c7->cd(1);
  handsomeTH1(pp.hGenChSdM,1);
  handsomeTH1(pp.hRecoChSdM,1);
  pp.hGenChSdM->SetXTitle("SoftDrop Ch'd Mass (GeV)");
  pp.hGenChSdM->DrawCopy("hist");
  pp.hRecoChSdM->DrawCopy("e same");

  TLegend *leg7= new TLegend(0.556546,0.3894737,1,0.6347368,NULL,"brNDC");
  easyLeg(leg7,"Chg'd sub-jet");
  leg7->AddEntry(pp.hGenChSdM, "Truth chg'd particles","l");
  leg7->AddEntry(pp.hRecoChSdM, "Reco tracks");
  leg7->Draw();
  drawText("pp MC", 0.35, 0.9, 15);
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
  aa[6].hGenChSdM->DrawCopy("hist");
  aa[6].hRecoChSdM->DrawCopy("e same");
  drawText("PbPb MC 60-80%", 0.3, 0.8,1,20);
  TLegend *leg71= new TLegend(0.3062558,0.452381,0.9990587,0.7163265,NULL,"brNDC");
  easyLeg(leg71,"PbPb MC, p_{T}^{constituent} > 4 GeV/c");
  leg71->AddEntry(aa[6].hGenChSdM, "Truth chg'd particles","l");
  leg71->AddEntry(aa[6].hRecoChSdM, "Reco tracks");
  leg71->Draw();
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

  aa[0].hGenChSdM->DrawCopy("hist");
  aa[0].hRecoChSdM->DrawCopy("e same");
  drawText("0-10%", 0.3, 0.8,1,20);
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
  
  c7->SaveAs("figures/c7.pdf");

  TCanvas* c8=  new TCanvas("c8","",1200,450);
  makeEfficiencyCanvas(c8,4);
  c8->cd(1);
  handsomeTH1(pp.hGenSdM,1);
  handsomeTH1(pp.hRecoSdM,1);
  cleverRange(pp.hGenSdM,100,10000);
  pp.hGenSdM->SetXTitle("SoftDrop Mass (GeV)");
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

  c8->SaveAs("figures/c8.pdf");
  

}





