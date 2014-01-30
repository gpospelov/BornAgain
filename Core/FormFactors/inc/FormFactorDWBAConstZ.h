// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorDWBAConstZ.h
//! @brief     Defines class FormFactorDWBAConstZ.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORDWBACONSTZ_H_
#define FORMFACTORDWBACONSTZ_H_

#include "FormFactorDWBA.h"

//! @class FormFactorDWBAConstZ
//! @ingroup formfactors_internal
//! @brief Calculates a DWBA formfactor for particles at fixed depth.

class BA_CORE_API_ FormFactorDWBAConstZ : public FormFactorDWBA
{
public:
    FormFactorDWBAConstZ(IFormFactor* p_form_factor, double depth=0.0);
    virtual ~FormFactorDWBAConstZ() {}
    virtual FormFactorDWBAConstZ *clone() const;
    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    virtual complex_t evaluate(const cvector_t& k_i,
            const Bin1DCVector& k_f_bin, const Bin1D &alpha_f_bin) const;
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

#endif /* FORMFACTORDWBACONSTZ_H_ */


