#include "google_test.h"
#include "ApplicationModels.h"
#include "DataItem.h"
#include "DataItemView.h"
#include "GUIHelpers.h"
#include "MessageService.h"
#include "projectdocument.h"
#include "RealDataModel.h"
#include "SessionModel.h"
#include "test_utils.h"

class TestDataItemViews : public ::testing::Test
{
public:
    ~TestDataItemViews();

    DataItem* insertNewDataItem(SessionModel& model, double val);
};

TestDataItemViews::~TestDataItemViews() = default;

DataItem* TestDataItemViews::insertNewDataItem(SessionModel& model, double val)
{
    DataItem* item = dynamic_cast<DataItem*>(model.insertNewItem(Constants::SpecularDataType));
    auto data = TestUtils::createData(val, TestUtils::DIM::D1);
    item->setOutputData(data.release());
    return item;
}

TEST_F(TestDataItemViews, testDataLinking)
{
    SessionModel model("TempModel");
    auto view_item = dynamic_cast<DataItemView*>(model.insertNewItem(Constants::DataItem1DViewType));
    DataItem* item = insertNewDataItem(model, 0.0);
    EXPECT_TRUE(view_item->addItem(item));

    auto stored_items = view_item->dataItems();
    EXPECT_EQ(stored_items.size(), 1u);
    EXPECT_EQ(stored_items[0], item);
}

TEST_F(TestDataItemViews, testLinkingSeveralItems)
{
    SessionModel model("TempModel");
    auto view_item = dynamic_cast<DataItemView*>(model.insertNewItem(Constants::DataItem1DViewType));
    DataItem* item = insertNewDataItem(model, 0.0);
    DataItem* item2 = insertNewDataItem(model, 1.0);
    DataItem* item3 = insertNewDataItem(model, 2.0);
    EXPECT_TRUE(view_item->addItem(item));
    EXPECT_TRUE(view_item->addItem(item2));
    EXPECT_TRUE(view_item->addItem(item3));

    auto stored_items = view_item->dataItems();
    EXPECT_EQ(stored_items.size(), 3u);
    EXPECT_EQ(stored_items[0], item);
    EXPECT_EQ(stored_items[1], item2);
    EXPECT_EQ(stored_items[2], item3);
}

TEST_F(TestDataItemViews, testBrokenLink)
{
    SessionModel model("TempModel");
    auto view_item = dynamic_cast<DataItemView*>(model.insertNewItem(Constants::DataItem1DViewType));
    DataItem* item = insertNewDataItem(model, 0.0);
    EXPECT_TRUE(view_item->addItem(item));

    auto stored_items = view_item->dataItems();
    EXPECT_EQ(stored_items.size(), 1u);
    EXPECT_EQ(stored_items[0], item);

    DataItem* item2 = insertNewDataItem(model, 1.0);
    EXPECT_TRUE(view_item->addItem(item2));
    EXPECT_THROW(view_item->dataItems(), GUIHelpers::Error);
}

TEST_F(TestDataItemViews, testWrongHostingModel)
{
    SessionModel model("TempModel");
    DataItem* item = insertNewDataItem(model, 0.0);
    auto view_item = dynamic_cast<DataItemView*>(model.insertNewItem(Constants::DataItem1DViewType));
    EXPECT_TRUE(view_item->addItem(item));

    SessionModel model2("TempModel2");
    DataItem* item2 = insertNewDataItem(model2, 1.0);
    EXPECT_FALSE(view_item->addItem(item2));

    auto stored_items = view_item->dataItems();
    EXPECT_EQ(stored_items.size(), 1u);
    EXPECT_EQ(stored_items[0], item);
}

TEST_F(TestDataItemViews, testSavingLinkedData)
{
    const QString projectDir("test_savingLinkedData");
    TestUtils::create_dir(projectDir);
    const QString projectFileName(projectDir + "/document.pro");
    {
        ApplicationModels models;
        ProjectDocument document;

        SessionModel* real_data_model = models.realDataModel();
        DataItem* item = insertNewDataItem(*real_data_model, 0.0);
        DataItem* item2 = insertNewDataItem(*real_data_model, 1.0);
        auto view_item = dynamic_cast<DataItemView*>(
            real_data_model->insertNewItem(Constants::DataItem1DViewType));
        view_item->addItem(item);
        view_item->addItem(item2);

        document.setApplicationModels(&models);
        document.save(projectFileName);
    }

    ApplicationModels models;
    MessageService message_service;
    ProjectDocument document;
    document.setApplicationModels(&models);
    document.setLogger(&message_service);
    document.load(projectFileName);

    SessionModel* real_data_model = models.realDataModel();
    auto view_item = real_data_model->topItem<DataItemView>();
    EXPECT_TRUE(view_item);

    auto linked_items = view_item->dataItems();
    auto model_items = real_data_model->topItems<DataItem>();
    EXPECT_EQ(linked_items.size(), 2u);
    EXPECT_EQ(model_items.size(), 2);
    for (auto item : model_items) {
        auto data_item = dynamic_cast<DataItem*>(item);
        EXPECT_TRUE(data_item);
        EXPECT_TRUE(data_item == linked_items[0] || data_item == linked_items[1]);
    }
}
