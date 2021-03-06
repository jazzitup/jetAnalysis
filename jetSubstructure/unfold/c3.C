{
//=========Macro generated from canvas: c3/
//=========  (Fri May 11 21:30:50 2018) by ROOT version5.34/34
   TCanvas *c3 = new TCanvas("c3", "",772,83,500,500);
   gStyle->SetOptStat(0);
   c3->Range(-0.0544,-0.0050625,0.2656,0.0286875);
   c3->SetFillColor(0);
   c3->SetBorderMode(0);
   c3->SetBorderSize(0);
   c3->SetTickx(1);
   c3->SetTicky(1);
   c3->SetLeftMargin(0.17);
   c3->SetRightMargin(0.08);
   c3->SetTopMargin(0.05);
   c3->SetBottomMargin(0.15);
   c3->SetFrameLineColor(0);
   c3->SetFrameBorderMode(0);
   c3->SetFrameLineColor(0);
   c3->SetFrameBorderMode(0);
   Double_t xAxis4[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hr_ix5 = new TH1D("hr_ix5","",9, xAxis4);
   hr_ix5->SetBinContent(1,-100);
   hr_ix5->SetBinContent(2,0.009926599);
   hr_ix5->SetBinContent(3,0.009933154);
   hr_ix5->SetBinContent(4,0.01026592);
   hr_ix5->SetBinContent(5,0.01052641);
   hr_ix5->SetBinContent(6,0.01097478);
   hr_ix5->SetBinContent(7,0.01151339);
   hr_ix5->SetBinContent(8,0.01216029);
   hr_ix5->SetBinContent(9,0.01221219);
   hr_ix5->SetBinError(1,100);
   hr_ix5->SetBinError(2,0.0002628409);
   hr_ix5->SetBinError(3,5.0938e-05);
   hr_ix5->SetBinError(4,2.577408e-05);
   hr_ix5->SetBinError(5,2.00169e-05);
   hr_ix5->SetBinError(6,2.025058e-05);
   hr_ix5->SetBinError(7,2.490398e-05);
   hr_ix5->SetBinError(8,3.073035e-05);
   hr_ix5->SetBinError(9,0.0001051441);
   hr_ix5->SetMinimum(0);
   hr_ix5->SetMaximum(0.027);
   hr_ix5->SetEntries(0.9982505);
   hr_ix5->SetStats(0);
   hr_ix5->SetLineStyle(0);
   hr_ix5->SetMarkerStyle(20);
   hr_ix5->GetXaxis()->SetTitle("(m/p_{T})_{Truth}");
   hr_ix5->GetXaxis()->SetRange(2,8);
   hr_ix5->GetXaxis()->CenterTitle(true);
   hr_ix5->GetXaxis()->SetNdivisions(505);
   hr_ix5->GetXaxis()->SetLabelFont(42);
   hr_ix5->GetXaxis()->SetLabelOffset(0.01);
   hr_ix5->GetXaxis()->SetLabelSize(0.045);
   hr_ix5->GetXaxis()->SetTitleSize(0.055);
   hr_ix5->GetXaxis()->SetTitleOffset(1.3);
   hr_ix5->GetXaxis()->SetTitleFont(42);
   hr_ix5->GetYaxis()->SetTitle("#sigma[(m/p_{T})^{2}_{Reco}]");
   hr_ix5->GetYaxis()->CenterTitle(true);
   hr_ix5->GetYaxis()->SetNdivisions(505);
   hr_ix5->GetYaxis()->SetLabelFont(42);
   hr_ix5->GetYaxis()->SetLabelOffset(0.01);
   hr_ix5->GetYaxis()->SetLabelSize(0.045);
   hr_ix5->GetYaxis()->SetTitleSize(0.055);
   hr_ix5->GetYaxis()->SetTitleOffset(1.4);
   hr_ix5->GetYaxis()->SetTitleFont(42);
   hr_ix5->GetZaxis()->SetLabelFont(42);
   hr_ix5->GetZaxis()->SetLabelSize(0.045);
   hr_ix5->GetZaxis()->SetTitleSize(0.035);
   hr_ix5->GetZaxis()->SetTitleFont(42);
   hr_ix5->Draw("");
   Double_t xAxis5[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hr_ix7 = new TH1D("hr_ix7","",9, xAxis5);
   hr_ix7->SetBinContent(1,-100);
   hr_ix7->SetBinContent(2,0.006384215);
   hr_ix7->SetBinContent(3,0.006703439);
   hr_ix7->SetBinContent(4,0.006983545);
   hr_ix7->SetBinContent(5,0.007381424);
   hr_ix7->SetBinContent(6,0.007927684);
   hr_ix7->SetBinContent(7,0.008547881);
   hr_ix7->SetBinContent(8,0.008986825);
   hr_ix7->SetBinContent(9,0.009524486);
   hr_ix7->SetBinError(1,100);
   hr_ix7->SetBinError(2,0.0001123366);
   hr_ix7->SetBinError(3,2.193737e-05);
   hr_ix7->SetBinError(4,1.342878e-05);
   hr_ix7->SetBinError(5,1.30683e-05);
   hr_ix7->SetBinError(6,1.69667e-05);
   hr_ix7->SetBinError(7,2.655951e-05);
   hr_ix7->SetBinError(8,3.860133e-05);
   hr_ix7->SetBinError(9,0.0001819669);
   hr_ix7->SetMinimum(0);
   hr_ix7->SetMaximum(0.027);
   hr_ix7->SetEntries(0.9987516);
   hr_ix7->SetStats(0);
   hr_ix7->SetLineColor(2);
   hr_ix7->SetLineStyle(0);
   hr_ix7->SetMarkerColor(2);
   hr_ix7->SetMarkerStyle(25);
   hr_ix7->GetXaxis()->SetTitle("(m/p_{T})_{Truth}");
   hr_ix7->GetXaxis()->SetRange(2,8);
   hr_ix7->GetXaxis()->CenterTitle(true);
   hr_ix7->GetXaxis()->SetNdivisions(505);
   hr_ix7->GetXaxis()->SetLabelFont(42);
   hr_ix7->GetXaxis()->SetLabelOffset(0.01);
   hr_ix7->GetXaxis()->SetLabelSize(0.045);
   hr_ix7->GetXaxis()->SetTitleSize(0.055);
   hr_ix7->GetXaxis()->SetTitleOffset(1.3);
   hr_ix7->GetXaxis()->SetTitleFont(42);
   hr_ix7->GetYaxis()->SetTitle("#sigma[(m/p_{T})^{2}_{Reco}]");
   hr_ix7->GetYaxis()->CenterTitle(true);
   hr_ix7->GetYaxis()->SetNdivisions(505);
   hr_ix7->GetYaxis()->SetLabelFont(42);
   hr_ix7->GetYaxis()->SetLabelOffset(0.01);
   hr_ix7->GetYaxis()->SetLabelSize(0.045);
   hr_ix7->GetYaxis()->SetTitleSize(0.055);
   hr_ix7->GetYaxis()->SetTitleOffset(1.4);
   hr_ix7->GetYaxis()->SetTitleFont(42);
   hr_ix7->GetZaxis()->SetLabelFont(42);
   hr_ix7->GetZaxis()->SetLabelSize(0.045);
   hr_ix7->GetZaxis()->SetTitleSize(0.035);
   hr_ix7->GetZaxis()->SetTitleFont(42);
   hr_ix7->Draw("same");
   Double_t xAxis6[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hr_ix11 = new TH1D("hr_ix11","",9, xAxis6);
   hr_ix11->SetBinContent(1,-100);
   hr_ix11->SetBinContent(2,0.00319866);
   hr_ix11->SetBinContent(3,0.003335414);
   hr_ix11->SetBinContent(4,0.003662442);
   hr_ix11->SetBinContent(5,0.004061353);
   hr_ix11->SetBinContent(6,0.00433539);
   hr_ix11->SetBinContent(7,0.004558163);
   hr_ix11->SetBinContent(8,0.0048885);
   hr_ix11->SetBinContent(9,0.00628252);
   hr_ix11->SetBinError(1,100);
   hr_ix11->SetBinError(2,1.005238e-05);
   hr_ix11->SetBinError(3,3.262282e-06);
   hr_ix11->SetBinError(4,3.636877e-06);
   hr_ix11->SetBinError(5,6.177047e-06);
   hr_ix11->SetBinError(6,1.082544e-05);
   hr_ix11->SetBinError(7,1.885225e-05);
   hr_ix11->SetBinError(8,3.076356e-05);
   hr_ix11->SetBinError(9,0.0004195778);
   hr_ix11->SetMinimum(0);
   hr_ix11->SetMaximum(0.027);
   hr_ix11->SetEntries(0.9993137);
   hr_ix11->SetStats(0);
   hr_ix11->SetLineColor(4);
   hr_ix11->SetLineStyle(0);
   hr_ix11->SetMarkerColor(4);
   hr_ix11->SetMarkerStyle(28);
   hr_ix11->GetXaxis()->SetTitle("(m/p_{T})_{Truth}");
   hr_ix11->GetXaxis()->SetRange(2,8);
   hr_ix11->GetXaxis()->CenterTitle(true);
   hr_ix11->GetXaxis()->SetNdivisions(505);
   hr_ix11->GetXaxis()->SetLabelFont(42);
   hr_ix11->GetXaxis()->SetLabelOffset(0.01);
   hr_ix11->GetXaxis()->SetLabelSize(0.045);
   hr_ix11->GetXaxis()->SetTitleSize(0.055);
   hr_ix11->GetXaxis()->SetTitleOffset(1.3);
   hr_ix11->GetXaxis()->SetTitleFont(42);
   hr_ix11->GetYaxis()->SetTitle("#sigma[(m/p_{T})^{2}_{Reco}]");
   hr_ix11->GetYaxis()->CenterTitle(true);
   hr_ix11->GetYaxis()->SetNdivisions(505);
   hr_ix11->GetYaxis()->SetLabelFont(42);
   hr_ix11->GetYaxis()->SetLabelOffset(0.01);
   hr_ix11->GetYaxis()->SetLabelSize(0.045);
   hr_ix11->GetYaxis()->SetTitleSize(0.055);
   hr_ix11->GetYaxis()->SetTitleOffset(1.4);
   hr_ix11->GetYaxis()->SetTitleFont(42);
   hr_ix11->GetZaxis()->SetLabelFont(42);
   hr_ix11->GetZaxis()->SetLabelSize(0.045);
   hr_ix11->GetZaxis()->SetTitleSize(0.035);
   hr_ix11->GetZaxis()->SetTitleFont(42);
   hr_ix11->Draw("same");
   TLatex *   tex = new TLatex(0.23,0.88,"ATLAS");
tex->SetNDC();
   tex->SetTextFont(72);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.39,0.88,"Simulation");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.23,0.82,"#sqrt{#font[12]{s}} = 5.02 TeV");
tex->SetNDC();
   tex->SetTextFont(43);
   tex->SetTextSize(25);
   tex->Draw();
      tex = new TLatex(0.23,0.76,"PbPb 0-10%");
tex->SetNDC();
   tex->SetTextFont(43);
   tex->SetTextSize(25);
   tex->Draw();
   
   TLegend *leg = new TLegend(0.2108434,0.56,0.6084337,0.7347368,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("NULL","Jet p_{T}","h");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("hr_ix5","100 < p_{T} < 125 GeV","pl");
   entry->SetLineColor(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("hr_ix7","158 < p_{T} < 199 GeV","pl");
   entry->SetLineColor(2);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(25);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("hr_ix11","398 < p_{T} < 500 GeV","pl");
   entry->SetLineColor(4);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(4);
   entry->SetMarkerStyle(28);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   c3->Modified();
   c3->cd();
   c3->SetSelected(c3);
}
