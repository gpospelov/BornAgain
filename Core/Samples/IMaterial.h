// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/IMaterial.h
//! @brief     Declares interface class IMaterial.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IMATERIAL_H
#define IMATERIAL_H

#include "INamed.h"
#include "Vectors3D.h"
#include "EigenCore.h"
#include "Rotations.h"
#include <string>
#include <iostream>

//! @class IMaterial
//! @ingroup materials_internal
//! @brief Interface to a named material.

class BA_CORE_API_ IMaterial : public INamed
{
public:
    //! Constructor that sets _name_.
    explicit IMaterial(const std::string &name) : INamed(name)
    {
    }

    //! Destructor.
    virtual ~IMaterial()
    {
    }

    //! Clone
    virtual IMaterial *clone() const;

    //! Indicates whether the interaction with the material is scalar.
    //! This means that different polarization states will be diffracted
    //! equally
    virtual bool isScalarMaterial() const
    {
        return true;
    }

    friend std::ostream &operator<<(std::ostream &ostr, const IMaterial &m)
    {
        m.print(ostr);
        return ostr;
    }

    //! Return refractive index.
    virtual complex_t getRefractiveIndex() const
    {
        return 1.0;
    }

#ifndef GCCXML_SKIP_THIS
    //! Get the effective scattering matrix from the refractive index
    //! and a given wavevector used for the specular calculation.
    //! This matrix appears in the one-dimensional Schroedinger equation
    //! in the z-direction
    Eigen::Matrix2cd getSpecularScatteringMatrix(const kvector_t k) const;

    //! Get the scattering matrix (~potential V) from the material.
    //! This matrix appears in the full three-dimensional Schroedinger equation.
    virtual Eigen::Matrix2cd getScatteringMatrix(double k_mag2) const;
#endif

    //! Create a new material that is transformed with respect to this one
    virtual const IMaterial *createTransformedMaterial(const IRotation &rotation) const;

protected:
    virtual void print(std::ostream &ostr) const
    {
        ostr << "IMat:" << getName() << "<" << this << ">";
    }
};

inline IMaterial *IMaterial::clone() const
{
    throw Exceptions::NotImplementedException("IMaterial is an interface and "
                                              "should not be cloned!");
}

#ifndef GCCXML_SKIP_THIS
inline Eigen::Matrix2cd IMaterial::getSpecularScatteringMatrix(const kvector_t k) const
{
    Eigen::Matrix2cd result;
    double k_mag2 = k.mag2();
    double xy_proj2 = k.magxy2() / k_mag2;
    result = getScatteringMatrix(k_mag2) - xy_proj2 * Eigen::Matrix2cd::Identity();
    return result;
}

#endif // GCCXML_SKIP_THIS

inline const IMaterial *IMaterial::createTransformedMaterial(const IRotation &rotation) const
{
    (void)rotation;
    throw Exceptions::NotImplementedException("IMaterial is an interface and "
                                              "should not be created!");
}

#endif // IMATERIAL_H
