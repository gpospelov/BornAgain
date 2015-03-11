// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/DrawHelper.cpp
//! @brief     Implements class DrawHelper.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "DrawHelper.h"
#include "Exceptions.h"
#include "MultiLayer.h"
#include "Utils.h"
#include "Lattice.h"
#include "MesoCrystal.h"
#include "Crystal.h"
#include "ParticleComposition.h"
#include "Units.h"
#include "FormFactorFullSphere.h"

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <list>
#include <algorithm>

#include "TROOT.h"
#include "TCanvas.h"
#include "TObject.h"
#include "TStyle.h"
#include "TKey.h"
#include "TLine.h"
#include "TBox.h"
#include "TLatex.h"
#include "TH1F.h"
#include "TFile.h"
#include "TDatime.h"
#include "TSystem.h"
#include <cstdlib>

std::vector<TCanvas *> DrawHelper::m_registered_canvases =
    std::vector<TCanvas *>();
int DrawHelper::m_default_canvas_xsize = 1024;
int DrawHelper::m_default_canvas_ysize = 768;

//! Assign function to canvas to handle mouse events inside canvas.

void DrawHelper::SetMagnifier(TCanvas *canvas)
{
    canvas->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)",
                    "DrawHelper", 0,
                    "ExecuteMagnifier(int,int,int,TObject*)");
}

//! Helper function to process double clicks inside TCanvas to magnify pads.

void DrawHelper::ExecuteMagnifier(int event, int px, int py, TObject *sel)
{
  (void)sel;
  if ( event == kButton1Double ) {
    TCanvas *c = (TCanvas *)gTQSender;
    char cname[256];
    sprintf(cname,"%s_%d",c->GetTitle(),std::rand());
    TPad *pad = c->Pick(px, py, 0);
    TPad *pad_new = dynamic_cast<TPad *>(pad->Clone());
    pad_new->SetPad(0.0, 0.0, 1.0, 1.0);
    TCanvas *c1 = new TCanvas(cname, cname, 1024, 768);
    c1->cd();
    pad_new->SetEditable(kTRUE);
    pad_new->Draw();
    pad_new->Modified();
    pad_new->Update();
    c1->RaiseWindow();
  }
}

//! Sets our own default style to draw things.

void DrawHelper::SetStyle()
{
    TStyle *scattStyle = new TStyle("Scattering", "Scattering style");

    // use plain black on white colors
    Int_t icol=0; // WHITE
    scattStyle->SetFrameBorderMode(icol);
    scattStyle->SetFrameFillColor(icol);
    scattStyle->SetCanvasBorderMode(icol);
    scattStyle->SetCanvasColor(icol);
    scattStyle->SetPadBorderMode(icol);
    scattStyle->SetPadColor(icol);
    scattStyle->SetStatColor(icol);

    // set the paper&  margin sizes
    scattStyle->SetPaperSize(20,26);
    scattStyle->SetPadTopMargin(0.1);
    scattStyle->SetPadRightMargin(0.1);
    scattStyle->SetPadBottomMargin(0.1);
    scattStyle->SetPadLeftMargin(0.1);

    // use large fonts
    //Int_t font=72; // Helvetica italics
    Int_t font=42; // Helvetica
    float tsize=0.05;
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
    scattStyle->SetLabelSize(tsize*0.8,"z");
    scattStyle->SetTitleSize(tsize,"z");

    // use bold lines and markers
    scattStyle->SetMarkerStyle(20);
    scattStyle->SetMarkerSize(0.2);
    scattStyle->SetHistLineWidth(2);
    scattStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes
    scattStyle->SetFuncWidth(1);

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

//! Save canvases in pdf file.

//! Method reads existing ROOT canvases from memory and save them in file
//!
//! Since canvases might have different aspect ratio with respect to pdf file,
//! simple saving leads to the distortion of aspect ratio. To avoid this,
//! following approach is used. Canvas are drawn first inside one master canvas
//! with right proportion, and then master canvas goes inside pdf file.
//!
void DrawHelper::SaveReportPDFObsolete()
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

//! Draw multilayer structure in gPad.

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
        double x1 = -size*0.5;
        double x2 = size*0.5;
        double y1 = z;
        double y2 = z+thickness;
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

//! Draw multilayer structure in gPad.

TCanvas *DrawHelper::createAndRegisterCanvas(std::string name, std::string title, int xsize, int ysize)
{
    if(xsize==0) xsize = m_default_canvas_xsize;
    if(ysize==0) ysize = m_default_canvas_ysize;

    TCanvas *c1 = new TCanvas(name.c_str(), title.c_str(), xsize, ysize);
    SetMagnifier(c1);
    m_registered_canvases.push_back(c1);

    return c1;
}


void DrawHelper::saveReport()
{
    // constructing string representing time to put it in the file name
    TDatime now;
    std::cout  << now.AsSQLString() << std::endl;
    std::string datime(now.AsSQLString());
    // replacing spaces
    for(size_t i=0; i<datime.size(); i++) if(datime[i]==' ') datime[i]='_';
    // removing ':'
    std::string::iterator end_pos = std::remove(datime.begin(), datime.end(), ':');
    datime.erase(end_pos, datime.end());

    // -----------------------
    // create pdf
    // -----------------------
    //std::string pdffilename(Utils::FileSystem::GetHomePath()+std::string("./Examples/Reports/report_")+datime+std::string(".pdf"));
    std::string pdffilename(std::string("./report_")+datime+std::string(".pdf"));
    // to print many different canvases into multy-page single file one uses following convention:
    // c1->Print("name.ps["); // create new empty file
    // c1->Print("name.ps");  // print canvas content into existing file (repeat as many times as required)
    // c1->Print("name.ps]"); // close file

    // canvas to save in pdf file
    TCanvas *cmaster = new TCanvas("cmaster", "cmaster", m_default_canvas_xsize, m_default_canvas_ysize);
    std::string stmpname = pdffilename + "[";
    cmaster->Print(stmpname.c_str()); // create new file

    for(std::vector<TCanvas *>::iterator it=m_registered_canvases.begin(); it!=m_registered_canvases.end(); ++it) {
        TCanvas *c1 = (*it);

        double xlow(0.05), ylow(0), xup(0.95), yup(0.95);
        TPad *header_pad = new TPad("headerpad", "headerpad", xlow, yup, xup, 1.);
        cmaster->cd();
        header_pad->Draw();
        header_pad->cd();
        TLatex tex;
        tex.SetNDC(1);
        tex.SetTextSize(0.4);
        std::string title=std::string(c1->GetName()) + std::string(":    ") +std::string(c1->GetTitle());
        tex.DrawLatex(0.002,0.1,title.c_str());

        TPad *main_pad = new TPad("main_pad", "main_pad", xlow, ylow, xup, yup);
        // draw pad in master canvas, draw user canvas in the pad and save whole thing in file
        cmaster->cd();
        main_pad->Draw();
        main_pad->cd();
        c1->DrawClonePad();
        cmaster->Print(pdffilename.c_str());

    }

    stmpname = pdffilename + "]";
    cmaster->Print(stmpname.c_str()); // close file

    // -----------------------
    // create ROOT
    // -----------------------
    //std::string rootfilename(Utils::FileSystem::GetHomePath()+std::string("./Examples/Reports/report_")+datime+std::string(".root"));
    std::string rootfilename(std::string("./report_")+datime+std::string(".root"));
    TFile *top = new TFile(rootfilename.c_str(), "RECREATE");
    for(std::vector<TCanvas *>::iterator it=m_registered_canvases.begin(); it!=m_registered_canvases.end(); ++it) {
        TCanvas *c1 = (*it);
        c1->Write();
    }
    top->Close();

    std::cout << "DrawHelper::saveReport() -> File '" << pdffilename << "' is created" << std::endl;
    std::cout << "DrawHelper::saveReport() -> File '" << rootfilename << "' is created" << std::endl;
}

//! Attempt to draw meso crystal lattice in 3d.

void DrawHelper::DrawMesoCrystal(const MultiLayer *sample)
{
    (void)sample;
//    gSystem->IgnoreSignal(kSigSegmentationViolation, true);
//    TEveManager::Create();

//    const LayerDecorator *layer_decor = dynamic_cast<const LayerDecorator *>(sample->getLayer(1));
//    if( !layer_decor ) throw RuntimeErrorException("DrawHelper::DrawMesoCrystal() -> layer_decor panic");
//    const MesoCrystal *meso = dynamic_cast<const MesoCrystal *>(layer_decor->getDecoration()->getParticleInfo(0)->getParticle());
//    if( !meso ) throw RuntimeErrorException("DrawHelper::DrawMesoCrystal() -> meso panic");
//    const Crystal *crystal = dynamic_cast<const Crystal *>(meso->getClusteredParticles());
//    if( !crystal ) throw RuntimeErrorException("DrawHelper::DrawMesoCrystal() -> nano_crystal panic");
//    Lattice lattice = crystal->getLattice();
//    const ParticleComposition *lattice_basis = crystal->getLatticeBasis();
//    if( !meso ) throw RuntimeErrorException("DrawHelper::DrawMesoCrystal() -> lattice_basis panic");

//    if( !ff_sphere) throw RuntimeErrorException("DrawHelper::DrawMesoCrystal() -> ff_sphere panic");

//    double nanoparticle_radius =ff_sphere->getRadius();

//    kvector_t bas_a = lattice.getBasisVectorA();
//    kvector_t bas_b = lattice.getBasisVectorB();
//    kvector_t bas_c = lattice.getBasisVectorC();

//    // drawing basis
//    TEveArrow* a1 = new TEveArrow(bas_a.x(), bas_a.y(), bas_a.z());
//    a1->SetMainColor(kYellow);
//    a1->SetTubeR(0.02);
//    a1->SetPickable(kTRUE);

//    TEveArrow* a2 = new TEveArrow(bas_b.x(), bas_b.y(), bas_b.z());
//    a2->SetMainColor(kYellow);
//    a2->SetTubeR(0.02);
//    a2->SetPickable(kTRUE);

//    TEveArrow* a3 = new TEveArrow(bas_c.x(), bas_c.y(), bas_c.z());
//    a3->SetMainColor(kYellow);
//    a3->SetTubeR(0.02);
//    a3->SetPickable(kTRUE);

////    gEve->AddElement(a1);
////    gEve->AddElement(a2);
////    gEve->AddElement(a3);

//    // drawing nano particles
//    char str[128];
//    for(int iz=0; iz<4; iz++) {
//        TEveElementList *list_of_layer = new TEveElementList();
//        sprintf(str,"zlayer%d",iz);
//        list_of_layer->SetName(str);
//        for(int ix=-4; ix<=4; ix++) {
//            for(int iy=-4; iy<=4; iy++){
////                for(int ix=-1; ix<=1; ix++) {
////                    for(int iy=-1; iy<=1; iy++){

//                kvector_t origin = iz*bas_c + ix*bas_a + iy*bas_b;
//                TEveElementList *list_of_basis = new TEveElementList();
//                sprintf(str,"basis_ix(%d)_iy(%d)",ix,iy);
//                list_of_basis->SetName(str);
//                for(size_t i=0; i<lattice_basis->getNbrParticles(); ++i) {
//                    std::vector<kvector_t> positions = lattice_basis->getParticlePositions(i);
//                    for(size_t j=0; j<positions.size(); ++j) {
//                        TEveGeoShape* x = new TEveGeoShape("SS");
//                         x->SetShape(new TGeoSphere(0, nanoparticle_radius));
//                         kvector_t pos = positions[j] + origin;
//                         if(i==0 && j==0) {
//                             x->SetMainColor(kOrange);
//                         } else{
//                             x->SetMainColor(kOrange);
//                         }

//                         if(iz==0 && pos.magxy() > 39.) continue;
//                         if(iz==1 && pos.magxy() > 34.) continue;
//                         if(iz==2 && pos.magxy() > 29.) continue;
//                         if(iz==3 && pos.magxy() > 25.) continue;
////                         if(pos.magxy() > 39.) continue;

//                         x->RefMainTrans().SetPos(pos.x(), pos.y(), pos.z()-70.);
//                         //x->SetMainTransparency(10);
//                         list_of_basis->AddElement(x);
//                         list_of_basis->SetPickable(kTRUE);
//                    }
//                }
//                list_of_layer->AddElement(list_of_basis);
//                list_of_layer->SetPickable(kTRUE);
//            }
//        }
//        gEve->AddElement(list_of_layer);
//    }

//    TEveViewer *ev = gEve->GetDefaultViewer();
//    TGLViewer  *gv = ev->GetGLViewer();
////    gv->SetGuideState(TGLUtil::kAxesEdge, kTRUE, kFALSE, 0);
////    gv->CurrentCamera().RotateRad(-.7, 0.5);
//    gv->SetCurrentCamera(TGLViewer::kCameraPerspXOY);
//    gv->CurrentCamera().RotateRad(-.7, -0.5);
//    gv->DoDraw();
//    gEve->FullRedraw3D(kTRUE);

}




