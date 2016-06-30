#ifndef TESTMAPPERFORITEM_H
#define TESTMAPPERFORITEM_H

#include "SessionItem.h"
#include "SampleModel.h"
#include "LayerItem.h"
#include "MultiLayerItem.h"
#include "item_constants.h"
#include <memory>
#include <QtTest>


//! Test Widget which logs calling activity of ModelMapper
class Widget {
public:
    Widget()
        : m_onPropertyChangeCount(0)
        , m_onChildPropertyChangeCount(0)
        , m_onParentChangeCount(0)
        , m_onChildrenChangeCount(0)
        , m_onSiblingsChangeCount(0)
    { }

    void clear()
    {
        m_onPropertyChangeCount = 0;
        m_onChildPropertyChangeCount = 0;
        m_onParentChangeCount = 0;
        m_onChildrenChangeCount = 0;
        m_onSiblingsChangeCount = 0;
        m_reported_items.clear();
        m_reported_names.clear();
    }

    void subscribe(ModelMapper *mapper, bool with_subscription = false)
    {
        clear();

        void *caller = (with_subscription ? this : 0);

        mapper->setOnPropertyChange(
                    [this] (QString name)
        {
            onPropertyChange(name);
        }, caller);

        mapper->setOnChildPropertyChange(
                    [this](SessionItem* item, QString name)
        {
            onChildPropertyChange(item, name);
        }, caller);

        mapper->setOnParentChange(
                    [this](SessionItem *parent) {
            onParentChange(parent);
        }, caller);


        mapper->setOnChildrenChange(
                    [this](SessionItem*)
        {
            onChildrenChange();
        }, caller);

        mapper->setOnSiblingsChange(
                    [this]()
        {
            onSiblingsChange();
        }, caller);

    }

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

    void unsubscribe(ModelMapper *mapper) {
        mapper->unsubscribe(this);
    }

    int m_onPropertyChangeCount;
    int m_onChildPropertyChangeCount;
    int m_onParentChangeCount;
    int m_onChildrenChangeCount;
    int m_onSiblingsChangeCount;
    QList<SessionItem *> m_reported_items;
    QStringList m_reported_names;
};


//! Test if ModelMapper reports correctly (number of callbacks,
//! names of properties and reporting items)
class TestMapperForItem : public QObject {
    Q_OBJECT

public:
    TestMapperForItem(QObject *parent = 0)
        : QObject(parent)
        , m_mapped_item(0)
    { }

    void setItem(SessionItem *item, Widget *widget = 0, bool with_subscription = false)
    {
        m_mapped_item = item;
        m_mapper.reset(new ModelMapper);
        m_mapper->setItem(item);
        if(widget) widget->subscribe(m_mapper.get(), with_subscription);
    }

private:
    SessionItem *m_mapped_item;
    std::unique_ptr<ModelMapper> m_mapper;

private slots:
    void test_initialCondition();
    void test_onPropertyChange();
    void test_onParentChange();
    void test_onChildrenChange();
    void test_onSiblingsChange();
    void test_Subscription();
    void test_TwoWidgetsSubscription();
};

inline void TestMapperForItem::test_initialCondition()
{
    Widget w;
    QCOMPARE(w.m_onPropertyChangeCount, 0);
    QCOMPARE(w.m_onChildPropertyChangeCount, 0);
    QCOMPARE(w.m_onParentChangeCount, 0);
    QCOMPARE(w.m_onChildrenChangeCount, 0);
    QCOMPARE(w.m_onSiblingsChangeCount, 0);
    QVERIFY(w.m_reported_items.isEmpty());
    QVERIFY(w.m_reported_names.isEmpty());
    QVERIFY(m_mapped_item == nullptr);
    QVERIFY(!m_mapper);
}

inline void TestMapperForItem::test_onPropertyChange()
{
    Widget w;
    SampleModel model;
    SessionItem *multilayer = model.insertNewItem(Constants::MultiLayerType);
    SessionItem *layer = model.insertNewItem(Constants::LayerType, model.indexOfItem(multilayer));

    // Mapper is looking on child; set property of child
    setItem(layer, &w);
    QVERIFY(m_mapped_item == layer);

    layer->setItemValue(LayerItem::P_THICKNESS, 1.0);
    QCOMPARE(w.m_onPropertyChangeCount, 1);
    QCOMPARE(w.m_onChildPropertyChangeCount, 0);
    QCOMPARE(w.m_onParentChangeCount, 0);
    QCOMPARE(w.m_onChildrenChangeCount, 0);
    QCOMPARE(w.m_onSiblingsChangeCount, 0);
    QVERIFY(w.m_reported_items.isEmpty());
    QVERIFY((w.m_reported_names.size() == 1) && (w.m_reported_names[0] == LayerItem::P_THICKNESS));

    // Mapper is looking on child; set property of parent;
    setItem(layer, &w);
    QVERIFY(m_mapped_item == layer);
    multilayer->setItemValue(MultiLayerItem::P_CROSS_CORR_LENGTH, 1.0);
    QCOMPARE(w.m_onPropertyChangeCount, 0);
    QCOMPARE(w.m_onChildPropertyChangeCount, 0);
    QCOMPARE(w.m_onParentChangeCount, 0);
    QCOMPARE(w.m_onChildrenChangeCount, 0);
    QCOMPARE(w.m_onSiblingsChangeCount, 0);
    QVERIFY(w.m_reported_items.isEmpty());
    QVERIFY(w.m_reported_names.isEmpty());

    // Mapper is looking on parent; set property of child;
    setItem(multilayer, &w);
    QVERIFY(m_mapped_item == multilayer);
    layer->setItemValue(LayerItem::P_THICKNESS, 2.0);
    QCOMPARE(w.m_onPropertyChangeCount, 0);
    QCOMPARE(w.m_onChildPropertyChangeCount, 1);
    QCOMPARE(w.m_onParentChangeCount, 0);
    QCOMPARE(w.m_onChildrenChangeCount, 0);
    QCOMPARE(w.m_onSiblingsChangeCount, 0);
    QVERIFY( (w.m_reported_items.size() == 1) && (w.m_reported_items[0] == layer));
    QVERIFY((w.m_reported_names.size() == 1) && (w.m_reported_names[0] == LayerItem::P_THICKNESS));

    // Mapper is looking on parent; set property of parent;
    setItem(multilayer, &w);
    QVERIFY(m_mapped_item == multilayer);
    multilayer->setItemValue(MultiLayerItem::P_CROSS_CORR_LENGTH, 2.0);
    QCOMPARE(w.m_onPropertyChangeCount, 1);
    QCOMPARE(w.m_onChildPropertyChangeCount, 0);
    QCOMPARE(w.m_onParentChangeCount, 0);
    QCOMPARE(w.m_onChildrenChangeCount, 0);
    QCOMPARE(w.m_onSiblingsChangeCount, 0);
    QVERIFY(w.m_reported_items.isEmpty());
    QVERIFY((w.m_reported_names.size() == 1) && (w.m_reported_names[0] == MultiLayerItem::P_CROSS_CORR_LENGTH));
}

inline void TestMapperForItem::test_onParentChange()
{
    Widget w;
    SampleModel model;
    SessionItem *multilayer = model.insertNewItem(Constants::MultiLayerType);
    SessionItem *layer = model.insertNewItem(Constants::LayerType, model.indexOfItem(multilayer));
//    SessionItem *layer = model.insertNewItem(Constants::LayerType);

    // Mapper is looking on child; changing child's parent
    setItem(layer, &w);
    QVERIFY(m_mapped_item == layer);
    multilayer->takeRow(layer->parentRow());
//    model.moveParameterizedItem(layer, multilayer);
    // FIXME check onParentChange while moving an item

    QCOMPARE(w.m_onPropertyChangeCount, 0);
    QCOMPARE(w.m_onChildPropertyChangeCount, 0);
    QCOMPARE(w.m_onParentChangeCount, 1);
    QCOMPARE(w.m_onChildrenChangeCount, 0);
    //QVERIFY((w.m_reported_items.size() == 1) && (w.m_reported_items[0] == nullptr));
    QVERIFY(w.m_reported_names.isEmpty());
}

inline void TestMapperForItem::test_onChildrenChange()
{
    Widget w;
    SampleModel model;
    SessionItem *multilayer = model.insertNewItem(Constants::MultiLayerType);

    // Mapper is looking on parent; adding new child to parent
    setItem(multilayer, &w);
    QVERIFY(m_mapped_item == multilayer);
    model.insertNewItem(Constants::LayerType, model.indexOfItem(multilayer));

    QCOMPARE(w.m_onPropertyChangeCount, 0);
    QCOMPARE(w.m_onChildPropertyChangeCount, 2);
    QCOMPARE(w.m_onParentChangeCount, 0);
    QCOMPARE(w.m_onChildrenChangeCount, 1);
    QCOMPARE(w.m_onSiblingsChangeCount, 0);
    QCOMPARE(w.m_reported_items.size(), 2);
    QCOMPARE(w.m_reported_names.size(), 2);
}

inline void TestMapperForItem::test_onSiblingsChange()
{
    Widget w;
    SampleModel model;
    SessionItem *multilayer = model.insertNewItem(Constants::MultiLayerType);
    SessionItem *layer = model.insertNewItem(Constants::LayerType, model.indexOfItem(multilayer));

    // Mapper is looking on child; adding another child to parent
    setItem(layer, &w);
    QVERIFY(m_mapped_item == layer);
    SessionItem *layer2 = model.insertNewItem(Constants::LayerType, model.indexOfItem(multilayer));
    Q_UNUSED(layer2);

    QCOMPARE(w.m_onPropertyChangeCount, 0);
    QCOMPARE(w.m_onChildPropertyChangeCount, 0);
    QCOMPARE(w.m_onParentChangeCount, 0);
    QCOMPARE(w.m_onChildrenChangeCount, 0);
    QCOMPARE(w.m_onSiblingsChangeCount, 1);
    QVERIFY(w.m_reported_items.isEmpty());
    QVERIFY(w.m_reported_names.isEmpty());

    multilayer->takeItem(1, MultiLayerItem::T_LAYERS);
    QCOMPARE(w.m_onSiblingsChangeCount, 2);

    // FIXME
//    multilayer->takeRow(layer2->parentRow());
    //    QCOMPARE(m_onSiblingsChangeCount, 2);
}

inline void TestMapperForItem::test_Subscription()
{
    Widget w;
    SampleModel model;
    SessionItem *multilayer = model.insertNewItem(Constants::MultiLayerType);
    SessionItem *layer = model.insertNewItem(Constants::LayerType, model.indexOfItem(multilayer));

    // Mapper is looking on child; set property of child
    setItem(layer, &w, true);
    QVERIFY(m_mapped_item == layer);
    layer->setItemValue(LayerItem::P_THICKNESS, 1.0);
    QCOMPARE(w.m_onPropertyChangeCount, 1);
    QCOMPARE(w.m_onChildPropertyChangeCount, 0);
    QCOMPARE(w.m_onParentChangeCount, 0);
    QCOMPARE(w.m_onChildrenChangeCount, 0);
    QCOMPARE(w.m_onSiblingsChangeCount, 0);
    QVERIFY(w.m_reported_items.isEmpty());
    QVERIFY((w.m_reported_names.size() == 1) && (w.m_reported_names[0] == LayerItem::P_THICKNESS));

    layer->setItemValue(LayerItem::P_THICKNESS, 2.0);
    QCOMPARE(w.m_onPropertyChangeCount, 2);

    // unsubscribe widget and check that it doesn't react on item value change
    w.unsubscribe(m_mapper.get());
    layer->setItemValue(LayerItem::P_THICKNESS, 3.0);
    QCOMPARE(w.m_onPropertyChangeCount, 2);
}

inline void TestMapperForItem::test_TwoWidgetsSubscription()
{
    Widget w1, w2;
    SampleModel model;
    SessionItem *multilayer = model.insertNewItem(Constants::MultiLayerType);
    SessionItem *layer = model.insertNewItem(Constants::LayerType, model.indexOfItem(multilayer));

    // Mapper is looking on child; set property of child
    setItem(layer);
    w1.subscribe(m_mapper.get(), true);
    w2.subscribe(m_mapper.get(), true);
    QCOMPARE(w1.m_onPropertyChangeCount, 0);
    QCOMPARE(w2.m_onPropertyChangeCount, 0);

    layer->setItemValue(LayerItem::P_THICKNESS, 1.0);
    QCOMPARE(w1.m_onPropertyChangeCount, 1);
    QCOMPARE(w2.m_onPropertyChangeCount, 1);

    w1.unsubscribe(m_mapper.get());
    layer->setItemValue(LayerItem::P_THICKNESS, 2.0);
    QCOMPARE(w1.m_onPropertyChangeCount, 1);
    QCOMPARE(w2.m_onPropertyChangeCount, 2);

}



#endif
