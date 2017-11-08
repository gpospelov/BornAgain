#include <QtTest>
#include "ModelUtils.h"
#include "SessionModel.h"
#include "item_constants.h"
#include "ComponentProxyModel.h"
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

//! Set model to proxy. Model contains simple item.

inline void TestComponentProxyModel::test_setModelWithItem()
{
    SessionModel model("TestModel");
    model.insertNewItem(Constants::PropertyType);

    ComponentProxyModel proxy;
    proxy.setSessionModel(&model);

    QCOMPARE(model.rowCount(QModelIndex()), 1);
    QCOMPARE(model.columnCount(QModelIndex()), static_cast<int>(SessionModel::MAX_COLUMNS));
    QCOMPARE(proxy.rowCount(QModelIndex()), 1);
}
