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
    FormFactorLorentz *p_clone = new FormFactorLorentz(m_height, m_width);
    p_clone->setBinSizes(m_bin_qy, m_bin_qz);
    return p_clone;
}

complex_t FormFactorLorentz::evaluate_for_q(const cvector_t &q) const
{
    static const double sigma2 = 4.0*std::pow(M_PI, 2.0/3.0);
    double R = m_width;
    double H = m_height;

    complex_t xnorm = R*R*q.x()*q.x()/sigma2;
    complex_t ynorm = R*R*q.y()*q.y()/sigma2;
    complex_t znorm = H*H*q.z()*q.z()/sigma2;

    complex_t result = H*R*R/(1.0 + xnorm + ynorm + znorm);

    return result;
}

/* ************************************************************************* */
// print class
/* ************************************************************************* */
void FormFactorLorentz::print(std::ostream &ostr) const
{
    ISample::print(ostr);
//    ostr << " (height:"<<m_height << " width:"<<m_width << ")";
}
