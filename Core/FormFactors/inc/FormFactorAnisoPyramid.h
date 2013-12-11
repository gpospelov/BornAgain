// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorAnisoPyramid.h
//! @brief     Defines class FormFactorAnisoPyramid
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORANISOPYRAMID_H
#define FORMFACTORANISOPYRAMID_H

#include "IFormFactorBorn.h"
#include "IStochasticParameter.h"

//! Form factor of an anisotropic pyramid.

class BA_CORE_API_ FormFactorAnisoPyramid : public IFormFactorBorn
{
public:
    //! @brief anisotropic pyramid constructor
    //! @param height of anisotropic pyramide
    //! @param length of anisotropic pyramid's base
    //! @param width of anisotropic pyramid's base
    //! @param angle in radians between base and facet
    FormFactorAnisoPyramid(double length, double width, double height, double alpha);

    ~FormFactorAnisoPyramid() {}
    virtual FormFactorAnisoPyramid *clone() const;

    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    virtual int getNumberOfStochasticParameters() const { return 4; }

    virtual double getHeight() const { return m_height; }
    virtual void setHeight(double height) { m_height = height; }

    virtual double getLength() const { return m_length; }
    virtual void setLength(double length) { m_length = length; }

    virtual double getWidth() const { return m_width; }
    virtual void setWidth(double width) { m_width = width; }

    virtual double getAlpha() const { return m_alpha; }
    virtual void setAlpha(double alpha) { m_alpha = alpha; }

    virtual complex_t evaluate_for_q(const cvector_t& q) const;

protected:
    virtual void init_parameters();

private:
    double m_length;
    double m_width;
    double m_height;
    double m_alpha;
};

#endif // FORMFACTORANISOPYRAMID_H
