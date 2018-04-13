bool selectedCent(int icent=0) {
  if ( icent ==0 )  return true;
  if ( icent ==3 )  return true;
  if ( icent ==6 )  return true;
  if ( icent ==1 )  return true;
  if ( icent ==2 )  return true;
  if ( icent ==4 )  return true;
  if ( icent ==5 )  return true;
  else return false; 
  return 0;
}


TH2D* getRewTable(int kSample, int icent)  { 
  TFile* fReweight = new TFile("reweightFactors/reweightingFactor_weightCut10_opt772_flucCut0.3_factorized_v50.root"); // Apr 7
  //  TFile* fReweight = new TFile("reweightFactors/reweightingFactor_weightCut10_opt772_flucCut0.3_factorized.root"); // Mar 28
  //  TFile* fReweight = new TFile("reweightFactors/reweightingFactor_weightCut10_opt771_flucCut0.3_fcalWeighted.root");
  TH2D* hTemp = (TH2D*)fReweight->Get(Form("factorizedRatio_kSample%d_icent%d",kSample,icent));  // 00
  //  TH2D* hTemp = (TH2D*)fReweight->Get(Form("factorizedRatioVarP_kSample%d_icent%d",kSample,icent));  // plus50%
  //  TH2D* hTemp = (TH2D*)fReweight->Get(Form("factorizedRatioVarM_kSample%d_icent%d",kSample,icent));  // plus50%
  //  TH2D* hTemp = (TH2D*)fReweight->Get(Form("factorizedRatio2_kSample%d_icent%d",kSample,icent)); // 01
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

TString jz2PPStringSys = "jetSubstructure_ppMC_HION9_jz2sys_v50.root";
TString jz3PPStringSys = "jetSubstructure_ppMC_HION9_jz3sys_v50.root";
TString jz4PPStringSys = "jetSubstructure_ppMC_HION9_jz4sys_v50.root";

TString jz2PbPbString = jz2PbPbStringSys;
TString jz3PbPbString = jz3PbPbStringSys;
TString jz4PbPbString = jz4PbPbStringSys;

TString jz2PPString = jz2PPStringSys;
TString jz3PPString = jz3PPStringSys;
TString jz4PPString = jz4PPStringSys;

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
    nBins = 6;
    for ( int i=0 ; i<= nBins ; i++) {
      xBin[i] = -10 + ( 35 + 10 ) * float(i)/nBins;
    }
  }

  else if ( optX == 77) {// reweighting 
    nBins = 9;  // default
    double ptBin[10]={100.000, 125.892,  158.488,  199.525,  251.186,  316.224,  398.101,  500.,  630.944, 999.970};
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

}


void getXvalues( double &recoVarX, double &truthVarX, jetSubStr myJetMc, int optX) {
  if ( optX == 1 ) {
    truthVarX = myJetMc.genPt;
    recoVarX = myJetMc.recoPt;
  }
  if ( optX == 2 )  {
    recoVarX = myJetMc.nTrkRaw - myJetMc.nTrkBkg;
    truthVarX = myJetMc.genNch;
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
  else if ( (optY==2) || (optY==8) ) {
    nBins = 9;
    double massBin[10] = { -0.2,0,0.03,0.06,0.09,0.12,0.15,0.18,0.24,0.3};
    //    nBins = 9;
    //    double massBin[10] = { -0.5,0,0.03,0.06,0.09,0.12,0.15,0.18,0.24,0.5};
    for ( int i=0 ; i<= nBins ; i++) {
      yBin[i] = massBin[i];
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
    nBins = 50;
    double highY = 0.35;
    double lowY = -0.2;
    double massBin[101];
    for ( int i=0 ; i<= nBins ; i++) {
      massBin[i] = lowY + (highY-lowY)*i/nBins;
      yBin[i] = massBin[i];
    }
    //  */

    /*
      nBins = 8;
      double massBin[9] = { -0.2, -0.1, 0, 0.05,0.1,0.15,0.2,0.25,0.35};
      for ( int i=0 ; i<= nBins ; i++) {
      yBin[i] = massBin[i];
      }
    */
  }
  
  else if ( optY == 78) {
    nBins = 6;
    double massBin[7] = { -0.5,0,0.1,0.13,0.16,0.2,0.5};
    for ( int i=0 ; i<= nBins ; i++) {
      yBin[i] = massBin[i];
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
  
}


bool passGenEvent( jetSubStr myJetMc, int icent)  {

  double ptCutGen = 20;
  double ptCutUpGen = 1000;
  
  if ( myJetMc.cent != icent )
    return false;
  
  if ( myJetMc.genPt < ptCutGen ) 
    return false;
  
  if ( myJetMc.genPt > ptCutUpGen ) 
    return false;

  if ( (myJetMc.recoMass / myJetMc.recoPt) > 0.3  )
    return false;
  if ( (myJetMc.recoMass / myJetMc.recoPt) < -0.2 )
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

  if ( (myJetMc.recoMass / myJetMc.recoPt) > 0.3  )
    return false;
  if ( (myJetMc.recoMass / myJetMc.recoPt) < -0.2 )
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

  if ( (myJetMc.recoMass / myJetMc.recoPt) > 0.3  )
    return false;
  if ( (myJetMc.recoMass / myJetMc.recoPt) < -0.2 )
    return false;
  
  return true;

}
