#include "App.h"
#ifdef __CINT__
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   AppLinkDef.h
//! @brief  Steering file for ROOT dictionary generation
//! @author Scientific Computing Group at FRM II
//! @date   01.04.2012

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ class ISingleton<DrawHelper>+;
#pragma link C++ class DrawHelper+;

//#pragma link C++ class MultiIndex+;
//#pragma link C++ class OutputData<double>+;
#pragma link C++ class TestEventStructure+;

#endif
