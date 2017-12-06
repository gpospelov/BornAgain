#include <QtTest>
#include "LayerItem.h"
#include "ExternalProperty.h"
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
};

//! Checking default material of the layer.

inline void TestLayerItems::test_LayerDefaultMaterial()
{
    ApplicationModels models;
    auto layer = models.sampleModel()->insertNewItem(Constants::LayerType);
    auto materials = models.materialModel()->topItems();
    auto defMaterial = materials.front();

    ExternalProperty material = layer->getItemValue(LayerItem::P_MATERIAL).value<ExternalProperty>();
    QCOMPARE(material.text(), QString("Default"));
    QCOMPARE(material.identifier(), defMaterial->getItemValue(MaterialItem::P_IDENTIFIER).toString());
}
