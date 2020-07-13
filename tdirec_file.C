//testing wrting a ROOT macro for generating the TTree PDFs for MMC
//note: ctrl + / lets you block comment

// #include <TRandom2.h>
// #include <TH1.h>
// #include <TGraph.h>
// #include <TF1.h>
#include <TMath.h>
// #include <TLorentzVector.h>
// #include <TVector3.h>
// #include <vector>
// #include <TObject.h>
// #include <TDirectory.h>
// #include <TTree.h>
//
// #include <memory>
// #include <string>

#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TRandom.h"
#include "TTree.h"
#include "TFormula.h"
#include "TF1.h"

Double_t fit_pT(Double_t *x, Double_t *par){
   Float_t xx = x[0];
   Double_t f = par[0]*exp(-par[1]*sqrt(xx)) + par[2] + par[3]*xx;
   return f;
 }

Double_t fit_nuTau(Double_t *x, Double_t *par){
   Float_t xx = x[0];
   //Double_t f = par[0] * exp(-0.5*( (x-par[1]) / par[2] )*( (x-par[1]) / par[2]));
   Double_t f = par[0] * exp(-0.5*pow(((xx-par[1])/par[2]),2.0)) + exp(par[3] + par[4]*xx);
   return f;
  }


int load_file(){

  //declaring file and folder structure for PDFs
   TFile *hfile = TFile::Open("/Users/ibhallaladd/Desktop/pdf_test_new.root","RECREATE","Demo ROOT file with fit pdfs & trees");
   hfile->mkdir("MMC2019MC16");
   hfile->cd("MMC2019MC16");

   hfile->mkdir("MMC2019MC16/lep");
   //hfile->cd("lep");
   hfile->mkdir("MMC2019MC16/lep/nuTauRatio");
   hfile->mkdir("MMC2019MC16/lep/tauNuAngle3d");
   hfile->mkdir("MMC2019MC16/lep/nuMass");

   hfile->mkdir("MMC2019MC16/had");
   //hfile->cd("had");
   hfile->mkdir("MMC2019MC16/had/tauNuAngle3d-1p0n");
   hfile->mkdir("MMC2019MC16/had/tauNuAngle3d-1p1n");
   hfile->mkdir("MMC2019MC16/had/tauNuAngle3d-1pXn");
   hfile->mkdir("MMC2019MC16/had/tauNuAngle3d-3p0n");
   hfile->mkdir("MMC2019MC16/had/tauNuAngle3d-3pXn");
   hfile->mkdir("MMC2019MC16/had/nuTauRatioLead-1p0n");
   hfile->mkdir("MMC2019MC16/had/nuTauRatioLead-1p1n");
   hfile->mkdir("MMC2019MC16/had/nuTauRatioLead-1pXn");
   hfile->mkdir("MMC2019MC16/had/nuTauRatioLead-3p0n");
   hfile->mkdir("MMC2019MC16/had/nuTauRatioLead-3pXn");
   hfile->mkdir("MMC2019MC16/had/nuTauRatioSublead-1p0n");
   hfile->mkdir("MMC2019MC16/had/nuTauRatioSublead-1p1n");
   hfile->mkdir("MMC2019MC16/had/nuTauRatioSublead-1pXn");
   hfile->mkdir("MMC2019MC16/had/nuTauRatioSublead-3p0n");
   hfile->mkdir("MMC2019MC16/had/nuTauRatioSublead-3pXn");

   //now filling the folders with TF1s, need to cd before making the TF1
   //is this how it should be specified to the MMC?

   //-------------------COPY THIS BLOCK AND CHANGE RELEVANT PIECES FOR SAVING NEW PDFS-------------------
   hfile->cd("MMC2019MC16/lep/nuTauRatio");
   TF1 *nuTauRatio_lep = new TF1("fit",fit_nuTau,0,50,5);
   nuTauRatio_lep->SetParameters(-2.41143324e+05,-4.15457437e+00, -9.84793203e-01,3.50135378e+00,-3.98569060e+00);
   nuTauRatio_lep->SetParNames("p0", "p1", "p2", "p3", "p4");
   nuTauRatio_lep->Write();
   //----------------------------------------------------------------------------------------------------



   hfile->Close();

}
