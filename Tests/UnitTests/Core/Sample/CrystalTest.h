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
    EXPECT_EQ(children.size(), 1u);
    EXPECT_EQ(children.at(0)->getName(), BornAgain::ParticleCompositionType);
}
