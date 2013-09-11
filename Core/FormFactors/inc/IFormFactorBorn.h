// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/IFormFactorBorn.h
//! @brief     Defines pure virtual interface class IFormFactorBorn.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IFORMFACTORBORN_H_
#define IFORMFACTORBORN_H_

#include "IFormFactor.h"

//! Pure virtual interface for Born form factors (only depending on q=ki-kf).

class BA_CORE_API_ IFormFactorBorn : public IFormFactor
{
 public:
    IFormFactorBorn() {}
    virtual ~IFormFactorBorn() {}
    virtual IFormFactorBorn *clone() const=0;

    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    virtual complex_t evaluate(const cvector_t& k_i,
            const Bin1DCVector& k_f_bin, Bin1D alpha_f_bin) const;

#ifndef GCCXML_SKIP_THIS
    virtual Eigen::Matrix2cd evaluatePol(const cvector_t& k_i,
            const Bin1DCVector& k_f1_bin, const Bin1DCVector& k_f2_bin,
            double alpha_i, Bin1D alpha_f_bin, Bin1D phi_f_bin) const;
#endif

    //! evaluate scattering amplitude for complex wavevector
    //! @param q  wavevector transfer \f$q\equiv k_i-k_f\f$
    virtual complex_t evaluate_for_q(const cvector_t& q) const=0;

    //! Returns volume.

    //! Default implementation: form factor at q=0.
    //! Overload this for more efficient implementation
    //! (or to avoid endless loop caused by big bin approximation).
    virtual double getVolume() const;

 protected:
    //! Returns radial part of scattering amplitude for large bins
    double bigRadialPart(const Bin1DCVector& q_bin) const;

    //! Returns z-part of scattering amplitude for large bins
    complex_t bigZPart(const Bin1DCVector& q_bin) const;

 private:
    //! determine if a large bin size approximation should be used
    bool useLargeBinApproximation(const Bin1DCVector& q_bin) const;

    //! approximate intensity that does not contain rapid oscillations
    double bigRadialIntegrand(double qR, void *params) const;

    //! calculates the integrated intensity along the z-direction
    double bigZPartIntegral(double qH2) const;
};

#endif /* IFORMFACTORBORN_H_ */


