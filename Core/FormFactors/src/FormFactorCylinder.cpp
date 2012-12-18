#include "FormFactorCylinder.h"
#include "StochasticDiracDelta.h"

#include "MathFunctions.h"
#include "Numeric.h"

FormFactorCylinder::FormFactorCylinder(double height, double radius)
{
    setName("FormFactorCylinder");
    m_height = height;
    m_radius = radius;
    init_parameters();
    //    mp_height = new StochasticDiracDelta<double>(height);
    //    mp_radius = new StochasticDiracDelta<double>(radius);
}

//FormFactorCylinder::FormFactorCylinder(StochasticParameter<double> *p_height, StochasticParameter<double> *p_radius)
//    : mp_height(p_height)
//    , mp_radius(p_radius)
//{
//}

FormFactorCylinder::~FormFactorCylinder()
{
//    delete mp_height;
//    delete mp_radius;
}


/* ************************************************************************* */
// initialize pool parameters, i.e. register some of class members for later access via parameter pool
/* ************************************************************************* */
void FormFactorCylinder::init_parameters()
{
    getParameterPool()->clear();
    getParameterPool()->registerParameter("height", &m_height);
    getParameterPool()->registerParameter("radius", &m_radius);
}


FormFactorCylinder* FormFactorCylinder::clone() const
{
    FormFactorCylinder *p_clone = new FormFactorCylinder(m_height, m_radius);
    return p_clone;
}

complex_t FormFactorCylinder::evaluate_for_q(const cvector_t &q) const
{
    double R = m_radius;
    double H = m_height;

    complex_t qzH_half = q.z()*H/2.0;
    complex_t z_part = H*MathFunctions::Sinc(qzH_half)*std::exp(complex_t(0.0, 1.0)*qzH_half);

    complex_t qrR = q.magxy()*R;
    complex_t J1_qrR_div_qrR = std::abs(qrR) > Numeric::double_epsilon ? MathFunctions::Bessel_J1(std::abs(qrR))/qrR : 0.5;
    complex_t radial_part = 2*M_PI*R*R*J1_qrR_div_qrR;

    return radial_part*z_part;
}
/* ************************************************************************* */
// print class
/* ************************************************************************* */
void FormFactorCylinder::print(std::ostream &ostr) const
{
    ISample::print(ostr);
//    ostr << " (height:"<<m_height << " radius:"<<m_radius << ")";
}
