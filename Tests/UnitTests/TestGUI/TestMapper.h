#ifndef TESTMAPPER_H
#define TESTMAPPER_H

#include "ParameterizedItem.h"
#include "SampleModel.h"
#include "InstrumentModel.h"
#include "item_constants.h"
#include "ParticleItem.h"
#include "ParticleCompositionItem.h"
#include "ParticleDistributionItem.h"
#include "InterferenceFunctionItems.h"
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
    ParameterizedItem *multilayer = model.insertNewItem(Constants::MultiLayerType);
    ParameterizedItem *layer = model.insertNewItem(Constants::LayerType, multilayer->index());
    ParameterizedItem *layout = model.insertNewItem(Constants::ParticleLayoutType, layer->index());

    // composition added to layout should have abundance enabled
    ParameterizedItem *compositionFree = model.insertNewItem(Constants::ParticleCompositionType, layout->index());
    QVERIFY(compositionFree->getItem(ParticleItem::P_ABUNDANCE)->isEnabled());

    // composition added to distribution should have abundance disabled
    ParameterizedItem *distribution = model.insertNewItem(Constants::ParticleDistributionType, layout->index());
    ParameterizedItem *composition = model.insertNewItem(Constants::ParticleCompositionType, distribution->index());
    QVERIFY(composition->getItem(ParticleItem::P_ABUNDANCE)->isEnabled() == false);

    model.removeRows(composition->index().row(), 1, composition->parent()->index());
    QVERIFY(composition->getItem(ParticleItem::P_ABUNDANCE)->isEnabled());

}

inline void TestMapper::test_Inference2DRotationAngleToggle()
{
    SampleModel model;
    ParameterizedItem *multilayer = model.insertNewItem(Constants::MultiLayerType);
    ParameterizedItem *layer = model.insertNewItem(Constants::LayerType, multilayer->index());
    ParameterizedItem *layout = model.insertNewItem(Constants::ParticleLayoutType, layer->index());

    ParameterizedItem *inference = model.insertNewItem(Constants::InterferenceFunction2DParaCrystalType, layout->index());

    // rotation (xi) should be disabled if integration is on
    inference->setRegisteredProperty(InterferenceFunction2DParaCrystalItem::P_XI_INTEGRATION, true);
    QVERIFY(inference->getItem(InterferenceFunction2DParaCrystalItem::P_ROTATION_ANGLE)->isEnabled() == false);

    // rotation (xi) should be enabled if integration is off
    inference->setRegisteredProperty(InterferenceFunction2DParaCrystalItem::P_XI_INTEGRATION, false);
    QVERIFY(!inference->getItem(InterferenceFunction2DParaCrystalItem::P_ROTATION_ANGLE)->isEnabled() == false);

}

inline void TestMapper::test_instrumentAlignmentPropertyVisibility()
{
    InstrumentModel model;
    ParameterizedItem *instrument = model.insertNewItem(Constants::InstrumentType);
    ParameterizedItem *detector = model.insertNewItem(Constants::DetectorType, instrument->index());
    detector->setGroupProperty(DetectorItem::P_DETECTOR, Constants::RectangularDetectorType);
    ParameterizedItem *rectangular = detector->getGroupItem(DetectorItem::P_DETECTOR);


    ComboProperty alignment = rectangular->getRegisteredProperty(RectangularDetectorItem::P_ALIGNMENT)
            .value<ComboProperty>();
    // generic has some more items visible
    alignment.setValue(Constants::ALIGNMENT_GENERIC);
    rectangular->setRegisteredProperty(RectangularDetectorItem::P_ALIGNMENT, QVariant::fromValue<ComboProperty>(alignment));
    QVERIFY(rectangular->getItem(RectangularDetectorItem::P_NORMAL)->isVisible());

    // should be disabled if we switch
    alignment.setValue(Constants::ALIGNMENT_TO_REFLECTED_BEAM);
    rectangular->setRegisteredProperty(RectangularDetectorItem::P_ALIGNMENT, QVariant::fromValue<ComboProperty>(alignment));
    QVERIFY(rectangular->getItem(RectangularDetectorItem::P_NORMAL)->isVisible() == false);

}

inline void TestMapper::test_removeMaskOnDetectorChange()
{
    InstrumentModel model;
    ParameterizedItem *instrument = model.insertNewItem(Constants::InstrumentType);
    ParameterizedItem *detector = model.insertNewItem(Constants::DetectorType, instrument->index());
    detector->setGroupProperty(DetectorItem::P_DETECTOR, Constants::RectangularDetectorType);
    model.insertNewItem(Constants::MaskContainerType, detector->index());
    QVERIFY(detector->getUnregisteredChildren().size() == 1);
    // after change the mask container should be removed
    detector->setGroupProperty(DetectorItem::P_DETECTOR, Constants::SphericalDetectorType);
    QVERIFY(detector->getUnregisteredChildren().size() == 0);

}

#endif
