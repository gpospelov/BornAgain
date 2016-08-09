// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorCone6.h
//! @brief     Defines class FormFactorCone6
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015-16
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORCONE6_H
#define FORMFACTORCONE6_H

#include "FormFactorPolyhedron.h"

//! @class FormFactorCone6
//! @ingroup formfactors
//! @brief The formfactor of a cone6.
class BA_CORE_API_ FormFactorCone6 : public FormFactorPolyhedron
{
public:
    FormFactorCone6(double base_edge, double height,  double alpha);

    virtual FormFactorCone6* clone() const {
        return new FormFactorCone6(m_base_edge, m_height, m_alpha); }
    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    double getBaseEdge() const { return m_base_edge; }
    double getHeight() const { return m_height; }
    double getAlpha() const { return m_alpha; }

private:
    static const PolyhedralTopology topology;
    void onChange() final;
    double m_base_edge;
    double m_height;
    double m_alpha;
};

#endif // FORMFACTORCONE6_H
