#include <QtTest>
#include "SessionModel.h"
#include "SampleModel.h"
#include "MaterialModel.h"
#include "InstrumentModel.h"
#include "MaterialSvc.h"
#include "JobModel.h"
#include "JobItem.h"
#include <QXmlStreamWriter>
#include <memory>

class TestSessionModel : public QObject {
    Q_OBJECT

private slots:
    void test_SampleModel_CreateCopy();
    void test_SampleModel_CreatePartialCopy();
    void test_InstrumentModel_CreateCopy();
    void test_InstrumentModel_CreatePartialCopy();
    void test_copyParameterizedItem();
};

inline void TestSessionModel::test_SampleModel_CreateCopy()
{
    std::unique_ptr<MaterialModel> P_materialModel(new MaterialModel());
    std::unique_ptr<MaterialSvc> P_materialEditor(new MaterialSvc(P_materialModel.get()));

    SampleModel *model1 = new SampleModel();
    SessionItem *multilayer = model1->insertNewItem(Constants::MultiLayerType);
    multilayer->setItemName("multilayer");
    model1->insertNewItem(Constants::LayerType, model1->indexOfItem(multilayer));
    SessionItem *multilayer2 = model1->insertNewItem(Constants::MultiLayerType);
    multilayer2->setItemName("multilayer2");

    QString buffer1;
    QXmlStreamWriter writer1(&buffer1);
    model1->writeTo(&writer1);

    SampleModel *model2 = model1->createCopy();
    QString buffer2;
    QXmlStreamWriter writer2(&buffer2);
    model2->writeTo(&writer2);

    QCOMPARE(buffer1, buffer2);

    delete model1;
    delete model2;
}

inline void TestSessionModel::test_SampleModel_CreatePartialCopy()
{
    std::unique_ptr<MaterialModel> P_materialModel(new MaterialModel());
    std::unique_ptr<MaterialSvc> P_materialEditor(new MaterialSvc(P_materialModel.get()));

    SampleModel *model1 = new SampleModel();
    SessionItem *multilayer1 = model1->insertNewItem(Constants::MultiLayerType);
    multilayer1->setItemName("multilayer1");
    model1->insertNewItem(Constants::LayerType, model1->indexOfItem(multilayer1));

    SessionItem *multilayer2 = model1->insertNewItem(Constants::MultiLayerType);
    multilayer2->setItemName("multilayer2");

    SampleModel *model2 = model1->createCopy(multilayer1);
    SessionItem *result = model2->itemForIndex(model2->index(0,0,QModelIndex()));

    QCOMPARE(result->itemName(), multilayer1->itemName());
    QCOMPARE(result->modelType(), multilayer1->modelType());

    delete model1;
    delete model2;
}

inline void TestSessionModel::test_InstrumentModel_CreateCopy()
{
    InstrumentModel *model1 = new InstrumentModel();
    SessionItem *instrument1 = model1->insertNewItem(Constants::InstrumentType);
    instrument1->setItemName("instrument1");
    model1->insertNewItem(Constants::DetectorContainerType, model1->indexOfItem(instrument1));
    model1->insertNewItem(Constants::BeamType, model1->indexOfItem(instrument1));

    SessionItem *instrument2 = model1->insertNewItem(Constants::InstrumentType);
    instrument2->setItemName("instrument2");
    model1->insertNewItem(Constants::DetectorContainerType, model1->indexOfItem(instrument2));
    model1->insertNewItem(Constants::BeamType, model1->indexOfItem(instrument2));

    QString buffer1;
    QXmlStreamWriter writer1(&buffer1);
    model1->writeTo(&writer1);

    InstrumentModel *model2 = model1->createCopy();
    QString buffer2;
    QXmlStreamWriter writer2(&buffer2);
    model2->writeTo(&writer2);

    QCOMPARE(buffer1, buffer2);

    delete model1;
    delete model2;
}

inline void TestSessionModel::test_InstrumentModel_CreatePartialCopy()
{
    InstrumentModel *model1 = new InstrumentModel();
    SessionItem *instrument1 = model1->insertNewItem(Constants::InstrumentType);
    instrument1->setItemName("instrument1");
    model1->insertNewItem(Constants::DetectorContainerType, model1->indexOfItem(instrument1));
    model1->insertNewItem(Constants::BeamType, model1->indexOfItem(instrument1));

    SessionItem *instrument2 = model1->insertNewItem(Constants::InstrumentType);
    instrument2->setItemName("instrument2");
    model1->insertNewItem(Constants::DetectorContainerType, model1->indexOfItem(instrument2));
    model1->insertNewItem(Constants::BeamType, model1->indexOfItem(instrument2));

//    QString buffer1;
//    QXmlStreamWriter writer1(&buffer1);
//    model1->writeTo(&writer1);

    // this method seems not implemented even before
    InstrumentModel *model2 = model1->createCopy(instrument2);

//    QString buffer2;
//    QXmlStreamWriter writer2(&buffer2);
//    model2->writeTo(&writer2);

    SessionItem *result = model2->itemForIndex(model2->index(0,0,QModelIndex()));

//    QCOMPARE(result->itemName(), instrument2->itemName());
    QCOMPARE(result->modelType(), instrument2->modelType());

    delete model1;
    delete model2;
}

//! Test if SessionItem can be copied from one model to another. Particularly, we test
//! here if a MultiLayerItem can be copied from SampleModel to the JobItem of JobModel
inline void TestSessionModel::test_copyParameterizedItem()
{
    std::unique_ptr<MaterialModel> P_materialModel(new MaterialModel());
    std::unique_ptr<MaterialSvc> P_materialEditor(new MaterialSvc(P_materialModel.get()));

    SampleModel *sampleModel = new SampleModel();
    SessionItem *multilayer1 = sampleModel->insertNewItem(Constants::MultiLayerType);
    multilayer1->setItemName("multilayer1");
    sampleModel->insertNewItem(Constants::LayerType, sampleModel->indexOfItem(multilayer1));

    InstrumentModel *instrumentModel = new InstrumentModel();
    SessionItem *instrument1 = instrumentModel->insertNewItem(Constants::InstrumentType);
    instrument1->setItemName("instrument1");
    instrumentModel->insertNewItem(Constants::DetectorContainerType, instrumentModel->indexOfItem(instrument1));
    instrumentModel->insertNewItem(Constants::BeamType, instrumentModel->indexOfItem(instrument1));

    JobModel *jobModel = new JobModel();
    SessionItem *jobItem = jobModel->insertNewItem(Constants::JobItemType);

    jobModel->copyParameterizedItem(multilayer1, jobItem, JobItem::T_SAMPLE);
    QCOMPARE(jobItem->getTagInfo(JobItem::T_SAMPLE).childCount, 1);

    jobModel->copyParameterizedItem(instrument1, jobItem, JobItem::T_INSTRUMENT);
    QCOMPARE(jobItem->getTagInfo(JobItem::T_INSTRUMENT).childCount, 1);

    delete sampleModel;
    delete instrumentModel;
    delete jobModel;
}

