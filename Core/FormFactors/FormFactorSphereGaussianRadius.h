// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorSphereGaussianRadius.h
//! @brief     Defines and implements class FormFactorSphereGaussianRadius.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORSPHEREGAUSSIANRADIUS_H_
#define FORMFACTORSPHEREGAUSSIANRADIUS_H_
#include "MathFunctions.h"

#include "IFormFactor.h"
#include "FormFactorFullSphere.h"
#include <cassert>

//! @class FormFactorSphereGaussianRadius
//! @ingroup formfactors
//! @brief The formfactor of sphere with gaussian radius distribution.

class BA_CORE_API_ FormFactorSphereGaussianRadius : public IFormFactorBorn
{
public:
    FormFactorSphereGaussianRadius(double mean, double sigma);
    virtual FormFactorSphereGaussianRadius *clone() const;
    virtual ~FormFactorSphereGaussianRadius();

    virtual void accept(ISampleVisitor *visitor) const;

    virtual double getRadius() const;

    virtual complex_t evaluate_for_q(const cvector_t q) const;

protected:
    virtual bool check_initialization() const;
    virtual void init_parameters();

private:
    double calculateMeanR3() const;

    double m_mean; //!< This is the mean radius
    double m_sigma;
    double m_mean_r3; //!< This is the radius that gives the mean volume
    FormFactorFullSphere *p_ff_sphere;
};

#endif /* FORMFACTORSPHEREGAUSSIANRADIUS_H_ */


