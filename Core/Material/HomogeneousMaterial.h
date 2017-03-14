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

#include "IMaterial.h"
#include <vector>

//! An homogeneous material with a refractive index.
//! @ingroup materials

class BA_CORE_API_ HomogeneousMaterial : public IMaterial
{
public:
    //! Constructs a material with _name_ and _refractive_index_.
    HomogeneousMaterial(const std::string &name, const complex_t refractive_index);

    //! Constructs a material with _name_ and refractive_index parameters
    //! delta and beta (n = 1 - delta + i*beta).
    HomogeneousMaterial(const std::string &name, double refractive_index_delta,
                        double refractive_index_beta);
    ~HomogeneousMaterial() {}

    HomogeneousMaterial* clone() const override;
    HomogeneousMaterial* cloneInverted() const override;

    complex_t refractiveIndex() const override;
    void setRefractiveIndex(const complex_t refractive_index);

    const IMaterial* createTransformedMaterial(const Transform3D& transform) const override;

protected:
    void print(std::ostream &ostr) const override;

    complex_t m_refractive_index; //!< complex index of refraction
};

#endif // HOMOGENEOUSMATERIAL_H
