#include "InterferenceFunction2DParaCrystal.h"
#include "MathFunctions.h"

#include <functional>

double wrapFunctionForGSL(double xi, void* p_unary_function)
{
    std::binder1st<std::const_mem_fun1_t<double, InterferenceFunction2DParaCrystal, double> > *p_f =
            (std::binder1st<std::const_mem_fun1_t<double, InterferenceFunction2DParaCrystal, double> > *)p_unary_function;
    return (*p_f)(xi);
}

InterferenceFunction2DParaCrystal::InterferenceFunction2DParaCrystal(double peak_distance, double alpha_lattice, double width, double corr_length)
: m_peak_distance(peak_distance)
, m_alpha_lattice(alpha_lattice)
, m_width(width)
, m_corr_length(corr_length)
, m_use_corr_length(true)
, m_domain_size_1(0.0)
, m_domain_size_2(0.0)
{
    setName("InterferenceFunction2DParaCrystal");
    if (m_corr_length==0.0) {
        m_use_corr_length = false;
    }
    init_parameters();
}

double InterferenceFunction2DParaCrystal::evaluate(const cvector_t &q) const
{
    double qxr = q.x().real();
    double qyr = q.y().real();
    m_qpar = std::sqrt(qxr*qxr + qyr*qyr);
    std::binder1st<std::const_mem_fun1_t<double, InterferenceFunction2DParaCrystal, double> > f_base = std::bind1st(std::mem_fun(&InterferenceFunction2DParaCrystal::interferenceForXi), this);
    gsl_function f;
    f.function = &wrapFunctionForGSL;
    f.params = &f_base;
    double result = MathFunctions::Integrate1D(&f, 0.0, M_PI)/M_PI;
    return result;
}

void InterferenceFunction2DParaCrystal::init_parameters()
{
    getParameterPool()->clear();
    getParameterPool()->registerParameter("peak_distance", &m_peak_distance);
    getParameterPool()->registerParameter("width", &m_width);
    getParameterPool()->registerParameter("corr_length", &m_corr_length);
}


double InterferenceFunction2DParaCrystal::interferenceForXi(double xi) const
{
    double result = interference1D(m_qpar, xi, m_domain_size_1)*interference1D(m_qpar, xi + m_alpha_lattice, m_domain_size_2);
    return result;
}

double InterferenceFunction2DParaCrystal::interference1D(double qpar,
        double xi, double domain_size) const
{
    double result;
    int n = (int)std::abs(domain_size/m_peak_distance);
    double nd = (double)n;
    complex_t fp = FTCauchyDistribution(qpar, xi);
    if (n<1) {
        result = ((1.0 + fp)/(1.0 - fp)).real();
    }
    else {
        if (std::abs(1.0-fp) < Numeric::double_epsilon) {
            result = nd;
        }
        else {
            complex_t tmp;
            if (std::log(std::abs(fp)+Numeric::double_min)*nd < std::log(Numeric::double_min)) {
                tmp = complex_t(0.0, 0.0);
            }
            else {
                tmp = std::pow(fp,n-1);
            }
            // TODO: remove factor 2.0 in second term
            double intermediate = ((1.0-1.0/nd)*fp/(1.0-fp) - fp*fp*(1.0-tmp)/nd/(1.0-fp)/(1.0-fp)).real();
            result = 1.0 + 2.0*intermediate;
        }
    }
    return result;
}

complex_t InterferenceFunction2DParaCrystal::FTCauchyDistribution(double qpar, double xi) const
{
    complex_t phase = std::exp(complex_t(0.0, 1.0)*qpar*m_peak_distance*std::cos(xi));
    double amplitude = std::pow(1.0+qpar*qpar*m_width*m_width, -1.5);
    complex_t result = phase*amplitude;
    if (m_use_corr_length) {
        result *= std::exp(-m_peak_distance/m_corr_length);
    }
    return result;
}

