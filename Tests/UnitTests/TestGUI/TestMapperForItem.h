#ifndef TESTMAPPERFORITEM_H
#define TESTMAPPERFORITEM_H

#include "SessionItem.h"
#include "SampleModel.h"
#include "LayerItem.h"
#include "MultiLayerItem.h"
#include "item_constants.h"
#include <memory>
#include <QtTest>


//! Test if ModelMapper reports correctly (number of callbacks,
//! names of properties and reporting items)
class TestMapperForItem : public QObject {
    Q_OBJECT

public:
    TestMapperForItem(QObject *parent = 0)
        : QObject(parent)
        , m_onPropertyChangeCount(0)
        , m_onChildPropertyChangeCount(0)
        , m_onParentChangeCount(0)
        , m_onChildrenChangeCount(0)
        , m_mapped_item(0)
        , m_reporting_item(0)
    { }

    void clear()
    {
        m_onPropertyChangeCount = 0;
        m_onChildPropertyChangeCount = 0;
        m_onParentChangeCount = 0;
        m_onChildrenChangeCount = 0;
        m_mapped_item = 0;
        m_reporting_item = 0;
        m_reporting_name.clear();
    }

    void setItem(SessionItem *item)
    {
        clear();
        m_mapped_item = item;
        m_mapper.reset(new ModelMapper);
        m_mapper->setItem(item);

        m_mapper->setOnPropertyChange(
                    [this] (QString name)
        {
            onPropertyChange(name);
        });

        m_mapper->setOnChildPropertyChange(
                    [this](SessionItem* item, QString name)
        {
            onChildPropertyChange(item, name);
        });

        m_mapper->setOnParentChange(
                    [this](SessionItem *parent) {
            onParentChange(parent);
        });


        m_mapper->setOnChildrenChange(
                    [this]()
        {
            onChildrenChange();
        });



    }

private:
    void onPropertyChange(const QString &name)
    {
        m_reporting_name = name;
        m_onPropertyChangeCount++;
    }

    void onChildPropertyChange(SessionItem *item, const QString &name)
    {
        m_reporting_item = item;
        m_reporting_name = name;
        m_onChildPropertyChangeCount++;
    }

    void onParentChange(SessionItem *item)
    {
        m_reporting_item = item;
        m_onParentChangeCount++;
    }

    void onChildrenChange()
    {
        m_onChildrenChangeCount++;
    }

    int m_onPropertyChangeCount;
    int m_onChildPropertyChangeCount;
    int m_onParentChangeCount;
    int m_onChildrenChangeCount;
    SessionItem *m_mapped_item;
    SessionItem *m_reporting_item;
    QString m_reporting_name;
    std::unique_ptr<ModelMapper> m_mapper;

private slots:

    void test_onPropertyChange();


};

inline void TestMapperForItem::test_onPropertyChange()
{
    SampleModel model;
    SessionItem *multilayer = model.insertNewItem(Constants::MultiLayerType);
    SessionItem *layer = model.insertNewItem(Constants::LayerType, model.indexOfItem(multilayer));

    // check initial state of our test class
    QVERIFY(m_onPropertyChangeCount == 0);
    QVERIFY(m_onChildPropertyChangeCount == 0);
    QVERIFY(m_onParentChangeCount == 0);
    QVERIFY(m_onChildrenChangeCount == 0);
    QVERIFY(m_mapped_item == nullptr);
    QVERIFY(m_reporting_item == nullptr);
    QVERIFY(m_reporting_name.isEmpty());

    // Mapper is looking on child; set property of child
    setItem(layer);
    layer->setItemValue(LayerItem::P_THICKNESS, 1.0);
    QVERIFY(m_onPropertyChangeCount == 1);
    QVERIFY(m_onChildPropertyChangeCount == 0);
    QVERIFY(m_onParentChangeCount == 0);
    QVERIFY(m_onChildrenChangeCount == 0);
    QVERIFY(m_mapped_item == layer);
    QVERIFY(m_reporting_item == nullptr);
    QVERIFY(m_reporting_name == LayerItem::P_THICKNESS);

    // Mapper is looking on child; set property of parent;
    setItem(layer);
    multilayer->setItemValue(MultiLayerItem::P_CROSS_CORR_LENGTH, 1.0);
    QVERIFY(m_onPropertyChangeCount == 0);
    QVERIFY(m_onChildPropertyChangeCount == 0);
    QVERIFY(m_onParentChangeCount == 0);
    QVERIFY(m_onChildrenChangeCount == 0);
    QVERIFY(m_mapped_item == layer);
    QVERIFY(m_reporting_item == nullptr);
    QVERIFY(m_reporting_name.isEmpty());

    // Mapper is looking on parent; set property of child;
//    setItem(multilayer);
//    layer->setItemValue(LayerItem::P_THICKNESS, 1.0);
//    QVERIFY(m_onPropertyChangeCount == 0);
////    QVERIFY(m_onChildPropertyChangeCount == 1);
//    QVERIFY(m_onParentChangeCount == 0);
//    QVERIFY(m_onChildrenChangeCount == 0);
//    QVERIFY(m_mapped_item == multilayer);
////    QVERIFY(m_reporting_item == layer);
//    QVERIFY(m_reporting_name == LayerItem::P_THICKNESS);


}

#endif
