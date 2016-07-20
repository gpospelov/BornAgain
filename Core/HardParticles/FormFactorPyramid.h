// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticles/FormFactorPyramid.h
//! @brief     Declares class FormFactorPyramid
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015-16
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORPYRAMID_H
#define FORMFACTORPYRAMID_H

#include "FormFactorPolyhedron.h" // inheriting from

//! @class FormFactorPyramid
//! @ingroup formfactors
//! @brief The formfactor of a quadratic pyramid
class BA_CORE_API_ FormFactorPyramid : public FormFactorPolyhedron
{
public:
    FormFactorPyramid(double base_edge, double height, double alpha);

    virtual FormFactorPyramid* clone() const final;
    virtual void accept(ISampleVisitor *visitor) const final;

    double getHeight() const { return m_height; }
    double getBaseEdge() const { return m_base_edge; }
    double getAlpha() const { return m_alpha; }

private:
    static const PolyhedralTopology topology;
    virtual void onChange() final;

    double m_base_edge;
    double m_height;
    double m_alpha;
};

#endif // FORMFACTORPYRAMID_H
