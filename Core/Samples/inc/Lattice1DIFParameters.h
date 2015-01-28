// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/Lattice1DIFParameters.h
//! @brief     Defines class Lattice1DIFParameters.
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef LATTICE1DIFPARAMETERS_H_
#define LATTICE1DIFPARAMETERS_H_

#include "IParameterized.h"

//! @class Lattice1DIFParameters
//! @ingroup samples
//! @brief Additional parameters for 1D lattice

class BA_CORE_API_ Lattice1DIFParameters
{
public:
    Lattice1DIFParameters() : m_length(0), m_xi(0) { }

    double m_length;
    double m_xi;
};

#endif /* LATTICE1DIFPARAMETERS_H_ */


