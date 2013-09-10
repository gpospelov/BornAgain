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
            complex_t wavevector_scattering_factor=1.0);
    ~FormFactorDecoratorRefractiveIndex();

    FormFactorDecoratorRefractiveIndex *clone() const;

    //! Sets the material of the scatterer
    void setMaterial(const IMaterial *p_material);

    virtual complex_t getAmbientRefractiveIndex() const {
        return m_refractive_index;
    }

    virtual void setAmbientMaterial(const IMaterial *p_material);
 private:
    complex_t getRefractiveIndexFactor(const complex_t& ambient_index,
            const complex_t& particle_index) const;

    complex_t m_refractive_index;
    complex_t m_ambient_refractive_index;
    complex_t m_wavevector_scattering_factor;
};

inline FormFactorDecoratorRefractiveIndex::FormFactorDecoratorRefractiveIndex(
        IFormFactor* p_form_factor, complex_t wavevector_scattering_factor)
: FormFactorDecoratorFactor(p_form_factor, 1.0)
, m_refractive_index(1.0)
, m_ambient_refractive_index(1.0)
, m_wavevector_scattering_factor(wavevector_scattering_factor)
{
    setName("FormFactorDecoratorRefractiveIndex");
}

inline FormFactorDecoratorRefractiveIndex::~FormFactorDecoratorRefractiveIndex()
{
}

inline FormFactorDecoratorRefractiveIndex*
FormFactorDecoratorRefractiveIndex::clone() const
{
    FormFactorDecoratorRefractiveIndex *result =
            new FormFactorDecoratorRefractiveIndex(mp_form_factor->clone(),
                    m_wavevector_scattering_factor);
    result->m_refractive_index = m_refractive_index;
    result->m_ambient_refractive_index = m_ambient_refractive_index;
    result->m_factor = m_factor;
    result->setName(getName());
    return result;
}

inline void FormFactorDecoratorRefractiveIndex::setMaterial(
        const IMaterial* p_material)
{
    if (p_material) {
        m_refractive_index = p_material->getRefractiveIndex();
    }
    m_factor = getRefractiveIndexFactor(m_ambient_refractive_index,
                                        m_refractive_index);
}

inline void FormFactorDecoratorRefractiveIndex::setAmbientMaterial(
        const IMaterial *p_material)
{
    if (p_material) {
        m_ambient_refractive_index = p_material->getRefractiveIndex();
    }
    m_factor = getRefractiveIndexFactor(m_ambient_refractive_index,
                                        m_refractive_index);
}

inline complex_t FormFactorDecoratorRefractiveIndex::getRefractiveIndexFactor(
        const complex_t& ambient_index, const complex_t& particle_index) const
{
    return m_wavevector_scattering_factor *
            (particle_index*particle_index - ambient_index*ambient_index);
}

#endif /* FORMFACTORDECORATORREFRACTIVEINDEX_H_ */


