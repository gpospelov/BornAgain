// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorCylinder.h
//! @brief     Defines class FormFactorCylinder.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORCYLINDER_H
#define FORMFACTORCYLINDER_H

#include "IFormFactorBorn.h"

//! Form factor of a cylinder.

class FormFactorCylinder : public IFormFactorBorn
{
 public:
    FormFactorCylinder(double height, double radius);
    ~FormFactorCylinder() {}
    virtual FormFactorCylinder *clone() const;

    virtual int getNumberOfStochasticParameters() const { return 2; }

    virtual double getHeight() const { return m_height; }
    virtual double getRadius() const { return m_radius; }

    virtual complex_t evaluate_for_q(const cvector_t& q) const;

 protected:
    virtual void init_parameters();

 private:
    double m_height;
    double m_radius;
};

#endif // FORMFACTORCYLINDER_H


