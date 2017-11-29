#include <QtTest>
#include "MaterialPropertyController.h"
#include "MaterialModel.h"
#include "SampleModel.h"
#include "LayerItem.h"
#include "MaterialItem.h"
#include "MaterialProperty.h"
#include "ColorProperty.h"
#include "MaterialItemUtils.h"

class TestMaterialPropertyController : public QObject
{
    Q_OBJECT
public:

private slots:
    void test_ControllerForLayer();
    void test_ControllerInEditorContext();
};


inline void TestMaterialPropertyController::test_ControllerForLayer()
{
    MaterialModel materialModel;
    auto mat1 = materialModel.addMaterial("name1", 1.0, 2.0);
    materialModel.addMaterial("name2", 3.0, 4.0);

    SampleModel sampleModel;
    auto layer = sampleModel.insertNewItem(Constants::LayerType);

    int property_changed(0);
    layer->mapper()->setOnPropertyChange([&property_changed](const QString& name) {
        if (name == LayerItem::P_MATERIAL)
            ++property_changed;
    }, this);

    MaterialPropertyController controller;
    controller.setModels(&materialModel, &sampleModel);
    QCOMPARE(property_changed, 0);

    // changing name of MaterialItem in MaterialModel, looking for MaterialProperty change
    mat1->setItemName("newname");
//    QCOMPARE(property_changed, 1);
    MaterialProperty property = layer->getItemValue(LayerItem::P_MATERIAL).value<MaterialProperty>();
    QCOMPARE(property.getIdentifier(), mat1->getIdentifier());
    QCOMPARE(property.getName(), mat1->itemName());
    QCOMPARE(property.getColor(), mat1->getColor());

    // changing color of MaterialItem
    ColorProperty colorProperty(Qt::red);
    mat1->setItemValue(MaterialItem::P_COLOR, colorProperty.getVariant());
//    QCOMPARE(property_changed, 2);
    property = layer->getItemValue(LayerItem::P_MATERIAL).value<MaterialProperty>();
    QCOMPARE(property.getIdentifier(), mat1->getIdentifier());
    QCOMPARE(property.getName(), mat1->itemName());
    QCOMPARE(property.getColor(), mat1->getColor());
    QCOMPARE(property.getColor(), QColor(Qt::red));

    // removing material from the model, property should become undefined
    materialModel.removeRows(0, 1, QModelIndex());
//    QCOMPARE(property_changed, 3);
    property = layer->getItemValue(LayerItem::P_MATERIAL).value<MaterialProperty>();
    QCOMPARE(property.getIdentifier(), QString());
    QCOMPARE(property.getName(), QString("Undefined"));
    QCOMPARE(property.getColor(), QColor(Qt::red));
}

//! Test MaterialProperty update in sample items when working on model clone.

inline void TestMaterialPropertyController::test_ControllerInEditorContext()
{
    MaterialModel materialModel;
    auto mat1 = materialModel.addMaterial("name1", 1.0, 2.0);
    auto mat2 = materialModel.addMaterial("name2", 1.0, 2.0);
    auto mat3 = materialModel.addMaterial("name3", 1.0, 2.0);

    SampleModel sampleModel;
    auto layer1 = sampleModel.insertNewItem(Constants::LayerType);
    auto layer2 = sampleModel.insertNewItem(Constants::LayerType);
    auto layer3 = sampleModel.insertNewItem(Constants::LayerType);

    MaterialPropertyController controller;
    controller.setModels(&materialModel, &sampleModel);

    layer1->setItemValue(LayerItem::P_MATERIAL, MaterialItemUtils::materialProperty(*mat1).getVariant());
    layer2->setItemValue(LayerItem::P_MATERIAL, MaterialItemUtils::materialProperty(*mat2).getVariant());
    layer3->setItemValue(LayerItem::P_MATERIAL, MaterialItemUtils::materialProperty(*mat3).getVariant());

    // Making copy of material model
    std::unique_ptr<MaterialModel> materialsCopy(materialModel.createCopy());
    auto mat1copy = dynamic_cast<MaterialItem*>(materialsCopy->itemForIndex(materialsCopy->index(0, 0, QModelIndex())));
    auto mat2copy = dynamic_cast<MaterialItem*>(materialsCopy->itemForIndex(materialsCopy->index(1, 0, QModelIndex())));
    auto mat3copy = dynamic_cast<MaterialItem*>(materialsCopy->itemForIndex(materialsCopy->index(2, 0, QModelIndex())));
    QCOMPARE(mat1->getColor(), mat1copy->getColor());
    QCOMPARE(mat1->itemName(), mat1copy->itemName());
    QCOMPARE(mat1->getIdentifier(), mat1copy->getIdentifier());
    QCOMPARE(mat2->getColor(), mat2copy->getColor());
    QCOMPARE(mat2->itemName(), mat2copy->itemName());
    QCOMPARE(mat2->getIdentifier(), mat2copy->getIdentifier());
    QCOMPARE(mat3->itemName(), mat3copy->itemName());
    QCOMPARE(mat3->getIdentifier(), mat3copy->getIdentifier());

    // Removing mat2 from the copy
    materialsCopy->removeRows(1, 1, QModelIndex());
    mat1copy = dynamic_cast<MaterialItem*>(materialsCopy->itemForIndex(materialsCopy->index(0, 0, QModelIndex())));
    mat3copy = dynamic_cast<MaterialItem*>(materialsCopy->itemForIndex(materialsCopy->index(1, 0, QModelIndex())));
    QCOMPARE(mat1->getColor(), mat1copy->getColor());
    QCOMPARE(mat1->itemName(), mat1copy->itemName());
    QCOMPARE(mat3->getColor(), mat3copy->getColor());
    QCOMPARE(mat3->itemName(), mat3copy->itemName());

    // changing mat3
    mat3copy->setItemName("name3changed");

    // copying back to original model
    materialModel.clear();
    materialModel.initFrom(materialsCopy.get(), 0);
    materialModel.createdFromCopy();

    // layer2 should have undefined material property
    MaterialProperty property = layer2->getItemValue(LayerItem::P_MATERIAL).value<MaterialProperty>();
    QCOMPARE(property.getName(), QString("Undefined"));
    QCOMPARE(property.getIdentifier(), QString(""));
    QCOMPARE(property.getColor(), QColor(Qt::red));

    // layer3 should have different MaterialProperty name
    property = layer3->getItemValue(LayerItem::P_MATERIAL).value<MaterialProperty>();
    QCOMPARE(property.getName(), QString("name3changed"));
}
