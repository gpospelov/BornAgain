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
//! @file      Samples/IMaterial.h 
//! @brief     Defines class IMaterial.
//
// ************************************************************************** //

#ifndef IMATERIAL_H
#define IMATERIAL_H

#include <string>
#include <iostream>
#include <typeinfo>
#include "INamed.h"

//! A Material

class IMaterial : public INamed
{
public:
    IMaterial() {}
    IMaterial(const std::string &name) : INamed(name) {}
    IMaterial(const IMaterial &other);
    IMaterial &operator=(const IMaterial &other);
    virtual ~IMaterial() {}

    //! print material class
    friend std::ostream &operator<<(std::ostream &ostr, const IMaterial &m) { m.print(ostr); return ostr; }

protected:
    //! print material class
    virtual void print(std::ostream &ostr) const {
        //ostr << typeid(*this).name() << " " << this;
        ostr << getName() << " " << this;
    }

};

#endif // IMATERIAL_H
