#include "HomogeneousMaterial.h"
#include "Rotations.h"
#include "Units.h"

class HomogeneousMaterialTest : public ::testing::Test
{
public:
    HomogeneousMaterialTest() {}
    virtual ~HomogeneousMaterialTest() {}
};

TEST_F(HomogeneousMaterialTest, HomogeneousMaterialWithRefIndex)
{
    complex_t refIndex = complex_t(1.0, 2.0);
    kvector_t magnetism = kvector_t(3.0, 4.0, 5.0);
    HomogeneousMaterial material("MagMaterial", refIndex, magnetism);
    EXPECT_EQ("MagMaterial", material.getName());
    EXPECT_EQ(refIndex, material.refractiveIndex());
    EXPECT_EQ(magnetism, material.magneticField());

    complex_t refIndex2 = complex_t(2.0, 3.0);
    material.setRefractiveIndex(refIndex2);
    EXPECT_EQ(refIndex2, material.refractiveIndex());

    kvector_t magnetism2 = kvector_t(5.0, 6.0, 7.0);
    material.setMagneticField(magnetism2);
    EXPECT_EQ(magnetism2, material.magneticField());
}

TEST_F(HomogeneousMaterialTest, HomogeneousMaterialWithRefIndexAndMagField)
{
    kvector_t magnetism = kvector_t(3.0, 4.0, 5.0);
    HomogeneousMaterial material("MagMaterial", 2.0, 2.0, magnetism);
    EXPECT_EQ("MagMaterial", material.getName());
    EXPECT_EQ(complex_t(-1.0, 2.0), material.refractiveIndex());
    EXPECT_EQ(magnetism, material.magneticField());

    complex_t refIndex2 = complex_t(2.0, 3.0);
    material.setRefractiveIndex(refIndex2);
    EXPECT_EQ(refIndex2, material.refractiveIndex());

    kvector_t magnetism2 = kvector_t(5.0, 6.0, 7.0);
    material.setMagneticField(magnetism2);
    EXPECT_EQ(magnetism2, material.magneticField());
}

TEST_F(HomogeneousMaterialTest, HomogeneousMaterialTransform)
{
    complex_t refIndex = complex_t(0.0, 0.0);
    kvector_t magnetism = kvector_t(0.0, 0.0, 0.0);
    HomogeneousMaterial material("MagMaterial", refIndex, magnetism);

    RotationZ transform(45.*Units::degree);
    HomogeneousMaterial material2 = material.transformedMaterial(transform.getTransform3D());

    EXPECT_EQ("MagMaterial", material2.getName());
    EXPECT_EQ(refIndex, material2.refractiveIndex());
}

TEST_F(HomogeneousMaterialTest, HomogeneousMaterialCopy)
{
    complex_t refIndex = complex_t(1.0, 2.0);
    kvector_t magnetism = kvector_t(3.0, 4.0, 5.0);
    HomogeneousMaterial material("MagMaterial", refIndex, magnetism);

    HomogeneousMaterial copy = material;

    EXPECT_EQ("MagMaterial", copy.getName());
    EXPECT_EQ(refIndex, copy.refractiveIndex());
    EXPECT_EQ(magnetism, copy.magneticField());

    complex_t refIndex2 = complex_t(2.0, 3.0);
    copy.setRefractiveIndex(refIndex2);
    EXPECT_EQ(refIndex2, copy.refractiveIndex());

    kvector_t magnetism2 = kvector_t(5.0, 6.0, 7.0);
    copy.setMagneticField(magnetism2);
    EXPECT_EQ(magnetism2, copy.magneticField());

    RotationZ transform(45.*Units::degree);
    HomogeneousMaterial material2 = copy.transformedMaterial(transform.getTransform3D());

    EXPECT_EQ("MagMaterial", material2.getName());
    EXPECT_EQ(refIndex2, material2.refractiveIndex());
}
