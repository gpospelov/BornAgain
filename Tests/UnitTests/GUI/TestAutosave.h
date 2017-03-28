#include <QtTest>
#include "AutosaveService.h"
#include "projectdocument.h"
#include "ApplicationModels.h"
#include "InstrumentModel.h"
#include "InstrumentItem.h"
#include "RealDataModel.h"
#include "RealDataItem.h"
#include "IntensityDataItem.h"
#include "JobItemUtils.h"
#include "GUIHelpers.h"
#include <QSignalSpy>
#include <QDebug>

class TestAutosave : public QObject
{
    Q_OBJECT

private slots:
    // helper method to modify something in a model
    void modify_models(ApplicationModels* models)
    {
        auto instrument = models->instrumentModel()->instrumentItem();
        instrument->setItemValue(InstrumentItem::P_IDENTIFIER, GUIHelpers::createUuid());
    }

    void test_autoSave();
    void test_autoSaveIncludingData();
};

inline void TestAutosave::test_autoSave()
{
    const int autosave_time(100);
    ApplicationModels models;

    // Preparing place for project
    const QString projectDir("test_autoSave");
    const QString projectFileName("test_autoSave/document.pro");
    GUIHelpers::createSubdir(".", projectDir);

    ProjectDocument* document = new ProjectDocument;
    document->setApplicationModels(&models);
    document->save(projectFileName);

    // Setting up autosave
    AutosaveService autosave;
    autosave.setAutosaveTime(autosave_time);
    autosave.setDocument(document);

    QCOMPARE(autosave.autosaveDir(), QString("test_autoSave/autosave"));
    QCOMPARE(autosave.autosaveName(), QString("test_autoSave/autosave/document.pro"));

    QDir autosaveDir(autosave.autosaveDir());
    QVERIFY(autosaveDir.exists());

    QSignalSpy spyAutosave(&autosave, SIGNAL(autosaved()));

    // modify document once and check
    modify_models(&models);
    QVERIFY(document->isModified() == true);
    QVERIFY(spyAutosave.wait(autosave_time * 1.5));
    QCOMPARE(spyAutosave.count(), 1);

    // saving document and checking that autosave is not triggered
    document->save(projectFileName);
    QVERIFY(document->isModified() == false);
    QCOMPARE(spyAutosave.count(), 1);

    // modify several times and check
    for (size_t i = 0; i < 10; ++i)
        modify_models(&models);

    QVERIFY(spyAutosave.wait(autosave_time * 1.5));
    QCOMPARE(spyAutosave.count(), 2);

    // remove autosave dir
    autosave.removeAutosaveDir();
    QVERIFY(autosaveDir.exists() == false);
}

inline void TestAutosave::test_autoSaveIncludingData()
{
    const int autosave_time(100);
    ApplicationModels models;

    RealDataItem* realData = dynamic_cast<RealDataItem*>(
        models.realDataModel()->insertNewItem(Constants::RealDataType));
    Q_ASSERT(realData);
    IntensityDataItem* intensityItem = realData->intensityDataItem();
    JobItemUtils::createDefaultDetectorMap(intensityItem,
                                           models.instrumentModel()->instrumentItem());
    intensityItem->setItemValue(IntensityDataItem::P_FILE_NAME, "realdata.int.gz");

    const QString projectDir("test_autoSave");
    const QString projectFileName("test_autoSave/document.pro");
    GUIHelpers::createSubdir(".", projectDir);

    ProjectDocument* document = new ProjectDocument;
    document->setApplicationModels(&models);
    document->save(projectFileName);

    // Setting up auto save
    AutosaveService autosave;
    autosave.setAutosaveTime(autosave_time);
    autosave.setDocument(document);

    QSignalSpy spyAutosave(&autosave, SIGNAL(autosaved()));

    // modify document once and check
    modify_models(&models);
    QVERIFY(spyAutosave.wait(autosave_time * 1.5));
    QCOMPARE(spyAutosave.count(), 1);

    QFileInfo info("test_autoSave/autosave/document.pro");
    QVERIFY(info.exists());

    info.setFile("test_autoSave/autosave/realdata.int.gz");
    QVERIFY(info.exists());
}
