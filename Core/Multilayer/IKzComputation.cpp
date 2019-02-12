#include "IKzComputation.h"
#include "Layer.h"
#include "MultiLayer.h"
#include "Units.h"

namespace
{
complex_t normalizedSLD(const Material& material);

// use small imaginary value if passed argument is very small
complex_t checkForUnderflow(complex_t val);
} // namespace

IKzComputation::~IKzComputation() = default;

std::vector<complex_t> ReducedKzComputation::compute(const MultiLayer& sample, kvector_t k)
{
    const size_t N = sample.numberOfLayers();
    const double n_ref = sample.layer(0)->material()->refractiveIndex(2 * M_PI / k.mag()).real();
    const double k_base = k.mag() * (k.z() > 0.0 ? -1 : 1);

    std::vector<complex_t> kz(N);
    // Calculate refraction angle, expressed as k_z, for each layer.
    complex_t rad = sample.layer(0)->scalarReducedPotential(k, n_ref);
    kz[0] = k_base * std::sqrt(rad);
    for (size_t i = 1; i < N; ++i) {
        rad = checkForUnderflow(sample.layer(i)->scalarReducedPotential(k, n_ref));
        kz[i] = k_base * std::sqrt(rad);
    }
    return kz;
}

KzComputation::KzComputation(kvector_t k) : m_k(k) {}

std::vector<complex_t> KzComputation::compute(const MultiLayer& sample) const
{
    const size_t N = sample.numberOfLayers();
    const double kz_val = m_k.z();
    const double k_sign = kz_val > 0.0 ? -1 : 1;
    const double k2 = m_k.mag2();
    const double kz2 = kz_val * kz_val;
    const double wl = 2 * M_PI / std::sqrt(k2);
    const complex_t n2_ref = sample.layer(0)->material()->refractiveIndex2(wl);

    std::vector<complex_t> kz(N);
    kz[0] = -kz_val;
    for (size_t i = 1; i < N; ++i) {
        const complex_t n2_norm = sample.layer(i)->material()->refractiveIndex2(wl) - n2_ref;
        kz[i] = k_sign * std::sqrt(checkForUnderflow(k2 * n2_norm + kz2));
    }
    return kz;
}

KzComputation* KzComputation::clone() const
{
    return new KzComputation(m_k);
}

KzFromSLDComputation::KzFromSLDComputation(double kz) : m_kz(kz) {}

std::vector<complex_t> KzFromSLDComputation::compute(const MultiLayer& sample) const
{
    const size_t N = sample.numberOfLayers();
    const double k_sign = m_kz > 0.0 ? -1 : 1;
    std::vector<complex_t> kz(N);

    complex_t kz2_base = m_kz * m_kz + normalizedSLD(*sample.layer(0)->material());
    kz[0] = -m_kz;
    // Calculate refraction angle, expressed as k_z, for each layer.
    for (size_t i = 1; i < N; ++i) {
        complex_t kz2 = checkForUnderflow(kz2_base - normalizedSLD(*sample.layer(i)->material()));
        kz[i] = k_sign * std::sqrt(kz2);
    }
    return kz;
}

KzFromSLDComputation *KzFromSLDComputation::clone() const
{
    return new KzFromSLDComputation(m_kz);
}

namespace
{
complex_t normalizedSLD(const Material& material)
{
    if (material.typeID() != MATERIAL_TYPES::MaterialBySLD)
        throw std::runtime_error("Error in normalizedSLD: passed material has wrong type");

    complex_t sld = std::conj(material.materialData()) / (Units::angstrom * Units::angstrom);
    sld *= 4.0 * M_PI;
    return sld;
}

complex_t checkForUnderflow(complex_t val)
{
    return std::norm(val) < 1e-80 ? complex_t(0.0, 1e-40) : val;
}
} // namespace
