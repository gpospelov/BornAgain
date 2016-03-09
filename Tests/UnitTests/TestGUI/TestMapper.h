#ifndef TESTMAPPER_H
#define TESTMAPPER_H

#include "SessionItem.h"
#include "SampleModel.h"
#include "InstrumentModel.h"
#include "item_constants.h"
#include "ParticleItem.h"
#include "ParticleCompositionItem.h"
#include "ParticleDistributionItem.h"
#include "InterferenceFunctionItems.h"
#include "ParticleLayoutItem.h"
#include "DetectorItems.h"
#include "ComboProperty.h"
#include <memory>
#include <QtTest>

class TestMapper : public QObject {
    Q_OBJECT

private slots:
    void test_ParticeleCompositionUpdate();
    void test_Inference2DRotationAngleToggle();
    void test_instrumentAlignmentPropertyVisibility();
    void test_removeMaskOnDetectorChange();
};

inline void TestMapper::test_ParticeleCompositionUpdate()
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

inline void TestMapper::test_Inference2DRotationAngleToggle()
{
    SampleModel model;
    SessionItem *multilayer = model.insertNewItem(Constants::MultiLayerType);
    SessionItem *layer = model.insertNewItem(Constants::LayerType, multilayer->index());
    SessionItem *layout = model.insertNewItem(Constants::ParticleLayoutType, layer->index());

    SessionItem *inference = model.insertNewItem(Constants::InterferenceFunction2DParaCrystalType,
                                                       layout->index(), -1, ParticleLayoutItem::T_INTERFERENCE);

    // rotation (xi) should be disabled if integration is on
    inference->setItemValue(InterferenceFunction2DParaCrystalItem::P_XI_INTEGRATION, true);
    QVERIFY(inference->getItem(InterferenceFunction2DParaCrystalItem::P_ROTATION_ANGLE)->isEnabled() == false);

    // rotation (xi) should be enabled if integration is off
    inference->setItemValue(InterferenceFunction2DParaCrystalItem::P_XI_INTEGRATION, false);
    QVERIFY(!inference->getItem(InterferenceFunction2DParaCrystalItem::P_ROTATION_ANGLE)->isEnabled() == false);

}

inline void TestMapper::test_instrumentAlignmentPropertyVisibility()
{
    InstrumentModel model;
    SessionItem *instrument = model.insertNewItem(Constants::InstrumentType);
    SessionItem *detector = model.insertNewItem(Constants::DetectorType, instrument->index());
    detector->setGroupProperty(DetectorItem::P_DETECTOR, Constants::RectangularDetectorType);
    SessionItem *rectangular = detector->getGroupItem(DetectorItem::P_DETECTOR);


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

inline void TestMapper::test_removeMaskOnDetectorChange()
{
    InstrumentModel model;
    SessionItem *instrument = model.insertNewItem(Constants::InstrumentType);
    SessionItem *detector = model.insertNewItem(Constants::DetectorType, instrument->index());
    detector->setGroupProperty(DetectorItem::P_DETECTOR, Constants::RectangularDetectorType);
    model.insertNewItem(Constants::MaskContainerType, detector->index());
    QVERIFY(detector->getItems(DetectorItem::T_MASKS).size() == 1);
    // after change the mask container should be removed
    detector->setGroupProperty(DetectorItem::P_DETECTOR, Constants::SphericalDetectorType);
    QVERIFY(detector->getItems(DetectorItem::T_MASKS).size() == 0);

}

#endif
