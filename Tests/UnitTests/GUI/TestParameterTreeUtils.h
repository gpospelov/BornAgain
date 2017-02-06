#include <QtTest>
#include "ParameterTreeItems.h"
#include "ParameterTreeUtils.h"
#include "LayerItem.h"
#include "SampleModel.h"

namespace {
    const QStringList expectedParticleParameterNames = {
        "Particle/AnisoPyramid/Length", "Particle/AnisoPyramid/Width",
        "Particle/AnisoPyramid/Height", "Particle/AnisoPyramid/Alpha",
        "Particle/Abundance", "Particle/Position Offset/X",
        "Particle/Position Offset/Y", "Particle/Position Offset/Z"};

    const QStringList expectedParticleParameterTranslations = {
        "Particle/AnisoPyramid/Length", "Particle/AnisoPyramid/Width",
        "Particle/AnisoPyramid/Height", "Particle/AnisoPyramid/Alpha",
        "Particle/Abundance", "Particle/PositionX",
        "Particle/PositionY", "Particle/PositionZ"};
}

class TestParameterTreeUtils : public QObject {
    Q_OBJECT

private slots:
    void test_parameterTreeNames();
    void test_parameterTranslatedNames();
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
    QCOMPARE(1,1);
    SampleModel model;

    SessionItem *particle = model.insertNewItem(Constants::ParticleType);

    QCOMPARE(ParameterTreeUtils::translatedParameterTreeNames(particle),
             expectedParticleParameterTranslations);
}
