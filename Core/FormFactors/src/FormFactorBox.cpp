#include "FormFactorBox.h"
#include "MathFunctions.h"

FormFactorBox::FormFactorBox(double radius, double width, double height)

 :m_radius(radius)
 ,m_width(width)
 ,m_height(height)
{
}

FormFactorBox::~FormFactorBox()
{
}

FormFactorBox* FormFactorBox::clone() const
{
    return new FormFactorBox(m_radius, m_width, m_height );
}

complex_t FormFactorBox::evaluate_for_q(const cvector_t& q) const
{
    complex_t qxR = q.x()*m_radius;
    complex_t qyW = q.y()*m_width;
    complex_t qzHdiv2 = q.z()*m_height/2.0;

    complex_t phase_factor = std::exp(complex_t(0.0, 1.0)*qzHdiv2);
       return getVolume() *phase_factor*MathFunctions::Sinc(qxR)*MathFunctions::Sinc(qyW)
                          *MathFunctions::Sinc(qzHdiv2);
   }



  void FormFactorBox::init_parameters()
   {
       getParameterPool()->clear();
       getParameterPool()->registerParameter("radius", &m_radius);
       getParameterPool()->registerParameter( "width",  &m_width);
       getParameterPool()->registerParameter("height", &m_height);

   }

   void FormFactorBox::print(std::ostream& ostr) const
   {
       ISample::print(ostr);
   }

