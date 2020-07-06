#include "Core/Particle/Crystal.h"
#include "Core/Basics/BornAgainNamespace.h"
#include "Core/Lattice/Lattice.h"
#include "Core/Particle/ParticleComposition.h"
#include "Tests/UnitTests/utilities/google_test.h"

class CrystalTest : public ::testing::Test
{
};

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
