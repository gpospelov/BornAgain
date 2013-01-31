#include "FormFactorSphere.h"
#include "StochasticDiracDelta.h"
#include "Numeric.h"
#include "MathFunctions.h"
#include <cmath>
#include "MemberFunctionIntegrator.h"
#include "MemberComplexFunctionIntegrator.h"


FormFactorSphere::FormFactorSphere(double radius, double height)
    : m_radius(radius)
    , m_height(height)
{
    setName("FormFactorSphere");
    assert(m_height <= 2.*m_radius);
    init_parameters();

    MemberComplexFunctionIntegrator<FormFactorSphere>::mem_function p_mf = &FormFactorSphere::Integrand;
    m_integrator = new  MemberComplexFunctionIntegrator<FormFactorSphere>(p_mf, this);
}


FormFactorSphere::~FormFactorSphere()
{
    delete m_integrator;
}

/* ************************************************************************* */
// initialize pool parameters
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
}

complex_t FormFactorSphere::Integrand(double Z, void* params) const
{
    (void)params;
    double  Rz  = std::sqrt(  std::abs(m_radius*m_radius-Z*Z) );
    complex_t q_p = m_q.magxy(); // sqrt(x*x + y*y)
    return  Rz*Rz*MathFunctions::Bessel_C1(std::abs(q_p*Rz)) * std::exp(complex_t(0.0, 1.0)*m_q.z()*Z);
}

complex_t FormFactorSphere::evaluate_for_q(const cvector_t &q) const
{
    m_q = q;
    complex_t iqzR = complex_t(0.0, 1.0)*m_q.z()*(m_height-m_radius);

//    MemberComplexFunctionIntegrator<FormFactorSphere>::mem_function p_mf = &FormFactorSphere::SphereIntegrand;
//    MemberComplexFunctionIntegrator<FormFactorSphere> integrator(p_mf,this);

    complex_t integral = m_integrator->integrate(m_radius-m_height, m_radius);
    return 2.0*M_PI*integral*std::exp(iqzR);
}



// ----------------------------------------------------------------------------
// Another version
// ----------------------------------------------------------------------------
//double FormFactorSphere::evaluate_for_q_real() const
//{
//    MemberFunctionIntegrator<FormFactorSphere>::mem_function p_mf = &FormFactorSphere::SphereIntegralReal;
//    MemberFunctionIntegrator<FormFactorSphere> integrator(p_mf,this);
//    return integrator.integrate(m_radius-m_height, m_radius, (void *)0);
//}

//double FormFactorSphere::SphereIntegralReal(double Z, void* params) const
//{
//    (void)params;
//    return SphereIntegrand(Z).real();
//}

//double FormFactorSphere::evaluate_for_q_imag() const
//{
//    MemberFunctionIntegrator<FormFactorSphere>::mem_function p_mf = &FormFactorSphere::SphereIntegralImaginary;
//    MemberFunctionIntegrator<FormFactorSphere> integrator(p_mf,this);
//    return integrator.integrate(m_radius-m_height, m_radius, (void *)0);
//}

//double FormFactorSphere::SphereIntegralImaginary(double Z, void* params) const
//{
//    (void)params;
//    return SphereIntegrand(Z).imag();
//}

//complex_t FormFactorSphere::SphereIntegrand(double Z) const
//{
//    double  Rz  = std::sqrt(  std::abs(m_radius*m_radius-Z*Z) );
//    complex_t q_p = m_q.perp(); // sqrt(x*x + y*y)
//    return  Rz*Rz*MathFunctions::Bessel_C1(std::abs(q_p*Rz)) * std::exp(complex_t(0.0, 1.0)*m_q.z()*Z);
//}

//complex_t FormFactorSphere::evaluate_for_q(const cvector_t &q) const
//{
//    m_q = q;
//    complex_t iqzR = complex_t(0.0, 1.0)*m_q.z()*(m_height-m_radius);
//    return 2.0*M_PI*complex_t(evaluate_for_q_real(), evaluate_for_q_imag() )*std::exp(iqzR);
//}



// ----------------------------------------------------------------------------
// Another version (Ali)
// ----------------------------------------------------------------------------

//double FormFactorSphere::evaluate_for_q_real() const

//{
//    double H = m_height;
//    MemberFunctionIntegrator<FormFactorSphere>::mem_function p_mf = &FormFactorSphere::SphereIntegralReal;
//    MemberFunctionIntegrator<FormFactorSphere> integrator(p_mf,this);
//    double RealRadial = integrator.integrate(0, H, (void *)0);
//    return RealRadial;
// }


// double FormFactorSphere::SphereIntegralReal(double Z, void* params) const
// {
//     (void)params;
//      double R = m_radius;
//      complex_t qz = m_q.z();
//      complex_t qx = m_q.x();
//      complex_t qy = m_q.y();

//     double  Rz  = std::abs(std::sqrt((R*R)-(Z*Z)));
//     double qrRz = std::abs(std::sqrt((qx)*(qx) + (qy)*(qy))*Rz);
//     double  J1_qrRz_div_qrRz = std::abs(qrRz) > Numeric::double_epsilon ? MathFunctions::Bessel_J1(std::abs(qrRz))/qrRz : 0.5;
//     double exp_real = std::exp(complex_t(0.0, 1.0)*qz*Z).real();
//     return  2.0*M_PI*Rz*Rz*J1_qrRz_div_qrRz * exp_real;
// }


// //*********************************Imaginary Part***************************//
// complex_t FormFactorSphere::evaluate_for_q_imag() const
//{
//    double H = m_height;
//    MemberFunctionIntegrator<FormFactorSphere>::mem_function p_mf = &FormFactorSphere::SphereIntegralImaginary;
//    MemberFunctionIntegrator<FormFactorSphere> integrator(p_mf,this);
//    complex_t ImaginaryRadial = integrator.integrate(0, H, (void *)0);
//    return ImaginaryRadial;
// }
// double FormFactorSphere::SphereIntegralImaginary(double Z, void* params) const
// {
//     (void)params;
//      double R = m_radius;
//      complex_t qz = m_q.z();
//      complex_t qx = m_q.x();
//      complex_t qy = m_q.y();

//      double  Rz  = std::abs(std::sqrt((R*R)-(Z*Z)));
//     double qrRz = std::abs(std::sqrt((qx)*(qx) + (qy)*(qy))*Rz);
//     double  J1_qrRz_div_qrRz = std::abs(qrRz) > Numeric::double_epsilon ? MathFunctions::Bessel_J1(std::abs(qrRz))/qrRz : 0.5;
//     double exp_imag = std::exp(complex_t(0.0, 1.0)*qz*Z).imag();
//     return  2.0*M_PI*Rz*Rz*J1_qrRz_div_qrRz * exp_imag;
//    }


// //***************************Sum of Two Integrals*****************************//
// complex_t FormFactorSphere::evaluate_for_q(const cvector_t &q) const

// {
//     m_q = q;
//     double H = m_height;
//     double R = m_radius;
//     complex_t qz = m_q.z();
//     double iqzHR = std::exp(complex_t(0.0, 1.0)*qz*(H-R)).real();

//     return complex_t(0.0, 1.0)*evaluate_for_q_imag() + evaluate_for_q_real() * iqzHR;    //* a_part;
// }

