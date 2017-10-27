// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Material/WavelengthIndependentMaterial.h
//! @brief     Defines class WavelengthIndependentMaterial.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef WAVELENGTHINDEPENDENTMATERIAL_H_
#define WAVELENGTHINDEPENDENTMATERIAL_H_

#include "BaseMaterialImpl.h"
#include "Material.h"

class BA_CORE_API_ WavelengthIndependentMaterial : public BaseMaterialImpl
{
public:
    friend BA_CORE_API_ Material MaterialBySLD(const std::string&, double, double, kvector_t);

    friend BA_CORE_API_ Material MaterialByAbsCX(const std::string&, double, double, kvector_t);

    virtual ~WavelengthIndependentMaterial();

    //! Returns pointer to a copy of material
    virtual WavelengthIndependentMaterial* clone() const override;

    virtual complex_t refractiveIndex(double wavelength) const override;
    virtual complex_t refractiveIndex2(double wavelength) const override;

    //! Returns underlying material data
    virtual complex_t materialData() const override;

    //! Returns \pi/(wl*wl) - sld, with wl being the wavelength
    virtual complex_t scalarSubtrSLD(const WavevectorInfo& wavevectors) const override;

    //! Prints object data
    virtual void print(std::ostream &ostr) const override;

private:
    WavelengthIndependentMaterial(const std::string& name, double sld, double abs_term,
                                  kvector_t magnetization);

    double m_sld; //!< product of number density and coherent scattering length
                  //!< (scattering length density)
    double m_abs_term;  //!< product of number density and
                        //!< absorption cross-section normalized to wavelength
};

#endif /* WAVELENGTHINDEPENDENTMATERIAL_H_ */
