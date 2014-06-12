// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/src/InterferenceFunction1DParaCrystal.cpp
//! @brief     Implements class InterferenceFunction1DParaCrystal.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "InterferenceFunction1DParaCrystal.h"
#include "MathFunctions.h"

InterferenceFunction1DParaCrystal::InterferenceFunction1DParaCrystal(
        double peak_distance, double damping_length)
    : m_peak_distance(peak_distance)
    , m_damping_length(damping_length)
    , mp_pdf(0)
    , m_use_damping_length(true)
    , m_kappa(0.0)
    , m_domain_size(0.0)
{
    setName("InterferenceFunction1DParaCrystal");
    if (m_damping_length==0.0) {
        m_use_damping_length = false;
    }
    init_parameters();
}

void InterferenceFunction1DParaCrystal::init_parameters()
{
    clearParameterPool();
    registerParameter("peak_distance", &m_peak_distance);
    registerParameter("damping_length", &m_damping_length);
    registerParameter("size_spacing_coupling", &m_kappa);
    registerParameter("domain_size", &m_domain_size);
}


InterferenceFunction1DParaCrystal *InterferenceFunction1DParaCrystal::clone() const {
    InterferenceFunction1DParaCrystal *result =
        new InterferenceFunction1DParaCrystal(
            m_peak_distance, m_damping_length);
    result->setName(getName());
    result->setDomainSize(getDomainSize());
    result->setKappa(m_kappa);
    if (mp_pdf) {
        result->setProbabilityDistribution(*mp_pdf);
    }
    return result;
}


double InterferenceFunction1DParaCrystal::evaluate(const cvector_t& q) const
{
    if (!mp_pdf) {
        throw NullPointerException("InterferenceFunction1DParaCrystal::"
                "evaluate() -> Error! Probability distribution for "
                "interference funtion not properly initialized");
    }
    double result=0.0;
    double qxr = q.x().real();
    double qyr = q.y().real();
    double qpar = std::sqrt(qxr*qxr + qyr*qyr);
    int n = (int)std::abs(m_domain_size/m_peak_distance);
    double nd = (double)n;
    complex_t fp = FTPDF(qpar);
    if (n<1) {
        result = ((1.0 + fp)/(1.0 - fp)).real();
    } else {
        if (std::abs(1.0-fp) < Numeric::double_epsilon ) {
            result = nd;
        }
        else if (std::abs(1.0-fp)*nd < 2e-4) {
            double intermediate = MathFunctions::geometricSum(fp, n).real()/nd;
            result = 1.0 + 2.0*intermediate;
        }
        else {
            complex_t tmp;
            double double_min = std::numeric_limits<double>::min();
            if (std::log(std::abs(fp)+double_min)*nd < std::log(double_min)) {
                tmp = complex_t(0.0, 0.0);
            } else {
            tmp = std::pow(fp,n-1);
            }
            double intermediate = ((1.0-1.0/nd)*fp/(1.0-fp)
                    - fp*fp*(1.0-tmp)/nd/(1.0-fp)/(1.0-fp)).real();
            result = 1.0 + 2.0*intermediate;
        }
    }
    return result;
}

complex_t InterferenceFunction1DParaCrystal::FTPDF(
    double qpar) const
{
    complex_t phase = std::exp(complex_t(0.0, 1.0)*qpar*m_peak_distance);
    double amplitude = mp_pdf->evaluate(qpar);
    complex_t result = phase*amplitude;
    if (m_use_damping_length) {
        result *= std::exp(-m_peak_distance/m_damping_length);
    }
    return result;
}

void InterferenceFunction1DParaCrystal::setProbabilityDistribution(
        const IFTDistribution1D &pdf)
{
    if (mp_pdf != &pdf) {
        delete mp_pdf;
        mp_pdf = pdf.clone();
    }
}

const IFTDistribution1D
    *InterferenceFunction1DParaCrystal::getPropabilityDistribution() const
{
    return mp_pdf;
}


