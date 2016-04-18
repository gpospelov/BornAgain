// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorLongRipple2Gauss.h
//! @brief     Defines class FormFactorLongRipple2Gauss.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORLONGRIPPLE2GAUSS_H
#define FORMFACTORLONGRIPPLE2GAUSS_H

#include "IFormFactorBorn.h"

//! @class FormFactorLongRipple2Gauss
//! @ingroup formfactors
//! @brief The formfactor for a triangular ripple.

class BA_CORE_API_ FormFactorLongRipple2Gauss : public IFormFactorBorn
{
public:
    //! @brief FormFactorLongRipple2Gauss constructor
    //! @param length of Ripple2
    //! @param width of triangular cross section
    //! @param height of triangular cross section
    //! @param asymmetry length of triangular cross section
    FormFactorLongRipple2Gauss(double length, double width, double height, double asymetry);

    virtual ~FormFactorLongRipple2Gauss() { }

    virtual FormFactorLongRipple2Gauss *clone() const;

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

inline double FormFactorLongRipple2Gauss::getHeight() const
{
    return m_height;
}

inline double FormFactorLongRipple2Gauss::getWidth() const
{
    return m_width;
}

inline double FormFactorLongRipple2Gauss::getLength() const
{
    return m_length;
}

inline double FormFactorLongRipple2Gauss::getAsymmetry() const
{
    return m_d;
}

#endif // FORMFACTORLONGRIPPLE2GAUSS_H
