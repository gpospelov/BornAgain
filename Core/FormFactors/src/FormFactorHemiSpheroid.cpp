#include "FormFactorHemiSpheroid.h"
#include "StochasticDiracDelta.h"
#include "MathFunctions.h"
#include "Numeric.h"
#include "Units.h"
#include "Exceptions.h"
#include <iostream>
#include "MemberFunctionIntegrator.h"

FormFactorHemiSpheroid::FormFactorHemiSpheroid(double radius, double width, double height)
{
    setName("FormFactorHemiSpheroid");
    m_radius = radius;
    m_width  = width;
    m_height = height;
    init_parameters();
}


FormFactorHemiSpheroid::~FormFactorHemiSpheroid()
{
}

/* ************************************************************************* */
// initialize pool parameters, i.e. register some of class members for later access via parameter pool
/* ************************************************************************* */
void FormFactorHemiSpheroid::init_parameters()
{
    getParameterPool()->clear();
    getParameterPool()->registerParameter("radius", &m_radius);
    getParameterPool()->registerParameter("width",  &m_width);
    getParameterPool()->registerParameter("height", &m_height);
}

FormFactorHemiSpheroid* FormFactorHemiSpheroid::clone() const
{
   FormFactorHemiSpheroid* ffSpheroid = new FormFactorHemiSpheroid(m_radius,  m_width, m_height);
   return ffSpheroid;
}


//********************Real Part of the Integral*********************************/
double FormFactorHemiSpheroid::evaluate_for_q_real() const

{
    double H = m_height;
    MemberFunctionIntegrator<FormFactorHemiSpheroid>::mem_function p_mf = &FormFactorHemiSpheroid::HemiSpheroidIntegralReal;
    MemberFunctionIntegrator<FormFactorHemiSpheroid> integrator(p_mf,this);
    double RealRadial = integrator.integrate(0, H, (void *)0);
    return RealRadial;
 }

 double FormFactorHemiSpheroid::HemiSpheroidIntegralReal(double Z, void* params) const
 {

    (void)params;
     double R = m_radius;
     double W = m_height;
     double H = m_height;


     complex_t qz = m_q.z();
     complex_t qx = m_q.x();
     complex_t qy = m_q.y();

     double Wz    =  W * std::sqrt(1-((Z*Z)/(H*H)));
     double Rz    =  R * std::sqrt(1-((Z*Z)/(H*H)));
     double gamma = (std::sqrt ((( qx*Rz)*(qx*Rz)) + ((qy*Wz)*(qy*Wz)))).real();
     double J1_gamma_div_gamma = std::abs(gamma) > Numeric::double_epsilon ? MathFunctions::Bessel_J1(std::abs(gamma))/gamma: 0.5;
     double exp_real = std::exp(complex_t(0.0, 1.0)*qz*Z).real();
     return  Rz *Wz * J1_gamma_div_gamma * exp_real;

 }


 //*********************************Imaginary Part***************************//
 complex_t FormFactorHemiSpheroid::evaluate_for_q_imag() const
{
    double H = m_height;
    MemberFunctionIntegrator<FormFactorHemiSpheroid>::mem_function p_mf = &FormFactorHemiSpheroid::HemiSpheroidIntegralImaginary;
    MemberFunctionIntegrator<FormFactorHemiSpheroid> integrator(p_mf,this);
    double ImaginaryRadial = integrator.integrate(0, H, (void *)0);
    return ImaginaryRadial;
 }
 double FormFactorHemiSpheroid::HemiSpheroidIntegralImaginary(double Z, void* params) const
 {
     (void)params;
      double R = m_radius;
      double W = m_height;
      double H = m_height;


       complex_t qx = m_q.x();
       complex_t qy = m_q.y();
       complex_t qz = m_q.z();

      double Wz    =  W * std::sqrt(1-((Z*Z)/(H*H)));
      double Rz    =  R * std::sqrt(1-((Z*Z)/(H*H)));
      double gamma = (std::sqrt ((( qx*Rz)*(qx*Rz)) + ((qy*Wz)*(qy*Wz)))).real();
      double J1_gamma_div_gamma = std::abs(gamma) > Numeric::double_epsilon ? MathFunctions::Bessel_J1(std::abs(gamma))/gamma: 0.5;
      double exp_imag = std::exp(complex_t(0.0,-1.0)*qz*Z).imag();
      return  Rz *Wz * J1_gamma_div_gamma * exp_imag;
    }


 //***************************Sum of Two Integrals*****************************//
 complex_t FormFactorHemiSpheroid::evaluate_for_q(const cvector_t &q) const

 {
     m_q = q;
     return 2.0* M_PI* complex_t(0.0, 1.0)*evaluate_for_q_imag() + evaluate_for_q_real();
 }

