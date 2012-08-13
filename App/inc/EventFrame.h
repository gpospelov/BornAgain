#ifndef EVENTFRAME_H
#define EVENTFRAME_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   EventFrame.h
//! @brief  Definition of EventFrame class for writing in root files
//! @author Scientific Computing Group at FRM II
//! @date   19.07.2012


#include "TObject.h"
#include <vector>

//- -------------------------------------------------------------------
//! @class EventFrame
//! @brief event structure to save in the root file
//- -------------------------------------------------------------------
class EventFrame
{
public:
    EventFrame();
    virtual ~EventFrame(){}

    void clear();

    int nframe; // number of frame
    double alpha_i; // alpha_i
    double phi_i; // phi_i;

    int nphi_f; // number of phi_f bins in the frame
    double phi_f_min; // minimum value of phi_f
    double phi_f_max; // maximu value of phi_f

    int nalpha_f; // number of alpha_f bins in the frame
    double alpha_f_min; // minimum value of alpha_f
    double alpha_f_max; // maximum value of alpha_f

    double malpha; // rotation of meso around Y
    double mphi; // rotation of meso around Z
    double npR; // size of nano particles inside if meso
    std::vector<std::vector<double > > vi; // frame of measured intensities [phi_f][alpha_f]
    std::vector<std::vector<double > > valpha_f; // values of alpha_f for the frame
    std::vector<std::vector<double > > vphi_f; // values of phi_f for the frames

    ClassDef(EventFrame,1)
};



#endif // EventFrame_H
