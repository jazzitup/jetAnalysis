void unfolding_1D(char *infile1 = "out_2_10e7.root", char *infile2 = "out_25_10e7_2.root"){
    gSystem->Load("/home/sickles/comp/roounfold/trunk.r349/libRooUnfold.so");
    TFile *f1 = new TFile(infile1);
    TFile *f2 = new TFile(infile2);
    TH1D *htrue = f1->Get("htrue");
    TH1D *htrue_data = f2->Get("htrue");
    htrue_data->SetName("htrue_data");
    TH1D *hmeas = f2->Get("hmeas");
    TH1D *hmeasMC = f1->Get("hmeas");
    hmeasMC->SetName("hmeasMC");
    TH2D *hres = f1->Get("hres");
    TH1D *hratio_meas = (TH1D *)hmeas->Clone();
    hratio_meas->SetName("hratio_meas");
    hratio_meas->SetLineColor(1);
    hratio_meas->Divide(htrue);

    int itr = 4;

    RooUnfoldResponse *response = new RooUnfoldResponse(hmeasMC,htrue,hres);
    RooUnfoldBayes *unfold = new RooUnfoldBayes(response,hmeas,itr);

    TH1D *hunfolded = unfold->Hreco();

    TH1D *hratio = (TH1D *)hunfolded->Clone();
    hratio->Divide(htrue_data);
    hratio->SetMaximum(2);
    hratio->SetMinimum(0);
    hratio->Draw();
    hratio_meas->Draw("same");

    ostringstream name;
    name << "ratio_" << itr << ".pdf";
    gPad->Print(name.str().c_str());
}


