// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Material/RefractiveIndexMaterial.h
//! @brief     Defines class RefractiveIndexMaterial.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef REFRACTIVECOEFMATERIAL_H_
#define REFRACTIVECOEFMATERIAL_H_

#include "BaseMaterialImpl.h"
#include "Material.h"

class BA_CORE_API_ RefractiveCoefMaterial : public BaseMaterialImpl
{
public:
    //! Constructs a material with _name_ and _refractive_index_.
    friend BA_CORE_API_ Material RefractiveIndexMaterial(const std::string&, complex_t, kvector_t);

    //! Constructs a material with _name_ and refractive_index parameters
    //! \f$\delta\f$ and \f$\beta\f$ for refractive index \f$n = 1 - \delta + i \beta\f$.
    friend BA_CORE_API_ Material RefractiveIndexMaterial(const std::string&, double, double,
                                                         kvector_t);

    virtual ~RefractiveCoefMaterial();

    //! Returns pointer to a copy of material
    virtual RefractiveCoefMaterial* clone() const override;

    virtual complex_t refractiveIndex(double wavelength) const override;
    virtual complex_t refractiveIndex2(double wavelength) const override;

    //! Returns underlying material data
    virtual complex_t materialData() const override;

    //! Returns \pi/(wl*wl) - sld, with wl being the wavelength
    virtual complex_t scalarSubtrSLD(const WavevectorInfo& wavevectors) const override;

    //! Prints object data
    virtual void print(std::ostream &ostr) const override;

private:
    RefractiveCoefMaterial(const std::string& name, double delta, double beta,
                           kvector_t magnetization);

    double m_delta; //!< \f$\delta\f$ coefficient for refractive index \f$n = 1 - \delta + i \beta\f$
    double m_beta; //!< \f$\beta\f$ coefficient for refractive index \f$n = 1 - \delta + i \beta\f$
};

#endif /* REFRACTIVECOEFMATERIAL_H_ */
