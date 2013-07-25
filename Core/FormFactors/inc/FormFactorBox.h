// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorBox.h
//! @brief     Defines class FormFactorBox.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
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
    FormFactorBox( double radius, double width, double height)
        : m_radius(radius), m_width(width), m_height(height) {}

    ~FormFactorBox() {}

    FormFactorBox *clone() const
    { return new FormFactorBox(m_radius, m_width, m_height ); }

    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    int getNumberOfStochasticParameters() const { return 2; }

    //! Returns radius of Box
    double getRadius() const { return m_radius; }

    //! Returns width of Box
    double getwidth() const { return m_width; }

    complex_t evaluate_for_q(const cvector_t& q) const;

    double getVolume() const { return 4*m_height*m_radius*m_width; }

    double getHeight() const { return m_height; }

 protected:
    void init_parameters();

 private:
    double m_radius;
    double m_width;
    double m_height;
};

#endif // FORMFACTORBOX_H


