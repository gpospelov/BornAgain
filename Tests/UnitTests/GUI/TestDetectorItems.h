#include <QtTest>
#include "RectangularDetectorItem.h"
#include "InstrumentModel.h"
#include "ComboProperty.h"
#include "InstrumentItem.h"
#include "DetectorItems.h"
#include "ConvolutionDetectorResolution.h"
#include "ResolutionFunction2DGaussian.h"
#include "IDetector2D.h"
#include "Units.h"

class TestDetectorItems : public QObject {
    Q_OBJECT

private slots:
    void test_detectorAlignment();
    void test_resolutionFunction();
};

inline void TestDetectorItems::test_detectorAlignment()
{
    InstrumentModel model;
    SessionItem* detector = model.insertNewItem(Constants::RectangularDetectorType);

    ComboProperty alignment
        = detector->getItemValue(RectangularDetectorItem::P_ALIGNMENT).value<ComboProperty>();
    // generic has some more items visible
    alignment.setValue(Constants::ALIGNMENT_GENERIC);
    detector->setItemValue(RectangularDetectorItem::P_ALIGNMENT,
                           QVariant::fromValue<ComboProperty>(alignment));
    QVERIFY(detector->getItem(RectangularDetectorItem::P_NORMAL)->isVisible());

    // should be disabled if we switch
    alignment.setValue(Constants::ALIGNMENT_TO_REFLECTED_BEAM);
    detector->setItemValue(RectangularDetectorItem::P_ALIGNMENT,
                           QVariant::fromValue<ComboProperty>(alignment));
    QVERIFY(detector->getItem(RectangularDetectorItem::P_NORMAL)->isVisible() == false);
}

inline void TestDetectorItems::test_resolutionFunction()
{
    InstrumentModel model;
    InstrumentItem* instrument = dynamic_cast<InstrumentItem*>(
                model.insertNewItem(Constants::InstrumentType));

    DetectorItem *detectorItem = instrument->detectorItem();

    detectorItem->setGroupProperty(DetectorItem::P_RESOLUTION_FUNCTION,
                                   Constants::ResolutionFunction2DGaussianType);

    auto detector = detectorItem->createDetector();

    auto convol = dynamic_cast<const ConvolutionDetectorResolution*>(detector->detectorResolution());

    auto gaussian = dynamic_cast<const ResolutionFunction2DGaussian*>(convol->getResolutionFunction2D());


    QCOMPARE(Units::rad2deg(gaussian->getSigmaX()), 0.02);


}
