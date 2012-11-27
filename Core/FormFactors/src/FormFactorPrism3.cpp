#include "FormFactorPrism3.h"
#include "StochasticDiracDelta.h"

#include "MathFunctions.h"

FormFactorPrism3::FormFactorPrism3(double height, double half_side)
{
    setName("FormFactorPrism3");
    m_height = height;
    m_half_side = half_side;
    m_root3 = std::sqrt(3.0);
    init_parameters();
    //    mp_height = new StochasticDiracDelta<double>(height);
    //    mp_half_side = new StochasticDiracDelta<double>(half_side);
}

//FormFactorPrism3::FormFactorPrism3(StochasticParameter<double>* p_height,
//        StochasticParameter<double>* p_half_side)
//: mp_height(p_height)
//, mp_half_side(p_half_side)
//{
//    m_root3 = std::sqrt(3.0);
//}

FormFactorPrism3::~FormFactorPrism3()
{
//    delete mp_height;
//    delete mp_half_side;
}

/* ************************************************************************* */
// initialize pool parameters, i.e. register some of class members for later access via parameter pool
/* ************************************************************************* */
void FormFactorPrism3::init_parameters()
{
    getParameterPool()->clear();
    getParameterPool()->registerParameter("height", &m_height);
    getParameterPool()->registerParameter("half_side", &m_half_side);
}


FormFactorPrism3* FormFactorPrism3::clone() const
{
    FormFactorPrism3 *p_clone = new FormFactorPrism3(m_height, m_half_side );
    p_clone->setBinSizes(m_bin_qy, m_bin_qz);
    return p_clone;
}

complex_t FormFactorPrism3::evaluate_for_q(const cvector_t &q) const
{
    complex_t qz = q.z();
    double R = m_half_side;
    double H = m_height;

    complex_t qzH_half = qz*H/2.0;
    complex_t z_part = H*MathFunctions::Sinc(qzH_half)*std::exp(complex_t(0.0, 1.0)*qzH_half);

    complex_t xy_part = complex_t(0.0, 0.0);
    if (std::abs(q.x())==0.0 && std::abs(q.y())==0.0) {
        xy_part = m_root3*R*R;
    }
    else {
        complex_t r3qyR = m_root3*q.y()*R;
        complex_t expminiqyRdivr3 = std::exp(-complex_t(0.0, 1.0)*q.y()*R/m_root3);
        if (std::abs(q.x()*q.x()-3.0*q.y()*q.y())==0.0) {
            xy_part = complex_t(0.0, 1.0)*m_root3*expminiqyRdivr3*
                    (std::sin(r3qyR)-r3qyR*std::exp(complex_t(0.0, 1.0)*r3qyR))/q.x()/q.x();
        }
        else {
            complex_t qxR = q.x()*R;
            xy_part = std::exp(complex_t(0.0, 1.0)*r3qyR)-std::cos(qxR)-complex_t(0.0, 1.0)*r3qyR*
                    MathFunctions::Sinc(qxR);
            xy_part *= 2.0*m_root3*expminiqyRdivr3/(q.x()*q.x()-3.0*q.y()*q.y());
        }
    }

    return xy_part*z_part;
}


/* ************************************************************************* */
// print class
/* ************************************************************************* */
void FormFactorPrism3::print(std::ostream &ostr) const
{
    ISample::print(ostr);
//    ostr <<  " (height:"<<m_height << " half_side:"<<m_half_side << ")";
}

