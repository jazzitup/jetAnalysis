#include "getSdHists.C"
/*
  TH1D* hEffDphi[10];
  TH1D* hEffDrap[10];
*/
void drawSoftDrop(int ptLow=150, int ptHigh=250) { 
  
  TString fnamePP = "ntuples/jetSubTree_pythia_r1.0_jz3_v1.6.root";
  TString fnameAA = "ntuples/jetSubTree_himix_r1.0_jz3_v1.6.root";
  
  TString ptCut = Form("genPt>%d && genPt<%d",ptLow, ptHigh) ; 
  TString recoPtCut = Form("pt>%d && pt<%d",ptLow, ptHigh) ; 
  sdVariable pp = getSdHists("pp", fnamePP, 0, ptCut );
  sdVariable ppLA = getSdHists("pp",fnamePP, 0, ptCut + " && chTheta>0.1"); // large angle
  
  sdVariable aa[7];
  sdVariable aaLA[7];
  sdVariable aaR[7];  // reco pt cut is applied
  
  for ( int icent = 0 ; icent<=6 ; icent++) {
    aa[icent] = getSdHists(Form("pbpb%d",icent),fnameAA , icent, ptCut ) ;
    aaR[icent] = getSdHists(Form("pbpbR%d",icent),fnameAA , icent, recoPtCut ) ;
    aaLA[icent] = getSdHists(Form("pbpbLA%d",icent),fnameAA, icent, ptCut + " && chTheta>0.1") ;
  }
  TCanvas* c1=  new TCanvas("c1","",1000,500);
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
  leg3->AddEntry(aa[6].hGenTheta,"Truth chg'd particles","l");
  leg3->AddEntry(aa[6].hRecoTheta,"Reco","pl");
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
  leg3->Draw();
  
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
  aa[6].hRecoChTheta->SetXTitle("#theta between subjets");
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
  TCanvas* c6ppLA=  new TCanvas("c6ppLA","",400,400);
  handsomeTH1(ppLA.hGenChZg,1);
  handsomeTH1(ppLA.hRecoChZg,1);
  ppLA.hGenChZg->SetXTitle("z_{g} = min(p_{T}^{1},p_{T}^{2})/(p_{T}^{1}+p_{T}^{2})");
  cleverRange(ppLA.hGenChZg,1.6);
  ppLA.hGenChZg->SetNdivisions(505);
  ppLA.hGenChZg->DrawCopy("hist");
  ppLA.hRecoChZg->DrawCopy("e same");

  TLegend *leg6 = new TLegend(0.419598,0.5073333,0.9572864,0.7033333,NULL,"brNDC");
  easyLeg(leg6,"Charged sub-jet");
  leg6->AddEntry(ppLA.hGenChZg,"Truth chg'd particle","l");
  leg6->AddEntry(ppLA.hRecoChZg,"Reco track","pl");
  leg6->Draw();
  drawText(Form("p_{T}^{jet}: %d - %d GeV,   |#eta^{jet}| < 1.2",ptLow,ptHigh),0.25,0.87,1,15);
  drawText("p_{T}^{track} > 4 GeV/c",0.25,0.83,1,15);
  drawText("Subjet #theta > 0.1",0.25,0.74,2,20);

  TCanvas* c6=  new TCanvas("c6","",1200,400);
  c6->Divide(3,1);
  c6->cd(1);
  handsomeTH1(aaLA[6].hGenChZg,1);
  handsomeTH1(aaLA[6].hRecoChZg,1);
  aaLA[6].hGenChZg->SetXTitle("z_{g} = min(p_{T}^{1},p_{T}^{2})/(p_{T}^{1}+p_{T}^{2})");
  cleverRange(aaLA[6].hGenChZg,1.6);
  aaLA[6].hGenChZg->SetNdivisions(505);
  aaLA[6].hGenChZg->DrawCopy("hist");
  aaLA[6].hRecoChZg->DrawCopy("e same");
  drawText("60-80%", 0.6, 0.8,1,25);

  c6->cd(2);
  handsomeTH1(aaLA[3].hGenChZg,1);
  handsomeTH1(aaLA[3].hRecoChZg,1);
  aaLA[3].hGenChZg->SetXTitle("z_{g} = min(p_{T}^{1},p_{T}^{2})/(p_{T}^{1}+p_{T}^{2})");
  cleverRange(aaLA[3].hGenChZg,1.6);
  aaLA[3].hGenChZg->SetNdivisions(505);
  aaLA[3].hGenChZg->DrawCopy("hist");
  aaLA[3].hRecoChZg->DrawCopy("e same");
  drawText("30-40%", 0.6, 0.8,1,25);

  c6->cd(3);
  handsomeTH1(aaLA[0].hGenChZg,1);
  handsomeTH1(aaLA[0].hRecoChZg,1);
  aaLA[0].hGenChZg->SetXTitle("z_{g} = min(p_{T}^{1},p_{T}^{2})/(p_{T}^{1}+p_{T}^{2})");
  cleverRange(aaLA[0].hGenChZg,1.6);
  aaLA[0].hGenChZg->SetNdivisions(505);
  aaLA[0].hGenChZg->DrawCopy("hist");
  aaLA[0].hRecoChZg->DrawCopy("e same");
  drawText("0-10%", 0.6, 0.8,1,25);
  
}


