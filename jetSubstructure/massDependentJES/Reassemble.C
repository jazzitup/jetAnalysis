void Reassemble()
{
  
  double ptBin[13]={63.096, 82., 100.000, 125.892,  158.488,  199.525,  251.186,  316.224,  398.101,  500.,  630.944, 794.308, 999.970};
  double massBin[13] = { -0.15,-0.06,-0.03,0,0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3,0.35};

  TH2D* h2_pT_mOverPT=new TH2D("h2_pT_mOverPT",12,ptBin,12,massbin);
  for(unsigned int icent=0; icent<=6; icent++)
  {
    ss.str("");
    if(icent==0) ss << "jes_pp_cent0.root";
    else ss << "jes_PbPb_cent" << icent << ".root";
    TFile* fin=TFile::Open(ss.str().c_str());
    for(int xbin=1; xbin<=h2_pT_mOverPT->GetNbinsX(); xbin++)
    {
      for(int ybin=1; ybin<=h2_pT_mOverPT->GetNbinsY(); ybin++)
      {
	ss.str("");
	ss << "jes_iy" << ybin << "_ipt" << xbin;
	TH1D* 
      }
    }
      

    

  }


}
