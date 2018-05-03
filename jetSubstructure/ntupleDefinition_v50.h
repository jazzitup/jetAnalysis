#ifndef NTUPLEDEF_V50
#define NTUPLEDEF_V50
struct jetSubStr { //v4.7
  
  Int_t cent;
  float weight, rhoCh;
  float recoMass, recoPt, recoRawPt, recoEta, recoRap, recoPhi, recoRcPt, recoSdPt, recoSdMass, recoSdZ, recoSdTheta, recoSdPt1, recoSdRap1, recoSdPhi1, recoSdPt2, recoSdRap2, recoSdPhi2, recoSdArea1, recoSdArea2;
  float recoChPt, recoChMass, recoChPtRaw, recoChMassRaw, recoChMassGm, recoChSdPt, recoChSdMass, recoChSdZ, recoChSdTheta;
  float matchDr, genMass, genPt,  genEta, genRap, genPhi, genRcPt,  genSdPt, genSdMass, genSdz, genSdtheta, genSdPt1, genSdRap1, genSdPhi1, genSdPt2, genSdRap2, genSdPhi2, genSdArea1, genSdArea2 ;
  float genNch, genChSdPt, genChSdMass, genChSdZ, genChSdTheta;
  float recoTrNsub, recoTrTheta, recoTrMassRaw, recoTrMassCorr, recoTrDels, genTrNsub, genTrTheta, genTrMass, genTrDels;  // trimming
  float nTrkRaw, nTrkBkg, nTrkBkgNoWgt,  recoChPtRcSubt, recoChMassRcSubt, drTrkJetBkg, maxTrkPt ;   // random cone
  float fcalet;
};

#endif
