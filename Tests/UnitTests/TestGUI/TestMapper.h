#ifndef TESTMAPPER_H
#define TESTMAPPER_H

#include "ParameterizedItem.h"
#include "SampleModel.h"
#include "item_constants.h"
#include "ParticleItem.h"
#include "ParticleCompositionItem.h"
#include "ParticleDistributionItem.h"
#include <memory>
#include <QtTest>

class TestMapper : public QObject {
    Q_OBJECT

private slots:
    void test_ParticeleCompositionUpdate();
};

inline void TestMapper::test_ParticeleCompositionUpdate()
{
    SampleModel model;
    ParameterizedItem *multilayer = model.insertNewItem(Constants::MultiLayerType);
    ParameterizedItem *layer = model.insertNewItem(Constants::LayerType, multilayer->index());
    ParameterizedItem *layout = model.insertNewItem(Constants::ParticleLayoutType, layer->index());

    // composition added to layout should have abundance enabled
    ParameterizedItem *compositionFree = model.insertNewItem(Constants::ParticleCompositionType, layout->index());
    QVERIFY(compositionFree->getPropertyAttribute(ParticleItem::P_ABUNDANCE).isDisabled() == false);

    // composition added to distribution should have abundance disabled
    ParameterizedItem *distribution = model.insertNewItem(Constants::ParticleDistributionType, layout->index());
    ParameterizedItem *composition = model.insertNewItem(Constants::ParticleCompositionType, distribution->index());
    QVERIFY(composition->getPropertyAttribute(ParticleItem::P_ABUNDANCE).isDisabled() == true);

    model.removeRows(composition->index().row, 1, composition->parent()->index());
    QVERIFY(composition->getPropertyAttribute(ParticleItem::P_ABUNDANCE).isDisabled() == false);

}


#endif
