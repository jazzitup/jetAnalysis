#include "FitResponseSlices.h"
#include <algorithm>
#include <sstream>
#include <cmath>
#include <TH3D.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TLatex.h>
#include <TMath.h>
#include <TLegend.h>

namespace
{
  double MyGamma(double* x, double* par) 
  {
    double y=(x[0]-par[2])/par[0];
    if(y<0.) return 0;
    double arg=-y+(par[1]-1.)*std::log(y);
    double stirling=par[1]*(std::log(par[1])-1.)+0.5*std::log(2.*TMath::Pi()/par[1]);
    arg-=stirling;
    return std::exp(arg)/par[0];
    // }
    // return std::exp(arg)/(par[0]*TMath::Gamma(par[1]));
  }
}


FitResponseSlices::FitResponseSlices() : m_fit_max(2.),
					 m_Nsigma_fit(1.5),
					 m_plot_path("plots"),
					 m_dump_fits(true),
					 m_min_count(1e-12),
					 m_doGammaFits(true),
					 m_verbose(true)
{
}

void FitResponseSlices::fitAllSlices() const
{
  TFile* fout=new TFile("JMS.root","recreate");
  std::stringstream ss;
  for(unsigned int icent=0; icent<=7; icent++)
  {
    ss.str("");
    if(icent==0) ss << "jes_pp_cent0.root";
    else ss << "jes_PbPb_cent" << icent-1 << ".root";
    TFile* fin=TFile::Open(ss.str().c_str());
    fitSingleBin(fin,fout,icent);
    fin->Close();
  }
  fout->Write();
  fout->Close();
}

void FitResponseSlices::fitSingleBin(TFile* fin, TFile* fout, int jc) const
{
  float rmin=0;
  std::stringstream ss;
  std::string xvar("#it{p}_{T}");
  ss.str("");
  ss << xvar << "^{ reco} / " << xvar << "^{ truth}";
  std::string yvar(ss.str().c_str());
  ss.str("");
  ss << "#LT " << yvar << " #GT";
  std::string title_m(ss.str());
  ss.str("");
  ss << "#it{#sigma}[ " << yvar << " ]";
  std::string title_s(ss.str());
  ss.str("");
  ss << "Mode [ " << yvar << " ]";
  std::string title_mode(ss.str());
  ss.str("");
  ss << "#it{S} [ " << yvar << " ]";
  std::string title_S(ss.str());

  
  double ptBin[13]={63.096, 82., 100.000, 125.892,  158.488,  199.525,  251.186,  316.224,  398.101,  500.,  630.944, 794.308, 999.970};
  //double massBin[13] = { -0.15,-0.06,-0.03,0,0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3,0.35};
  double massBin[10] = {0,0.03, 0.06, 0.09, 0.12, 0.15, 0.18, 0.24, 0.3,0.35};

  std::string tt;
  fout->cd();
  ss.str("");
  ss << "h2_JES_c" << jc;
  TH2D* h2_mu=new TH2D(ss.str().c_str(),";#it{p}_{T} [GeV];(#it{m}/#it{p}_{T})^{2}",12,ptBin,9,massBin);
  tt="Gaussian " + title_m;
  h2_mu->GetZaxis()->SetTitle(tt.c_str());
  
  ss.str("");
  ss << "h2_JER_c" << jc;
  TH2D* h2_sigma=(TH2D*)h2_mu->Clone(ss.str().c_str());
  tt="Gaussian " + title_s;
  h2_sigma->GetZaxis()->SetTitle(tt.c_str());

  ss.str("");
  ss << "h2_mean_c" << jc;
  TH2D* h2_mean=(TH2D*)h2_mu->Clone(ss.str().c_str());
  tt="Statistical " + title_m;
  h2_mean->GetZaxis()->SetTitle(tt.c_str());
  
  ss.str("");
  ss << "h2_stddev_c" << jc;
  TH2D* h2_stddev=(TH2D*)h2_sigma->Clone(ss.str().c_str());
  tt="Statistical " + title_s;
  h2_stddev->GetZaxis()->SetTitle(tt.c_str());
  
  ss.str("");
  ss << "h2_mode_c" << jc;
  TH2D* h2_mode=(TH2D*)h2_sigma->Clone(ss.str().c_str());
  tt="Statistical " + title_mode;
  h2_mode->GetZaxis()->SetTitle(tt.c_str());

  ss.str("");
  ss << "h2_skewness_c" << jc;
  TH2D* h2_skewness=(TH2D*)h2_sigma->Clone(ss.str().c_str());
  h2_skewness->GetZaxis()->SetTitle(title_S.c_str());

  ss.str("");
  ss << "h2_gammaMean_c" << jc;
  TH2D* h2_gammaMean=(TH2D*)h2_mu->Clone(ss.str().c_str());
  tt="Gamma "+ title_m;
  h2_gammaMean->GetZaxis()->SetTitle(tt.c_str());
  
  ss.str("");
  ss << "h2_gammaStddev_c" << jc;
  TH2D* h2_gammaStddev=(TH2D*)h2_sigma->Clone(ss.str().c_str());
  tt="Gamma " + title_s;
  h2_gammaStddev->GetZaxis()->SetTitle(tt.c_str());
  
  ss.str("");
  ss << "h2_gammaMode_c" << jc;
  TH2D* h2_gammaMode=(TH2D*)h2_mode->Clone(ss.str().c_str());
  tt="Gamma " +title_mode;
  h2_gammaMode->GetZaxis()->SetTitle(tt.c_str());
  
  ss.str("");
  ss << "h2_gammaTheta_c" << jc;
  TH2D* h2_gammaTheta=(TH2D*)h2_mu->Clone(ss.str().c_str());
  h2_gammaTheta->GetZaxis()->SetTitle("#it{#theta}_{#it{#Gamma}}");

  ss.str("");
  ss << "h2_gammaK_c" << jc;
  TH2D* h2_gammaK=(TH2D*)h2_mu->Clone(ss.str().c_str());
  h2_gammaK->GetZaxis()->SetTitle("#it{k}_{#it{#Gamma}}");




  TCanvas can("can","",600,400);
  //can.SetLogy();
  can.SetMargin(0.05,0.05,0.15,0.1);
  TLatex lat;
  lat.SetTextFont(42);
  lat.SetTextSize(0.035);
  lat.SetNDC(true);
  lat.SetTextAlign(33);

  
  for(int xbin=1; xbin<=h2_mu->GetNbinsX(); xbin++)
  {
    for(int ybin=1; ybin<=h2_mu->GetNbinsY(); ybin++)
    {
      ss.str("");
      ss << "jes_iy" << ybin+3 << "_ipt" << xbin;
      TH1D* h1_slice=(TH1D*)fin->Get(ss.str().c_str());
      h1_slice->SetDirectory(0);
      double dd=h1_slice->Integral("width");
      if(dd < m_min_count) continue;
      h1_slice->Scale(1./dd);
      TF1 f1("f1","gaus",rmin,m_fit_max);
      f1.SetParameters(1,h1_slice->GetMean(),h1_slice->GetRMS());
      float  mu=f1.GetParameter(1);
      float sigma=f1.GetParameter(2);
      if(sigma < 5e-4) sigma=0.3;
      float fmin=0;
      float fmax=m_fit_max;
      h1_slice->Fit(&f1,"NOQR","",rmin,m_fit_max);
      if(m_Nsigma_fit > 0)
      {
	fmin=std::max(rmin,mu-m_Nsigma_fit*sigma);
	fmax=std::min(mu+m_Nsigma_fit*sigma,m_fit_max);
      }
      TF1 f2("f2","gaus",fmin,fmax);
      f2.SetParameters(f1.GetParameter(0),mu,sigma);
      if(m_verbose)
      {
	std::cout << std::setw(30) << h1_slice->GetName()
		  << std::setw(10) << xbin 
		  << std::setw(10) << m_fit_max
		  << std::setw(15) << fmin << std::setw(15) << fmax 
		  << std::setw(15) << mu << std::setw(15) << sigma << std::endl;
      }
      h1_slice->Fit(&f2,"NOQR","",fmin,fmax);

      mu=f2.GetParameter(1);
      sigma=f2.GetParameter(2);
      double mu_e=f2.GetParError(1);
      double sigma_e=f2.GetParError(2);


      h2_mu->SetBinContent(xbin,ybin,mu);
      h2_mu->SetBinError(xbin,mu_e);
      h2_sigma->SetBinContent(xbin,ybin,sigma);
      h2_sigma->SetBinError(xbin,sigma_e);
      
      h2_mean->SetBinContent(xbin,ybin,h1_slice->GetMean());
      h2_mean->SetBinError(xbin,h1_slice->GetMeanError());
      
      h2_stddev->SetBinContent(xbin,ybin,h1_slice->GetRMS());
      h2_stddev->SetBinError(xbin,h1_slice->GetRMSError());
      
      h2_skewness->SetBinContent(xbin,ybin,h1_slice->GetSkewness());
      h2_mode->SetBinContent(xbin,ybin,h1_slice->GetXaxis()->GetBinCenter(h1_slice->GetMaximumBin()));
      h2_mode->SetBinError(xbin,ybin,h1_slice->GetXaxis()->GetBinWidth(h1_slice->GetMaximumBin()));
      
      TF1 f3("f3",MyGamma,rmin,m_fit_max,3);
      double k0=h2_mean->GetBinContent(xbin,ybin)/h2_stddev->GetBinContent(xbin,ybin);
      k0=k0*k0;
      double theta0=h2_mean->GetBinContent(xbin,ybin)/k0;
      f3.SetParameters(theta0,k0,0);
      //if(h2->GetXaxis()->GetBinLowEdge(xbin) < 400.) f3.FixParameter(3,-1);
      //else f3.SetParameters(1,1,0,1);

      if(m_doGammaFits) h1_slice->Fit("f3","NORQ","",fmin,fmax);

      double p0=f3.GetParameter(0);
      double e0=f3.GetParError(0);
      double p1=f3.GetParameter(1);
      double e1=f3.GetParError(1);
      double p2=f3.GetParameter(2);
      
      
      if((TMath::IsNaN(p0) || TMath::IsNaN(p1) || TMath::IsNaN(e0) || TMath::IsNaN(e1) || p1 < 0 || e1/p1 > 1. || e0/p0 > 1) )
      {
	p0=0;
	e0=0;
	p1=0;
	e1=0;
	p2=0;
	
      }
      
      h2_gammaTheta->SetBinContent(xbin,ybin,p0);
      h2_gammaTheta->SetBinError(xbin,e0);
      h2_gammaK->SetBinContent(xbin,ybin,p1);
      h2_gammaK->SetBinError(xbin,e1);
      h2_gammaMean->SetBinContent(xbin,ybin,p0*p1+p2);
      h2_gammaMean->SetBinError(xbin,0);
      h2_gammaStddev->SetBinContent(xbin,ybin,p0*std::sqrt(p1));
      h2_gammaStddev->SetBinError(xbin,0);
      h2_gammaMode->SetBinContent(xbin,ybin,p0*(p1-1)+p2);
      h2_gammaMode->SetBinError(xbin,0);
      if(m_dump_fits) 
      {
	h1_slice->SetMarkerStyle(24);
	if(!gPad->GetLogy()) 
	{
	  double mmmax=h1_slice->GetBinContent(h1_slice->GetMaximumBin());
	  h1_slice->GetYaxis()->SetRangeUser(0,mmmax*1.25);
	}
	h1_slice->GetYaxis()->SetLabelSize(0.02);
	h1_slice->Draw();
	f2.SetLineColor(kRed);
	f2.Draw("Same");
	f3.SetLineColor(kAzure);
	f3.SetLineStyle(3);
	f3.Draw("same");
	ss.str("");
	ss << (int) h2_mu->GetXaxis()->GetBinLowEdge(xbin) << " < #it{p}_{T} < "
	   << (int) h2_mu->GetXaxis()->GetBinUpEdge(xbin) << " GeV   ";
	lat.DrawLatex(0.99,0.99,ss.str().c_str());
	ss.str("");
	ss << "#it{#mu} = " << std::setprecision(5) << mu
	   << " #pm " << std::setprecision(3) << mu_e
	   << "                "
	   << "#it{#sigma} = " << std::setprecision(3) << sigma
	   << " #pm " << std::setprecision(3) << sigma_e;
	lat.DrawLatex(0.99,0.95,ss.str().c_str());
	ss.str("");
	ss << m_plot_path << "/" << h1_slice->GetName() << "_c" << jc << ".pdf";
	can.Print(ss.str().c_str());
      
      }
      //delete h1_slice;
    }
  }
  std::vector<TH2*> h2v={h2_mu,
			 h2_mean,
			 h2_gammaMean,
			 h2_mode,
			 h2_gammaMode,
			 h2_sigma,
			 h2_stddev,
			 h2_gammaStddev,
			 h2_skewness,
			 h2_gammaTheta,
			 h2_gammaK};

  

  TCanvas* c2=new TCanvas("c","c",800,600);
  c2->SetMargin(0.15,0.25,0.2,0.05);
  for(unsigned int i=0; i<h2v.size(); i++)
  {
    TH2* h2=h2v[i];
    float ymin=0.5;
    float ymax=1.5;
    if(i==5 || i==6 || i==7)
    {
      ymin=0;
      ymax=0.35;
    }
    if(i>7)
    {
      ymin=-1;
      ymax=1;
    }
    std::string title=h2->GetZaxis()->GetTitle();
    //vs pT
    //gPad->SetLogx();
    TLegend* leg=new TLegend(0.77,0.2,0.98,0.98);
    leg->SetFillColor(0);
    leg->SetTextFont(42);
    leg->SetTextSize(0.02);
    std::string dopt("pe same");
    if(i>7) dopt="hist L same";
    for(int ybin=1; ybin < h2->GetNbinsY(); ybin++)
    {
      ss.str("");
      ss << h2->GetTitle() << "_vsPt_y" << ybin;
      TH1D* h1=(TH1D*)h2->ProjectionX(ss.str().c_str(),ybin,ybin);
      EquipHistogram(h1,ybin-1);
      h1->GetYaxis()->SetRangeUser(ymin,ymax);
      h1->GetXaxis()->SetMoreLogLabels();
      h1->GetYaxis()->SetTitle(h2->GetZaxis()->GetTitle());
      if(ybin==1) h1->Draw("axis");
      h1->Draw(dopt.c_str());
      ss.str("");
      ss << h2->GetYaxis()->GetBinLowEdge(ybin) << "< (#it{m} / #it{p}_{T})^{2} < "
	 << h2->GetYaxis()->GetBinUpEdge(ybin);
      leg->AddEntry(h1,ss.str().c_str(),"PL");
    }
    leg->Draw("same");
    ss.str("");
    ss << "perf/perf_";
    if(i<10) ss <<"0";
    ss << i << "_vsPt_c" << jc << ".pdf";
    c2->Print(ss.str().c_str());
    //
    //vs m/pT
    gPad->SetLogx(false);
    leg->Clear();
    for(int xbin=1; xbin < h2->GetNbinsX(); xbin++)
    {
      ss.str("");
      ss << h2->GetTitle() << "_vsMoverPt_x" << xbin;
      TH1D* h1=(TH1D*)h2->ProjectionY(ss.str().c_str(),xbin,xbin);
      EquipHistogram(h1,xbin-1);
      h1->GetYaxis()->SetRangeUser(ymin,ymax);
      h1->GetYaxis()->SetTitle(h2->GetZaxis()->GetTitle());
      if(xbin==1) h1->Draw("axis");
      h1->Draw(dopt.c_str());
      ss.str("");
      ss <<static_cast<int>(h2->GetXaxis()->GetBinLowEdge(xbin)) << "< #it{p}_{T} < "
	<< static_cast<int>(h2->GetXaxis()->GetBinUpEdge(xbin)) << " GeV";
      leg->AddEntry(h1,ss.str().c_str(),"PL");

    }
    leg->Draw("same");
    ss.str("");
    ss << "perf/perf_";
    if(i<10) ss <<"0";
    ss << i << "_vsMoverPT_c" << jc << ".pdf";
    c2->Print(ss.str().c_str());
  }

}


