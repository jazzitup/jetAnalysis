#include "getSdHists.C"
/*
  TH1D* hEffDphi[10];
  TH1D* hEffDrap[10];
*/
void drawSoftDrop(int ptLow=150, int ptHigh=250) { 

  TString ptCut = Form("genPt>%d && genPt<%d",ptLow, ptHigh) ; 
  sdVariable pp = getSdHists("pp","ntuples/jetSubstructure_output_user.mphipps.12075082.EXT0._000128.DAOD_HION9.AOD.pool.root", 0, ptCut );
  sdVariable aa[7];
  for ( int icent = 0 ; icent<=6 ; icent++) {
    aa[icent] = getSdHists(Form("pbpb%d",icent),"ntuples/jetSubstructure_output_DAOD_HION9.11573635._000058.pool.root.1", icent, ptCut ) ;
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
  pp.hEffDphi->Draw("hist");
  aa[6].hEffDphi->Draw("same e"); 
  aa[0].hEffDphi->Draw("same e"); 
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
  pp.hEffDrap->Draw("hist");
  aa[6].hEffDrap->Draw("same e"); 
  aa[0].hEffDrap->Draw("same e"); 
  
  // Calorimeter subjets
  TCanvas* c2pp=  new TCanvas("c2pp","",400,400);
  handsomeTH1(pp.hGenTheta,1);
  handsomeTH1(pp.hRecoTheta,1);
  pp.hGenTheta->SetXTitle("#theta between subjets");
  pp.hGenTheta->Draw("hist");
  pp.hRecoTheta->Draw("e same");

  TLegend *leg2= new TLegend(0.5036546,0.3894737,1,0.6347368,NULL,"brNDC");
  easyLeg(leg2,"Full subjets (PYTHIA)");
  leg2->AddEntry(pp.hGenTheta,"Truth","l");
  leg2->AddEntry(pp.hRecoTheta,"Reco","pl");
  leg2->Draw();
  
  drawText(Form("p_{T}^{jet}: %d - %d GeV,   |#eta^{jet}| < 1.2",ptLow,ptHigh),0.35,0.8,1,15);
  drawText("p_{T}^{track} > 4 GeV/c",0.35,0.7,1,15);
  
  TCanvas* c2=  new TCanvas("c2","",1200,400);
  c2->Divide(3,1);
  c2->cd(1);
  handsomeTH1(aa[6].hGenTheta,2,1,24);
  handsomeTH1(aa[6].hRecoTheta,2,1,24);
  aa[6].hGenTheta->SetXTitle("#theta between subjets");
  aa[6].hGenTheta->Draw("hist");
  aa[6].hRecoTheta->Draw("e same");
  drawText("60-80%", 0.3, 0.8,1,25);
  TLegend *leg3= new TLegend(0.4662558,0.452381,0.9990587,0.7163265,NULL,"brNDC");
  easyLeg(leg3,"PbPb MC");
  leg3->AddEntry(aa[6].hGenTheta,"Truth","l");
  leg3->AddEntry(aa[6].hRecoTheta,"Reco","pl");
  leg3->Draw();

  c2->cd(2);
  handsomeTH1(aa[3].hGenTheta,2,1,20);
  handsomeTH1(aa[3].hRecoTheta,2,1,20);
  aa[3].hGenTheta->SetXTitle("#theta between subjets");
  aa[3].hGenTheta->Draw("hist");
  aa[3].hRecoTheta->Draw("e same");
  drawText("30-40%", 0.3, 0.8,1,25);

  c2->cd(3);
  handsomeTH1(aa[0].hGenTheta,2);
  handsomeTH1(aa[0].hRecoTheta,2);
  aa[0].hGenTheta->SetXTitle("#theta between subjets");
  aa[0].hGenTheta->Draw("hist");
  aa[0].hRecoTheta->Draw("e same");
  drawText("0-10%", 0.3, 0.8,1,25);


  // theta vs charged theta
  TCanvas* c3pp=  new TCanvas("c3pp","",400,800);
  c3pp->Divide(1,2); 
  c3pp->cd(1);
  handsomeTH1(pp.hGenChTheta,1);
  handsomeTH1(pp.hRecoChTheta,1);
  pp.hGenChTheta->SetXTitle("#theta between subjets");
  pp.hGenChTheta->Draw("hist");
  pp.hRecoChTheta->Draw("e same");

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
  aa[6].hGenChTheta->Draw("hist");
  aa[6].hRecoChTheta->Draw("e same");
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
  aa[3].hGenChTheta->Draw("hist");
  aa[3].hRecoChTheta->Draw("e same");
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
  aa[0].hGenChTheta->Draw("hist");
  aa[0].hRecoChTheta->Draw("e same");
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
  pp.hGenTheta->Draw("hist");
  pp.hGenChTheta->Draw("e same");

  TLegend* leg5 = new TLegend(0.3036546,0.3894737,0.9,0.6347368,NULL,"brNDC");
  easyLeg(leg5,"PYTHIA MC");
  leg5->AddEntry(pp.hGenTheta, "Full particle subjets","l");
  leg5->AddEntry(pp.hGenChTheta, "Chg'd particle subjets");
  leg5->Draw();
  drawText(Form("p_{T}^{jet}: %d - %d GeV,   |#eta^{jet}| < 1.2",ptLow,ptHigh),0.35,0.8,1,15);
  drawText("p_{T}^{track} > 4 GeV/c",0.35,0.7,1,15);

  c4pp->cd(2);
  ppRatio = (TH1D*)pp.hGenChTheta->Clone("ppRatio");
  ppRatio->Divide(pp.hGenTheta);
  ppRatio->SetAxisRange(0,2,"Y");
  ppRatio->SetYTitle("Track/Calo");
  ppRatio->DrawCopy();
  jumSun(0,1,1,1);  
  

  // Bin migration effect?
  
}
