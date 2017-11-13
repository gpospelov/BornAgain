#include <QtTest>
#include "ModelUtils.h"
#include "SessionModel.h"
#include "item_constants.h"
#include "ComponentProxyModel.h"
#include "ProxyModelStrategy.h"
#include "VectorItem.h"
#include "ParticleItem.h"
#include "FormFactorItems.h"
#include <QSignalSpy>
#include <QDebug>

class TestProxyModelStrategy : public QObject
{
    Q_OBJECT
public:

private slots:
    void test_identityStrategy();
    void test_identityStrategyParticle();
    void test_componentStrategyParticle();
};

//! Checking the mapping in the case of PropertyItem inserted in the source.

inline void TestProxyModelStrategy::test_identityStrategy()
{
    SessionModel model("TestModel");
    ComponentProxyModel proxy;
    IndentityProxyStrategy strategy;

    QCOMPARE(strategy.sourceToProxy().size(), 0);
    QCOMPARE(strategy.proxySourceParent().size(), 0);

    // building the map of empty source
    strategy.buildModelMap(&model, &proxy);
    QCOMPARE(strategy.sourceToProxy().size(), 0);
    QCOMPARE(strategy.proxySourceParent().size(), 0);

    // building map when simple item
    SessionItem* item = model.insertNewItem(Constants::PropertyType);
    strategy.buildModelMap(&model, &proxy);
    QCOMPARE(strategy.sourceToProxy().size(), 2);
    QCOMPARE(strategy.proxySourceParent().size(), 2);

    // Checking of persistent indices of source and proxy
    auto it = strategy.sourceToProxy().begin();
    // index of source, col=0
    QCOMPARE(it.key().row(), 0);
    QCOMPARE(it.key().column(), 0);
    QCOMPARE(it.key().internalPointer(), item);
    // index of proxy, col=0
    QCOMPARE(it.value().row(), 0);
    QCOMPARE(it.value().column(), 0);
    QCOMPARE(it.value().internalPointer(), item);
    ++it;
    // index of source, col=1
    QCOMPARE(it.key().row(), 0);
    QCOMPARE(it.key().column(), 1);
    QCOMPARE(it.key().internalPointer(), item);
    // index of proxy, col=1
    QCOMPARE(it.value().row(), 0);
    QCOMPARE(it.value().column(), 1);
    QCOMPARE(it.value().internalPointer(), item);

    // Checking parent of proxy
    it = strategy.proxySourceParent().begin();
    QCOMPARE(it.key().row(), 0);
    QCOMPARE(it.key().column(), 0);
    QCOMPARE(it.key().internalPointer(), item);
    QVERIFY(it.value() == QModelIndex());
}

//! Checking the mapping in the case of ParticleItem inserted in the source.

inline void TestProxyModelStrategy::test_identityStrategyParticle()
{
    SessionModel model("TestModel");
    ComponentProxyModel proxy;
    IndentityProxyStrategy strategy;

    SessionItem* item = model.insertNewItem(Constants::ParticleType);

    // building the map of source
    strategy.buildModelMap(&model, &proxy);
    SessionItem* group = item->getItem(ParticleItem::P_FORM_FACTOR);
    SessionItem* ffItem = item->getGroupItem(ParticleItem::P_FORM_FACTOR);
    QVERIFY(ffItem->parent() == group);
    QVERIFY(ffItem->modelType() == Constants::CylinderType);

    // Checking "real" parent of proxy index related to form factor.
    // For identity model we are testing, it has to be just group property.
    auto ffProxyIndex = strategy.sourceToProxy().value(model.indexOfItem(ffItem));
    auto parentOfProxy = strategy.proxySourceParent().value(ffProxyIndex);
    QVERIFY(parentOfProxy == model.indexOfItem(group));

    // Checking "real" parent of Cylinders radius. It has to be CylinderItem
    SessionItem* radiusItem = ffItem->getItem(CylinderItem::P_RADIUS);
    auto radiusProxyIndex = strategy.sourceToProxy().value(model.indexOfItem(radiusItem));
    parentOfProxy = strategy.proxySourceParent().value(radiusProxyIndex);
    QVERIFY(parentOfProxy == model.indexOfItem(ffItem));
}

//! Checking the mapping of ComponentProxyStrategy in the case of ParticleItem inserted in
//! the source.

inline void TestProxyModelStrategy::test_componentStrategyParticle()
{
    SessionModel model("TestModel");
    ComponentProxyModel proxy;
    ComponentProxyStrategy strategy;

    SessionItem* item = model.insertNewItem(Constants::ParticleType);

    // building the map of  source
    strategy.buildModelMap(&model, &proxy);
    SessionItem* group = item->getItem(ParticleItem::P_FORM_FACTOR);
    SessionItem* ffItem = item->getGroupItem(ParticleItem::P_FORM_FACTOR);
    QVERIFY(ffItem->parent() == group);
    QVERIFY(ffItem->modelType() == Constants::CylinderType);

    // original indices
    QModelIndex particleIndex = model.indexOfItem(item);
    QModelIndex groupIndex = model.indexOfItem(group);
    QModelIndex ffIndex = model.indexOfItem(ffItem);
    QModelIndex radiusIndex = model.indexOfItem(ffItem->getItem(CylinderItem::P_RADIUS));

    // proxy indices
    QModelIndex particleProxyIndex = strategy.sourceToProxy().value(particleIndex);
    QModelIndex groupProxyIndex = strategy.sourceToProxy().value(groupIndex);
    QModelIndex ffProxyIndex = strategy.sourceToProxy().value(ffIndex);
    QModelIndex radiusProxyIndex = strategy.sourceToProxy().value(radiusIndex);
    QVERIFY(particleProxyIndex.isValid());
    QVERIFY(groupProxyIndex.isValid());
    QVERIFY(ffProxyIndex.isValid() == false); // ff is excluded from hierarchy
    QVERIFY(radiusProxyIndex.isValid());

    // Checking "real" parents of indices
    QVERIFY(strategy.proxySourceParent().value(ffProxyIndex) == QModelIndex());
    QVERIFY(strategy.proxySourceParent().value(radiusProxyIndex) == groupIndex);
    QVERIFY(strategy.proxySourceParent().value(groupProxyIndex) == particleIndex);
}

