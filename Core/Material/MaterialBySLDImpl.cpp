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

namespace
{
// Returns SLD-like complex value, where real part is SLD and imaginary one is
// wavelength-independent absorptive term
inline complex_t getSLD(double sld, double abs_term)
{
    return complex_t(sld, -abs_term / 2.0);
}

inline double getWlPrefactor(double wavelength)
{
    return wavelength * wavelength / M_PI;
}
}

MaterialBySLDImpl::MaterialBySLDImpl(const std::string& name, double sld,
                                                             double abs_term,
                                                             kvector_t magnetization)
    : MagneticMaterialImpl(name, magnetization), m_sld(sld), m_abs_term(abs_term)
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
    return 1.0 - getWlPrefactor(wavelength) * getSLD(m_sld, m_abs_term);
}

complex_t MaterialBySLDImpl::materialData() const
{
    return complex_t(m_sld, m_abs_term);
}

complex_t MaterialBySLDImpl::scalarSubtrSLD(const WavevectorInfo& wavevectors) const
{
    double wavelength = wavevectors.getWavelength();
    return 1.0 / getWlPrefactor(wavelength) - getSLD(m_sld, m_abs_term);
}

void MaterialBySLDImpl::print(std::ostream& ostr) const
{
    ostr << "MaterialBySLD:" << getName() << "<" << this << ">{ "
         << "sld=" << m_sld << ", absorp_term=" << m_abs_term
         << ", B=" << magnetization() << "}";
}
