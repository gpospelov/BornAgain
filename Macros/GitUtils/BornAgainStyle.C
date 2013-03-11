#include "TStyle.h"
//
// Scattering Style at FRM-II, based on style file from ATLAS, based on a style file from BaBar
//

void BornAgainStyle() {

  std::cout << "\nApplying Scattering style settings...\n" << std::endl ;
  
  TStyle *scattStyle = new TStyle("Scattering","Scattering style");

  // use plain black on white colors
  Int_t icol=0; // WHITE
  scattStyle->SetFrameBorderMode(icol);
  scattStyle->SetFrameFillColor(icol);
  scattStyle->SetCanvasBorderMode(icol);
  scattStyle->SetCanvasColor(icol);
  scattStyle->SetPadBorderMode(icol);
  scattStyle->SetPadColor(icol);
  scattStyle->SetStatColor(icol);
  //scattStyle->SetFillColor(icol); // don't use: white fill color floa *all* objects

  // set the paper & margin sizes
  scattStyle->SetPaperSize(20,26);
  scattStyle->SetPadTopMargin(0.05);
  scattStyle->SetPadRightMargin(0.05);
  scattStyle->SetPadBottomMargin(0.16);
  scattStyle->SetPadLeftMargin(0.16);

  // use large fonts
  //Int_t font=72; // Helvetica italics
  Int_t font=42; // Helvetica
  Double_t tsize=0.05;
  scattStyle->SetTextFont(font);

  scattStyle->SetTextSize(tsize);
  scattStyle->SetLabelFont(font,"x");
  scattStyle->SetTitleFont(font,"x");
  scattStyle->SetLabelFont(font,"y");
  scattStyle->SetTitleFont(font,"y");
  scattStyle->SetLabelFont(font,"z");
  scattStyle->SetTitleFont(font,"z");
  
  scattStyle->SetLabelSize(tsize,"x");
  scattStyle->SetTitleSize(tsize,"x");
  scattStyle->SetLabelSize(tsize,"y");
  scattStyle->SetTitleSize(tsize,"y");
  scattStyle->SetLabelSize(tsize,"z");
  scattStyle->SetTitleSize(tsize,"z");

  // use bold lines and markers
  scattStyle->SetMarkerStyle(20);
  scattStyle->SetMarkerSize(1.2);
  scattStyle->SetHistLineWidth(2.);
  scattStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes

  // get rid of X error bars and y error bar caps
  //scattStyle->SetErrorX(0.001);

  // do not display any of the standard histogram decorations
  scattStyle->SetOptTitle(0);
  //scattStyle->SetOptStat(1111);
  scattStyle->SetOptStat(1);
  //scattStyle->SetOptFit(1111);
  scattStyle->SetOptFit(0);

  // put tick marks on top and RHS of plots
  scattStyle->SetPadTickX(1);
  scattStyle->SetPadTickY(1);

  // reset plain style
  //gROOT->SetStyle("Plain");

  gROOT->SetStyle("Scattering");
  gROOT->ForceStyle();

}

