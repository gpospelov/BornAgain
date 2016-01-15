// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorLorentz.h
//! @brief     Defines class FormFactorLorentz.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORLORENTZ_H_
#define FORMFACTORLORENTZ_H_

#include "IFormFactorBorn.h"

//! @class FormFactorLorentz
//! @ingroup formfactors
//! @brief The formfactor of a lorentzian.

class BA_CORE_API_ FormFactorLorentz : public IFormFactorBorn
{
public:
    FormFactorLorentz(double volume);
    FormFactorLorentz(double width, double height);

    virtual FormFactorLorentz *clone() const;

    virtual void accept(ISampleVisitor *visitor) const;

    virtual double getRadius() const;

    //! Returns height of shape
    double getHeight() const;

    //! Returns width of shape
    double getWidth() const;

    virtual complex_t evaluate_for_q(const cvector_t& q) const;

protected:
    virtual bool check_initialization() const;
    virtual void init_parameters();

private:
    double m_width;
    double m_height;
    void initialize();
};

inline double FormFactorLorentz::getHeight() const
{
    return m_height;
}

inline double FormFactorLorentz::getWidth() const
{
    return m_width;
}

#endif /* FORMFACTORLORENTZ_H_ */


