// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/src/InterferenceFunction2DParaCrystal.cpp
//! @brief     Implements class InterferenceFunction2DParaCrystal.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "InterferenceFunction2DParaCrystal.h"
#include "MathFunctions.h"
#include "MemberFunctionIntegrator.h"
#include "Exceptions.h"

#include <functional>

InterferenceFunction2DParaCrystal::InterferenceFunction2DParaCrystal(double length_1, double length_2, double alpha_lattice, double xi, double corr_length)
: m_alpha_lattice(alpha_lattice)
, m_xi(xi)
, m_integrate_xi(false)
, m_corr_length(corr_length)
, m_use_corr_length(true)
{
    m_lattice_lengths[0] = length_1;
    m_lattice_lengths[1] = length_2;
    m_pdfs[0] = 0;
    m_pdfs[1] = 0;
    m_domain_sizes[0] = 0.0;
    m_domain_sizes[1] = 0.0;
    setName("InterferenceFunction2DParaCrystal");
    if (m_corr_length==0.0) {
        m_use_corr_length = false;
    }
    init_parameters();
}

InterferenceFunction2DParaCrystal::~InterferenceFunction2DParaCrystal()
{
    for (size_t i=0; i<2; ++i) {
        if (m_pdfs[i]) delete m_pdfs[i];
    }
}

void InterferenceFunction2DParaCrystal::setProbabilityDistributions(
        const IFTDistribution2D& pdf_1, const IFTDistribution2D& pdf_2)
{
    for (size_t i=0; i<2; ++i) {
        if (m_pdfs[i]) delete m_pdfs[i];
    }
    m_pdfs[0] = pdf_1.clone();
    m_pdfs[1] = pdf_2.clone();
}

double InterferenceFunction2DParaCrystal::evaluate(const cvector_t& q) const
{
    m_qx = q.x().real();
    m_qy = q.y().real();
    double result;
    if (m_integrate_xi) {
        MemberFunctionIntegrator<InterferenceFunction2DParaCrystal>::mem_function p_member_function =& InterferenceFunction2DParaCrystal::interferenceForXi;
        MemberFunctionIntegrator<InterferenceFunction2DParaCrystal> integrator(p_member_function, this);
        result = integrator.integrate(0.0, M_PI, (void*)0)/M_PI;
   }
    else {
        result = interferenceForXi(m_xi, (void*)0);
    }
    return result;
}

std::string InterferenceFunction2DParaCrystal::addParametersToExternalPool(std::string path,
        ParameterPool* external_pool, int copy_number) const
{
    // add own parameters
    std::string  new_path = IParameterized::addParametersToExternalPool(path, external_pool, copy_number);

    // add parameters of the probability density functions
    if (m_pdfs[0]) {
        m_pdfs[0]->addParametersToExternalPool(new_path, external_pool, 0);
    }
    if (m_pdfs[1]) {
        m_pdfs[1]->addParametersToExternalPool(new_path, external_pool, 1);
    }
    return new_path;
}

InterferenceFunction2DParaCrystal* InterferenceFunction2DParaCrystal::createSquare(
        double peak_distance, double corr_length, double domain_size_1, double domain_size_2)
{
    InterferenceFunction2DParaCrystal *p_new = new InterferenceFunction2DParaCrystal(peak_distance, peak_distance, M_PI/2.0, 0.0, corr_length);
    p_new->setDomainSizes(domain_size_1, domain_size_2);
    p_new->setIntegrationOverXi(true);
    return p_new;
}

InterferenceFunction2DParaCrystal* InterferenceFunction2DParaCrystal::createHexagonal(
        double peak_distance, double corr_length, double domain_size_1, double domain_size_2)
{
    InterferenceFunction2DParaCrystal *p_new = new InterferenceFunction2DParaCrystal(peak_distance, peak_distance, 2*M_PI/3.0, 0.0, corr_length);
    p_new->setDomainSizes(domain_size_1, domain_size_2);
    p_new->setIntegrationOverXi(true);
    return p_new;
}

void InterferenceFunction2DParaCrystal::transformToPrincipalAxes(double qx,
        double qy, double gamma, double delta, double& q_pa_1, double& q_pa_2) const
{
    q_pa_1 = qx*std::cos(gamma) + qy*std::sin(gamma);
    q_pa_2 = qx*std::cos(gamma+delta) + qy*std::sin(gamma+delta);
}

void InterferenceFunction2DParaCrystal::init_parameters()
{
    getParameterPool()->clear();
    getParameterPool()->registerParameter("lattice_length_1", &m_lattice_lengths[0]);
    getParameterPool()->registerParameter("lattice_length_2", &m_lattice_lengths[1]);
    getParameterPool()->registerParameter("lattice_angle", &m_alpha_lattice);
    getParameterPool()->registerParameter("lattice_orientation", &m_xi);
    getParameterPool()->registerParameter("corr_length", &m_corr_length);
    getParameterPool()->registerParameter("domain_size_1", &m_domain_sizes[0]);
    getParameterPool()->registerParameter("domain_size_2", &m_domain_sizes[1]);
}

double InterferenceFunction2DParaCrystal::interferenceForXi(double xi, void *params) const
{
    (void)params;
    double result = interference1D(m_qx, m_qy, xi, 0)*interference1D(m_qx, m_qy, xi + m_alpha_lattice, 1);
    return result;
}

double InterferenceFunction2DParaCrystal::interference1D(double qx, double qy, double xi, size_t index) const
{
    if (index > 1) {
        throw OutOfBoundsException("Index of interference function probability must be < 2");
    }
    if (!m_pdfs[0] || !m_pdfs[1]) {
        throw NullPointerException("Probability distributions for interference funtion not properly initialized");
    }
    double result;
    int n = (int)std::abs(m_domain_sizes[index]/m_lattice_lengths[index]);
    double nd = (double)n;
    complex_t fp = FTPDF(qx, qy, xi, index);
    if (n<1) {
        result = ((1.0 + fp)/(1.0 - fp)).real();
    } else {
        if (std::abs(1.0-fp) < Numeric::double_epsilon) {
            result = nd;
        } else {
            complex_t tmp;
            double double_min = std::numeric_limits<double>::min();
            if (std::log(std::abs(fp)+double_min)*nd < std::log(double_min)) {
                tmp = complex_t(0.0, 0.0);
            } else {
                tmp = std::pow(fp,n-1);
            }
            double intermediate = ((1.0-1.0/nd)*fp/(1.0-fp) - fp*fp*(1.0-tmp)/nd/(1.0-fp)/(1.0-fp)).real();
            result = 1.0 + 2.0*intermediate;
        }
    }
    return result;
}

complex_t InterferenceFunction2DParaCrystal::FTPDF(double qx, double qy, double xi, size_t index) const
{
    double qa = qx*m_lattice_lengths[index]*std::cos(xi) +
        qy*m_lattice_lengths[index]*std::sin(xi);
    complex_t phase = std::exp(complex_t(0.0, 1.0)*qa);
    // transform q to principal axes:
    double qp1, qp2;
    double gamma = xi + m_pdfs[index]->getGamma();
    double delta = m_pdfs[index]->getDelta();
    transformToPrincipalAxes(qx, qy, gamma, delta, qp1, qp2);
    double amplitude = m_pdfs[index]->evaluate(qp1, qp2);
    complex_t result = phase*amplitude;
    if (m_use_corr_length) {
        result *= std::exp(-m_lattice_lengths[index]/m_corr_length);
    }
    return result;
}


