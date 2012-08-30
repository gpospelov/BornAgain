#include "FormFactorLorentz.h"
#include "StochasticDiracDelta.h"

#include "MathFunctions.h"
#include "Numeric.h"

FormFactorLorentz::FormFactorLorentz(double volume)
{
    setName("FormFactorLorentz");
    double R = std::pow(volume, 1.0/3.0);
    m_height = R;
    m_width = R;
    init_parameters();
}


FormFactorLorentz::FormFactorLorentz(double height, double width)
{
    setName("FormFactorLorentz");
    m_height = height;
    m_width = width;
    init_parameters();
    //    mp_height = new StochasticDiracDelta<double>(height);
    //    mp_width = new StochasticDiracDelta<double>(width);
}

//FormFactorLorentz::FormFactorLorentz(StochasticParameter<double> *p_height, StochasticParameter<double> *p_width)
//    : mp_height(p_height)
//    , mp_width(p_width)
//{
//}

FormFactorLorentz::~FormFactorLorentz()
{
//    delete mp_height;
//    delete mp_width;
}


/* ************************************************************************* */
// initialize pool parameters, i.e. register some of class members for later access via parameter pool
/* ************************************************************************* */
void FormFactorLorentz::init_parameters()
{
    getParameterPool()->clear();
    getParameterPool()->registerParameter("height", &m_height);
    getParameterPool()->registerParameter("width", &m_width);
}


FormFactorLorentz* FormFactorLorentz::clone() const
{
    return new FormFactorLorentz(m_height, m_width);
//    return new FormFactorLorentz(mp_height->clone(), mp_radius->clone());
}

complex_t FormFactorLorentz::evaluate_for_complex_qz(kvector_t q, complex_t qz) const
{
//    double R = mp_radius->getCurrent();
//    double H = mp_height->getCurrent();
    double R = m_width;
    double H = m_height;

    complex_t z_part = H/(1.0 + (H*qz/2.0)*(H*qz/2.0));

    double radial_part = R*R/(1.0 + (R*q.x()/2.0)*(R*q.x()/2.0))/(1.0 + (R*q.y()/2.0)*(R*q.y()/2.0));

    return radial_part*z_part;
}

complex_t FormFactorLorentz::evaluate_for_q(cvector_t q) const
{
//    double R = mp_radius->getCurrent();
//    double H = mp_height->getCurrent();
    double R = m_width;
    double H = m_height;

    complex_t z_part = H/(1.0 + (H*q.z()/2.0)*(H*q.z()/2.0));

    complex_t radial_part = R*R/(1.0 + (R*q.x()/2.0)*(R*q.x()/2.0))/(1.0 + (R*q.y()/2.0)*(R*q.y()/2.0));

    return radial_part*z_part;
}

/* ************************************************************************* */
// print class
/* ************************************************************************* */
void FormFactorLorentz::print(std::ostream &ostr) const
{
    ISample::print(ostr);
//    ostr << " (height:"<<m_height << " width:"<<m_width << ")";
}
