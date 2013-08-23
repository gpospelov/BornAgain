// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorDecoratorRefractiveIndex.h
//! @brief     Defines class FormFactorDecoratorRefractiveIndex.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORDECORATORREFRACTIVEINDEX_H_
#define FORMFACTORDECORATORREFRACTIVEINDEX_H_

#include "FormFactorDecoratorFactor.h"
#include "HomogeneousMaterial.h"

//! Decorates a scalar form factor with the correct factor for the material's
//! refractive index and that of its surrounding material

class FormFactorDecoratorRefractiveIndex : public FormFactorDecoratorFactor
{
 public:
    FormFactorDecoratorRefractiveIndex(IFormFactor *p_form_factor,
            const complex_t& refractive_index);
    ~FormFactorDecoratorRefractiveIndex();

    FormFactorDecoratorRefractiveIndex *clone() const;

    virtual complex_t getAmbientRefractiveIndex() const {
        return m_refractive_index;
    }

    virtual void setAmbientMaterial(const IMaterial *p_material);
 private:
    complex_t getRefractiveIndexFactor(const complex_t& ambient_index,
            const complex_t& particle_index) const;

    complex_t m_refractive_index;
};

inline FormFactorDecoratorRefractiveIndex::FormFactorDecoratorRefractiveIndex(
        IFormFactor* p_form_factor, const complex_t& refractive_index)
: FormFactorDecoratorFactor(p_form_factor,
        getRefractiveIndexFactor(complex_t(1.0, 0.0), refractive_index))
, m_refractive_index(refractive_index)
{
    setName("FormFactorDecoratorRefractiveIndex");
}

inline FormFactorDecoratorRefractiveIndex::~FormFactorDecoratorRefractiveIndex()
{
}

inline FormFactorDecoratorRefractiveIndex* FormFactorDecoratorRefractiveIndex::clone() const
{
    FormFactorDecoratorRefractiveIndex *result =
            new FormFactorDecoratorRefractiveIndex(mp_form_factor->clone(), m_refractive_index);
    result->m_factor = m_factor;
    result->setName(getName());
    return result;
}

inline void FormFactorDecoratorRefractiveIndex::setAmbientMaterial(
        const IMaterial *p_material)
{
    complex_t ambient_refractive_index(1.0, 0.0);
    if (p_material) {
        ambient_refractive_index = p_material->getRefractiveIndex();
    }
    m_factor = getRefractiveIndexFactor(ambient_refractive_index, m_refractive_index);
}

inline complex_t FormFactorDecoratorRefractiveIndex::getRefractiveIndexFactor(
        const complex_t& ambient_index, const complex_t& particle_index) const
{
    return (ambient_index*ambient_index - particle_index*particle_index);
}

#endif /* FORMFACTORDECORATORREFRACTIVEINDEX_H_ */


