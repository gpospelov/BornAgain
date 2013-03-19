// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @copyright Forschungszentrum Jülich GmbH 2013
//             
//  Homepage:  apps.jcns.fz-juelich.de/BornAgain
//  License:   GNU General Public License v3 or higher (see COPYING)
//
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
//! @file      FormFactors/FormFactorFullSphere.h 
//! @brief     Defines class FormFactorFullSphere.
//
// ************************************************************************** //

#ifndef FORMFACTORFULLSPHERE_H_
#define FORMFACTORFULLSPHERE_H_

#include "IFormFactorBorn.h"
#include "IStochasticParameter.h"

//! ?

class FormFactorFullSphere : public IFormFactorBorn
{
public:
    FormFactorFullSphere(double radius);
    ~FormFactorFullSphere();
    virtual FormFactorFullSphere *clone() const;

    virtual int getNumberOfStochasticParameters() const { return 1; }

    //! return radius of sphere
    virtual double getRadius() const { return m_radius; }

    //! return diameter of sphere
    virtual double getHeight() const { return 2.0*m_radius; }

    virtual complex_t evaluate_for_q(const cvector_t &q) const;

protected:
    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();

private:
    double m_radius;
};

#endif /* FORMFACTORFULLSPHERE_H_ */
