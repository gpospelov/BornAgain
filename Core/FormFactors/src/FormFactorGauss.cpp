#include "FormFactorGauss.h"
#include "StochasticDiracDelta.h"

#include "MathFunctions.h"
#include "Numeric.h"

FormFactorGauss::FormFactorGauss(double volume)
{
    setName("FormFactorGauss");
    double R = std::pow(volume, 1.0/3.0);
    m_height = R;
    m_width = R;
    init_parameters();
}


FormFactorGauss::FormFactorGauss(double height, double width)
{
    setName("FormFactorGauss");
    m_height = height;
    m_width = width;
    init_parameters();
    //    mp_height = new StochasticDiracDelta<double>(height);
    //    mp_width = new StochasticDiracDelta<double>(width);
}

//FormFactorGauss::FormFactorGauss(StochasticParameter<double> *p_height, StochasticParameter<double> *p_width)
//    : mp_height(p_height)
//    , mp_width(p_width)
//{
//}

FormFactorGauss::~FormFactorGauss()
{
//    delete mp_height;
//    delete mp_width;
}


/* ************************************************************************* */
// initialize pool parameters, i.e. register some of class members for later access via parameter pool
/* ************************************************************************* */
void FormFactorGauss::init_parameters()
{
    getParameterPool()->clear();
    getParameterPool()->registerParameter("height", &m_height);
    getParameterPool()->registerParameter("width", &m_width);
}


FormFactorGauss* FormFactorGauss::clone() const
{
    return new FormFactorGauss(m_height, m_width);
//    return new FormFactorGauss(mp_height->clone(), mp_radius->clone());
}

complex_t FormFactorGauss::evaluate_for_q(cvector_t q) const
{
//    double R = mp_width->getCurrent();
//    double H = mp_height->getCurrent();
    double R = m_width;
    double H = m_height;

//    complex_t z_phase = std::exp(complex_t(0.0, 1.0)*q.z()*H/2.0);
    complex_t z_part = H*std::exp(-q.z()*q.z()*H*H/8.0/M_PI);

    complex_t radial_part = R*R*std::exp(-(q.x()*q.x()+q.y()*q.y())*R*R/8.0/M_PI);

    return radial_part*z_part;
}

/* ************************************************************************* */
// print class
/* ************************************************************************* */
void FormFactorGauss::print(std::ostream &ostr) const
{
    ISample::print(ostr);
//    ostr << " (height:"<<m_height << " width:"<<m_width << ")";
}
