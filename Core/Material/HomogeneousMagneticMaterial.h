// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Material/HomogeneousMagneticMaterial.h
//! @brief     Defines class HomogeneousMagneticMaterial
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef HOMOGENEOUSMAGNETICMATERIAL_H
#define HOMOGENEOUSMAGNETICMATERIAL_H

#include "HomogeneousMaterial.h"

//! A homogeneous material with magnetization.
//! @ingroup materials

class BA_CORE_API_ HomogeneousMagneticMaterial : public HomogeneousMaterial
{
public:
#ifndef SWIG
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
#endif
    //! Constructs a material with _name_, _refractive_index_ and _magnetic_field_
    HomogeneousMagneticMaterial(const std::string& name, const complex_t refractive_index,
                                const kvector_t magnetic_field);

    //! Constructs a material with _name_, refractive_index parameters and _magnetic_field_
    HomogeneousMagneticMaterial(const std::string &name, double refractive_index_delta,
                                double refractive_index_beta, const kvector_t magnetic_field);

    HomogeneousMagneticMaterial* clone() const final;
    HomogeneousMagneticMaterial* cloneInverted() const final;

    //! Get the magnetic field (in Tesla)
    kvector_t magneticField() const;

    //! Set the magnetic field (in Tesla)
    void setMagneticField(const kvector_t magnetic_field) { m_magnetic_field = magnetic_field; }

    bool isScalarMaterial() const final { return false; }

#ifndef SWIG
    virtual Eigen::Matrix2cd polarizedSLD(const WavevectorInfo& wavevectors) const;

    //! Get the scattering matrix for a material defined by its magnetization (experimental)
    Eigen::Matrix2cd polarizedSLDExperimental(const WavevectorInfo& wavevectors) const;

    virtual Eigen::Matrix2cd polarizedFresnel(const kvector_t k, double n_ref) const;
#endif

    const IMaterial* createTransformedMaterial(const Transform3D& transform) const final;

protected:
    void print(std::ostream &ostr) const final;

    kvector_t m_magnetic_field; //!< magnetic field in Tesla
private:
    //! Function to initialize some private members
    void initializePrivateMembers();
    //! This prefactor contains planck's constant, the neutron mass and
    //! its magnetic moment (units nm^-2 T^-1)
    static const double m_magnetic_prefactor;

//! The unit matrix
#ifndef SWIG
    Eigen::Matrix2cd m_unit_matrix;
    std::vector<Eigen::Matrix2cd, Eigen::aligned_allocator<Eigen::Matrix2cd> > m_pauli_operator;
#endif
};

#endif // HOMOGENEOUSMAGNETICMATERIAL_H
