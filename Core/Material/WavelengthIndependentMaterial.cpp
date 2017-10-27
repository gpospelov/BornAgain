#include "WavelengthIndependentMaterial.h"
#include "WavevectorInfo.h"

namespace
{
// Returns SLD-like complex value, where real part is SLD and imaginary one is
// wavelength-independent absorptive term
inline complex_t getSLD(double delta_factor, double beta_factor)
{
    return complex_t(delta_factor, -beta_factor / 2.0);
}

inline double getWlPrefactor(double wavelength)
{
    return wavelength * wavelength / M_PI;
}
}

WavelengthIndependentMaterial::WavelengthIndependentMaterial(const std::string& name, double sld,
                                                             double abs_term,
                                                             kvector_t magnetization)
    : BaseMaterialImpl(name, magnetization), m_sld(sld), m_abs_term(abs_term)
{}

WavelengthIndependentMaterial::~WavelengthIndependentMaterial()
{}

WavelengthIndependentMaterial* WavelengthIndependentMaterial::clone() const
{
    return new WavelengthIndependentMaterial(*this);
}

complex_t WavelengthIndependentMaterial::refractiveIndex(double wavelength) const
{
    return std::sqrt(refractiveIndex2(wavelength));
}

complex_t WavelengthIndependentMaterial::refractiveIndex2(double wavelength) const
{
    return 1.0 - getWlPrefactor(wavelength) * getSLD(m_sld, m_abs_term);
}

complex_t WavelengthIndependentMaterial::materialData() const
{
    return complex_t(m_sld, m_abs_term);
}

complex_t WavelengthIndependentMaterial::scalarSubtrSLD(const WavevectorInfo& wavevectors) const
{
    double wavelength = wavevectors.getWavelength();
    return 1.0 / getWlPrefactor(wavelength) - getSLD(m_sld, m_abs_term);
}

void WavelengthIndependentMaterial::print(std::ostream& ostr) const
{
    ostr << "WavelengthIndependentMaterial:" << getName() << "<" << this << ">{ "
         << "sld=" << m_sld << ", absorp_term=" << m_abs_term
         << ", B=" << magnetization() << "}";
}
