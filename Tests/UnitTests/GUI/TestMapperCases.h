#include "SampleModel.h"
#include "ParticleItem.h"
#include "ParticleLayoutItem.h"
#include "ComboProperty.h"
#include "DocumentModel.h"
#include "SimulationOptionsItem.h"
#include <QtTest>

class TestMapperCases : public QObject
{
    Q_OBJECT

private slots:
    void test_ParticeleCompositionUpdate();
    void test_SimulationOptionsComputationToggle();
};

inline void TestMapperCases::test_ParticeleCompositionUpdate()
{
    SampleModel model;
    SessionItem* multilayer = model.insertNewItem(Constants::MultiLayerType);
    SessionItem* layer = model.insertNewItem(Constants::LayerType, multilayer->index());
    SessionItem* layout = model.insertNewItem(Constants::ParticleLayoutType, layer->index());

    // composition added to layout should have abundance enabled
    SessionItem* compositionFree
        = model.insertNewItem(Constants::ParticleCompositionType, layout->index());
    QVERIFY(compositionFree->getItem(ParticleItem::P_ABUNDANCE)->isEnabled());

    // composition added to distribution should have abundance disabled
    SessionItem* distribution
        = model.insertNewItem(Constants::ParticleDistributionType, layout->index());
    SessionItem* composition
        = model.insertNewItem(Constants::ParticleCompositionType, distribution->index());
    QVERIFY(composition->getItem(ParticleItem::P_ABUNDANCE)->isEnabled() == false);

    composition = distribution->takeRow(composition->parentRow());
    QVERIFY(composition->getItem(ParticleItem::P_ABUNDANCE)->isEnabled());
    delete composition;
}

inline void TestMapperCases::test_SimulationOptionsComputationToggle()
{
    DocumentModel model;
    model.insertNewItem(Constants::SimulationOptionsType);

    SimulationOptionsItem* item = model.getSimulationOptionsItem();

    ComboProperty combo
        = item->getItemValue(SimulationOptionsItem::P_COMPUTATION_METHOD).value<ComboProperty>();
    QCOMPARE(combo.getValue(), Constants::SIMULATION_ANALYTICAL);
    QVERIFY(item->getItem(SimulationOptionsItem::P_MC_POINTS)->isEnabled() == false);

    combo.setValue(Constants::SIMULATION_MONTECARLO);
    item->setItemValue(SimulationOptionsItem::P_COMPUTATION_METHOD, combo.getVariant());
    QVERIFY(item->getItem(SimulationOptionsItem::P_MC_POINTS)->isEnabled() == true);
}
