#include "DrawHelper.h"
#include <iostream>
#include "TROOT.h"
#include "TCanvas.h"
#include "TObject.h"
#include "TStyle.h"
#include "TKey.h"


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


/* ************************************************************************* */
// assign function to handle mouse events inside canvas
/* ************************************************************************* */
void DrawHelper::SetMagnifier(TCanvas *canvas)
{
  canvas->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "DrawHelper", this, "ExecuteMagnifier(int,int,int,TObject*)");
}


/* ************************************************************************* */
// helper function to process double clicks inside TCanvas to magnify pads
/* ************************************************************************* */
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
// Set our own default style to draw things
/* ************************************************************************* */
void DrawHelper::SetStyle()
{
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




/* ************************************************************************* */
// Save canvases in pdf file.
// Method reads existing ROOT canvases from memory and save them in file
//
// Since canvases might have different aspect ratio with respect to pdf file,
// simple saving leads to the distortion of aspect ratio. To avoid this,
// following approach is used. Canvas are drawn first inside one master canvas
// with right proportion, and then master canvas goes inside pdf file.
/* ************************************************************************* */
void DrawHelper::SaveReport()
{
    std::string sfilename("report.pdf");
    int npx_master(768);
    int npy_master(1024);

    // to print many different canvases into multy-page single file one uses following convention:
    // c1->Print("name.ps["); // create new empty file
    // c1->Print("name.ps");  // print canvas content into existing file (repeat as many times as required)
    // c1->Print("name.ps]"); // close file

    // canvas to save in pdf file
    TCanvas *cmaster = new TCanvas("cmaster", "cmaster", npx_master, npy_master);
    std::string stmpname = sfilename + "[";
    cmaster->Print(stmpname.c_str()); // create new file
    //cmaster->SetBatch(kTRUE);

    // loop over existing user canvas in memory
    TList *coll = dynamic_cast<TList *>(gROOT->GetListOfCanvases());
    TIter next(coll);
    while(TCanvas *c1 = dynamic_cast<TCanvas *>(next()) ) {
        if( strcmp(c1->GetName(), "cmaster") == 0) continue; // skipping master canvas

        // canvas->Print(sfilename.c_str()); // simple method if file page and all canvases have same aspect ratio

        // preserving aspect ratio of user's canvas
        // first we need appropriate TPad in our master canvas which has same aspect ratio as user canvas
        double xlow(0), ylow(0), xup(1), yup(1);
        if( c1->GetWindowWidth() >= c1->GetWindowHeight() ) {
            double npx_user_new = npx_master;
            double npy_user_new = npx_user_new * c1->GetWindowHeight()/c1->GetWindowWidth();
            xlow=0; xup = 1;
            double ywidth = npy_user_new/npy_master;
            ylow = (1-ywidth)/2.;
            yup = ylow + ywidth;
        } else {
            double npy_user_new = npy_master;
            double npx_user_new = npy_user_new * c1->GetWindowWidth()/c1->GetWindowHeight();
            ylow=0; yup = 1;
            double xwidth = npx_user_new/npx_master;
            xlow = (1-xwidth)/2.;
            xup = xlow + xwidth;
        }
        TPad *pad = new TPad("tmppad", "tmppad", xlow, ylow, xup, yup);

        // draw pad in master canvas, draw user canvas in the pad and save whole thing in file
        cmaster->cd();
        pad->Draw();
        pad->cd();
        c1->DrawClonePad();
        cmaster->Print(sfilename.c_str());
    }

    stmpname = sfilename + "]";
    cmaster->Print(stmpname.c_str()); // close file
}



