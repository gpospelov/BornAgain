// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Material/MaterialBySLDImpl.cpp
//! @brief     Implements class MaterialBySLDImpl.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "MaterialBySLDImpl.h"
#include "WavevectorInfo.h"
#include "Units.h"

namespace
{
const double square_angstroms = Units::angstrom * Units::angstrom;

inline double getWlPrefactor(double wavelength)
{
    return wavelength * wavelength / M_PI;
}

inline complex_t getSLD(double sld_real, double sld_imag)
{
    return complex_t(sld_real, -sld_imag);
}
}

MaterialBySLDImpl::MaterialBySLDImpl(const std::string& name, double sld_real, double sld_imag,
                                     kvector_t magnetization)
    : MagneticMaterialImpl(name, magnetization)
    , m_sld_real(sld_real)
    , m_sld_imag(sld_imag)
{}

MaterialBySLDImpl* MaterialBySLDImpl::clone() const
{
    return new MaterialBySLDImpl(*this);
}

complex_t MaterialBySLDImpl::refractiveIndex(double wavelength) const
{
    return std::sqrt(refractiveIndex2(wavelength));
}

complex_t MaterialBySLDImpl::refractiveIndex2(double wavelength) const
{
    return 1.0 - getWlPrefactor(wavelength) * getSLD(m_sld_real, m_sld_imag);
}

complex_t MaterialBySLDImpl::materialData() const
{
    return complex_t(m_sld_real * square_angstroms, m_sld_imag * square_angstroms);
}

complex_t MaterialBySLDImpl::scalarSubtrSLD(const WavevectorInfo& wavevectors) const
{
    double wavelength = wavevectors.getWavelength();
    return 1.0 / getWlPrefactor(wavelength) - getSLD(m_sld_real, m_sld_imag);
}

void MaterialBySLDImpl::print(std::ostream& ostr) const
{
    ostr << "MaterialBySLD:" << getName() << "<" << this << ">{ "
         << "sld_real=" << m_sld_real << ", sld_imag = " << m_sld_imag
         << ", B=" << magnetization() << "}";
}
