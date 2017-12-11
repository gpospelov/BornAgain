#include "InstrumentModel.h"
#include "JobItem.h"
#include "JobModel.h"
#include "MaterialModel.h"
#include "SampleModel.h"
#include "SessionModel.h"
#include "google_test.h"
#include <QXmlStreamWriter>
#include <QSignalSpy>
#include <memory>

class TestSessionModel : public ::testing::Test
{
public:
    ~TestSessionModel();
};

TestSessionModel::~TestSessionModel() = default;

//! Testing SessionModel::setData notifications.

TEST_F(TestSessionModel, setData)
{
    SessionModel model("TestModel");
    auto item = model.insertNewItem(Constants::PropertyType);

    QSignalSpy spy(&model, &SessionModel::dataChanged);

    QVariant data(42.0);

    // setting the data and checking that signal was emmitted only once
    EXPECT_TRUE(model.setData(model.indexOfItem(item), data, Qt::DisplayRole));
    EXPECT_EQ(spy.count(), 1);
    EXPECT_EQ(item->value().toDouble(), 42.0);
    QList<QVariant> arguments = spy.takeFirst();
    EXPECT_EQ(arguments.at(0).toModelIndex(), model.indexOfItem(item));

    // setting the same data second time
    EXPECT_FALSE(model.setData(model.indexOfItem(item), data, Qt::DisplayRole));
    EXPECT_EQ(spy.count(), 0);

    // setting another data
    EXPECT_TRUE(model.setData(model.indexOfItem(item), QVariant(43.0), Qt::DisplayRole));
    EXPECT_EQ(spy.count(), 1);
}

TEST_F(TestSessionModel, test_SampleModel_CreateCopy)
{
    std::unique_ptr<MaterialModel> P_materialModel(new MaterialModel());

    SampleModel model1;
    SessionItem* multilayer = model1.insertNewItem(Constants::MultiLayerType);
    multilayer->setItemName("multilayer");
    model1.insertNewItem(Constants::LayerType, model1.indexOfItem(multilayer));
    SessionItem* multilayer2 = model1.insertNewItem(Constants::MultiLayerType);
    multilayer2->setItemName("multilayer2");

    QString buffer1;
    QXmlStreamWriter writer1(&buffer1);
    model1.writeTo(&writer1);

    std::unique_ptr<SampleModel> model2(model1.createCopy());
    QString buffer2;
    QXmlStreamWriter writer2(&buffer2);
    model2->writeTo(&writer2);

    EXPECT_EQ(buffer1, buffer2);
}

TEST_F(TestSessionModel, test_SampleModel_CreatePartialCopy)
{
    std::unique_ptr<MaterialModel> P_materialModel(new MaterialModel());

    SampleModel model1;
    SessionItem* multilayer1 = model1.insertNewItem(Constants::MultiLayerType);
    multilayer1->setItemName("multilayer1");
    model1.insertNewItem(Constants::LayerType, model1.indexOfItem(multilayer1));

    SessionItem* multilayer2 = model1.insertNewItem(Constants::MultiLayerType);
    multilayer2->setItemName("multilayer2");

    std::unique_ptr<SampleModel> model2(model1.createCopy(multilayer1));
    SessionItem* result = model2->itemForIndex(model2->index(0, 0, QModelIndex()));

    EXPECT_EQ(result->itemName(), multilayer1->itemName());
    EXPECT_EQ(result->modelType(), multilayer1->modelType());
}

TEST_F(TestSessionModel, test_InstrumentModel_CreateCopy)
{
    InstrumentModel model1;
    SessionItem* instrument1 = model1.insertNewItem(Constants::InstrumentType);
    instrument1->setItemName("instrument1");

    SessionItem* instrument2 = model1.insertNewItem(Constants::InstrumentType);
    instrument2->setItemName("instrument2");

    QString buffer1;
    QXmlStreamWriter writer1(&buffer1);
    model1.writeTo(&writer1);

    std::unique_ptr<InstrumentModel> model2(model1.createCopy());
    QString buffer2;
    QXmlStreamWriter writer2(&buffer2);
    model2->writeTo(&writer2);

    EXPECT_EQ(buffer1, buffer2);
}

TEST_F(TestSessionModel, test_InstrumentModel_CreatePartialCopy)
{
    InstrumentModel model1;
    SessionItem* instrument1 = model1.insertNewItem(Constants::InstrumentType);
    instrument1->setItemName("instrument1");

    SessionItem* instrument2 = model1.insertNewItem(Constants::InstrumentType);
    instrument2->setItemName("instrument2");

    std::unique_ptr<InstrumentModel> model2(model1.createCopy(instrument2));
    SessionItem* result = model2->itemForIndex(model2->index(0, 0, QModelIndex()));
    EXPECT_EQ(result->modelType(), instrument2->modelType());
}

//! Test if SessionItem can be copied from one model to another. Particularly, we test
//! here if a MultiLayerItem can be copied from SampleModel to the JobItem of JobModel

TEST_F(TestSessionModel, test_copyParameterizedItem)
{
    std::unique_ptr<MaterialModel> P_materialModel(new MaterialModel());

    SampleModel sampleModel;
    SessionItem* multilayer1 = sampleModel.insertNewItem(Constants::MultiLayerType);
    multilayer1->setItemName("multilayer1");
    sampleModel.insertNewItem(Constants::LayerType, sampleModel.indexOfItem(multilayer1));

    InstrumentModel instrumentModel;
    SessionItem* instrument1 = instrumentModel.insertNewItem(Constants::InstrumentType);
    instrument1->setItemName("instrument1");

    JobModel jobModel;
    SessionItem* jobItem = jobModel.insertNewItem(Constants::JobItemType);

    jobModel.copyParameterizedItem(multilayer1, jobItem, JobItem::T_SAMPLE);
    EXPECT_EQ(jobItem->getTagInfo(JobItem::T_SAMPLE).childCount, 1);

    jobModel.copyParameterizedItem(instrument1, jobItem, JobItem::T_INSTRUMENT);
    EXPECT_EQ(jobItem->getTagInfo(JobItem::T_INSTRUMENT).childCount, 1);
}
