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

    ~FormFactorCuboctahedron() {}
    virtual FormFactorCuboctahedron *clone() const;

    virtual void accept(ISampleVisitor *visitor) const;

    double getHeight() const;
    void setHeight(double height);

    double getHeightRatio() const;
    void setHeightRatio(double height_ratio);

    double getLength() const;
    void setLength(double length);

    double getAlpha() const;
    void setAlpha(double alpha);

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

inline void FormFactorCuboctahedron::setHeight(double height)
{
    m_height = height;
}

inline double FormFactorCuboctahedron::getHeightRatio() const
{
    return m_height_ratio;
}

inline void FormFactorCuboctahedron::setHeightRatio(double height_ratio)
{
    m_height_ratio = height_ratio;
}

inline double FormFactorCuboctahedron::getLength() const
{
    return m_length;
}

inline void FormFactorCuboctahedron::setLength(double length)
{
    m_length = length;
}

inline double FormFactorCuboctahedron::getAlpha() const
{
    return m_alpha;
}

inline void FormFactorCuboctahedron::setAlpha(double alpha)
{
    m_alpha = alpha;
}

#endif // FORMFACTORCUBOCTAHEDRON_H
