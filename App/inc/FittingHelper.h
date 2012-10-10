#ifndef FITTINGHELPER_H
#define FITTINGHELPER_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   FittingHelper.h
//! @brief  Collection of helper classes for fitting from App
//! @author Scientific Computing Group at FRM II
//! @date   08.10.2012


#include "IObserver.h"
#include <string>

namespace FittingHelper {


//- -------------------------------------------------------------------
//! @class ObserveAndDraw
//! @brief Draw fit progress at the end of each FitSuite's minimization function call
//- -------------------------------------------------------------------
class ObserveAndDraw : public IObserver
{
public:
    ObserveAndDraw(std::string canvas_name) : m_ncall(0), m_canvas_name(canvas_name) {}
    void update(IObservable *subject);
private:
    int m_ncall; //! number of call of given observer
    std::string m_canvas_name; //! canvas name were to draw
};


}


#endif // FITTINGHELPER_H
