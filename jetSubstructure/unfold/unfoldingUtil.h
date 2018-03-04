//TString fReweightName = "reweightFactors/reweightingFactor_weightCut10_v2.root";
TString fReweightName = "reweightFactors/reweightingFactor_v4_fit.root";

bool applyMDJ = true;

struct jesHists {
  TH2D* hgTheta;
  TH2D* hgK;
  TH2D* hgMean;
  TH2D* hJES;
} ;


jesHists getGammaFunction(int kSample, int icent) {
  TFile* f1 = new TFile("../massDependentJES/JMS.root");
  int sampleID;
  if ( kSample == kPP) sampleID =0 ;
  else if ( kSample == kPbPb) {
    sampleID = icent + 1 ;
  }

  jesHists ret;
  cout << Form("h2_gammaTheta_c%d",sampleID)<< endl;
  cout << Form("h2_gammaKc%d",sampleID) << endl;
  cout << Form("h2_gammaMean_c%d",sampleID) << endl;
  TH2D* tempTheta = (TH2D*)f1->Get(Form("h2_gammaTheta_c%d",sampleID));
  TH2D* tempK = (TH2D*)f1->Get(Form("h2_gammaK_c%d",sampleID));
  TH2D* tempMean = (TH2D*)f1->Get(Form("h2_gammaMean_c%d",sampleID));
  TH2D* tempJES = (TH2D*)f1->Get(Form("h2_JES_c%d",sampleID));
  ret.hgTheta = tempTheta;
  ret.hgK = tempK;
  ret.hgMean = tempMean;
  ret.hJES = tempJES;
  return ret;
}
 

bool selectedCent(int icent=0) {
  if ( icent ==0 )  return true;
  else return false; 
  if ( icent ==1 )  return true;
  if ( icent ==2 )  return true;
  if ( icent ==3 )  return true;
  if ( icent ==4 )  return true;
  if ( icent ==5 )  return true;
  if ( icent ==6 )  return true;
  return false;
}


void getXbin(int &nBins, double* xBin, int optX) {
  if ( optX == 1 ) {

    nBins = 13;  // default
    double ptBin[14]={20,40,63.096, 82., 100.000, 125.892,  158.488,  199.525,  251.186,  316.224,  398.101,  500.,  630.944, 999.970};
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

void getYbin(int &nBins, double* yBin, double *yBinSqrt, int optY) {

  if ( optY == 1) {
    nBins = 18;
    double massBin[19] = { -35,-19,-17,-15, -13,-10,0,10,13,15,17,19,21,24,28,35,50,100,200};
    for ( int i=0 ; i<= nBins ; i++) {
      yBinSqrt[i] = massBin[i];
    }
    for ( int i=0 ; i<= nBins ; i++) {
      yBin[i] = massBin[i]*massBin[i];
      if ( massBin[i] < 0 )
        yBin[i] = - yBin[i];
    }
  }
  else if ( (optY==2) || (optY==8) ) {
    nBins = 10;
    double massBin[11] = { -0.5,-0.05,0,0.05,0.1,0.13,0.16,0.2,0.24,0.3,0.5};
    
    for ( int i=0 ; i<= nBins ; i++) {
      yBinSqrt[i] = massBin[i];
      
      if  ( massBin[i] > 0 )        yBin[i] = massBin[i]*massBin[i];
      else                          yBin[i] = -1.0 * massBin[i]*massBin[i];
    }
  }
  else if ( optY == 3) {
    nBins = 10;
    double massBin[11] = { -0.5,-0.05,0,0.05,0.1,0.13,0.16,0.2,0.24,0.3,0.5};
    
    for ( int i=0 ; i<= nBins ; i++) {
      yBinSqrt[i] = massBin[i];
      
      if  ( massBin[i] > 0 )        yBin[i] = massBin[i]*massBin[i];
      else                          yBin[i] = -1.0 * massBin[i]*massBin[i];
    }
  }
  else if ( optY == 4) {
    //    nBins = 1;
    //    double massBin[2] = { -0.5,0.5};
    nBins = 4;
    double massBin[5] = { -0.5, 0, 0.16, 0.2, 0.5};
    
    for ( int i=0 ; i<= nBins ; i++) {
      yBinSqrt[i] = massBin[i];
      if  ( massBin[i] > 0 )        yBin[i] = massBin[i]*massBin[i];
      else                          yBin[i] = -1.0 * massBin[i]*massBin[i];
    }
  }
  
  else if ( optY == 7)   {
    nBins = 12 ;
    for ( int i=0 ; i<= nBins ; i++) {
      yBin[i] = -2000 + (2000+2000) * float(i)/nBins ;
    }
  }
  
  else if ( optY == 77) {
    nBins = 6;
    double massBin[9] = { -50, -25,0,25,50,75,100,300};
    for ( int i=0 ; i<= nBins ; i++) {
      yBinSqrt[i] = massBin[i];
    }
    for ( int i=0 ; i<= nBins ; i++) {
      yBin[i] = massBin[i]*massBin[i];
      if ( massBin[i] < 0 )
        yBin[i] = - yBin[i];
    }
  }

  else if ( optY == 78) {
    nBins = 6;
    double massBin[7] = { -0.5,0,0.1,0.13,0.16,0.2,0.5};
    for ( int i=0 ; i<= nBins ; i++) {
      yBinSqrt[i] = massBin[i];
    }
    for ( int i=0 ; i<= nBins ; i++) {
      yBin[i] = massBin[i]*massBin[i];
      if ( massBin[i] < 0 )
        yBin[i] = - yBin[i];
    }
  }
  
}



const Double_t cutdummy= -99999.0;

void getYvalues( double &recoVarY, double &truthVarY, jetSubStr myJetMc, int optY) {

  double genM2 = myJetMc.genMass* myJetMc.genMass;
  double recoM2 = myJetMc.recoMass * myJetMc.recoMass;
  double genPt2 = myJetMc.genPt* myJetMc.genPt;
  double recoPt2 = myJetMc.recoPt * myJetMc.recoPt;


  if ( myJetMc.recoMass < 0 ) recoM2 = - recoM2;
  double genMoverPt2 = genM2 / genPt2;
  double recoMoverPt2 = recoM2 / recoPt2;

  if (optY==1)  {
    recoVarY = recoM2;
    truthVarY = genM2;
  }
  if ( (optY==2) || (optY ==3) )  {
    recoVarY = recoMoverPt2;
    truthVarY = genMoverPt2;
  }
  else if ( optY == 7) { // charge assisted mass
    truthVarY = genM2;
    float recoVarYsqrt = myJetMc.recoChMassRcSubt * myJetMc.recoPt / myJetMc.recoChPtRcSubt ;
    recoVarY = recoVarYsqrt * recoVarYsqrt;
    if ( recoVarYsqrt < 0)   recoVarY = - recoVarY ;
  }

  else if ( optY == 8) { // charge assisted mass
    truthVarY = genMoverPt2;
    float recoVarYsqrt = myJetMc.recoChMassRcSubt / myJetMc.recoChPtRcSubt ;
    recoVarY = recoVarYsqrt * recoVarYsqrt;
    if ( recoVarYsqrt < 0)   recoVarY = - recoVarY ;
  }

}


/*
void transformSqrt (TH1D* h1, TH1D* h2) {
  h2->Reset();
  for ( int i = 0 ; i <=h1->GetNbinsX() ; i++) {
    double xx = h1->GetBinCenter(i);
    double yy = h1->GetBinContent(i);
    double yye = h1->GetBinError(i);
    //    if ( yy < 0 )
    //      continue;
    int theBin;
    if ( xx >= 0 )    theBin = h2->FindBin( sqrt(xx) );
    else    theBin = h2->FindBin( - sqrt(-xx) );
    h2->SetBinContent(theBin, yy);
    h2->SetBinError(theBin, yye);
  }
}
*/

bool passEvent( jetSubStr myJetMc, int icent, bool isMC)  {

  double ptCut = 100;
  double ptCutGen = 20;

  double ptCutUp = 1000;
  double ptCutUpGen = 630.944;

  if ( myJetMc.cent != icent )
    return false;
  if ( myJetMc.recoPt < ptCut )
    return false;

  if ( myJetMc.recoPt > ptCutUp )
    return false;

  if ( (isMC) && ( myJetMc.genPt < ptCutGen ) ) 
    return false;

  if ( (isMC) && ( myJetMc.genPt > ptCutUpGen ) ) 
    return false;

  return true;

}


