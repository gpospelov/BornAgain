#include "Lattice2DParameters.h"
#include "BornAgainNamespace.h"

#include <iostream>

class LatticeTest : public ::testing::Test
{
protected:
    LatticeTest(){}
};


TEST_F(LatticeTest, basicLattice)
{
    const double length1(1.0), length2(2.0), angle(3.0);
    BasicLattice lattice(length1, length2, angle);
    EXPECT_EQ(lattice.length1(), length1);
    EXPECT_EQ(lattice.length2(), length2);
    EXPECT_EQ(lattice.latticeAngle(), angle);
    EXPECT_EQ(lattice.rotationAngle(), 0.0);

    const double new_value(42.0);

    lattice.setParameterValue(BornAgain::LatticeLength1, new_value);
    EXPECT_EQ(lattice.length1(), new_value);
    lattice.setParameterValue(BornAgain::LatticeLength2, new_value);
    EXPECT_EQ(lattice.length2(), new_value);
    lattice.setParameterValue(BornAgain::LatticeAngle, new_value);
    EXPECT_EQ(lattice.latticeAngle(), new_value);
    lattice.setParameterValue(BornAgain::Xi, new_value);
    EXPECT_EQ(lattice.rotationAngle(), new_value);
}

TEST_F(LatticeTest, basicLatticeClone)
{
    const double length1(1.0), length2(2.0), angle(3.0), xi(4.0);
    BasicLattice lattice(length1, length2, angle, xi);

    std::unique_ptr<Lattice2D> clone(lattice.clone());
    EXPECT_EQ(clone->length1(), length1);
    EXPECT_EQ(clone->length2(), length2);
    EXPECT_EQ(clone->latticeAngle(), angle);
    EXPECT_EQ(clone->rotationAngle(), xi);
    EXPECT_EQ(clone->getName(), BornAgain::BasicLatticeType);
}

TEST_F(LatticeTest, squareLatticeClone)
{
    const double length(1.0), xi(4.0);
    SquareLattice lattice(length, xi);

    std::unique_ptr<Lattice2D> clone(lattice.clone());
    EXPECT_EQ(clone->length1(), length);
    EXPECT_EQ(clone->length2(), length);
    EXPECT_DOUBLE_EQ(clone->latticeAngle(), M_PI/2.0);
    EXPECT_EQ(clone->rotationAngle(), xi);
    EXPECT_EQ(clone->getName(), BornAgain::SquareLatticeType);

    // registered parameters of clone
    const double new_value(42.0);
    clone->setParameterValue(BornAgain::LatticeLength, new_value);
    EXPECT_EQ(clone->length1(), new_value);
    EXPECT_EQ(clone->length2(), new_value);
    clone->setParameterValue(BornAgain::Xi, new_value);
    EXPECT_EQ(clone->rotationAngle(), new_value);
}

TEST_F(LatticeTest, hexagonalLatticeClone)
{
    const double length(1.0), xi(4.0);
    HexagonalLattice lattice(length, xi);

    std::unique_ptr<Lattice2D> clone(lattice.clone());
    EXPECT_EQ(clone->length1(), length);
    EXPECT_EQ(clone->length2(), length);
    EXPECT_DOUBLE_EQ(clone->latticeAngle(), 2.*M_PI/3.0);
    EXPECT_EQ(clone->rotationAngle(), xi);
    EXPECT_EQ(clone->getName(), BornAgain::HexagonalLatticeType);

    // registered parameters of clone
    const double new_value(42.0);
    clone->setParameterValue(BornAgain::LatticeLength, new_value);
    EXPECT_EQ(clone->length1(), new_value);
    EXPECT_EQ(clone->length2(), new_value);
    clone->setParameterValue(BornAgain::Xi, new_value);
    EXPECT_EQ(clone->rotationAngle(), new_value);
}

TEST_F(LatticeTest, onChange)
{
    class Parent : public INode{
    public:
        Parent() : m_changed(false) {}
        void accept(INodeVisitor* visitor) const final { visitor->visit(this); }
        virtual void onChange() { m_changed = true; }
        bool m_changed;
    };

    Parent parent;
    const double length1(1.0), length2(2.0), angle(3.0), xi(4.0);
    BasicLattice lattice(length1, length2, angle, xi);

    parent.registerChild(&lattice);
    EXPECT_FALSE(parent.m_changed);
    lattice.setParameterValue(BornAgain::LatticeLength1, 42.0);
    EXPECT_TRUE(parent.m_changed);
}
