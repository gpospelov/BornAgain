#include "MaterialDataItems.h"
#include "MaterialItem.h"
#include "MaterialItemUtils.h"
#include "MaterialModel.h"
#include "google_test.h"
#include <memory>

class TestMaterialModel : public ::testing::Test
{
public:
    ~TestMaterialModel();
};

TestMaterialModel::~TestMaterialModel() = default;

TEST_F(TestMaterialModel, test_ParticeleCompositionUpdate)
{
    std::unique_ptr<MaterialModel> model(new MaterialModel);

    EXPECT_EQ(model->rowCount(QModelIndex()), 0);

    const double delta(0.2), beta(0.1);
    const QString name("MaterialName");
    MaterialItem* item = model->addRefractiveMaterial(name, delta, beta);

    EXPECT_EQ(model->rowCount(QModelIndex()), 1);
    EXPECT_EQ(model->itemForIndex(item->index()), item);
    EXPECT_EQ(model->rowCount(QModelIndex()), 1);

    EXPECT_EQ(item->itemName(), name);
    auto materialData = item->getGroupItem(MaterialItem::P_MATERIAL_DATA);
    EXPECT_EQ(materialData->getItemValue(MaterialRefractiveDataItem::P_DELTA), delta);
    EXPECT_EQ(materialData->getItemValue(MaterialRefractiveDataItem::P_BETA), beta);
}

TEST_F(TestMaterialModel, test_cloneMaterial)
{
    std::unique_ptr<MaterialModel> model(new MaterialModel);

    EXPECT_EQ(model->rowCount(QModelIndex()), 0);

    const double delta(0.2), beta(0.1);
    const QString name("MaterialName");
    MaterialItem* item = model->addRefractiveMaterial(name, delta, beta);
    const QString origIdentifier = item->identifier();

    MaterialItem* clonedMaterial = model->cloneMaterial(item->index());
    EXPECT_EQ(model->rowCount(QModelIndex()), 2);

    // clone should not change identifier of original material (as it once happened)
    EXPECT_EQ(item->identifier(), origIdentifier);

    // cloned material should have different identifier
    EXPECT_TRUE(clonedMaterial->identifier() != item->identifier());

    // checking name of cloned material
    EXPECT_EQ(item->itemName() + " (clone)", clonedMaterial->itemName());

    auto materialData = clonedMaterial->getGroupItem(MaterialItem::P_MATERIAL_DATA);
    EXPECT_EQ(materialData->getItemValue(MaterialRefractiveDataItem::P_DELTA), delta);
    EXPECT_EQ(materialData->getItemValue(MaterialRefractiveDataItem::P_BETA), beta);
}

//! Checks the method which returns MaterialItem from known identifier.

TEST_F(TestMaterialModel, test_materialItemFromIdentifier)
{
    MaterialModel model;
    MaterialItem* mat1 = model.addRefractiveMaterial("aaa", 1.0, 2.0);
    MaterialItem* mat2 = model.addRefractiveMaterial("bbb", 3.0, 4.0);
    EXPECT_TRUE(mat1 == model.materialFromIdentifier(mat1->identifier()));
    EXPECT_TRUE(mat2 == model.materialFromIdentifier(mat2->identifier()));
    EXPECT_TRUE(nullptr == model.materialFromIdentifier("non-existing-identifier"));
}

//! Checks the method which returns MaterialItem from material name.

TEST_F(TestMaterialModel, test_materialItemFromName)
{
    MaterialModel model;
    MaterialItem* mat1 = model.addRefractiveMaterial("aaa", 1.0, 2.0);
    MaterialItem* mat2 = model.addRefractiveMaterial("bbb", 3.0, 4.0);
    EXPECT_TRUE(mat1 == model.materialFromName(mat1->itemName()));
    EXPECT_TRUE(mat2 == model.materialFromName(mat2->itemName()));
    EXPECT_TRUE(nullptr == model.materialFromName("non-existing-name"));
}

//! Checks the method which construct MaterialProperty from MaterialItem.

TEST_F(TestMaterialModel, test_materialPropertyFromMaterial)
{
    MaterialModel model;
    MaterialItem* mat = model.addRefractiveMaterial("Something", 1.0, 2.0);

    ExternalProperty property = MaterialItemUtils::materialProperty(*mat);
    EXPECT_EQ(property.text(), QString("Something"));
    EXPECT_EQ(property.color(), mat->color());
    EXPECT_EQ(property.identifier(), mat->identifier());
}

//! Default MaterialProperty construction.

TEST_F(TestMaterialModel, test_defaultMaterialProperty)
{
    MaterialModel model;

    // testing default material property from MaterialItemUtils
    // in the absence of any materials, property should be in invalid state
    ExternalProperty property = MaterialItemUtils::defaultMaterialProperty();
    EXPECT_TRUE(property.isValid() == false);

    // adding materials to the model, default property should refer to first material in a model
    auto mat1 = model.addRefractiveMaterial("Something1", 1.0, 2.0);
    model.addRefractiveMaterial("Something2", 3.0, 4.0);
    ExternalProperty property2 = MaterialItemUtils::defaultMaterialProperty();
    EXPECT_EQ(property2.text(), QString("Something1"));
    EXPECT_EQ(property2.color(), mat1->color());
    EXPECT_EQ(property2.identifier(), mat1->identifier());
}
