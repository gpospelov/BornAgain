//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      Sample/HardParticle/Polyhedron.cpp
//! @brief     Implements class Polyhedron.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

//! The mathematics implemented here is described in full detail in a paper
//! by Joachim Wuttke, entitled
//! "Numerically stable form factor of any polygon and polyhedron"

#include "Sample/HardParticle/Polyhedron.h"
#include "Sample/HardParticle/PolyhedralTopology.h"
#include "Base/Math/Functions.h"
#include <iomanip>
#include <iostream>
#include <stdexcept> // need overlooked by g++ 5.4
#include <boost/format.hpp>

namespace {
const double eps = 2e-16;
const double q_limit_series = 1e-2;
const int n_limit_series = 20;
} // namespace

Polyhedron::Polyhedron(const PolyhedralTopology& topology, double z_bottom,
                       const std::vector<kvector_t>& vertices)
{

    m_vertices.clear();
    for (const kvector_t& vertex : vertices)
        m_vertices.push_back(vertex - kvector_t{0, 0, z_bottom});

    try {
        m_z_bottom = z_bottom;
        m_sym_Ci = topology.symmetry_Ci;

        double diameter = 0;
        for (size_t j = 0; j < vertices.size(); ++j)
            for (size_t jj = j + 1; jj < vertices.size(); ++jj)
                diameter = std::max(diameter, (vertices[j] - vertices[jj]).mag());

        m_faces.clear();
        for (const PolygonalTopology& tf : topology.faces) {
            std::vector<kvector_t> corners; // of one face
            for (int i : tf.vertexIndices)
                corners.push_back(vertices[i]);
            if (PolyhedralFace::diameter(corners) <= 1e-14 * diameter)
                continue; // skip ridiculously small face
            m_faces.push_back(PolyhedralFace(corners, tf.symmetry_S2));
        }
        if (m_faces.size() < 4)
            throw std::logic_error("Less than four non-vanishing faces");

        m_radius = 0;
        m_volume = 0;
        for (const PolyhedralFace& Gk : m_faces) {
            m_radius = std::max(m_radius, Gk.radius3d());
            m_volume += Gk.pyramidalVolume();
        }
        if (m_sym_Ci) {
            if (m_faces.size() & 1)
                throw std::logic_error("Odd #faces violates symmetry Ci");
            size_t N = m_faces.size() / 2;
            // for this tests, m_faces must be in a specific order
            for (size_t k = 0; k < N; ++k)
                m_faces[k].assert_Ci(m_faces[2 * N - 1 - k]);
            // keep only half of the faces
            m_faces.erase(m_faces.begin() + N, m_faces.end());
        }
    } catch (std::invalid_argument& e) {
        throw std::invalid_argument(std::string("Invalid parameterization of Polyhedron: ")
                                    + e.what());
    } catch (std::logic_error& e) {
        throw std::logic_error(std::string("Bug in Polyhedron: ") + e.what()
                               + " [please report to the maintainers]");
    } catch (std::exception& e) {
        throw std::runtime_error(std::string("Unexpected exception in Polyhedron: ") + e.what()
                                 + " [please report to the maintainers]");
    }
}

Polyhedron::~Polyhedron() = default;

void Polyhedron::assert_platonic() const
{
    // just one test; one could do much more ...
    double pyramidal_volume = 0;
    for (const auto& Gk : m_faces)
        pyramidal_volume += Gk.pyramidalVolume();
    pyramidal_volume /= m_faces.size();
    for (const auto& Gk : m_faces)
        if (std::abs(Gk.pyramidalVolume() - pyramidal_volume) > 160 * eps * pyramidal_volume) {
            std::cerr << std::setprecision(16)
                      << "Bug: pyr_volume(this face)=" << Gk.pyramidalVolume()
                      << " vs pyr_volume(avge)=" << pyramidal_volume << "\n";
            throw std::runtime_error("Deviant pyramidal volume in Platonic Polyhedron");
        }
}

double Polyhedron::volume() const
{
    return m_volume;
}
double Polyhedron::radius() const
{
    return m_radius;
}

const std::vector<kvector_t>& Polyhedron::vertices()
{
    return m_vertices;
}

//! Returns the form factor F(q) of this polyhedron, respecting the offset z_bottom.

complex_t Polyhedron::evaluate_for_q(const cvector_t& q) const
{
    try {
        return exp_I(-m_z_bottom * q.z()) * evaluate_centered(q);
    } catch (std::logic_error& e) {
        throw std::logic_error(std::string("Bug in Polyhedron: ") + e.what()
                               + " [please report to the maintainers]");
    } catch (std::runtime_error& e) {
        throw std::runtime_error(std::string("Numeric computation failed in Polyhedron: ")
                                 + e.what() + " [please report to the maintainers]");
    } catch (std::exception& e) {
        throw std::runtime_error(std::string("Unexpected exception in Polyhedron: ") + e.what()
                                 + " [please report to the maintainers]");
    }
}

//! Returns the form factor F(q) of this polyhedron, with origin at z=0.

complex_t Polyhedron::evaluate_centered(const cvector_t& q) const
{
    double q_red = m_radius * q.mag();
#ifdef ALGORITHM_DIAGNOSTIC
    polyhedralDiagnosis.reset();
#endif
    if (q_red == 0) {
        return m_volume;
    } else if (q_red < q_limit_series) {
        // summation of power series
        complex_t sum = 0;
        complex_t n_fac = (m_sym_Ci ? -2 : -1) / q.mag2();
        int count_return_condition = 0;
        for (int n = 2; n < n_limit_series; ++n) {
            if (m_sym_Ci && n & 1)
                continue;
#ifdef ALGORITHM_DIAGNOSTIC
            polyhedralDiagnosis.order = std::max(polyhedralDiagnosis.order, n);
#endif
            complex_t term = 0;
            for (const PolyhedralFace& Gk : m_faces) {
                complex_t tmp = Gk.ff_n(n + 1, q);
                term += tmp;
            }
            term *= n_fac;
#ifdef ALGORITHM_DIAGNOSTIC
            polyhedralDiagnosis.msg +=
                boost::str(boost::format("  + term(n=%2i) = %23.17e+i*%23.17e\n")
                           % n % term.real() % term.imag());
#endif
            sum += term;
            if (std::abs(term) <= eps * std::abs(sum) || std::abs(sum) < eps * m_volume)
                ++count_return_condition;
            else
                count_return_condition = 0;
            if (count_return_condition > 2)
                return m_volume + sum; // regular exit
            n_fac = m_sym_Ci ? -n_fac : mul_I(n_fac);
        }
        throw std::runtime_error("Series F(q) not converged");
    } else {
        // direct evaluation of analytic formula (coefficients may involve series)
        complex_t sum = 0;
        for (const PolyhedralFace& Gk : m_faces) {
            complex_t qn = Gk.normalProjectionConj(q); // conj(q)*normal
            if (std::abs(qn) < eps * q.mag())
                continue;
            complex_t term = qn * Gk.ff(q, m_sym_Ci);
#ifdef ALGORITHM_DIAGNOSTIC
            polyhedralDiagnosis.msg +=
                boost::str(boost::format("  + face_ff = %23.17e+i*%23.17e\n")
                           % term.real() % term.imag());
#endif
            sum += term;
        }
#ifdef ALGORITHM_DIAGNOSTIC
        polyhedralDiagnosis.msg +=
            boost::str(boost::format(" -> raw sum = %23.17e+i*%23.17e; divisor = %23.17e\n")
                       % sum.real() % sum.imag() % q.mag2());
#endif
        return sum / I / q.mag2();
    }
}
