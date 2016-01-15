// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorztruncatedCube.cpp
//! @brief     Implements class FormFactorTruncatedCube.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorTruncatedCube.h"
#include "BornAgainNamespace.h"
#include "FormFactorBox.h"
#include "MathFunctions.h"

using namespace  BornAgain;

FormFactorTruncatedCube::FormFactorTruncatedCube(
   double length, double removed_length)
    : m_length(length)
    , m_removed_length(removed_length)
{
    setName(FFTruncatedCubeType);
    check_initialization();
    init_parameters();
}

void FormFactorTruncatedCube::init_parameters()
{
    clearParameterPool();
    registerParameter(Length, &m_length);
    registerParameter(RemovedLength, &m_removed_length);
}

FormFactorTruncatedCube* FormFactorTruncatedCube::clone() const
{
    return new FormFactorTruncatedCube(m_length, m_removed_length);
}

void FormFactorTruncatedCube::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}

double FormFactorTruncatedCube::getRadius() const
{
    return m_length/2.0;
}

bool FormFactorTruncatedCube::check_initialization() const
{
    bool result(true);
    if(m_removed_length > 0.5*m_length) {
        std::ostringstream ostr;
        ostr << "::FormFactorTruncatedCube() -> Error in class initialization ";
        ostr << "with parameters 'length':" << m_length;
        ostr << " 'removed_length':" << m_removed_length << "\n\n";
        ostr << "Check for removed_length <= 0.5*length failed.";
        throw Exceptions::ClassInitializationException(ostr.str());
    }
    return result;
}

complex_t FormFactorTruncatedCube::evaluate_for_q(const cvector_t& q) const
{
    FormFactorBox fffull(m_length, m_length, m_length);
    complex_t ffcube = fffull.evaluate_for_q(q);
    const complex_t im(0.0,1.0);

    complex_t qz = q.z();
    complex_t qy = q.y();
    complex_t qx = q.x();
    cvector_t rotatq1 = q;
    cvector_t rotatq2(qy, -qx, qz);
    cvector_t rotatq3(-qx, -qy, qz);
    cvector_t rotatq4(-qy, qx, qz);
    cvector_t rotatq5(qx, qy, -qz);
    cvector_t rotatq6(qy, -qx, -qz);
    cvector_t rotatq7(-qx, -qy, -qz);
    cvector_t rotatq8(-qy, qx, -qz);

    complex_t ffE1 = ffVertex(rotatq1);
    complex_t ffE2 = ffVertex(rotatq2);
    complex_t ffE3 = ffVertex(rotatq3);
    complex_t ffE4 = ffVertex(rotatq4);
    complex_t ffE5 = ffVertex(rotatq5);
    complex_t ffE6 = ffVertex(rotatq6);
    complex_t ffE7 = ffVertex(rotatq7);
    complex_t ffE8 = ffVertex(rotatq8);

    complex_t result = ffcube - (ffE1 + ffE2 + ffE3 + ffE4)
                              - std::exp(im*qz*m_length)*(ffE5 + ffE6 + ffE7 + ffE8);

    return result;
}

bool compareModulus(complex_t a, complex_t b) {
    return (std::abs(a) < std::abs(b));
}

complex_t FormFactorTruncatedCube::ffVertex(const cvector_t& q) const
{
    double L = m_length;
    double t = m_removed_length;
    const complex_t im(0.,1.);
    complex_t a = q.x();
    complex_t b = q.y();
    complex_t c = -q.z();

    complex_t prefactor = std::exp(im*L*(a+b)/2.0);
    std::vector<complex_t> qvector(3);
    qvector[0] = a;
    qvector[1] = b;
    qvector[2] = c;
    std::sort(qvector.begin(), qvector.end(), compareModulus);

    return prefactor*ffVertexSymmetric(t, qvector[0], qvector[1], qvector[2]);
}

// Version of the vertex form factor which is symmetric in a,b,c
// Expects the arguments (a,b,c) to be ordered by their absolute value: |a|<=|b|<=|c|
complex_t FormFactorTruncatedCube::ffVertexSymmetric(double t, complex_t a, complex_t b,
                                                     complex_t c) const
{
    const complex_t im(0.,1.);
    if (std::norm(a*t) <= Numeric::double_epsilon) {
        if (std::norm(b*t) <= Numeric::double_epsilon) {
            if (std::norm(c*t) <= Numeric::double_epsilon) {
                return std::pow(t, 3)/6.0;
            }
            return -im*(std::exp(-im*c*t) - (1.0 - im*c*t - c*c*t*t/2.0))/(c*c*c);
        }
        if (std::norm((b-c)*t) <= Numeric::double_epsilon) {
            return -im*(std::exp(-im*c*t)*(-2.0-im*c*t) + 2.0 - im*c*t)/(c*c*c);
        }
        complex_t numerator = -im * ( c*c*std::exp(-im*b*t) - b*b*std::exp(-im*c*t)
                                    + b*b - c*c -im*t*b*c*(b-c) );
        complex_t denominator = b*b*c*c*(b-c);
        return numerator/denominator;
    }
    if (std::norm((a-b)*t) <= Numeric::double_epsilon) {
        if (std::norm((b-c)*t) <= Numeric::double_epsilon) {
            return im*(1.0 - std::exp(-im*b*t)*(1.0 + im*b*t - b*b*t*t/2.0))/std::pow(b,3);
        } else {
            return ffVertexDiagonal(t, a, c);
        }
    } else if (std::norm((b-c)*t) <= Numeric::double_epsilon) {
        return ffVertexDiagonal(t, b, a);
    }
    complex_t t1 = 1.0;
    complex_t t2 = -b*c*std::exp(-im*a*t)/((a-b)*(a-c));
    complex_t t3 = -a*c*std::exp(-im*b*t)/((b-a)*(b-c));
    complex_t t4 = -a*b*std::exp(-im*c*t)/((c-a)*(c-b));
    return im*(t1+t2+t3+t4)/(a*b*c);
}

// Version of the vertex form factor that treats the case where two q components are
// equal; they will be passed as the 'a' parameter
complex_t FormFactorTruncatedCube::ffVertexDiagonal(double t, complex_t a, complex_t b) const
{
    const complex_t im(0.,1.);
    complex_t prefactor = im/(a*a*b*std::pow(a-b, 2));
    complex_t t1 = (a-b)*(a-b);
    complex_t t2 = -a*a*std::exp(-im*b*t);
    complex_t t3 = std::exp(-im*a*t)*(2.0*a*b - b*b + im*a*b*(a-b)*t);
    return prefactor*(t1 + t2 + t3);
}

