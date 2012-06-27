#ifndef IMATERIAL_H
#define IMATERIAL_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   IMaterial.h
//! @brief  Definition of IMaterial class
//! @author Scientific Computing Group at FRM II
//! @date   01.04.2012

#include <string>
#include <iostream>
#include <typeinfo>
#include "INamed.h"


//- -------------------------------------------------------------------
//! @class IMaterial
//! @brief Material definition
//- -------------------------------------------------------------------
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
