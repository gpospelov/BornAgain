// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorPrism3.h
//! @brief     Defines class FormFactorPrism3.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORPRISM3_H_
#define FORMFACTORPRISM3_H_

#include "IFormFactorBorn.h"
#include "IStochasticParameter.h"

//! @class FormFactorPrism3
//! @ingroup formfactors
//! @brief The formfactor of a prism based on a regular triangle.

class BA_CORE_API_ FormFactorPrism3 : public IFormFactorBorn
{
public:
    //! @brief Prism3 constructor
    //! @param length of a side of Prism3's base
    //! @param height of Prism3
    FormFactorPrism3(double length, double height);
    ~FormFactorPrism3() {}
    virtual FormFactorPrism3 *clone() const;

    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    virtual int getNumberOfStochasticParameters() const { return 2; }

    virtual double getHeight() const { return m_height; }
    virtual void setHeight(double height) { m_height = height; }

    virtual double getLength() const { return m_length; }
    virtual void setLength(double length) { m_length = length; }

    virtual complex_t evaluate_for_q(const cvector_t& q) const;

protected:
    virtual void init_parameters();

private:
    double m_length;
    double m_height;
    double m_root3; // Cached value of square root of 3
};

#endif /* FORMFACTORPRISM3_H_ */


