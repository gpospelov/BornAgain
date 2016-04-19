// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/FormFactorRipple2.h
//! @brief     Defines class FormFactorRipple2.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORRIPPLE2_H
#define FORMFACTORRIPPLE2_H

#include "IFormFactorBorn.h"

//! @class FormFactorRipple2
//! @ingroup formfactors
//! @brief The formfactor for a triangular ripple.

class BA_CORE_API_ FormFactorRipple2 : public IFormFactorBorn
{
public:
    //! @brief Ripple2 constructor
    //! @param length of Ripple2
    //! @param width of triangular cross section
    //! @param height of triangular cross section
    //! @param asymmetry length of triangular cross section
    FormFactorRipple2(double length, double width, double height, double asymetry);

    virtual ~FormFactorRipple2() { }

    virtual FormFactorRipple2 *clone() const;

    virtual void accept(ISampleVisitor *visitor) const;

    virtual double getRadius() const;

    double getHeight() const;

    double getWidth() const;

    double getLength() const;

    double getAsymmetry() const;

    virtual complex_t evaluate_for_q(const cvector_t q) const;

protected:
    virtual bool check_initialization() const;
    virtual void init_parameters();

private:
    double m_width;
    double m_height;
    double m_length;
    double m_d;
    mutable cvector_t m_q;
};

inline double FormFactorRipple2::getHeight() const
{
    return m_height;
}

inline double FormFactorRipple2::getWidth() const
{
    return m_width;
}

inline double FormFactorRipple2::getLength() const
{
    return m_length;
}

inline double FormFactorRipple2::getAsymmetry() const
{
    return m_d;
}

#endif // FORMFACTORRIPPLE2_H
