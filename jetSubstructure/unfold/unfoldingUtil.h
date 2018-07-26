#ifndef UNFOLDINGUTIL_H
#define UNFOLDINGUTIL_H

bool selectedCent(int icent=0) {
  if ( icent ==0 )  return true;
  //  if ( icent ==1 )  return true;
  //  if ( icent ==2 )  return true;
  //  if ( icent ==3 )  return true;
  if ( icent ==4 )  return true;
  //  if ( icent ==5 )  return true;
  //  if ( icent ==6 )  return true;
  else return false; 
  return 0;
}



int findMbin(double mpt=0) {
  if ( mpt < 0.06 ) return 1;
  else if ( mpt < 0.1 ) return 2;
  else if ( mpt < 0.15 ) return 3;
  else 
    return 4;
}



TH2D* getRewTable(int kSample, int icent)  { 
  TFile* fReweight = new TFile("reweightFactorsEta/reweightingFactor_weightCut10_flucCut0.3_factorized_v60.root"); // Default, set in Apr 7
  // int nSys = 210;  TFile* fReweight = new TFile(Form("reweightFactors/reweightingFactor_weightCut10_opt772_flucCut0.3_factorized_v50_nSys%d.root",nSys));   cout << " Using nSys = " << nSys << "table!! " << endl << endl << endl;

  //  TFile* fReweight = new TFile("reweightFactors/reweightingFactor_weightCut10_opt772_flucCut0.3_factorized.root"); // Mar 28
  //  TFile* fReweight = new TFile("reweightFactors/reweightingFactor_weightCut10_opt771_flucCut0.3_fcalWeighted.root");
  TH2D* hTemp = (TH2D*)fReweight->Get(Form("factorizedRatio2_kSample%d_icent%d",kSample,icent));  // 00 default
  //  TH2D* hTemp = (TH2D*)fReweight->Get(Form("factorizedRatioVarP_kSample%d_icent%d",kSample,icent));  // plus50%
  //  TH2D* hTemp = (TH2D*)fReweight->Get(Form("factorizedRatioVarM_kSample%d_icent%d",kSample,icent));  // minus50%
  //  TH2D* hTemp = (TH2D*)fReweight->Get(Form("factorizedRatio_kSample%d_icent%d",kSample,icent)); // 01
  return hTemp;
}

TH2D* getRewTableEta(int kSample, int icent, int etaBin)  { 
  TFile* fReweight = new TFile(Form("reweightFactorsEta/reweightingFactor_etaBin%d_weightCut10_flucCut0.3_factorized_v60.root",etaBin)); // Default, set in Apr 7
  TH2D* hTemp = (TH2D*)fReweight->Get(Form("factorizedRatio2_kSample%d_icent%d",kSample,icent));  // 00 default
  return hTemp;
}
/*
  TString jz2PbPbString = "jetSubstructure_MC_HION9_jz2_v4.7_v4_Jan23_ptCut90Eta2.1.root";
  TString jz3PbPbString = "jetSubstructure_MC_HION9_jz3_v4.7_v4_Jan23_ptCut90Eta2.1.root";
  TString jz4PbPbString = "jetSubstructure_MC_HION9_jz4_v4.7_v4_Jan23_ptCut90Eta2.1.root";
  TString   jz2PPString = "jetSubstructure_MC_HION9_jz2_v4.7_r4_pp_Jan23_ptCut90Eta2.1.root";
  TString   jz3PPString = "jetSubstructure_MC_HION9_jz3_v4.7_r4_pp_Jan23_ptCut90Eta2.1.root";
  TString   jz4PPString = "jetSubstructure_MC_HION9_jz4_v4.7_r4_pp_Jan23_ptCut90Eta2.1.root";
*/
// systematics
TString jz2PbPbStringSys = "jetSubstructure_MC_HION9_jz2sys_v50.root";
TString jz3PbPbStringSys = "jetSubstructure_MC_HION9_jz3sys_v50.root";
TString jz4PbPbStringSys = "jetSubstructure_MC_HION9_jz4sys_v50.root";

TString jz2PPStringSys = "jetSubstructure_ppMC_HION9_jz2sys_v50_april14.root";     // _april14 is added only for pp as ptSysHI is fixed
TString jz3PPStringSys = "jetSubstructure_ppMC_HION9_jz3sys_v50_april14.root";     // _april14 is added only for pp as ptSysHI is fixed
TString jz4PPStringSys = "jetSubstructure_ppMC_HION9_jz4sys_v50_april14.root";     // _april14 is added only for pp as ptSysHI is fixed

TString jz2PbPbString = "jetSubstructure_pbpbMC_HION9_jz2_v51_april124.root";
TString jz3PbPbString = "jetSubstructure_pbpbMC_HION9_jz3_v51_april124.root";
TString jz4PbPbString = "jetSubstructure_pbpbMC_HION9_jz4_v51_april124.root";

TString jz2PPString = "jetSubstructure_ppMC_HION9_jz2_v52_april124.root";
TString jz3PPString = "jetSubstructure_ppMC_HION9_jz3_v52_april124.root";
TString jz4PPString = "jetSubstructure_ppMC_HION9_jz4_v52_april124.root";

TString ppDataString = "jetSubstructure_data_HION9_v50_r4_pp.root";
TString pbpbDataString = "jetSubstructure_data_HION9_v50_r4_pbpb.root";

TString getPtSysName( int nSys) {
  if (nSys < 0) 
    return "";
  else if ( (nSys >=0) && (nSys <= 21) )    // 0 -21 : pp intrinsic
    return Form("ptSysPP%d",nSys);
  else if ( (nSys >=100) && (nSys <= 106) )    // 100 -106 : HI intrinsic
    return Form("ptSysHI%d",nSys-100);
  else 
    return "";
}

int getRefIter( int kSample=0, int icent=0) {

  return 6;

  if ( kSample == 0 ) return 6;
  if ( kSample == 1 ) {
    if ( icent == 0 ) return 6;
    if ( icent == 1 ) return 4;
    if ( icent == 2 ) return 4;
    if ( icent == 3 ) return 4;
    if ( icent == 4 ) return 3;
    if ( icent == 5 ) return 3;
    if ( icent == 6 ) return 3;
  }
  
  return -1;
}



void getXbin(int &nBins, double* xBin, int optX) {
  if ( optX == 1 ) {

    //    nBins = 13;  // default
    //    double ptBin[14]={20,40,63.096, 82., 100.000, 125.892,  158.488,  199.525,  251.186,  316.224,  398.101,  500.,  630.944, 999.970};
    nBins = 12;  // default
    double ptBin[13]={20,40,63.096, 82., 100.000, 125.892,  158.488,  199.525,  251.186,  316.224,  398.101,  500.,  630.944};
    for ( int i=0 ; i<= nBins ; i++) {
      xBin[i] = ptBin[i] ;
    }
  }
  else if ( optX == 2) {
    nBins = 8;  // default
    double ptBin[9]={100.000, 125.892,  158.488,  199.525,  251.186,  316.224,  398.101,  500.,  1000};
    for ( int i=0 ; i<= nBins ; i++) {
      xBin[i] = ptBin[i] ;
    }
  }

  else if ( optX == 3) {
    nBins = 8;  // default
    double ptBin[9]={100.000, 125.892,  158.488,  199.525,  251.186,  316.224,  398.101,  500.,  1000};
    for ( int i=0 ; i<= nBins ; i++) {
      xBin[i] = ptBin[i] ;
    }
  }

  else if ( optX == 21) { //  21 is reserved for calibration 
    nBins = 6;  // default
    double ptBin[7]={100.000, 126, 158, 200,  251,  316.224,  500};
    for ( int i=0 ; i<= nBins ; i++) {
      xBin[i] = ptBin[i] ;
    }
  }
  else if ( optX == 210) { //  21, etabin =2 
    nBins = 6;  // default
    double ptBin[7]={100.000, 126, 158, 200,  251,  316.224, 500};
    for ( int i=0 ; i<= nBins ; i++) {
      xBin[i] = ptBin[i] ;
    }
  }
  else if ( optX == 211) { //  21, etabin =2 
    nBins = 6;  // default
    double ptBin[7]={100.000, 126, 158, 200,  251,  316.224, 500};
    for ( int i=0 ; i<= nBins ; i++) {
      xBin[i] = ptBin[i] ;
    }
  }
  else if ( optX == 212) { //  21, etabin =2 
    nBins = 5;  // default
    double ptBin[6]={100.000, 126, 158, 200,  251,  316.224};
    for ( int i=0 ; i<= nBins ; i++) {
      xBin[i] = ptBin[i] ;
    }
  }
  else if ( optX == 77) {// reweighting 
    nBins = 8;  // default
    double ptBin[10]={100.000, 125.892,  158.488,  199.525,  251.186,  316.224,  398.101,  500., 999.970};
    for ( int i=0 ; i<= nBins ; i++) {
      xBin[i] = ptBin[i] ;
    }
  }
  
  else if ( optX == 78) {// reweighting 
    nBins = 9;  // default
    double ptBin[10]={100.000, 125.892,  158.488,  199.525,  251.186,  316.224,  398.101,  500.,  630.944, 999.970};
    for ( int i=0 ; i<= nBins ; i++) {
      xBin[i] = ptBin[i] ;
    }
  }
  else if ( (optX == 79) || ( optX==80) )  {
    nBins = 4;
    //    double ptBin[10]={100.000, 125.892,  158.488,  199.525,  251.186,  316.224,  398.101,  500.,  630.944, 999.970};
    double ptBin[5]={100.000, 125.892, 199.525,  500.,  999.970};
    for ( int i=0 ; i<= nBins ; i++) {
      xBin[i] = ptBin[i] ;
    }
  }
  
}

void getXvalues( double &recoVarX, double &truthVarX, jetSubStr myJetMc, int optX) {
  if ( (optX == 1) || ( optX==2) || ( optX==3) ) {
    truthVarX = myJetMc.genPt;
    recoVarX = myJetMc.recoPt;
  }
  if ( optX == 79 )  {
    recoVarX =  myJetMc.genPt;
    truthVarX = myJetMc.recoPt;
  }
  if ( optX == 80 )  {
    recoVarX =  myJetMc.genPt;
    truthVarX = myJetMc.recoPt;
  }

}

void getYbin(int &nBins, double* yBin, int optY) {

  if ( optY == 1) {
    //    nBins = 18;
    //    double massBin[19] = { -35,-19,-17,-15, -13,-10,0,10,13,15,17,19,21,24,28,35,50,100,200};
    nBins = 13;
    double massBin[14] = { -35,-15,0,10,15,20,25,30,40,50,70,100,150,300};
    for ( int i=0 ; i<= nBins ; i++) {
      yBin[i] = massBin[i];
    }
  }
  else if ( (optY==2) || (optY==8) ) { // m/pT 
    nBins = 9;
    double massBinLog[10] = { -10000, -2.8, -2.6, -2.4, -2.2, -2, -1.8, -1.6, -1.2, -.8};
    yBin[0] = -.5;
    for ( int i=1 ; i<= nBins ; i++) {
      yBin[i] = pow(10, massBinLog[i]/2);
    }
  }
  else if ( optY == 21) { //  21 is reserved for calibration.  Used only for Truth m/pT 
    nBins = 9;
    double massBinLog[20] = { -10000, -2.8, -2.6, -2.4, -2.2, -2, -1.8, -1.6, -1.2, -.8}; 
    yBin[0] = 0;  
    for ( int i=1 ; i<= nBins ; i++) {
      yBin[i] = pow(10, massBinLog[i]/2);
    }
  }
  
  
  else if ( optY == 3) {
    nBins = 10;
    double massBin[11] = { -0.5,-0.05,0,0.05,0.1,0.13,0.16,0.2,0.24,0.3,0.5};
    for ( int i=0 ; i<= nBins ; i++) {
      yBin[i] = massBin[i];
    }
    
  }
  else if ( optY == 4) {
    nBins = 4;
    double massBin[5] = { -0.5, 0, 0.16, 0.2, 0.5};
    
    for ( int i=0 ; i<= nBins ; i++) {
      yBin[i] = massBin[i];
    }
  }
  else if ( optY == 7)   {
    nBins = 12 ;
    for ( int i=0 ; i<= nBins ; i++) {
      yBin[i] = -2000 + (2000+2000) * float(i)/nBins ;
    }
  }
  
  else if ( optY == 77) {
    nBins = 7;
    double massBin[8] = { -50, -25,0,25,50,75,100,300};
    for ( int i=0 ; i<= nBins ; i++) {
      yBin[i] = massBin[i];
    }
  }
  else if ( optY == 771) {
    nBins = 12;
    double massBin[13] = { -50, -30,-10,0,10,20,30,40,50,75,100,200,300};
    for ( int i=0 ; i<= nBins ; i++) {
      yBin[i] = massBin[i];
    }
  }
  else if ( optY == 772) {
    // /*
    nBins = 30;
    double highY = 0.4;
    double lowY = -0.2;
    double massBin[101];
    for ( int i=0 ; i<= nBins ; i++) {
      massBin[i] = lowY + (highY-lowY)*i/nBins;
      yBin[i] = massBin[i];
    }
  }
  
  else if ( optY == 78) {
    nBins = 6;
    double massBin[7] = { -0.5,0,0.1,0.13,0.16,0.2,0.5};
    for ( int i=0 ; i<= nBins ; i++) {
      yBin[i] = massBin[i];
    }
  }

  else if ( optY == 79) {
    nBins = 10;
    //    double massBin[11] = { -0.2,0,0.015,0.03,0.06,0.09,0.12,0.15,0.18,0.24,0.3};
    double massBin[11] = { -0.2,0,0.01, 0.02, 0.04, 0.06, 0.08, 0.12, 0.16, 0.24, 0.32};
    for ( int i=0 ; i<= nBins ; i++) {
      if ( massBin[i] > 0 )
	yBin[i] = massBin[i] * massBin[i];
      else
	yBin[i] = - massBin[i] * massBin[i];

      yBin[i] = yBin[i] + 1 ;
    }
  }
  else if ( optY == 80) {
    nBins = 8;
    //    double massBin[11] = { -0.2,0,0.015,0.03,0.06,0.09,0.12,0.15,0.18,0.24,0.3};
    //    double massBin[10] = { -0.1, 0 , 0.03, 0.06, 0.09, 0.12, 0.16, 0.2, 0.25, 0.3};
    //    double massBin[8] = { -0.1, 0 , 0.05, 0.10, 0.15, 0.2, 0.25, 0.3};
    double massBin[9] = { -0.05, 0.05, 0.08, 0.12, 0.15, 0.18, 0.24, 0.3,0.5};
    for ( int i=0 ; i<= nBins ; i++) {
      if ( massBin[i] > 0 )
	yBin[i] = massBin[i] * massBin[i];
      else
	yBin[i] = - massBin[i] * massBin[i];

      yBin[i] = sqrt(yBin[i] + 1) ;
    }
  }
  
}


void getRebinMpt(int &nYbins, double* yBin, int icent, int ptBin) {

  if ( (icent ==0) && ( ptBin <= 9 ) ) {
    getYbin(nYbins, yBin, 2);
  }
  else if ( (icent ==0) && ( ptBin >= 10 ) ) {
    cout << "rebinning" << endl;
    nYbins = 8;
    double ytemp[9] = { -0.5,-0.05,0,0.05,0.1,0.13,0.2,0.3,0.5};
    for ( int i =0 ; i<=8 ; i++) { 
      yBin[i] = ytemp[i];
    }
  }
  else  {
    getYbin(nYbins, yBin, 2);
  }
  
  
}


const Double_t cutdummy= -99999.0;

void getYvalues( double &recoVarY, double &truthVarY, jetSubStr myJetMc, int optY) {

  double genM = myJetMc.genMass;
  if ( genM < 0 ) genM = 0.000001;
  double recoM = myJetMc.recoMass;
  double genPt = myJetMc.genPt;
  double recoPt = myJetMc.recoPt;

  double genMoverPt = genM / genPt;
  double recoMoverPt = recoM / recoPt;

  if (optY==1)  {
    recoVarY = recoM;
    truthVarY = genM;
  }
  else if ( (optY==2) || (optY ==3) )  {
    truthVarY = genMoverPt;
    recoVarY = recoMoverPt;
  }
  else if ( optY == 7) { // charge assisted mass
    truthVarY = genM;
    recoVarY = myJetMc.recoChMassRcSubt * myJetMc.recoPt / myJetMc.recoChPtRcSubt ;
  }
  else if ( optY == 8) { // charge assisted mass
    truthVarY = genMoverPt;
    recoVarY = myJetMc.recoChMassRcSubt / myJetMc.recoChPtRcSubt ;
  }
  else if ( optY == 79) { 
    truthVarY = genMoverPt * genMoverPt;
    if ( recoMoverPt > 0 )
      recoVarY = recoMoverPt * recoMoverPt;
    else 
      recoVarY = - recoVarY;
    
    recoVarY = recoVarY + 1;
    truthVarY = truthVarY + 1;
  }
  else if ( optY == 80) { 
    truthVarY = genMoverPt * genMoverPt;
    if ( recoMoverPt > 0 )
      recoVarY = recoMoverPt * recoMoverPt;
    else 
      recoVarY = - recoVarY;
    
    recoVarY = recoVarY + 1;
    truthVarY = truthVarY + 1;
  }
  else { 
    cout << " Error in unfoldingUtil::getYvalues! " << endl << " optY  = " << optY << " option is not defined in this function" << endl;
  }
  
}


bool passGenEvent( jetSubStr myJetMc, int icent)  {

  double ptCutGen = 60;
  double ptCutUpGen = 1000;
  
  if ( myJetMc.cent != icent )
    return false;
  
  if ( myJetMc.genPt < ptCutGen ) 
    return false;
  
  if ( myJetMc.genPt > ptCutUpGen ) 
    return false;

  return true;
  
}


bool passRecoEvent( jetSubStr myJetMc, int icent)  {

  double ptCut = 100;
  double ptCutUp = 1000;

  if ( myJetMc.cent != icent )
    return false;

  if ( myJetMc.recoPt < ptCut )
    return false;

  if ( myJetMc.recoPt > ptCutUp )
    return false;
  
  return true;

}


bool passEvent( jetSubStr myJetMc, int icent, bool isMC)  {
  if ( !passRecoEvent(myJetMc, icent) )
    return false;
  if ( (isMC) && !passGenEvent(myJetMc, icent) )
    return false;
  
  return true;
  
} 

bool passEtaCut( jetSubStr myJetMc, int etaBin) {
  int absEta = fabs(myJetMc.recoEta);
  if (  (absEta < 0.3) && (etaBin == 0) )
    return true;
  if (  (absEta >= 0.3) &&  (absEta < 1.2) && (etaBin == 1) )
    return true;
  if (  (absEta >= 1.2) &&  (absEta < 2.1) && (etaBin == 2) )
    return true;
  
  return false;

}

bool passJesEvent( jetSubStr myJetMc, int icent)  {

  if ( !passGenEvent(myJetMc, icent) )
    return false;
  
  double ptCut = 50;
  double ptCutUp = 1000;
  
  if ( myJetMc.cent != icent )
    return false;

  if ( myJetMc.recoPt < ptCut )
    return false;

  if ( myJetMc.recoPt > ptCutUp )
    return false;

  return true;

}

#endif
