// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/GUIObjectBuilder.h
//! @brief     Defines class GUIObjectBuilder
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef GUIOBJECTBUILDER_H
#define GUIOBJECTBUILDER_H

#include "ISampleVisitor.h"
#include "Samples.h"
#include "InterferenceFunctions.h"
#include "MaterialProperty.h"
#include <QMap>

class InstrumentModel;
class SampleModel;
class SessionItem;
class DocumentModel;

//! Class to build SampleModel and InstrumentModel from domain's ISample
class BA_CORE_API_ GUIObjectBuilder : public ISampleVisitor
{
public:
    GUIObjectBuilder();
    virtual ~GUIObjectBuilder(){}

    SessionItem *populateSampleModel(SampleModel *sampleModel,
                                           const GISASSimulation &simulation,
                                           const QString &sampleName=QString());

    SessionItem *populateSampleModel(SampleModel *sampleModel,
                                           const ISample &sample,
                                           const QString &sampleName=QString());

    SessionItem *populateInstrumentModel(InstrumentModel *instrumentModel,
                                               const GISASSimulation &simulation,
                                               const QString &instrumentName=QString());


    SessionItem *populateDocumentModel(DocumentModel *documentModel,
                                               const GISASSimulation &simulation);

    using ISampleVisitor::visit;

    void visit(const ParticleLayout *);

    void visit(const Layer *);

    void visit(const LayerInterface *);

    void visit(const MultiLayer *);

    void visit(const Particle *);
    void visit(const ParticleDistribution *);
    void visit(const ParticleCoreShell *);
    void visit(const ParticleComposition *);

    void visit(const FormFactorAnisoPyramid *);
    void visit(const FormFactorBox *);
    void visit(const FormFactorCone *);
    void visit(const FormFactorCone6 *);
    void visit(const FormFactorCuboctahedron *);
    void visit(const FormFactorCylinder *);
    void visit(const FormFactorDodecahedron *);
    void visit(const FormFactorEllipsoidalCylinder *);
    void visit(const FormFactorFullSphere *);
    void visit(const FormFactorFullSpheroid *);
    void visit(const FormFactorHemiEllipsoid *);
    void visit(const FormFactorIcosahedron *);
    void visit(const FormFactorPrism3 *);
    void visit(const FormFactorPrism6 *);
    void visit(const FormFactorPyramid *);
    void visit(const FormFactorRipple1 *);
    void visit(const FormFactorRipple2 *);
    void visit(const FormFactorTetrahedron *);
    void visit(const FormFactorTruncatedCube *);
    void visit(const FormFactorTruncatedSphere *);
    void visit(const FormFactorTruncatedSpheroid *);

    void visit(const InterferenceFunctionRadialParaCrystal *);
    void visit(const InterferenceFunction2DParaCrystal *);
    void visit(const InterferenceFunction1DLattice *);
    void visit(const InterferenceFunction2DLattice *);
    void visit(const InterferenceFunctionNone *);

    void visit(const LayerRoughness *);

    void visit(const RotationX *);
    void visit(const RotationY *);
    void visit(const RotationZ *);
    void visit(const RotationEuler *);

private:
    void buildAbundanceInfo(SessionItem *particleItem);
    void buildPositionInfo(SessionItem *particleItem, const IParticle *sample);
    MaterialProperty createMaterialFromDomain(const IMaterial *);

    SampleModel *m_sampleModel;

    QMap<int, SessionItem *> m_levelToParentItem;
    QMap<QString, double > m_propertyToValue;
    QMap<QString, bool> m_sample_encountered;
    QMap<SessionItem *, const ISample *> m_itemToSample;
    QString m_topSampleName;
};

#endif // GUIOBJECTBUILDER_H
