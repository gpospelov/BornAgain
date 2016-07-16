// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/FormFactors/IFormFactorBorn.h
//! @brief     Declares pure virtual interface class IFormFactorBorn.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IFORMFACTORBORN_H
#define IFORMFACTORBORN_H

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

#ifndef SWIG
    virtual Eigen::Matrix2cd evaluatePol(const WavevectorInfo& wavevectors) const;
#endif

    //! evaluate scattering amplitude for complex wavevector
    //! @param q  wavevector transfer q=k_i-k_f
    virtual complex_t evaluate_for_q(const cvector_t q) const=0;

protected:
    //! check if object initialization was correct
    virtual bool check_initialization() const;
};

#ifdef POLYHEDRAL_DIAGNOSTIC
//! Information about the latest form factor evaluation. Not thread-safe.
//! Used only by external test program.
class Diagnosis {
public:
    int maxOrder;
    int nExpandedFaces;
    int debmsg;
    bool request_convergence;
    bool operator!=( const Diagnosis& other ) const {
        return maxOrder!=other.maxOrder || nExpandedFaces!=other.nExpandedFaces; }
    friend std::ostream& operator<< (std::ostream& stream, const Diagnosis& diag) {
        return stream<<" ["<<diag.nExpandedFaces<<":"<<diag.maxOrder<<"]";
    }
};
#endif

#endif // IFORMFACTORBORN_H
