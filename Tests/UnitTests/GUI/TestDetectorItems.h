#include <QtTest>
#include "RectangularDetectorItem.h"
#include "InstrumentModel.h"
#include "ComboProperty.h"

class TestDetectorItems : public QObject {
    Q_OBJECT

private slots:
    void test_detectorAlignment();
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
