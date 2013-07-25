// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      HomogeneousMagneticMaterial.h
//! @brief     Defines class HomogeneousMagneticMaterial
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef HOMOGENEOUSMAGNETICMATERIAL_H_
#define HOMOGENEOUSMAGNETICMATERIAL_H_

#include "HomogeneousMaterial.h"

#include <Eigen/Core>

//! An homogeneous material with magnetization

class HomogeneousMagneticMaterial : public HomogeneousMaterial
{
public:
    //! Constructs a material with _name_, _refractive_index_ and
    //! _magnetic_field_
    HomogeneousMagneticMaterial(const std::string& name,
                                const complex_t& refractive_index,
                                const kvector_t& magnetic_field);

    //! Constructs a material with _name_, refractive_index parameters and
    //! _magnetic_field_
    HomogeneousMagneticMaterial(const std::string& name,
                                double refractive_index_delta,
                                double refractive_index_beta,
                                const kvector_t& magnetic_field);

    //! Get the magnetic field (in Tesla)
    kvector_t getMagneticField() const { return m_magnetic_field; }

    //! Set the magnetic field (in Tesla)
    void setMagneticField(const kvector_t& magnetic_field) {
        m_magnetic_field = magnetic_field;
    }

    //! Indicates that the material is not scalar. This means that different
    //! polarization states will be diffracted differently
    virtual bool isScalarMaterial() { return false; }

    //! Get the scattering matrix from the refractive index, the
    //! magnetic field and a given wavevector
    Eigen::Matrix2cd getScatteringMatrix(const kvector_t& k) const;
protected:
    kvector_t m_magnetic_field; //!< magnetic field in Tesla
private:
    //! Function to initialize some private members
    void initializePrivateMemebers();
    //! This prefactor contains planck's constant, the neutron mass and
    //! its magnetic moment (units nm^-2 T^-1)
    static const double m_magnetic_prefactor;

    //! The unit matrix
    Eigen::Matrix2cd m_unit_matrix;
    std::vector<Eigen::Matrix2cd> m_pauli_operator;
};


#endif /* HOMOGENEOUSMAGNETICMATERIAL_H_ */
