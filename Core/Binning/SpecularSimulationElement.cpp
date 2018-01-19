#include "SpecularSimulationElement.h"
#include "SpecularData.h"

const double phi_i_0 = 0.0;

SpecularSimulationElement::SpecularSimulationElement(double wavelength, double alpha_i)
    : m_wavelength(wavelength)
    , m_alpha_i(alpha_i)
    , m_intensity(0.0)
    , m_specular_data(std::make_unique<SpecularData>())
{
}

SpecularSimulationElement::SpecularSimulationElement(const SpecularSimulationElement& other)
    : m_polarization(other.m_polarization)
    , m_wavelength(other.m_wavelength)
    , m_alpha_i(other.m_alpha_i)
    , m_intensity(other.m_intensity)
{
    if (other.m_specular_data)
        m_specular_data.reset(new SpecularData(*other.m_specular_data));
}

SpecularSimulationElement::SpecularSimulationElement(SpecularSimulationElement&& other) noexcept
    : m_polarization(std::move(other.m_polarization))
    , m_wavelength(other.m_wavelength)
    , m_alpha_i(other.m_alpha_i)
    , m_intensity(other.m_intensity)
    , m_specular_data(std::move(other.m_specular_data))
{
}

SpecularSimulationElement::~SpecularSimulationElement() = default;

SpecularSimulationElement& SpecularSimulationElement::operator=(const SpecularSimulationElement &other)
{
    if (this != &other) {
        SpecularSimulationElement tmp(other);
        tmp.swapContent(*this);
    }
    return *this;
}

kvector_t SpecularSimulationElement::getKi() const
{
    return vecOfLambdaAlphaPhi(m_wavelength, m_alpha_i, phi_i_0);
}

void SpecularSimulationElement::swapContent(SpecularSimulationElement &other)
{
    m_polarization.swapContent(other.m_polarization);
    std::swap(m_wavelength, other.m_wavelength);
    std::swap(m_alpha_i, other.m_alpha_i);
    std::swap(m_intensity, other.m_intensity);
    std::swap(m_specular_data, other.m_specular_data);
}

void SpecularSimulationElement::setSpecular(std::unique_ptr<SpecularData> specular_data)
{
    m_specular_data = std::move(specular_data);
}

