#ifndef DRAWHELPER_H
#define DRAWHELPER_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   DrawHelper.h
//! @brief  Helper class for graphics in ROOT
//! @author Scientific Computing Group at FRM II
//! @date   01.04.2012

#include "TObject.h"
#include "ISingleton.h"

#include <vector>
#include <string>

class TCanvas;
class MultiLayer;
class TPad;


//- -------------------------------------------------------------------
//! @class DrawHelper
//! @brief Several usefull utilities for graphics in ROOT
//!
//! Provides magnification of pads in canvas, common style for drawing,
//! saving of all opened canvases from memory to pdf file
//- -------------------------------------------------------------------
class DrawHelper : public ISingleton<DrawHelper>, public TObject
{
public:
    //! set own drawing style
    static void SetStyle();

    //! saving canvases from memory into multipage pdf file
    static void SaveReportPDFObsolete();

    //! connect user canvas with magnifier function
    void SetMagnifier(TCanvas *c);

    //! process double click in canvas to magnify given pad
    void ExecuteMagnifier(Int_t event, Int_t px, Int_t py, TObject *sel);

    //! draw multilayer structure in TPad
    void DrawMultilayer(const MultiLayer *sample);

    //! create and register canvas
    TCanvas *createAndRegisterCanvas(std::string name, std::string title);

    //! save reports (pdf and ROOT)
    void saveReport();

    //! attempt to draw meso crystal lattice in 3d
    void DrawMesoCrystal(const MultiLayer *sample);

protected:
    DrawHelper();
    friend class ISingleton<DrawHelper >;

private:
    int m_default_canvas_xsize;
    int m_default_canvas_ysize;

    std::vector<TCanvas *> m_registered_canvases;

  ClassDef(DrawHelper,1)
};

#endif // DRAWHELPER_H
