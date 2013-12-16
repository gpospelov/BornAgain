// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorDWBAPolConstZ.h
//! @brief     Defines class FormFactorDWBAPolConstZ.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORDWBAPOLCONSTZ_H_
#define FORMFACTORDWBAPOLCONSTZ_H_

#include "FormFactorDWBAPol.h"

//! @class FormFactorDWBAPolConstZ
//! @ingroup ff_internals
//! @brief Calculates a polarized DWBA formfactor for particles at fixed depth.

class BA_CORE_API_ FormFactorDWBAPolConstZ : public FormFactorDWBAPol
{
public:
    FormFactorDWBAPolConstZ(IFormFactor *p_formfactor, double depth=0.0);
    virtual ~FormFactorDWBAPolConstZ();

    virtual FormFactorDWBAPolConstZ *clone() const;

    //! calls the ISampleVisitor's visit method
    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    //! Calculates and returns a polarized form factor calculation in DWBA
    virtual Eigen::Matrix2cd evaluatePol(const cvector_t& k_i,
            const Bin1DCVector& k_f_bin, Bin1D alpha_f, Bin1D phi_f) const;

protected:
    double m_depth;

private:
    inline complex_t getDepthPhase(const complex_t& q_z) const
    {
        complex_t exponent = -complex_t(0.0,1.0)*q_z*m_depth;
                             // Minus sign for depth (m_depth > 0)
        return std::exp(exponent);
    }
};


#endif /* FORMFACTORDWBAPOLCONSTZ_H_ */
