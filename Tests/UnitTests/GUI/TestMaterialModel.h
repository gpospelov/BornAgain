#ifndef TESTMATERIALMODEL_H
#define TESTMATERIALMODEL_H

#include "MaterialModel.h"
#include "MaterialItem.h"
#include "RefractiveIndexItem.h"
#include <QtTest>
#include <memory>

class TestMaterialModel : public QObject {
    Q_OBJECT

private slots:
    void test_addMaterial();
    void test_cloneMaterial();
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
    const RefractiveIndexItem *refIndex = dynamic_cast<const RefractiveIndexItem *>(
        item->getItem(MaterialItem::P_REFRACTIVE_INDEX));
    QCOMPARE(refIndex->getDelta(), delta);
    QCOMPARE(refIndex->getBeta(), beta);

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

    const RefractiveIndexItem *refIndex = dynamic_cast<const RefractiveIndexItem *>(
        clonedMaterial->getItem(MaterialItem::P_REFRACTIVE_INDEX));
    QCOMPARE(refIndex->getDelta(), delta);
    QCOMPARE(refIndex->getBeta(), beta);


}

#endif // TESTMATERIALMODEL_H
