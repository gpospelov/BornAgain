#include "MaterialModel.h"
#include "MaterialItem.h"
#include "MaterialDataItem.h"
#include "MaterialItemUtils.h"
#include "MaterialSvc.h"
#include <QtTest>
#include <memory>

class TestMaterialModel : public QObject {
    Q_OBJECT

private slots:
    void test_addMaterial();
    void test_cloneMaterial();
    void test_materialItemFromIdentifier();
    void test_materialItemFromName();
    void test_materialPropertyFromMaterial();
    void test_defaultMaterialProperty();
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

//! Checks the method which returns MaterialItem from material name.

inline void TestMaterialModel::test_materialItemFromName()
{
    MaterialModel model;
    MaterialItem* mat1 = model.addMaterial("aaa", 1.0, 2.0);
    MaterialItem* mat2 = model.addMaterial("bbb", 3.0, 4.0);
    QVERIFY(mat1 == model.materialFromName(mat1->itemName()));
    QVERIFY(mat2 == model.materialFromName(mat2->itemName()));
    QVERIFY(nullptr == model.materialFromName("non-existing-name"));
}

//! Checks the method which construct MaterialProperty from MaterialItem.

inline void TestMaterialModel::test_materialPropertyFromMaterial()
{
    MaterialModel model;
    MaterialSvc svc; // FIXME remove after MaterialSvc gone.
    MaterialItem* mat = model.addMaterial("Something", 1.0, 2.0);

    MaterialProperty property = MaterialItemUtils::materialProperty(*mat);
    QCOMPARE(property.getName(), QString("Something"));
    QCOMPARE(property.getColor(), mat->getColor());
    QCOMPARE(property.getIdentifier(), mat->getIdentifier());

    // FIXME remove checks below after MaterialSvc gone

    // setting new name of material
    mat->setItemName("newname");
    QCOMPARE(property.getName(), QString("newname"));
}

//! Default MaterialProperty construction.

inline void TestMaterialModel::test_defaultMaterialProperty()
{
    MaterialModel model;
    MaterialSvc svc; // FIXME remove after MaterialSvc gone.

    // testing default constructed material property
    MaterialProperty property;
    QCOMPARE(property.getName(), QString("Undefined"));
    QCOMPARE(property.getColor(), QColor(Qt::red));
    QCOMPARE(property.getIdentifier(), QString(""));

    // testing default material property from MaterialItemUtils
    MaterialProperty property2 = MaterialItemUtils::defaultMaterialProperty();
    QCOMPARE(property2.getName(), QString("Undefined"));
    QCOMPARE(property2.getColor(), QColor(Qt::red));
    QCOMPARE(property2.getIdentifier(), QString(""));

    // adding materials to the model, default property should refer to first material in a model
    auto mat1 = model.addMaterial("Something1", 1.0, 2.0);
    model.addMaterial("Something2", 3.0, 4.0);
    MaterialProperty property3 = MaterialItemUtils::defaultMaterialProperty();
    QCOMPARE(property3.getName(), QString("Something1"));
    QCOMPARE(property3.getColor(), mat1->getColor());
    QCOMPARE(property3.getIdentifier(), mat1->getIdentifier());
}
