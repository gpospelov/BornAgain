// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorCuboctahedron.h
//! @brief     Defines class FormFactorCuboctahedron
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORCUBOCTAHEDRON_H
#define FORMFACTORCUBOCTAHEDRON_H

#include "IFormFactorBorn.h"

//! @class FormFactorCuboctahedron
//! @ingroup formfactors
//! @brief The formfactor of a cuboctahedron.

class BA_CORE_API_ FormFactorCuboctahedron : public IFormFactorBorn
{
public:
    //! @brief Cuboctahedron constructor
    //! @param length of one side of Cuboctahedron's square base
    //! @param height of bottom of Cuboctahedron
    //! @param height_ratio : height top part/height bottom part
    //! @param angle in radians between base and facet

    FormFactorCuboctahedron(double length, double height,
                            double height_ratio, double alpha);

    virtual ~FormFactorCuboctahedron() {}
    virtual FormFactorCuboctahedron *clone() const;

    virtual void accept(ISampleVisitor *visitor) const;

    virtual double getRadius() const;

    double getHeight() const;

    double getHeightRatio() const;

    double getLength() const;

    double getAlpha() const;

    virtual complex_t evaluate_for_q(const cvector_t& q) const;

protected:
    virtual bool check_initialization() const;
    virtual void init_parameters();

private:
    double m_height;
    double m_length;
    double m_height_ratio;
    double m_alpha;
};

inline double FormFactorCuboctahedron::getHeight() const
{
    return m_height;
}

inline double FormFactorCuboctahedron::getHeightRatio() const
{
    return m_height_ratio;
}

inline double FormFactorCuboctahedron::getLength() const
{
    return m_length;
}

inline double FormFactorCuboctahedron::getAlpha() const
{
    return m_alpha;
}

#endif // FORMFACTORCUBOCTAHEDRON_H
