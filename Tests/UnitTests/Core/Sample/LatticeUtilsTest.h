#include "google_test.h"
#include "LatticeUtils.h"
#include "ILatticeOrientation.h"

class LatticeUtilsTest : public ::testing::Test
{
protected:
    ~LatticeUtilsTest();
};

LatticeUtilsTest::~LatticeUtilsTest() = default;

// tests the creation of an FCC lattice with the primitive cube aligned along the q-axes
TEST_F(LatticeUtilsTest, cubeAlignedFCCTest)
{
    MillerIndexOrientation cube_aligned(MillerIndexOrientation::QZ, { 0, 0, 1},
                                        MillerIndexOrientation::QY, { 0, 1, 0});
    auto lattice = LatticeUtils::CreateFCCLattice(2.0, cube_aligned);
    auto a1 = lattice.getBasisVectorA();
    auto a2 = lattice.getBasisVectorB();
    auto a3 = lattice.getBasisVectorC();

    kvector_t v1 { 0.0, 1.0, 1.0 };
    kvector_t v2 { 1.0, 0.0, 1.0 };
    kvector_t v3 { 1.0, 1.0, 0.0 };

    EXPECT_EQ(a1, v1);
    EXPECT_EQ(a2, v2);
    EXPECT_EQ(a3, v3);
}

// tests the creation of an FCC lattice with the primitive cube aligned along the q-axes
TEST_F(LatticeUtilsTest, diagonalAlignedFCCTest)
{
    MillerIndexOrientation cube_aligned(MillerIndexOrientation::QZ, { 1, 1, 1},
                                        MillerIndexOrientation::QX, { 1, 1, 0});
    auto lattice = LatticeUtils::CreateFCCLattice(2.0, cube_aligned);
    auto a1 = lattice.getBasisVectorA();
    auto a2 = lattice.getBasisVectorB();
    auto a3 = lattice.getBasisVectorC();

    EXPECT_EQ(a1.z(), a2.z());
    EXPECT_EQ(a2.z(), a3.z());
    EXPECT_EQ(a1.x(), a2.x());
    EXPECT_EQ(a1.y(), -a2.y());
}

// tests the creation of an HCP lattice
TEST_F(LatticeUtilsTest, trivialAlignedHCPTest)
{
    MillerIndexOrientation trivial_aligned(MillerIndexOrientation::QZ, { 0, 0, 1},
                                        MillerIndexOrientation::QX, { 2, -1, 0});
    auto lattice = LatticeUtils::CreateHCPLattice(2.0, 4.0, trivial_aligned);
    auto a1 = lattice.getBasisVectorA();
    auto a2 = lattice.getBasisVectorB();
    auto a3 = lattice.getBasisVectorC();

    kvector_t v1 { 2.0, 0.0, 0.0 };
    kvector_t v2 { -1.0, std::sqrt(3.0), 0.0 };
    kvector_t v3 { 1.0, 1.0/std::sqrt(3.0), 2.0 };

    EXPECT_EQ(a1, v1);
    EXPECT_EQ(a2, v2);
    EXPECT_EQ(a3, v3);
}
