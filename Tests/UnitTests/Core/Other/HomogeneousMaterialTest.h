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
    const HomogeneousMaterial * tMaterial = material.createTransformedMaterial(
                                                transform.getTransform3D());

    EXPECT_EQ("MagMaterial", tMaterial->getName());
    EXPECT_EQ(refIndex, tMaterial->refractiveIndex());

    delete tMaterial;
}

TEST_F(HomogeneousMaterialTest, HomogeneousMaterialClone)
{
    complex_t refIndex = complex_t(1.0, 2.0);
    kvector_t magnetism = kvector_t(3.0, 4.0, 5.0);
    HomogeneousMaterial material("MagMaterial", refIndex, magnetism);

    HomogeneousMaterial * clone = material.clone();

    EXPECT_EQ("MagMaterial", clone->getName());
    EXPECT_EQ(refIndex, clone->refractiveIndex());
    EXPECT_EQ(magnetism, clone->magneticField());

    complex_t refIndex2 = complex_t(2.0, 3.0);
    clone->setRefractiveIndex(refIndex2);
    EXPECT_EQ(refIndex2, clone->refractiveIndex());

    kvector_t magnetism2 = kvector_t(5.0, 6.0, 7.0);
    clone->setMagneticField(magnetism2);
    EXPECT_EQ(magnetism2, clone->magneticField());

    RotationZ transform(45.*Units::degree);
    const HomogeneousMaterial * tMaterial = clone->createTransformedMaterial(
                                                transform.getTransform3D());

    EXPECT_EQ("MagMaterial", tMaterial->getName());
    EXPECT_EQ(refIndex2, tMaterial->refractiveIndex());

    delete tMaterial;
    delete clone;
}
