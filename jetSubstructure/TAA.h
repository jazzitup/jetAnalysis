#include "commonUtility.h" 
double getTaa(int icent) {  // mb-1
  if ( icent==0)       return 23.35;
  else if ( icent==1)  return 14.33;
  else if ( icent==2)  return 8.63;
  else if ( icent==3)  return 4.94;
  else if ( icent==4)  return 2.63;
  else if ( icent==5)  return 1.27;
  else if ( icent==6)  return 0.39;
  else return 0; 
}

double getTaaRelErr(int icent) { 
  if ( icent==0)  return 0.2 / getTaa(icent); // mb-1
  else if ( icent==1)  return 0.17/ getTaa(icent);
  else if ( icent==2)  return 0.17/ getTaa(icent);
  else if ( icent==3)  return 0.15/ getTaa(icent);
  else if ( icent==4)  return 0.11/ getTaa(icent);
  else if ( icent==5)  return 0.07/ getTaa(icent);
  else if ( icent==6)  return 0.03/ getTaa(icent);
  else return 0;
}

double getLumiRelErr(int icent) { 
  float ppUnc = 0.054;
  float pbpbUnc = getTaaRelErr(icent);
  return sqrt ( ppUnc*ppUnc + pbpbUnc*pbpbUnc );
}

double getNEvent(int icent, double lumi = 0.49) { // 0.49 nb
  double scaleFac = lumi/0.49;
  if ( icent < 6)
    return 3.74e8 * scaleFac; 
  else if ( icent == 6)  
    return 3.74e8 * 2 * scaleFac; 
  else
    return 0;
}

void CsScalePP( TH1D* hpp) {
  hpp->Scale( 1. / 25300000. );  // 25300 nb-1 =  25.3 pb-1
}

void CsScalePbPb( TH1D* hpbpb, int icent =-1, double lumi = 0.49) {
  if ( icent == -1 ) {
    cout << "centrality is not specified" << endl;
    return;
  }
  hpbpb->Scale( 1000. / ( getNEvent(icent, lumi) * getTaa(icent) )  ); // nb-1
}

