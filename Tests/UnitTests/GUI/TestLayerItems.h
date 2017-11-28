#include <QtTest>
#include "LayerItem.h"
#include "MaterialProperty.h"
#include "ApplicationModels.h"
#include "SampleModel.h"
#include "MaterialModel.h"
#include "MaterialItem.h"
#include "ModelMapper.h"

//! Tests for LayerItem

class TestLayerItems : public QObject {
    Q_OBJECT

private slots:
    void test_LayerDefaultMaterial();
//    void test_onMaterialChange();
};

//! Checking default material of the layer.

inline void TestLayerItems::test_LayerDefaultMaterial()
{
    ApplicationModels models;
    auto layer = models.sampleModel()->insertNewItem(Constants::LayerType);
    auto materials = models.materialModel()->topItems();
    auto defMaterial = materials.front();

    MaterialProperty material = layer->getItemValue(LayerItem::P_MATERIAL).value<MaterialProperty>();
    QCOMPARE(material.getName(), QString("Default"));
    QCOMPARE(material.getIdentifier(), defMaterial->getItemValue(MaterialItem::P_IDENTIFIER).toString());
}

//! Checks that change of material in MaterialModel is propagated to the LayerItem.

//inline void TestLayerItems::test_onMaterialChange()
//{
//    ApplicationModels models;
//    auto layer = models.sampleModel()->insertNewItem(Constants::LayerType);
//    auto materials = models.materialModel()->topItems();
//    auto defMaterial = materials.front();

//    int property_changed(0);
//    layer->mapper()->setOnPropertyChange([&property_changed](const QString& name) {
//        if (name == LayerItem::P_MATERIAL)
//            ++property_changed;
//    }, this);

//    defMaterial->setItemName("NewName");
//    QCOMPARE(property_changed, 2); // should be ==1, Fixme after implementing MaterialPropertyController
//    MaterialProperty material = layer->getItemValue(LayerItem::P_MATERIAL).value<MaterialProperty>();

//    // FIXME reenable after MaterialPropertyController implementation
////    QCOMPARE(material.getName(), QString("NewName"));
//}
