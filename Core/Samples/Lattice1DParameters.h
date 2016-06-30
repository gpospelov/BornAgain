// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Samples/Lattice1DParameters.h
//! @brief     Declares class Lattice1DParameters.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef LATTICE1DPARAMETERS_H_
#define LATTICE1DPARAMETERS_H_

#include "IParameterized.h"

//! @class Lattice1DParameters
//! @ingroup samples
//! @brief Additional parameters for 1D lattice

class BA_CORE_API_ Lattice1DParameters
{
public:
    Lattice1DParameters() : m_length(0), m_xi(0) { }

    double m_length;
    double m_xi;
};

#endif /* LATTICE1DPARAMETERS_H_ */
