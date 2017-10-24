#include "MaterialUtils.h"
#include "PhysicalConstants.h"

using PhysConsts::m_n;
using PhysConsts::g_factor_n;
using PhysConsts::mu_N;
using PhysConsts::h_bar;
// The factor 1e-18 is here to have unit: 1/T*nm^-2
constexpr double magnetic_prefactor
    = (m_n * g_factor_n * mu_N / h_bar / h_bar)
      * 1e-18;

// Unit 2x2 matrix
const Eigen::Matrix2cd Unit_Matrix(Eigen::Matrix2cd::Identity());

// Imaginary unit
namespace {
const complex_t I(0,1);

// Pauli matrices
const Eigen::Matrix2cd Pauli_X((Eigen::Matrix2cd() << 0,  1,
                                                      1,  0).finished());
const Eigen::Matrix2cd Pauli_Y((Eigen::Matrix2cd() << 0, -I,
                                                      I,  0).finished());
const Eigen::Matrix2cd Pauli_Z((Eigen::Matrix2cd() << 1,  0,
                                                      0, -1).finished());
}

template <typename T>
Eigen::Matrix2cd MagnetizationCorrection(complex_t unit_factor, double magnetic_factor,
                                                      BasicVector3D<T> polarization){
    Eigen::Matrix2cd result = unit_factor * Unit_Matrix +
        magnetic_factor * (
            Pauli_X * polarization[0] +
            Pauli_Y * polarization[1] +
            Pauli_Z * polarization[2]
        );
    return result;
}
template Eigen::Matrix2cd MagnetizationCorrection(complex_t unit_factor, double magnetic_factor,
                                                  kvector_t polarization);
template Eigen::Matrix2cd MagnetizationCorrection(complex_t unit_factor, double magnetic_factor,
                                                  cvector_t polarization);

complex_t ScalarReducedPotential(complex_t n, kvector_t k, double n_ref)
{
    return n*n - n_ref*n_ref*k.sin2Theta();
}

Eigen::Matrix2cd PolarizedReducedPotential(complex_t n, kvector_t b_field,
                                           kvector_t k, double n_ref)
{
    Eigen::Matrix2cd result;
    double factor = magnetic_prefactor / k.mag2();
    complex_t unit_factor = ScalarReducedPotential(n, k, n_ref);
    return MagnetizationCorrection(unit_factor, factor, b_field);
}
