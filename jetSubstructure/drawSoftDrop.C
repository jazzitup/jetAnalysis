#include "getSdHists.C"
/*
  TH1D* hEffDphi[10];
  TH1D* hEffDrap[10];
*/
void drawSoftDrop(int ptLow=150, int ptHigh=250, float thetaCut = 0.2, int numEvents = 100000 ){
  
  TString fnamePP = "ntuples/jetSubTree_pythia_r1.0_jz3_v1.6.root";
  //TString fnameAA = "ntuples/jetSubstructure_himix_r1.0_bkgKill0_jz3.root";
  //  TString fnameAA = "ntuples/jetSubstructure_himix_r1.0_ptCut8_jz3_v1.9.root";
  TString fnameAA = "ntuples/jetSubstructure_himix_r1.0_bkgKill0_jz3_v1.9.root";
  
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
  
  // Calorimeter subjets
  TCanvas* c2pp=  new TCanvas("c2pp","",400,400);
  handsomeTH1(pp.hGenTheta,1);
  handsomeTH1(pp.hRecoTheta,1);
  pp.hGenTheta->SetXTitle("#theta between subjets");
  pp.hGenTheta->DrawCopy("hist");
  pp.hRecoTheta->DrawCopy("e same");

  TLegend *leg2= new TLegend(0.336546,0.3894737,1,0.6347368,NULL,"brNDC");
  easyLeg(leg2,"Full subjets (PYTHIA)");
  leg2->AddEntry(pp.hGenTheta,"Truth sub-jet","l");
  leg2->AddEntry(pp.hRecoTheta,"Calo sub-jet","pl");
  leg2->Draw();
  
  drawText(Form("p_{T}^{jet}: %d - %d GeV,   |#eta^{jet}| < 1.2",ptLow,ptHigh),0.35,0.8,1,15);
  //  drawText("p_{T}^{track} > 4 GeV/c",0.35,0.7,1,15);
  
  TCanvas* c2=  new TCanvas("c2","",1200,400);
  c2->Divide(3,1);
  c2->cd(1);
  handsomeTH1(aa[6].hGenTheta,2,1,24);
  handsomeTH1(aa[6].hRecoTheta,2,1,24);
  aa[6].hGenTheta->SetXTitle("#theta between subjets");
  aa[6].hGenTheta->DrawCopy("hist");
  aa[6].hRecoTheta->DrawCopy("e same");
  drawText("60-80%", 0.3, 0.8,1,25);
  TLegend *leg3= new TLegend(0.3062558,0.452381,0.9990587,0.7163265,NULL,"brNDC");
  easyLeg(leg3,"PbPb MC");
  leg3->AddEntry(aa[6].hGenTheta,"Truth particles","l");
  leg3->AddEntry(aa[6].hRecoTheta,"Reco tower","pl");
  leg3->Draw();

  c2->cd(2);
  handsomeTH1(aa[3].hGenTheta,2,1,20);
  handsomeTH1(aa[3].hRecoTheta,2,1,20);
  aa[3].hGenTheta->SetXTitle("#theta between subjets");
  aa[3].hGenTheta->DrawCopy("hist");
  aa[3].hRecoTheta->DrawCopy("e same");
  drawText("30-40%", 0.3, 0.8,1,25);

  c2->cd(3);
  handsomeTH1(aa[0].hGenTheta,2);
  handsomeTH1(aa[0].hRecoTheta,2);
  aa[0].hGenTheta->SetXTitle("#theta between subjets");
  aa[0].hGenTheta->DrawCopy("hist");
  aa[0].hRecoTheta->DrawCopy("e same");
  drawText("0-10%", 0.3, 0.8,1,25);


  // theta vs charged theta
  TCanvas* c3pp=  new TCanvas("c3pp","",400,800);
  c3pp->Divide(1,2); 
  c3pp->cd(1);
  handsomeTH1(pp.hGenChTheta,1);
  handsomeTH1(pp.hRecoChTheta,1);
  pp.hGenChTheta->SetXTitle("#theta between subjets");
  pp.hGenChTheta->DrawCopy("hist");
  pp.hRecoChTheta->DrawCopy("e same");

  TLegend* leg4 = (TLegend*)leg2->Clone("leg4");
  leg4->SetHeader("Charged sub-jet");
  leg4->Draw();
  drawText(Form("p_{T}^{jet}: %d - %d GeV,   |#eta^{jet}| < 1.2",ptLow,ptHigh),0.35,0.8,1,15);
  drawText("p_{T}^{track} > 4 GeV/c",0.35,0.7,1,15);

  c3pp->cd(2);
  TH1D* ppRatio = (TH1D*)pp.hRecoChTheta->Clone("ppRatio");
  ppRatio->Divide(pp.hGenChTheta);
  ppRatio->SetAxisRange(0,2,"Y");
  ppRatio->SetYTitle("Reco/Truth");
  ppRatio->DrawCopy();
  jumSun(0,1,1,1);
  
  TCanvas* c3=  new TCanvas("c3","",1200,800);
  c3->Divide(3,2);
  c3->cd(1);
  handsomeTH1(aa[6].hGenChTheta,2,1,24);
  handsomeTH1(aa[6].hRecoChTheta,2,1,24);
  aa[6].hGenChTheta->SetXTitle("#theta between subjets");
  cleverRange(aa[6].hGenChTheta);
  aa[6].hGenChTheta->DrawCopy("hist");
  aa[6].hRecoChTheta->DrawCopy("e same");
  drawText("60-80%", 0.3, 0.8,1,25);
  TLegend *leg31= new TLegend(0.3062558,0.452381,0.9990587,0.7163265,NULL,"brNDC");
  easyLeg(leg31,"PbPb MC, p_{T}^{constituent} > 4 GeV/c");
  leg31->AddEntry(aa[6].hGenChTheta, "Truth Charged Subjet");
  leg31->AddEntry(aa[6].hRecoChTheta, "Reco Charged Subjet");
  leg31->Draw();
  
  c3->cd(4);
  TH1D* rat = (TH1D*)aa[6].hRecoChTheta->Clone("rat");
  rat->Divide(aa[6].hGenChTheta);
  rat->SetAxisRange(0,5,"Y");
  rat->SetYTitle("Reco/Truth");
  rat->DrawCopy();
  jumSun(0,1,1,1);

  c3->cd(2);
  handsomeTH1(aa[3].hGenChTheta,2,1,20);
  handsomeTH1(aa[3].hRecoChTheta,2,1,20);
  aa[3].hGenChTheta->SetXTitle("#theta between subjets");
  cleverRange(aa[3].hGenChTheta);
  aa[3].hGenChTheta->DrawCopy("hist");
  aa[3].hRecoChTheta->DrawCopy("e same");
  drawText("30-40%", 0.3, 0.8,1,25);
  c3->cd(5);
  rat = (TH1D*)aa[3].hRecoChTheta->Clone("rat");
  rat->Divide(aa[3].hGenChTheta);
  rat->SetAxisRange(0,5,"Y");
  rat->SetYTitle("Reco/Truth");
  rat->DrawCopy();
  jumSun(0,1,1,1);

  c3->cd(3);
  handsomeTH1(aa[0].hGenChTheta,2);
  handsomeTH1(aa[0].hRecoChTheta,2);
  aa[0].hGenChTheta->SetXTitle("#theta between subjets");
  cleverRange(aa[0].hGenChTheta);
  aa[0].hGenChTheta->DrawCopy("hist");
  aa[0].hRecoChTheta->DrawCopy("e same");
  drawText("0-10%", 0.3, 0.8,1,25);
  c3->cd(6);
  rat = (TH1D*)aa[0].hRecoChTheta->Clone("rat");
  rat->Divide(aa[0].hGenChTheta);
  rat->SetAxisRange(0,5,"Y");
  rat->SetYTitle("Reco/Truth");
  rat->DrawCopy();
  jumSun(0,1,1,1);

  
  // theta vs ch theta
  // theta vs charged theta
  TCanvas* c4pp=  new TCanvas("c4pp","",400,800);
  c4pp->Divide(1,2);
  c4pp->cd(1);
  handsomeTH1(pp.hGenChTheta,1);
  handsomeTH1(pp.hGenTheta,1);
  pp.hGenTheta->DrawCopy("hist");
  pp.hGenChTheta->DrawCopy("e same");

  TLegend* leg5 = new TLegend(0.3036546,0.3894737,0.9,0.6347368,NULL,"brNDC");
  easyLeg(leg5,"PYTHIA MC");
  leg5->AddEntry(pp.hGenTheta, "Ntrl + Cha'd particles","l");
  leg5->AddEntry(pp.hGenChTheta, "Chg'd only");
  leg5->Draw();
  drawText(Form("p_{T}^{jet}: %d - %d GeV,   |#eta^{jet}| < 1.2",ptLow,ptHigh),0.35,0.8,1,15);
  drawText("constituent p_{T} > 4 GeV/c",0.35,0.7,1,15);

  c4pp->cd(2);
  ppRatio = (TH1D*)pp.hGenChTheta->Clone("ppRatio");
  ppRatio->Divide(pp.hGenTheta);
  ppRatio->SetAxisRange(0,2,"Y");
  ppRatio->SetYTitle("Charge/Full");
  ppRatio->DrawCopy();
  jumSun(0,1,1,1);  
  

  // Bin migration effect?

  TCanvas* c5=  new TCanvas("c5","",1200,800);
  c5->Divide(3,2);
  c5->cd(1);
  handsomeTH1(aa[6].hRecoChTheta,2);
  handsomeTH1(aaR[6].hRecoChTheta,2,1,24);
  aa[6].hRecoChTheta->SetXTitle("#theta of Reco'ed Ch. subjets");
  scaleInt(aa[6].hRecoChTheta);
  scaleInt(aaR[6].hRecoChTheta);
  aa[6].hRecoChTheta->DrawCopy();
  aaR[6].hRecoChTheta->DrawCopy("same");
  drawText("60-80%", 0.3, 0.8,1,25);
  TLegend *leg30= new TLegend(0.3062558,0.452381,0.9990587,0.7163265,NULL,"brNDC");
  easyLeg(leg30,Form("PbPb MC, %d < p_{T}^{jet} < %d GeV/c",ptLow, ptHigh));
  leg30->AddEntry(aa[6].hRecoChTheta,"p_{T}^{truth Jet}");
  leg30->AddEntry(aaR[6].hRecoChTheta,"p_{T}^{Reco Jet}");
  leg30->Draw();

  c5->cd(4);
  rat = (TH1D*)aaR[6].hRecoChTheta->Clone("rat");
  rat->Divide(aa[6].hRecoChTheta);
  rat->SetAxisRange(0,5,"Y");
  rat->SetYTitle("[Reco p_{T} cut] / [Truth p_{T} cut]");
  rat->DrawCopy();

  jumSun(0,1,1,1);

  c5->cd(2);
  handsomeTH1(aa[3].hRecoChTheta,2);
  handsomeTH1(aaR[3].hRecoChTheta,2,1,24);
  aa[3].hRecoChTheta->SetXTitle("#theta between subjets");
  scaleInt(aa[3].hRecoChTheta);
  scaleInt(aaR[3].hRecoChTheta);
  aa[3].hRecoChTheta->DrawCopy();
  aaR[3].hRecoChTheta->DrawCopy("same");
  drawText("30-40%", 0.3, 0.8,1,25);
  c5->cd(5);
  rat = (TH1D*)aaR[3].hRecoChTheta->Clone("rat");
  rat->Divide(aa[3].hRecoChTheta);
  rat->SetAxisRange(0,5,"Y");
  rat->SetYTitle("[Reco cut] / [Truth cut]");
  rat->DrawCopy();
  jumSun(0,1,1,1);

  c5->cd(3);
  handsomeTH1(aa[0].hRecoChTheta,2);
  handsomeTH1(aaR[0].hRecoChTheta,2,1,24);
  aa[0].hRecoChTheta->SetXTitle("#theta between subjets");
  scaleInt(aa[0].hRecoChTheta);
  scaleInt(aaR[0].hRecoChTheta);
  aa[0].hRecoChTheta->DrawCopy();
  aaR[0].hRecoChTheta->DrawCopy("same");
  drawText("0-10%", 0.3, 0.8,1,25);
  c5->cd(6);
  rat = (TH1D*)aaR[0].hRecoChTheta->Clone("rat");
  rat->Divide(aa[0].hRecoChTheta);
  rat->SetAxisRange(0,5,"Y");
  rat->SetYTitle("[Reco cut] / [Truth cut]");
  rat->DrawCopy();
  jumSun(0,1,1,1);
  
  c5->SaveAs("jet_pt_bin_migration.gif");



  // z_{g}
  // theta vs charged theta
  TCanvas* c6pp=  new TCanvas("c6pp","",400,400);
  handsomeTH1(pp.hGenChZg,1);
  handsomeTH1(pp.hRecoChZg,1);
  pp.hGenChZg->SetXTitle("z_{g} = min(p_{T}^{1},p_{T}^{2})/(p_{T}^{1}+p_{T}^{2})");
  cleverRange(pp.hGenChZg,1.6);
  pp.hGenChZg->SetNdivisions(505);
  pp.hGenChZg->DrawCopy("hist");
  pp.hRecoChZg->DrawCopy("e same");

  TLegend *leg6 = new TLegend(0.419598,0.5073333,0.9572864,0.7033333,NULL,"brNDC");
  easyLeg(leg6,"Charged subjets");
  leg6->AddEntry(pp.hGenChZg,"Truth Charges","l");
  leg6->AddEntry(pp.hRecoChZg,"Tracks","pl");
  leg6->Draw();
  drawText(Form("p_{T}^{jet}: %d - %d GeV,   |#eta^{jet}| < 1.2",ptLow,ptHigh),0.25,0.87,1,15);
  drawText("p_{T}^{track} > 8 GeV",0.25,0.83,1,15);
  drawText(Form("#Delta#theta > %.1f",(float)thetaCut),0.25,0.74,2,20);

  TCanvas* c6=  new TCanvas("c6","",1200,400);
  c6->Divide(3,1);
  c6->cd(1);
  handsomeTH1(aa[6].hGenChZg,1);
  handsomeTH1(aa[6].hRecoChZg,1);
  aa[6].hGenChZg->SetXTitle("z_{g} = min(p_{T}^{1},p_{T}^{2})/(p_{T}^{1}+p_{T}^{2})");
  cleverRange(aa[6].hGenChZg,1.6);
  aa[6].hGenChZg->SetNdivisions(505);
  aa[6].hGenChZg->DrawCopy("hist");
  aa[6].hRecoChZg->DrawCopy("e same");
  drawText("60-80%", 0.6, 0.8,1,25);
  leg6->Draw();
  c6->cd(2);
  handsomeTH1(aa[3].hGenChZg,1);
  handsomeTH1(aa[3].hRecoChZg,1);
  aa[3].hGenChZg->SetXTitle("z_{g} = min(p_{T}^{1},p_{T}^{2})/(p_{T}^{1}+p_{T}^{2})");
  cleverRange(aa[3].hGenChZg,1.6);
  aa[3].hGenChZg->SetNdivisions(505);
  aa[3].hGenChZg->DrawCopy("hist");
  aa[3].hRecoChZg->DrawCopy("e same");
  drawText("30-40%", 0.6, 0.8,1,25);

  c6->cd(3);
  handsomeTH1(aa[0].hGenChZg,1);
  handsomeTH1(aa[0].hRecoChZg,1);
  aa[0].hGenChZg->SetXTitle("z_{g} = min(p_{T}^{1},p_{T}^{2})/(p_{T}^{1}+p_{T}^{2})");
  cleverRange(aa[0].hGenChZg,1.6);
  aa[0].hGenChZg->SetNdivisions(505);
  aa[0].hGenChZg->DrawCopy("hist");
  aa[0].hRecoChZg->DrawCopy("e same");
  drawText("0-10%", 0.6, 0.8,1,25);


  ///////////////////////  
  // Mass distribution //
  ///////////////////////
  TCanvas* c7pp=  new TCanvas("c7pp","",400,800);
  c7pp->Divide(1,2); 
  c7pp->cd(1);
  handsomeTH1(pp.hGenChSdM,1);
  handsomeTH1(pp.hRecoChSdM,1);
  pp.hGenChSdM->SetXTitle("SoftDrop Ch'd Mass (GeV)");
  pp.hGenChSdM->DrawCopy("hist");
  pp.hRecoChSdM->DrawCopy("e same");

  TLegend* leg7 = (TLegend*)leg2->Clone("leg7");
  leg7->SetHeader("Charged sub-jet");
  leg7->Draw();
  drawText(Form("p_{T}^{jet}: %d - %d GeV,   |#eta^{jet}| < 1.2",ptLow,ptHigh),0.35,0.8,1,15);
  drawText("p_{T}^{track} > 4 GeV/c",0.35,0.7,1,15);

  c7pp->cd(2);
  TH1D* ppRatioChM = (TH1D*)pp.hRecoChSdM->Clone("ppRatioChM");
  ppRatioChM->Divide(pp.hGenChSdM);
  ppRatioChM->SetAxisRange(0,2,"Y");
  ppRatioChM->SetYTitle("Reco/Truth");
  ppRatioChM->DrawCopy();
  jumSun(0,1,1,1);
  
  TCanvas* c7=  new TCanvas("c7","",1200,800);
  c7->Divide(3,2);
  c7->cd(1);
  handsomeTH1(aa[6].hGenChSdM,2,1,24);
  handsomeTH1(aa[6].hRecoChSdM,2,1,24);
  aa[6].hGenChSdM->SetXTitle("SoftDrop Ch'ed Mass (GeV)");
  cleverRange(aa[6].hGenChSdM);
  aa[6].hGenChSdM->DrawCopy("hist");
  aa[6].hRecoChSdM->DrawCopy("e same");
  drawText("60-80%", 0.3, 0.8,1,25);
  TLegend *leg71= new TLegend(0.3062558,0.452381,0.9990587,0.7163265,NULL,"brNDC");
  easyLeg(leg71,"PbPb MC, p_{T}^{constituent} > 4 GeV/c");
  leg71->AddEntry(aa[6].hGenChSdM, "Truth Charged Subjet");
  leg71->AddEntry(aa[6].hRecoChSdM, "Reco Charged Subjet");
  leg71->Draw();
  
  c7->cd(4);
  TH1D* ratChM = (TH1D*)aa[6].hRecoChSdM->Clone("ratChM");
  ratChM->Divide(aa[6].hGenChSdM);
  ratChM->SetAxisRange(0,5,"Y");
  ratChM->SetYTitle("Reco/Truth");
  ratChM->DrawCopy();
  jumSun(0,1,1,1);

  c7->cd(2);
  handsomeTH1(aa[3].hGenChSdM,2,1,20);
  handsomeTH1(aa[3].hRecoChSdM,2,1,20);
  aa[3].hGenChSdM->SetXTitle("SoftDrop Mass (GeV)");
  cleverRange(aa[3].hGenChSdM);
  aa[3].hGenChSdM->DrawCopy("hist");
  aa[3].hRecoChSdM->DrawCopy("e same");
  drawText("30-40%", 0.3, 0.8,1,25);
  c7->cd(5);
  ratChM = (TH1D*)aa[3].hRecoChSdM->Clone("ratChM");
  ratChM->Divide(aa[3].hGenChSdM);
  ratChM->SetAxisRange(0,5,"Y");
  ratChM->SetYTitle("Reco/Truth");
  ratChM->DrawCopy();
  jumSun(0,1,1,1);

  c7->cd(3);
  handsomeTH1(aa[0].hGenChSdM,2);
  handsomeTH1(aa[0].hRecoChSdM,2);
  aa[0].hGenChSdM->SetXTitle("SoftDrop Mass (GeV)");
  cleverRange(aa[0].hGenChSdM);
  aa[0].hGenChSdM->DrawCopy("hist");
  aa[0].hRecoChSdM->DrawCopy("e same");
  drawText("0-10%", 0.3, 0.8,1,25);
  c7->cd(6);
  ratChM = (TH1D*)aa[0].hRecoChSdM->Clone("ratChM");
  ratChM->Divide(aa[0].hGenChSdM);
  ratChM->SetAxisRange(0,5,"Y");
  ratChM->SetYTitle("Reco/Truth");
  ratChM->DrawCopy();
  jumSun(0,1,1,1);
  
  TCanvas* c8pp=  new TCanvas("c8pp","",400,800);
  c8pp->Divide(1,2); 
  c8pp->cd(1);
  handsomeTH1(pp.hGenSdM,1);
  handsomeTH1(pp.hRecoSdM,1);
  pp.hGenSdM->SetXTitle("SoftDrop Mass (GeV)");
  pp.hGenSdM->DrawCopy("hist");
  pp.hRecoSdM->DrawCopy("e same");

  TLegend* leg8 = (TLegend*)leg2->Clone("leg8");
  leg8->SetHeader("Charged sub-jet");
  leg8->Draw();
  drawText(Form("p_{T}^{jet}: %d - %d GeV,   |#eta^{jet}| < 1.2",ptLow,ptHigh),0.35,0.8,1,15);
  drawText("p_{T}^{track} > 4 GeV/c",0.35,0.7,1,15);

  c8pp->cd(2);
  TH1D* ppRatioM = (TH1D*)pp.hRecoSdM->Clone("ppRatioM");
  ppRatioM->Divide(pp.hGenSdM);
  ppRatioM->SetAxisRange(0,2,"Y");
  ppRatioM->SetYTitle("Reco/Truth");
  ppRatioM->DrawCopy();
  jumSun(0,1,1,1);
  
  TCanvas* c8=  new TCanvas("c8","",1200,800);
  c8->Divide(3,2);
  c8->cd(1);
  handsomeTH1(aa[6].hGenSdM,2,1,24);
  handsomeTH1(aa[6].hRecoSdM,2,1,24);
  aa[6].hGenSdM->SetXTitle("SoftDrop Mass (GeV)");
  cleverRange(aa[6].hGenSdM);
  aa[6].hGenSdM->DrawCopy("hist");
  aa[6].hRecoSdM->DrawCopy("e same");
  drawText("60-80%", 0.3, 0.8,1,25);
  TLegend *leg81= new TLegend(0.3062558,0.452381,0.9990587,0.7163265,NULL,"brNDC");
  easyLeg(leg81,"PbPb MC, p_{T}^{constituent} > 4 GeV/c");
  leg81->AddEntry(aa[6].hGenSdM, "Truth Charged Subjet");
  leg81->AddEntry(aa[6].hRecoSdM, "Reco Charged Subjet");
  leg81->Draw();
  
  c8->cd(4);
  TH1D* ratM = (TH1D*)aa[6].hRecoSdM->Clone("ratM");
  ratM->Divide(aa[6].hGenSdM);
  ratM->SetAxisRange(0,5,"Y");
  ratM->SetYTitle("Reco/Truth");
  ratM->DrawCopy();
  jumSun(0,1,1,1);

  c8->cd(2);
  handsomeTH1(aa[3].hGenSdM,2,1,20);
  handsomeTH1(aa[3].hRecoSdM,2,1,20);
  aa[3].hGenSdM->SetXTitle("SoftDrop Mass (GeV)");
  cleverRange(aa[3].hGenSdM);
  aa[3].hGenSdM->DrawCopy("hist");
  aa[3].hRecoSdM->DrawCopy("e same");
  drawText("30-40%", 0.3, 0.8,1,25);
  c8->cd(5);
  ratM = (TH1D*)aa[3].hRecoSdM->Clone("ratM");
  ratM->Divide(aa[3].hGenSdM);
  ratM->SetAxisRange(0,5,"Y");
  ratM->SetYTitle("Reco/Truth");
  ratM->DrawCopy();
  jumSun(0,1,1,1);
  
  c8->cd(3);
  handsomeTH1(aa[0].hGenSdM,2);
  handsomeTH1(aa[0].hRecoSdM,2);
  aa[0].hGenSdM->SetXTitle("SoftDrop Mass (GeV)");
  cleverRange(aa[0].hGenSdM);
  aa[0].hGenSdM->DrawCopy("hist");
  aa[0].hRecoSdM->DrawCopy("e same");
  drawText("0-10%", 0.3, 0.8,1,25);
  c8->cd(6);
  ratM = (TH1D*)aa[0].hRecoSdM->Clone("ratM");
  ratM->Divide(aa[0].hGenSdM);
  ratM->SetAxisRange(0,5,"Y");
  ratM->SetYTitle("Reco/Truth");
  ratM->DrawCopy();
  jumSun(0,1,1,1);
  

}





