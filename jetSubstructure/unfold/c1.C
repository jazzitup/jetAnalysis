void c1()
{
//=========Macro generated from canvas: c1/
//=========  (Fri Apr 27 17:23:39 2018) by ROOT version6.10/08
   TCanvas *c1 = new TCanvas("c1", "",4,45,1156,660);
   gStyle->SetOptStat(0);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(0);
   c1->SetTickx(1);
   c1->SetTicky(1);
   c1->SetLeftMargin(0.17);
   c1->SetRightMargin(0.08);
   c1->SetTopMargin(0.05);
   c1->SetBottomMargin(0.15);
   c1->SetFrameLineColor(0);
   c1->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: p_0_0
   TPad *p_0_0 = new TPad("p_0_0", "p_0_0",0,0.692228,0.2334152,1);
   p_0_0->Draw();
   p_0_0->cd();
   p_0_0->Range(-0.1292308,0,0.24,0.01392553);
   p_0_0->SetFillColor(0);
   p_0_0->SetBorderMode(0);
   p_0_0->SetBorderSize(0);
   p_0_0->SetTickx(1);
   p_0_0->SetTicky(1);
   p_0_0->SetLeftMargin(0.35);
   p_0_0->SetRightMargin(0);
   p_0_0->SetTopMargin(0.05);
   p_0_0->SetBottomMargin(0);
   p_0_0->SetFrameLineColor(0);
   p_0_0->SetFrameBorderMode(0);
   p_0_0->SetFrameLineColor(0);
   p_0_0->SetFrameBorderMode(0);
   Double_t xAxis1[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt6__1 = new TH1D("hPbPbUnfSq_ipt6__1","",9, xAxis1);
   hPbPbUnfSq_ipt6__1->SetBinContent(2,4.784206e-05);
   hPbPbUnfSq_ipt6__1->SetBinContent(3,0.001395007);
   hPbPbUnfSq_ipt6__1->SetBinContent(4,0.004857215);
   hPbPbUnfSq_ipt6__1->SetBinContent(5,0.006614628);
   hPbPbUnfSq_ipt6__1->SetBinContent(6,0.005569402);
   hPbPbUnfSq_ipt6__1->SetBinContent(7,0.003099673);
   hPbPbUnfSq_ipt6__1->SetBinContent(8,0.0009135757);
   hPbPbUnfSq_ipt6__1->SetBinContent(9,6.15062e-05);
   hPbPbUnfSq_ipt6__1->SetBinError(2,4.515963e-07);
   hPbPbUnfSq_ipt6__1->SetBinError(3,8.329669e-06);
   hPbPbUnfSq_ipt6__1->SetBinError(4,2.081526e-05);
   hPbPbUnfSq_ipt6__1->SetBinError(5,2.156366e-05);
   hPbPbUnfSq_ipt6__1->SetBinError(6,1.892707e-05);
   hPbPbUnfSq_ipt6__1->SetBinError(7,1.307688e-05);
   hPbPbUnfSq_ipt6__1->SetBinError(8,6.618592e-06);
   hPbPbUnfSq_ipt6__1->SetBinError(9,6.94047e-07);
   hPbPbUnfSq_ipt6__1->SetMinimum(0);
   hPbPbUnfSq_ipt6__1->SetMaximum(0.01322926);
   hPbPbUnfSq_ipt6__1->SetEntries(330812.9);
   hPbPbUnfSq_ipt6__1->SetStats(0);
   hPbPbUnfSq_ipt6__1->SetLineStyle(0);
   hPbPbUnfSq_ipt6__1->SetMarkerStyle(20);
   hPbPbUnfSq_ipt6__1->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt6__1->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt6__1->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt6__1->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt6__1->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt6__1->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt6__1->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt6__1->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt6__1->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt6__1->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt6__1->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt6__1->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt6__1->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt6__1->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt6__1->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt6__1->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt6__1->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt6__1->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt6__1->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt6__1->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt6__1->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt6__1->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt6__1->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt6__1->Draw("");
   TBox *box = new TBox(0,4.784206e-05,0.03,5.807703e-05);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.03,0.001395007,0.06,0.001585169);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.06,0.004857215,0.09,0.005327759);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.09,0.006614628,0.12,0.007152242);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.12,0.005569402,0.15,0.006124798);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.15,0.003099673,0.18,0.003562138);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.18,0.0009135757,0.24,0.001194984);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0,3.764328e-05,0.03,4.784206e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.03,0.001205536,0.06,0.001395007);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.06,0.004384554,0.09,0.004857215);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.09,0.006077574,0.12,0.006614628);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.12,0.005039218,0.15,0.005569402);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.15,0.002660658,0.18,0.003099673);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.18,0.0006474832,0.24,0.0009135757);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   Double_t xAxis2[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt6__2 = new TH1D("hPbPbUnfSq_ipt6__2","",9, xAxis2);
   hPbPbUnfSq_ipt6__2->SetBinContent(2,4.784206e-05);
   hPbPbUnfSq_ipt6__2->SetBinContent(3,0.001395007);
   hPbPbUnfSq_ipt6__2->SetBinContent(4,0.004857215);
   hPbPbUnfSq_ipt6__2->SetBinContent(5,0.006614628);
   hPbPbUnfSq_ipt6__2->SetBinContent(6,0.005569402);
   hPbPbUnfSq_ipt6__2->SetBinContent(7,0.003099673);
   hPbPbUnfSq_ipt6__2->SetBinContent(8,0.0009135757);
   hPbPbUnfSq_ipt6__2->SetBinContent(9,6.15062e-05);
   hPbPbUnfSq_ipt6__2->SetBinError(2,4.515963e-07);
   hPbPbUnfSq_ipt6__2->SetBinError(3,8.329669e-06);
   hPbPbUnfSq_ipt6__2->SetBinError(4,2.081526e-05);
   hPbPbUnfSq_ipt6__2->SetBinError(5,2.156366e-05);
   hPbPbUnfSq_ipt6__2->SetBinError(6,1.892707e-05);
   hPbPbUnfSq_ipt6__2->SetBinError(7,1.307688e-05);
   hPbPbUnfSq_ipt6__2->SetBinError(8,6.618592e-06);
   hPbPbUnfSq_ipt6__2->SetBinError(9,6.94047e-07);
   hPbPbUnfSq_ipt6__2->SetMinimum(0);
   hPbPbUnfSq_ipt6__2->SetMaximum(0.01322926);
   hPbPbUnfSq_ipt6__2->SetEntries(330812.9);
   hPbPbUnfSq_ipt6__2->SetStats(0);
   hPbPbUnfSq_ipt6__2->SetLineStyle(0);
   hPbPbUnfSq_ipt6__2->SetMarkerStyle(20);
   hPbPbUnfSq_ipt6__2->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt6__2->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt6__2->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt6__2->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt6__2->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt6__2->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt6__2->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt6__2->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt6__2->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt6__2->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt6__2->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt6__2->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt6__2->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt6__2->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt6__2->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt6__2->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt6__2->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt6__2->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt6__2->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt6__2->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt6__2->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt6__2->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt6__2->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt6__2->Draw("same");
   TLatex *   tex = new TLatex(0.33,0.84,"ATLAS");
tex->SetNDC();
   tex->SetTextFont(72);
   tex->SetTextSize(0.11);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.55,0.84,"Internal");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.11);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.33,0.73,"PbPb 0-10%");
tex->SetNDC();
   tex->SetTextFont(43);
   tex->SetTextSize(20);
   tex->Draw();
      tex = new TLatex(0.33,0.6,"125 < p_{T}^{jet} < 158 GeV");
tex->SetNDC();
   tex->SetTextFont(43);
   tex->SetTextSize(18);
   tex->Draw();
   Double_t xAxis3[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt6_copy__3 = new TH1D("hPbPbUnfSq_ipt6_copy__3","",9, xAxis3);
   hPbPbUnfSq_ipt6_copy__3->SetBinContent(2,4.784206e-05);
   hPbPbUnfSq_ipt6_copy__3->SetBinContent(3,0.001395007);
   hPbPbUnfSq_ipt6_copy__3->SetBinContent(4,0.004857215);
   hPbPbUnfSq_ipt6_copy__3->SetBinContent(5,0.006614628);
   hPbPbUnfSq_ipt6_copy__3->SetBinContent(6,0.005569402);
   hPbPbUnfSq_ipt6_copy__3->SetBinContent(7,0.003099673);
   hPbPbUnfSq_ipt6_copy__3->SetBinContent(8,0.0009135757);
   hPbPbUnfSq_ipt6_copy__3->SetBinContent(9,6.15062e-05);
   hPbPbUnfSq_ipt6_copy__3->SetBinError(2,4.515963e-07);
   hPbPbUnfSq_ipt6_copy__3->SetBinError(3,8.329669e-06);
   hPbPbUnfSq_ipt6_copy__3->SetBinError(4,2.081526e-05);
   hPbPbUnfSq_ipt6_copy__3->SetBinError(5,2.156366e-05);
   hPbPbUnfSq_ipt6_copy__3->SetBinError(6,1.892707e-05);
   hPbPbUnfSq_ipt6_copy__3->SetBinError(7,1.307688e-05);
   hPbPbUnfSq_ipt6_copy__3->SetBinError(8,6.618592e-06);
   hPbPbUnfSq_ipt6_copy__3->SetBinError(9,6.94047e-07);
   hPbPbUnfSq_ipt6_copy__3->SetMinimum(0);
   hPbPbUnfSq_ipt6_copy__3->SetMaximum(0.01322926);
   hPbPbUnfSq_ipt6_copy__3->SetEntries(330812.9);
   hPbPbUnfSq_ipt6_copy__3->SetDirectory(0);
   hPbPbUnfSq_ipt6_copy__3->SetStats(0);
   hPbPbUnfSq_ipt6_copy__3->SetLineStyle(0);
   hPbPbUnfSq_ipt6_copy__3->SetMarkerStyle(20);
   hPbPbUnfSq_ipt6_copy__3->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt6_copy__3->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt6_copy__3->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt6_copy__3->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt6_copy__3->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt6_copy__3->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt6_copy__3->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt6_copy__3->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt6_copy__3->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt6_copy__3->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt6_copy__3->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt6_copy__3->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt6_copy__3->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt6_copy__3->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt6_copy__3->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt6_copy__3->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt6_copy__3->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt6_copy__3->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt6_copy__3->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt6_copy__3->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt6_copy__3->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt6_copy__3->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt6_copy__3->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt6_copy__3->Draw("sameaxis");
   p_0_0->Modified();
   c1->cd();
  
// ------------>Primitives in pad: p_0_1
   TPad *p_0_1 = new TPad("p_0_1", "p_0_1",0,0.3998446,0.2334152,0.692228);
   p_0_1->Draw();
   p_0_1->cd();
   p_0_1->Range(-0.1292308,0,0.24,0.01931589);
   p_0_1->SetFillColor(0);
   p_0_1->SetBorderMode(0);
   p_0_1->SetBorderSize(0);
   p_0_1->SetTickx(1);
   p_0_1->SetTicky(1);
   p_0_1->SetLeftMargin(0.35);
   p_0_1->SetRightMargin(0);
   p_0_1->SetTopMargin(0);
   p_0_1->SetBottomMargin(0);
   p_0_1->SetFrameLineColor(0);
   p_0_1->SetFrameBorderMode(0);
   p_0_1->SetFrameLineColor(0);
   p_0_1->SetFrameBorderMode(0);
   Double_t xAxis4[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt6__4 = new TH1D("hPbPbUnfSq_ipt6__4","",9, xAxis4);
   hPbPbUnfSq_ipt6__4->SetBinContent(2,7.645568e-05);
   hPbPbUnfSq_ipt6__4->SetBinContent(3,0.002100511);
   hPbPbUnfSq_ipt6__4->SetBinContent(4,0.006863918);
   hPbPbUnfSq_ipt6__4->SetBinContent(5,0.009657947);
   hPbPbUnfSq_ipt6__4->SetBinContent(6,0.008189627);
   hPbPbUnfSq_ipt6__4->SetBinContent(7,0.004940819);
   hPbPbUnfSq_ipt6__4->SetBinContent(8,0.001618686);
   hPbPbUnfSq_ipt6__4->SetBinContent(9,0.0001204166);
   hPbPbUnfSq_ipt6__4->SetBinError(2,1.889456e-06);
   hPbPbUnfSq_ipt6__4->SetBinError(3,2.716334e-05);
   hPbPbUnfSq_ipt6__4->SetBinError(4,5.697494e-05);
   hPbPbUnfSq_ipt6__4->SetBinError(5,6.572596e-05);
   hPbPbUnfSq_ipt6__4->SetBinError(6,6.301711e-05);
   hPbPbUnfSq_ipt6__4->SetBinError(7,4.983191e-05);
   hPbPbUnfSq_ipt6__4->SetBinError(8,2.668686e-05);
   hPbPbUnfSq_ipt6__4->SetBinError(9,3.925505e-06);
   hPbPbUnfSq_ipt6__4->SetMinimum(0);
   hPbPbUnfSq_ipt6__4->SetMaximum(0.01931589);
   hPbPbUnfSq_ipt6__4->SetEntries(70550.09);
   hPbPbUnfSq_ipt6__4->SetStats(0);
   hPbPbUnfSq_ipt6__4->SetLineStyle(0);
   hPbPbUnfSq_ipt6__4->SetMarkerStyle(20);
   hPbPbUnfSq_ipt6__4->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt6__4->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt6__4->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt6__4->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt6__4->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt6__4->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt6__4->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt6__4->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt6__4->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt6__4->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt6__4->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt6__4->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt6__4->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt6__4->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt6__4->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt6__4->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt6__4->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt6__4->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt6__4->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt6__4->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt6__4->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt6__4->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt6__4->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt6__4->Draw("");
   box = new TBox(0,7.645568e-05,0.03,9.170593e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.03,0.002100511,0.06,0.002381066);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.06,0.006863918,0.09,0.007566402);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.09,0.009657947,0.12,0.0105284);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.12,0.008189627,0.15,0.009112448);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.15,0.004940819,0.18,0.005852906);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.18,0.001618686,0.24,0.002090866);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0,5.993274e-05,0.03,7.645568e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.03,0.001819319,0.06,0.002100511);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.06,0.006181412,0.09,0.006863918);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.09,0.008822554,0.12,0.009657947);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.12,0.007306441,0.15,0.008189627);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.15,0.004045482,0.18,0.004940819);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.18,0.001173374,0.24,0.001618686);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   Double_t xAxis5[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt6__5 = new TH1D("hPbPbUnfSq_ipt6__5","",9, xAxis5);
   hPbPbUnfSq_ipt6__5->SetBinContent(2,7.645568e-05);
   hPbPbUnfSq_ipt6__5->SetBinContent(3,0.002100511);
   hPbPbUnfSq_ipt6__5->SetBinContent(4,0.006863918);
   hPbPbUnfSq_ipt6__5->SetBinContent(5,0.009657947);
   hPbPbUnfSq_ipt6__5->SetBinContent(6,0.008189627);
   hPbPbUnfSq_ipt6__5->SetBinContent(7,0.004940819);
   hPbPbUnfSq_ipt6__5->SetBinContent(8,0.001618686);
   hPbPbUnfSq_ipt6__5->SetBinContent(9,0.0001204166);
   hPbPbUnfSq_ipt6__5->SetBinError(2,1.889456e-06);
   hPbPbUnfSq_ipt6__5->SetBinError(3,2.716334e-05);
   hPbPbUnfSq_ipt6__5->SetBinError(4,5.697494e-05);
   hPbPbUnfSq_ipt6__5->SetBinError(5,6.572596e-05);
   hPbPbUnfSq_ipt6__5->SetBinError(6,6.301711e-05);
   hPbPbUnfSq_ipt6__5->SetBinError(7,4.983191e-05);
   hPbPbUnfSq_ipt6__5->SetBinError(8,2.668686e-05);
   hPbPbUnfSq_ipt6__5->SetBinError(9,3.925505e-06);
   hPbPbUnfSq_ipt6__5->SetMinimum(0);
   hPbPbUnfSq_ipt6__5->SetMaximum(0.01931589);
   hPbPbUnfSq_ipt6__5->SetEntries(70550.09);
   hPbPbUnfSq_ipt6__5->SetStats(0);
   hPbPbUnfSq_ipt6__5->SetLineStyle(0);
   hPbPbUnfSq_ipt6__5->SetMarkerStyle(20);
   hPbPbUnfSq_ipt6__5->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt6__5->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt6__5->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt6__5->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt6__5->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt6__5->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt6__5->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt6__5->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt6__5->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt6__5->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt6__5->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt6__5->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt6__5->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt6__5->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt6__5->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt6__5->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt6__5->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt6__5->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt6__5->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt6__5->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt6__5->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt6__5->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt6__5->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt6__5->Draw("same");
      tex = new TLatex(0.33,0.73,"PbPb 30-40%");
tex->SetNDC();
   tex->SetTextFont(43);
   tex->SetTextSize(20);
   tex->Draw();
   Double_t xAxis6[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt6_copy__6 = new TH1D("hPbPbUnfSq_ipt6_copy__6","",9, xAxis6);
   hPbPbUnfSq_ipt6_copy__6->SetBinContent(2,7.645568e-05);
   hPbPbUnfSq_ipt6_copy__6->SetBinContent(3,0.002100511);
   hPbPbUnfSq_ipt6_copy__6->SetBinContent(4,0.006863918);
   hPbPbUnfSq_ipt6_copy__6->SetBinContent(5,0.009657947);
   hPbPbUnfSq_ipt6_copy__6->SetBinContent(6,0.008189627);
   hPbPbUnfSq_ipt6_copy__6->SetBinContent(7,0.004940819);
   hPbPbUnfSq_ipt6_copy__6->SetBinContent(8,0.001618686);
   hPbPbUnfSq_ipt6_copy__6->SetBinContent(9,0.0001204166);
   hPbPbUnfSq_ipt6_copy__6->SetBinError(2,1.889456e-06);
   hPbPbUnfSq_ipt6_copy__6->SetBinError(3,2.716334e-05);
   hPbPbUnfSq_ipt6_copy__6->SetBinError(4,5.697494e-05);
   hPbPbUnfSq_ipt6_copy__6->SetBinError(5,6.572596e-05);
   hPbPbUnfSq_ipt6_copy__6->SetBinError(6,6.301711e-05);
   hPbPbUnfSq_ipt6_copy__6->SetBinError(7,4.983191e-05);
   hPbPbUnfSq_ipt6_copy__6->SetBinError(8,2.668686e-05);
   hPbPbUnfSq_ipt6_copy__6->SetBinError(9,3.925505e-06);
   hPbPbUnfSq_ipt6_copy__6->SetMinimum(0);
   hPbPbUnfSq_ipt6_copy__6->SetMaximum(0.01931589);
   hPbPbUnfSq_ipt6_copy__6->SetEntries(70550.09);
   hPbPbUnfSq_ipt6_copy__6->SetDirectory(0);
   hPbPbUnfSq_ipt6_copy__6->SetStats(0);
   hPbPbUnfSq_ipt6_copy__6->SetLineStyle(0);
   hPbPbUnfSq_ipt6_copy__6->SetMarkerStyle(20);
   hPbPbUnfSq_ipt6_copy__6->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt6_copy__6->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt6_copy__6->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt6_copy__6->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt6_copy__6->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt6_copy__6->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt6_copy__6->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt6_copy__6->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt6_copy__6->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt6_copy__6->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt6_copy__6->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt6_copy__6->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt6_copy__6->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt6_copy__6->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt6_copy__6->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt6_copy__6->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt6_copy__6->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt6_copy__6->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt6_copy__6->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt6_copy__6->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt6_copy__6->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt6_copy__6->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt6_copy__6->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt6_copy__6->Draw("sameaxis");
   p_0_1->Modified();
   c1->cd();
  
// ------------>Primitives in pad: p_0_2
   TPad *p_0_2 = new TPad("p_0_2", "p_0_2",0,0.01,0.2334152,0.3998446);
   p_0_2->Draw();
   p_0_2->cd();
   p_0_2->Range(-0.1292308,-0.008749087,0.24,0.02624726);
   p_0_2->SetFillColor(0);
   p_0_2->SetBorderMode(0);
   p_0_2->SetBorderSize(0);
   p_0_2->SetTickx(1);
   p_0_2->SetTicky(1);
   p_0_2->SetLeftMargin(0.35);
   p_0_2->SetRightMargin(0);
   p_0_2->SetTopMargin(0);
   p_0_2->SetBottomMargin(0.25);
   p_0_2->SetFrameLineColor(0);
   p_0_2->SetFrameBorderMode(0);
   p_0_2->SetFrameLineColor(0);
   p_0_2->SetFrameBorderMode(0);
   Double_t xAxis7[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt6__7 = new TH1D("hPbPbUnfSq_ipt6__7","",9, xAxis7);
   hPbPbUnfSq_ipt6__7->SetBinContent(2,0.0001302606);
   hPbPbUnfSq_ipt6__7->SetBinContent(3,0.002845333);
   hPbPbUnfSq_ipt6__7->SetBinContent(4,0.009270261);
   hPbPbUnfSq_ipt6__7->SetBinContent(5,0.01312363);
   hPbPbUnfSq_ipt6__7->SetBinContent(6,0.01125403);
   hPbPbUnfSq_ipt6__7->SetBinContent(7,0.006639654);
   hPbPbUnfSq_ipt6__7->SetBinContent(8,0.002050129);
   hPbPbUnfSq_ipt6__7->SetBinContent(9,0.0001422945);
   hPbPbUnfSq_ipt6__7->SetBinError(2,1.868656e-05);
   hPbPbUnfSq_ipt6__7->SetBinError(3,8.600715e-05);
   hPbPbUnfSq_ipt6__7->SetBinError(4,0.0001740202);
   hPbPbUnfSq_ipt6__7->SetBinError(5,0.000210833);
   hPbPbUnfSq_ipt6__7->SetBinError(6,0.0002014036);
   hPbPbUnfSq_ipt6__7->SetBinError(7,0.0001663901);
   hPbPbUnfSq_ipt6__7->SetBinError(8,7.966356e-05);
   hPbPbUnfSq_ipt6__7->SetBinError(9,1.017851e-05);
   hPbPbUnfSq_ipt6__7->SetMinimum(0);
   hPbPbUnfSq_ipt6__7->SetMaximum(0.02624726);
   hPbPbUnfSq_ipt6__7->SetEntries(12869.99);
   hPbPbUnfSq_ipt6__7->SetStats(0);
   hPbPbUnfSq_ipt6__7->SetLineStyle(0);
   hPbPbUnfSq_ipt6__7->SetMarkerStyle(20);
   hPbPbUnfSq_ipt6__7->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt6__7->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt6__7->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt6__7->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt6__7->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt6__7->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt6__7->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt6__7->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt6__7->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt6__7->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt6__7->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt6__7->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt6__7->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt6__7->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt6__7->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt6__7->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt6__7->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt6__7->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt6__7->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt6__7->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt6__7->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt6__7->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt6__7->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt6__7->Draw("");
   box = new TBox(0,0.0001302606,0.03,0.0001712469);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.03,0.002845333,0.06,0.003299953);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.06,0.009270261,0.09,0.0102852);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.09,0.01312363,0.12,0.01439789);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.12,0.01125403,0.15,0.01268123);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.15,0.006639654,0.18,0.007758455);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.18,0.002050129,0.24,0.002472909);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0,9.632414e-05,0.03,0.0001302606);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.03,0.002430675,0.06,0.002845333);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.06,0.008299906,0.09,0.009270261);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.09,0.01183727,0.12,0.01312363);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.12,0.009800688,0.15,0.01125403);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.15,0.0055565,0.18,0.006639654);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.18,0.001667321,0.24,0.002050129);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   Double_t xAxis8[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt6__8 = new TH1D("hPbPbUnfSq_ipt6__8","",9, xAxis8);
   hPbPbUnfSq_ipt6__8->SetBinContent(2,0.0001302606);
   hPbPbUnfSq_ipt6__8->SetBinContent(3,0.002845333);
   hPbPbUnfSq_ipt6__8->SetBinContent(4,0.009270261);
   hPbPbUnfSq_ipt6__8->SetBinContent(5,0.01312363);
   hPbPbUnfSq_ipt6__8->SetBinContent(6,0.01125403);
   hPbPbUnfSq_ipt6__8->SetBinContent(7,0.006639654);
   hPbPbUnfSq_ipt6__8->SetBinContent(8,0.002050129);
   hPbPbUnfSq_ipt6__8->SetBinContent(9,0.0001422945);
   hPbPbUnfSq_ipt6__8->SetBinError(2,1.868656e-05);
   hPbPbUnfSq_ipt6__8->SetBinError(3,8.600715e-05);
   hPbPbUnfSq_ipt6__8->SetBinError(4,0.0001740202);
   hPbPbUnfSq_ipt6__8->SetBinError(5,0.000210833);
   hPbPbUnfSq_ipt6__8->SetBinError(6,0.0002014036);
   hPbPbUnfSq_ipt6__8->SetBinError(7,0.0001663901);
   hPbPbUnfSq_ipt6__8->SetBinError(8,7.966356e-05);
   hPbPbUnfSq_ipt6__8->SetBinError(9,1.017851e-05);
   hPbPbUnfSq_ipt6__8->SetMinimum(0);
   hPbPbUnfSq_ipt6__8->SetMaximum(0.02624726);
   hPbPbUnfSq_ipt6__8->SetEntries(12869.99);
   hPbPbUnfSq_ipt6__8->SetStats(0);
   hPbPbUnfSq_ipt6__8->SetLineStyle(0);
   hPbPbUnfSq_ipt6__8->SetMarkerStyle(20);
   hPbPbUnfSq_ipt6__8->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt6__8->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt6__8->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt6__8->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt6__8->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt6__8->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt6__8->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt6__8->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt6__8->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt6__8->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt6__8->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt6__8->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt6__8->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt6__8->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt6__8->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt6__8->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt6__8->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt6__8->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt6__8->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt6__8->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt6__8->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt6__8->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt6__8->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt6__8->Draw("same");
      tex = new TLatex(0.33,0.73,"PbPb 60-80%");
tex->SetNDC();
   tex->SetTextFont(43);
   tex->SetTextSize(20);
   tex->Draw();
   Double_t xAxis9[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt6_copy__9 = new TH1D("hPbPbUnfSq_ipt6_copy__9","",9, xAxis9);
   hPbPbUnfSq_ipt6_copy__9->SetBinContent(2,0.0001302606);
   hPbPbUnfSq_ipt6_copy__9->SetBinContent(3,0.002845333);
   hPbPbUnfSq_ipt6_copy__9->SetBinContent(4,0.009270261);
   hPbPbUnfSq_ipt6_copy__9->SetBinContent(5,0.01312363);
   hPbPbUnfSq_ipt6_copy__9->SetBinContent(6,0.01125403);
   hPbPbUnfSq_ipt6_copy__9->SetBinContent(7,0.006639654);
   hPbPbUnfSq_ipt6_copy__9->SetBinContent(8,0.002050129);
   hPbPbUnfSq_ipt6_copy__9->SetBinContent(9,0.0001422945);
   hPbPbUnfSq_ipt6_copy__9->SetBinError(2,1.868656e-05);
   hPbPbUnfSq_ipt6_copy__9->SetBinError(3,8.600715e-05);
   hPbPbUnfSq_ipt6_copy__9->SetBinError(4,0.0001740202);
   hPbPbUnfSq_ipt6_copy__9->SetBinError(5,0.000210833);
   hPbPbUnfSq_ipt6_copy__9->SetBinError(6,0.0002014036);
   hPbPbUnfSq_ipt6_copy__9->SetBinError(7,0.0001663901);
   hPbPbUnfSq_ipt6_copy__9->SetBinError(8,7.966356e-05);
   hPbPbUnfSq_ipt6_copy__9->SetBinError(9,1.017851e-05);
   hPbPbUnfSq_ipt6_copy__9->SetMinimum(0);
   hPbPbUnfSq_ipt6_copy__9->SetMaximum(0.02624726);
   hPbPbUnfSq_ipt6_copy__9->SetEntries(12869.99);
   hPbPbUnfSq_ipt6_copy__9->SetDirectory(0);
   hPbPbUnfSq_ipt6_copy__9->SetStats(0);
   hPbPbUnfSq_ipt6_copy__9->SetLineStyle(0);
   hPbPbUnfSq_ipt6_copy__9->SetMarkerStyle(20);
   hPbPbUnfSq_ipt6_copy__9->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt6_copy__9->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt6_copy__9->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt6_copy__9->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt6_copy__9->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt6_copy__9->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt6_copy__9->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt6_copy__9->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt6_copy__9->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt6_copy__9->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt6_copy__9->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt6_copy__9->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt6_copy__9->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt6_copy__9->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt6_copy__9->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt6_copy__9->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt6_copy__9->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt6_copy__9->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt6_copy__9->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt6_copy__9->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt6_copy__9->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt6_copy__9->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt6_copy__9->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt6_copy__9->Draw("sameaxis");
   p_0_2->Modified();
   c1->cd();
  
// ------------>Primitives in pad: p_1_0
   TPad *p_1_0 = new TPad("p_1_0", "p_1_0",0.2334152,0.692228,0.3851351,1);
   p_1_0->Draw();
   p_1_0->cd();
   p_1_0->Range(0,0,0.24,0.004374097);
   p_1_0->SetFillColor(0);
   p_1_0->SetBorderMode(0);
   p_1_0->SetBorderSize(0);
   p_1_0->SetTickx(1);
   p_1_0->SetTicky(1);
   p_1_0->SetLeftMargin(0);
   p_1_0->SetRightMargin(0);
   p_1_0->SetTopMargin(0.05);
   p_1_0->SetBottomMargin(0);
   p_1_0->SetFrameLineColor(0);
   p_1_0->SetFrameBorderMode(0);
   p_1_0->SetFrameLineColor(0);
   p_1_0->SetFrameBorderMode(0);
   Double_t xAxis10[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt7__10 = new TH1D("hPbPbUnfSq_ipt7__10","",9, xAxis10);
   hPbPbUnfSq_ipt7__10->SetBinContent(2,2.394115e-05);
   hPbPbUnfSq_ipt7__10->SetBinContent(3,0.0006312567);
   hPbPbUnfSq_ipt7__10->SetBinContent(4,0.001736589);
   hPbPbUnfSq_ipt7__10->SetBinContent(5,0.002077696);
   hPbPbUnfSq_ipt7__10->SetBinContent(6,0.001504085);
   hPbPbUnfSq_ipt7__10->SetBinContent(7,0.0008101983);
   hPbPbUnfSq_ipt7__10->SetBinContent(8,0.0002317568);
   hPbPbUnfSq_ipt7__10->SetBinContent(9,8.542752e-06);
   hPbPbUnfSq_ipt7__10->SetBinError(2,3.533319e-07);
   hPbPbUnfSq_ipt7__10->SetBinError(3,6.00559e-06);
   hPbPbUnfSq_ipt7__10->SetBinError(4,1.171413e-05);
   hPbPbUnfSq_ipt7__10->SetBinError(5,1.165702e-05);
   hPbPbUnfSq_ipt7__10->SetBinError(6,1.011766e-05);
   hPbPbUnfSq_ipt7__10->SetBinError(7,7.590188e-06);
   hPbPbUnfSq_ipt7__10->SetBinError(8,3.967155e-06);
   hPbPbUnfSq_ipt7__10->SetBinError(9,2.216475e-07);
   hPbPbUnfSq_ipt7__10->SetMinimum(0);
   hPbPbUnfSq_ipt7__10->SetMaximum(0.004155392);
   hPbPbUnfSq_ipt7__10->SetEntries(99123.16);
   hPbPbUnfSq_ipt7__10->SetStats(0);
   hPbPbUnfSq_ipt7__10->SetLineStyle(0);
   hPbPbUnfSq_ipt7__10->SetMarkerStyle(20);
   hPbPbUnfSq_ipt7__10->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt7__10->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt7__10->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt7__10->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt7__10->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt7__10->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt7__10->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt7__10->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt7__10->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt7__10->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt7__10->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt7__10->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt7__10->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt7__10->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt7__10->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt7__10->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt7__10->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt7__10->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt7__10->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt7__10->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt7__10->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt7__10->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt7__10->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt7__10->Draw("");
   box = new TBox(0,2.394115e-05,0.03,2.859716e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.03,0.0006312567,0.06,0.0007215972);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.06,0.001736589,0.09,0.001927143);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.09,0.002077696,0.12,0.002278738);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.12,0.001504085,0.15,0.001691739);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.15,0.0008101983,0.18,0.001001629);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.18,0.0002317568,0.24,0.000339846);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0,1.934289e-05,0.03,2.394115e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.03,0.0005427031,0.06,0.0006312567);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.06,0.001549416,0.09,0.001736589);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.09,0.00187333,0.12,0.002077696);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.12,0.001309643,0.15,0.001504085);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.15,0.0006182939,0.18,0.0008101983);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.18,0.0001288765,0.24,0.0002317568);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   Double_t xAxis11[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt7__11 = new TH1D("hPbPbUnfSq_ipt7__11","",9, xAxis11);
   hPbPbUnfSq_ipt7__11->SetBinContent(2,2.394115e-05);
   hPbPbUnfSq_ipt7__11->SetBinContent(3,0.0006312567);
   hPbPbUnfSq_ipt7__11->SetBinContent(4,0.001736589);
   hPbPbUnfSq_ipt7__11->SetBinContent(5,0.002077696);
   hPbPbUnfSq_ipt7__11->SetBinContent(6,0.001504085);
   hPbPbUnfSq_ipt7__11->SetBinContent(7,0.0008101983);
   hPbPbUnfSq_ipt7__11->SetBinContent(8,0.0002317568);
   hPbPbUnfSq_ipt7__11->SetBinContent(9,8.542752e-06);
   hPbPbUnfSq_ipt7__11->SetBinError(2,3.533319e-07);
   hPbPbUnfSq_ipt7__11->SetBinError(3,6.00559e-06);
   hPbPbUnfSq_ipt7__11->SetBinError(4,1.171413e-05);
   hPbPbUnfSq_ipt7__11->SetBinError(5,1.165702e-05);
   hPbPbUnfSq_ipt7__11->SetBinError(6,1.011766e-05);
   hPbPbUnfSq_ipt7__11->SetBinError(7,7.590188e-06);
   hPbPbUnfSq_ipt7__11->SetBinError(8,3.967155e-06);
   hPbPbUnfSq_ipt7__11->SetBinError(9,2.216475e-07);
   hPbPbUnfSq_ipt7__11->SetMinimum(0);
   hPbPbUnfSq_ipt7__11->SetMaximum(0.004155392);
   hPbPbUnfSq_ipt7__11->SetEntries(99123.16);
   hPbPbUnfSq_ipt7__11->SetStats(0);
   hPbPbUnfSq_ipt7__11->SetLineStyle(0);
   hPbPbUnfSq_ipt7__11->SetMarkerStyle(20);
   hPbPbUnfSq_ipt7__11->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt7__11->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt7__11->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt7__11->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt7__11->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt7__11->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt7__11->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt7__11->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt7__11->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt7__11->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt7__11->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt7__11->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt7__11->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt7__11->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt7__11->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt7__11->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt7__11->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt7__11->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt7__11->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt7__11->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt7__11->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt7__11->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt7__11->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt7__11->Draw("same");
      tex = new TLatex(0.18,0.6,"158 < p_{T}^{jet} < 199 GeV");
tex->SetNDC();
   tex->SetTextFont(43);
   tex->SetTextSize(18);
   tex->Draw();
   Double_t xAxis12[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt7_copy__12 = new TH1D("hPbPbUnfSq_ipt7_copy__12","",9, xAxis12);
   hPbPbUnfSq_ipt7_copy__12->SetBinContent(2,2.394115e-05);
   hPbPbUnfSq_ipt7_copy__12->SetBinContent(3,0.0006312567);
   hPbPbUnfSq_ipt7_copy__12->SetBinContent(4,0.001736589);
   hPbPbUnfSq_ipt7_copy__12->SetBinContent(5,0.002077696);
   hPbPbUnfSq_ipt7_copy__12->SetBinContent(6,0.001504085);
   hPbPbUnfSq_ipt7_copy__12->SetBinContent(7,0.0008101983);
   hPbPbUnfSq_ipt7_copy__12->SetBinContent(8,0.0002317568);
   hPbPbUnfSq_ipt7_copy__12->SetBinContent(9,8.542752e-06);
   hPbPbUnfSq_ipt7_copy__12->SetBinError(2,3.533319e-07);
   hPbPbUnfSq_ipt7_copy__12->SetBinError(3,6.00559e-06);
   hPbPbUnfSq_ipt7_copy__12->SetBinError(4,1.171413e-05);
   hPbPbUnfSq_ipt7_copy__12->SetBinError(5,1.165702e-05);
   hPbPbUnfSq_ipt7_copy__12->SetBinError(6,1.011766e-05);
   hPbPbUnfSq_ipt7_copy__12->SetBinError(7,7.590188e-06);
   hPbPbUnfSq_ipt7_copy__12->SetBinError(8,3.967155e-06);
   hPbPbUnfSq_ipt7_copy__12->SetBinError(9,2.216475e-07);
   hPbPbUnfSq_ipt7_copy__12->SetMinimum(0);
   hPbPbUnfSq_ipt7_copy__12->SetMaximum(0.004155392);
   hPbPbUnfSq_ipt7_copy__12->SetEntries(99123.16);
   hPbPbUnfSq_ipt7_copy__12->SetDirectory(0);
   hPbPbUnfSq_ipt7_copy__12->SetStats(0);
   hPbPbUnfSq_ipt7_copy__12->SetLineStyle(0);
   hPbPbUnfSq_ipt7_copy__12->SetMarkerStyle(20);
   hPbPbUnfSq_ipt7_copy__12->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt7_copy__12->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt7_copy__12->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt7_copy__12->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt7_copy__12->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt7_copy__12->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt7_copy__12->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt7_copy__12->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt7_copy__12->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt7_copy__12->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt7_copy__12->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt7_copy__12->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt7_copy__12->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt7_copy__12->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt7_copy__12->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt7_copy__12->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt7_copy__12->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt7_copy__12->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt7_copy__12->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt7_copy__12->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt7_copy__12->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt7_copy__12->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt7_copy__12->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt7_copy__12->Draw("sameaxis");
   
   TLegend *leg = new TLegend(0,0.955,0.5,1,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   leg->Draw();
   p_1_0->Modified();
   c1->cd();
  
// ------------>Primitives in pad: p_1_1
   TPad *p_1_1 = new TPad("p_1_1", "p_1_1",0.2334152,0.3998446,0.3851351,0.692228);
   p_1_1->Draw();
   p_1_1->cd();
   p_1_1->Range(0,0,0.24,0.005866668);
   p_1_1->SetFillColor(0);
   p_1_1->SetBorderMode(0);
   p_1_1->SetBorderSize(0);
   p_1_1->SetTickx(1);
   p_1_1->SetTicky(1);
   p_1_1->SetLeftMargin(0);
   p_1_1->SetRightMargin(0);
   p_1_1->SetTopMargin(0);
   p_1_1->SetBottomMargin(0);
   p_1_1->SetFrameLineColor(0);
   p_1_1->SetFrameBorderMode(0);
   p_1_1->SetFrameLineColor(0);
   p_1_1->SetFrameBorderMode(0);
   Double_t xAxis13[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt7__13 = new TH1D("hPbPbUnfSq_ipt7__13","",9, xAxis13);
   hPbPbUnfSq_ipt7__13->SetBinContent(2,3.762661e-05);
   hPbPbUnfSq_ipt7__13->SetBinContent(3,0.0008722048);
   hPbPbUnfSq_ipt7__13->SetBinContent(4,0.002347508);
   hPbPbUnfSq_ipt7__13->SetBinContent(5,0.002933334);
   hPbPbUnfSq_ipt7__13->SetBinContent(6,0.002275751);
   hPbPbUnfSq_ipt7__13->SetBinContent(7,0.001197917);
   hPbPbUnfSq_ipt7__13->SetBinContent(8,0.0003131539);
   hPbPbUnfSq_ipt7__13->SetBinContent(9,1.828169e-05);
   hPbPbUnfSq_ipt7__13->SetBinError(2,1.418805e-06);
   hPbPbUnfSq_ipt7__13->SetBinError(3,1.713803e-05);
   hPbPbUnfSq_ipt7__13->SetBinError(4,3.120621e-05);
   hPbPbUnfSq_ipt7__13->SetBinError(5,3.477315e-05);
   hPbPbUnfSq_ipt7__13->SetBinError(6,3.269722e-05);
   hPbPbUnfSq_ipt7__13->SetBinError(7,2.572962e-05);
   hPbPbUnfSq_ipt7__13->SetBinError(8,1.125737e-05);
   hPbPbUnfSq_ipt7__13->SetBinError(9,1.189639e-06);
   hPbPbUnfSq_ipt7__13->SetMinimum(0);
   hPbPbUnfSq_ipt7__13->SetMaximum(0.005866668);
   hPbPbUnfSq_ipt7__13->SetEntries(22593.04);
   hPbPbUnfSq_ipt7__13->SetStats(0);
   hPbPbUnfSq_ipt7__13->SetLineStyle(0);
   hPbPbUnfSq_ipt7__13->SetMarkerStyle(20);
   hPbPbUnfSq_ipt7__13->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt7__13->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt7__13->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt7__13->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt7__13->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt7__13->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt7__13->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt7__13->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt7__13->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt7__13->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt7__13->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt7__13->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt7__13->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt7__13->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt7__13->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt7__13->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt7__13->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt7__13->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt7__13->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt7__13->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt7__13->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt7__13->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt7__13->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt7__13->Draw("");
   box = new TBox(0,3.762661e-05,0.03,4.604646e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.03,0.0008722048,0.06,0.001023078);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.06,0.002347508,0.09,0.002644335);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.09,0.002933334,0.12,0.003165017);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.12,0.002275751,0.15,0.002568686);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.15,0.001197917,0.18,0.001501907);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.18,0.0003131539,0.24,0.00041553);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0,2.905428e-05,0.03,3.762661e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.03,0.0007201729,0.06,0.0008722048);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.06,0.002049938,0.09,0.002347508);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.09,0.002694928,0.12,0.002933334);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.12,0.001975467,0.15,0.002275751);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.15,0.0008927254,0.18,0.001197917);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.18,0.0002150354,0.24,0.0003131539);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   Double_t xAxis14[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt7__14 = new TH1D("hPbPbUnfSq_ipt7__14","",9, xAxis14);
   hPbPbUnfSq_ipt7__14->SetBinContent(2,3.762661e-05);
   hPbPbUnfSq_ipt7__14->SetBinContent(3,0.0008722048);
   hPbPbUnfSq_ipt7__14->SetBinContent(4,0.002347508);
   hPbPbUnfSq_ipt7__14->SetBinContent(5,0.002933334);
   hPbPbUnfSq_ipt7__14->SetBinContent(6,0.002275751);
   hPbPbUnfSq_ipt7__14->SetBinContent(7,0.001197917);
   hPbPbUnfSq_ipt7__14->SetBinContent(8,0.0003131539);
   hPbPbUnfSq_ipt7__14->SetBinContent(9,1.828169e-05);
   hPbPbUnfSq_ipt7__14->SetBinError(2,1.418805e-06);
   hPbPbUnfSq_ipt7__14->SetBinError(3,1.713803e-05);
   hPbPbUnfSq_ipt7__14->SetBinError(4,3.120621e-05);
   hPbPbUnfSq_ipt7__14->SetBinError(5,3.477315e-05);
   hPbPbUnfSq_ipt7__14->SetBinError(6,3.269722e-05);
   hPbPbUnfSq_ipt7__14->SetBinError(7,2.572962e-05);
   hPbPbUnfSq_ipt7__14->SetBinError(8,1.125737e-05);
   hPbPbUnfSq_ipt7__14->SetBinError(9,1.189639e-06);
   hPbPbUnfSq_ipt7__14->SetMinimum(0);
   hPbPbUnfSq_ipt7__14->SetMaximum(0.005866668);
   hPbPbUnfSq_ipt7__14->SetEntries(22593.04);
   hPbPbUnfSq_ipt7__14->SetStats(0);
   hPbPbUnfSq_ipt7__14->SetLineStyle(0);
   hPbPbUnfSq_ipt7__14->SetMarkerStyle(20);
   hPbPbUnfSq_ipt7__14->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt7__14->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt7__14->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt7__14->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt7__14->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt7__14->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt7__14->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt7__14->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt7__14->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt7__14->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt7__14->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt7__14->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt7__14->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt7__14->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt7__14->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt7__14->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt7__14->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt7__14->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt7__14->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt7__14->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt7__14->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt7__14->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt7__14->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt7__14->Draw("same");
   Double_t xAxis15[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt7_copy__15 = new TH1D("hPbPbUnfSq_ipt7_copy__15","",9, xAxis15);
   hPbPbUnfSq_ipt7_copy__15->SetBinContent(2,3.762661e-05);
   hPbPbUnfSq_ipt7_copy__15->SetBinContent(3,0.0008722048);
   hPbPbUnfSq_ipt7_copy__15->SetBinContent(4,0.002347508);
   hPbPbUnfSq_ipt7_copy__15->SetBinContent(5,0.002933334);
   hPbPbUnfSq_ipt7_copy__15->SetBinContent(6,0.002275751);
   hPbPbUnfSq_ipt7_copy__15->SetBinContent(7,0.001197917);
   hPbPbUnfSq_ipt7_copy__15->SetBinContent(8,0.0003131539);
   hPbPbUnfSq_ipt7_copy__15->SetBinContent(9,1.828169e-05);
   hPbPbUnfSq_ipt7_copy__15->SetBinError(2,1.418805e-06);
   hPbPbUnfSq_ipt7_copy__15->SetBinError(3,1.713803e-05);
   hPbPbUnfSq_ipt7_copy__15->SetBinError(4,3.120621e-05);
   hPbPbUnfSq_ipt7_copy__15->SetBinError(5,3.477315e-05);
   hPbPbUnfSq_ipt7_copy__15->SetBinError(6,3.269722e-05);
   hPbPbUnfSq_ipt7_copy__15->SetBinError(7,2.572962e-05);
   hPbPbUnfSq_ipt7_copy__15->SetBinError(8,1.125737e-05);
   hPbPbUnfSq_ipt7_copy__15->SetBinError(9,1.189639e-06);
   hPbPbUnfSq_ipt7_copy__15->SetMinimum(0);
   hPbPbUnfSq_ipt7_copy__15->SetMaximum(0.005866668);
   hPbPbUnfSq_ipt7_copy__15->SetEntries(22593.04);
   hPbPbUnfSq_ipt7_copy__15->SetDirectory(0);
   hPbPbUnfSq_ipt7_copy__15->SetStats(0);
   hPbPbUnfSq_ipt7_copy__15->SetLineStyle(0);
   hPbPbUnfSq_ipt7_copy__15->SetMarkerStyle(20);
   hPbPbUnfSq_ipt7_copy__15->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt7_copy__15->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt7_copy__15->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt7_copy__15->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt7_copy__15->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt7_copy__15->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt7_copy__15->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt7_copy__15->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt7_copy__15->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt7_copy__15->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt7_copy__15->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt7_copy__15->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt7_copy__15->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt7_copy__15->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt7_copy__15->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt7_copy__15->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt7_copy__15->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt7_copy__15->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt7_copy__15->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt7_copy__15->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt7_copy__15->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt7_copy__15->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt7_copy__15->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt7_copy__15->Draw("sameaxis");
   p_1_1->Modified();
   c1->cd();
  
// ------------>Primitives in pad: p_1_2
   TPad *p_1_2 = new TPad("p_1_2", "p_1_2",0.2334152,0.01,0.3851351,0.3998446);
   p_1_2->Draw();
   p_1_2->cd();
   p_1_2->Range(0,-0.002375375,0.24,0.007126126);
   p_1_2->SetFillColor(0);
   p_1_2->SetBorderMode(0);
   p_1_2->SetBorderSize(0);
   p_1_2->SetTickx(1);
   p_1_2->SetTicky(1);
   p_1_2->SetLeftMargin(0);
   p_1_2->SetRightMargin(0);
   p_1_2->SetTopMargin(0);
   p_1_2->SetBottomMargin(0.25);
   p_1_2->SetFrameLineColor(0);
   p_1_2->SetFrameBorderMode(0);
   p_1_2->SetFrameLineColor(0);
   p_1_2->SetFrameBorderMode(0);
   Double_t xAxis16[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt7__16 = new TH1D("hPbPbUnfSq_ipt7__16","",9, xAxis16);
   hPbPbUnfSq_ipt7__16->SetBinContent(2,4.607408e-05);
   hPbPbUnfSq_ipt7__16->SetBinContent(3,0.001206503);
   hPbPbUnfSq_ipt7__16->SetBinContent(4,0.00301615);
   hPbPbUnfSq_ipt7__16->SetBinContent(5,0.003563063);
   hPbPbUnfSq_ipt7__16->SetBinContent(6,0.002571802);
   hPbPbUnfSq_ipt7__16->SetBinContent(7,0.001396246);
   hPbPbUnfSq_ipt7__16->SetBinContent(8,0.0004111171);
   hPbPbUnfSq_ipt7__16->SetBinContent(9,1.919045e-05);
   hPbPbUnfSq_ipt7__16->SetBinError(2,3.52458e-06);
   hPbPbUnfSq_ipt7__16->SetBinError(3,5.770918e-05);
   hPbPbUnfSq_ipt7__16->SetBinError(4,9.20505e-05);
   hPbPbUnfSq_ipt7__16->SetBinError(5,0.0001024809);
   hPbPbUnfSq_ipt7__16->SetBinError(6,9.042532e-05);
   hPbPbUnfSq_ipt7__16->SetBinError(7,7.641986e-05);
   hPbPbUnfSq_ipt7__16->SetBinError(8,3.329048e-05);
   hPbPbUnfSq_ipt7__16->SetBinError(9,3.150025e-06);
   hPbPbUnfSq_ipt7__16->SetMinimum(0);
   hPbPbUnfSq_ipt7__16->SetMaximum(0.007126126);
   hPbPbUnfSq_ipt7__16->SetEntries(3936.848);
   hPbPbUnfSq_ipt7__16->SetStats(0);
   hPbPbUnfSq_ipt7__16->SetLineStyle(0);
   hPbPbUnfSq_ipt7__16->SetMarkerStyle(20);
   hPbPbUnfSq_ipt7__16->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt7__16->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt7__16->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt7__16->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt7__16->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt7__16->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt7__16->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt7__16->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt7__16->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt7__16->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt7__16->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt7__16->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt7__16->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt7__16->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt7__16->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt7__16->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt7__16->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt7__16->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt7__16->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt7__16->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt7__16->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt7__16->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt7__16->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt7__16->Draw("");
   box = new TBox(0,4.607408e-05,0.03,6.120901e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.03,0.001206503,0.06,0.001455076);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.06,0.00301615,0.09,0.003367865);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.09,0.003563063,0.12,0.003898263);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.12,0.002571802,0.15,0.002994336);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.15,0.001396246,0.18,0.00168123);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.18,0.0004111171,0.24,0.0005054845);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0,3.140872e-05,0.03,4.607408e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.03,0.0009581156,0.06,0.001206503);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.06,0.002657174,0.09,0.00301615);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.09,0.003217466,0.12,0.003563063);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.12,0.00215058,0.15,0.002571802);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.15,0.001113421,0.18,0.001396246);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.18,0.0003181801,0.24,0.0004111171);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   Double_t xAxis17[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt7__17 = new TH1D("hPbPbUnfSq_ipt7__17","",9, xAxis17);
   hPbPbUnfSq_ipt7__17->SetBinContent(2,4.607408e-05);
   hPbPbUnfSq_ipt7__17->SetBinContent(3,0.001206503);
   hPbPbUnfSq_ipt7__17->SetBinContent(4,0.00301615);
   hPbPbUnfSq_ipt7__17->SetBinContent(5,0.003563063);
   hPbPbUnfSq_ipt7__17->SetBinContent(6,0.002571802);
   hPbPbUnfSq_ipt7__17->SetBinContent(7,0.001396246);
   hPbPbUnfSq_ipt7__17->SetBinContent(8,0.0004111171);
   hPbPbUnfSq_ipt7__17->SetBinContent(9,1.919045e-05);
   hPbPbUnfSq_ipt7__17->SetBinError(2,3.52458e-06);
   hPbPbUnfSq_ipt7__17->SetBinError(3,5.770918e-05);
   hPbPbUnfSq_ipt7__17->SetBinError(4,9.20505e-05);
   hPbPbUnfSq_ipt7__17->SetBinError(5,0.0001024809);
   hPbPbUnfSq_ipt7__17->SetBinError(6,9.042532e-05);
   hPbPbUnfSq_ipt7__17->SetBinError(7,7.641986e-05);
   hPbPbUnfSq_ipt7__17->SetBinError(8,3.329048e-05);
   hPbPbUnfSq_ipt7__17->SetBinError(9,3.150025e-06);
   hPbPbUnfSq_ipt7__17->SetMinimum(0);
   hPbPbUnfSq_ipt7__17->SetMaximum(0.007126126);
   hPbPbUnfSq_ipt7__17->SetEntries(3936.848);
   hPbPbUnfSq_ipt7__17->SetStats(0);
   hPbPbUnfSq_ipt7__17->SetLineStyle(0);
   hPbPbUnfSq_ipt7__17->SetMarkerStyle(20);
   hPbPbUnfSq_ipt7__17->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt7__17->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt7__17->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt7__17->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt7__17->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt7__17->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt7__17->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt7__17->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt7__17->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt7__17->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt7__17->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt7__17->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt7__17->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt7__17->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt7__17->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt7__17->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt7__17->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt7__17->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt7__17->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt7__17->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt7__17->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt7__17->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt7__17->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt7__17->Draw("same");
   Double_t xAxis18[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt7_copy__18 = new TH1D("hPbPbUnfSq_ipt7_copy__18","",9, xAxis18);
   hPbPbUnfSq_ipt7_copy__18->SetBinContent(2,4.607408e-05);
   hPbPbUnfSq_ipt7_copy__18->SetBinContent(3,0.001206503);
   hPbPbUnfSq_ipt7_copy__18->SetBinContent(4,0.00301615);
   hPbPbUnfSq_ipt7_copy__18->SetBinContent(5,0.003563063);
   hPbPbUnfSq_ipt7_copy__18->SetBinContent(6,0.002571802);
   hPbPbUnfSq_ipt7_copy__18->SetBinContent(7,0.001396246);
   hPbPbUnfSq_ipt7_copy__18->SetBinContent(8,0.0004111171);
   hPbPbUnfSq_ipt7_copy__18->SetBinContent(9,1.919045e-05);
   hPbPbUnfSq_ipt7_copy__18->SetBinError(2,3.52458e-06);
   hPbPbUnfSq_ipt7_copy__18->SetBinError(3,5.770918e-05);
   hPbPbUnfSq_ipt7_copy__18->SetBinError(4,9.20505e-05);
   hPbPbUnfSq_ipt7_copy__18->SetBinError(5,0.0001024809);
   hPbPbUnfSq_ipt7_copy__18->SetBinError(6,9.042532e-05);
   hPbPbUnfSq_ipt7_copy__18->SetBinError(7,7.641986e-05);
   hPbPbUnfSq_ipt7_copy__18->SetBinError(8,3.329048e-05);
   hPbPbUnfSq_ipt7_copy__18->SetBinError(9,3.150025e-06);
   hPbPbUnfSq_ipt7_copy__18->SetMinimum(0);
   hPbPbUnfSq_ipt7_copy__18->SetMaximum(0.007126126);
   hPbPbUnfSq_ipt7_copy__18->SetEntries(3936.848);
   hPbPbUnfSq_ipt7_copy__18->SetDirectory(0);
   hPbPbUnfSq_ipt7_copy__18->SetStats(0);
   hPbPbUnfSq_ipt7_copy__18->SetLineStyle(0);
   hPbPbUnfSq_ipt7_copy__18->SetMarkerStyle(20);
   hPbPbUnfSq_ipt7_copy__18->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt7_copy__18->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt7_copy__18->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt7_copy__18->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt7_copy__18->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt7_copy__18->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt7_copy__18->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt7_copy__18->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt7_copy__18->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt7_copy__18->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt7_copy__18->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt7_copy__18->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt7_copy__18->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt7_copy__18->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt7_copy__18->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt7_copy__18->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt7_copy__18->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt7_copy__18->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt7_copy__18->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt7_copy__18->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt7_copy__18->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt7_copy__18->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt7_copy__18->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt7_copy__18->Draw("sameaxis");
   p_1_2->Modified();
   c1->cd();
  
// ------------>Primitives in pad: p_2_0
   TPad *p_2_0 = new TPad("p_2_0", "p_2_0",0.3851351,0.692228,0.536855,1);
   p_2_0->Draw();
   p_2_0->cd();
   p_2_0->Range(0,0,0.24,0.001163514);
   p_2_0->SetFillColor(0);
   p_2_0->SetBorderMode(0);
   p_2_0->SetBorderSize(0);
   p_2_0->SetTickx(1);
   p_2_0->SetTicky(1);
   p_2_0->SetLeftMargin(0);
   p_2_0->SetRightMargin(0);
   p_2_0->SetTopMargin(0.05);
   p_2_0->SetBottomMargin(0);
   p_2_0->SetFrameLineColor(0);
   p_2_0->SetFrameBorderMode(0);
   p_2_0->SetFrameLineColor(0);
   p_2_0->SetFrameBorderMode(0);
   Double_t xAxis19[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt8__19 = new TH1D("hPbPbUnfSq_ipt8__19","",9, xAxis19);
   hPbPbUnfSq_ipt8__19->SetBinContent(2,1.046683e-05);
   hPbPbUnfSq_ipt8__19->SetBinContent(3,0.0002543474);
   hPbPbUnfSq_ipt8__19->SetBinContent(4,0.0005526692);
   hPbPbUnfSq_ipt8__19->SetBinContent(5,0.0005406854);
   hPbPbUnfSq_ipt8__19->SetBinContent(6,0.0003522301);
   hPbPbUnfSq_ipt8__19->SetBinContent(7,0.0001873425);
   hPbPbUnfSq_ipt8__19->SetBinContent(8,4.821576e-05);
   hPbPbUnfSq_ipt8__19->SetBinContent(9,8.052219e-07);
   hPbPbUnfSq_ipt8__19->SetBinError(2,2.471591e-07);
   hPbPbUnfSq_ipt8__19->SetBinError(3,3.943749e-06);
   hPbPbUnfSq_ipt8__19->SetBinError(4,6.115099e-06);
   hPbPbUnfSq_ipt8__19->SetBinError(5,5.724753e-06);
   hPbPbUnfSq_ipt8__19->SetBinError(6,5.105162e-06);
   hPbPbUnfSq_ipt8__19->SetBinError(7,3.948708e-06);
   hPbPbUnfSq_ipt8__19->SetBinError(8,1.803472e-06);
   hPbPbUnfSq_ipt8__19->SetBinError(9,5.582163e-08);
   hPbPbUnfSq_ipt8__19->SetMinimum(0);
   hPbPbUnfSq_ipt8__19->SetMaximum(0.001105338);
   hPbPbUnfSq_ipt8__19->SetEntries(28367.12);
   hPbPbUnfSq_ipt8__19->SetStats(0);
   hPbPbUnfSq_ipt8__19->SetLineStyle(0);
   hPbPbUnfSq_ipt8__19->SetMarkerStyle(20);
   hPbPbUnfSq_ipt8__19->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt8__19->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt8__19->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt8__19->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt8__19->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt8__19->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt8__19->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt8__19->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt8__19->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt8__19->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt8__19->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt8__19->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt8__19->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt8__19->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt8__19->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt8__19->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt8__19->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt8__19->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt8__19->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt8__19->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt8__19->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt8__19->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt8__19->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt8__19->Draw("");
   box = new TBox(0,1.046683e-05,0.03,1.291914e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.03,0.0002543474,0.06,0.0003010023);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.06,0.0005526692,0.09,0.0006248363);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.09,0.0005406854,0.12,0.0005942647);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.12,0.0003522301,0.15,0.0004183657);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.15,0.0001873425,0.18,0.0002566222);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.18,4.821576e-05,0.24,7.323636e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0,8.02698e-06,0.03,1.046683e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.03,0.0002075956,0.06,0.0002543474);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.06,0.0004808722,0.09,0.0005526692);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.09,0.0004883554,0.12,0.0005406854);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.12,0.0002868821,0.15,0.0003522301);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.15,0.0001177184,0.18,0.0001873425);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.18,2.332689e-05,0.24,4.821576e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   Double_t xAxis20[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt8__20 = new TH1D("hPbPbUnfSq_ipt8__20","",9, xAxis20);
   hPbPbUnfSq_ipt8__20->SetBinContent(2,1.046683e-05);
   hPbPbUnfSq_ipt8__20->SetBinContent(3,0.0002543474);
   hPbPbUnfSq_ipt8__20->SetBinContent(4,0.0005526692);
   hPbPbUnfSq_ipt8__20->SetBinContent(5,0.0005406854);
   hPbPbUnfSq_ipt8__20->SetBinContent(6,0.0003522301);
   hPbPbUnfSq_ipt8__20->SetBinContent(7,0.0001873425);
   hPbPbUnfSq_ipt8__20->SetBinContent(8,4.821576e-05);
   hPbPbUnfSq_ipt8__20->SetBinContent(9,8.052219e-07);
   hPbPbUnfSq_ipt8__20->SetBinError(2,2.471591e-07);
   hPbPbUnfSq_ipt8__20->SetBinError(3,3.943749e-06);
   hPbPbUnfSq_ipt8__20->SetBinError(4,6.115099e-06);
   hPbPbUnfSq_ipt8__20->SetBinError(5,5.724753e-06);
   hPbPbUnfSq_ipt8__20->SetBinError(6,5.105162e-06);
   hPbPbUnfSq_ipt8__20->SetBinError(7,3.948708e-06);
   hPbPbUnfSq_ipt8__20->SetBinError(8,1.803472e-06);
   hPbPbUnfSq_ipt8__20->SetBinError(9,5.582163e-08);
   hPbPbUnfSq_ipt8__20->SetMinimum(0);
   hPbPbUnfSq_ipt8__20->SetMaximum(0.001105338);
   hPbPbUnfSq_ipt8__20->SetEntries(28367.12);
   hPbPbUnfSq_ipt8__20->SetStats(0);
   hPbPbUnfSq_ipt8__20->SetLineStyle(0);
   hPbPbUnfSq_ipt8__20->SetMarkerStyle(20);
   hPbPbUnfSq_ipt8__20->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt8__20->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt8__20->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt8__20->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt8__20->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt8__20->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt8__20->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt8__20->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt8__20->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt8__20->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt8__20->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt8__20->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt8__20->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt8__20->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt8__20->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt8__20->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt8__20->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt8__20->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt8__20->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt8__20->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt8__20->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt8__20->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt8__20->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt8__20->Draw("same");
      tex = new TLatex(0.18,0.6,"199 < p_{T}^{jet} < 251 GeV");
tex->SetNDC();
   tex->SetTextFont(43);
   tex->SetTextSize(18);
   tex->Draw();
   Double_t xAxis21[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt8_copy__21 = new TH1D("hPbPbUnfSq_ipt8_copy__21","",9, xAxis21);
   hPbPbUnfSq_ipt8_copy__21->SetBinContent(2,1.046683e-05);
   hPbPbUnfSq_ipt8_copy__21->SetBinContent(3,0.0002543474);
   hPbPbUnfSq_ipt8_copy__21->SetBinContent(4,0.0005526692);
   hPbPbUnfSq_ipt8_copy__21->SetBinContent(5,0.0005406854);
   hPbPbUnfSq_ipt8_copy__21->SetBinContent(6,0.0003522301);
   hPbPbUnfSq_ipt8_copy__21->SetBinContent(7,0.0001873425);
   hPbPbUnfSq_ipt8_copy__21->SetBinContent(8,4.821576e-05);
   hPbPbUnfSq_ipt8_copy__21->SetBinContent(9,8.052219e-07);
   hPbPbUnfSq_ipt8_copy__21->SetBinError(2,2.471591e-07);
   hPbPbUnfSq_ipt8_copy__21->SetBinError(3,3.943749e-06);
   hPbPbUnfSq_ipt8_copy__21->SetBinError(4,6.115099e-06);
   hPbPbUnfSq_ipt8_copy__21->SetBinError(5,5.724753e-06);
   hPbPbUnfSq_ipt8_copy__21->SetBinError(6,5.105162e-06);
   hPbPbUnfSq_ipt8_copy__21->SetBinError(7,3.948708e-06);
   hPbPbUnfSq_ipt8_copy__21->SetBinError(8,1.803472e-06);
   hPbPbUnfSq_ipt8_copy__21->SetBinError(9,5.582163e-08);
   hPbPbUnfSq_ipt8_copy__21->SetMinimum(0);
   hPbPbUnfSq_ipt8_copy__21->SetMaximum(0.001105338);
   hPbPbUnfSq_ipt8_copy__21->SetEntries(28367.12);
   hPbPbUnfSq_ipt8_copy__21->SetDirectory(0);
   hPbPbUnfSq_ipt8_copy__21->SetStats(0);
   hPbPbUnfSq_ipt8_copy__21->SetLineStyle(0);
   hPbPbUnfSq_ipt8_copy__21->SetMarkerStyle(20);
   hPbPbUnfSq_ipt8_copy__21->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt8_copy__21->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt8_copy__21->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt8_copy__21->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt8_copy__21->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt8_copy__21->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt8_copy__21->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt8_copy__21->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt8_copy__21->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt8_copy__21->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt8_copy__21->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt8_copy__21->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt8_copy__21->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt8_copy__21->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt8_copy__21->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt8_copy__21->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt8_copy__21->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt8_copy__21->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt8_copy__21->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt8_copy__21->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt8_copy__21->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt8_copy__21->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt8_copy__21->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt8_copy__21->Draw("sameaxis");
   
   leg = new TLegend(0,0.955,0.5,1,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   leg->Draw();
   p_2_0->Modified();
   c1->cd();
  
// ------------>Primitives in pad: p_2_1
   TPad *p_2_1 = new TPad("p_2_1", "p_2_1",0.3851351,0.3998446,0.536855,0.692228);
   p_2_1->Draw();
   p_2_1->cd();
   p_2_1->Range(0,0,0.24,0.001559693);
   p_2_1->SetFillColor(0);
   p_2_1->SetBorderMode(0);
   p_2_1->SetBorderSize(0);
   p_2_1->SetTickx(1);
   p_2_1->SetTicky(1);
   p_2_1->SetLeftMargin(0);
   p_2_1->SetRightMargin(0);
   p_2_1->SetTopMargin(0);
   p_2_1->SetBottomMargin(0);
   p_2_1->SetFrameLineColor(0);
   p_2_1->SetFrameBorderMode(0);
   p_2_1->SetFrameLineColor(0);
   p_2_1->SetFrameBorderMode(0);
   Double_t xAxis22[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt8__22 = new TH1D("hPbPbUnfSq_ipt8__22","",9, xAxis22);
   hPbPbUnfSq_ipt8__22->SetBinContent(2,1.813156e-05);
   hPbPbUnfSq_ipt8__22->SetBinContent(3,0.0003570556);
   hPbPbUnfSq_ipt8__22->SetBinContent(4,0.0007700302);
   hPbPbUnfSq_ipt8__22->SetBinContent(5,0.0007798466);
   hPbPbUnfSq_ipt8__22->SetBinContent(6,0.0005171887);
   hPbPbUnfSq_ipt8__22->SetBinContent(7,0.0002623274);
   hPbPbUnfSq_ipt8__22->SetBinContent(8,6.448219e-05);
   hPbPbUnfSq_ipt8__22->SetBinContent(9,2.103178e-06);
   hPbPbUnfSq_ipt8__22->SetBinError(2,1.273463e-06);
   hPbPbUnfSq_ipt8__22->SetBinError(3,1.105227e-05);
   hPbPbUnfSq_ipt8__22->SetBinError(4,1.625126e-05);
   hPbPbUnfSq_ipt8__22->SetBinError(5,1.675703e-05);
   hPbPbUnfSq_ipt8__22->SetBinError(6,1.498718e-05);
   hPbPbUnfSq_ipt8__22->SetBinError(7,1.180336e-05);
   hPbPbUnfSq_ipt8__22->SetBinError(8,4.714129e-06);
   hPbPbUnfSq_ipt8__22->SetBinError(9,3.258033e-07);
   hPbPbUnfSq_ipt8__22->SetMinimum(0);
   hPbPbUnfSq_ipt8__22->SetMaximum(0.001559693);
   hPbPbUnfSq_ipt8__22->SetEntries(7186.674);
   hPbPbUnfSq_ipt8__22->SetStats(0);
   hPbPbUnfSq_ipt8__22->SetLineStyle(0);
   hPbPbUnfSq_ipt8__22->SetMarkerStyle(20);
   hPbPbUnfSq_ipt8__22->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt8__22->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt8__22->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt8__22->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt8__22->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt8__22->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt8__22->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt8__22->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt8__22->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt8__22->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt8__22->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt8__22->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt8__22->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt8__22->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt8__22->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt8__22->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt8__22->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt8__22->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt8__22->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt8__22->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt8__22->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt8__22->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt8__22->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt8__22->Draw("");
   box = new TBox(0,1.813156e-05,0.03,2.302115e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.03,0.0003570556,0.06,0.0004438867);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.06,0.0007700302,0.09,0.0008734699);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.09,0.0007798466,0.12,0.0008534122);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.12,0.0005171887,0.15,0.0006386595);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.15,0.0002623274,0.18,0.0003438531);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.18,6.448219e-05,0.24,8.618447e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0,1.307835e-05,0.03,1.813156e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.03,0.0002708063,0.06,0.0003570556);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.06,0.0006691386,0.09,0.0007700302);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.09,0.000707879,0.12,0.0007798466);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.12,0.0003949063,0.15,0.0005171887);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.15,0.0001802464,0.18,0.0002623274);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.18,4.314223e-05,0.24,6.448219e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   Double_t xAxis23[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt8__23 = new TH1D("hPbPbUnfSq_ipt8__23","",9, xAxis23);
   hPbPbUnfSq_ipt8__23->SetBinContent(2,1.813156e-05);
   hPbPbUnfSq_ipt8__23->SetBinContent(3,0.0003570556);
   hPbPbUnfSq_ipt8__23->SetBinContent(4,0.0007700302);
   hPbPbUnfSq_ipt8__23->SetBinContent(5,0.0007798466);
   hPbPbUnfSq_ipt8__23->SetBinContent(6,0.0005171887);
   hPbPbUnfSq_ipt8__23->SetBinContent(7,0.0002623274);
   hPbPbUnfSq_ipt8__23->SetBinContent(8,6.448219e-05);
   hPbPbUnfSq_ipt8__23->SetBinContent(9,2.103178e-06);
   hPbPbUnfSq_ipt8__23->SetBinError(2,1.273463e-06);
   hPbPbUnfSq_ipt8__23->SetBinError(3,1.105227e-05);
   hPbPbUnfSq_ipt8__23->SetBinError(4,1.625126e-05);
   hPbPbUnfSq_ipt8__23->SetBinError(5,1.675703e-05);
   hPbPbUnfSq_ipt8__23->SetBinError(6,1.498718e-05);
   hPbPbUnfSq_ipt8__23->SetBinError(7,1.180336e-05);
   hPbPbUnfSq_ipt8__23->SetBinError(8,4.714129e-06);
   hPbPbUnfSq_ipt8__23->SetBinError(9,3.258033e-07);
   hPbPbUnfSq_ipt8__23->SetMinimum(0);
   hPbPbUnfSq_ipt8__23->SetMaximum(0.001559693);
   hPbPbUnfSq_ipt8__23->SetEntries(7186.674);
   hPbPbUnfSq_ipt8__23->SetStats(0);
   hPbPbUnfSq_ipt8__23->SetLineStyle(0);
   hPbPbUnfSq_ipt8__23->SetMarkerStyle(20);
   hPbPbUnfSq_ipt8__23->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt8__23->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt8__23->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt8__23->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt8__23->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt8__23->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt8__23->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt8__23->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt8__23->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt8__23->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt8__23->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt8__23->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt8__23->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt8__23->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt8__23->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt8__23->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt8__23->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt8__23->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt8__23->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt8__23->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt8__23->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt8__23->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt8__23->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt8__23->Draw("same");
   Double_t xAxis24[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt8_copy__24 = new TH1D("hPbPbUnfSq_ipt8_copy__24","",9, xAxis24);
   hPbPbUnfSq_ipt8_copy__24->SetBinContent(2,1.813156e-05);
   hPbPbUnfSq_ipt8_copy__24->SetBinContent(3,0.0003570556);
   hPbPbUnfSq_ipt8_copy__24->SetBinContent(4,0.0007700302);
   hPbPbUnfSq_ipt8_copy__24->SetBinContent(5,0.0007798466);
   hPbPbUnfSq_ipt8_copy__24->SetBinContent(6,0.0005171887);
   hPbPbUnfSq_ipt8_copy__24->SetBinContent(7,0.0002623274);
   hPbPbUnfSq_ipt8_copy__24->SetBinContent(8,6.448219e-05);
   hPbPbUnfSq_ipt8_copy__24->SetBinContent(9,2.103178e-06);
   hPbPbUnfSq_ipt8_copy__24->SetBinError(2,1.273463e-06);
   hPbPbUnfSq_ipt8_copy__24->SetBinError(3,1.105227e-05);
   hPbPbUnfSq_ipt8_copy__24->SetBinError(4,1.625126e-05);
   hPbPbUnfSq_ipt8_copy__24->SetBinError(5,1.675703e-05);
   hPbPbUnfSq_ipt8_copy__24->SetBinError(6,1.498718e-05);
   hPbPbUnfSq_ipt8_copy__24->SetBinError(7,1.180336e-05);
   hPbPbUnfSq_ipt8_copy__24->SetBinError(8,4.714129e-06);
   hPbPbUnfSq_ipt8_copy__24->SetBinError(9,3.258033e-07);
   hPbPbUnfSq_ipt8_copy__24->SetMinimum(0);
   hPbPbUnfSq_ipt8_copy__24->SetMaximum(0.001559693);
   hPbPbUnfSq_ipt8_copy__24->SetEntries(7186.674);
   hPbPbUnfSq_ipt8_copy__24->SetDirectory(0);
   hPbPbUnfSq_ipt8_copy__24->SetStats(0);
   hPbPbUnfSq_ipt8_copy__24->SetLineStyle(0);
   hPbPbUnfSq_ipt8_copy__24->SetMarkerStyle(20);
   hPbPbUnfSq_ipt8_copy__24->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt8_copy__24->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt8_copy__24->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt8_copy__24->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt8_copy__24->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt8_copy__24->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt8_copy__24->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt8_copy__24->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt8_copy__24->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt8_copy__24->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt8_copy__24->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt8_copy__24->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt8_copy__24->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt8_copy__24->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt8_copy__24->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt8_copy__24->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt8_copy__24->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt8_copy__24->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt8_copy__24->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt8_copy__24->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt8_copy__24->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt8_copy__24->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt8_copy__24->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt8_copy__24->Draw("sameaxis");
   p_2_1->Modified();
   c1->cd();
  
// ------------>Primitives in pad: p_2_2
   TPad *p_2_2 = new TPad("p_2_2", "p_2_2",0.3851351,0.01,0.536855,0.3998446);
   p_2_2->Draw();
   p_2_2->cd();
   p_2_2->Range(0,-0.000599469,0.24,0.001798407);
   p_2_2->SetFillColor(0);
   p_2_2->SetBorderMode(0);
   p_2_2->SetBorderSize(0);
   p_2_2->SetTickx(1);
   p_2_2->SetTicky(1);
   p_2_2->SetLeftMargin(0);
   p_2_2->SetRightMargin(0);
   p_2_2->SetTopMargin(0);
   p_2_2->SetBottomMargin(0.25);
   p_2_2->SetFrameLineColor(0);
   p_2_2->SetFrameBorderMode(0);
   p_2_2->SetFrameLineColor(0);
   p_2_2->SetFrameBorderMode(0);
   Double_t xAxis25[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt8__25 = new TH1D("hPbPbUnfSq_ipt8__25","",9, xAxis25);
   hPbPbUnfSq_ipt8__25->SetBinContent(2,2.384281e-05);
   hPbPbUnfSq_ipt8__25->SetBinContent(3,0.0004128513);
   hPbPbUnfSq_ipt8__25->SetBinContent(4,0.0008992035);
   hPbPbUnfSq_ipt8__25->SetBinContent(5,0.0008738523);
   hPbPbUnfSq_ipt8__25->SetBinContent(6,0.0005581547);
   hPbPbUnfSq_ipt8__25->SetBinContent(7,0.0002772038);
   hPbPbUnfSq_ipt8__25->SetBinContent(8,9.96675e-05);
   hPbPbUnfSq_ipt8__25->SetBinContent(9,2.24784e-06);
   hPbPbUnfSq_ipt8__25->SetBinError(2,5.523436e-06);
   hPbPbUnfSq_ipt8__25->SetBinError(3,3.078245e-05);
   hPbPbUnfSq_ipt8__25->SetBinError(4,4.636383e-05);
   hPbPbUnfSq_ipt8__25->SetBinError(5,4.654367e-05);
   hPbPbUnfSq_ipt8__25->SetBinError(6,4.018593e-05);
   hPbPbUnfSq_ipt8__25->SetBinError(7,3.215254e-05);
   hPbPbUnfSq_ipt8__25->SetBinError(8,1.525017e-05);
   hPbPbUnfSq_ipt8__25->SetBinError(9,5.257733e-07);
   hPbPbUnfSq_ipt8__25->SetMinimum(0);
   hPbPbUnfSq_ipt8__25->SetMaximum(0.001798407);
   hPbPbUnfSq_ipt8__25->SetEntries(1198.49);
   hPbPbUnfSq_ipt8__25->SetStats(0);
   hPbPbUnfSq_ipt8__25->SetLineStyle(0);
   hPbPbUnfSq_ipt8__25->SetMarkerStyle(20);
   hPbPbUnfSq_ipt8__25->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt8__25->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt8__25->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt8__25->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt8__25->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt8__25->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt8__25->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt8__25->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt8__25->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt8__25->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt8__25->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt8__25->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt8__25->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt8__25->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt8__25->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt8__25->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt8__25->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt8__25->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt8__25->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt8__25->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt8__25->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt8__25->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt8__25->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt8__25->Draw("");
   box = new TBox(0,2.384281e-05,0.03,3.356049e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.03,0.0004128513,0.06,0.0005382113);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.06,0.0008992035,0.09,0.001008261);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.09,0.0008738523,0.12,0.0009859076);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.12,0.0005581547,0.15,0.0006850774);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.15,0.0002772038,0.18,0.0003583102);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.18,9.96675e-05,0.24,0.000127557);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0,1.404908e-05,0.03,2.384281e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.03,0.0002892007,0.06,0.0004128513);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.06,0.000793566,0.09,0.0008992035);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.09,0.0007614063,0.12,0.0008738523);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.12,0.0004292527,0.15,0.0005581547);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.15,0.0002035058,0.18,0.0002772038);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.18,7.040196e-05,0.24,9.96675e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   Double_t xAxis26[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt8__26 = new TH1D("hPbPbUnfSq_ipt8__26","",9, xAxis26);
   hPbPbUnfSq_ipt8__26->SetBinContent(2,2.384281e-05);
   hPbPbUnfSq_ipt8__26->SetBinContent(3,0.0004128513);
   hPbPbUnfSq_ipt8__26->SetBinContent(4,0.0008992035);
   hPbPbUnfSq_ipt8__26->SetBinContent(5,0.0008738523);
   hPbPbUnfSq_ipt8__26->SetBinContent(6,0.0005581547);
   hPbPbUnfSq_ipt8__26->SetBinContent(7,0.0002772038);
   hPbPbUnfSq_ipt8__26->SetBinContent(8,9.96675e-05);
   hPbPbUnfSq_ipt8__26->SetBinContent(9,2.24784e-06);
   hPbPbUnfSq_ipt8__26->SetBinError(2,5.523436e-06);
   hPbPbUnfSq_ipt8__26->SetBinError(3,3.078245e-05);
   hPbPbUnfSq_ipt8__26->SetBinError(4,4.636383e-05);
   hPbPbUnfSq_ipt8__26->SetBinError(5,4.654367e-05);
   hPbPbUnfSq_ipt8__26->SetBinError(6,4.018593e-05);
   hPbPbUnfSq_ipt8__26->SetBinError(7,3.215254e-05);
   hPbPbUnfSq_ipt8__26->SetBinError(8,1.525017e-05);
   hPbPbUnfSq_ipt8__26->SetBinError(9,5.257733e-07);
   hPbPbUnfSq_ipt8__26->SetMinimum(0);
   hPbPbUnfSq_ipt8__26->SetMaximum(0.001798407);
   hPbPbUnfSq_ipt8__26->SetEntries(1198.49);
   hPbPbUnfSq_ipt8__26->SetStats(0);
   hPbPbUnfSq_ipt8__26->SetLineStyle(0);
   hPbPbUnfSq_ipt8__26->SetMarkerStyle(20);
   hPbPbUnfSq_ipt8__26->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt8__26->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt8__26->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt8__26->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt8__26->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt8__26->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt8__26->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt8__26->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt8__26->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt8__26->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt8__26->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt8__26->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt8__26->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt8__26->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt8__26->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt8__26->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt8__26->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt8__26->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt8__26->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt8__26->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt8__26->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt8__26->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt8__26->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt8__26->Draw("same");
   Double_t xAxis27[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt8_copy__27 = new TH1D("hPbPbUnfSq_ipt8_copy__27","",9, xAxis27);
   hPbPbUnfSq_ipt8_copy__27->SetBinContent(2,2.384281e-05);
   hPbPbUnfSq_ipt8_copy__27->SetBinContent(3,0.0004128513);
   hPbPbUnfSq_ipt8_copy__27->SetBinContent(4,0.0008992035);
   hPbPbUnfSq_ipt8_copy__27->SetBinContent(5,0.0008738523);
   hPbPbUnfSq_ipt8_copy__27->SetBinContent(6,0.0005581547);
   hPbPbUnfSq_ipt8_copy__27->SetBinContent(7,0.0002772038);
   hPbPbUnfSq_ipt8_copy__27->SetBinContent(8,9.96675e-05);
   hPbPbUnfSq_ipt8_copy__27->SetBinContent(9,2.24784e-06);
   hPbPbUnfSq_ipt8_copy__27->SetBinError(2,5.523436e-06);
   hPbPbUnfSq_ipt8_copy__27->SetBinError(3,3.078245e-05);
   hPbPbUnfSq_ipt8_copy__27->SetBinError(4,4.636383e-05);
   hPbPbUnfSq_ipt8_copy__27->SetBinError(5,4.654367e-05);
   hPbPbUnfSq_ipt8_copy__27->SetBinError(6,4.018593e-05);
   hPbPbUnfSq_ipt8_copy__27->SetBinError(7,3.215254e-05);
   hPbPbUnfSq_ipt8_copy__27->SetBinError(8,1.525017e-05);
   hPbPbUnfSq_ipt8_copy__27->SetBinError(9,5.257733e-07);
   hPbPbUnfSq_ipt8_copy__27->SetMinimum(0);
   hPbPbUnfSq_ipt8_copy__27->SetMaximum(0.001798407);
   hPbPbUnfSq_ipt8_copy__27->SetEntries(1198.49);
   hPbPbUnfSq_ipt8_copy__27->SetDirectory(0);
   hPbPbUnfSq_ipt8_copy__27->SetStats(0);
   hPbPbUnfSq_ipt8_copy__27->SetLineStyle(0);
   hPbPbUnfSq_ipt8_copy__27->SetMarkerStyle(20);
   hPbPbUnfSq_ipt8_copy__27->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt8_copy__27->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt8_copy__27->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt8_copy__27->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt8_copy__27->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt8_copy__27->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt8_copy__27->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt8_copy__27->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt8_copy__27->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt8_copy__27->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt8_copy__27->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt8_copy__27->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt8_copy__27->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt8_copy__27->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt8_copy__27->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt8_copy__27->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt8_copy__27->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt8_copy__27->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt8_copy__27->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt8_copy__27->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt8_copy__27->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt8_copy__27->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt8_copy__27->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt8_copy__27->Draw("sameaxis");
   p_2_2->Modified();
   c1->cd();
  
// ------------>Primitives in pad: p_3_0
   TPad *p_3_0 = new TPad("p_3_0", "p_3_0",0.536855,0.692228,0.6885749,1);
   p_3_0->Draw();
   p_3_0->cd();
   p_3_0->Range(0,0,0.24,0.0003054862);
   p_3_0->SetFillColor(0);
   p_3_0->SetBorderMode(0);
   p_3_0->SetBorderSize(0);
   p_3_0->SetTickx(1);
   p_3_0->SetTicky(1);
   p_3_0->SetLeftMargin(0);
   p_3_0->SetRightMargin(0);
   p_3_0->SetTopMargin(0.05);
   p_3_0->SetBottomMargin(0);
   p_3_0->SetFrameLineColor(0);
   p_3_0->SetFrameBorderMode(0);
   p_3_0->SetFrameLineColor(0);
   p_3_0->SetFrameBorderMode(0);
   Double_t xAxis28[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt9__28 = new TH1D("hPbPbUnfSq_ipt9__28","",9, xAxis28);
   hPbPbUnfSq_ipt9__28->SetBinContent(2,4.168662e-06);
   hPbPbUnfSq_ipt9__28->SetBinContent(3,8.002589e-05);
   hPbPbUnfSq_ipt9__28->SetBinContent(4,0.000145106);
   hPbPbUnfSq_ipt9__28->SetBinContent(5,0.0001221079);
   hPbPbUnfSq_ipt9__28->SetBinContent(6,6.912955e-05);
   hPbPbUnfSq_ipt9__28->SetBinContent(7,3.023197e-05);
   hPbPbUnfSq_ipt9__28->SetBinContent(8,5.812101e-06);
   hPbPbUnfSq_ipt9__28->SetBinContent(9,5.685667e-08);
   hPbPbUnfSq_ipt9__28->SetBinError(2,1.660734e-07);
   hPbPbUnfSq_ipt9__28->SetBinError(3,2.166069e-06);
   hPbPbUnfSq_ipt9__28->SetBinError(4,2.851744e-06);
   hPbPbUnfSq_ipt9__28->SetBinError(5,2.650474e-06);
   hPbPbUnfSq_ipt9__28->SetBinError(6,2.234607e-06);
   hPbPbUnfSq_ipt9__28->SetBinError(7,1.54832e-06);
   hPbPbUnfSq_ipt9__28->SetBinError(8,5.459811e-07);
   hPbPbUnfSq_ipt9__28->SetBinError(9,9.012638e-09);
   hPbPbUnfSq_ipt9__28->SetMinimum(0);
   hPbPbUnfSq_ipt9__28->SetMaximum(0.0002902119);
   hPbPbUnfSq_ipt9__28->SetEntries(7525.19);
   hPbPbUnfSq_ipt9__28->SetStats(0);
   hPbPbUnfSq_ipt9__28->SetLineStyle(0);
   hPbPbUnfSq_ipt9__28->SetMarkerStyle(20);
   hPbPbUnfSq_ipt9__28->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt9__28->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt9__28->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt9__28->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt9__28->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt9__28->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt9__28->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt9__28->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt9__28->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt9__28->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt9__28->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt9__28->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt9__28->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt9__28->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt9__28->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt9__28->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt9__28->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt9__28->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt9__28->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt9__28->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt9__28->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt9__28->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt9__28->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt9__28->Draw("");
   box = new TBox(0,4.168662e-06,0.03,5.435484e-06);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.03,8.002589e-05,0.06,9.991913e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.06,0.000145106,0.09,0.0001656132);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.09,0.0001221079,0.12,0.0001395801);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.12,6.912955e-05,0.15,9.280446e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.15,3.023197e-05,0.18,4.510047e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.18,5.812101e-06,0.24,8.656434e-06);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0,2.904468e-06,0.03,4.168662e-06);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.03,6.031117e-05,0.06,8.002589e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.06,0.0001248771,0.09,0.000145106);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.09,0.0001047913,0.12,0.0001221079);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.12,4.551396e-05,0.15,6.912955e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.15,1.543803e-05,0.18,3.023197e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.18,3.092865e-06,0.24,5.812101e-06);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   Double_t xAxis29[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt9__29 = new TH1D("hPbPbUnfSq_ipt9__29","",9, xAxis29);
   hPbPbUnfSq_ipt9__29->SetBinContent(2,4.168662e-06);
   hPbPbUnfSq_ipt9__29->SetBinContent(3,8.002589e-05);
   hPbPbUnfSq_ipt9__29->SetBinContent(4,0.000145106);
   hPbPbUnfSq_ipt9__29->SetBinContent(5,0.0001221079);
   hPbPbUnfSq_ipt9__29->SetBinContent(6,6.912955e-05);
   hPbPbUnfSq_ipt9__29->SetBinContent(7,3.023197e-05);
   hPbPbUnfSq_ipt9__29->SetBinContent(8,5.812101e-06);
   hPbPbUnfSq_ipt9__29->SetBinContent(9,5.685667e-08);
   hPbPbUnfSq_ipt9__29->SetBinError(2,1.660734e-07);
   hPbPbUnfSq_ipt9__29->SetBinError(3,2.166069e-06);
   hPbPbUnfSq_ipt9__29->SetBinError(4,2.851744e-06);
   hPbPbUnfSq_ipt9__29->SetBinError(5,2.650474e-06);
   hPbPbUnfSq_ipt9__29->SetBinError(6,2.234607e-06);
   hPbPbUnfSq_ipt9__29->SetBinError(7,1.54832e-06);
   hPbPbUnfSq_ipt9__29->SetBinError(8,5.459811e-07);
   hPbPbUnfSq_ipt9__29->SetBinError(9,9.012638e-09);
   hPbPbUnfSq_ipt9__29->SetMinimum(0);
   hPbPbUnfSq_ipt9__29->SetMaximum(0.0002902119);
   hPbPbUnfSq_ipt9__29->SetEntries(7525.19);
   hPbPbUnfSq_ipt9__29->SetStats(0);
   hPbPbUnfSq_ipt9__29->SetLineStyle(0);
   hPbPbUnfSq_ipt9__29->SetMarkerStyle(20);
   hPbPbUnfSq_ipt9__29->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt9__29->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt9__29->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt9__29->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt9__29->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt9__29->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt9__29->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt9__29->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt9__29->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt9__29->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt9__29->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt9__29->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt9__29->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt9__29->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt9__29->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt9__29->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt9__29->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt9__29->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt9__29->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt9__29->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt9__29->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt9__29->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt9__29->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt9__29->Draw("same");
      tex = new TLatex(0.18,0.6,"251 < p_{T}^{jet} < 316 GeV");
tex->SetNDC();
   tex->SetTextFont(43);
   tex->SetTextSize(18);
   tex->Draw();
   Double_t xAxis30[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt9_copy__30 = new TH1D("hPbPbUnfSq_ipt9_copy__30","",9, xAxis30);
   hPbPbUnfSq_ipt9_copy__30->SetBinContent(2,4.168662e-06);
   hPbPbUnfSq_ipt9_copy__30->SetBinContent(3,8.002589e-05);
   hPbPbUnfSq_ipt9_copy__30->SetBinContent(4,0.000145106);
   hPbPbUnfSq_ipt9_copy__30->SetBinContent(5,0.0001221079);
   hPbPbUnfSq_ipt9_copy__30->SetBinContent(6,6.912955e-05);
   hPbPbUnfSq_ipt9_copy__30->SetBinContent(7,3.023197e-05);
   hPbPbUnfSq_ipt9_copy__30->SetBinContent(8,5.812101e-06);
   hPbPbUnfSq_ipt9_copy__30->SetBinContent(9,5.685667e-08);
   hPbPbUnfSq_ipt9_copy__30->SetBinError(2,1.660734e-07);
   hPbPbUnfSq_ipt9_copy__30->SetBinError(3,2.166069e-06);
   hPbPbUnfSq_ipt9_copy__30->SetBinError(4,2.851744e-06);
   hPbPbUnfSq_ipt9_copy__30->SetBinError(5,2.650474e-06);
   hPbPbUnfSq_ipt9_copy__30->SetBinError(6,2.234607e-06);
   hPbPbUnfSq_ipt9_copy__30->SetBinError(7,1.54832e-06);
   hPbPbUnfSq_ipt9_copy__30->SetBinError(8,5.459811e-07);
   hPbPbUnfSq_ipt9_copy__30->SetBinError(9,9.012638e-09);
   hPbPbUnfSq_ipt9_copy__30->SetMinimum(0);
   hPbPbUnfSq_ipt9_copy__30->SetMaximum(0.0002902119);
   hPbPbUnfSq_ipt9_copy__30->SetEntries(7525.19);
   hPbPbUnfSq_ipt9_copy__30->SetDirectory(0);
   hPbPbUnfSq_ipt9_copy__30->SetStats(0);
   hPbPbUnfSq_ipt9_copy__30->SetLineStyle(0);
   hPbPbUnfSq_ipt9_copy__30->SetMarkerStyle(20);
   hPbPbUnfSq_ipt9_copy__30->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt9_copy__30->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt9_copy__30->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt9_copy__30->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt9_copy__30->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt9_copy__30->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt9_copy__30->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt9_copy__30->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt9_copy__30->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt9_copy__30->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt9_copy__30->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt9_copy__30->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt9_copy__30->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt9_copy__30->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt9_copy__30->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt9_copy__30->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt9_copy__30->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt9_copy__30->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt9_copy__30->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt9_copy__30->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt9_copy__30->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt9_copy__30->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt9_copy__30->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt9_copy__30->Draw("sameaxis");
   
   leg = new TLegend(0,0.955,0.5,1,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   leg->Draw();
   p_3_0->Modified();
   c1->cd();
  
// ------------>Primitives in pad: p_3_1
   TPad *p_3_1 = new TPad("p_3_1", "p_3_1",0.536855,0.3998446,0.6885749,0.692228);
   p_3_1->Draw();
   p_3_1->cd();
   p_3_1->Range(0,0,0.24,0.0004028536);
   p_3_1->SetFillColor(0);
   p_3_1->SetBorderMode(0);
   p_3_1->SetBorderSize(0);
   p_3_1->SetTickx(1);
   p_3_1->SetTicky(1);
   p_3_1->SetLeftMargin(0);
   p_3_1->SetRightMargin(0);
   p_3_1->SetTopMargin(0);
   p_3_1->SetBottomMargin(0);
   p_3_1->SetFrameLineColor(0);
   p_3_1->SetFrameBorderMode(0);
   p_3_1->SetFrameLineColor(0);
   p_3_1->SetFrameBorderMode(0);
   Double_t xAxis31[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt9__31 = new TH1D("hPbPbUnfSq_ipt9__31","",9, xAxis31);
   hPbPbUnfSq_ipt9__31->SetBinContent(2,5.824144e-06);
   hPbPbUnfSq_ipt9__31->SetBinContent(3,0.000109499);
   hPbPbUnfSq_ipt9__31->SetBinContent(4,0.0002014268);
   hPbPbUnfSq_ipt9__31->SetBinContent(5,0.0001753483);
   hPbPbUnfSq_ipt9__31->SetBinContent(6,9.303782e-05);
   hPbPbUnfSq_ipt9__31->SetBinContent(7,3.674711e-05);
   hPbPbUnfSq_ipt9__31->SetBinContent(8,1.044163e-05);
   hPbPbUnfSq_ipt9__31->SetBinContent(9,4.251344e-07);
   hPbPbUnfSq_ipt9__31->SetBinError(2,5.557492e-07);
   hPbPbUnfSq_ipt9__31->SetBinError(3,5.818643e-06);
   hPbPbUnfSq_ipt9__31->SetBinError(4,7.73776e-06);
   hPbPbUnfSq_ipt9__31->SetBinError(5,7.516123e-06);
   hPbPbUnfSq_ipt9__31->SetBinError(6,6.083787e-06);
   hPbPbUnfSq_ipt9__31->SetBinError(7,4.060685e-06);
   hPbPbUnfSq_ipt9__31->SetBinError(8,1.730564e-06);
   hPbPbUnfSq_ipt9__31->SetBinError(9,1.778454e-07);
   hPbPbUnfSq_ipt9__31->SetMinimum(0);
   hPbPbUnfSq_ipt9__31->SetMaximum(0.0004028536);
   hPbPbUnfSq_ipt9__31->SetEntries(1925.564);
   hPbPbUnfSq_ipt9__31->SetStats(0);
   hPbPbUnfSq_ipt9__31->SetLineStyle(0);
   hPbPbUnfSq_ipt9__31->SetMarkerStyle(20);
   hPbPbUnfSq_ipt9__31->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt9__31->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt9__31->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt9__31->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt9__31->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt9__31->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt9__31->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt9__31->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt9__31->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt9__31->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt9__31->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt9__31->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt9__31->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt9__31->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt9__31->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt9__31->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt9__31->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt9__31->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt9__31->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt9__31->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt9__31->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt9__31->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt9__31->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt9__31->Draw("");
   box = new TBox(0,5.824144e-06,0.03,8.304695e-06);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.03,0.000109499,0.06,0.0001442761);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.06,0.0002014268,0.09,0.0002274994);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.09,0.0001753483,0.12,0.0002091363);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.12,9.303782e-05,0.15,0.000128668);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.15,3.674711e-05,0.18,4.872483e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.18,1.044163e-05,0.24,1.442447e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0,3.295748e-06,0.03,5.824144e-06);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.03,7.455627e-05,0.06,0.000109499);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.06,0.0001760228,0.09,0.0002014268);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.09,0.0001421397,0.12,0.0001753483);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.12,5.760706e-05,0.15,9.303782e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.15,2.510205e-05,0.18,3.674711e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.18,6.506752e-06,0.24,1.044163e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   Double_t xAxis32[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt9__32 = new TH1D("hPbPbUnfSq_ipt9__32","",9, xAxis32);
   hPbPbUnfSq_ipt9__32->SetBinContent(2,5.824144e-06);
   hPbPbUnfSq_ipt9__32->SetBinContent(3,0.000109499);
   hPbPbUnfSq_ipt9__32->SetBinContent(4,0.0002014268);
   hPbPbUnfSq_ipt9__32->SetBinContent(5,0.0001753483);
   hPbPbUnfSq_ipt9__32->SetBinContent(6,9.303782e-05);
   hPbPbUnfSq_ipt9__32->SetBinContent(7,3.674711e-05);
   hPbPbUnfSq_ipt9__32->SetBinContent(8,1.044163e-05);
   hPbPbUnfSq_ipt9__32->SetBinContent(9,4.251344e-07);
   hPbPbUnfSq_ipt9__32->SetBinError(2,5.557492e-07);
   hPbPbUnfSq_ipt9__32->SetBinError(3,5.818643e-06);
   hPbPbUnfSq_ipt9__32->SetBinError(4,7.73776e-06);
   hPbPbUnfSq_ipt9__32->SetBinError(5,7.516123e-06);
   hPbPbUnfSq_ipt9__32->SetBinError(6,6.083787e-06);
   hPbPbUnfSq_ipt9__32->SetBinError(7,4.060685e-06);
   hPbPbUnfSq_ipt9__32->SetBinError(8,1.730564e-06);
   hPbPbUnfSq_ipt9__32->SetBinError(9,1.778454e-07);
   hPbPbUnfSq_ipt9__32->SetMinimum(0);
   hPbPbUnfSq_ipt9__32->SetMaximum(0.0004028536);
   hPbPbUnfSq_ipt9__32->SetEntries(1925.564);
   hPbPbUnfSq_ipt9__32->SetStats(0);
   hPbPbUnfSq_ipt9__32->SetLineStyle(0);
   hPbPbUnfSq_ipt9__32->SetMarkerStyle(20);
   hPbPbUnfSq_ipt9__32->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt9__32->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt9__32->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt9__32->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt9__32->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt9__32->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt9__32->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt9__32->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt9__32->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt9__32->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt9__32->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt9__32->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt9__32->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt9__32->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt9__32->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt9__32->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt9__32->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt9__32->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt9__32->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt9__32->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt9__32->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt9__32->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt9__32->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt9__32->Draw("same");
   Double_t xAxis33[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt9_copy__33 = new TH1D("hPbPbUnfSq_ipt9_copy__33","",9, xAxis33);
   hPbPbUnfSq_ipt9_copy__33->SetBinContent(2,5.824144e-06);
   hPbPbUnfSq_ipt9_copy__33->SetBinContent(3,0.000109499);
   hPbPbUnfSq_ipt9_copy__33->SetBinContent(4,0.0002014268);
   hPbPbUnfSq_ipt9_copy__33->SetBinContent(5,0.0001753483);
   hPbPbUnfSq_ipt9_copy__33->SetBinContent(6,9.303782e-05);
   hPbPbUnfSq_ipt9_copy__33->SetBinContent(7,3.674711e-05);
   hPbPbUnfSq_ipt9_copy__33->SetBinContent(8,1.044163e-05);
   hPbPbUnfSq_ipt9_copy__33->SetBinContent(9,4.251344e-07);
   hPbPbUnfSq_ipt9_copy__33->SetBinError(2,5.557492e-07);
   hPbPbUnfSq_ipt9_copy__33->SetBinError(3,5.818643e-06);
   hPbPbUnfSq_ipt9_copy__33->SetBinError(4,7.73776e-06);
   hPbPbUnfSq_ipt9_copy__33->SetBinError(5,7.516123e-06);
   hPbPbUnfSq_ipt9_copy__33->SetBinError(6,6.083787e-06);
   hPbPbUnfSq_ipt9_copy__33->SetBinError(7,4.060685e-06);
   hPbPbUnfSq_ipt9_copy__33->SetBinError(8,1.730564e-06);
   hPbPbUnfSq_ipt9_copy__33->SetBinError(9,1.778454e-07);
   hPbPbUnfSq_ipt9_copy__33->SetMinimum(0);
   hPbPbUnfSq_ipt9_copy__33->SetMaximum(0.0004028536);
   hPbPbUnfSq_ipt9_copy__33->SetEntries(1925.564);
   hPbPbUnfSq_ipt9_copy__33->SetDirectory(0);
   hPbPbUnfSq_ipt9_copy__33->SetStats(0);
   hPbPbUnfSq_ipt9_copy__33->SetLineStyle(0);
   hPbPbUnfSq_ipt9_copy__33->SetMarkerStyle(20);
   hPbPbUnfSq_ipt9_copy__33->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt9_copy__33->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt9_copy__33->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt9_copy__33->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt9_copy__33->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt9_copy__33->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt9_copy__33->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt9_copy__33->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt9_copy__33->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt9_copy__33->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt9_copy__33->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt9_copy__33->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt9_copy__33->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt9_copy__33->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt9_copy__33->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt9_copy__33->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt9_copy__33->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt9_copy__33->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt9_copy__33->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt9_copy__33->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt9_copy__33->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt9_copy__33->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt9_copy__33->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt9_copy__33->Draw("sameaxis");
   p_3_1->Modified();
   c1->cd();
  
// ------------>Primitives in pad: p_3_2
   TPad *p_3_2 = new TPad("p_3_2", "p_3_2",0.536855,0.01,0.6885749,0.3998446);
   p_3_2->Draw();
   p_3_2->cd();
   p_3_2->Range(0,-0.0001739893,0.24,0.0005219679);
   p_3_2->SetFillColor(0);
   p_3_2->SetBorderMode(0);
   p_3_2->SetBorderSize(0);
   p_3_2->SetTickx(1);
   p_3_2->SetTicky(1);
   p_3_2->SetLeftMargin(0);
   p_3_2->SetRightMargin(0);
   p_3_2->SetTopMargin(0);
   p_3_2->SetBottomMargin(0.25);
   p_3_2->SetFrameLineColor(0);
   p_3_2->SetFrameBorderMode(0);
   p_3_2->SetFrameLineColor(0);
   p_3_2->SetFrameBorderMode(0);
   Double_t xAxis34[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt9__34 = new TH1D("hPbPbUnfSq_ipt9__34","",9, xAxis34);
   hPbPbUnfSq_ipt9__34->SetBinContent(2,6.780682e-06);
   hPbPbUnfSq_ipt9__34->SetBinContent(3,0.0001378349);
   hPbPbUnfSq_ipt9__34->SetBinContent(4,0.000260984);
   hPbPbUnfSq_ipt9__34->SetBinContent(5,0.0002488067);
   hPbPbUnfSq_ipt9__34->SetBinContent(6,0.0001369533);
   hPbPbUnfSq_ipt9__34->SetBinContent(7,3.463878e-05);
   hPbPbUnfSq_ipt9__34->SetBinContent(8,1.370029e-05);
   hPbPbUnfSq_ipt9__34->SetBinContent(9,1.772363e-08);
   hPbPbUnfSq_ipt9__34->SetBinError(2,1.552029e-06);
   hPbPbUnfSq_ipt9__34->SetBinError(3,1.649321e-05);
   hPbPbUnfSq_ipt9__34->SetBinError(4,2.283738e-05);
   hPbPbUnfSq_ipt9__34->SetBinError(5,2.263075e-05);
   hPbPbUnfSq_ipt9__34->SetBinError(6,1.997856e-05);
   hPbPbUnfSq_ipt9__34->SetBinError(7,9.557202e-06);
   hPbPbUnfSq_ipt9__34->SetBinError(8,5.095362e-06);
   hPbPbUnfSq_ipt9__34->SetBinError(9,5.574167e-09);
   hPbPbUnfSq_ipt9__34->SetMinimum(0);
   hPbPbUnfSq_ipt9__34->SetMaximum(0.0005219679);
   hPbPbUnfSq_ipt9__34->SetEntries(391.8455);
   hPbPbUnfSq_ipt9__34->SetStats(0);
   hPbPbUnfSq_ipt9__34->SetLineStyle(0);
   hPbPbUnfSq_ipt9__34->SetMarkerStyle(20);
   hPbPbUnfSq_ipt9__34->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt9__34->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt9__34->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt9__34->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt9__34->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt9__34->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt9__34->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt9__34->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt9__34->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt9__34->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt9__34->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt9__34->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt9__34->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt9__34->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt9__34->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt9__34->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt9__34->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt9__34->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt9__34->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt9__34->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt9__34->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt9__34->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt9__34->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt9__34->Draw("");
   box = new TBox(0,6.780682e-06,0.03,1.16315e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.03,0.0001378349,0.06,0.0001933705);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.06,0.000260984,0.09,0.0002943337);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.09,0.0002488067,0.12,0.0002903583);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.12,0.0001369533,0.15,0.0002023206);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.15,3.463878e-05,0.18,4.847735e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.18,1.370029e-05,0.24,1.853002e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0,1.965096e-06,0.03,6.780682e-06);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.03,8.23001e-05,0.06,0.0001378349);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.06,0.0002271785,0.09,0.000260984);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.09,0.0002073328,0.12,0.0002488067);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.12,7.16128e-05,0.15,0.0001369533);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.15,2.061722e-05,0.18,3.463878e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.18,8.791486e-06,0.24,1.370029e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   Double_t xAxis35[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt9__35 = new TH1D("hPbPbUnfSq_ipt9__35","",9, xAxis35);
   hPbPbUnfSq_ipt9__35->SetBinContent(2,6.780682e-06);
   hPbPbUnfSq_ipt9__35->SetBinContent(3,0.0001378349);
   hPbPbUnfSq_ipt9__35->SetBinContent(4,0.000260984);
   hPbPbUnfSq_ipt9__35->SetBinContent(5,0.0002488067);
   hPbPbUnfSq_ipt9__35->SetBinContent(6,0.0001369533);
   hPbPbUnfSq_ipt9__35->SetBinContent(7,3.463878e-05);
   hPbPbUnfSq_ipt9__35->SetBinContent(8,1.370029e-05);
   hPbPbUnfSq_ipt9__35->SetBinContent(9,1.772363e-08);
   hPbPbUnfSq_ipt9__35->SetBinError(2,1.552029e-06);
   hPbPbUnfSq_ipt9__35->SetBinError(3,1.649321e-05);
   hPbPbUnfSq_ipt9__35->SetBinError(4,2.283738e-05);
   hPbPbUnfSq_ipt9__35->SetBinError(5,2.263075e-05);
   hPbPbUnfSq_ipt9__35->SetBinError(6,1.997856e-05);
   hPbPbUnfSq_ipt9__35->SetBinError(7,9.557202e-06);
   hPbPbUnfSq_ipt9__35->SetBinError(8,5.095362e-06);
   hPbPbUnfSq_ipt9__35->SetBinError(9,5.574167e-09);
   hPbPbUnfSq_ipt9__35->SetMinimum(0);
   hPbPbUnfSq_ipt9__35->SetMaximum(0.0005219679);
   hPbPbUnfSq_ipt9__35->SetEntries(391.8455);
   hPbPbUnfSq_ipt9__35->SetStats(0);
   hPbPbUnfSq_ipt9__35->SetLineStyle(0);
   hPbPbUnfSq_ipt9__35->SetMarkerStyle(20);
   hPbPbUnfSq_ipt9__35->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt9__35->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt9__35->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt9__35->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt9__35->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt9__35->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt9__35->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt9__35->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt9__35->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt9__35->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt9__35->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt9__35->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt9__35->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt9__35->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt9__35->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt9__35->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt9__35->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt9__35->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt9__35->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt9__35->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt9__35->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt9__35->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt9__35->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt9__35->Draw("same");
   Double_t xAxis36[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt9_copy__36 = new TH1D("hPbPbUnfSq_ipt9_copy__36","",9, xAxis36);
   hPbPbUnfSq_ipt9_copy__36->SetBinContent(2,6.780682e-06);
   hPbPbUnfSq_ipt9_copy__36->SetBinContent(3,0.0001378349);
   hPbPbUnfSq_ipt9_copy__36->SetBinContent(4,0.000260984);
   hPbPbUnfSq_ipt9_copy__36->SetBinContent(5,0.0002488067);
   hPbPbUnfSq_ipt9_copy__36->SetBinContent(6,0.0001369533);
   hPbPbUnfSq_ipt9_copy__36->SetBinContent(7,3.463878e-05);
   hPbPbUnfSq_ipt9_copy__36->SetBinContent(8,1.370029e-05);
   hPbPbUnfSq_ipt9_copy__36->SetBinContent(9,1.772363e-08);
   hPbPbUnfSq_ipt9_copy__36->SetBinError(2,1.552029e-06);
   hPbPbUnfSq_ipt9_copy__36->SetBinError(3,1.649321e-05);
   hPbPbUnfSq_ipt9_copy__36->SetBinError(4,2.283738e-05);
   hPbPbUnfSq_ipt9_copy__36->SetBinError(5,2.263075e-05);
   hPbPbUnfSq_ipt9_copy__36->SetBinError(6,1.997856e-05);
   hPbPbUnfSq_ipt9_copy__36->SetBinError(7,9.557202e-06);
   hPbPbUnfSq_ipt9_copy__36->SetBinError(8,5.095362e-06);
   hPbPbUnfSq_ipt9_copy__36->SetBinError(9,5.574167e-09);
   hPbPbUnfSq_ipt9_copy__36->SetMinimum(0);
   hPbPbUnfSq_ipt9_copy__36->SetMaximum(0.0005219679);
   hPbPbUnfSq_ipt9_copy__36->SetEntries(391.8455);
   hPbPbUnfSq_ipt9_copy__36->SetDirectory(0);
   hPbPbUnfSq_ipt9_copy__36->SetStats(0);
   hPbPbUnfSq_ipt9_copy__36->SetLineStyle(0);
   hPbPbUnfSq_ipt9_copy__36->SetMarkerStyle(20);
   hPbPbUnfSq_ipt9_copy__36->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt9_copy__36->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt9_copy__36->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt9_copy__36->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt9_copy__36->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt9_copy__36->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt9_copy__36->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt9_copy__36->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt9_copy__36->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt9_copy__36->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt9_copy__36->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt9_copy__36->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt9_copy__36->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt9_copy__36->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt9_copy__36->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt9_copy__36->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt9_copy__36->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt9_copy__36->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt9_copy__36->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt9_copy__36->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt9_copy__36->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt9_copy__36->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt9_copy__36->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt9_copy__36->Draw("sameaxis");
   p_3_2->Modified();
   c1->cd();
  
// ------------>Primitives in pad: p_4_0
   TPad *p_4_0 = new TPad("p_4_0", "p_4_0",0.6885749,0.692228,0.8402948,1);
   p_4_0->Draw();
   p_4_0->cd();
   p_4_0->Range(0,0,0.24,7.433301e-05);
   p_4_0->SetFillColor(0);
   p_4_0->SetBorderMode(0);
   p_4_0->SetBorderSize(0);
   p_4_0->SetTickx(1);
   p_4_0->SetTicky(1);
   p_4_0->SetLeftMargin(0);
   p_4_0->SetRightMargin(0);
   p_4_0->SetTopMargin(0.05);
   p_4_0->SetBottomMargin(0);
   p_4_0->SetFrameLineColor(0);
   p_4_0->SetFrameBorderMode(0);
   p_4_0->SetFrameLineColor(0);
   p_4_0->SetFrameBorderMode(0);
   Double_t xAxis37[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt10__37 = new TH1D("hPbPbUnfSq_ipt10__37","",9, xAxis37);
   hPbPbUnfSq_ipt10__37->SetBinContent(2,2.004832e-06);
   hPbPbUnfSq_ipt10__37->SetBinContent(3,2.66806e-05);
   hPbPbUnfSq_ipt10__37->SetBinContent(4,3.530818e-05);
   hPbPbUnfSq_ipt10__37->SetBinContent(5,2.328274e-05);
   hPbPbUnfSq_ipt10__37->SetBinContent(6,1.265021e-05);
   hPbPbUnfSq_ipt10__37->SetBinContent(7,5.250903e-06);
   hPbPbUnfSq_ipt10__37->SetBinContent(8,6.647442e-07);
   hPbPbUnfSq_ipt10__37->SetBinContent(9,2.699255e-08);
   hPbPbUnfSq_ipt10__37->SetBinError(2,1.441924e-07);
   hPbPbUnfSq_ipt10__37->SetBinError(3,1.240605e-06);
   hPbPbUnfSq_ipt10__37->SetBinError(4,1.270194e-06);
   hPbPbUnfSq_ipt10__37->SetBinError(5,1.118624e-06);
   hPbPbUnfSq_ipt10__37->SetBinError(6,9.271793e-07);
   hPbPbUnfSq_ipt10__37->SetBinError(7,6.436772e-07);
   hPbPbUnfSq_ipt10__37->SetBinError(8,1.637324e-07);
   hPbPbUnfSq_ipt10__37->SetBinError(9,2.036714e-08);
   hPbPbUnfSq_ipt10__37->SetMinimum(0);
   hPbPbUnfSq_ipt10__37->SetMaximum(7.061636e-05);
   hPbPbUnfSq_ipt10__37->SetEntries(1964.277);
   hPbPbUnfSq_ipt10__37->SetStats(0);
   hPbPbUnfSq_ipt10__37->SetLineStyle(0);
   hPbPbUnfSq_ipt10__37->SetMarkerStyle(20);
   hPbPbUnfSq_ipt10__37->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt10__37->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt10__37->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt10__37->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt10__37->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt10__37->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt10__37->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt10__37->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt10__37->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt10__37->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt10__37->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt10__37->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt10__37->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt10__37->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt10__37->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt10__37->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt10__37->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt10__37->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt10__37->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt10__37->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt10__37->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt10__37->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt10__37->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt10__37->Draw("");
   box = new TBox(0,2.004832e-06,0.03,2.730267e-06);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.03,2.66806e-05,0.06,3.395428e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.06,3.530818e-05,0.09,3.888228e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.09,2.328274e-05,0.12,2.935225e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.12,1.265021e-05,0.15,1.819812e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.15,5.250903e-06,0.18,8.018188e-06);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.18,6.647442e-07,0.24,9.660784e-07);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0,1.270398e-06,0.03,2.004832e-06);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.03,1.937645e-05,0.06,2.66806e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.06,3.172504e-05,0.09,3.530818e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.09,1.712022e-05,0.12,2.328274e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.12,7.054341e-06,0.15,1.265021e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.15,2.47982e-06,0.18,5.250903e-06);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.18,3.704754e-07,0.24,6.647442e-07);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   Double_t xAxis38[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt10__38 = new TH1D("hPbPbUnfSq_ipt10__38","",9, xAxis38);
   hPbPbUnfSq_ipt10__38->SetBinContent(2,2.004832e-06);
   hPbPbUnfSq_ipt10__38->SetBinContent(3,2.66806e-05);
   hPbPbUnfSq_ipt10__38->SetBinContent(4,3.530818e-05);
   hPbPbUnfSq_ipt10__38->SetBinContent(5,2.328274e-05);
   hPbPbUnfSq_ipt10__38->SetBinContent(6,1.265021e-05);
   hPbPbUnfSq_ipt10__38->SetBinContent(7,5.250903e-06);
   hPbPbUnfSq_ipt10__38->SetBinContent(8,6.647442e-07);
   hPbPbUnfSq_ipt10__38->SetBinContent(9,2.699255e-08);
   hPbPbUnfSq_ipt10__38->SetBinError(2,1.441924e-07);
   hPbPbUnfSq_ipt10__38->SetBinError(3,1.240605e-06);
   hPbPbUnfSq_ipt10__38->SetBinError(4,1.270194e-06);
   hPbPbUnfSq_ipt10__38->SetBinError(5,1.118624e-06);
   hPbPbUnfSq_ipt10__38->SetBinError(6,9.271793e-07);
   hPbPbUnfSq_ipt10__38->SetBinError(7,6.436772e-07);
   hPbPbUnfSq_ipt10__38->SetBinError(8,1.637324e-07);
   hPbPbUnfSq_ipt10__38->SetBinError(9,2.036714e-08);
   hPbPbUnfSq_ipt10__38->SetMinimum(0);
   hPbPbUnfSq_ipt10__38->SetMaximum(7.061636e-05);
   hPbPbUnfSq_ipt10__38->SetEntries(1964.277);
   hPbPbUnfSq_ipt10__38->SetStats(0);
   hPbPbUnfSq_ipt10__38->SetLineStyle(0);
   hPbPbUnfSq_ipt10__38->SetMarkerStyle(20);
   hPbPbUnfSq_ipt10__38->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt10__38->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt10__38->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt10__38->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt10__38->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt10__38->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt10__38->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt10__38->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt10__38->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt10__38->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt10__38->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt10__38->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt10__38->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt10__38->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt10__38->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt10__38->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt10__38->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt10__38->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt10__38->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt10__38->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt10__38->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt10__38->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt10__38->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt10__38->Draw("same");
      tex = new TLatex(0.18,0.6,"316 < p_{T}^{jet} < 398 GeV");
tex->SetNDC();
   tex->SetTextFont(43);
   tex->SetTextSize(18);
   tex->Draw();
   Double_t xAxis39[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt10_copy__39 = new TH1D("hPbPbUnfSq_ipt10_copy__39","",9, xAxis39);
   hPbPbUnfSq_ipt10_copy__39->SetBinContent(2,2.004832e-06);
   hPbPbUnfSq_ipt10_copy__39->SetBinContent(3,2.66806e-05);
   hPbPbUnfSq_ipt10_copy__39->SetBinContent(4,3.530818e-05);
   hPbPbUnfSq_ipt10_copy__39->SetBinContent(5,2.328274e-05);
   hPbPbUnfSq_ipt10_copy__39->SetBinContent(6,1.265021e-05);
   hPbPbUnfSq_ipt10_copy__39->SetBinContent(7,5.250903e-06);
   hPbPbUnfSq_ipt10_copy__39->SetBinContent(8,6.647442e-07);
   hPbPbUnfSq_ipt10_copy__39->SetBinContent(9,2.699255e-08);
   hPbPbUnfSq_ipt10_copy__39->SetBinError(2,1.441924e-07);
   hPbPbUnfSq_ipt10_copy__39->SetBinError(3,1.240605e-06);
   hPbPbUnfSq_ipt10_copy__39->SetBinError(4,1.270194e-06);
   hPbPbUnfSq_ipt10_copy__39->SetBinError(5,1.118624e-06);
   hPbPbUnfSq_ipt10_copy__39->SetBinError(6,9.271793e-07);
   hPbPbUnfSq_ipt10_copy__39->SetBinError(7,6.436772e-07);
   hPbPbUnfSq_ipt10_copy__39->SetBinError(8,1.637324e-07);
   hPbPbUnfSq_ipt10_copy__39->SetBinError(9,2.036714e-08);
   hPbPbUnfSq_ipt10_copy__39->SetMinimum(0);
   hPbPbUnfSq_ipt10_copy__39->SetMaximum(7.061636e-05);
   hPbPbUnfSq_ipt10_copy__39->SetEntries(1964.277);
   hPbPbUnfSq_ipt10_copy__39->SetDirectory(0);
   hPbPbUnfSq_ipt10_copy__39->SetStats(0);
   hPbPbUnfSq_ipt10_copy__39->SetLineStyle(0);
   hPbPbUnfSq_ipt10_copy__39->SetMarkerStyle(20);
   hPbPbUnfSq_ipt10_copy__39->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt10_copy__39->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt10_copy__39->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt10_copy__39->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt10_copy__39->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt10_copy__39->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt10_copy__39->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt10_copy__39->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt10_copy__39->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt10_copy__39->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt10_copy__39->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt10_copy__39->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt10_copy__39->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt10_copy__39->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt10_copy__39->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt10_copy__39->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt10_copy__39->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt10_copy__39->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt10_copy__39->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt10_copy__39->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt10_copy__39->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt10_copy__39->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt10_copy__39->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt10_copy__39->Draw("sameaxis");
   
   leg = new TLegend(0,0.955,0.5,1,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   leg->Draw();
   p_4_0->Modified();
   c1->cd();
  
// ------------>Primitives in pad: p_4_1
   TPad *p_4_1 = new TPad("p_4_1", "p_4_1",0.6885749,0.3998446,0.8402948,0.692228);
   p_4_1->Draw();
   p_4_1->cd();
   p_4_1->Range(0,0,0.24,8.636699e-05);
   p_4_1->SetFillColor(0);
   p_4_1->SetBorderMode(0);
   p_4_1->SetBorderSize(0);
   p_4_1->SetTickx(1);
   p_4_1->SetTicky(1);
   p_4_1->SetLeftMargin(0);
   p_4_1->SetRightMargin(0);
   p_4_1->SetTopMargin(0);
   p_4_1->SetBottomMargin(0);
   p_4_1->SetFrameLineColor(0);
   p_4_1->SetFrameBorderMode(0);
   p_4_1->SetFrameLineColor(0);
   p_4_1->SetFrameBorderMode(0);
   Double_t xAxis40[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt10__40 = new TH1D("hPbPbUnfSq_ipt10__40","",9, xAxis40);
   hPbPbUnfSq_ipt10__40->SetBinContent(2,1.887246e-06);
   hPbPbUnfSq_ipt10__40->SetBinContent(3,2.815654e-05);
   hPbPbUnfSq_ipt10__40->SetBinContent(4,4.31835e-05);
   hPbPbUnfSq_ipt10__40->SetBinContent(5,3.013427e-05);
   hPbPbUnfSq_ipt10__40->SetBinContent(6,1.550937e-05);
   hPbPbUnfSq_ipt10__40->SetBinContent(7,7.936777e-06);
   hPbPbUnfSq_ipt10__40->SetBinContent(8,1.219876e-06);
   hPbPbUnfSq_ipt10__40->SetBinContent(9,4.891144e-08);
   hPbPbUnfSq_ipt10__40->SetBinError(2,3.089825e-07);
   hPbPbUnfSq_ipt10__40->SetBinError(3,2.757123e-06);
   hPbPbUnfSq_ipt10__40->SetBinError(4,3.265804e-06);
   hPbPbUnfSq_ipt10__40->SetBinError(5,2.867067e-06);
   hPbPbUnfSq_ipt10__40->SetBinError(6,2.295456e-06);
   hPbPbUnfSq_ipt10__40->SetBinError(7,1.859899e-06);
   hPbPbUnfSq_ipt10__40->SetBinError(8,5.294564e-07);
   hPbPbUnfSq_ipt10__40->SetBinError(9,5.161753e-08);
   hPbPbUnfSq_ipt10__40->SetMinimum(0);
   hPbPbUnfSq_ipt10__40->SetMaximum(8.636699e-05);
   hPbPbUnfSq_ipt10__40->SetEntries(468.0781);
   hPbPbUnfSq_ipt10__40->SetStats(0);
   hPbPbUnfSq_ipt10__40->SetLineStyle(0);
   hPbPbUnfSq_ipt10__40->SetMarkerStyle(20);
   hPbPbUnfSq_ipt10__40->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt10__40->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt10__40->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt10__40->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt10__40->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt10__40->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt10__40->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt10__40->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt10__40->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt10__40->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt10__40->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt10__40->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt10__40->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt10__40->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt10__40->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt10__40->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt10__40->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt10__40->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt10__40->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt10__40->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt10__40->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt10__40->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt10__40->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt10__40->Draw("");
   box = new TBox(0,1.887246e-06,0.03,2.93469e-06);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.03,2.815654e-05,0.06,3.835745e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.06,4.31835e-05,0.09,4.690166e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.09,3.013427e-05,0.12,4.010992e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.12,1.550937e-05,0.15,2.019886e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.15,7.936777e-06,0.18,1.095722e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.18,1.219876e-06,0.24,1.952487e-06);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0,8.36129e-07,0.03,1.887246e-06);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.03,1.791549e-05,0.06,2.815654e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.06,3.928307e-05,0.09,4.31835e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.09,2.016416e-05,0.12,3.013427e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.12,1.086681e-05,0.15,1.550937e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.15,4.928422e-06,0.18,7.936777e-06);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.18,4.901851e-07,0.24,1.219876e-06);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   Double_t xAxis41[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt10__41 = new TH1D("hPbPbUnfSq_ipt10__41","",9, xAxis41);
   hPbPbUnfSq_ipt10__41->SetBinContent(2,1.887246e-06);
   hPbPbUnfSq_ipt10__41->SetBinContent(3,2.815654e-05);
   hPbPbUnfSq_ipt10__41->SetBinContent(4,4.31835e-05);
   hPbPbUnfSq_ipt10__41->SetBinContent(5,3.013427e-05);
   hPbPbUnfSq_ipt10__41->SetBinContent(6,1.550937e-05);
   hPbPbUnfSq_ipt10__41->SetBinContent(7,7.936777e-06);
   hPbPbUnfSq_ipt10__41->SetBinContent(8,1.219876e-06);
   hPbPbUnfSq_ipt10__41->SetBinContent(9,4.891144e-08);
   hPbPbUnfSq_ipt10__41->SetBinError(2,3.089825e-07);
   hPbPbUnfSq_ipt10__41->SetBinError(3,2.757123e-06);
   hPbPbUnfSq_ipt10__41->SetBinError(4,3.265804e-06);
   hPbPbUnfSq_ipt10__41->SetBinError(5,2.867067e-06);
   hPbPbUnfSq_ipt10__41->SetBinError(6,2.295456e-06);
   hPbPbUnfSq_ipt10__41->SetBinError(7,1.859899e-06);
   hPbPbUnfSq_ipt10__41->SetBinError(8,5.294564e-07);
   hPbPbUnfSq_ipt10__41->SetBinError(9,5.161753e-08);
   hPbPbUnfSq_ipt10__41->SetMinimum(0);
   hPbPbUnfSq_ipt10__41->SetMaximum(8.636699e-05);
   hPbPbUnfSq_ipt10__41->SetEntries(468.0781);
   hPbPbUnfSq_ipt10__41->SetStats(0);
   hPbPbUnfSq_ipt10__41->SetLineStyle(0);
   hPbPbUnfSq_ipt10__41->SetMarkerStyle(20);
   hPbPbUnfSq_ipt10__41->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt10__41->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt10__41->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt10__41->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt10__41->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt10__41->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt10__41->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt10__41->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt10__41->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt10__41->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt10__41->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt10__41->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt10__41->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt10__41->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt10__41->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt10__41->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt10__41->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt10__41->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt10__41->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt10__41->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt10__41->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt10__41->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt10__41->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt10__41->Draw("same");
   Double_t xAxis42[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt10_copy__42 = new TH1D("hPbPbUnfSq_ipt10_copy__42","",9, xAxis42);
   hPbPbUnfSq_ipt10_copy__42->SetBinContent(2,1.887246e-06);
   hPbPbUnfSq_ipt10_copy__42->SetBinContent(3,2.815654e-05);
   hPbPbUnfSq_ipt10_copy__42->SetBinContent(4,4.31835e-05);
   hPbPbUnfSq_ipt10_copy__42->SetBinContent(5,3.013427e-05);
   hPbPbUnfSq_ipt10_copy__42->SetBinContent(6,1.550937e-05);
   hPbPbUnfSq_ipt10_copy__42->SetBinContent(7,7.936777e-06);
   hPbPbUnfSq_ipt10_copy__42->SetBinContent(8,1.219876e-06);
   hPbPbUnfSq_ipt10_copy__42->SetBinContent(9,4.891144e-08);
   hPbPbUnfSq_ipt10_copy__42->SetBinError(2,3.089825e-07);
   hPbPbUnfSq_ipt10_copy__42->SetBinError(3,2.757123e-06);
   hPbPbUnfSq_ipt10_copy__42->SetBinError(4,3.265804e-06);
   hPbPbUnfSq_ipt10_copy__42->SetBinError(5,2.867067e-06);
   hPbPbUnfSq_ipt10_copy__42->SetBinError(6,2.295456e-06);
   hPbPbUnfSq_ipt10_copy__42->SetBinError(7,1.859899e-06);
   hPbPbUnfSq_ipt10_copy__42->SetBinError(8,5.294564e-07);
   hPbPbUnfSq_ipt10_copy__42->SetBinError(9,5.161753e-08);
   hPbPbUnfSq_ipt10_copy__42->SetMinimum(0);
   hPbPbUnfSq_ipt10_copy__42->SetMaximum(8.636699e-05);
   hPbPbUnfSq_ipt10_copy__42->SetEntries(468.0781);
   hPbPbUnfSq_ipt10_copy__42->SetDirectory(0);
   hPbPbUnfSq_ipt10_copy__42->SetStats(0);
   hPbPbUnfSq_ipt10_copy__42->SetLineStyle(0);
   hPbPbUnfSq_ipt10_copy__42->SetMarkerStyle(20);
   hPbPbUnfSq_ipt10_copy__42->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt10_copy__42->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt10_copy__42->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt10_copy__42->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt10_copy__42->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt10_copy__42->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt10_copy__42->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt10_copy__42->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt10_copy__42->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt10_copy__42->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt10_copy__42->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt10_copy__42->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt10_copy__42->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt10_copy__42->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt10_copy__42->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt10_copy__42->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt10_copy__42->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt10_copy__42->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt10_copy__42->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt10_copy__42->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt10_copy__42->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt10_copy__42->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt10_copy__42->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt10_copy__42->Draw("sameaxis");
   p_4_1->Modified();
   c1->cd();
  
// ------------>Primitives in pad: p_4_2
   TPad *p_4_2 = new TPad("p_4_2", "p_4_2",0.6885749,0.01,0.8402948,0.3998446);
   p_4_2->Draw();
   p_4_2->cd();
   p_4_2->Range(0,-4.199875e-05,0.24,0.0001259963);
   p_4_2->SetFillColor(0);
   p_4_2->SetBorderMode(0);
   p_4_2->SetBorderSize(0);
   p_4_2->SetTickx(1);
   p_4_2->SetTicky(1);
   p_4_2->SetLeftMargin(0);
   p_4_2->SetRightMargin(0);
   p_4_2->SetTopMargin(0);
   p_4_2->SetBottomMargin(0.25);
   p_4_2->SetFrameLineColor(0);
   p_4_2->SetFrameBorderMode(0);
   p_4_2->SetFrameLineColor(0);
   p_4_2->SetFrameBorderMode(0);
   Double_t xAxis43[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt10__43 = new TH1D("hPbPbUnfSq_ipt10__43","",9, xAxis43);
   hPbPbUnfSq_ipt10__43->SetBinContent(2,4.040432e-06);
   hPbPbUnfSq_ipt10__43->SetBinContent(3,5.042077e-05);
   hPbPbUnfSq_ipt10__43->SetBinContent(4,6.299813e-05);
   hPbPbUnfSq_ipt10__43->SetBinContent(5,4.560068e-05);
   hPbPbUnfSq_ipt10__43->SetBinContent(6,1.915969e-05);
   hPbPbUnfSq_ipt10__43->SetBinContent(7,2.665184e-06);
   hPbPbUnfSq_ipt10__43->SetBinContent(8,2.88488e-06);
   hPbPbUnfSq_ipt10__43->SetBinContent(9,1.203093e-08);
   hPbPbUnfSq_ipt10__43->SetBinError(2,1.40865e-06);
   hPbPbUnfSq_ipt10__43->SetBinError(3,9.97959e-06);
   hPbPbUnfSq_ipt10__43->SetBinError(4,9.604637e-06);
   hPbPbUnfSq_ipt10__43->SetBinError(5,9.116137e-06);
   hPbPbUnfSq_ipt10__43->SetBinError(6,6.840905e-06);
   hPbPbUnfSq_ipt10__43->SetBinError(7,2.191262e-06);
   hPbPbUnfSq_ipt10__43->SetBinError(8,2.176797e-06);
   hPbPbUnfSq_ipt10__43->SetBinError(9,7.922875e-09);
   hPbPbUnfSq_ipt10__43->SetMinimum(0);
   hPbPbUnfSq_ipt10__43->SetMaximum(0.0001259963);
   hPbPbUnfSq_ipt10__43->SetEntries(113.6335);
   hPbPbUnfSq_ipt10__43->SetStats(0);
   hPbPbUnfSq_ipt10__43->SetLineStyle(0);
   hPbPbUnfSq_ipt10__43->SetMarkerStyle(20);
   hPbPbUnfSq_ipt10__43->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt10__43->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt10__43->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt10__43->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt10__43->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt10__43->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt10__43->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt10__43->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt10__43->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt10__43->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt10__43->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt10__43->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt10__43->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt10__43->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt10__43->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt10__43->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt10__43->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt10__43->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt10__43->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt10__43->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt10__43->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt10__43->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt10__43->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt10__43->Draw("");
   box = new TBox(0,4.040432e-06,0.03,7.162864e-06);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.03,5.042077e-05,0.06,7.143866e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.06,6.299813e-05,0.09,7.014226e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.09,4.560068e-05,0.12,6.283999e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.12,1.915969e-05,0.15,3.778331e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.15,2.665184e-06,0.18,3.853077e-06);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.18,2.88488e-06,0.24,4.46958e-06);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0,9.328621e-07,0.03,4.040432e-06);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.03,2.948911e-05,0.06,5.042077e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.06,5.621287e-05,0.09,6.299813e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.09,2.843086e-05,0.12,4.560068e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.12,5.571126e-07,0.15,1.915969e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.15,1.475819e-06,0.18,2.665184e-06);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.18,1.308228e-06,0.24,2.88488e-06);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   Double_t xAxis44[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt10__44 = new TH1D("hPbPbUnfSq_ipt10__44","",9, xAxis44);
   hPbPbUnfSq_ipt10__44->SetBinContent(2,4.040432e-06);
   hPbPbUnfSq_ipt10__44->SetBinContent(3,5.042077e-05);
   hPbPbUnfSq_ipt10__44->SetBinContent(4,6.299813e-05);
   hPbPbUnfSq_ipt10__44->SetBinContent(5,4.560068e-05);
   hPbPbUnfSq_ipt10__44->SetBinContent(6,1.915969e-05);
   hPbPbUnfSq_ipt10__44->SetBinContent(7,2.665184e-06);
   hPbPbUnfSq_ipt10__44->SetBinContent(8,2.88488e-06);
   hPbPbUnfSq_ipt10__44->SetBinContent(9,1.203093e-08);
   hPbPbUnfSq_ipt10__44->SetBinError(2,1.40865e-06);
   hPbPbUnfSq_ipt10__44->SetBinError(3,9.97959e-06);
   hPbPbUnfSq_ipt10__44->SetBinError(4,9.604637e-06);
   hPbPbUnfSq_ipt10__44->SetBinError(5,9.116137e-06);
   hPbPbUnfSq_ipt10__44->SetBinError(6,6.840905e-06);
   hPbPbUnfSq_ipt10__44->SetBinError(7,2.191262e-06);
   hPbPbUnfSq_ipt10__44->SetBinError(8,2.176797e-06);
   hPbPbUnfSq_ipt10__44->SetBinError(9,7.922875e-09);
   hPbPbUnfSq_ipt10__44->SetMinimum(0);
   hPbPbUnfSq_ipt10__44->SetMaximum(0.0001259963);
   hPbPbUnfSq_ipt10__44->SetEntries(113.6335);
   hPbPbUnfSq_ipt10__44->SetStats(0);
   hPbPbUnfSq_ipt10__44->SetLineStyle(0);
   hPbPbUnfSq_ipt10__44->SetMarkerStyle(20);
   hPbPbUnfSq_ipt10__44->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt10__44->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt10__44->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt10__44->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt10__44->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt10__44->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt10__44->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt10__44->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt10__44->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt10__44->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt10__44->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt10__44->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt10__44->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt10__44->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt10__44->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt10__44->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt10__44->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt10__44->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt10__44->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt10__44->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt10__44->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt10__44->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt10__44->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt10__44->Draw("same");
      tex = new TLatex(0.18,0.73,"316 < p_{T}^{jet} < 500 GeV");
tex->SetNDC();
   tex->SetTextFont(43);
   tex->SetTextSize(18);
   tex->Draw();
   Double_t xAxis45[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt10_copy__45 = new TH1D("hPbPbUnfSq_ipt10_copy__45","",9, xAxis45);
   hPbPbUnfSq_ipt10_copy__45->SetBinContent(2,4.040432e-06);
   hPbPbUnfSq_ipt10_copy__45->SetBinContent(3,5.042077e-05);
   hPbPbUnfSq_ipt10_copy__45->SetBinContent(4,6.299813e-05);
   hPbPbUnfSq_ipt10_copy__45->SetBinContent(5,4.560068e-05);
   hPbPbUnfSq_ipt10_copy__45->SetBinContent(6,1.915969e-05);
   hPbPbUnfSq_ipt10_copy__45->SetBinContent(7,2.665184e-06);
   hPbPbUnfSq_ipt10_copy__45->SetBinContent(8,2.88488e-06);
   hPbPbUnfSq_ipt10_copy__45->SetBinContent(9,1.203093e-08);
   hPbPbUnfSq_ipt10_copy__45->SetBinError(2,1.40865e-06);
   hPbPbUnfSq_ipt10_copy__45->SetBinError(3,9.97959e-06);
   hPbPbUnfSq_ipt10_copy__45->SetBinError(4,9.604637e-06);
   hPbPbUnfSq_ipt10_copy__45->SetBinError(5,9.116137e-06);
   hPbPbUnfSq_ipt10_copy__45->SetBinError(6,6.840905e-06);
   hPbPbUnfSq_ipt10_copy__45->SetBinError(7,2.191262e-06);
   hPbPbUnfSq_ipt10_copy__45->SetBinError(8,2.176797e-06);
   hPbPbUnfSq_ipt10_copy__45->SetBinError(9,7.922875e-09);
   hPbPbUnfSq_ipt10_copy__45->SetMinimum(0);
   hPbPbUnfSq_ipt10_copy__45->SetMaximum(0.0001259963);
   hPbPbUnfSq_ipt10_copy__45->SetEntries(113.6335);
   hPbPbUnfSq_ipt10_copy__45->SetDirectory(0);
   hPbPbUnfSq_ipt10_copy__45->SetStats(0);
   hPbPbUnfSq_ipt10_copy__45->SetLineStyle(0);
   hPbPbUnfSq_ipt10_copy__45->SetMarkerStyle(20);
   hPbPbUnfSq_ipt10_copy__45->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt10_copy__45->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt10_copy__45->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt10_copy__45->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt10_copy__45->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt10_copy__45->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt10_copy__45->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt10_copy__45->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt10_copy__45->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt10_copy__45->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt10_copy__45->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt10_copy__45->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt10_copy__45->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt10_copy__45->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt10_copy__45->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt10_copy__45->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt10_copy__45->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt10_copy__45->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt10_copy__45->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt10_copy__45->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt10_copy__45->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt10_copy__45->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt10_copy__45->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt10_copy__45->Draw("sameaxis");
   p_4_2->Modified();
   c1->cd();
  
// ------------>Primitives in pad: p_5_0
   TPad *p_5_0 = new TPad("p_5_0", "p_5_0",0.8402948,0.692228,1,1);
   p_5_0->Draw();
   p_5_0->cd();
   p_5_0->Range(0,0,0.2526316,1.339705e-05);
   p_5_0->SetFillColor(0);
   p_5_0->SetBorderMode(0);
   p_5_0->SetBorderSize(0);
   p_5_0->SetTickx(1);
   p_5_0->SetTicky(1);
   p_5_0->SetLeftMargin(0);
   p_5_0->SetRightMargin(0.05);
   p_5_0->SetTopMargin(0.05);
   p_5_0->SetBottomMargin(0);
   p_5_0->SetFrameLineColor(0);
   p_5_0->SetFrameBorderMode(0);
   p_5_0->SetFrameLineColor(0);
   p_5_0->SetFrameBorderMode(0);
   Double_t xAxis46[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt11__46 = new TH1D("hPbPbUnfSq_ipt11__46","",9, xAxis46);
   hPbPbUnfSq_ipt11__46->SetBinContent(2,5.03517e-07);
   hPbPbUnfSq_ipt11__46->SetBinContent(3,5.841012e-06);
   hPbPbUnfSq_ipt11__46->SetBinContent(4,6.363598e-06);
   hPbPbUnfSq_ipt11__46->SetBinContent(5,3.151134e-06);
   hPbPbUnfSq_ipt11__46->SetBinContent(6,1.54341e-06);
   hPbPbUnfSq_ipt11__46->SetBinContent(7,8.614678e-07);
   hPbPbUnfSq_ipt11__46->SetBinContent(8,1.531375e-07);
   hPbPbUnfSq_ipt11__46->SetBinContent(9,3.294173e-09);
   hPbPbUnfSq_ipt11__46->SetBinError(2,6.70937e-08);
   hPbPbUnfSq_ipt11__46->SetBinError(3,5.389041e-07);
   hPbPbUnfSq_ipt11__46->SetBinError(4,5.125406e-07);
   hPbPbUnfSq_ipt11__46->SetBinError(5,3.89216e-07);
   hPbPbUnfSq_ipt11__46->SetBinError(6,2.886755e-07);
   hPbPbUnfSq_ipt11__46->SetBinError(7,2.454188e-07);
   hPbPbUnfSq_ipt11__46->SetBinError(8,7.974164e-08);
   hPbPbUnfSq_ipt11__46->SetBinError(9,3.325203e-09);
   hPbPbUnfSq_ipt11__46->SetMinimum(0);
   hPbPbUnfSq_ipt11__46->SetMaximum(1.27272e-05);
   hPbPbUnfSq_ipt11__46->SetEntries(401.9913);
   hPbPbUnfSq_ipt11__46->SetStats(0);
   hPbPbUnfSq_ipt11__46->SetLineStyle(0);
   hPbPbUnfSq_ipt11__46->SetMarkerStyle(20);
   hPbPbUnfSq_ipt11__46->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt11__46->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt11__46->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt11__46->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt11__46->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt11__46->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt11__46->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt11__46->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt11__46->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt11__46->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt11__46->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt11__46->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt11__46->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt11__46->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt11__46->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt11__46->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt11__46->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt11__46->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt11__46->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt11__46->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt11__46->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt11__46->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt11__46->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt11__46->Draw("");
   box = new TBox(0,5.03517e-07,0.03,7.795463e-07);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.03,5.841012e-06,0.06,7.685723e-06);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.06,6.363598e-06,0.09,7.243668e-06);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.09,3.151134e-06,0.12,4.543832e-06);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.12,1.54341e-06,0.15,2.12543e-06);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.15,8.614678e-07,0.18,1.174948e-06);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.18,1.531375e-07,0.24,2.317894e-07);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0,2.278743e-07,0.03,5.03517e-07);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.03,4.003249e-06,0.06,5.841012e-06);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.06,5.511355e-06,0.09,6.363598e-06);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.09,1.757662e-06,0.12,3.151134e-06);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.12,9.540195e-07,0.15,1.54341e-06);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.15,5.503414e-07,0.18,8.614678e-07);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.18,7.651389e-08,0.24,1.531375e-07);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   Double_t xAxis47[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt11__47 = new TH1D("hPbPbUnfSq_ipt11__47","",9, xAxis47);
   hPbPbUnfSq_ipt11__47->SetBinContent(2,5.03517e-07);
   hPbPbUnfSq_ipt11__47->SetBinContent(3,5.841012e-06);
   hPbPbUnfSq_ipt11__47->SetBinContent(4,6.363598e-06);
   hPbPbUnfSq_ipt11__47->SetBinContent(5,3.151134e-06);
   hPbPbUnfSq_ipt11__47->SetBinContent(6,1.54341e-06);
   hPbPbUnfSq_ipt11__47->SetBinContent(7,8.614678e-07);
   hPbPbUnfSq_ipt11__47->SetBinContent(8,1.531375e-07);
   hPbPbUnfSq_ipt11__47->SetBinContent(9,3.294173e-09);
   hPbPbUnfSq_ipt11__47->SetBinError(2,6.70937e-08);
   hPbPbUnfSq_ipt11__47->SetBinError(3,5.389041e-07);
   hPbPbUnfSq_ipt11__47->SetBinError(4,5.125406e-07);
   hPbPbUnfSq_ipt11__47->SetBinError(5,3.89216e-07);
   hPbPbUnfSq_ipt11__47->SetBinError(6,2.886755e-07);
   hPbPbUnfSq_ipt11__47->SetBinError(7,2.454188e-07);
   hPbPbUnfSq_ipt11__47->SetBinError(8,7.974164e-08);
   hPbPbUnfSq_ipt11__47->SetBinError(9,3.325203e-09);
   hPbPbUnfSq_ipt11__47->SetMinimum(0);
   hPbPbUnfSq_ipt11__47->SetMaximum(1.27272e-05);
   hPbPbUnfSq_ipt11__47->SetEntries(401.9913);
   hPbPbUnfSq_ipt11__47->SetStats(0);
   hPbPbUnfSq_ipt11__47->SetLineStyle(0);
   hPbPbUnfSq_ipt11__47->SetMarkerStyle(20);
   hPbPbUnfSq_ipt11__47->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt11__47->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt11__47->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt11__47->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt11__47->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt11__47->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt11__47->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt11__47->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt11__47->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt11__47->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt11__47->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt11__47->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt11__47->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt11__47->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt11__47->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt11__47->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt11__47->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt11__47->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt11__47->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt11__47->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt11__47->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt11__47->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt11__47->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt11__47->Draw("same");
      tex = new TLatex(0.18,0.6,"398 < p_{T}^{jet} < 500 GeV");
tex->SetNDC();
   tex->SetTextFont(43);
   tex->SetTextSize(18);
   tex->Draw();
   Double_t xAxis48[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt11_copy__48 = new TH1D("hPbPbUnfSq_ipt11_copy__48","",9, xAxis48);
   hPbPbUnfSq_ipt11_copy__48->SetBinContent(2,5.03517e-07);
   hPbPbUnfSq_ipt11_copy__48->SetBinContent(3,5.841012e-06);
   hPbPbUnfSq_ipt11_copy__48->SetBinContent(4,6.363598e-06);
   hPbPbUnfSq_ipt11_copy__48->SetBinContent(5,3.151134e-06);
   hPbPbUnfSq_ipt11_copy__48->SetBinContent(6,1.54341e-06);
   hPbPbUnfSq_ipt11_copy__48->SetBinContent(7,8.614678e-07);
   hPbPbUnfSq_ipt11_copy__48->SetBinContent(8,1.531375e-07);
   hPbPbUnfSq_ipt11_copy__48->SetBinContent(9,3.294173e-09);
   hPbPbUnfSq_ipt11_copy__48->SetBinError(2,6.70937e-08);
   hPbPbUnfSq_ipt11_copy__48->SetBinError(3,5.389041e-07);
   hPbPbUnfSq_ipt11_copy__48->SetBinError(4,5.125406e-07);
   hPbPbUnfSq_ipt11_copy__48->SetBinError(5,3.89216e-07);
   hPbPbUnfSq_ipt11_copy__48->SetBinError(6,2.886755e-07);
   hPbPbUnfSq_ipt11_copy__48->SetBinError(7,2.454188e-07);
   hPbPbUnfSq_ipt11_copy__48->SetBinError(8,7.974164e-08);
   hPbPbUnfSq_ipt11_copy__48->SetBinError(9,3.325203e-09);
   hPbPbUnfSq_ipt11_copy__48->SetMinimum(0);
   hPbPbUnfSq_ipt11_copy__48->SetMaximum(1.27272e-05);
   hPbPbUnfSq_ipt11_copy__48->SetEntries(401.9913);
   hPbPbUnfSq_ipt11_copy__48->SetDirectory(0);
   hPbPbUnfSq_ipt11_copy__48->SetStats(0);
   hPbPbUnfSq_ipt11_copy__48->SetLineStyle(0);
   hPbPbUnfSq_ipt11_copy__48->SetMarkerStyle(20);
   hPbPbUnfSq_ipt11_copy__48->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt11_copy__48->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt11_copy__48->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt11_copy__48->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt11_copy__48->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt11_copy__48->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt11_copy__48->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt11_copy__48->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt11_copy__48->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt11_copy__48->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt11_copy__48->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt11_copy__48->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt11_copy__48->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt11_copy__48->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt11_copy__48->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt11_copy__48->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt11_copy__48->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt11_copy__48->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt11_copy__48->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt11_copy__48->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt11_copy__48->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt11_copy__48->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt11_copy__48->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt11_copy__48->Draw("sameaxis");
   
   leg = new TLegend(0,0.955,0.5,1,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   leg->Draw();
   p_5_0->Modified();
   c1->cd();
  
// ------------>Primitives in pad: p_5_1
   TPad *p_5_1 = new TPad("p_5_1", "p_5_1",0.8402948,0.3998446,1,0.692228);
   p_5_1->Draw();
   p_5_1->cd();
   p_5_1->Range(0,0,0.2526316,1.67478e-05);
   p_5_1->SetFillColor(0);
   p_5_1->SetBorderMode(0);
   p_5_1->SetBorderSize(0);
   p_5_1->SetTickx(1);
   p_5_1->SetTicky(1);
   p_5_1->SetLeftMargin(0);
   p_5_1->SetRightMargin(0.05);
   p_5_1->SetTopMargin(0);
   p_5_1->SetBottomMargin(0);
   p_5_1->SetFrameLineColor(0);
   p_5_1->SetFrameBorderMode(0);
   p_5_1->SetFrameLineColor(0);
   p_5_1->SetFrameBorderMode(0);
   Double_t xAxis49[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt11__49 = new TH1D("hPbPbUnfSq_ipt11__49","",9, xAxis49);
   hPbPbUnfSq_ipt11__49->SetBinContent(2,7.345704e-07);
   hPbPbUnfSq_ipt11__49->SetBinContent(3,8.373901e-06);
   hPbPbUnfSq_ipt11__49->SetBinContent(4,8.205157e-06);
   hPbPbUnfSq_ipt11__49->SetBinContent(5,4.619608e-06);
   hPbPbUnfSq_ipt11__49->SetBinContent(6,2.641814e-06);
   hPbPbUnfSq_ipt11__49->SetBinContent(7,5.455431e-07);
   hPbPbUnfSq_ipt11__49->SetBinContent(8,1.347674e-07);
   hPbPbUnfSq_ipt11__49->SetBinContent(9,2.988239e-10);
   hPbPbUnfSq_ipt11__49->SetBinError(2,1.932644e-07);
   hPbPbUnfSq_ipt11__49->SetBinError(3,1.448716e-06);
   hPbPbUnfSq_ipt11__49->SetBinError(4,1.280188e-06);
   hPbPbUnfSq_ipt11__49->SetBinError(5,1.041688e-06);
   hPbPbUnfSq_ipt11__49->SetBinError(6,9.241154e-07);
   hPbPbUnfSq_ipt11__49->SetBinError(7,3.822645e-07);
   hPbPbUnfSq_ipt11__49->SetBinError(8,1.623441e-07);
   hPbPbUnfSq_ipt11__49->SetBinError(9,2.198457e-10);
   hPbPbUnfSq_ipt11__49->SetMinimum(0);
   hPbPbUnfSq_ipt11__49->SetMaximum(1.67478e-05);
   hPbPbUnfSq_ipt11__49->SetEntries(117.0666);
   hPbPbUnfSq_ipt11__49->SetStats(0);
   hPbPbUnfSq_ipt11__49->SetLineStyle(0);
   hPbPbUnfSq_ipt11__49->SetMarkerStyle(20);
   hPbPbUnfSq_ipt11__49->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt11__49->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt11__49->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt11__49->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt11__49->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt11__49->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt11__49->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt11__49->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt11__49->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt11__49->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt11__49->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt11__49->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt11__49->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt11__49->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt11__49->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt11__49->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt11__49->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt11__49->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt11__49->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt11__49->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt11__49->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt11__49->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt11__49->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt11__49->Draw("");
   box = new TBox(0,7.345704e-07,0.03,1.253324e-06);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.03,8.373901e-06,0.06,1.102509e-05);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.06,8.205157e-06,0.09,9.706549e-06);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.09,4.619608e-06,0.12,6.015334e-06);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.12,2.641814e-06,0.15,4.064214e-06);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.15,5.455431e-07,0.18,7.558702e-07);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.18,1.347674e-07,0.24,2.235296e-07);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0,2.160691e-07,0.03,7.345704e-07);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.03,5.728293e-06,0.06,8.373901e-06);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.06,6.740777e-06,0.09,8.205157e-06);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.09,3.222419e-06,0.12,4.619608e-06);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.12,1.210463e-06,0.15,2.641814e-06);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.15,3.404839e-07,0.18,5.455431e-07);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   box = new TBox(0.18,4.822654e-08,0.24,1.347674e-07);

   ci = TColor::GetColor("#00cccc");
   box->SetFillColor(ci);

   ci = TColor::GetColor("#00cccc");
   box->SetLineColor(ci);
   box->Draw();
   Double_t xAxis50[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt11__50 = new TH1D("hPbPbUnfSq_ipt11__50","",9, xAxis50);
   hPbPbUnfSq_ipt11__50->SetBinContent(2,7.345704e-07);
   hPbPbUnfSq_ipt11__50->SetBinContent(3,8.373901e-06);
   hPbPbUnfSq_ipt11__50->SetBinContent(4,8.205157e-06);
   hPbPbUnfSq_ipt11__50->SetBinContent(5,4.619608e-06);
   hPbPbUnfSq_ipt11__50->SetBinContent(6,2.641814e-06);
   hPbPbUnfSq_ipt11__50->SetBinContent(7,5.455431e-07);
   hPbPbUnfSq_ipt11__50->SetBinContent(8,1.347674e-07);
   hPbPbUnfSq_ipt11__50->SetBinContent(9,2.988239e-10);
   hPbPbUnfSq_ipt11__50->SetBinError(2,1.932644e-07);
   hPbPbUnfSq_ipt11__50->SetBinError(3,1.448716e-06);
   hPbPbUnfSq_ipt11__50->SetBinError(4,1.280188e-06);
   hPbPbUnfSq_ipt11__50->SetBinError(5,1.041688e-06);
   hPbPbUnfSq_ipt11__50->SetBinError(6,9.241154e-07);
   hPbPbUnfSq_ipt11__50->SetBinError(7,3.822645e-07);
   hPbPbUnfSq_ipt11__50->SetBinError(8,1.623441e-07);
   hPbPbUnfSq_ipt11__50->SetBinError(9,2.198457e-10);
   hPbPbUnfSq_ipt11__50->SetMinimum(0);
   hPbPbUnfSq_ipt11__50->SetMaximum(1.67478e-05);
   hPbPbUnfSq_ipt11__50->SetEntries(117.0666);
   hPbPbUnfSq_ipt11__50->SetStats(0);
   hPbPbUnfSq_ipt11__50->SetLineStyle(0);
   hPbPbUnfSq_ipt11__50->SetMarkerStyle(20);
   hPbPbUnfSq_ipt11__50->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt11__50->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt11__50->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt11__50->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt11__50->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt11__50->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt11__50->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt11__50->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt11__50->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt11__50->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt11__50->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt11__50->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt11__50->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt11__50->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt11__50->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt11__50->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt11__50->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt11__50->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt11__50->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt11__50->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt11__50->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt11__50->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt11__50->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt11__50->Draw("same");
   Double_t xAxis51[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *hPbPbUnfSq_ipt11_copy__51 = new TH1D("hPbPbUnfSq_ipt11_copy__51","",9, xAxis51);
   hPbPbUnfSq_ipt11_copy__51->SetBinContent(2,7.345704e-07);
   hPbPbUnfSq_ipt11_copy__51->SetBinContent(3,8.373901e-06);
   hPbPbUnfSq_ipt11_copy__51->SetBinContent(4,8.205157e-06);
   hPbPbUnfSq_ipt11_copy__51->SetBinContent(5,4.619608e-06);
   hPbPbUnfSq_ipt11_copy__51->SetBinContent(6,2.641814e-06);
   hPbPbUnfSq_ipt11_copy__51->SetBinContent(7,5.455431e-07);
   hPbPbUnfSq_ipt11_copy__51->SetBinContent(8,1.347674e-07);
   hPbPbUnfSq_ipt11_copy__51->SetBinContent(9,2.988239e-10);
   hPbPbUnfSq_ipt11_copy__51->SetBinError(2,1.932644e-07);
   hPbPbUnfSq_ipt11_copy__51->SetBinError(3,1.448716e-06);
   hPbPbUnfSq_ipt11_copy__51->SetBinError(4,1.280188e-06);
   hPbPbUnfSq_ipt11_copy__51->SetBinError(5,1.041688e-06);
   hPbPbUnfSq_ipt11_copy__51->SetBinError(6,9.241154e-07);
   hPbPbUnfSq_ipt11_copy__51->SetBinError(7,3.822645e-07);
   hPbPbUnfSq_ipt11_copy__51->SetBinError(8,1.623441e-07);
   hPbPbUnfSq_ipt11_copy__51->SetBinError(9,2.198457e-10);
   hPbPbUnfSq_ipt11_copy__51->SetMinimum(0);
   hPbPbUnfSq_ipt11_copy__51->SetMaximum(1.67478e-05);
   hPbPbUnfSq_ipt11_copy__51->SetEntries(117.0666);
   hPbPbUnfSq_ipt11_copy__51->SetDirectory(0);
   hPbPbUnfSq_ipt11_copy__51->SetStats(0);
   hPbPbUnfSq_ipt11_copy__51->SetLineStyle(0);
   hPbPbUnfSq_ipt11_copy__51->SetMarkerStyle(20);
   hPbPbUnfSq_ipt11_copy__51->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   hPbPbUnfSq_ipt11_copy__51->GetXaxis()->SetRange(2,8);
   hPbPbUnfSq_ipt11_copy__51->GetXaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt11_copy__51->GetXaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt11_copy__51->GetXaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt11_copy__51->GetXaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt11_copy__51->GetXaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt11_copy__51->GetXaxis()->SetTitleSize(20);
   hPbPbUnfSq_ipt11_copy__51->GetXaxis()->SetTitleOffset(2.8);
   hPbPbUnfSq_ipt11_copy__51->GetXaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt11_copy__51->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   hPbPbUnfSq_ipt11_copy__51->GetYaxis()->CenterTitle(true);
   hPbPbUnfSq_ipt11_copy__51->GetYaxis()->SetNdivisions(505);
   hPbPbUnfSq_ipt11_copy__51->GetYaxis()->SetLabelFont(43);
   hPbPbUnfSq_ipt11_copy__51->GetYaxis()->SetLabelOffset(0.01);
   hPbPbUnfSq_ipt11_copy__51->GetYaxis()->SetLabelSize(18);
   hPbPbUnfSq_ipt11_copy__51->GetYaxis()->SetTitleSize(15);
   hPbPbUnfSq_ipt11_copy__51->GetYaxis()->SetTitleOffset(4.5);
   hPbPbUnfSq_ipt11_copy__51->GetYaxis()->SetTitleFont(43);
   hPbPbUnfSq_ipt11_copy__51->GetZaxis()->SetLabelFont(42);
   hPbPbUnfSq_ipt11_copy__51->GetZaxis()->SetLabelSize(0.045);
   hPbPbUnfSq_ipt11_copy__51->GetZaxis()->SetTitleSize(0.035);
   hPbPbUnfSq_ipt11_copy__51->GetZaxis()->SetTitleFont(42);
   hPbPbUnfSq_ipt11_copy__51->Draw("sameaxis");
   p_5_1->Modified();
   c1->cd();
  
// ------------>Primitives in pad: p_5_2
   TPad *p_5_2 = new TPad("p_5_2", "p_5_2",0.8402948,0.01,1,0.3998446);
   p_5_2->Draw();
   p_5_2->cd();
   p_5_2->Range(0,-0.01673127,0.2526316,1.67478e-05);
   p_5_2->SetFillColor(0);
   p_5_2->SetBorderMode(0);
   p_5_2->SetBorderSize(0);
   p_5_2->SetTickx(1);
   p_5_2->SetTicky(1);
   p_5_2->SetLeftMargin(0);
   p_5_2->SetRightMargin(0.05);
   p_5_2->SetTopMargin(0);
   p_5_2->SetBottomMargin(0.999);
   p_5_2->SetFrameLineColor(0);
   p_5_2->SetFrameBorderMode(0);
   p_5_2->SetFrameLineColor(0);
   p_5_2->SetFrameBorderMode(0);
   Double_t xAxis52[10] = {-0.2, 0, 0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3}; 
   
   TH1D *dummyhist_copy__52 = new TH1D("dummyhist_copy__52","",9, xAxis52);
   dummyhist_copy__52->SetMinimum(0);
   dummyhist_copy__52->SetMaximum(1.67478e-05);
   dummyhist_copy__52->SetDirectory(0);
   dummyhist_copy__52->SetStats(0);
   dummyhist_copy__52->SetLineStyle(0);
   dummyhist_copy__52->SetMarkerStyle(20);
   dummyhist_copy__52->GetXaxis()->SetTitle("m^{jet}/p_{T}^{jet}");
   dummyhist_copy__52->GetXaxis()->SetRange(2,8);
   dummyhist_copy__52->GetXaxis()->CenterTitle(true);
   dummyhist_copy__52->GetXaxis()->SetNdivisions(505);
   dummyhist_copy__52->GetXaxis()->SetLabelFont(43);
   dummyhist_copy__52->GetXaxis()->SetLabelOffset(0.01);
   dummyhist_copy__52->GetXaxis()->SetLabelSize(18);
   dummyhist_copy__52->GetXaxis()->SetTitleSize(20);
   dummyhist_copy__52->GetXaxis()->SetTitleOffset(2.8);
   dummyhist_copy__52->GetXaxis()->SetTitleFont(43);
   dummyhist_copy__52->GetYaxis()->SetTitle("#frac{1}{N_{evt}} #frac{dN^{jet}}{dp_{T}d(m/p_{T})}  (GeV^{-1})");
   dummyhist_copy__52->GetYaxis()->CenterTitle(true);
   dummyhist_copy__52->GetYaxis()->SetNdivisions(505);
   dummyhist_copy__52->GetYaxis()->SetLabelFont(43);
   dummyhist_copy__52->GetYaxis()->SetLabelOffset(0.01);
   dummyhist_copy__52->GetYaxis()->SetLabelSize(18);
   dummyhist_copy__52->GetYaxis()->SetTitleSize(15);
   dummyhist_copy__52->GetYaxis()->SetTitleOffset(4.5);
   dummyhist_copy__52->GetYaxis()->SetTitleFont(43);
   dummyhist_copy__52->GetZaxis()->SetLabelFont(42);
   dummyhist_copy__52->GetZaxis()->SetLabelSize(0.045);
   dummyhist_copy__52->GetZaxis()->SetTitleSize(0.035);
   dummyhist_copy__52->GetZaxis()->SetTitleFont(42);
   dummyhist_copy__52->Draw("");
   p_5_2->Modified();
   c1->cd();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
