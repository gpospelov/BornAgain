// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorCuboctahedron.h
//! @brief     Defines class FormFactorCuboctahedron
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORCUBOCTAHEDRON_H
#define FORMFACTORCUBOCTAHEDRON_H

#include "IFormFactorBorn.h"
#include "IStochasticParameter.h"

//! @class FormFactorCuboctahedron
//! @ingroup formfactors
//! @brief The formfactor of cuboctahedron.

class BA_CORE_API_ FormFactorCuboctahedron : public IFormFactorBorn
{
public:
    //! @brief cuboctahedron constructor
    //! @param height of bottom of cuboctahedron
    //! @param height ratio : height top part/height bottom part
    //! @param half_side half of cuboctahedron's base
    //! @param angle in radians between base and facet

    FormFactorCuboctahedron(double half_side, double height,
                            double height_ratio, double alpha);

    ~FormFactorCuboctahedron() {}
    virtual FormFactorCuboctahedron *clone() const;

    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    virtual int getNumberOfStochasticParameters() const { return 4; }

    virtual double getHeight() const { return m_height; }
    virtual void setHeight(double height) { m_height = height; }

    virtual double getHeightRatio() const { return m_height_ratio; }
    virtual void setHeightRatio(double height_ratio) { m_height_ratio
                                                     = height_ratio; }

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
    double m_height_ratio;
    double m_alpha;
};

#endif // FORMFACTORCUBOCTAHEDRON_H
