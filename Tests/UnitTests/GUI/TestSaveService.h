#include <QtTest>
#include "AutosaveController.h"
#include "projectdocument.h"
#include "ApplicationModels.h"
#include "InstrumentModel.h"
#include "InstrumentItem.h"
#include "RealDataModel.h"
#include "RealDataItem.h"
#include "IntensityDataItem.h"
#include "JobItemUtils.h"
#include "GUIHelpers.h"
#include "SaveService.h"
#include "ProjectUtils.h"
#include "test_utils.h"
#include <QSignalSpy>
#include <QDebug>

class TestSaveService : public QObject
{
    Q_OBJECT

private:
    // helper method to modify something in a model
    void modify_models(ApplicationModels* models)
    {
        auto instrument = models->instrumentModel()->instrumentItem();
        instrument->setItemValue(InstrumentItem::P_IDENTIFIER, GUIHelpers::createUuid());
    }

private slots:
    void test_autoSaveController();
    void test_autoSaveControllerNewDocument();
    void test_saveService();
    void test_saveServiceWithData();
    void test_autosaveEnabled();
};

//! Testing AutosaveController. It watches ProjectDocument and sends autosaveRequest() when
//! number of document changes has been accumulated.

inline void TestSaveService::test_autoSaveController()
{
    const QString projectDir("test_autoSaveController");
    TestUtils::create_dir(projectDir);

    const QString projectFileName(projectDir+"/document.pro");

    const int autosave_time(100);

    ApplicationModels models;
    std::unique_ptr<ProjectDocument> document(new ProjectDocument);
    document->setApplicationModels(&models);
    document->save(projectFileName);

    // setting up autosave
    AutosaveController autosave;
    autosave.setAutosaveTime(autosave_time);
    autosave.setDocument(document.get());

    // checking proposed autosave directory
    QCOMPARE(autosave.autosaveDir(), QString(projectDir+"/autosave"));
    QCOMPARE(autosave.autosaveName(), QString(projectDir+"/autosave/document.pro"));

    QSignalSpy spyAutosave(&autosave, SIGNAL(autosaveRequest()));

    // modify document once and check that autosave directory was created
    modify_models(&models);
    QVERIFY(document->isModified() == true);
    QVERIFY(spyAutosave.wait(autosave_time * 3.0));
    QCOMPARE(spyAutosave.count(), 1);
    QVERIFY(ProjectUtils::exists(autosave.autosaveDir()));

    // saving document and checking that autosave is not triggered
    document->save(projectFileName);
    QVERIFY(document->isModified() == false);
    QCOMPARE(spyAutosave.count(), 1);

    // modify several times and check than autosave was triggered only once
    for (size_t i = 0; i < 10; ++i)
        modify_models(&models);

    QVERIFY(spyAutosave.wait(autosave_time * 3.0));
    QCOMPARE(spyAutosave.count(), 2);

    // remove autosave dir
    autosave.removeAutosaveDir();
    QVERIFY(ProjectUtils::exists(autosave.autosaveDir()) == false);
}

//! AutosaveController shouldn't trigger autosaveRequest() if document has no name.

inline void TestSaveService::test_autoSaveControllerNewDocument()
{
    ApplicationModels models;
    std::unique_ptr<ProjectDocument> document(new ProjectDocument);
    document->setApplicationModels(&models);

    const int autosave_time(100);

    AutosaveController autosave;
    autosave.setAutosaveTime(autosave_time);
    autosave.setDocument(document.get());

    QSignalSpy spyAutosave(&autosave, SIGNAL(autosaveRequest()));

    modify_models(&models);
    QVERIFY(spyAutosave.wait(autosave_time * 3.0) == false);
    QCOMPARE(spyAutosave.count(), 0);
}

//! Testing SaveService on simple documents (no heavy data).
//! SaveService should be able to save project file and send documentSaved() signal.

inline void TestSaveService::test_saveService()
{
    const QString projectDir("test_saveService");
    TestUtils::create_dir(projectDir);
    const QString projectFileName(projectDir+"/document.pro");

    ApplicationModels models;
    std::unique_ptr<ProjectDocument> document(new ProjectDocument);
    document->setApplicationModels(&models);
    modify_models(&models);

    QVERIFY(ProjectUtils::exists(projectFileName) == false);

    SaveService service;
    QSignalSpy spySaveService(&service, SIGNAL(projectSaved()));

    service.setDocument(document.get());
    service.save(projectFileName);

    QCOMPARE(spySaveService.count(), 1);
    QVERIFY(ProjectUtils::exists(projectFileName) == true);

    // after save, document should be in non-modified state, project file name should be updated
    QCOMPARE(document->projectFileName(), projectFileName);
    QVERIFY(document->isModified() == false);

}

//! Testing SaveService on documents having nonXML data.
//! SaveService should be able to save project file (in main thread) and project nonXML
//! in second thread.

inline void TestSaveService::test_saveServiceWithData()
{
    const QString projectDir("test_saveServiceWithData");
    TestUtils::create_dir(projectDir);
    const QString projectFileName(projectDir+"/document.pro");

    ApplicationModels models;
    RealDataItem* realData = dynamic_cast<RealDataItem*>(
        models.realDataModel()->insertNewItem(Constants::RealDataType));
    Q_ASSERT(realData);
    IntensityDataItem* intensityItem = realData->intensityDataItem();
    JobItemUtils::createDefaultDetectorMap(intensityItem,
                                           models.instrumentModel()->instrumentItem());
    intensityItem->setItemValue(IntensityDataItem::P_FILE_NAME, "realdata.int.gz");

    std::unique_ptr<ProjectDocument> document(new ProjectDocument);
    document->setApplicationModels(&models);

    QVERIFY(ProjectUtils::exists(projectFileName) == false);

    SaveService service;
    QSignalSpy spySaveService(&service, SIGNAL(projectSaved()));

    service.setDocument(document.get());
    service.save(projectFileName);

    spySaveService.wait(100); // waiting saving in a thread is complete

    QCOMPARE(spySaveService.count(), 1);
    QVERIFY(ProjectUtils::exists(projectFileName) == true);
    QVERIFY(ProjectUtils::exists(projectDir+"/realdata.int.gz") == true);
    QVERIFY(document->isModified() == false);
}

//! Testing SaveService when autosave is enabled.

inline void TestSaveService::test_autosaveEnabled()
{
    const QString projectDir("test_autosaveEnabled");
    TestUtils::create_dir(projectDir);
    const QString projectFileName(projectDir+"/document.pro");

    ApplicationModels models;
    RealDataItem* realData = dynamic_cast<RealDataItem*>(
        models.realDataModel()->insertNewItem(Constants::RealDataType));
    IntensityDataItem* intensityItem = realData->intensityDataItem();
    JobItemUtils::createDefaultDetectorMap(intensityItem,
                                           models.instrumentModel()->instrumentItem());
    intensityItem->setItemValue(IntensityDataItem::P_FILE_NAME, "realdata.int.gz");

    std::unique_ptr<ProjectDocument> document(new ProjectDocument(projectFileName));
    document->setApplicationModels(&models);

    QVERIFY(document->isModified() == false);

    SaveService service;
    service.setAutosaveEnabled(true);
    const int autosave_time(100);
    service.setAutosaveTime(autosave_time);
    service.setDocument(document.get());

    QSignalSpy spySaveService(&service, SIGNAL(projectSaved()));
    service.save(projectFileName);

    spySaveService.wait(autosave_time*3); // waiting saving in a thread is complete
    QCOMPARE(spySaveService.count(), 1);
    QVERIFY(document->isModified() == false);
    QVERIFY(ProjectUtils::exists(projectDir+"/document.pro"));
    QVERIFY(ProjectUtils::exists(projectDir+"/realdata.int.gz"));

    // modify several times and check SaveService signals
    for (size_t i = 0; i < 10; ++i)
        modify_models(&models);

    QVERIFY(document->isModified() == true);

    spySaveService.wait(autosave_time*3); // waiting saving in a thread is complete
    QCOMPARE(spySaveService.count(), 2);

    QVERIFY(ProjectUtils::exists(projectDir+"/autosave/document.pro"));
    QVERIFY(ProjectUtils::exists(projectDir+"/autosave/realdata.int.gz"));

    // after autosave the project has to be still in modified state
    QVERIFY(document->isModified() == true);
    // after autosave, project file name should remain the same
    QCOMPARE(document->projectFileName(), projectFileName);
}
