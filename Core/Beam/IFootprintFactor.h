// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Beam/IFootprintFactor.h
//! @brief     Defines class IFootprintFactor.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef IFOOTPRINTFACTOR_H_
#define IFOOTPRINTFACTOR_H_

#include "WinDllMacros.h"

class MultiLayer;
class Beam;

//! Defines the base for classes to calculate beam footprint factor
//! @ingroup simulation

class BA_CORE_API_ IFootprintFactor
{
public:
    IFootprintFactor(double width_ratio);
    virtual ~IFootprintFactor();

    void setWidthRatio(double width_ratio);
    double widthRatio() const {return m_width_ratio;}

    //! Calculate footprint correction coefficient from the beam incident angle _alpha_.
    virtual double calculate(double alpha) const = 0;

private:
    double m_width_ratio; //! Beam to sample width ratio
};

#endif /* IFOOTPRINTFACTOR_H_ */
