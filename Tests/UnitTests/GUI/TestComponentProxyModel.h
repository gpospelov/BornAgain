#include <QtTest>
#include "ModelUtils.h"
#include "SessionModel.h"
#include "item_constants.h"
#include "ComponentProxyModel.h"
#include "VectorItem.h"
#include <QSignalSpy>
#include <QDebug>

class TestComponentProxyModel : public QObject
{
    Q_OBJECT
public:

private slots:
    void test_emptyModel();
    void test_setModel();
    void test_setModelWithItem();
    void test_setModelWithVector();
    void test_displayRole();
};

//! Empty proxy model.

inline void TestComponentProxyModel::test_emptyModel()
{
    ComponentProxyModel proxy;
    QCOMPARE(proxy.rowCount(QModelIndex()), 0);
    QCOMPARE(proxy.columnCount(QModelIndex()), static_cast<int>(SessionModel::MAX_COLUMNS));
    QVERIFY(proxy.sourceModel() == nullptr);
}

//! Set empty model to proxy.

inline void TestComponentProxyModel::test_setModel()
{
    SessionModel model("TestModel");
    ComponentProxyModel proxy;

    QSignalSpy spy(&proxy, &ComponentProxyModel::modelReset);
    proxy.setSessionModel(&model);

    QCOMPARE(spy.count(), 1);
    QCOMPARE(proxy.rowCount(QModelIndex()), 0);
    QCOMPARE(proxy.columnCount(QModelIndex()), static_cast<int>(SessionModel::MAX_COLUMNS));
    QCOMPARE(proxy.sourceModel(), &model);
}

//! Set model to proxy. Model already contains simple item.

inline void TestComponentProxyModel::test_setModelWithItem()
{
    SessionModel model("TestModel");
    model.insertNewItem(Constants::PropertyType);

    ComponentProxyModel proxy;
    proxy.setSessionModel(&model);

    QCOMPARE(model.rowCount(QModelIndex()), 1);
    QCOMPARE(model.columnCount(QModelIndex()), static_cast<int>(SessionModel::MAX_COLUMNS));
    QCOMPARE(proxy.rowCount(QModelIndex()), 1);
    QCOMPARE(proxy.columnCount(QModelIndex()), static_cast<int>(SessionModel::MAX_COLUMNS));
}

//! Set model to proxy. Model already contains VectorItem.

inline void TestComponentProxyModel::test_setModelWithVector()
{
    const int ncols = static_cast<int>(SessionModel::MAX_COLUMNS);

    SessionModel model("TestModel");
    SessionItem* item = model.insertNewItem(Constants::VectorType);
    item->setItemValue(VectorItem::P_X, 1.0);
    item->setItemValue(VectorItem::P_Y, 2.0);
    item->setItemValue(VectorItem::P_Z, 3.0);

    ComponentProxyModel proxy;
    proxy.setSessionModel(&model);

    // rows, cols of root index
    QCOMPARE(model.rowCount(QModelIndex()), 1);
    QCOMPARE(model.columnCount(QModelIndex()), ncols);
    QCOMPARE(proxy.rowCount(QModelIndex()), 1);
    QCOMPARE(proxy.columnCount(QModelIndex()), ncols);

    // mapFromSource, mapToSource for VectorItem
    QModelIndex sourceVector = model.index(0, 0, QModelIndex());
    QModelIndex proxyVector = proxy.index(0, 0, QModelIndex());
    QVERIFY(sourceVector != proxyVector);
    QVERIFY(sourceVector.internalPointer() == proxyVector.internalPointer());
    QCOMPARE(proxyVector, proxy.mapFromSource(sourceVector));
    QCOMPARE(sourceVector, proxy.mapToSource(proxyVector));

    // rows, cols of VectorItem
    QCOMPARE(model.rowCount(sourceVector), 3); // x,y,z
    QCOMPARE(model.columnCount(sourceVector), ncols);
    QCOMPARE(proxy.rowCount(proxyVector), 3); // x,y,z
    QCOMPARE(proxy.columnCount(proxyVector), ncols);

    // mapFromSource, mapToSource for P_X
    QModelIndex sourceX = model.index(0, 0, sourceVector);
    QModelIndex proxyX = proxy.index(0, 0, proxyVector);
    QVERIFY(sourceX != proxyX);
    QVERIFY(sourceX.internalPointer() == proxyX.internalPointer());
    QCOMPARE(proxyX, proxy.mapFromSource(sourceX));
    QCOMPARE(sourceX, proxy.mapToSource(proxyX));

    // rows, cols of P_X
    QCOMPARE(model.rowCount(sourceX), 0);
    QCOMPARE(model.columnCount(sourceX), ncols);
    QCOMPARE(proxy.rowCount(proxyX), 0);
    QCOMPARE(proxy.columnCount(proxyX), ncols);

    // mapFromSource, mapToSource for P_Z
    QModelIndex sourceZ = model.index(2, 0, sourceVector);
    QModelIndex proxyZ = proxy.index(2, 0, proxyVector);
    QVERIFY(sourceZ != proxyZ);
    QVERIFY(sourceZ.internalPointer() == proxyZ.internalPointer());
    QCOMPARE(proxyZ, proxy.mapFromSource(sourceZ));
    QCOMPARE(sourceZ, proxy.mapToSource(proxyZ));

    // rows, cols of P_Z
    QCOMPARE(model.rowCount(sourceZ), 0);
    QCOMPARE(model.columnCount(sourceZ), ncols);
    QCOMPARE(proxy.rowCount(proxyZ), 0);
    QCOMPARE(proxy.columnCount(proxyZ), ncols);
}

//! Set model to proxy. Model already contains two PropertyItems. Checking data() method.

inline void TestComponentProxyModel::test_displayRole()
{
    SessionModel model("TestModel");
    SessionItem* item1 = model.insertNewItem(Constants::PropertyType);
    item1->setValue(1.0);
    SessionItem* item2 = model.insertNewItem(Constants::PropertyType);
    item2->setValue(2.0);

    QCOMPARE(model.data(model.index(0, 1, QModelIndex()), Qt::DisplayRole).toDouble(), 1.0);
    QCOMPARE(model.data(model.index(1, 1, QModelIndex()), Qt::DisplayRole).toDouble(), 2.0);

    ComponentProxyModel proxy;
    proxy.setSessionModel(&model);

    QCOMPARE(proxy.data(proxy.index(0, 1, QModelIndex()), Qt::DisplayRole).toDouble(), 1.0);
    QCOMPARE(proxy.data(proxy.index(1, 1, QModelIndex()), Qt::DisplayRole).toDouble(), 2.0);
}
