// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorDecoratorScalarMaterial.h
//! @brief     Defines class FormFactorDecoratorScalarMaterial.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORDECORATORSCALARMATERIAL_H_
#define FORMFACTORDECORATORSCALARMATERIAL_H_

#include "FormFactorDecoratorFactor.h"
#include "HomogeneousMaterial.h"

//! Decorates a scalar form factor with the correct factor for the material's
//! refractive index and that of its surrounding material

class FormFactorDecoratorScalarMaterial : public FormFactorDecoratorFactor
{
 public:
    FormFactorDecoratorScalarMaterial(IFormFactor *p_form_factor,
            complex_t wavevector_scattering_factor=1.0);
    ~FormFactorDecoratorScalarMaterial();

    FormFactorDecoratorScalarMaterial *clone() const;

    //! Sets the material of the scatterer
    void setMaterial(const IMaterial *p_material);

    //! Retrieves the refractive index of the ambient material
    virtual complex_t getAmbientRefractiveIndex() const {
        if (mp_ambient_material) {
            return mp_ambient_material->getRefractiveIndex();
        }
        return 1.0;
    }

    //! Sets the ambient material
    virtual void setAmbientMaterial(const IMaterial *p_material);
 private:
    complex_t getRefractiveIndexFactor() const;

    complex_t m_wavevector_scattering_factor;
    const IMaterial *mp_material;
    const IMaterial *mp_ambient_material;
};

inline FormFactorDecoratorScalarMaterial::FormFactorDecoratorScalarMaterial(
        IFormFactor* p_form_factor, complex_t wavevector_scattering_factor)
: FormFactorDecoratorFactor(p_form_factor, 1.0)
, m_wavevector_scattering_factor(wavevector_scattering_factor)
, mp_material(0)
, mp_ambient_material(0)
{
    setName("FormFactorDecoratorScalarMaterial");
}

inline FormFactorDecoratorScalarMaterial::~FormFactorDecoratorScalarMaterial()
{
}

inline FormFactorDecoratorScalarMaterial*
FormFactorDecoratorScalarMaterial::clone() const
{
    FormFactorDecoratorScalarMaterial *result =
            new FormFactorDecoratorScalarMaterial(mp_form_factor->clone(),
                    m_wavevector_scattering_factor);
    result->setMaterial(mp_material);
    result->setAmbientMaterial(mp_ambient_material);
    result->setName(getName());
    return result;
}

inline void FormFactorDecoratorScalarMaterial::setMaterial(
        const IMaterial* p_material)
{
    if (p_material) {
        mp_material = p_material;
    }
    m_factor = getRefractiveIndexFactor();
}

inline void FormFactorDecoratorScalarMaterial::setAmbientMaterial(
        const IMaterial *p_material)
{
    if (p_material) {
        mp_ambient_material = p_material;
    }
    m_factor = getRefractiveIndexFactor();
}

inline complex_t
FormFactorDecoratorScalarMaterial::getRefractiveIndexFactor() const
{
    if (mp_material && mp_ambient_material) {
        complex_t particle_index = mp_material->getRefractiveIndex();
        complex_t ambient_index = mp_ambient_material->getRefractiveIndex();
        return m_wavevector_scattering_factor *
                (particle_index*particle_index - ambient_index*ambient_index);
    }
    else return m_wavevector_scattering_factor;
}

#endif /* FORMFACTORDECORATORSCALARMATERIAL_H_ */


