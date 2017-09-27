#include "drawBasicPerf.C"
void drawJES() {
  Jes Jcent0 = drawBasicPerf(10,0);
  
  TCanvas* cj1 = new TCanvas("cj1","",800,400);
  cj1->Divide(2,1);
  cj1->cd(1);
  Jcent0.hScale[1]->Draw();
  cj1->cd(2);
  Jcent0.hRes[1]->Draw();
  cj1->SaveAs("cj1.png");
}
