#include "getSdHists.C"
/*
  TH1D* hEffDphi[10];
  TH1D* hEffDrap[10];
*/
void drawSoftDrop() { 

  TString ptCut = "genPt>150 && genPt<250" ; 
  sdVariable ppSd = getSdHists("pp","ntuples/jetSubstructure_output_user.mphipps.12075082.EXT0._000128.DAOD_HION9.AOD.pool.root", 0, ptCut );
  sdVariable pbpbSd[7];
  for ( int icent = 0 ; icent<=6 ; icent++) {
    pbpbSd[icent] = getSdHists(Form("pbpb%d",icent),"ntuples/jetSubstructure_output_DAOD_HION9.11573635._000058.pool.root.1", icent, ptCut ) ;
  }
  TCanvas* c1=  new TCanvas("c1","",1000,500);
  c1->Divide(2,1);
  c1->cd(1);
  handsomeTH1(ppSd.hEffDphi,1);
  handsomeTH1(pbpbSd[6].hEffDphi);
  handsomeTH1(pbpbSd[0].hEffDphi,2);
  ppSd.hEffDphi->SetXTitle("#Delta#phi of track");
  ppSd.hEffDphi->SetYTitle("Efficiency");
  ppSd.hEffDphi->SetAxisRange(0,1.4,"Y");
  ppSd.hEffDphi->SetNdivisions(505);
  ppSd.hEffDphi->Draw("hist");
  pbpbSd[6].hEffDphi->Draw("same e"); 
  pbpbSd[0].hEffDphi->Draw("same e"); 
  TLegend *leg1= new TLegend(0.2672428,0.2089151,0.9999582,0.4709989,NULL,"brNDC");
  easyLeg(leg1,"Tracks in #DeltaR <1.0 cone");
  leg1->AddEntry( ppSd.hEffDphi, "PYTHIA","l");
  leg1->AddEntry( pbpbSd[6].hEffDphi, "+ PbPb 70-80%%","p");
  leg1->AddEntry( pbpbSd[0].hEffDphi, "+ PbPb 0-10%%","p");
  leg1->Draw();
  c1->cd(2);
  handsomeTH1(ppSd.hEffDrap,1);
  handsomeTH1(pbpbSd[6].hEffDrap);
  handsomeTH1(pbpbSd[0].hEffDrap,2);
  ppSd.hEffDrap->SetXTitle("#Deltay  of track");
  ppSd.hEffDrap->SetYTitle("Efficiency");
  ppSd.hEffDrap->SetAxisRange(0,1.2,"Y");
  ppSd.hEffDrap->SetNdivisions(505);
  ppSd.hEffDrap->Draw("hist");
  pbpbSd[6].hEffDrap->Draw("same e"); 
  pbpbSd[0].hEffDrap->Draw("same e"); 
  

}
