// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorInfLongBox.h
//! @brief     Defines class FormFactorInfLongBox.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORINFLONGBOX_H
#define FORMFACTORINFLONGBOX_H

#include "IFormFactorBorn.h"
#include "IStochasticParameter.h"

//! @class FormFactorInfLongBox
//! @ingroup formfactors
//! @brief The formfactor for a infinite long rectangular box.

class BA_CORE_API_ FormFactorInfLongBox : public IFormFactorBorn
{
public:
    FormFactorInfLongBox( double width, double height)
        : m_width(width), m_height(height) {

            setName("FormFactorInfLongBox");
            init_parameters();
        }

    virtual ~FormFactorInfLongBox() {}

    FormFactorInfLongBox *clone() const;

    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    int getNumberOfStochasticParameters() const { return 2; }

    //! Returns height of Box
    double getHeight() const { return m_height; }

    //! Returns radius of Box
    virtual double getRadius() const { return m_width/2.0; }

    //! Returns width of Box
    double getWidth() const { return m_width; }

    virtual complex_t evaluate(const cvector_t& k_i,
            const Bin1DCVector& k_f_bin, Bin1D alpha_f_bin) const;

    virtual complex_t evaluate_for_q(const cvector_t& q) const;

    double getVolume() const;

protected:
    virtual void init_parameters();

private:
    double m_width;
    double m_height;
};

#endif // FORMFACTORINFLONGBOX_H


