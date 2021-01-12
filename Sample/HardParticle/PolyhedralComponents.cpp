//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      Sample/HardParticle/PolyhedralComponents.cpp
//! @brief     Implements classes PolyhedralEdge, PolyhedralFace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/HardParticle/PolyhedralComponents.h"
#include "Base/Math/Functions.h"
#include "Base/Math/Precomputed.h"
#include <iomanip>
#include <stdexcept> // need overlooked by g++ 5.4

namespace {
const double eps = 2e-16;
constexpr auto ReciprocalFactorialArray = Math::generateReciprocalFactorialArray<171>();
} // namespace

#ifdef ALGORITHM_DIAGNOSTIC
void PolyhedralDiagnosis::reset() {
    order = 0; algo = 0; msg.clear();
};
std::string PolyhedralDiagnosis::message() const {
    std::string ret = "algo=" + std::to_string(algo) + ", order=" + std::to_string(order);
    if (!msg.empty())
        ret += ", msg:\n" + msg;
    return ret;
}
bool PolyhedralDiagnosis::operator==(const PolyhedralDiagnosis& other) const
{
    return order==other.order && algo==other.algo;
}
bool PolyhedralDiagnosis::operator!=(const PolyhedralDiagnosis& other) const
{
    return !(*this==other);
}
#endif


//  ************************************************************************************************
//  PolyhedralEdge implementation
//  ************************************************************************************************

PolyhedralEdge::PolyhedralEdge(kvector_t _Vlow, kvector_t _Vhig)
    : m_E((_Vhig - _Vlow) / 2), m_R((_Vhig + _Vlow) / 2)
{
    if (m_E.mag2() == 0)
        throw std::invalid_argument("At least one edge has zero length");
};

//! Returns sum_l=0^M/2 u^2l v^(M-2l) / (2l+1)!(M-2l)! - vperp^M/M!

complex_t PolyhedralEdge::contrib(int M, cvector_t qpa, complex_t qrperp) const
{
    complex_t u = qE(qpa);
    complex_t v2 = m_R.dot(qpa);
    complex_t v1 = qrperp;
    complex_t v = v2 + v1;
    // std::cout << std::scientific << std::showpos << std::setprecision(16) << "contrib: u=" << u
    //              << " v1=" << v1 << " v2=" << v2 << "\n";
    if (v == 0.) { // only 2l=M contributes
        if (M & 1) // M is odd
            return 0.;
        else
            return ReciprocalFactorialArray[M] * (pow(u, M) / (M + 1.) - pow(v1, M));
    }
    complex_t ret = 0;
    // the l=0 term, minus (qperp.R)^M, which cancels under the sum over E*contrib()
    if (v1 == 0.) {
        ret = ReciprocalFactorialArray[M] * pow(v2, M);
    } else if (v2 == 0.) {
        ; // leave ret=0
    } else {
        // binomial expansion
        for (int mm = 1; mm <= M; ++mm) {
            complex_t term = ReciprocalFactorialArray[mm] * ReciprocalFactorialArray[M - mm]
                             * pow(v2, mm) * pow(v1, M - mm);
            ret += term;
            // std::cout << "contrib mm=" << mm << " t=" << term << " s=" << ret << "\n";
        }
    }
    if (u == 0.)
        return ret;
    for (int l = 1; l <= M / 2; ++l) {
        complex_t term = ReciprocalFactorialArray[M - 2 * l] * ReciprocalFactorialArray[2 * l + 1]
                         * pow(u, 2 * l) * pow(v, M - 2 * l);
        ret += term;
        // std::cout << "contrib l=" << l << " t=" << term << " s=" << ret << "\n";
    }
    return ret;
}

//  ************************************************************************************************
//  PolyhedralFace implementation
//  ************************************************************************************************

double PolyhedralFace::qpa_limit_series = 3e-2;
int PolyhedralFace::n_limit_series = 20;

//! Static method, returns diameter of circle that contains all vertices.

double PolyhedralFace::diameter(const std::vector<kvector_t>& V)
{
    double diameterFace = 0;
    for (size_t j = 0; j < V.size(); ++j)
        for (size_t jj = j + 1; jj < V.size(); ++jj)
            diameterFace = std::max(diameterFace, (V[j] - V[jj]).mag());
    return diameterFace;
}

//! Sets internal variables for given vertex chain.

//! @param V oriented vertex list
//! @param _sym_S2 true if face has a perpedicular two-fold symmetry axis

PolyhedralFace::PolyhedralFace(const std::vector<kvector_t>& V, bool _sym_S2) : sym_S2(_sym_S2)
{
    size_t NV = V.size();
    if (!NV)
        throw std::logic_error("Face with no edges");
    if (NV < 3)
        throw std::logic_error("Face with less than three edges");

    // compute radius in 2d and 3d
    m_radius_2d = diameter(V) / 2;
    m_radius_3d = 0;
    for (const kvector_t& v : V)
        m_radius_3d = std::max(m_radius_3d, v.mag());

    // Initialize list of 'edges'.
    // Do not create an edge if two vertices are too close to each other.
    // TODO This is implemented in a somewhat sloppy way: we just skip an edge if it would
    //      be too short. This leaves tiny open edges. In a clean implementation, we
    //      rather should merge adjacent vertices before generating edges.
    for (size_t j = 0; j < NV; ++j) {
        size_t jj = (j + 1) % NV;
        if ((V[j] - V[jj]).mag() < 1e-14 * m_radius_2d)
            continue; // distance too short -> skip this edge
        edges.push_back(PolyhedralEdge(V[j], V[jj]));
    }
    size_t NE = edges.size();
    if (NE < 3)
        throw std::invalid_argument("Face has less than three non-vanishing edges");

    // compute n_k, rperp
    m_normal = kvector_t();
    for (size_t j = 0; j < NE; ++j) {
        size_t jj = (j + 1) % NE;
        kvector_t ee = edges[j].E().cross(edges[jj].E());
        if (ee.mag2() == 0) {
            throw std::logic_error("Two adjacent edges are parallel");
        }
        m_normal += ee.unit();
    }
    m_normal /= NE;
    m_rperp = 0;
    for (size_t j = 0; j < NV; ++j)
        m_rperp += V[j].dot(m_normal);
    m_rperp /= NV;
    // assert that the vertices lay in a plane
    for (size_t j = 1; j < NV; ++j)
        if (std::abs(V[j].dot(m_normal) - m_rperp) > 1e-14 * m_radius_3d)
            throw std::logic_error("Face is not planar");
    // compute m_area
    m_area = 0;
    for (size_t j = 0; j < NV; ++j) {
        size_t jj = (j + 1) % NV;
        m_area += m_normal.dot(V[j].cross(V[jj])) / 2;
    }
    // only now deal with inversion symmetry
    if (sym_S2) {
        if (NE & 1)
            throw std::logic_error("Odd #edges violates symmetry S2");
        NE /= 2;
        for (size_t j = 0; j < NE; ++j) {
            if (((edges[j].R() - m_rperp * m_normal) + (edges[j + NE].R() - m_rperp * m_normal))
                    .mag()
                > 1e-12 * m_radius_2d)
                throw std::logic_error("Edge centers violate symmetry S2");
            if ((edges[j].E() + edges[j + NE].E()).mag() > 1e-12 * m_radius_2d)
                throw std::logic_error("Edge vectors violate symmetry S2");
        }
        // keep only half of the egdes
        edges.erase(edges.begin() + NE, edges.end());
    }
}

//! Sets qperp and qpa according to argument q and to this polygon's normal.

void PolyhedralFace::decompose_q(cvector_t q, complex_t& qperp, cvector_t& qpa) const
{
    qperp = m_normal.dot(q);
    qpa = q - qperp * m_normal;
    // improve numeric accuracy:
    qpa -= m_normal.dot(qpa) * m_normal;
    if (qpa.mag() < eps * std::abs(qperp))
        qpa = cvector_t(0., 0., 0.);
}

//! Returns core contribution to f_n

complex_t PolyhedralFace::ff_n_core(int m, cvector_t qpa, complex_t qperp) const
{
    const cvector_t prevec = 2. * m_normal.cross(qpa); // complex conjugation not here but in .dot
    complex_t ret = 0;
    const complex_t qrperp = qperp * m_rperp;
    for (size_t i = 0; i < edges.size(); ++i) {
        const PolyhedralEdge& e = edges[i];
        const complex_t vfac = prevec.dot(e.E());
        const complex_t tmp = e.contrib(m + 1, qpa, qrperp);
        ret += vfac * tmp;
        //     std::cout << std::scientific << std::showpos << std::setprecision(16)
        //               << "DBX ff_n_core " << m << " " << vfac << " " << tmp
        //               << " term=" << vfac * tmp << " sum=" << ret << "\n";
    }
    return ret;
}

//! Returns contribution qn*f_n [of order q^(n+1)] from this face to the polyhedral form factor.

complex_t PolyhedralFace::ff_n(int n, cvector_t q) const
{
    complex_t qn = q.dot(m_normal); // conj(q)*normal (dot is antilinear in 'this' argument)
    if (std::abs(qn) < eps * q.mag())
        return 0.;
    complex_t qperp;
    cvector_t qpa;
    decompose_q(q, qperp, qpa);
    double qpa_mag2 = qpa.mag2();
    if (qpa_mag2 == 0.) {
        return qn * pow(qperp * m_rperp, n) * m_area * ReciprocalFactorialArray[n];
    } else if (sym_S2) {
        return qn * (ff_n_core(n, qpa, qperp) + ff_n_core(n, -qpa, qperp)) / qpa_mag2;
    } else {
        complex_t tmp = ff_n_core(n, qpa, qperp);
        // std::cout << "DBX ff_n " << n << " " << qn << " " << tmp << " " << qpa_mag2 << "\n";
        return qn * tmp / qpa_mag2;
    }
}

//! Returns sum of n>=1 terms of qpa expansion of 2d form factor

complex_t PolyhedralFace::expansion(complex_t fac_even, complex_t fac_odd, cvector_t qpa,
                                    double abslevel) const
{
#ifdef ALGORITHM_DIAGNOSTIC
    polyhedralDiagnosis.algo += 1;
#endif
    complex_t sum = 0;
    complex_t n_fac = I;
    int count_return_condition = 0;
    for (int n = 1; n < n_limit_series; ++n) {
#ifdef ALGORITHM_DIAGNOSTIC
        polyhedralDiagnosis.order = std::max(polyhedralDiagnosis.order, n);
#endif
        complex_t term = n_fac * (n & 1 ? fac_odd : fac_even) * ff_n_core(n, qpa, 0) / qpa.mag2();
        // std::cout << std::setprecision(16) << "    sum=" << sum << " +term=" << term << "\n";
        sum += term;
        if (std::abs(term) <= eps * std::abs(sum) || std::abs(sum) < eps * abslevel)
            ++count_return_condition;
        else
            count_return_condition = 0;
        if (count_return_condition > 2)
            return sum; // regular exit
        n_fac = mul_I(n_fac);
    }
    throw std::runtime_error("Series f(q_pa) not converged");
}

//! Returns core contribution to analytic 2d form factor.

complex_t PolyhedralFace::edge_sum_ff(cvector_t q, cvector_t qpa, bool sym_Ci) const
{
    cvector_t prevec = m_normal.cross(qpa); // complex conjugation will take place in .dot
    complex_t sum = 0;
    complex_t vfacsum = 0;
    for (size_t i = 0; i < edges.size(); ++i) {
        const PolyhedralEdge& e = edges[i];
        complex_t qE = e.qE(qpa);
        complex_t qR = e.qR(qpa);
        complex_t Rfac = sym_S2 ? sin(qR) : (sym_Ci ? cos(e.qR(q)) : exp_I(qR));
        complex_t vfac;
        if (sym_S2 || i < edges.size() - 1) {
            vfac = prevec.dot(e.E());
            vfacsum += vfac;
        } else {
            vfac = -vfacsum; // to improve numeric accuracy: qcE_J = - sum_{j=0}^{J-1} qcE_j
        }
        complex_t term = vfac * Math::sinc(qE) * Rfac;
        sum += term;
        //    std::cout << std::scientific << std::showpos << std::setprecision(16)
        //              << "    sum=" << sum << " term=" << term << " vf=" << vfac << " qE=" << qE
        //              << " qR=" << qR << " sinc=" << Math::sinc(qE) << " Rfac=" << Rfac << "\n";
    }
    return sum;
}

//! Returns the contribution ff(q) of this face to the polyhedral form factor.

complex_t PolyhedralFace::ff(cvector_t q, bool sym_Ci) const
{
    complex_t qperp;
    cvector_t qpa;
    decompose_q(q, qperp, qpa);
    double qpa_red = m_radius_2d * qpa.mag();
    complex_t qr_perp = qperp * m_rperp;
    complex_t ff0 = (sym_Ci ? 2. * I * sin(qr_perp) : exp_I(qr_perp)) * m_area;
    if (qpa_red == 0) {
        return ff0;
    } else if (qpa_red < qpa_limit_series && !sym_S2) {
        // summation of power series
        complex_t fac_even;
        complex_t fac_odd;
        if (sym_Ci) {
            fac_even = 2. * mul_I(sin(qr_perp));
            fac_odd = 2. * cos(qr_perp);
        } else {
            fac_even = exp_I(qr_perp);
            fac_odd = fac_even;
        }
        return ff0 + expansion(fac_even, fac_odd, qpa, std::abs(ff0));
    } else {
        // direct evaluation of analytic formula
        complex_t prefac;
        if (sym_S2)
            prefac = sym_Ci ? -8. * sin(qr_perp) : 4. * mul_I(exp_I(qr_perp));
        else
            prefac = sym_Ci ? 4. : 2. * exp_I(qr_perp);
        // std::cout << "       qrperp=" << qr_perp << " => prefac=" << prefac << "\n";
        return prefac * edge_sum_ff(q, qpa, sym_Ci) / mul_I(qpa.mag2());
    }
}

//! Two-dimensional form factor, for use in prism, from power series.

complex_t PolyhedralFace::ff_2D_expanded(cvector_t qpa) const
{
    return m_area + expansion(1., 1., qpa, std::abs(m_area));
}

//! Two-dimensional form factor, for use in prism, from sum over edge form factors.

complex_t PolyhedralFace::ff_2D_direct(cvector_t qpa) const
{
    return (sym_S2 ? 4. : 2. / I) * edge_sum_ff(qpa, qpa, false) / qpa.mag2();
}

//! Returns the two-dimensional form factor of this face, for use in a prism.

complex_t PolyhedralFace::ff_2D(cvector_t qpa) const
{
    if (std::abs(qpa.dot(m_normal)) > eps * qpa.mag())
        throw std::logic_error("ff_2D called with perpendicular q component");
    double qpa_red = m_radius_2d * qpa.mag();
    if (qpa_red == 0) {
        return m_area;
    } else if (qpa_red < qpa_limit_series && !sym_S2) {
        return ff_2D_expanded(qpa);
    } else {
        return ff_2D_direct(qpa);
    }
}

//! Throws if deviation from inversion symmetry is detected. Does not check vertices.

void PolyhedralFace::assert_Ci(const PolyhedralFace& other) const
{
    if (std::abs(m_rperp - other.m_rperp) > 1e-15 * (m_rperp + other.m_rperp))
        throw std::logic_error("Faces with different distance from origin violate symmetry Ci");
    if (std::abs(m_area - other.m_area) > 1e-15 * (m_area + other.m_area))
        throw std::logic_error("Faces with different areas violate symmetry Ci");
    if ((m_normal + other.m_normal).mag() > 1e-14)
        throw std::logic_error("Faces do not have opposite orientation, violating symmetry Ci");
}
