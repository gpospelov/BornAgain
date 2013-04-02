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
//#include <typeinfo>
#include "INamed.h"

//! Interface to a named material.

class IMaterial : public INamed
{
 public:
    //! Constructor that sets _name_.
    explicit IMaterial(const std::string& name) : INamed(name) {}

    //! Copy constructor. TODO: test whether needed
    IMaterial(const IMaterial& other) : INamed(other) {}

    //! Destructor.
    virtual ~IMaterial() {}

    friend std::ostream &operator<<(std::ostream &ostr, const IMaterial &m)
    { m.print(ostr); return ostr; }

 protected:
    virtual void print(std::ostream& ostr) const
    { ostr << "IMat:" << getName() << "<" << this << ">"; }
        // TODO: try ostr << typeid(*this).name() << " " << this;
};

#endif // IMATERIAL_H


