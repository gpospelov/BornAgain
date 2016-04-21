#ifndef TESTSESSIONITEM_H
#define TESTSESSIONITEM_H


#include <QtTest>
#include "SessionItem.h"
#include "GUIHelpers.h"
#include "SessionModel.h"
#include "verify_throw_macro.h"



class TestSessionItem : public QObject {
    Q_OBJECT
private:
    void verify_get_item(SessionItem *item, const QString &tag, QVector<SessionItem*> list);
private slots:
    void test_constructor();
    void test_tags();
    void test_data_roles();
    void test_model_types();
};


inline void TestSessionItem::verify_get_item(SessionItem *item, const QString &tag, QVector<SessionItem *> list)
{
    if (list.size() > 0)
        QVERIFY(item->getItem(tag) == list[0]);
    else
        QVERIFY(item->getItem(tag) == nullptr);
    auto items = item->getItems(tag);
    QVERIFY(items.size() == list.size());
    QVERIFY(items == list);
    QVERIFY(item->getItem(tag, -1) == nullptr);
    QVERIFY(item->getItem(tag, list.size()) == nullptr);
    for (int i = 0; i < list.size(); i++) {
        QVERIFY(item->getItem(tag, i) == list[i]);
    }
}

inline void TestSessionItem::test_constructor()
{
    const QString modeltype = "This is the model type";
    SessionItem *item = new SessionItem(modeltype);
    QVERIFY(item->modelType() == modeltype);
    QVERIFY(item->model() == nullptr);
    QVERIFY(item->parent() == nullptr);
    // TODO add some more tests for children, roles, tags ...
}

inline void TestSessionItem::test_tags()
{
    const QString modeltype = "This is the model type";
    const QString tag1 = "TAG1";
    const QString tag2 = "TAG2";
    const QString tag3 = "TAG3";
    const QString tag4 = "TAG4";
    SessionItem *item = new SessionItem(modeltype);
    QVector<SessionItem*> items;
    for (int i = 0; i < 10; i++)
        items.append(new SessionItem(modeltype));

    // before using a tag, it must be registered
    QVERIFY(item->registerTag(tag1));

    // register twice returns false
    QVERIFY(item->registerTag(tag1) == false);

    // register empty string returns false
    QVERIFY(item->registerTag("") == false);

    // now we insert one element at the beginning
    QVERIFY(item->insertItem(0, items[0], tag1));

    // insertion out of range is forbidden
    QVERIFY(item->insertItem(-1, items[0], tag1) == false);
    QVERIFY(item->insertItem(2, items[0], tag1) == false);

    // double insertion is forbidden
    QVERIFY(item->insertItem(0, items[0], tag1) == false);

    // we try to access tagged items
    verify_get_item(item, tag1, items.mid(0, 1));

    // nullptr is not allowed
    QVERIFY(item->insertItem(1, nullptr, tag1) == false);
    verify_get_item(item, tag1, items.mid(0, 1));

    // LIMITS
    // register tag with limit 0 - 1
    QVERIFY(item->registerTag(tag2, 0, 1));

    QVERIFY(item->insertItem(0, items[1], tag2));
    verify_get_item(item, tag2, items.mid(1,1));
    QVERIFY(item->insertItem(1, items[1], tag2) == false);

    // register tag with limit 0 - 3 (using item 2 - 5)
    QVERIFY(item->registerTag(tag3, 0, 4));

    // add four items
    for (int i = 0; i < 4; i++) {
        QVERIFY(item->insertItem(i, items[2 + i], tag3));
        verify_get_item(item, tag3, items.mid(2, i+1));
    }

    // the fifth should fail
    QVERIFY(item->insertItem(0, items[6], tag3) == false);

    // items should be unchanged
    verify_get_item(item, tag3, items.mid(2, 4));

    // register tag with limit 4 - 4 add items to fill up limit
    QVERIFY(item->registerTag(tag4, 4, 4));

    // add four items
    for (int i = 0; i < 4; i++) {
        QVERIFY(item->insertItem(i, items[6 + i], tag4));
        verify_get_item(item, tag4, items.mid(6, i+1));
    }
    QVERIFY(item->insertItem(0, items[6], tag4) == false);

    // REMOVAL

    // tag4 can not be removed
    SessionItem *last = item->takeItem(3, tag4);
    QVERIFY(last == nullptr);
    verify_get_item(item, tag4, items.mid(6, 4));

    // remove all from tag3, checking access of tag4
    for (int i = 0; i < 4; i++) {
        last = item->takeItem(3-i, tag3);
        QVERIFY(last == items[5-i]);
        verify_get_item(item, tag3, items.mid(2,3-i));
        verify_get_item(item, tag4, items.mid(6,4));
    }

    delete item;
}

inline void TestSessionItem::test_data_roles()
{
    SessionItem *item = new SessionItem("Some model type");
    item->setData(Qt::DisplayRole, 1234);
    QVERIFY(item->data(Qt::DisplayRole) == 1234);
    QVERIFY(item->data(Qt::EditRole) == 1234);
    item->setData(Qt::EditRole, 5432);
    QVERIFY(item->data(Qt::DisplayRole) == 5432);
    QVERIFY(item->data(Qt::EditRole) == 5432);
    for (int i = 0; i < 10; i++) {
        QVERIFY(item->data(SessionModel::EndSessionRoles + i).isValid() == false);
        item->setData(SessionModel::EndSessionRoles + i, i);
        QVERIFY(item->data(SessionModel::EndSessionRoles + i) == i);
    }
}

inline void TestSessionItem::test_model_types()
{
    const QString model1 = "modeltype 1";
    const QString model2 = "modeltype 2";
    const QString model3 = "modeltype 3";
    const QString model4 = "modeltype 4";
    const QString model5 = "modeltype 5";

    SessionItem *item = new SessionItem("modeltype does not matter");
    QVERIFY(item->registerTag("Tag1", 0, -1, QStringList() << model1 << model2));
    QVERIFY(item->insertItem(0, new SessionItem(model1), "Tag1"));
    QVERIFY(item->insertItem(0, new SessionItem(model2), "Tag1"));
    QVERIFY(item->insertItem(0, new SessionItem(model3), "Tag1") == false);
    QVERIFY(item->insertItem(0, new SessionItem(model4), "Tag1") == false);
    QVERIFY(item->insertItem(0, new SessionItem(model5), "Tag1") == false);
    QVERIFY(item->registerTag("Tag2", 0, -1, QStringList() << model3 << model4 << model5));
    QVERIFY(item->insertItem(0, new SessionItem(model1), "Tag2") == false);
    QVERIFY(item->insertItem(0, new SessionItem(model2), "Tag2") == false);
    QVERIFY(item->insertItem(0, new SessionItem(model3), "Tag2"));
    QVERIFY(item->insertItem(0, new SessionItem(model4), "Tag2"));
    QVERIFY(item->insertItem(0, new SessionItem(model5), "Tag2"));
}

//inline void TestParameterizedItem::test_registerProperty()
//{
//    SessionItem item;
//    QString property_name("MyProperty");
//    double value(1.0);
////    QSignalSpy spy(&item, SIGNAL(propertyChanged(QString)));

//    // access non-existing property
//    QCOMPARE(false, item.isRegisteredTag(property_name));
//    QVERIFY_THROW(item.getRegisteredProperty(property_name), GUIHelpers::Error);
//    QVERIFY_THROW(item.setRegisteredProperty(property_name, value), GUIHelpers::Error);

//    // registering new property
//    item.registerProperty(property_name, value);
//    QCOMPARE(true, item.isRegisteredTag(property_name));
////    QCOMPARE(spy.count(), 1);
////    QList<QVariant> arguments = spy.takeFirst();
////    QCOMPARE(arguments.size(), 1);
////    QCOMPARE(arguments.at(0).toString(), property_name);
//    QCOMPARE(item.getRegisteredProperty(property_name).toDouble(), value);
////    QCOMPARE(spy.count(), 0);

//    // setting property value
//    double new_value(2.0);
//    item.setRegisteredProperty(property_name, new_value);
////    QCOMPARE(spy.count(), 1);
////    arguments = spy.takeFirst();
////    QCOMPARE(arguments.size(), 1);
////    QCOMPARE(arguments.at(0).toString(), property_name);
//    QCOMPARE(item.getRegisteredProperty(property_name).toDouble(), new_value);

//    // setting property value to wrong QVariant
//    QVERIFY_THROW(item.setRegisteredProperty(property_name, QString("aaa")), GUIHelpers::Error);

//    // attempt to register already existing property
//    QVERIFY_THROW(item.registerProperty(property_name, 1.0), GUIHelpers::Error);

//    // remove registered property
//    item.removeRegisteredProperty(property_name);
////    QCOMPARE(spy.count(), 1);
////    arguments = spy.takeFirst();
////    QCOMPARE(arguments.size(), 1);
////    QCOMPARE(arguments.at(0).toString(), property_name);
//    QVERIFY_THROW(item.getRegisteredProperty(property_name), GUIHelpers::Error);
//}

//inline void TestParameterizedItem::test_SelectableGroupProperty()
//{
////    SessionItem item;
////    QCOMPARE(item.getSubItems().size(), 0);
//}


#endif
