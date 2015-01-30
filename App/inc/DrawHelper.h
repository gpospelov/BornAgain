// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/DrawHelper.h
//! @brief     Defines class DrawHelper.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DRAWHELPER_H
#define DRAWHELPER_H

#include "TObject.h"
#include <vector>
#include <string>

#include "TCanvas.h"
#include "TH2D.h"

class MultiLayer;
class TPad;

//! Several usefull utilities for graphics in ROOT

//! Provides magnification of pads in canvas, common style for drawing,
//! saving of all opened canvases from memory to pdf file
//!
class DrawHelper :public TObject
{
public:
    //! Sets own drawing style
    static void SetStyle();

    //! saving canvases from memory into multipage pdf file
    static void SaveReportPDFObsolete();

    //! connect user canvas with magnifier function
    static void SetMagnifier(TCanvas *c);

    //! process double click in canvas to magnify given pad
    static void ExecuteMagnifier(Int_t event, Int_t px, Int_t py, TObject *sel);

    //! draw multilayer structure in TPad
    static void DrawMultilayer(const MultiLayer *sample);

    //! Creates and register canvas
    static TCanvas *createAndRegisterCanvas(
        std::string name, std::string title, int xsize=0, int ysize=0);

    //! save reports (pdf and ROOT)
    static void saveReport();

    //! attempt to draw meso crystal lattice in 3d
    static void DrawMesoCrystal(const MultiLayer *sample);

private:
    static int m_default_canvas_xsize;
    static int m_default_canvas_ysize;
    static std::vector<TCanvas *> m_registered_canvases;

  ClassDef(DrawHelper,1)
};

#endif /* DRAWHELPER_H */


