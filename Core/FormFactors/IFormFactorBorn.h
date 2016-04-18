// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/IFormFactorBorn.h
//! @brief     Defines pure virtual interface class IFormFactorBorn.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IFORMFACTORBORN_H_
#define IFORMFACTORBORN_H_

#include "IFormFactor.h"

//! @class IFormFactorBorn
//! @ingroup formfactors_internal
//! @brief Pure virtual interface for Born form factors.
//! Depends only on q=ki-kf.

class BA_CORE_API_ IFormFactorBorn : public IFormFactor
{
public:
    IFormFactorBorn() {}
    virtual ~IFormFactorBorn() {}
    virtual IFormFactorBorn *clone() const=0;

    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    virtual complex_t evaluate(const WavevectorInfo& wavevectors) const;

#ifndef GCCXML_SKIP_THIS
    virtual Eigen::Matrix2cd evaluatePol(const WavevectorInfo& wavevectors) const;
#endif

    //! evaluate scattering amplitude for complex wavevector
    //! @param q  wavevector transfer q=k_i-k_f
    virtual complex_t evaluate_for_q(const cvector_t q) const=0;

protected:
    //! check if object initialization was correct
    virtual bool check_initialization() const;
};

#endif /* IFORMFACTORBORN_H_ */


