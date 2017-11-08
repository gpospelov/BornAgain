#include <QtTest>
#include "ModelUtils.h"
#include "SessionModel.h"
#include "item_constants.h"
#include "ComponentProxyModel.h"

class TestComponentProxyModel : public QObject
{
    Q_OBJECT
public:

private slots:
    void test_emptyModel();
};

//! Testing iteration over empty model.

inline void TestComponentProxyModel::test_emptyModel()
{
    SessionModel model("TestModel");
    ComponentProxyModel proxy;

    proxy.setSessionModel(&model);
    QCOMPARE(proxy.rowCount(QModelIndex()), 0);
    QCOMPARE(proxy.columnCount(QModelIndex()), static_cast<int>(SessionModel::MAX_COLUMNS));
}
