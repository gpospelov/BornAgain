#include <QtTest>
#include "RealDataModel.h"
#include "InstrumentModel.h"
#include "JobItemUtils.h"
#include "InstrumentItem.h"
#include "RealDataItem.h"
#include "IntensityDataItem.h"
#include "LinkInstrumentManager.h"
#include "RectangularDetectorItem.h"
#include "AxesItems.h"
#include <QSignalSpy>
#include <QDebug>

class TestLinkInstrument : public QObject
{
    Q_OBJECT

private slots:
    void test_linkInstrumentManager();
    void test_canLinkToInstrument();
};

//! Checks that LinkInstrumentManager listens instrument model.

inline void TestLinkInstrument::test_linkInstrumentManager()
{
    InstrumentModel instrumentModel;
    RealDataModel realDataModel;
    LinkInstrumentManager manager;
    manager.setModels(&instrumentModel, &realDataModel);

    // initial state of LinkInstrumentManager
    QCOMPARE(manager.instrumentNames(), QStringList() << "Undefined");
    QSignalSpy spy(&manager, SIGNAL(instrumentMapUpdated()));

    // populating instrument model
    InstrumentItem* instrument
        = dynamic_cast<InstrumentItem*>(instrumentModel.insertNewItem(Constants::InstrumentType));
    QString identifier = instrument->getItemValue(InstrumentItem::P_IDENTIFIER).toString();

    // checking that LinkInstrumentManager was notified about new instrument
    QCOMPARE(spy.count(), 1);
    QCOMPARE(manager.instrumentNames(), QStringList() << "Undefined" << instrument->itemName());

    QCOMPARE(manager.getInstrument(identifier), instrument);
    QCOMPARE(manager.instrumentComboIndex(identifier), 1);

    // removing instrument
    instrumentModel.removeRow(0);
    QCOMPARE(spy.count(), 2);
    QCOMPARE(manager.instrumentNames(), QStringList() << "Undefined");
    QVERIFY(manager.getInstrument(identifier) == nullptr);
    QCOMPARE(manager.instrumentComboIndex(identifier), -1);
}

inline void TestLinkInstrument::test_canLinkToInstrument()
{
    InstrumentModel instrumentModel;
    RealDataModel realDataModel;
    LinkInstrumentManager manager;
    manager.setModels(&instrumentModel, &realDataModel);

    // populating instrument model
    InstrumentItem* instrument
        = dynamic_cast<InstrumentItem*>(instrumentModel.insertNewItem(Constants::InstrumentType));
    QString identifier = instrument->getItemValue(InstrumentItem::P_IDENTIFIER).toString();

    // populating real data model, setting intensity data
    RealDataItem* realData
        = dynamic_cast<RealDataItem*>(realDataModel.insertNewItem(Constants::RealDataType));
    JobItemUtils::createDefaultDetectorMap(realData->intensityDataItem(), instrument);

    QVERIFY(manager.canLinkDataToInstrument(realData, identifier));

    // making link
    realData->setItemValue(RealDataItem::P_INSTRUMENT_ID, identifier);
    QCOMPARE(manager.linkedItems(instrument), QList<RealDataItem*>() << realData);

    // changing detector type and checking that link remain
    instrument->setDetectorGroup(Constants::RectangularDetectorType);
    QCOMPARE(manager.linkedItems(instrument), QList<RealDataItem*>() << realData);

    // changing detector binning and checking that link is destroyed
    DetectorItem* detectorItem = instrument->detectorItem();
    auto& x_axis = detectorItem->item<BasicAxisItem>(RectangularDetectorItem::P_X_AXIS);
    x_axis.setItemValue(BasicAxisItem::P_NBINS, 10);

    QCOMPARE(manager.linkedItems(instrument), QList<RealDataItem*>());
    QCOMPARE(realData->getItemValue(RealDataItem::P_INSTRUMENT_ID).toString(), QString());
}
