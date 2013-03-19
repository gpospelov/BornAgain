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
//! @file      FormFactors/FormFactorEllipsoid.h 
//! @brief     Defines class FormFactorEllipsoid.
//
// ************************************************************************** //

#ifndef FORMFACTORELLIPSOID_H
#define FORMFACTORELLIPSOID_H

#include "IFormFactorBorn.h"
#include "IStochasticParameter.h"

//! ?

class FormFactorEllipsoid : public IFormFactorBorn
{
public:
    FormFactorEllipsoid( double radius, double width, double height, double alpha);
    ~FormFactorEllipsoid();
    virtual FormFactorEllipsoid *clone() const;

    virtual int getNumberOfStochasticParameters() const { return 2; }

    //! return radius of Ellipsoid
    double getRadius() const { return m_radius; }

    //! return width of Ellipsoid
    double getWidth() const { return m_width; }

    virtual double getVolume() const {
        return 2.0*m_height*m_radius*m_width;
    }

    virtual double getHeight() const { return m_height; }

    virtual complex_t evaluate_for_q(const cvector_t &q) const;

protected:
    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();

private:
    double m_radius;
    double m_width;
    double m_height;
    double m_alpha;
};

#endif // FORMFACTORELLIPSOID_H
