// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/FormFactorPrism3.h
//! @brief     Declares class FormFactorPrism3.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015-16
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORPRISM3_H
#define FORMFACTORPRISM3_H
#include "FormFactorPolyhedron.h"

//! @class FormFactorPrism3
//! @ingroup formfactors
//! @brief The formfactor of a prism based on an equilateral triangle.

class BA_CORE_API_ FormFactorPrism3 : public FormFactorPolygonalPrism
{
public:
    FormFactorPrism3(const double base_edge, const double height);

    static PolyhedralFace prismatic_face(const double base_edge);

    virtual FormFactorPrism3 *clone() const;
    virtual void accept(ISampleVisitor *visitor) const;

    double getBaseEdge() const { return m_base_edge; }

private:
    double m_base_edge;
};

#endif // FORMFACTORPRISM3_H
