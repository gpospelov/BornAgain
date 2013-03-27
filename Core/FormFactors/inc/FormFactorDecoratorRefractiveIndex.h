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

//! ?

class FormFactorDecoratorRefractiveIndex : public FormFactorDecoratorFactor
{
 public:
    FormFactorDecoratorRefractiveIndex(IFormFactor *p_form_factor, const complex_t& refractive_index);
    ~FormFactorDecoratorRefractiveIndex();

    FormFactorDecoratorRefractiveIndex *clone() const;

    virtual void setAmbientRefractiveIndex(const complex_t& ambient_refractive_index);
 private:
    complex_t getRefractiveIndexFactor(const complex_t& ambient_index, const complex_t& particle_index) const;

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
    FormFactorDecoratorRefractiveIndex *p_new =
            new FormFactorDecoratorRefractiveIndex(mp_form_factor->clone(), m_refractive_index);
    p_new->m_factor = m_factor;
    return p_new;
}

inline void FormFactorDecoratorRefractiveIndex::setAmbientRefractiveIndex(
        const complex_t& ambient_refractive_index)
{
    m_factor = getRefractiveIndexFactor(ambient_refractive_index, m_refractive_index);
}

inline complex_t FormFactorDecoratorRefractiveIndex::getRefractiveIndexFactor(
        const complex_t& ambient_index, const complex_t& particle_index) const
{
    return (ambient_index*ambient_index - particle_index*particle_index);
}

#endif /* FORMFACTORDECORATORREFRACTIVEINDEX_H_ */
