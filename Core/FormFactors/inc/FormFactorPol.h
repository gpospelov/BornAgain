// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorPol.h
//! @brief     Defines class FormFactorPol.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORPOL_H_
#define FORMFACTORPOL_H_

#include "IFormFactorDecorator.h"
#include "LayerSpecularInfo.h"

#ifndef GCCXML_SKIP_THIS
#include <Eigen/Core>
#endif

//! Evaluates a polarized form factor (which is a 2x2 matrix)

class BA_CORE_API_ FormFactorPol : public IFormFactor
{
public:
    FormFactorPol() {}
    virtual ~FormFactorPol();

    virtual FormFactorPol *clone() const=0;

    // Scalar evaluate throws exception
    virtual complex_t evaluate(const cvector_t& k_i,
            const Bin1DCVector& k_f_bin, double alpha_i, double alpha_f) const;

#ifndef GCCXML_SKIP_THIS
    //! Calculates and returns a polarized form factor calculation in DWBA
    virtual Eigen::Matrix2cd evaluatePol(const cvector_t& k_i,
            const Bin1DCVector& k_f1_bin, const Bin1DCVector& k_f2_bin,
            double alpha_i, double alpha_f, double phi_f) const=0;
#endif
};

#endif /* FORMFACTORPOL_H_ */
