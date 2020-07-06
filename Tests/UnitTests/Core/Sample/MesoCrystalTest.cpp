#include "Core/Particle/MesoCrystal.h"
#include "Core/Basics/BornAgainNamespace.h"
#include "Core/Particle/Crystal.h"
#include "Core/HardParticle/FormFactorFullSphere.h"
#include "Core/Lattice/Lattice.h"
#include "Core/Particle/ParticleComposition.h"
#include "Tests/UnitTests/utilities/google_test.h"

class MesoCrystalTest : public ::testing::Test
{
};

TEST_F(MesoCrystalTest, getChildren)
{
    Lattice lattice = Lattice::createHexagonalLattice(1.0, 2.0);
    ParticleComposition composition;
    Crystal crystal(composition, lattice);
    MesoCrystal meso(crystal, FormFactorFullSphere(1.0));

    std::vector<const INode*> children = meso.getChildren();
    EXPECT_EQ(children.size(), 2u);
    EXPECT_EQ(children.at(0)->getName(), BornAgain::CrystalType);
    EXPECT_EQ(children.at(1)->getName(), BornAgain::FFFullSphereType);

    // children when rotation is set
    meso.setRotation(RotationY(45.));
    children = meso.getChildren();
    EXPECT_EQ(children.size(), 3u);
    EXPECT_EQ(children.at(0)->getName(), BornAgain::YRotationType);
    EXPECT_EQ(children.at(1)->getName(), BornAgain::CrystalType);
    EXPECT_EQ(children.at(2)->getName(), BornAgain::FFFullSphereType);
}
