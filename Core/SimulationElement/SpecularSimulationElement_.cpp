#include "SpecularSimulationElement_.h"
#include "IKzComputation.h"
#include "Layer.h"
#include "MultiLayer.h"

SpecularSimulationElement_::SpecularSimulationElement_(double kz, double, double)
    : m_intensity(0.0)
    , m_calculation_flag(true)
    , m_kz_computation(std::make_unique<KzFromSLDComputation>(kz))
{}

SpecularSimulationElement_::SpecularSimulationElement_(double wavelength, double, double alpha,
                                                       double)
    : m_intensity(0.0)
    , m_calculation_flag(true)
    , m_kz_computation(
          std::make_unique<KzComputation>(vecOfLambdaAlphaPhi(wavelength, alpha, /*phi = */ 0.0)))
{
}

SpecularSimulationElement_::SpecularSimulationElement_(const SpecularSimulationElement_& other)
    : m_polarization(other.m_polarization)
    , m_intensity(other.m_intensity)
    , m_calculation_flag(other.m_calculation_flag)
    , m_kz_computation(other.m_kz_computation->clone())
{
}

SpecularSimulationElement_::SpecularSimulationElement_(SpecularSimulationElement_&& other) noexcept
    : m_polarization(std::move(other.m_polarization))
    , m_intensity(other.m_intensity)
    , m_calculation_flag(other.m_calculation_flag)
    , m_kz_computation(std::move(other.m_kz_computation))
{
}

SpecularSimulationElement_::~SpecularSimulationElement_() = default;

SpecularSimulationElement_& SpecularSimulationElement_::
operator=(const SpecularSimulationElement_& other)
{
    if (this != &other) {
        SpecularSimulationElement_ tmp(other);
        tmp.swapContent(*this);
    }
    return *this;
}

std::vector<complex_t> SpecularSimulationElement_::produceKz(const MultiLayer& sample)
{
    return m_kz_computation->compute(sample);
}

void SpecularSimulationElement_::swapContent(SpecularSimulationElement_ &other)
{
    m_polarization.swapContent(other.m_polarization);
    std::swap(m_intensity, other.m_intensity);
    std::swap(m_calculation_flag, other.m_calculation_flag);
    m_kz_computation.swap(other.m_kz_computation);
}
