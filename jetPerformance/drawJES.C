#include "drawBasicPerf.C"
void drawJES() {
  Jes ppJes = drawBasicPerf(10,0,0);// pp 
  Jes pbpbJes[10];
  for ( int icent = 0 ; icent <=6 ; icent++) { 
    pbpbJes[icent] = drawBasicPerf(10,icent,1); // pbpb
  }
  
  TCanvas* cj1 = new TCanvas("cj1","",500,800);
  cj1->Divide(1,2);
  cj1->cd(1);
  handsomeTH1(ppJes.hScale[0],1);
  ppJes.hScale[0]->SetAxisRange(-0.22,0.32,"Y");
  ppJes.hScale[0]->SetAxisRange(51,500,"X");
  ppJes.hScale[0]->SetTitle("");
  ppJes.hScale[0]->SetXTitle("p_{T}^{Truth} (GeV/c)");
  ppJes.hScale[0]->SetYTitle("<p_{T}^Reco/p_{T}^{Truth}> -1");
  ppJes.hScale[0]->Draw("hist");
  int color[10] = {2,4,8,6,41,8,5};
  for ( int icent = 0 ; icent <=6 ; icent++) {
    handsomeTH1(pbpbJes[icent].hScale[0], color[icent]);
    pbpbJes[icent].hScale[0]->Draw("same");
  }
  jumSun(50,0,500,0);
  cj1->cd(2);
  handsomeTH1(ppJes.hRes[0],1);
  ppJes.hRes[0]->SetAxisRange(0,0.5,"Y");
  ppJes.hRes[0]->SetAxisRange(51,500,"X");
  ppJes.hRes[0]->SetTitle("");
  ppJes.hRes[0]->SetXTitle("p_{T}^{Truth} (GeV/c)");
  ppJes.hRes[0]->SetYTitle("Resolution");
  for ( int icent = 0 ; icent <=6 ; icent++) {
    handsomeTH1(pbpbJes[icent].hRes[0], color[icent]);

    TF1* f = new TF1(Form("f_%d",icent),"[0] + [1]/sqrt(x) + [2]/x");
    pbpbJes[icent].hRes[0]->Fit(f);
    pbpbJes[icent].hRes[0]->GetFunction(Form("f_%d",icent))->SetLineColor(color[icent]);
    pbpbJes[icent].hRes[0]->GetFunction(Form("f_%d",icent))->SetLineStyle(2);
    //    f->DrawCopy();
  }

  ppJes.hRes[0]->Draw("hist");
  for ( int icent = 0 ; icent <=6 ; icent++) {
    pbpbJes[icent].hRes[0]->Draw("same");
  }


  gPad->SetLogx();
  TLegend *leg1 = new TLegend(0.4673663,0.5605442,0.9999478,0.914966,NULL,"brNDC");

  easyLeg(leg1,"R=1.0, HION9");
  leg1->AddEntry(pbpbJes[0].hRes[0],"0-10%");
  leg1->AddEntry(pbpbJes[1].hRes[0],"10-20%");
  leg1->AddEntry(pbpbJes[2].hRes[0],"20-30%");
  leg1->AddEntry(pbpbJes[3].hRes[0],"30-40%");
  leg1->AddEntry(pbpbJes[4].hRes[0],"40-50%");
  leg1->AddEntry(pbpbJes[5].hRes[0],"50-60%");
  leg1->AddEntry(pbpbJes[6].hRes[0],"60-80%");
  leg1->AddEntry(ppJes.hRes[0],"PYTHIA only");
  leg1->Draw();
  cj1->SaveAs("cj1.png");

  


  
}
