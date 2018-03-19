
#include <TH1.h>
#include <map>

const float MYALPHA=0.2;
const int NUMCENTBINS=15;
const int NUMYBINS=4;
int colors[NUMCENTBINS]={1,kRed-4,kAzure-3,kGreen+2,
			 kMagenta+2,kOrange+2,kCyan+3,
			 28,41,kGray,kGreen-6,
			 kOrange-1,kSpring+2,kPink+1,24};

int styles[NUMCENTBINS]={20,21,33,34,29,
			 24,25,23,27,30,28,
			 20,21,33,34};

float sizes[NUMCENTBINS]={1,1,1.6,1.2,1.6,1,
			  1,1,1.6,1,1,
			  1,1,1.6,1.2};

int fill_colors[4]={kRed-9,kAzure-9,kGreen-9,kMagenta-9};
//std::string atlas_tag="#bf{#it{ATLAS}} internal";
std::string atlas_tag="#bf{#it{ATLAS}}";
void EquipHistogram(TH1* h1, unsigned int index)
{
  int index_prime=index;
  h1->SetMarkerColor(colors[index_prime]);
  h1->SetLineColor(colors[index_prime]);
  h1->SetLineWidth(1);
  h1->SetMarkerStyle(styles[index_prime]);
  h1->SetMarkerSize(sizes[index_prime]);
}

void EquipGraph(TGraph* h1, unsigned int index)
{
  int index_prime=index;
  h1->SetMarkerColor(colors[index_prime]);
  h1->SetLineColor(colors[index_prime]);
  h1->SetMarkerStyle(styles[index_prime]);
  h1->SetMarkerSize(1e-4);
}

// void DrawHisto(TH1* h1, unsigned int index, std::string opt, bool as_graph=false)
// {
//   EquipHistogram(h1,index);
//   if(as_graph) HistoToGraph(h1)->Draw(opt.c_str());
//   else h1->Draw(opt.c_str());
// }

// TGraphErrors* HistoToGraph(TH1* h1)
// {
//   TGraphErrors* g=new TGraphErrors();
//   for(int i=1; i<=h1->GetNbinsX(); i++)
//   {
//     g->SetPoint(i-1,h1->GetXaxis()->GetBinCenter(i),h1->GetBinContent(i));
//     g->SetPointError(i-1,h1->GetXaxis()->GetBinWidth(i)*0.5,h1->GetBinError(i));
//   }
//   g->SetMarkerSize(h1->GetMarkerSize());
//   g->SetMarkerStyle(h1->GetMarkerStyle());
//   g->SetMarkerColor(h1->GetMarkerColor());
//   g->SetLineColor(h1->GetLineColor());
//   return g;
// }


// double GetTAA(int icent)
// {
//   double TAA_VALS[NUMCENTBINS]={23.4473,
// 				14.4261,
// 				8.73438,
// 				5.03516,
// 				2.70469,
// 				1.32969,
// 				0.592188,
// 				0.235156,
// 				0.0867188,
// 				0.0359375,
// 				29.0266,
// 				25.6199,
// 				20.5934,
// 				0.413672,
// 				0.0697917};
//   return TAA_VALS[icent-1];
// }

// std::string ParseCentralityCut(std::string htitle)
// {
//   std::stringstream ss;
//   if(htitle.find("cleaning")!=std::string::npos)
//   {
//     ss << "#LT #it{T}_{AA} #GT_{MB} #it{#sigma_{pp}}";
//     //ss << "#it{#sigma}_{NN}^{jet}/#it{#sigma}_{NN}^{inel}";
//     return ss.str();
//   }
//   size_t pos1=htitle.find("<");
//   size_t pos2=htitle.find("=");
//   size_t pos3=htitle.find("&&",pos2);


//   ss << htitle.substr(0,pos1-1) << " - " << htitle.substr(pos2+1,pos3-pos2-1) << " %";
//   std::string hname(ss.str());
//   size_t pos=hname.find(" ");
//   while(pos!=std::string::npos) 
//   {
//     hname.replace(pos,1,"");
//     pos=hname.find(" ");
//   }
//   return hname;
  

// }


// void DrawAxisLabels(float ymin, float size, bool doX=true)
// {
//   TLatex* lat=new TLatex();
//   lat->SetTextFont(42);
//   lat->SetTextSize(size);
//   if(doX) lat->SetTextAlign(23);
//   else lat->SetTextAlign(32);
//   double vals[6]={40,60,100,200,400,800};
//   for(unsigned int v=0; v<6; v++)
//   {
//     std::stringstream ss;
//     ss << vals[v];
//     if(doX)lat->DrawLatex(vals[v],ymin,ss.str().c_str());
//     else lat->DrawLatex(ymin,vals[v],ss.str().c_str());
//   }


// }

// std::string ParseEtaCut(std::string htitle, std::string var)
// {
//   std::stringstream ss;
//   std::string svar(var);
//   if(var.find("eta")!=std::string::npos) svar="#eta";
//   else svar="y";
			      
//   size_t pos1=htitle.find(var);
//   if(pos1==std::string::npos)
//   {
//     ss << "0  < |#it{" << svar <<  "}| < 2.1";
//     return ss.str();
//   };

//   size_t pos2=htitle.find(">",pos1);
//   size_t pos3=htitle.find("&&",pos2);
//   size_t pos4=htitle.find("=",pos3);

//   ss << htitle.substr(pos2+1,pos3-pos2-1) << " < |#it{" << svar << "}| < " << htitle.substr(pos4+1);
//   return ss.str();
// }

// void DrawXLabels(float ymin, float size, float min, float max)
// {
//   TLatex* lat=new TLatex();
//   lat->SetTextFont(42);
//   lat->SetTextSize(size);
//   lat->SetTextAlign(23);
//   double vals[6]={20,40,60,100,200,400};
//   for(unsigned int v=0; v<6; v++)
//   {
//     if(vals[v] < min) continue;
//     if(vals[v] > max) continue;
//     std::stringstream ss;
//     ss << vals[v];
//     lat->DrawLatex(vals[v],ymin,ss.str().c_str());
//   }


// }

// void GraphToBandCenter(TGraphAsymmErrors* g_in, TGraph* g_high, TGraph* g_low)
// {
//   int j=0;
//   for(int i=0; i<g_in->GetN(); i++)
//   {
//     double pt=g_in->GetX()[i];
//     double high=g_in->GetY()[i]+g_in->GetErrorYhigh(i);
//     double low=g_in->GetY()[i]-g_in->GetErrorYlow(i);
//     if(i==0)
//     {
//       g_high->SetPoint(j,pt-g_in->GetErrorXlow(i),high);
//       g_low->SetPoint(j,pt-g_in->GetErrorXlow(i),low);
//       j++;
//     }
//     g_high->SetPoint(j,pt,high);
//     g_low->SetPoint(j,pt,low);
//     j++;
//     if(i==g_in->GetN()-1)
//     {
//       g_high->SetPoint(j,pt+g_in->GetErrorXhigh(i),high);
//       g_low->SetPoint(j,pt+g_in->GetErrorXhigh(i),low);
//       j++;
//     }
//   }
// }
// void GraphToBand(TGraphAsymmErrors* g_in, TGraph* g_high, TGraph* g_low)
// {
//   int j=0;
//   for(int i=0; i<g_in->GetN(); i++)
//   {
//     double pt=g_in->GetX()[i];
//     double high=g_in->GetY()[i]+g_in->GetErrorYhigh(i);
//     double low=g_in->GetY()[i]-g_in->GetErrorYlow(i);
//     g_high->SetPoint(j,pt-g_in->GetErrorXlow(i),high);
//     g_low->SetPoint(j,pt-g_in->GetErrorXlow(i),low);
//     j++;
//     g_high->SetPoint(j,pt+g_in->GetErrorXhigh(i),high);
//     g_low->SetPoint(j,pt+g_in->GetErrorXhigh(i),low);
//     j++;
//   }
// }
// void GraphToBox(TGraphAsymmErrors* g, int border, int fill, int style, double dx=-1, float xmin=40, float xmax=300, float ymin=0, float ymax=1.5)
// {
//   for(unsigned int ipoint=0; ipoint<g->GetN(); ipoint++)
//   {
//     double y=g->GetY()[ipoint];
//     double x=g->GetX()[ipoint];
//     if(dx <0) dx=g->GetErrorX(ipoint);
//     double dy_low=g->GetErrorYlow(ipoint);
//     double dy_high=g->GetErrorYhigh(ipoint);
//     if(x < xmin || x > xmax) continue;
//     if(y < ymin || y > ymax) continue;
//     TBox* b=new TBox(x-dx,y-dy_low,x+dx,y+dy_high);
//     b->SetLineColor(border);
//     b->SetFillColor(fill);
//     b->SetFillStyle(style);
//     //b->Draw();
//     b->Draw("l");
//   }

// }

// void GraphToBoxLog(TGraphAsymmErrors* g, int border, int fill, int style, double dx=1.05, float xmin=40, float xmax=300, float ymin=0, float ymax=1.5)
// {
//   for(unsigned int ipoint=0; ipoint<g->GetN(); ipoint++)
//   {
//     double y=g->GetY()[ipoint];
//     double x=g->GetX()[ipoint];
//     if(dx <0) dx=g->GetErrorX(ipoint);
//     double dy_low=g->GetErrorYlow(ipoint);
//     double dy_high=g->GetErrorYhigh(ipoint);
//     if(x < xmin || x > xmax) continue;
//     if(y < ymin || y > ymax) continue;
//     TBox* b=new TBox(x/dx,y-dy_low,x*dx,y+dy_high);
//     b->SetLineColor(border);
//     //b->SetFillColor(fill);
//     //b->SetFillStyle(style);


//     //b->Draw();
//     b->Draw("l");
//   }

// }

// TGraphAsymmErrors* GetSelectedSystematics(TFile* fin, std::string prefix, const std::vector<std::string>& sys_list)
// {

//   if(sys_list.size()==0) return new TGraphAsymmErrors();
//   std::stringstream ss;
//   TGraphAsymmErrors* g=0;
//   for(int i=0; i<sys_list.size(); i++)
//   {
//     if(sys_list.at(i).find("eff")!=std::string::npos) continue;
//     //if(sys_list.at(i).find("JE")==std::string::npos) continue;
//     ss.str("");
//     ss << prefix << "_" << sys_list[i];
//     TGraphAsymmErrors* g_sys=(TGraphAsymmErrors*)fin->Get(ss.str().c_str());
//     if(i==0) g=g_sys;
//     else SumGraphInQuadrature(g,g_sys);
//   }
//   return g;
// }

// void SumGraphInQuadrature(TGraphAsymmErrors* g, TGraphAsymmErrors* g_sys)
// {
//   for(int i=0; i<g->GetN(); i++)
//   {
//     double dy_low=g->GetErrorYlow(i);
//     double dy_low_sys=g_sys->GetErrorYlow(i);
//     dy_low=std::sqrt(dy_low*dy_low+dy_low_sys*dy_low_sys);

//     double dy_high=g->GetErrorYhigh(i);
//     double dy_high_sys=g_sys->GetErrorYhigh(i);
//     dy_high=std::sqrt(dy_high*dy_high+dy_high_sys*dy_high_sys);
//     g->SetPointError(i,g->GetErrorXlow(i),g->GetErrorXhigh(i),dy_low,dy_high);
//   }

// }

// TGraphAsymmErrors* Prune(TGraphAsymmErrors* g, double ptmin, double ptmax, bool keepXerr=true)
// {

//   TGraphAsymmErrors* g_copy=new TGraphAsymmErrors();
//   std::map<float,int> points;
//   for(int i=0; i<g->GetN(); i++)
//   {
//     double pt=g->GetX()[i];
//     if(pt > ptmin && pt < ptmax && g->GetY()[i] > 1e-3) points.insert(std::pair<float,int>(pt,i));
//   }
//   int ip=0;
//   for(std::map<float,int>::iterator mitr=points.begin(); mitr!=points.end(); mitr++)
//   {
//     int i=mitr->second;
//     double pt=g->GetX()[i];
//     g_copy->SetPoint(ip,pt,g->GetY()[i]);
//     if(keepXerr) g_copy->SetPointError(ip,g->GetErrorXlow(i),g->GetErrorXhigh(i),g->GetErrorYlow(i),g->GetErrorYhigh(i));
//     else g_copy->SetPointError(ip,0,0,g->GetErrorYlow(i),g->GetErrorYhigh(i));
//     ip++;
//   }
//   g_copy->SetName(g->GetName());
//   g_copy->SetTitle(g->GetTitle());
//   return g_copy;
// }


// void DrawCommonErrorBox(double x, double y, double dy, double dx, int border, int fill, int style,bool log=true)
// {

//   TBox* b;
//   if(log) b=new TBox(x/dx,y-dy,x*dx,y+dy);
//   else b=new TBox(x-dx,y-dy,x+dx,y+dy);
//   b->SetLineColor(border);
//   b->SetFillColor(fill);
//   b->SetFillStyle(style);
//   b->Draw();
// }

// void DrawTAAErrorBox(int icent, double x, double dx, int border, int fill, int style, bool log=true)
// {
//  double TAA_VALS[NUMCENTBINS]={23.4473,
// 				14.4261,
// 				8.73438,
// 				5.03516,
// 				2.70469,
// 				1.32969,
// 				0.592188,
// 				0.235156,
// 				0.0867188,
// 				0.0359375,
// 				29.0266,
// 				25.6199,
// 				20.5934,
// 				0.413672,
// 				0.0697917};

//   double TAAERROR[NUMCENTBINS]={0.37034,
// 				0.29621,
// 				0.26268,
// 				0.22402,
// 				0.17321,
// 				0.11702,
// 				0.069545,
// 				0.035957,
// 				0.015591,
// 				0.0090371,
// 				0.45908,
// 				0.39873,
// 				0.3414,
// 				0.052736,
// 				0.013406};

//   DrawCommonErrorBox(x,1,TAAERROR[icent-1]/TAA_VALS[icent-1],dx,border,fill,style,log);
// }

// void StaggerPoints(TGraphAsymmErrors* g, double dx, bool log=true)
// {

//   for(int i=0; i<g->GetN(); i++)
//   {
//     double x=g->GetX()[i];
//     if(log) g->SetPoint(i,x*dx,g->GetY()[i]);
//     else g->SetPoint(i,x+dx,g->GetY()[i]);
//   }
// }

// void DrawEnds(TGraphAsymmErrors* g)
// {
//   TLine* l1=new TLine(g->GetX()[0]-g->GetErrorXlow(0),g->GetY()[0]-g->GetErrorYlow(0),g->GetX()[0]-g->GetErrorXlow(0),g->GetY()[0]+g->GetErrorYhigh(0));
//   l1->SetLineWidth(g->GetLineWidth());
//   l1->SetLineColor(g->GetLineColor());
//   l1->Draw();

//   int nn=g->GetN()-1;
//   TLine* l2=new TLine(g->GetX()[nn]+g->GetErrorXhigh(nn),g->GetY()[nn]-g->GetErrorYlow(nn),g->GetX()[nn]+g->GetErrorXhigh(nn),g->GetY()[nn]+g->GetErrorYhigh(nn));
//   l2->SetLineWidth(g->GetLineWidth());
//   l2->SetLineColor(g->GetLineColor());
//   l2->Draw();

// }

// std::string GetCentString(unsigned int icent)
// {
//   int cbins[7]={0,10,20,30,40,60,80};
//   std::stringstream ss;
//   ss << cbins[icent] << " - " << cbins[icent+1] << " %";
//   return ss.str();
// }
// std::string GetPtString(unsigned int ipt)
// {
//   if(ipt==3) return "#it{p}_{T 1} > 200 GeV";
//   int ptbins[4]={100,126,158,200};
//   std::stringstream ss;
//   ss << ptbins[ipt] << " < #it{p}_{T 1} <  " << ptbins[ipt+1] << " GeV";
//   return ss.str();
// }

