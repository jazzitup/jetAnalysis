#include "commonUtility.h" 
double getTaa(int icent) {  // mb-1
  if ( icent==0)  return 23.35;
  if ( icent==1)  return 14.33;
  if ( icent==2)  return 8.63;
  if ( icent==3)  return 4.94;
  if ( icent==4)  return 2.63;
  if ( icent==5)  return 1.27;
  if ( icent==6)  return 0.39;
}

double getTaaRelErr(int icent) { 
  if ( icent==0)  return 0.2 / getTaa(icent); // mb-1
  if ( icent==1)  return 0.17/ getTaa(icent);
  if ( icent==2)  return 0.17/ getTaa(icent);
  if ( icent==3)  return 0.15/ getTaa(icent);
  if ( icent==4)  return 0.11/ getTaa(icent);
  if ( icent==5)  return 0.07/ getTaa(icent);
  if ( icent==6)  return 0.03/ getTaa(icent);
}

double getNEvent(int icent, double lumi = 0.49) { // 0.49 nb
  double scaleFac = lumi/0.49;
  if ( icent == 6)  return 1.87e8 * 2 * scaleFac; 
  else if ( icent == 6)  return 1.87e8 * scaleFac; 
}

void CsScalePP( TH1D* hpp) {
  hpp->Scale( 1. / 25000000. );  // 25000000 micro barn-1,  25 pb-1
}

void CsScalePbPb( TH1D* hpbpb, int icent =-1, double lumi = 0.49) {
  if ( icent == -1 ) {
    cout << "centrality is not specified" << endl;
    return;
  }
  hpbpb->Scale( 1. / (getNEvent(icent, lumi) * getTaa (icent) )  ) ;
}

