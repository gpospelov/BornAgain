#include <QtTest>
#include "MaterialPropertyController.h"
#include "MaterialModel.h"
#include "SampleModel.h"
#include "LayerItem.h"
#include "MaterialItem.h"
#include "MaterialProperty.h"
#include "ColorProperty.h"

class TestMaterialPropertyController : public QObject
{
    Q_OBJECT
public:

private slots:
    void test_ControllerForLayer();
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
    QCOMPARE(property_changed, 1);
    MaterialProperty property = layer->getItemValue(LayerItem::P_MATERIAL).value<MaterialProperty>();
    QCOMPARE(property.getIdentifier(), mat1->getIdentifier());
    QCOMPARE(property.getName(), mat1->itemName());
    QCOMPARE(property.getColor(), mat1->getColor());

    // changing color of MaterialItem
    ColorProperty colorProperty(Qt::red);
    mat1->setItemValue(MaterialItem::P_COLOR, colorProperty.getVariant());
    QCOMPARE(property_changed, 2);
    property = layer->getItemValue(LayerItem::P_MATERIAL).value<MaterialProperty>();
    QCOMPARE(property.getIdentifier(), mat1->getIdentifier());
    QCOMPARE(property.getName(), mat1->itemName());
    QCOMPARE(property.getColor(), mat1->getColor());
    QCOMPARE(property.getColor(), QColor(Qt::red));

    // removing material from the model, property should become undefined
    materialModel.removeRows(0, 1, QModelIndex());
    QCOMPARE(property_changed, 3);
    property = layer->getItemValue(LayerItem::P_MATERIAL).value<MaterialProperty>();
    QCOMPARE(property.getIdentifier(), QString());
    QCOMPARE(property.getName(), QString("Undefined"));
    QCOMPARE(property.getColor(), QColor(Qt::red));
}
