#include "MaterialModel.h"
#include "MaterialItem.h"
#include "MaterialDataItem.h"
#include <QtTest>
#include <memory>

class TestMaterialModel : public QObject {
    Q_OBJECT

private slots:
    void test_addMaterial();
    void test_cloneMaterial();
    void test_materialItemFromIdentifier();
};

inline void TestMaterialModel::test_addMaterial()
{
    std::unique_ptr<MaterialModel> model(new MaterialModel);

    QCOMPARE(model->rowCount(QModelIndex()), 0);

    const double delta(0.2), beta(0.1);
    const QString name("MaterialName");
    MaterialItem *item = model->addMaterial(name, delta, beta);

    QCOMPARE(model->rowCount(QModelIndex()), 1);
    QCOMPARE(model->itemForIndex(item->index()), item);
    QCOMPARE(model->rowCount(QModelIndex()), 1);

    QCOMPARE(item->itemName(), name);
    const MaterialDataItem *refIndex = dynamic_cast<const MaterialDataItem *>(
        item->getItem(MaterialItem::P_MATERIAL_DATA));
    QCOMPARE(refIndex->getReal(), delta);
    QCOMPARE(refIndex->getImag(), beta);

}

inline void TestMaterialModel::test_cloneMaterial()
{
    std::unique_ptr<MaterialModel> model(new MaterialModel);

    QCOMPARE(model->rowCount(QModelIndex()), 0);

    const double delta(0.2), beta(0.1);
    const QString name("MaterialName");
    MaterialItem *item = model->addMaterial(name, delta, beta);
    const QString origIdentifier = item->getIdentifier();

    MaterialItem *clonedMaterial = model->cloneMaterial(item->index());
    QCOMPARE(model->rowCount(QModelIndex()), 2);

    // clone should not change identifier of original material (as it once happened)
    QCOMPARE(item->getIdentifier(), origIdentifier);

    // cloned material should have different identifier
    QVERIFY(clonedMaterial->getIdentifier() != item->getIdentifier());

    // checking name of cloned material
    QCOMPARE(item->itemName()+" (clone)", clonedMaterial->itemName());

    const MaterialDataItem *refIndex = dynamic_cast<const MaterialDataItem *>(
        clonedMaterial->getItem(MaterialItem::P_MATERIAL_DATA));
    QCOMPARE(refIndex->getReal(), delta);
    QCOMPARE(refIndex->getImag(), beta);
}

//! Checks the method which returns MaterialItem from known identifier.

inline void TestMaterialModel::test_materialItemFromIdentifier()
{
    MaterialModel model;
    MaterialItem* mat1 = model.addMaterial("aaa", 1.0, 2.0);
    MaterialItem* mat2 = model.addMaterial("bbb", 3.0, 4.0);
    QVERIFY(mat1 == model.materialFromIdentifier(mat1->getIdentifier()));
    QVERIFY(mat2 == model.materialFromIdentifier(mat2->getIdentifier()));
    QVERIFY(nullptr == model.materialFromIdentifier("non-existing-identifier"));
}
