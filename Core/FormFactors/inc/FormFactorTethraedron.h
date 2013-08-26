// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorTethraedron.h
//! @brief     Defines class FormFactorTethraedron
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORTETHRAEDRON_H
#define FORMFACTORTETHRAEDRON_H


#include "IFormFactorBorn.h"
#include "IStochasticParameter.h"

//! Form factor of tethraedron.

class BA_CORE_API_ FormFactorTethraedron : public IFormFactorBorn
{
 public:
    //! @brief tethraedron constructor
    //! @param height of tethraedron
    //! @param half_side half of tethraedron's base
    //! @param angle in radians between base and facet
    FormFactorTethraedron(double height, double half_side, double alpha);

    ~FormFactorTethraedron() {}
    virtual FormFactorTethraedron *clone() const;

    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    virtual int getNumberOfStochasticParameters() const { return 3; }

    virtual double getHeight() const { return m_height; }

    virtual complex_t evaluate_for_q(const cvector_t& q) const;

 protected:
    virtual void init_parameters();

 private:
    double m_height;
    double m_half_side;
    double m_alpha;
    double m_root3; // Cached value of square root of 3
};

#endif // FORMFACTORTETHRAEDRON_H
