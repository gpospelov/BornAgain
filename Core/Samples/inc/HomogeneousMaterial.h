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
//! @file      Samples/HomogeneousMaterial.h 
//! @brief     Defines class HomogeneousMaterial.
//
// ************************************************************************** //

#ifndef HOMOGENEOUSMATERIAL_H
#define HOMOGENEOUSMATERIAL_H

#include "IMaterial.h"
#include "Types.h"

//! A homogeneous material with refraction index

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
