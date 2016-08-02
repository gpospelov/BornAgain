// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorLongRipple2Gauss.h
//! @brief     Declares class FormFactorLongRipple2Gauss.
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

#include "IFormFactorBorn.h" // inheriting from

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
    FormFactorLongRipple2Gauss(double length, double width, double height, double asymmetry);

    virtual ~FormFactorLongRipple2Gauss() {}

    FormFactorLongRipple2Gauss* clone() const {
        return new FormFactorLongRipple2Gauss(m_length, m_width, m_height, m_d); }
    void accept(ISampleVisitor* visitor) const final { visitor->visit(this); }

    double getHeight() const { return m_height; }
    double getWidth() const { return m_width; }
    double getLength() const { return m_length; }
    double getAsymmetry() const { return m_d; }

    double getRadialExtension() const final;

    complex_t evaluate_for_q(const cvector_t q) const final;

protected:
    virtual bool check_initialization() const;

private:
    double m_width;
    double m_height;
    double m_length;
    double m_d;
    mutable cvector_t m_q;
};

#endif // FORMFACTORLONGRIPPLE2GAUSS_H
