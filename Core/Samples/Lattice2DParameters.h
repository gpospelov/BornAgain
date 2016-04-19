// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/Lattice2DParameters.h
//! @brief     Declares class Lattice2DParameters.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef LATTICE2DPARAMETERS_H_
#define LATTICE2DPARAMETERS_H_

#include "IParameterized.h"

//! @class Lattice2DParameters
//! @ingroup samples
//! @brief Additional parameters for 2D lattice

class Lattice2DParameters
{
public:
    Lattice2DParameters() : m_length_1(0), m_length_2(0), m_angle(0), m_xi(0) { }

    double m_length_1, m_length_2;
    double m_angle;
    double m_xi;
};

inline double getUnitCellArea(const Lattice2DParameters& lattice_params) {
    double length_1 = lattice_params.m_length_1;
    double length_2 = lattice_params.m_length_2;
    double angle = lattice_params.m_angle;
    return std::abs(length_1*length_2*std::sin(angle));
}

#endif /* LATTICE2DPARAMETERS_H_ */
