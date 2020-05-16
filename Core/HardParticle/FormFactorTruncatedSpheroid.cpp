// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorTruncatedSpheroid.cpp
//! @brief     Implements class FormFactorTruncatedSpheroid.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "FormFactorTruncatedSpheroid.h"
#include "BornAgainNamespace.h"
#include "Exceptions.h"
#include "MathConstants.h"
#include "MathFunctions.h"
#include "RealParameter.h"
#include "TruncatedEllipsoid.h"
#include <limits>

//! Constructor of a spheroidal dome.
//! @param radius: radius of the truncated spheroid in nanometers
//! @param height: height of the truncated spheroid in nanometers
//! @param height_flattening: ratio of the height of the corresponding full spheroid to its diameter
//! @param dh: length of cup truncated from the top
FormFactorTruncatedSpheroid::FormFactorTruncatedSpheroid(double radius, double height,
                                                         double height_flattening, double dh)
    : m_radius(radius), m_height(height), m_height_flattening(height_flattening), m_dh(dh)
{
    setName(BornAgain::FFTruncatedSpheroidType);
    check_initialization();
    registerParameter(BornAgain::Radius, &m_radius).setUnit(BornAgain::UnitsNm).setNonnegative();
    registerParameter(BornAgain::Height, &m_height).setUnit(BornAgain::UnitsNm).setNonnegative();
    registerParameter(BornAgain::HeightFlattening, &m_height_flattening).setNonnegative();
    registerParameter(BornAgain::DeltaHeight, &m_dh).setUnit(BornAgain::UnitsNm).setNonnegative();
    onChange();
}

bool FormFactorTruncatedSpheroid::check_initialization() const
{
    bool result(true);
    if (m_height > 2. * m_radius * m_height_flattening || m_dh > m_height) {
        std::ostringstream ostr;
        ostr << "::FormFactorTruncatedSpheroid() -> Error in class initialization with parameters ";
        ostr << " radius:" << m_radius;
        ostr << " height:" << m_height;
        ostr << " height_flattening:" << m_height_flattening << "\n\n";
        ostr << "Check for 'height <= 2.*radius*height_flattening' failed.";
        throw Exceptions::ClassInitializationException(ostr.str());
    }
    return result;
}

//! Integrand for complex form factor.
complex_t FormFactorTruncatedSpheroid::Integrand(double Z) const
{
    double R = m_radius;
    double fp = m_height_flattening;

    double Rz = std::sqrt(R * R - Z * Z / (fp * fp));
    complex_t qrRz = std::sqrt(m_q.x() * m_q.x() + m_q.y() * m_q.y()) * Rz;
    complex_t J1_qrRz_div_qrRz = MathFunctions::Bessel_J1c(qrRz);

    return Rz * Rz * J1_qrRz_div_qrRz * std::exp(complex_t(0.0, 1.0) * m_q.z() * Z);
}

complex_t FormFactorTruncatedSpheroid::evaluate_for_q(cvector_t q) const
{
    double H = m_height;
    double R = m_radius;
    double fp = m_height_flattening;
    m_q = q;

    if (std::abs(m_q.mag()) <= std::numeric_limits<double>::epsilon())
        return M_PI / 3. / fp * (H * H * (3. * R - H / fp) - m_dh * m_dh * (3. * R - m_dh / fp));
    complex_t z_part = std::exp(complex_t(0.0, 1.0) * m_q.z() * (H - fp * R));
    return M_TWOPI * z_part * m_integrator.integrate(
            [&](double Z){return Integrand(Z);}, fp * R - H, fp * R - m_dh);
}

IFormFactor* FormFactorTruncatedSpheroid::sliceFormFactor(ZLimits limits, const IRotation& rot,
                                                          kvector_t translation) const
{
    double height = m_height - m_dh;
    auto effects = computeSlicingEffects(limits, translation, height);
    FormFactorTruncatedSpheroid slicedff(m_radius, height - effects.dz_bottom, m_height_flattening,
                                         effects.dz_top + m_dh);
    return CreateTransformedFormFactor(slicedff, rot, effects.position);
}

void FormFactorTruncatedSpheroid::onChange()
{
    mP_shape.reset(
        new TruncatedEllipsoid(m_radius, m_radius, m_height_flattening * m_radius, m_height, m_dh));
}
