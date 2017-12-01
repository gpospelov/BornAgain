#ifndef LATTICETEST_H
#define LATTICETEST_H

#include "Lattice.h"
#include "google_test.h"
#include "MathConstants.h"

class LatticeTest : public ::testing::Test
{
 protected:
    LatticeTest(){}
    virtual ~LatticeTest(){}
};

// tests the declaration of Lattice object, copy constructor and the getBasisVector_() functions
TEST_F(LatticeTest, declarationTest)
{
    kvector_t a1(1,0,0), a2(0,1,0), a3(0,0,1);

    Lattice l1(a1, a2, a3);
    EXPECT_EQ(a1, l1.getBasisVectorA());
    EXPECT_EQ(a2, l1.getBasisVectorB());
    EXPECT_EQ(a3, l1.getBasisVectorC());

    Lattice l2(l1);
    EXPECT_EQ(a1, l2.getBasisVectorA());
    EXPECT_EQ(a2, l2.getBasisVectorB());
    EXPECT_EQ(a3, l2.getBasisVectorC());

    // calls and tests copy constructor
    Lattice l3 = Lattice(l2);
    EXPECT_EQ(a1, l3.getBasisVectorA());
    EXPECT_EQ(a2, l3.getBasisVectorB());
    EXPECT_EQ(a3, l3.getBasisVectorC());
}

// tests volume of the unit cell
TEST_F(LatticeTest, volumeTest)
{
    kvector_t a1(4,0,0), a2(0,2.1,0), a3(0,0,1);

    Lattice l1(a1, a2, a3);
    EXPECT_EQ(8.4, l1.volume());
}


// tests whether reciprocal lattice vectors have been initialized or not
TEST_F(LatticeTest, reciprocalTest)
{
    kvector_t a1(1,0,0), a2(0,1,0), a3(0,0,1);
    Lattice l1(a1, a2, a3);

    kvector_t b1, b2, b3, m_ra, m_rb, m_rc;

    // computing expected reciprocal lattice vectors
    kvector_t a23 = a2.cross(a3);
    kvector_t a31 = a3.cross(a1);
    kvector_t a12 = a1.cross(a2);
    m_ra = M_TWOPI/a1.dot(a23)*a23;
    m_rb = M_TWOPI/a2.dot(a31)*a31;
    m_rc = M_TWOPI/a3.dot(a12)*a12;

    l1.initialize();
    l1.getReciprocalLatticeBasis(b1, b2, b3);
    EXPECT_EQ(m_ra, b1);
    EXPECT_EQ(m_rb, b2);
    EXPECT_EQ(m_rc, b3);
}


// REAL lattice = physical lattice
// tests the nearest REAL LATTICE coordinates to a vector given in REAL SPACE
TEST_F(LatticeTest, nearestrealLatticecoordsTest)
{
    kvector_t a1(1,0,0), a2(0,1,0), a3(0,0,1);
    Lattice l1(a1, a2, a3);

    // vector_in is in real SPACE coordinates
    kvector_t vector_in(3.01,1.51,1.49);

    // vector_in is in real LATTICE coordinates
    ivector_t vector_expected(3,2,1);

    EXPECT_EQ(vector_expected, l1.getNearestLatticeVectorCoordinates(vector_in));
}

// REC. LATTICE = reciprocal lattice
// tests the nearest REC. LATTICE coordinates to a vector given in REC. SPACE
TEST_F(LatticeTest, nearestrecLatticecoordsTest)
{
    kvector_t a1(1,0,0), a2(0,1,0), a3(0,0,1);
    Lattice l1(a1, a2, a3);

    // vector_in is in reciprocal SPACE coordinates
    kvector_t vector_in(5.9,5.9,0);

    // vector_expected is in reciprocal LATTICE coordinates
    ivector_t vector_expected(1,1,0);

    EXPECT_EQ(vector_expected, l1.getNearestReciprocalLatticeVectorCoordinates(vector_in));
}


#endif // LATTICETEST_H
