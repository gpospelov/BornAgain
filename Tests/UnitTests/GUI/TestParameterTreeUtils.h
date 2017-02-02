#include <QtTest>
#include "ParameterTreeItems.h"
#include "ParameterTreeUtils.h"
#include "LayerItem.h"
#include "SampleModel.h"

namespace {
    const QStringList expectedForParticle = {
        "Particle/AnisoPyramid/Length", "Particle/AnisoPyramid/Width",
        "Particle/AnisoPyramid/Height", "Particle/AnisoPyramid/Alpha",
        "Particle/Abundance", "Particle/Position Offset/X",
        "Particle/Position Offset/Y", "Particle/Position Offset/Z"};
}


class TestParameterTreeUtils : public QObject {
    Q_OBJECT

private slots:
    void test_parameterTreeList();
};

//! Tests function returning list of names representing properties of given item.

inline void TestParameterTreeUtils::test_parameterTreeList()
{
    SampleModel model;

    SessionItem *layer = model.insertNewItem(Constants::LayerType);
    QCOMPARE(ParameterTreeUtils::parameterTreeList(layer), QStringList() << "Layer/Thickness");

    SessionItem *particle = model.insertNewItem(Constants::ParticleType);
    QCOMPARE(ParameterTreeUtils::parameterTreeList(particle), expectedForParticle);
}
