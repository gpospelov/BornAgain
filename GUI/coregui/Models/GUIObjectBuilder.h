// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Models/GUIObjectBuilder.h
//! @brief     Defines class GUIObjectBuilder.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef GUIOBJECTBUILDER_H
#define GUIOBJECTBUILDER_H

#include "ISampleVisitor.h"
#include "Samples.h"
#include "MaterialProperty.h"
#include <QMap>

class SessionModel;
class ParameterizedItem;

class GUIObjectBuilder : public ISampleVisitor
{
public:
    GUIObjectBuilder();
    ~GUIObjectBuilder(){}

    void populateModel(SessionModel *model, ISample *sample);

    using ISampleVisitor::visit;

    void visit(const ParticleLayout *);

    void visit(const Layer *);

    void visit(const LayerInterface *);

    void visit(const MultiLayer *);

    void visit(const Particle *);

    void visit(const ParticleInfo *);

    void visit(const FormFactorAnisoPyramid *);
    void visit(const FormFactorBox *);
    void visit(const FormFactorCone *);
    void visit(const FormFactorCone6 *);
    void visit(const FormFactorCuboctahedron *);
    void visit(const FormFactorCylinder *);
    void visit(const FormFactorEllipsoidalCylinder *);
    void visit(const FormFactorFullSphere *);
    void visit(const FormFactorFullSpheroid *);
    void visit(const FormFactorHemiEllipsoid *);
    void visit(const FormFactorPrism3 *);
    void visit(const FormFactorPrism6 *);
    void visit(const FormFactorPyramid *);
    void visit(const FormFactorRipple1 *);
    void visit(const FormFactorRipple2 *);
    void visit(const FormFactorTetrahedron *);
    void visit(const FormFactorTruncatedSphere *);
    void visit(const FormFactorTruncatedSpheroid *);

    void visit(const InterferenceFunctionNone *);

    void visit(const LayerRoughness *);

    ParameterizedItem *getTopItem() { return m_levelToParent[0]; }

private:
    MaterialProperty createMaterialFromDomain(const IMaterial *);

    SessionModel *m_sessionModel;

    QMap<int, ParameterizedItem *> m_levelToParent;

    QString m_topSampleName;
};

#endif // GUIOBJECTBUILDER_H
