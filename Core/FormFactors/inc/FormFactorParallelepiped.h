// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorParallelepiped.h
//! @brief     Defines class FormFactorParallelepiped.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORPARALLELEPIPED_H_
#define FORMFACTORPARALLELEPIPED_H_

#include "IFormFactorBorn.h"
#include "IStochasticParameter.h"

//! @class FormFactorParallelepiped
//! @ingroup formfactors
//! @brief The form actor of a parallelepiped.

class BA_CORE_API_ FormFactorParallelepiped : public IFormFactorBorn
{
public:
    FormFactorParallelepiped(double length, double height);
    ~FormFactorParallelepiped() {}
    virtual FormFactorParallelepiped *clone() const;

    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    virtual int getNumberOfStochasticParameters() const { return 2; }

    //! Returns side length of parallelepiped
    double getLength() const { return m_length; }

   // virtual double getVolume() const
   // { return m_height*m_length*m_length; }

    virtual double getHeight() const { return m_height; }

    virtual complex_t evaluate_for_q(const cvector_t& q) const;

protected:
    virtual void init_parameters();

private:
    double m_length;
    double m_height;
};

#endif /* FORMFACTORPARALLELEPIPED_H_ */


