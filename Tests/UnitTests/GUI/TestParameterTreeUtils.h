#include <QtTest>
#include "ParameterTreeItems.h"
#include "ParameterTreeUtils.h"
#include "LayerItem.h"
#include "SampleModel.h"
#include "ParticleItem.h"
#include "FormFactorItems.h"
#include "VectorItem.h"

namespace {
    const QStringList expectedParticleParameterNames = {
        "Particle/Cylinder/Radius", "Particle/Cylinder/Height", "Particle/Abundance",
        "Particle/Position Offset/X", "Particle/Position Offset/Y", "Particle/Position Offset/Z"};

    const QStringList expectedParticleParameterTranslations = {
        "Particle/Cylinder/Radius", "Particle/Cylinder/Height", "Particle/Abundance",
        "Particle/PositionX", "Particle/PositionY", "Particle/PositionZ"};

}

class TestParameterTreeUtils : public QObject {
    Q_OBJECT

private slots:
    void test_parameterTreeNames();
    void test_parameterTranslatedNames();
    void test_linkItemFromParameterName();
};

//! Tests parameter names of given item.

inline void TestParameterTreeUtils::test_parameterTreeNames()
{
    SampleModel model;

    SessionItem *layer = model.insertNewItem(Constants::LayerType);
    QCOMPARE(ParameterTreeUtils::parameterTreeNames(layer), QStringList() << "Layer/Thickness");

    SessionItem *particle = model.insertNewItem(Constants::ParticleType);
    QCOMPARE(ParameterTreeUtils::parameterTreeNames(particle), expectedParticleParameterNames);
}

//! Tests translated parameter names of given item.

inline void TestParameterTreeUtils::test_parameterTranslatedNames()
{
    SampleModel model;

    SessionItem *particle = model.insertNewItem(Constants::ParticleType);

    QCOMPARE(ParameterTreeUtils::translatedParameterTreeNames(particle),
             expectedParticleParameterTranslations);
}

//! Tests translated parameter names of given item.

inline void TestParameterTreeUtils::test_linkItemFromParameterName()
{
    SampleModel model;

    SessionItem* particle = model.insertNewItem(Constants::ParticleType);

    auto ffItem = static_cast<FormFactorItem*>(particle->getGroupItem(ParticleItem::P_FORM_FACTOR));
    Q_ASSERT(ffItem);
    QCOMPARE(ffItem->modelType(), Constants::CylinderType);

    QCOMPARE(
        ffItem->getItem(CylinderItem::P_RADIUS),
        ParameterTreeUtils::parameterNameToLinkedItem("Particle/Cylinder/Radius", particle));
    QCOMPARE(
        ffItem->getItem(CylinderItem::P_HEIGHT),
        ParameterTreeUtils::parameterNameToLinkedItem("Particle/Cylinder/Height", particle));
    QCOMPARE(particle->getItem(ParticleItem::P_POSITION)->getItem(VectorItem::P_X),
             ParameterTreeUtils::parameterNameToLinkedItem("Particle/Position Offset/X", particle));
}
