// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @copyright Forschungszentrum Jülich GmbH 2013
//             
//  Homepage:  apps.jcns.fz-juelich.de/BornAgain
//  License:   GNU General Public License v3 or higher (see COPYING)
//
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
//! @file      Samples/Lattice2DIFParameters.h 
//! @brief     Defines class Lattice2DIFParameters.
//
// ************************************************************************** //

#ifndef LATTICE2DIFPARAMETERS_H_
#define LATTICE2DIFPARAMETERS_H_

#include "IParameterized.h"

class Lattice2DIFParameters
{
public:
    Lattice2DIFParameters() : m_length_1(0), m_length_2(0), m_angle(0),
        m_xi(0), m_domain_size_1(0), m_domain_size_2(0),
        m_corr_length_1(0), m_corr_length_2(0) { }

    double m_length_1, m_length_2;
    double m_angle;
    double m_xi;
    double m_domain_size_1, m_domain_size_2;
    double m_corr_length_1, m_corr_length_2;
};

#endif /* LATTICE2DIFPARAMETERS_H_ */
