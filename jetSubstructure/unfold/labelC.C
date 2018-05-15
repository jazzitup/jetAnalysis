{
//=========Macro generated from canvas: labelC/
//=========  (Sun Mar 18 16:16:02 2018) by ROOT version5.34/34
   TCanvas *labelC = new TCanvas("labelC", "",497,54,228,327);
   gStyle->SetOptStat(0);
   labelC->Range(0,0,1,1);
   labelC->SetFillColor(0);
   labelC->SetBorderMode(0);
   labelC->SetBorderSize(0);
   labelC->SetTickx(1);
   labelC->SetTicky(1);
   labelC->SetLeftMargin(0.17);
   labelC->SetRightMargin(0.08);
   labelC->SetTopMargin(0.05);
   labelC->SetBottomMargin(0.15);
   labelC->SetFrameLineColor(0);
   labelC->SetFrameBorderMode(0);
   
   TLegend *leg = new TLegend(0.01769912,0.03311258,0.9823009,1,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.08);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("NULL","Unfolded","h");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("mcUnfSq_ix7_in0","4th iter.","lpf");
   entry->SetFillStyle(1001);
   entry->SetLineColor(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("mcUnfSq_ix7_in1","1st iter.","lpf");
   entry->SetFillStyle(1001);
   entry->SetLineColor(30);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(30);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("mcUnfSq_ix7_in2","2nd iter.","lpf");
   entry->SetFillStyle(1001);
   entry->SetLineColor(28);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(28);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("mcUnfSq_ix7_in3","6th iter.","lpf");
   entry->SetFillStyle(1001);
   entry->SetLineColor(6);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(6);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("mcUnfSq_ix7_in4","7th iter.","lpf");
   entry->SetFillStyle(1001);
   entry->SetLineColor(2);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("mcUnfSq_ix7_in5","8th iter.","lpf");
   entry->SetFillStyle(1001);
   entry->SetLineColor(4);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(4);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("mcUnfSq_ix7_in6","9th iter.","lpf");
   entry->SetFillStyle(1001);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#0000cc");
   entry->SetLineColor(ci);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#0000cc");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("mcUnfSq_ix7_in7","10th iter.","lpf");
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#000099");
   entry->SetLineColor(ci);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#000099");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("mcUnfSq_ix7_in8","11th iter.","lpf");
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#000066");
   entry->SetLineColor(ci);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#000066");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("mcUnfSq_ix7_in9","12th iter.","lpf");
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#000033");
   entry->SetLineColor(ci);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#000033");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("mcUnfSq_ix7_in10","13th iter.","lpf");
   entry->SetFillStyle(1001);
   entry->SetLineColor(ci);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("mcUnfSq_ix7_in11","14th iter.","lpf");
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#ffccff");
   entry->SetLineColor(ci);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#ffccff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("mcUnfSq_ix7_in12","15th iter.","lpf");
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#ff99ff");
   entry->SetLineColor(ci);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#ff99ff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   labelC->Modified();
   labelC->cd();
   labelC->SetSelected(labelC);
}
