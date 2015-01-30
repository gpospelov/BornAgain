// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/Lattice2DIFParameters.h
//! @brief     Defines class Lattice2DIFParameters.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef LATTICE2DIFPARAMETERS_H_
#define LATTICE2DIFPARAMETERS_H_

#include "IParameterized.h"

//! @class Lattice2DIFParameters
//! @ingroup samples
//! @brief Additional parameters for 2D lattice

class Lattice2DIFParameters
{
public:
    Lattice2DIFParameters() : m_length_1(0), m_length_2(0), m_angle(0),
        m_xi(0) { }

    double m_length_1, m_length_2;
    double m_angle;
    double m_xi;
};

#endif /* LATTICE2DIFPARAMETERS_H_ */


