// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Lattice/Lattice1DParameters.h
//! @brief     Defines class Lattice1DParameters.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef LATTICE1DPARAMETERS_H
#define LATTICE1DPARAMETERS_H

#include "Wrap/WinDllMacros.h"

//! Basic parameters of a one-dimensional lattice.
//! @ingroup samples

class BA_CORE_API_ Lattice1DParameters
{
public:
    Lattice1DParameters() : m_length(0), m_xi(0) {}
    //! @param length: Lattice constant.
    //! @param xi: Lattice rotation angle.
    Lattice1DParameters(double length, double xi) : m_length(length), m_xi(xi) {}

    double m_length;
    double m_xi;
};

#endif // LATTICE1DPARAMETERS_H
