#ifndef HOMOGENEOUSMATERIAL_H
#define HOMOGENEOUSMATERIAL_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   HomogeneousMaterial.h
//! @brief  Definition of HomogeneousMaterial class
//! @author Scientific Computing Group at FRM II
//! @date   01.04.2012

#include "IMaterial.h"
#include "Types.h"


//- -------------------------------------------------------------------
/// @class HomogeneousMaterial
/// @brief Definition of homogeneous material with refraction index
//- -------------------------------------------------------------------
class HomogeneousMaterial : public IMaterial
{
public:
    HomogeneousMaterial();
    HomogeneousMaterial(const complex_t &refractive_index);
    HomogeneousMaterial(const std::string &name, const complex_t &refractive_index);
    HomogeneousMaterial(const std::string &name, double refractive_index_real, double refractive_index_imag );
    HomogeneousMaterial(const HomogeneousMaterial &other);
    HomogeneousMaterial &operator=(const HomogeneousMaterial &other);
    virtual ~HomogeneousMaterial() {}

    /// return refractive index of the material
    complex_t getRefractiveIndex() const { return m_refractive_index; }

    /// set refractive index of he material
    void setRefractiveIndex(complex_t refractive_index) { m_refractive_index = refractive_index; }

protected:
    //! print material class
    virtual void print(std::ostream &ostr) const {
        ostr  << "  " << getName() << " " << this << " R" << m_refractive_index;
    }

    complex_t m_refractive_index; ///< complex index of refraction
};

#endif // HOMOGENEOUSMATERIAL_H
