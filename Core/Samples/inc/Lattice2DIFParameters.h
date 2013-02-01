#ifndef LATTICE2DIFPARAMETERS_H_
#define LATTICE2DIFPARAMETERS_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   Lattice2DIFParameters.h
//! @brief  Definition of Lattice2DIFParameters
//! @author Scientific Computing Group at FRM II
//! @date   Jan 22, 2013

#include "IParameterized.h"

struct Lattice2DIFParameters //: public IParameterized
{
    double m_length_1, m_length_2;
    double m_angle;
    double m_xi;
    double m_domain_size_1, m_domain_size_2;
    double m_corr_length_1, m_corr_length_2;
};


#endif /* LATTICE2DIFPARAMETERS_H_ */
