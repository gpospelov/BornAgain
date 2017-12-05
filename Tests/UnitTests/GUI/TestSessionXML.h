#include <QtTest>
#include "SessionItem.h"
#include "SessionXML2.h"
#include "SessionModel.h"
#include "FormFactorItems.h"
#include "ParticleItem.h"
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <memory>
#include <QDebug>

namespace
{
QString itemToXML(SessionItem* item)
{
    QString result;
    QXmlStreamWriter writer(&result);

    writer.writeStartElement(item->model()->getModelTag());
    writer.writeAttribute(SessionXML::ModelNameAttribute, item->model()->getModelName());

    SessionXML2::writeItemAndChildItems(&writer, item);

    writer.writeEndElement(); // m_model_tag

    return result;
}

void itemFromXML(QString buffer, SessionItem* item)
{
    QXmlStreamReader reader(buffer);
    SessionXML2::readItems(&reader, item);
}
}

class TestSessionXML : public QObject
{
    Q_OBJECT
private slots:
    void test_sessionItem();
    void test_FullSphereItem();
    void test_twoFullSphereItems();
    void test_emptyMultiLayer();
    void test_Layer();
    void test_Particle();
    void test_ParticleWithFF();
};

//! Testing to/from xml: simple property item.

inline void TestSessionXML::test_sessionItem()
{
    QString expected;

    SessionModel source("TestModel");
    source.insertNewItem(Constants::PropertyType);

    expected = "<TestModel Name=\"DefaultName\">"
               "<Item ModelType=\"Property\" Tag=\"rootTag\" DisplayName=\"Property\"/>"
               "</TestModel>";
    QCOMPARE(itemToXML(source.rootItem()), expected);

    SessionModel target("TestModel");
    itemFromXML(expected, target.rootItem());

    QCOMPARE(target.rowCount(QModelIndex()), 1);
    SessionItem* newItem = target.itemForIndex(target.index(0, 0, QModelIndex()));
    QCOMPARE(newItem->modelType(), Constants::PropertyType);
    QCOMPARE(newItem->displayName(), QString("Property"));
    QVERIFY(newItem->value().isValid() == false);
}

//! Testing to/from xml: FullSphereItem

inline void TestSessionXML::test_FullSphereItem()
{
    // source model, to xml
    SessionModel source("TestModel");
    SessionItem* sphere = source.insertNewItem(Constants::FullSphereType);
    SessionItem* radius = sphere->getItem(FullSphereItem::P_RADIUS);
    QString buffer = itemToXML(source.rootItem());

    // target model, from xml
    SessionModel target("TestModel");
    itemFromXML(buffer, target.rootItem());

    // checking top items in source and target models
    SessionItem* t_sphere = target.topItem();
    SessionItem* t_radius = t_sphere->getItem(FullSphereItem::P_RADIUS);

    QCOMPARE(sphere->parent()->tagFromItem(sphere), t_sphere->parent()->tagFromItem(t_sphere));
    QCOMPARE(sphere->displayName(), t_sphere->displayName());
    QCOMPARE(sphere->modelType(), t_sphere->modelType());
    QCOMPARE(sphere->numberOfChildren(), t_sphere->numberOfChildren());
    QCOMPARE(sphere->getItemValue(FullSphereItem::P_RADIUS),
             t_sphere->getItemValue(FullSphereItem::P_RADIUS));

    QCOMPARE(radius->parent()->tagFromItem(sphere), t_radius->parent()->tagFromItem(t_sphere));
    QCOMPARE(radius->displayName(), t_radius->displayName());
    QCOMPARE(radius->modelType(), t_radius->modelType());
    QCOMPARE(radius->numberOfChildren(), t_radius->numberOfChildren());
    QCOMPARE(radius->value().toDouble(), t_radius->value().toDouble());

    // final XML comparison
    QCOMPARE(buffer, itemToXML(target.rootItem()));
}

inline void TestSessionXML::test_twoFullSphereItems()
{
    // source model, to xml
    SessionModel source("TestModel");
    SessionItem* sphere1 = source.insertNewItem(Constants::FullSphereType);
    sphere1->setItemValue(FullSphereItem::P_RADIUS, 1.0);
    SessionItem* sphere2 = source.insertNewItem(Constants::FullSphereType);
    sphere2->setItemValue(FullSphereItem::P_RADIUS, 2.0);
    QString buffer = itemToXML(source.rootItem());

    SessionModel target("TestModel");
    itemFromXML(buffer, target.rootItem());

    // final XML comparison
    QCOMPARE(buffer, itemToXML(target.rootItem()));
}

inline void TestSessionXML::test_emptyMultiLayer()
{
    SessionModel source("TestModel");
    source.insertNewItem(Constants::MultiLayerType);
    QString buffer = itemToXML(source.rootItem());

    SessionModel target("TestModel");
    itemFromXML(buffer, target.rootItem());

    // final XML comparison
    QCOMPARE(buffer, itemToXML(target.rootItem()));
}

inline void TestSessionXML::test_Layer()
{
    SessionModel source("TestModel");
    source.insertNewItem(Constants::LayerType);
    QString buffer = itemToXML(source.rootItem());

    SessionModel target("TestModel");
    itemFromXML(buffer, target.rootItem());

    // final XML comparison
    QCOMPARE(buffer, itemToXML(target.rootItem()));
}

inline void TestSessionXML::test_Particle()
{
    SessionModel source("TestModel");
    source.insertNewItem(Constants::ParticleType);
    QString buffer = itemToXML(source.rootItem());

    SessionModel target("TestModel");
    itemFromXML(buffer, target.rootItem());

    // final XML comparison
    QCOMPARE(buffer, itemToXML(target.rootItem()));
}

inline void TestSessionXML::test_ParticleWithFF()
{
    SessionModel source("TestModel");
    SessionItem* particle = source.insertNewItem(Constants::ParticleType);

    particle->setGroupProperty(ParticleItem::P_FORM_FACTOR, Constants::AnisoPyramidType);
    QString buffer = itemToXML(source.rootItem());

    SessionModel target("TestModel");
    itemFromXML(buffer, target.rootItem());

    // final XML comparison
    QCOMPARE(buffer, itemToXML(target.rootItem()));
}
