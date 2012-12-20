
#include "FormFactorSphere.h"
#include "StochasticDiracDelta.h"
#include "Numeric.h"
#include "MathFunctions.h"
#include <cmath>

FormFactorSphere::FormFactorSphere(double radius, double height)
{
    setName("FormFactorSphere");
    m_radius = radius;
    m_height = height;


    init_parameters();
//    mp_radius = new StochasticDiracDelta<double>(radius);
}

//FormFactorSphere::FormFactorSphere(StochasticParameter<double> *p_radius)
//    : mp_radius(p_radius)
//{
//}

FormFactorSphere::~FormFactorSphere()
{
//    delete mp_radius;
}

/* ************************************************************************* */
// initialize pool parameters, i.e. register some of class members for later access via parameter pool
/* ************************************************************************* */
void FormFactorSphere::init_parameters()
{
    getParameterPool()->clear();
    getParameterPool()->registerParameter("radius", &m_radius);
    getParameterPool()->registerParameter("height", &m_height);
   }


FormFactorSphere* FormFactorSphere::clone() const
{
    return new FormFactorSphere(m_radius, m_height);
//    return new FormFactorSphere(mp_radius->clone());
}

complex_t FormFactorSphere::evaluate_for_q(const cvector_t &q) const
{
////    double R = mp_radius->getCurrent();
//    complex_t qx = q.x();
//    complex_t qy = q.y();
//    complex_t qz = q.z();
//    double R = m_radius;
//    double H = m_height;
//    double Z = .4;
//
//    complex_t iqzZ  = complex_t(0.0, 1.0)*qz*Z;
//    complex_t z_part= std::exp(iqzZ);
////  complex_t iqz(H-R) = complex_t(0.0, 1.0)*qz*(H-R);
//    complex_t a_part = std::exp(iqz(H -R));
//
//
//
//    complex_t Rz     = pow((R*R-z*z), 1/2);
//    complex_t q_parallel = pow((qx*qx - qy*qy), 1/2);

//    complex_t qR = std::sqrt( std::norm(q.x()) + std::norm(q.y()) + std::norm(qz) )*R;
//    complex_t radial;
//    if (std::abs(qR) < Numeric::double_epsilon) {
//        radial = volume;
//    }
//    else {
//
//     /*
//     double zl = R-H;
//       double zu = R;
//       double rzl = pow((r*r - z*z), 1/2)
//
//               fzl= rzl;
//               fzu = rzu;
//
//            double fz = -H*(fzl+fzu)/2;
//
//         radial = exp abc _part 2.pi.x) J1(q_parallel * Rz)
//
//         // way1 (standard)
//         //radial = 3*volume*(std::sin(qR) - qR*std::cos(qR))/(qR*qR*qR);
//
//         // way2 (fast)
//
//
//        // way3 (experimental)
//        // complex_t xsin, xcos;
//        // MathFunctions::FastSinCos(qR, xsin, xcos);
//        // radial = 3*volume*(xsin - qR*xcos)/(qR*qR*qR);
//
//
//        */
//    }
//
//    return radial*z_part;

    (void)q;
    return complex_t(0.0, 0.0);

}


/* ************************************************************************* */
// print class
/* ************************************************************************* */
void FormFactorSphere::print(std::ostream &ostr) const
{
    ISample::print(ostr);
//    ostr << " " << "(radius:"<<m_radius << ")";
}


//for (zk=0;zk<=2;zk+0.01) {
//
//    k[zk]=zk
//}
