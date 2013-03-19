// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/FormFactorBox.h
//! @brief     Defines class FormFactorBox.
//!
//! @homepage  apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef FORMFACTORBOX_H
#define FORMFACTORBOX_H

#include "IFormFactorBorn.h"
#include "IStochasticParameter.h"

//! ?

class FormFactorBox : public IFormFactorBorn
{
public:
    FormFactorBox( double radius, double width, double height);
    ~FormFactorBox();
    virtual FormFactorBox *clone() const;

    virtual int getNumberOfStochasticParameters() const { return 2; }

    //! return radius of Box
    double getRadius() const { return m_radius; }

    //! return width of Box
    double getwidth() const { return m_width; }

    virtual complex_t evaluate_for_q(const cvector_t &q) const;

    virtual double getVolume() const {
        return 4.0*m_height*m_radius*m_width;
    }

    virtual double getHeight() const { return m_height; }

protected:
    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();

private:
    double m_radius;
    double m_width;
    double m_height;
};

#endif // FORMFACTORBOX_H
