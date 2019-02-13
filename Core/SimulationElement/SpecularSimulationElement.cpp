#include "SpecularSimulationElement.h"
#include "IKzComputation.h"
#include "Layer.h"
#include "MultiLayer.h"

SpecularSimulationElement::SpecularSimulationElement(double kz, double, double)
    : m_intensity(0.0)
    , m_calculation_flag(true)
    , m_kz_computation([kz](const MultiLayer& sample) {
          return KzComputation::computeKzFromSLDs(sample, kz);
      })
{}

SpecularSimulationElement::SpecularSimulationElement(double wavelength, double, double alpha,
                                                     double)
    : m_intensity(0.0)
    , m_calculation_flag(true)
    , m_kz_computation(
          [k = vecOfLambdaAlphaPhi(wavelength, alpha, /*phi =*/0.0)](const MultiLayer& sample) {
              return KzComputation::computeKzFromRefIndeces(sample, k);
          })
{
}

SpecularSimulationElement::SpecularSimulationElement(const SpecularSimulationElement& other)
    : m_polarization(other.m_polarization)
    , m_intensity(other.m_intensity)
    , m_calculation_flag(other.m_calculation_flag)
    , m_kz_computation(other.m_kz_computation)
{
}

SpecularSimulationElement::SpecularSimulationElement(SpecularSimulationElement&& other) noexcept
    : m_polarization(std::move(other.m_polarization))
    , m_intensity(other.m_intensity)
    , m_calculation_flag(other.m_calculation_flag)
    , m_kz_computation(std::move(other.m_kz_computation))
{
}

SpecularSimulationElement::~SpecularSimulationElement() = default;

SpecularSimulationElement& SpecularSimulationElement::
operator=(const SpecularSimulationElement& other)
{
    if (this != &other) {
        SpecularSimulationElement tmp(other);
        tmp.swapContent(*this);
    }
    return *this;
}

std::vector<complex_t> SpecularSimulationElement::produceKz(const MultiLayer& sample)
{
    return m_kz_computation(sample);
}

void SpecularSimulationElement::swapContent(SpecularSimulationElement &other)
{
    m_polarization.swapContent(other.m_polarization);
    std::swap(m_intensity, other.m_intensity);
    std::swap(m_calculation_flag, other.m_calculation_flag);
    m_kz_computation.swap(other.m_kz_computation);
}
