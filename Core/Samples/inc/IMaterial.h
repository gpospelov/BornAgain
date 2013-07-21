// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/IMaterial.h
//! @brief     Defines and implements interface class IMaterial.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IMATERIAL_H
#define IMATERIAL_H

#include <string>
#include <iostream>
#include "INamed.h"

//! Interface to a named material.

class IMaterial : public INamed
{
 public:
    //! Constructor that sets _name_.
    explicit IMaterial(const std::string& name) : INamed(name) {}

    //! Destructor.
    virtual ~IMaterial() {}

    //! Indicates whether the interaction with the material is scalar.
    //! This means that different polarization states will be diffracted
    //! equally
    virtual bool isScalarMaterial() { return true; }

    friend std::ostream &operator<<(std::ostream &ostr, const IMaterial &m)
    { m.print(ostr); return ostr; }

 protected:
    virtual void print(std::ostream& ostr) const
    { ostr << "IMat:" << getName() << "<" << this << ">"; }
};

#endif // IMATERIAL_H


