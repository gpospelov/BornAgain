// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Material/MaterialBySLDImpl.h
//! @brief     Defines class MaterialBySLDImpl.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef MATERIALBYSLDIMPL_H_
#define MATERIALBYSLDIMPL_H_

#include "MagneticMaterialImpl.h"
#include "Material.h"

//! Material implementation based on wavelength-independent data (valid for a range of wavelengths)
//! @ingroup materials

class BA_CORE_API_ MaterialBySLDImpl : public MagneticMaterialImpl
{
public:
    friend BA_CORE_API_ Material MaterialBySLD(const std::string& name, double sld, double abs_term,
                                               kvector_t magnetization);

    virtual ~MaterialBySLDImpl() = default;

    //! Returns pointer to a copy of material
    MaterialBySLDImpl* clone() const override;

    //! Returns refractive index
    complex_t refractiveIndex(double wavelength) const override;

    //! Returns squared refractive index
    complex_t refractiveIndex2(double wavelength) const override;

    //! Returns underlying material data
    complex_t materialData() const override;

    //! Returns type of material implementation
    MATERIAL_TYPES typeID() const override
    {
        return MATERIAL_TYPES::MaterialBySLD;
    }

    //! Returns (\f$ \pi/\lambda^2 \f$ - sld), sld (in \f$nm^{-2}\f$) being the scattering length density
    complex_t scalarSubtrSLD(const WavevectorInfo& wavevectors) const override;

    //! Prints object data
    void print(std::ostream &ostr) const override;

private:
    MaterialBySLDImpl(const std::string& name, double sld, double abs_term,
                                  kvector_t magnetization);

    double m_sld; //!< product of number density and coherent scattering length
                  //!< (scattering length density)
    double m_abs_term;  //!< product of number density and
                        //!< absorption cross-section normalized to wavelength
};

#endif /* MATERIALBYSLDIMPL_H_ */
