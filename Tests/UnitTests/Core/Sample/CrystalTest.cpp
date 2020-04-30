#include "Crystal.h"
#include "BornAgainNamespace.h"
#include "Lattice.h"
#include "ParticleComposition.h"
#include "google_test.h"

class CrystalTest : public ::testing::Test
{
protected:
    ~CrystalTest();
};

CrystalTest::~CrystalTest() = default;

TEST_F(CrystalTest, getChildren)
{
    Lattice lattice = Lattice::createHexagonalLattice(1.0, 2.0);
    ParticleComposition composition;
    Crystal crystal(composition, lattice);

    std::vector<const INode*> children = crystal.getChildren();
    ASSERT_EQ(children.size(), 2u);
    EXPECT_EQ(children.at(0)->getName(), BornAgain::ParticleCompositionType);
    EXPECT_EQ(children.at(1)->getName(), BornAgain::LatticeType);
}
