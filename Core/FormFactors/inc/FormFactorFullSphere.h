// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorFullSphere.h
//! @brief     Defines class FormFactorFullSphere.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORFULLSPHERE_H_
#define FORMFACTORFULLSPHERE_H_

#include "IFormFactorBorn.h"

//! @ingroup formfactors
//! @class FormFactorFullSphere
//! @brief The formfactor of a sphere.
class BA_CORE_API_ FormFactorFullSphere : public IFormFactorBorn
{
public:
    //! @brief Full Sphere constructor
    //! @param radius of Sphere
    FormFactorFullSphere(double radius);

    virtual FormFactorFullSphere *clone() const;

    virtual void accept(ISampleVisitor *visitor) const;

    //! Returns radius of sphere
    virtual double getRadius() const { return m_radius; }
    void setRadius(double radius) { m_radius = radius; }

    virtual complex_t evaluate_for_q(const cvector_t& q) const;

protected:
    virtual bool check_initialization() const;
    virtual void init_parameters();

private:
    double m_radius;
};

#endif /* FORMFACTORFULLSPHERE_H_ */


