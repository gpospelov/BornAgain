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

    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    virtual int getNumberOfStochasticParameters() const;
    virtual bool isDistributedFormFactor() const { return true; }
    virtual void createDistributedFormFactors(
        std::vector<IFormFactor*>& form_factors,
        std::vector<double>& probabilities, size_t nbr_samples) const;

    virtual double getHeight() const { return p_ff_sphere->getHeight(); }

    virtual complex_t evaluate_for_q(const cvector_t& q) const;

protected:
    virtual void init_parameters();

private:
    double calculateMeanR3() const;

    double m_mean; //!< This is the mean radius
    double m_sigma;
    double m_mean_r3; //!< This is the radius that gives the mean volume
    FormFactorFullSphere *p_ff_sphere;
};

#endif /* FORMFACTORSPHEREGAUSSIANRADIUS_H_ */


