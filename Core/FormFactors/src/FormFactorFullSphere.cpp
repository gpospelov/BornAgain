#include "FormFactorFullSphere.h"
#include "StochasticDiracDelta.h"
#include "Numeric.h"

#include <cmath>

FormFactorFullSphere::FormFactorFullSphere(double radius)
{
    setName("FormFactorFullSphere");
    m_radius = radius;
    init_parameters();
//    mp_radius = new StochasticDiracDelta<double>(radius);
}

//FormFactorFullSphere::FormFactorFullSphere(StochasticParameter<double> *p_radius)
//    : mp_radius(p_radius)
//{
//}

FormFactorFullSphere::~FormFactorFullSphere()
{
//    delete mp_radius;
}

/* ************************************************************************* */
// initialize pool parameters, i.e. register some of class members for later access via parameter pool
/* ************************************************************************* */
void FormFactorFullSphere::init_parameters()
{
    getParameterPool()->clear();
    getParameterPool()->registerParameter("radius", &m_radius);
}


FormFactorFullSphere* FormFactorFullSphere::clone() const
{
    return new FormFactorFullSphere(m_radius);
//    return new FormFactorFullSphere(mp_radius->clone());
}

complex_t FormFactorFullSphere::evaluate_for_q(cvector_t q) const
{
//    double R = mp_radius->getCurrent();
    complex_t qz = q.z();
    double R = m_radius;

    complex_t iqzR = complex_t(0.0, 1.0)*qz*R;
    complex_t z_part = std::exp(iqzR);

    complex_t qR = std::sqrt( std::norm(q.x()) + std::norm(q.y()) + std::norm(qz) )*R;
    double volume = 4*M_PI*R*R*R/3;
    complex_t radial;
    if (std::abs(qR) < Numeric::double_epsilon) {
        radial = volume;
    }
    else {
        radial = 3*volume*(std::sin(qR) - qR*std::cos(qR))/(qR*qR*qR);
    }

    return radial*z_part;
}


/* ************************************************************************* */
// print class
/* ************************************************************************* */
void FormFactorFullSphere::print(std::ostream &ostr) const
{
    ISample::print(ostr);
//    ostr << " " << "(radius:"<<m_radius << ")";
}
