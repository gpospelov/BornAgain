// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorPyramid.h
//! @brief     Defines class FormFactorPyramid
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORPYRAMID_H
#define FORMFACTORPYRAMID_H

#include "IFormFactorBorn.h"
#include "IStochasticParameter.h"

//! @class FormFactorPyramid
//! @ingroup formfactors
//! @brief The form factor of pyramid.

class BA_CORE_API_ FormFactorPyramid : public IFormFactorBorn
{
public:
    //! @brief pyramid constructor
    //! @param length of pyramid's base
    //! @param height of pyramid
    //! @param angle in radians between base and facet
    FormFactorPyramid(double length, double height, double alpha);

    ~FormFactorPyramid() {}
    virtual FormFactorPyramid *clone() const;

    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    virtual int getNumberOfStochasticParameters() const { return 3; }

    virtual double getHeight() const { return m_height; }
    virtual void setHeight(double height) { m_height = height; }

    virtual double getLength() const { return m_length; }
    virtual void setLength(double length) { m_length = length; }

    virtual double getAlpha() const { return m_alpha; }
    virtual void setAlpha(double alpha) { m_alpha = alpha; }

    virtual complex_t evaluate_for_q(const cvector_t& q) const;

protected:
    virtual void init_parameters();

private:
    double m_length;
    double m_height;
    double m_alpha;
};

#endif // FORMFACTORPYRAMID_H


