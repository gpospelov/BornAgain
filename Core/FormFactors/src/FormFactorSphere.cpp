#include "FormFactorSphere.h"
#include "StochasticDiracDelta.h"
#include "Numeric.h"
#include "MathFunctions.h"
#include <cmath>
#include "MemberFunctionIntegrator.h"

FormFactorSphere::FormFactorSphere(double radius, double height)
{
    setName("FormFactorSphere");
    m_radius = radius;
    m_height = height,
    init_parameters();
}


FormFactorSphere::~FormFactorSphere()
{
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
   FormFactorSphere* ffSphere = new FormFactorSphere(m_radius, m_height);
   return ffSphere;
}


//********************Real Part of the Integral*********************************//
double FormFactorSphere::evaluate_for_q_real() const

{
    double H = m_height;
    MemberFunctionIntegrator<FormFactorSphere>::mem_function p_mf = &FormFactorSphere::SphereIntegralReal;
    MemberFunctionIntegrator<FormFactorSphere> integrator(p_mf,this);
    double RealRadial = integrator.integrate(0, H, (void *)0);
    return RealRadial;
 }


 double FormFactorSphere::SphereIntegralReal(double Z, void* params) const
 {
     (void)params;
      double R = m_radius;
      complex_t qz = m_q.z();
      complex_t qx = m_q.x();
      complex_t qy = m_q.y();

     double  Rz  = std::abs(std::sqrt((R*R)-(Z*Z)));
     double qrRz = std::abs(std::sqrt((qx)*(qx) + (qy)*(qy))*Rz);
     double  J1_qrRz_div_qrRz = std::abs(qrRz) > Numeric::double_epsilon ? MathFunctions::Bessel_J1(std::abs(qrRz))/qrRz : 0.5;
     double exp_real = std::exp(complex_t(0.0, 1.0)*qz*Z).real();
     return  2.0*M_PI*Rz*Rz*J1_qrRz_div_qrRz * exp_real;
 }


 //*********************************Imaginary Part***************************//
 complex_t FormFactorSphere::evaluate_for_q_imag() const
{
    double H = m_height;
    MemberFunctionIntegrator<FormFactorSphere>::mem_function p_mf = &FormFactorSphere::SphereIntegralImaginary;
    MemberFunctionIntegrator<FormFactorSphere> integrator(p_mf,this);
    complex_t ImaginaryRadial = integrator.integrate(0, H, (void *)0);
    return ImaginaryRadial;
 }
 double FormFactorSphere::SphereIntegralImaginary(double Z, void* params) const
 {
     (void)params;
      double R = m_radius;
      complex_t qz = m_q.z();
      complex_t qx = m_q.x();
      complex_t qy = m_q.y();

      double  Rz  = std::abs(std::sqrt((R*R)-(Z*Z)));
     double qrRz = std::abs(std::sqrt((qx)*(qx) + (qy)*(qy))*Rz);
     double  J1_qrRz_div_qrRz = std::abs(qrRz) > Numeric::double_epsilon ? MathFunctions::Bessel_J1(std::abs(qrRz))/qrRz : 0.5;
     double exp_imag = std::exp(complex_t(0.0, 1.0)*qz*Z).imag();
     return  2.0*M_PI*Rz*Rz*J1_qrRz_div_qrRz * exp_imag;
    }


 //***************************Sum of Two Integrals*****************************//
 complex_t FormFactorSphere::evaluate_for_q(const cvector_t &q) const

 {
     m_q = q;
     double H = m_height;
     double R = m_radius;
     complex_t qz = m_q.z();
     double iqzHR = std::exp(complex_t(0.0, 1.0)*qz*(H-R)).real();

     return complex_t(0.0, 1.0)*evaluate_for_q_imag() + evaluate_for_q_real() * iqzHR;    //* a_part;
 }



    void FormFactorSphere::print(std::ostream &ostr) const
    {
        ISample::print(ostr);
        //     ostr << " (height:"<< m_height << " radius:"<<m_radius << " " << "alpha: " << m_alpha << ")";
    }

