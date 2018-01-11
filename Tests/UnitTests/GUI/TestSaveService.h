#include "google_test.h"
#include "ApplicationModels.h"
#include "AutosaveController.h"
#include "GUIHelpers.h"
#include "InstrumentItems.h"
#include "InstrumentModel.h"
#include "IntensityDataItem.h"
#include "JobItemUtils.h"
#include "ProjectUtils.h"
#include "RealDataItem.h"
#include "RealDataModel.h"
#include "SaveService.h"
#include "projectdocument.h"
#include "test_utils.h"
#include <QSignalSpy>

class TestSaveService : public ::testing::Test
{
public:
    ~TestSaveService();

    // helper method to modify something in a model
    void modify_models(ApplicationModels* models)
    {
        auto instrument = models->instrumentModel()->instrumentItem();
        instrument->setItemValue(InstrumentItem::P_IDENTIFIER, GUIHelpers::createUuid());
    }
};

TestSaveService::~TestSaveService() = default;

//! Testing AutosaveController. It watches ProjectDocument and sends autosaveRequest() when
//! number of document changes has been accumulated.

TEST_F(TestSaveService, test_autoSaveController)
{
    const QString projectDir("test_autoSaveController");
    TestUtils::create_dir(projectDir);

    const QString projectFileName(projectDir + "/document.pro");

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
    EXPECT_EQ(autosave.autosaveDir(), QString(projectDir + "/autosave"));
    EXPECT_EQ(autosave.autosaveName(), QString(projectDir + "/autosave/document.pro"));

    QSignalSpy spyAutosave(&autosave, SIGNAL(autosaveRequest()));

    // modify document once and check that autosave directory was created
    modify_models(&models);
    EXPECT_TRUE(document->isModified());
    EXPECT_TRUE(spyAutosave.wait(autosave_time * 3));
    EXPECT_EQ(spyAutosave.count(), 1);
    EXPECT_TRUE(ProjectUtils::exists(autosave.autosaveDir()));

    // saving document and checking that autosave is not triggered
    document->save(projectFileName);
    EXPECT_FALSE(document->isModified());
    EXPECT_EQ(spyAutosave.count(), 1);

    // modify several times and check than autosave was triggered only once
    for (size_t i = 0; i < 10; ++i)
        modify_models(&models);

    EXPECT_TRUE(spyAutosave.wait(autosave_time * 3));
    EXPECT_EQ(spyAutosave.count(), 2);

    // remove autosave dir
    autosave.removeAutosaveDir();
    EXPECT_FALSE(ProjectUtils::exists(autosave.autosaveDir()));
}

//! AutosaveController shouldn't trigger autosaveRequest() if document has no name.

TEST_F(TestSaveService, test_autoSaveControllerNewDocument)
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
    EXPECT_FALSE(spyAutosave.wait(autosave_time * 3));
    EXPECT_EQ(spyAutosave.count(), 0);
}

//! Testing SaveService on simple documents (no heavy data).
//! SaveService should be able to save project file and send documentSaved() signal.

TEST_F(TestSaveService, test_saveService)
{
    const QString projectDir("test_saveService");
    TestUtils::create_dir(projectDir);
    const QString projectFileName(projectDir + "/document.pro");

    ApplicationModels models;
    std::unique_ptr<ProjectDocument> document(new ProjectDocument);
    document->setApplicationModels(&models);
    modify_models(&models);

    EXPECT_FALSE(ProjectUtils::exists(projectFileName));

    SaveService service;
    QSignalSpy spySaveService(&service, SIGNAL(projectSaved()));

    service.setDocument(document.get());
    service.save(projectFileName);

    EXPECT_EQ(spySaveService.count(), 1);
    EXPECT_TRUE(ProjectUtils::exists(projectFileName));

    // after save, document should be in non-modified state, project file name should be updated
    EXPECT_EQ(document->projectFileName(), projectFileName);
    EXPECT_FALSE(document->isModified());
}

//! Testing SaveService on documents having nonXML data.
//! SaveService should be able to save project file (in main thread) and project nonXML
//! in second thread.

TEST_F(TestSaveService, test_saveServiceWithData)
{
    const QString projectDir("test_saveServiceWithData");
    TestUtils::create_dir(projectDir);
    const QString projectFileName(projectDir + "/document.pro");

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

    EXPECT_FALSE(ProjectUtils::exists(projectFileName));

    SaveService service;
    QSignalSpy spySaveService(&service, SIGNAL(projectSaved()));

    service.setDocument(document.get());
    service.save(projectFileName);

    spySaveService.wait(100); // waiting saving in a thread is complete

    EXPECT_EQ(spySaveService.count(), 1);
    EXPECT_TRUE(ProjectUtils::exists(projectFileName));
    EXPECT_TRUE(ProjectUtils::exists(projectDir + "/realdata.int.gz"));
    EXPECT_FALSE(document->isModified());
}

//! Testing SaveService when autosave is enabled.

TEST_F(TestSaveService, test_autosaveEnabled)
{
    const QString projectDir("test_autosaveEnabled");
    TestUtils::create_dir(projectDir);
    const QString projectFileName(projectDir + "/document.pro");

    ApplicationModels models;
    RealDataItem* realData = dynamic_cast<RealDataItem*>(
        models.realDataModel()->insertNewItem(Constants::RealDataType));
    IntensityDataItem* intensityItem = realData->intensityDataItem();
    JobItemUtils::createDefaultDetectorMap(intensityItem,
                                           models.instrumentModel()->instrumentItem());
    intensityItem->setItemValue(IntensityDataItem::P_FILE_NAME, "realdata.int.gz");

    std::unique_ptr<ProjectDocument> document(new ProjectDocument(projectFileName));
    document->setApplicationModels(&models);

    EXPECT_FALSE(document->isModified());

    SaveService service;
    service.setAutosaveEnabled(true);
    const int autosave_time(100);
    service.setAutosaveTime(autosave_time);
    service.setDocument(document.get());

    QSignalSpy spySaveService(&service, SIGNAL(projectSaved()));
    service.save(projectFileName);

    spySaveService.wait(autosave_time * 3); // waiting saving in a thread is complete
    EXPECT_EQ(spySaveService.count(), 1);
    EXPECT_FALSE(document->isModified());
    EXPECT_TRUE(ProjectUtils::exists(projectDir + "/document.pro"));
    EXPECT_TRUE(ProjectUtils::exists(projectDir + "/realdata.int.gz"));

    // modify several times and check SaveService signals
    for (size_t i = 0; i < 10; ++i)
        modify_models(&models);

    EXPECT_TRUE(document->isModified());

    spySaveService.wait(autosave_time * 3); // waiting saving in a thread is complete
    EXPECT_EQ(spySaveService.count(), 2);

    EXPECT_TRUE(ProjectUtils::exists(projectDir + "/autosave/document.pro"));
    EXPECT_TRUE(ProjectUtils::exists(projectDir + "/autosave/realdata.int.gz"));

    // after autosave the project has to be still in modified state
    EXPECT_TRUE(document->isModified());
    // after autosave, project file name should remain the same
    EXPECT_EQ(document->projectFileName(), projectFileName);
}
