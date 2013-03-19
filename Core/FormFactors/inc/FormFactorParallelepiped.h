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
//! @file      FormFactors/FormFactorParallelepiped.h 
//! @brief     Defines class FormFactorParallelepiped.
//
// ************************************************************************** //

#ifndef FORMFACTORPARALLELEPIPED_H_
#define FORMFACTORPARALLELEPIPED_H_

#include "IFormFactorBorn.h"
#include "IStochasticParameter.h"

//! Form factor of a parallelepiped.

class FormFactorParallelepiped : public IFormFactorBorn
{
public:
    FormFactorParallelepiped(double height, double radius);
    ~FormFactorParallelepiped();
    virtual FormFactorParallelepiped *clone() const;

    virtual int getNumberOfStochasticParameters() const { return 2; }

    //! return radius of parallelepiped
    double getRadius() const { return m_radius; }

    virtual double getVolume() const {
        return 4.0*m_height*m_radius*m_radius;
    }

    virtual double getHeight() const { return m_height; }

    virtual complex_t evaluate_for_q(const cvector_t &q) const;

protected:
    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();

private:
    double m_height;
    double m_radius;
};

#endif /* FORMFACTORPARALLELEPIPED_H_ */
