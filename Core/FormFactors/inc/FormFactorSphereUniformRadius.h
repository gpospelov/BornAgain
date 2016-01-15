// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorSphereUniformRadius.h
//! @brief     Defines class FormFactorSphereUniformRadius.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORSPHEREUNIFORMRADIUS_H_
#define FORMFACTORSPHEREUNIFORMRADIUS_H_

#include "MathFunctions.h"

#include "IFormFactor.h"
#include "FormFactorFullSphere.h"
#include <cassert>

//! @class FormFactorSphereUniformRadius
//! @ingroup formfactors
//! @brief Integrated full sphere form factor over a uniform distribution of radii.

class BA_CORE_API_ FormFactorSphereUniformRadius : public IFormFactorBorn
{
public:
    FormFactorSphereUniformRadius(double mean, double full_width);
    virtual FormFactorSphereUniformRadius *clone() const;
    virtual ~FormFactorSphereUniformRadius();

    virtual void accept(ISampleVisitor *visitor) const;

    virtual complex_t evaluate_for_q(const cvector_t& q) const;

protected:
    virtual bool check_initialization() const;
    virtual void init_parameters();

private:
    bool checkParameters() const;
    double m_mean; //!< This is the mean radius
    double m_full_width; //!< This is the full width of the radius distribution
};

#endif /* FORMFACTORSPHEREUNIFORMRADIUS_H_ */
