#include <QtTest>
#include "ModelUtils.h"
#include "SessionModel.h"
#include "item_constants.h"
#include "ComponentProxyModel.h"
#include <QSignalSpy>

class TestComponentProxyModel : public QObject
{
    Q_OBJECT
public:

private slots:
    void test_emptyModel();
    void test_setModel();
};

//! Testing iteration over empty model.

inline void TestComponentProxyModel::test_emptyModel()
{
    ComponentProxyModel proxy;
    QCOMPARE(proxy.rowCount(QModelIndex()), 0);
    QCOMPARE(proxy.columnCount(QModelIndex()), static_cast<int>(SessionModel::MAX_COLUMNS));
    QVERIFY(proxy.sourceModel() == nullptr);
}

inline void TestComponentProxyModel::test_setModel()
{
    SessionModel model("TestModel");
    ComponentProxyModel proxy;

    QSignalSpy spy(&proxy, &ComponentProxyModel::modelReset);
    proxy.setSessionModel(&model);

    QCOMPARE(spy.count(), 1);
    QCOMPARE(proxy.rowCount(QModelIndex()), 0);
    QCOMPARE(proxy.columnCount(QModelIndex()), static_cast<int>(SessionModel::MAX_COLUMNS));
}
