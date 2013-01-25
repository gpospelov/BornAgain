#include "FormFactorEllipsoid.h"
#include "MathFunctions.h"

FormFactorEllipsoid::FormFactorEllipsoid(double radius, double width , double height , double alpha)
{
    setName("FormFactorPyramid");
    m_height = height;
    m_radius = radius;
    m_width  = width;
    m_alpha = alpha;
    init_parameters();
}

FormFactorEllipsoid::~FormFactorEllipsoid()
{
}

FormFactorEllipsoid* FormFactorEllipsoid::clone() const
{
    return new FormFactorEllipsoid(m_radius, m_width, m_height, m_alpha );
}

complex_t FormFactorEllipsoid::evaluate_for_q(const cvector_t& q) const
{
    complex_t qxR = q.x()*m_radius;
    complex_t qyW = q.y()*m_width;
    complex_t qzHdiv2 = q.z()*m_height/2.0;

    complex_t phase_factor = std::exp(complex_t(0.0, 1.0)*qzHdiv2);

    complex_t gamma  = std::sqrt((qxR)*(qxR) + (qyW)*(qyW));
    complex_t J1_gamma_div_gamma = std::abs(gamma) > Numeric::double_epsilon ? MathFunctions::Bessel_J1(std::abs(gamma))/gamma: 0.5;

    return M_PI * getVolume() * phase_factor * J1_gamma_div_gamma *MathFunctions::Sinc(qzHdiv2);
}


  void FormFactorEllipsoid::init_parameters()
   {
       getParameterPool()->clear();
       getParameterPool()->registerParameter("radius", &m_radius);
       getParameterPool()->registerParameter("width",  &m_width);
       getParameterPool()->registerParameter("height", &m_height);
       getParameterPool()->registerParameter("alpha" , &m_alpha);
   }

   void FormFactorEllipsoid::print(std::ostream& ostr) const
   {
       ISample::print(ostr);
   }


