// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/FormFactorCone6.h
//! @brief     Declares class FormFactorCone6
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
    //! @brief Cone6 constructor
    //! @param base_edge of hexagonal base (different from R in IsGisaxs)
    //! @param height of Cone6
    //! @param angle in radians between base and facet
    FormFactorCone6(double base_edge, double height,  double alpha);

    virtual FormFactorCone6* clone() const;
    virtual void accept(ISampleVisitor *visitor) const;

    double getBaseEdge() const { return m_base_edge; }
    double getHeight() const { return m_height; }
    double getAlpha() const { return m_alpha; }

private:
    static const Topology topology;
    virtual void onChange() final;
    double m_base_edge;
    double m_height;
    double m_alpha;
};

#endif // FORMFACTORCONE6_H
