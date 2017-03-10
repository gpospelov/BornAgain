#include "SessionItem.h"
#include "SampleModel.h"
#include "InstrumentModel.h"
#include "item_constants.h"
#include "ParticleItem.h"
#include "ParticleCompositionItem.h"
#include "InterferenceFunctionItems.h"
#include "ParticleLayoutItem.h"
#include "DetectorItems.h"
#include "SphericalDetectorItem.h"
#include "RectangularDetectorItem.h"
#include "ComboProperty.h"
#include "DocumentModel.h"
#include "SimulationOptionsItem.h"
#include "Lattice2DItems.h"
#include <memory>
#include <QtTest>

class TestMapperCases : public QObject {
    Q_OBJECT

private slots:
    void test_ParticeleCompositionUpdate();
    void test_instrumentAlignmentPropertyVisibility();
//    void test_removeMaskOnDetectorChange();
    void test_SimulationOptionsComputationToggle();
};

inline void TestMapperCases::test_ParticeleCompositionUpdate()
{
    SampleModel model;
    SessionItem *multilayer = model.insertNewItem(Constants::MultiLayerType);
    SessionItem *layer = model.insertNewItem(Constants::LayerType, multilayer->index());
    SessionItem *layout = model.insertNewItem(Constants::ParticleLayoutType, layer->index());

    // composition added to layout should have abundance enabled
    SessionItem *compositionFree = model.insertNewItem(Constants::ParticleCompositionType, layout->index());
    QVERIFY(compositionFree->getItem(ParticleItem::P_ABUNDANCE)->isEnabled());

    // composition added to distribution should have abundance disabled
    SessionItem *distribution = model.insertNewItem(Constants::ParticleDistributionType, layout->index());
    SessionItem *composition = model.insertNewItem(Constants::ParticleCompositionType, distribution->index());
    QVERIFY(composition->getItem(ParticleItem::P_ABUNDANCE)->isEnabled() == false);

    composition = distribution->takeRow(composition->parentRow());
    QVERIFY(composition->getItem(ParticleItem::P_ABUNDANCE)->isEnabled());
    delete composition;

}

inline void TestMapperCases::test_instrumentAlignmentPropertyVisibility()
{
    InstrumentModel model;
    SessionItem *instrument = model.insertNewItem(Constants::InstrumentType);
    SessionItem *detector = model.insertNewItem(Constants::DetectorContainerType, instrument->index());
    detector->setGroupProperty(DetectorContainerItem::P_DETECTOR, Constants::RectangularDetectorType);
    SessionItem *rectangular = detector->getGroupItem(DetectorContainerItem::P_DETECTOR);


    ComboProperty alignment = rectangular->getItemValue(RectangularDetectorItem::P_ALIGNMENT)
            .value<ComboProperty>();
    // generic has some more items visible
    alignment.setValue(Constants::ALIGNMENT_GENERIC);
    rectangular->setItemValue(RectangularDetectorItem::P_ALIGNMENT, QVariant::fromValue<ComboProperty>(alignment));
    QVERIFY(rectangular->getItem(RectangularDetectorItem::P_NORMAL)->isVisible());

    // should be disabled if we switch
    alignment.setValue(Constants::ALIGNMENT_TO_REFLECTED_BEAM);
    rectangular->setItemValue(RectangularDetectorItem::P_ALIGNMENT, QVariant::fromValue<ComboProperty>(alignment));
    QVERIFY(rectangular->getItem(RectangularDetectorItem::P_NORMAL)->isVisible() == false);

}

//inline void TestMapperCases::test_removeMaskOnDetectorChange()
//{
//    InstrumentModel model;
//    SessionItem *instrument = model.insertNewItem(Constants::InstrumentType);
//    SessionItem *detector = model.insertNewItem(Constants::DetectorContainerType, instrument->index());
//    detector->setGroupProperty(DetectorContainerItem::P_DETECTOR, Constants::RectangularDetectorType);
//    model.insertNewItem(Constants::MaskContainerType, detector->index());
//    QVERIFY(detector->getItems(DetectorContainerItem::T_MASKS).size() == 1);
//    // after change the mask container should be removed
//    detector->setGroupProperty(DetectorContainerItem::P_DETECTOR, Constants::SphericalDetectorType);
//    QVERIFY(detector->getItems(DetectorContainerItem::T_MASKS).size() == 0);
//}

inline void TestMapperCases::test_SimulationOptionsComputationToggle()
{
    DocumentModel model;
    model.insertNewItem(Constants::SimulationOptionsType);

    SimulationOptionsItem *item = model.getSimulationOptionsItem();

    ComboProperty combo = item->getItemValue(SimulationOptionsItem::P_COMPUTATION_METHOD).value<ComboProperty>();
    QCOMPARE(combo.getValue(), Constants::SIMULATION_ANALYTICAL);
    QVERIFY(item->getItem(SimulationOptionsItem::P_MC_POINTS)->isEnabled() == false);

    combo.setValue(Constants::SIMULATION_MONTECARLO);
    item->setItemValue(SimulationOptionsItem::P_COMPUTATION_METHOD, combo.getVariant());
    QVERIFY(item->getItem(SimulationOptionsItem::P_MC_POINTS)->isEnabled() == true);
}
