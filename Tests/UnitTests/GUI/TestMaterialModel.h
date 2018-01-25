#include "google_test.h"
#include "MaterialModel.h"
#include "MaterialItem.h"
#include "MaterialDataItem.h"
#include "MaterialItemUtils.h"
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
    MaterialItem* item = model->addMaterial(name, delta, beta);

    EXPECT_EQ(model->rowCount(QModelIndex()), 1);
    EXPECT_EQ(model->itemForIndex(item->index()), item);
    EXPECT_EQ(model->rowCount(QModelIndex()), 1);

    EXPECT_EQ(item->itemName(), name);
    auto& materialDataItem = item->groupItem<MaterialDataItem>(MaterialItem::P_MATERIAL_DATA);
    EXPECT_EQ(materialDataItem.getReal(), delta);
    EXPECT_EQ(materialDataItem.getImag(), beta);
}

TEST_F(TestMaterialModel, test_cloneMaterial)
{
    std::unique_ptr<MaterialModel> model(new MaterialModel);

    EXPECT_EQ(model->rowCount(QModelIndex()), 0);

    const double delta(0.2), beta(0.1);
    const QString name("MaterialName");
    MaterialItem* item = model->addMaterial(name, delta, beta);
    const QString origIdentifier = item->getIdentifier();

    MaterialItem* clonedMaterial = model->cloneMaterial(item->index());
    EXPECT_EQ(model->rowCount(QModelIndex()), 2);

    // clone should not change identifier of original material (as it once happened)
    EXPECT_EQ(item->getIdentifier(), origIdentifier);

    // cloned material should have different identifier
    EXPECT_TRUE(clonedMaterial->getIdentifier() != item->getIdentifier());

    // checking name of cloned material
    EXPECT_EQ(item->itemName() + " (clone)", clonedMaterial->itemName());

    auto& refIndex = clonedMaterial->groupItem<MaterialDataItem>(MaterialItem::P_MATERIAL_DATA);
    EXPECT_EQ(refIndex.getReal(), delta);
    EXPECT_EQ(refIndex.getImag(), beta);
}

//! Checks the method which returns MaterialItem from known identifier.

TEST_F(TestMaterialModel, test_materialItemFromIdentifier)
{
    MaterialModel model;
    MaterialItem* mat1 = model.addMaterial("aaa", 1.0, 2.0);
    MaterialItem* mat2 = model.addMaterial("bbb", 3.0, 4.0);
    EXPECT_TRUE(mat1 == model.materialFromIdentifier(mat1->getIdentifier()));
    EXPECT_TRUE(mat2 == model.materialFromIdentifier(mat2->getIdentifier()));
    EXPECT_TRUE(nullptr == model.materialFromIdentifier("non-existing-identifier"));
}

//! Checks the method which returns MaterialItem from material name.

TEST_F(TestMaterialModel, test_materialItemFromName)
{
    MaterialModel model;
    MaterialItem* mat1 = model.addMaterial("aaa", 1.0, 2.0);
    MaterialItem* mat2 = model.addMaterial("bbb", 3.0, 4.0);
    EXPECT_TRUE(mat1 == model.materialFromName(mat1->itemName()));
    EXPECT_TRUE(mat2 == model.materialFromName(mat2->itemName()));
    EXPECT_TRUE(nullptr == model.materialFromName("non-existing-name"));
}

//! Checks the method which construct MaterialProperty from MaterialItem.

TEST_F(TestMaterialModel, test_materialPropertyFromMaterial)
{
    MaterialModel model;
    MaterialItem* mat = model.addMaterial("Something", 1.0, 2.0);

    ExternalProperty property = MaterialItemUtils::materialProperty(*mat);
    EXPECT_EQ(property.text(), QString("Something"));
    EXPECT_EQ(property.color(), mat->getColor());
    EXPECT_EQ(property.identifier(), mat->getIdentifier());
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
    auto mat1 = model.addMaterial("Something1", 1.0, 2.0);
    model.addMaterial("Something2", 3.0, 4.0);
    ExternalProperty property2 = MaterialItemUtils::defaultMaterialProperty();
    EXPECT_EQ(property2.text(), QString("Something1"));
    EXPECT_EQ(property2.color(), mat1->getColor());
    EXPECT_EQ(property2.identifier(), mat1->getIdentifier());
}
