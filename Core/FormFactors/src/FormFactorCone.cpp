#include "FormFactorCone.h"
#include "StochasticDiracDelta.h"
#include "MathFunctions.h"
#include "Numeric.h"
#include "Units.h"
#include "Exceptions.h"
#include <iostream>
#include "MemberFunctionIntegrator.h"

FormFactorCone::FormFactorCone(double radius,double height,double alpha)
{
    setName("FormFactorCone");
    m_radius = radius;
    m_height = height;
    m_alpha = alpha;
    init_parameters();
}


FormFactorCone::~FormFactorCone()
{
}

/* ************************************************************************* */
// initialize pool parameters, i.e. register some of class members for later access via parameter pool
/* ************************************************************************* */
void FormFactorCone::init_parameters()
{
    getParameterPool()->clear();
    getParameterPool()->registerParameter("radius", &m_radius);
    getParameterPool()->registerParameter("height", &m_height);
    getParameterPool()->registerParameter("alpha",  &m_alpha);
}


FormFactorCone* FormFactorCone::clone() const
{
   FormFactorCone* ffCone = new FormFactorCone(m_radius, m_height, m_alpha);
   return ffCone;
}


//********************Real Part of the Integral*********************************//
double FormFactorCone::evaluate_for_q_real() const

{
    double H = m_height;
    MemberFunctionIntegrator<FormFactorCone>::mem_function p_mf = &FormFactorCone::ConeIntegralReal;
    MemberFunctionIntegrator<FormFactorCone> integrator(p_mf,this);
    double RealRadial = integrator.integrate(0, H, (void *)0);
    return RealRadial;
 }


 double FormFactorCone::ConeIntegralReal(double Z, void* params) const
 {
    (void)params;
    complex_t qz = m_q.z();
    complex_t qx = m_q.x();
    complex_t qy = m_q.y();
    double R = m_radius;
    double tan_alpha = std::tan(m_alpha);
    double Rz  = R-(Z/tan_alpha);
    double qrRz = std::abs(std::sqrt((qx)*(qx) + (qy)*(qy))*Rz);
    double J1_qrRz_div_qrRz = std::abs(qrRz) > Numeric::double_epsilon ? MathFunctions::Bessel_J1(std::abs(qrRz))/qrRz : 0.5;
    double exp_real = std::exp(complex_t(0.0, 1.0)*qz*Z).real();
    return 2.0 * M_PI *Rz*Rz * J1_qrRz_div_qrRz * exp_real;
      }


 //*********************************Imaginary Part***************************//
 complex_t FormFactorCone::evaluate_for_q_imag() const
{
    double H = m_height;
    MemberFunctionIntegrator<FormFactorCone>::mem_function p_mf = &FormFactorCone::ConeIntegralImaginary;
    MemberFunctionIntegrator<FormFactorCone> integrator(p_mf,this);
    complex_t ImaginaryRadial = integrator.integrate(0, H, (void *)0);
    return ImaginaryRadial;
 }
 double FormFactorCone::ConeIntegralImaginary(double Z, void* params) const
 {
    (void)params;
    complex_t qz = m_q.z();
    complex_t qx = m_q.x();
    complex_t qy = m_q.y();

    double R = m_radius;
    double tan_alpha = std::tan(m_alpha);
    double Rz  = R-(Z/tan_alpha);
    double qrRz = std::abs(std::sqrt((qx)*(qx) + (qy)*(qy))*Rz);
    double J1_qrRz_div_qrRz = std::abs(qrRz) > Numeric::double_epsilon ? MathFunctions::Bessel_J1(std::abs(qrRz))/qrRz : 0.5;
    double exp_imag = std::exp(complex_t(0.0, 1.0)*qz*Z).imag();
    return 2.0 * M_PI *Rz*Rz * J1_qrRz_div_qrRz * exp_imag;
    }


 //***************************Sum of Two Integrals*****************************//
 complex_t FormFactorCone::evaluate_for_q(const cvector_t &q) const

 {
     m_q = q;
     return complex_t(0.0, 1.0)*evaluate_for_q_imag() + evaluate_for_q_real();
 }



