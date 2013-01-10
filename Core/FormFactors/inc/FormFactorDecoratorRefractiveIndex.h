#ifndef FORMFACTORDECORATORREFRACTIVEINDEX_H_
#define FORMFACTORDECORATORREFRACTIVEINDEX_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   FormFactorDecoratorRefractiveIndex.h
//! @brief  Definition of FormFactorDecoratorRefractiveIndex class
//! @author Scientific Computing Group at FRM II
//! @date   Jul 12, 2012

#include "FormFactorDecoratorFactor.h"

class FormFactorDecoratorRefractiveIndex : public FormFactorDecoratorFactor
{
public:
    FormFactorDecoratorRefractiveIndex(IFormFactor *p_form_factor, const complex_t &refractive_index);
    ~FormFactorDecoratorRefractiveIndex();

    FormFactorDecoratorRefractiveIndex *clone() const;

    virtual void setAmbientRefractiveIndex(const complex_t &ambient_refractive_index);
private:
    FormFactorDecoratorRefractiveIndex(const FormFactorDecoratorRefractiveIndex &);
    FormFactorDecoratorRefractiveIndex &operator=(const FormFactorDecoratorRefractiveIndex &);

    complex_t getRefractiveIndexFactor(const complex_t &ambient_index, const complex_t &particle_index);

    complex_t m_refractive_index;
};

inline FormFactorDecoratorRefractiveIndex::FormFactorDecoratorRefractiveIndex(
        IFormFactor* p_form_factor, const complex_t &refractive_index)
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
        const complex_t &ambient_refractive_index)
{
    m_factor = getRefractiveIndexFactor(ambient_refractive_index, m_refractive_index);
}

inline complex_t FormFactorDecoratorRefractiveIndex::getRefractiveIndexFactor(
        const complex_t &ambient_index, const complex_t &particle_index)
{
    return (ambient_index*ambient_index - particle_index*particle_index);
}

#endif /* FORMFACTORDECORATORREFRACTIVEINDEX_H_ */
