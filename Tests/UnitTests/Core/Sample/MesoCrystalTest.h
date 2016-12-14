#include "Crystal.h"
#include "Lattice.h"
#include "MesoCrystal.h"
#include "FormFactorFullSphere.h"
#include "BornAgainNamespace.h"

class MesoCrystalTest : public ::testing::Test
{
protected:
    MesoCrystalTest(){}
};

TEST_F(MesoCrystalTest, getChildren)
{
    Lattice lattice = Lattice::createTrigonalLattice(1.0, 2.0);
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
