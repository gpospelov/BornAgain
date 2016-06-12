// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/FormFactors/FormFactorCuboctahedron.h
//! @brief     Declares class FormFactorCuboctahedron
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015-16
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORCUBOCTAHEDRON_H
#define FORMFACTORCUBOCTAHEDRON_H

#include "FormFactorPolyhedron.h"

//! @class FormFactorCuboctahedron
//! @ingroup formfactors
//! @brief The formfactor of a cuboctahedron.

class BA_CORE_API_ FormFactorCuboctahedron : public FormFactorPolyhedron
{
public:
    FormFactorCuboctahedron(double length, double height, double height_ratio, double alpha);

    virtual FormFactorCuboctahedron *clone() const final;
    virtual void accept(ISampleVisitor *visitor) const final;

    double getLength() const { return m_length; }
    double getHeight() const { return m_height; }
    double getHeightRatio() const { return m_height_ratio; }
    double getAlpha() const { return m_alpha; }

private:
    static const Topology topology;
    virtual void onChange() final;

    double m_length;
    double m_height;
    double m_height_ratio;
    double m_alpha;
};

#endif // FORMFACTORCUBOCTAHEDRON_H
