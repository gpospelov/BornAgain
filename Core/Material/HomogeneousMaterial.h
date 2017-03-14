// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Material/HomogeneousMaterial.h
//! @brief     Defines and implements class HomogeneousMaterial.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef HOMOGENEOUSMATERIAL_H
#define HOMOGENEOUSMATERIAL_H

#include "INamed.h"
#include "Complex.h"
#include "Vectors3D.h"
#include "EigenCore.h"
#include <vector>

class Transform3D;
class WavevectorInfo;

//! An homogeneous material with a refractive index and (optionally) a magnetic field.
//! @ingroup materials

class BA_CORE_API_ HomogeneousMaterial : public INamed
{
public:
    //! Constructs a default material (vacuum).
    HomogeneousMaterial();

    //! Constructs a material with _name_ and _refractive_index_.
    HomogeneousMaterial(const std::string &name, const complex_t refractive_index,
                        const kvector_t magnetic_field=kvector_t());

    //! Constructs a material with _name_ and refractive_index parameters
    //! delta and beta (n = 1 - delta + i*beta).
    HomogeneousMaterial(const std::string &name, double refractive_index_delta,
                        double refractive_index_beta, const kvector_t magnetic_field=kvector_t());
    ~HomogeneousMaterial() {}

    //! Constructs a material with inverted magnetic field
    HomogeneousMaterial inverted() const;

    complex_t refractiveIndex() const;
    void setRefractiveIndex(const complex_t refractive_index);

    //! Indicates whether the interaction with the material is scalar.
    //! This means that different polarization states will be diffracted equally
    bool isScalarMaterial() const;

    bool isMagneticMaterial() const { return !isScalarMaterial(); }

    //! Get the magnetic field (in Tesla)
    kvector_t magneticField() const;

    //! Set the magnetic field (in Tesla)
    void setMagneticField(const kvector_t magnetic_field);

    complex_t scalarSLD(const WavevectorInfo& wavevectors) const;

    //! Return the potential term that is used in the one-dimensional Fresnel calculations
    complex_t scalarFresnel(const kvector_t k, double n_ref) const;

#ifndef SWIG
    virtual Eigen::Matrix2cd polarizedSLD(const WavevectorInfo& wavevectors) const;

    //! Get the scattering matrix for a material defined by its magnetization (experimental)
    Eigen::Matrix2cd polarizedSLDExperimental(const WavevectorInfo& wavevectors) const;

    virtual Eigen::Matrix2cd polarizedFresnel(const kvector_t k, double n_ref) const;
#endif
    HomogeneousMaterial transformedMaterial(const Transform3D& transform) const;

    friend std::ostream& operator<<(std::ostream& ostr, const HomogeneousMaterial& mat);
private:
    void print(std::ostream &ostr) const;

    complex_t m_refractive_index; //!< complex index of refraction
    kvector_t m_magnetic_field; //!< magnetic field in Tesla
};

// Comparison operators:
bool operator==(const HomogeneousMaterial& left, const HomogeneousMaterial& right);
bool operator!=(const HomogeneousMaterial& left, const HomogeneousMaterial& right);

#endif // HOMOGENEOUSMATERIAL_H
