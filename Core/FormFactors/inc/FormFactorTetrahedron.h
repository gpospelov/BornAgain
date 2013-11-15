// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorTetrahedron.h
//! @brief     Defines class FormFactorTetrahedron
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORTETRAHEDRON_H
#define FORMFACTORTETRAHEDRON_H


#include "IFormFactorBorn.h"
#include "IStochasticParameter.h"

//! Form factor of tetrahedron.

class BA_CORE_API_ FormFactorTetrahedron : public IFormFactorBorn
{
public:
    //! @brief tetrahedron constructor
    //! @param height of tetrahedron
    //! @param half_side half of tetrahedron's base
    //! @param angle in radians between base and facet
    FormFactorTetrahedron(double height, double half_side, double alpha);

    ~FormFactorTetrahedron() {}
    virtual FormFactorTetrahedron *clone() const;

    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    virtual int getNumberOfStochasticParameters() const { return 3; }

    virtual double getHeight() const { return m_height; }
    virtual void setHeight(double height) { m_height = height; }

    virtual double getHalfSide() const { return m_half_side; }
    virtual void setHalfSide(double half_side) { m_half_side = half_side; }

    virtual double getAlpha() const { return m_alpha; }
    virtual void setAlpha(double alpha) { m_alpha = alpha; }

    virtual complex_t evaluate_for_q(const cvector_t& q) const;

protected:
    virtual void init_parameters();

private:
    double m_height;
    double m_half_side;
    double m_alpha;
    double m_root3; // Cached value of square root of 3
};

#endif // FORMFACTORTETRAHEDRON_H
