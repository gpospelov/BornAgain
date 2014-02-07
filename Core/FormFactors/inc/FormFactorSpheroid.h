// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorSpheroid.h
//! @brief     Defines class FormFactorSpheroid.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORSPHEROID_H
#define FORMFACTORSPHEROID_H

#include "IFormFactorBorn.h"
#include "IStochasticParameter.h"
#include "MemberComplexFunctionIntegrator.h"

//! @class FormFactorSpheroid
//! @ingroup formfactors
//! @brief The formfactor of a spheroid.

class BA_CORE_API_ FormFactorSpheroid : public IFormFactorBorn
{
public:
    //! @brief Spheroid constructor
    //! @param radius of Spheroid
    //! @param height of Spheroid
    //! @param flattening parameter in vertical direction (full height: 2 x flattening x radius)

    FormFactorSpheroid(double radius, double height, double height_flattening);

    ~FormFactorSpheroid() {delete m_integrator;}

    virtual FormFactorSpheroid *clone() const;

    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    virtual int getNumberOfStochasticParameters() const { return 3; }

    virtual double getHeight() const { return m_height; }

    virtual double getRadius() const { return m_radius; }

    virtual double getHeightFullSpheroid() const
    { return 2.*m_height_flattening*m_radius; }

    virtual complex_t evaluate_for_q(const cvector_t& q) const;

protected:
    virtual void init_parameters();

private:

    complex_t Integrand(double Z, void* params) const;

    double m_radius;
    double m_height;
    double m_height_flattening;
    mutable cvector_t m_q;

    MemberComplexFunctionIntegrator<FormFactorSpheroid> *m_integrator;
};


#endif // FORMFACTORSPHEROID_H
