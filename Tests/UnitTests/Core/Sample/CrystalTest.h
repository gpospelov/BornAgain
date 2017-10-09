#include "Crystal.h"
#include "Lattice.h"
#include "BornAgainNamespace.h"

class CrystalTest : public ::testing::Test
{
protected:
    CrystalTest(){}
};

TEST_F(CrystalTest, getChildren)
{
    Lattice lattice = Lattice::createTrigonalLattice(1.0, 2.0);
    ParticleComposition composition;
    Crystal crystal(composition, lattice);

    std::vector<const INode*> children = crystal.getChildren();
    ASSERT_EQ(children.size(), 2u);
    EXPECT_EQ(children.at(0)->getName(), BornAgain::ParticleCompositionType);
    EXPECT_EQ(children.at(1)->getName(), BornAgain::LatticeType);
}
