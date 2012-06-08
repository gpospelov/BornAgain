#include "DrawHelper.h"
#include "Exceptions.h"
#include "MultiLayer.h"

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <list>

#include "TROOT.h"
#include "TCanvas.h"
#include "TObject.h"
#include "TStyle.h"
#include "TKey.h"
#include "TLine.h"
#include "TBox.h"
#include "TLatex.h"
#include "TH1F.h"

DrawHelper *DrawHelper::m_instance = 0;
bool DrawHelper::m_destroyed = false;



DrawHelper::DrawHelper()
{

}


DrawHelper::~DrawHelper()
{
    std::cout << "DrawHelper::~DrawHelper() -> Info. Deleting material manager" << std::endl;
    m_instance = 0;
    m_destroyed = true;
}


/* ************************************************************************* */
// access to material manager
/* ************************************************************************* */
DrawHelper &DrawHelper::instance()
{
    // check if exists, if not, then initialise
    if( !m_instance) {
        // check for dead reference (i.e. object has been initialised but then somebody managed to delete it)
        if( m_destroyed ) {
            onDeadReference();
        } else {
            // first call initalise
            create();
        }
    }
    std::cout << "DrawHelper::Instance() -> Info. Accesing instance... " << m_instance << std::endl;
    return *m_instance;
}


/* ************************************************************************* */
// create single instance
/* ************************************************************************* */
void DrawHelper::create() {
    std::cout << "MaterialManager::Create() -> Info. Creating material manager" << std::endl;
    static DrawHelper theInstance;
    m_instance = &theInstance;
}


/* ************************************************************************* */
// Action for abnormal situation when object has been occasionally deleted.
// The possibility to rise object again should be still implemented.
/* ************************************************************************* */
void DrawHelper::onDeadReference() {
    throw DeadReferenceException("Dead reference detected.");
}




/* ************************************************************************* */
// assign function to canvas to handle mouse events inside canvas
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
  (void)sel;
  if ( (event == kButton1Double) ) {
    TCanvas *c = (TCanvas *) gTQSender;
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
    scattStyle->SetFuncWidth(1.);

    // get rid of X error bars and y error bar caps
    //scattStyle->SetErrorX(0.001);

    // do not display any of the standard histogram decorations
    scattStyle->SetOptTitle(1);
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


/* ************************************************************************* */
// Draw multilayer structure in gPad
/* ************************************************************************* */
void DrawHelper::DrawMultilayer(const MultiLayer *sample)
{
    size_t nlayers = sample->getNumberOfLayers();
    if(nlayers < 1) return;

    double z1 = sample->getLayerBottomZ(0);
    double z2 = sample->getLayerBottomZ(nlayers-1);

    double size = std::abs(z2 - z1);  // typical size of sample
    double margin = size*0.01;        // safety margin to avoid overlapping of layers
    double fake_thickness = size*0.3; // thickness for layers without defined thickness (like ambience&substrate)

    // frame to draw
    TH1F *h1 = gPad->DrawFrame(-size, -size*2., size, size*1.0);
    h1->GetXaxis()->SetTitle("X, [nm]");
    h1->GetYaxis()->SetTitle("Y, [nm]");
    h1->GetYaxis()->SetTitleOffset(1.4);

    // drawing properties for interfaces, material and their names
    TLine interface;
    interface.SetLineWidth(1);
    interface.SetLineStyle(3);
    interface.SetLineColor(kRed);
    TBox bulk;
    bulk.SetFillStyle(1001);
    TLatex tex;
    tex.SetNDC(false);
    tex.SetTextAlign(12);
    tex.SetTextSize(0.04);

    // defining set of good colors
    int a_colors[]={kOrange, kAzure+1, kViolet-9, kCyan+2, kViolet+6, kRed+1, kOrange-3, kBlue-9};
    std::list<int> good_colors(a_colors, a_colors+sizeof(a_colors)/sizeof(int));

    // map of correspondance between material with given name and used color
    // two colors are reserved for materials with name 'substrate' and 'ambience'
    std::map<std::string, int> colors;
    colors["substrate"] = kOrange-5;
    colors["ambience"] = kCyan-10;

    // loop over layers and drawing
    for(size_t i_layer = 0; i_layer<nlayers; i_layer++) {
        const Layer *layer = sample->getLayer(i_layer);
        double z = sample->getLayerBottomZ(i_layer);
        double thickness = layer->getThickness();

        //calculating size of box representing layer
        double x1(0), x2(0), y1(0), y2(0);
        x1 = -size*0.5;
        x2 = size*0.5;
        y1 = z;
        y2 = z+thickness;
        // but top and bottom layers need special treatment, since they thickness==0
        if(i_layer==0) { // ambience normally doesn't have thickness
            y1=z;
            y2=z+fake_thickness;
        }
        if(i_layer==nlayers-1) { // substrate normally doesn't have thickness and has wrong zbottom
            y2=z;
            y1=z-fake_thickness;
        }

        // selecting colors for bulk material, materials with same name will have same color
        int color = kBlack;
        std::string matname = layer->getMaterial()->getName();
        std::map<std::string, int>::iterator pos = colors.find(matname);
        if(pos != colors.end()) {
            // existing material
            color = pos->second;
        }else{
            // new material
            color = good_colors.front(); // taking color from list of good colors
            good_colors.remove(color);   // this color want be used anymore
            colors[matname] = color;     // saving correspondance of selected color and material
        }

        bulk.SetFillColor(color);
        bulk.DrawBox(x1,y1+margin,x2,y2-margin);
        tex.DrawLatex(x2+margin, (y1+y2)/2., matname.c_str());
        if(sample->getLayerBottomInterface(i_layer)) interface.DrawLine(x1,y1,x2,y1);
    }

    gPad->Update();
}



