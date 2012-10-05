#ifndef ROOTMINIMIZER_H
#define ROOTMINIMIZER_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   ROOTMinimizer.h
//! @brief  Definition of ROOTMinimizer class
//! @author Scientific Computing Group at FRM II
//! @date   05.10.2012

#include "Minimizer.h"
#include "OutputData.h"
// from ROOT
#include "Math/Minimizer.h"
#include "Math/Factory.h"
#include <string>

//- -------------------------------------------------------------------
//! @class FitSuite
//! @brief Wrapper for ROOT minimizers to interface with our FitSuite
//- -------------------------------------------------------------------
class ROOTMinimizer : public Minimizer
{
public:
    ROOTMinimizer(const std::string &minimizer_name, const std::string &algo_type);
    virtual ~ROOTMinimizer();

private:
    ROOT::Math::Minimizer *m_root_minimizer;
};

#endif // ROOTMINIMIZER_H
