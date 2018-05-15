{
//=========Macro generated from canvas: cleg2/
//=========  (Wed Apr 25 13:50:30 2018) by ROOT version5.34/34
   TCanvas *cleg2 = new TCanvas("cleg2", "",1205,45,200,602);
   gStyle->SetOptStat(0);
   cleg2->Range(0,0,1,1);
   cleg2->SetFillColor(0);
   cleg2->SetBorderMode(0);
   cleg2->SetBorderSize(0);
   cleg2->SetTickx(1);
   cleg2->SetTicky(1);
   cleg2->SetLeftMargin(0.17);
   cleg2->SetRightMargin(0.08);
   cleg2->SetTopMargin(0.05);
   cleg2->SetBottomMargin(0.15);
   cleg2->SetFrameLineColor(0);
   cleg2->SetFrameBorderMode(0);
   
   TLegend *leg = new TLegend(0,0.7058065,1,1,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.1);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("NULL","Systematics","h");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("sys_finalPlus_pp_ix6","Total","l");
   entry->SetLineColor(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("sysUnf_kSample0_icent0_ix6_reweight00_reweight00varP50percent","Unfolding","l");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#cc00cc");
   entry->SetLineColor(ci);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("sys_jes_plus_pp_ix6","JES","l");

   ci = TColor::GetColor("#3399ff");
   entry->SetLineColor(ci);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("kSample0_icent0_ix6_nSys100","JER","l");

   ci = TColor::GetColor("#0000ff");
   entry->SetLineColor(ci);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("kSample0_icent0_ix6_nSys210","JMS","l");

   ci = TColor::GetColor("#00ff00");
   entry->SetLineColor(ci);
   entry->SetLineStyle(7);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("kSample0_icent0_ix6_nSys200","JMR","l");

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(7);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   cleg2->Modified();
   cleg2->cd();
   cleg2->SetSelected(cleg2);
}
