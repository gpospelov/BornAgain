#include <QtTest>
#include "ModelUtils.h"
#include "SessionModel.h"
#include "item_constants.h"
#include "VectorItem.h"
#include <QVector>
#include <QDebug>

class TestModelUtils : public QObject
{
    Q_OBJECT
public:

private slots:
    void test_emptyModel();
    void test_vectorItem();
};

//! Testing iteration over empty model.

inline void TestModelUtils::test_emptyModel()
{
    SessionModel model("TestModel");

    QVector<QModelIndex> indices;

    ModelUtils::iterate(QModelIndex(), &model, [&](const QModelIndex& index){
        indices.push_back(index);
    });

    QCOMPARE(indices.size(), 0);
}

//! Testing iteration over the model with one VectorItem inserted.

inline void TestModelUtils::test_vectorItem()
{
    SessionModel model("TestModel");
    SessionItem* vectorItem = model.insertNewItem(Constants::VectorType);

    QVector<QModelIndex> indices;

    // checking indices visited during iteration
    ModelUtils::iterate(QModelIndex(), &model, [&](const QModelIndex& index){
        indices.push_back(index);
    });
    QCOMPARE(indices.size(), 8); // (VectorItem, P_X, P_Y, P_Z) x (row, col)

    indices.clear();
    ModelUtils::iterate(QModelIndex(), &model, [&](const QModelIndex& index){
        if (index.column() == 0)
            indices.push_back(index);
    });

    // checking SessionItems visited during the iteration
    QCOMPARE(indices.size(), 4); // (VectorItem, P_X, P_Y, P_Z) x (row, col)
    QCOMPARE(model.itemForIndex(indices.front()), vectorItem);
    QCOMPARE(model.itemForIndex(indices.back()), vectorItem->getItem(VectorItem::P_Z));
}
