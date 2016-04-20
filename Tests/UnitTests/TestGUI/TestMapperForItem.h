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
        , m_onSiblingsChangeCount(0)
        , m_mapped_item(0)
    { }

    void clear()
    {
        m_onPropertyChangeCount = 0;
        m_onChildPropertyChangeCount = 0;
        m_onParentChangeCount = 0;
        m_onChildrenChangeCount = 0;
        m_onSiblingsChangeCount = 0;
        m_mapped_item = 0;
        m_reported_items.clear();
        m_reported_names.clear();
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
                    [this](SessionItem*)
        {
            onChildrenChange();
        });

        m_mapper->setOnSiblingsChange(
                    [this]()
        {
            onSiblingsChange();
        });

    }

    void setItemSubscribe(SessionItem *item)
    {
        clear();
        m_mapped_item = item;
        m_mapper.reset(new ModelMapper);
        m_mapper->setItem(item);

        m_mapper->setOnPropertyChange(
                    [this] (QString name)
        {
            onPropertyChange(name);
        }, this);

        m_mapper->setOnChildPropertyChange(
                    [this](SessionItem* item, QString name)
        {
            onChildPropertyChange(item, name);
        }, this);

        m_mapper->setOnParentChange(
                    [this](SessionItem *parent) {
            onParentChange(parent);
        }, this);


        m_mapper->setOnChildrenChange(
                    [this](SessionItem*)
        {
            onChildrenChange();
        }, this);

        m_mapper->setOnSiblingsChange(
                    [this]()
        {
            onSiblingsChange();
        }, this);

    }


private:
    void onPropertyChange(const QString &name)
    {
        m_reported_names.append(name);
        m_onPropertyChangeCount++;
    }

    void onChildPropertyChange(SessionItem *item, const QString &name)
    {
        m_reported_items.append(item);
        m_reported_names.append(name);
        m_onChildPropertyChangeCount++;
    }

    void onParentChange(SessionItem *item)
    {
        m_reported_items.append(item);
        m_onParentChangeCount++;
    }

    void onChildrenChange()
    {
        m_onChildrenChangeCount++;
    }

    void onSiblingsChange()
    {
        m_onSiblingsChangeCount++;
    }

    int m_onPropertyChangeCount;
    int m_onChildPropertyChangeCount;
    int m_onParentChangeCount;
    int m_onChildrenChangeCount;
    int m_onSiblingsChangeCount;
    SessionItem *m_mapped_item;
    QList<SessionItem *> m_reported_items;
    QStringList m_reported_names;
    std::unique_ptr<ModelMapper> m_mapper;

private slots:

    void test_onPropertyChange();
    void test_onParentChange();
    void test_onChildrenChange();
    void test_onSiblingsChange();

    void test_Subscription();
};

inline void TestMapperForItem::test_onPropertyChange()
{
    SampleModel model;
    SessionItem *multilayer = model.insertNewItem(Constants::MultiLayerType);
    SessionItem *layer = model.insertNewItem(Constants::LayerType, model.indexOfItem(multilayer));

    // check initial state of our test class
    QCOMPARE(m_onPropertyChangeCount, 0);
    QCOMPARE(m_onChildPropertyChangeCount, 0);
    QCOMPARE(m_onParentChangeCount, 0);
    QCOMPARE(m_onChildrenChangeCount, 0);
    QCOMPARE(m_onSiblingsChangeCount, 0);
    QVERIFY(m_mapped_item == nullptr);
    QVERIFY(m_reported_items.isEmpty());
    QVERIFY(m_reported_names.isEmpty());

    // Mapper is looking on child; set property of child
    setItem(layer);
    layer->setItemValue(LayerItem::P_THICKNESS, 1.0);
    QCOMPARE(m_onPropertyChangeCount, 1);
    QCOMPARE(m_onChildPropertyChangeCount, 0);
    QCOMPARE(m_onParentChangeCount, 0);
    QCOMPARE(m_onChildrenChangeCount, 0);
    QCOMPARE(m_onSiblingsChangeCount, 0);
    QVERIFY(m_mapped_item == layer);
    QVERIFY(m_reported_items.isEmpty());
    QVERIFY((m_reported_names.size() == 1) && (m_reported_names[0] == LayerItem::P_THICKNESS));

    // Mapper is looking on child; set property of parent;
    setItem(layer);
    multilayer->setItemValue(MultiLayerItem::P_CROSS_CORR_LENGTH, 1.0);
    QCOMPARE(m_onPropertyChangeCount, 0);
    QCOMPARE(m_onChildPropertyChangeCount, 0);
    QCOMPARE(m_onParentChangeCount, 0);
    QCOMPARE(m_onChildrenChangeCount, 0);
    QCOMPARE(m_onSiblingsChangeCount, 0);
    QVERIFY(m_mapped_item == layer);
    QVERIFY(m_reported_items.isEmpty());
    QVERIFY(m_reported_names.isEmpty());

    // Mapper is looking on parent; set property of child;
    setItem(multilayer);
    layer->setItemValue(LayerItem::P_THICKNESS, 2.0);
    QCOMPARE(m_onPropertyChangeCount, 0);
    QCOMPARE(m_onChildPropertyChangeCount, 1);
    QCOMPARE(m_onParentChangeCount, 0);
    QCOMPARE(m_onChildrenChangeCount, 0);
    QCOMPARE(m_onSiblingsChangeCount, 0);
    QVERIFY(m_mapped_item == multilayer);
    QVERIFY( (m_reported_items.size() == 1) && (m_reported_items[0] == layer));
    QVERIFY((m_reported_names.size() == 1) && (m_reported_names[0] == LayerItem::P_THICKNESS));

    // Mapper is looking on parent; set property of parent;
    setItem(multilayer);
    multilayer->setItemValue(MultiLayerItem::P_CROSS_CORR_LENGTH, 2.0);
    QCOMPARE(m_onPropertyChangeCount, 1);
    QCOMPARE(m_onChildPropertyChangeCount, 0);
    QCOMPARE(m_onParentChangeCount, 0);
    QCOMPARE(m_onChildrenChangeCount, 0);
    QCOMPARE(m_onSiblingsChangeCount, 0);
    QVERIFY(m_mapped_item == multilayer);
    QVERIFY(m_reported_items.isEmpty());
    QVERIFY((m_reported_names.size() == 1) && (m_reported_names[0] == MultiLayerItem::P_CROSS_CORR_LENGTH));
}

inline void TestMapperForItem::test_onParentChange()
{
    clear();
    SampleModel model;
    SessionItem *multilayer = model.insertNewItem(Constants::MultiLayerType);
    SessionItem *layer = model.insertNewItem(Constants::LayerType, model.indexOfItem(multilayer));
//    SessionItem *layer = model.insertNewItem(Constants::LayerType);

    // Mapper is looking on child; changing child's parent
    setItem(layer);
    multilayer->takeRow(layer->parentRow());
//    model.moveParameterizedItem(layer, multilayer);
    // FIXME check onParentChange while moving an item

    QCOMPARE(m_onPropertyChangeCount, 0);
    QCOMPARE(m_onChildPropertyChangeCount, 0);
    QCOMPARE(m_onParentChangeCount, 1);
    QCOMPARE(m_onChildrenChangeCount, 0);
    QVERIFY(m_mapped_item == layer);
    //QVERIFY((m_reported_items.size() == 1) && (m_reported_items[0] == nullptr));
    QVERIFY(m_reported_names.isEmpty());
}

inline void TestMapperForItem::test_onChildrenChange()
{
    clear();
    SampleModel model;
    SessionItem *multilayer = model.insertNewItem(Constants::MultiLayerType);

    // Mapper is looking on parent; adding new child to parent
    setItem(multilayer);
    model.insertNewItem(Constants::LayerType, model.indexOfItem(multilayer));

    QCOMPARE(m_onPropertyChangeCount, 0);
    QCOMPARE(m_onChildPropertyChangeCount, 2);
    QCOMPARE(m_onParentChangeCount, 0);
    QCOMPARE(m_onChildrenChangeCount, 1);
    QCOMPARE(m_onSiblingsChangeCount, 0);
    QVERIFY(m_mapped_item == multilayer);
    QCOMPARE(m_reported_items.size(), 2);
    QCOMPARE(m_reported_names.size(), 2);
}

inline void TestMapperForItem::test_onSiblingsChange()
{
    clear();
    SampleModel model;
    SessionItem *multilayer = model.insertNewItem(Constants::MultiLayerType);
    SessionItem *layer = model.insertNewItem(Constants::LayerType, model.indexOfItem(multilayer));

    // Mapper is looking on child; adding another child to parent
    setItem(layer);
    SessionItem *layer2 = model.insertNewItem(Constants::LayerType, model.indexOfItem(multilayer));
    Q_UNUSED(layer2);

    QCOMPARE(m_onPropertyChangeCount, 0);
    QCOMPARE(m_onChildPropertyChangeCount, 0);
    QCOMPARE(m_onParentChangeCount, 0);
    QCOMPARE(m_onChildrenChangeCount, 0);
    QCOMPARE(m_onSiblingsChangeCount, 1);
    QVERIFY(m_mapped_item == layer);
    QVERIFY(m_reported_items.isEmpty());
    QVERIFY(m_reported_names.isEmpty());

    multilayer->takeItem(1, MultiLayerItem::T_LAYERS);
    QCOMPARE(m_onSiblingsChangeCount, 2);

    // FIXME
//    multilayer->takeRow(layer2->parentRow());
    //    QCOMPARE(m_onSiblingsChangeCount, 2);
}

inline void TestMapperForItem::test_Subscription()
{
    SampleModel model;
    SessionItem *multilayer = model.insertNewItem(Constants::MultiLayerType);
    SessionItem *layer = model.insertNewItem(Constants::LayerType, model.indexOfItem(multilayer));

    // Mapper is looking on child; set property of child
    setItemSubscribe(layer);
    layer->setItemValue(LayerItem::P_THICKNESS, 1.0);
    QCOMPARE(m_onPropertyChangeCount, 1);
    QCOMPARE(m_onChildPropertyChangeCount, 0);
    QCOMPARE(m_onParentChangeCount, 0);
    QCOMPARE(m_onChildrenChangeCount, 0);
    QCOMPARE(m_onSiblingsChangeCount, 0);
    QVERIFY(m_mapped_item == layer);
    QVERIFY(m_reported_items.isEmpty());
    QVERIFY((m_reported_names.size() == 1) && (m_reported_names[0] == LayerItem::P_THICKNESS));

    layer->setItemValue(LayerItem::P_THICKNESS, 2.0);
    QCOMPARE(m_onPropertyChangeCount, 2);

    m_mapper->unsubscribe(this);
    layer->setItemValue(LayerItem::P_THICKNESS, 3.0);
    QCOMPARE(m_onPropertyChangeCount, 2);
}



#endif
