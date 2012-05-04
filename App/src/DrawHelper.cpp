#include "DrawHelper.h"
#include <iostream>
#include "TROOT.h"
#include "TCanvas.h"
#include "TObject.h"
#include "TStyle.h"

DrawHelper *DrawHelper::m_instance = 0;


DrawHelper::DrawHelper()
{

}


DrawHelper::~DrawHelper()
{

}


DrawHelper *DrawHelper::instance()
{
  if( m_instance == 0) {
    m_instance = new DrawHelper();
  }
  return m_instance;
}


void DrawHelper::SetMagnifier(TCanvas *canvas)
{
  canvas->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "DrawHelper", this, "ExecuteMagnifier(int,int,int,TObject*)");
}


void DrawHelper::ExecuteMagnifier(int event, int px, int py, TObject *sel)
{
  TCanvas *c = (TCanvas *) gTQSender;
  if(sel) {
    // we do not need it for the moment
  }
  if ( (event == kButton1Double) ) {
    char cname[256];
    sprintf(cname,"%s_%d",c->GetTitle(),(int)time(0));
    TPad *pad = c->Pick(px, py, 0);
    TPad *pad_new = (TPad *) pad->Clone();
    pad_new->SetPad(0.0, 0.0, 1.0, 1.0);
    TCanvas *c1 = new TCanvas(cname, cname, 800, 600);
    c1->cd();
    pad_new->SetEditable(kTRUE);
    pad_new->Draw();
    pad_new->Modified();
     //gVirtualX->SetCursor(gPad->GetId()     , gVirtualX->CreateCursor(kWatch));
    pad_new->Update();
    c1->RaiseWindow();
  }
}



/* ************************************************************************* */
// Set our own style to draw things
/* ************************************************************************* */
void DrawHelper::SetStyle() {

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
    scattStyle->SetMarkerSize(0.2);
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
