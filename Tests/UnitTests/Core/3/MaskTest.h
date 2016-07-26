#ifndef MASKTEST_H
#define MASKTEST_H

#include "Mask.h"
#include "MaskCoordinateFunction.h"
#include "OutputData.h"

class MaskTest : public ::testing::Test
{
protected:
    MaskTest();
    virtual ~MaskTest();

    Mask* p_default_mask;
    MaskIndexModulus* p_modulo_mask;
    MaskCoordinates* p_rectangular_mask;
    MaskCoordinates* p_ellipse_mask;
};

MaskTest::MaskTest()
{
    p_default_mask = new Mask();
    p_default_mask->setMaxIndex(10);

    p_modulo_mask = new MaskIndexModulus(3, 1);
    p_modulo_mask->setMaxIndex(10);

    int dims[] = { 5, 5 };
    p_rectangular_mask = new MaskCoordinates(2, dims);
    int minima[] = { 1, 1 };
    int maxima[] = { 2, 2 };
    MaskCoordinateRectangleFunction* p_rectangle =
        new MaskCoordinateRectangleFunction(2, minima, maxima);
    p_rectangular_mask->setMaskCoordinateFunction(p_rectangle);

    p_ellipse_mask = new MaskCoordinates(2, dims);
    int center[] = { 2, 2 };
    int radii[] = { 1, 1 };
    MaskCoordinateEllipseFunction* p_ellipse = new MaskCoordinateEllipseFunction(2, center, radii);
    p_ellipse_mask->setMaskCoordinateFunction(p_ellipse);
}

MaskTest::~MaskTest()
{
    delete p_default_mask;
    delete p_modulo_mask;
    delete p_rectangular_mask;
    delete p_ellipse_mask;
}

TEST_F(MaskTest, DefaultFirstIndex)
{
    EXPECT_EQ((size_t)0, p_default_mask->getFirstValidIndex(0));
}

TEST_F(MaskTest, DefaultNextUninitialized)
{
    EXPECT_EQ((size_t)1, p_default_mask->getNextIndex(0));
    EXPECT_EQ((size_t)10, p_default_mask->getMaxIndex());
    EXPECT_EQ((size_t)1, p_default_mask->getOwnIndex());
    EXPECT_EQ((size_t)2, p_default_mask->getNextIndex(1));
    EXPECT_EQ((size_t)10, p_default_mask->getMaxIndex());
    EXPECT_EQ((size_t)2, p_default_mask->getOwnIndex());
}

TEST_F(MaskTest, DefaultNextEnd)
{
    EXPECT_EQ((size_t)9, p_default_mask->getNextIndex(8));
    EXPECT_EQ((size_t)10, p_default_mask->getMaxIndex());
    EXPECT_EQ((size_t)1, p_default_mask->getOwnIndex());
    EXPECT_EQ((size_t)10, p_default_mask->getNextIndex(9));
    EXPECT_EQ((size_t)10, p_default_mask->getMaxIndex());
    EXPECT_EQ((size_t)2, p_default_mask->getOwnIndex());
    EXPECT_EQ((size_t)10, p_default_mask->getNextIndex(12));
    EXPECT_EQ((size_t)10, p_default_mask->getMaxIndex());
    EXPECT_EQ((size_t)2, p_default_mask->getOwnIndex());
}

TEST_F(MaskTest, DefaultClone)
{
    Mask* p_mask  = new Mask();
    p_mask->setMaxIndex(10);
    EXPECT_EQ((size_t)0, p_mask->getFirstValidIndex(0));
    EXPECT_EQ((size_t)1, p_mask->getNextIndex(0));
    Mask* p_clone = p_mask->clone();
    EXPECT_EQ((size_t)2, p_clone->getNextIndex(1));
    EXPECT_EQ((size_t)2, p_clone->getOwnIndex());
    delete p_mask;
    EXPECT_EQ((size_t)3, p_clone->getNextIndex(2));
    EXPECT_EQ((size_t)3, p_clone->getOwnIndex());
    EXPECT_EQ((size_t)10, p_clone->getMaxIndex());
    delete p_clone;
}

TEST_F(MaskTest, ModuloFirstIndex)
{
    EXPECT_EQ((size_t)1, p_modulo_mask->getFirstValidIndex(0));
    EXPECT_EQ((size_t)10, p_modulo_mask->getMaxIndex());
}

TEST_F(MaskTest, ModuloNextUninitialized)
{
    EXPECT_EQ((size_t)1, p_modulo_mask->getNextIndex(0));
    EXPECT_EQ((size_t)10, p_modulo_mask->getMaxIndex());
    EXPECT_EQ((size_t)1, p_modulo_mask->getOwnIndex());
    EXPECT_EQ((size_t)4, p_modulo_mask->getNextIndex(1));
    EXPECT_EQ((size_t)10, p_modulo_mask->getMaxIndex());
    EXPECT_EQ((size_t)4, p_modulo_mask->getOwnIndex());
    EXPECT_EQ((size_t)7, p_modulo_mask->getNextIndex(4));
    EXPECT_EQ((size_t)10, p_modulo_mask->getMaxIndex());
    EXPECT_EQ((size_t)7, p_modulo_mask->getOwnIndex());
    EXPECT_EQ((size_t)10, p_modulo_mask->getNextIndex(7));
    EXPECT_EQ((size_t)10, p_modulo_mask->getMaxIndex());
    EXPECT_EQ((size_t)10, p_modulo_mask->getOwnIndex());
}

TEST_F(MaskTest, ModuloNextEnd)
{
    EXPECT_EQ((size_t)9, p_modulo_mask->getNextIndex(8));
    EXPECT_EQ((size_t)10, p_modulo_mask->getMaxIndex());
    EXPECT_EQ((size_t)1, p_modulo_mask->getOwnIndex());
    EXPECT_EQ((size_t)10, p_modulo_mask->getNextIndex(9));
    EXPECT_EQ((size_t)10, p_modulo_mask->getMaxIndex());
    EXPECT_EQ((size_t)2, p_modulo_mask->getOwnIndex());
    EXPECT_EQ((size_t)10, p_modulo_mask->getNextIndex(12));
    EXPECT_EQ((size_t)10, p_modulo_mask->getMaxIndex());
    EXPECT_EQ((size_t)2, p_modulo_mask->getOwnIndex());
}

TEST_F(MaskTest, ModuloClone)
{
    Mask* p_mask  = new MaskIndexModulus(3,1);
    p_mask->setMaxIndex(10);
    EXPECT_EQ((size_t)1, p_mask->getFirstValidIndex(0));
    EXPECT_EQ((size_t)4, p_mask->getNextIndex(1));
    Mask* p_clone = p_mask->clone();
    EXPECT_EQ((size_t)7, p_clone->getNextIndex(4));
    EXPECT_EQ((size_t)7, p_clone->getOwnIndex());
    delete p_mask;
    EXPECT_EQ((size_t)10, p_clone->getNextIndex(7));
    EXPECT_EQ((size_t)10, p_clone->getOwnIndex());
    EXPECT_EQ((size_t)10, p_clone->getMaxIndex());
    delete p_clone;
}

TEST_F(MaskTest, RectangularFirstIndex)
{
    EXPECT_EQ((size_t)0, p_rectangular_mask->getFirstValidIndex(0));
}

TEST_F(MaskTest, RectangularNextUninitialized)
{
    EXPECT_EQ((size_t)1, p_rectangular_mask->getNextIndex(0));
    EXPECT_EQ((size_t)25, p_rectangular_mask->getMaxIndex());
    EXPECT_EQ((size_t)1, p_rectangular_mask->getOwnIndex());
    EXPECT_EQ((size_t)2, p_rectangular_mask->getNextIndex(1));
    EXPECT_EQ((size_t)25, p_rectangular_mask->getMaxIndex());
    EXPECT_EQ((size_t)2, p_rectangular_mask->getOwnIndex());
}

TEST_F(MaskTest, RectangularMaskedElements)
{
    EXPECT_EQ((size_t)5, p_rectangular_mask->getNextIndex(4));
    EXPECT_EQ((size_t)25, p_rectangular_mask->getMaxIndex());
    EXPECT_EQ((size_t)1, p_rectangular_mask->getOwnIndex());
    EXPECT_EQ((size_t)8, p_rectangular_mask->getNextIndex(5));
    EXPECT_EQ((size_t)25, p_rectangular_mask->getMaxIndex());
    EXPECT_EQ((size_t)4, p_rectangular_mask->getOwnIndex());
    EXPECT_EQ((size_t)13, p_rectangular_mask->getNextIndex(12));
    EXPECT_EQ((size_t)25, p_rectangular_mask->getMaxIndex());
    EXPECT_EQ((size_t)5, p_rectangular_mask->getOwnIndex());
}

TEST_F(MaskTest, RectangularNextEnd)
{
    EXPECT_EQ((size_t)24, p_rectangular_mask->getNextIndex(23));
    EXPECT_EQ((size_t)25, p_rectangular_mask->getMaxIndex());
    EXPECT_EQ((size_t)1, p_rectangular_mask->getOwnIndex());
    EXPECT_EQ((size_t)25, p_rectangular_mask->getNextIndex(24));
    EXPECT_EQ((size_t)25, p_rectangular_mask->getMaxIndex());
    EXPECT_EQ((size_t)2, p_rectangular_mask->getOwnIndex());
    EXPECT_EQ((size_t)25, p_rectangular_mask->getNextIndex(25));
    EXPECT_EQ((size_t)25, p_rectangular_mask->getMaxIndex());
    EXPECT_EQ((size_t)2, p_rectangular_mask->getOwnIndex());
}

TEST_F(MaskTest, RectangularClone)
{
    Mask* p_mask  = p_rectangular_mask->clone();
    EXPECT_EQ((size_t)0, p_mask->getFirstValidIndex(0));
    EXPECT_EQ((size_t)1, p_mask->getNextIndex(0));
    Mask* p_clone = p_mask->clone();
    EXPECT_EQ((size_t)2, p_clone->getNextIndex(1));
    EXPECT_EQ((size_t)2, p_clone->getOwnIndex());
    delete p_mask;
    EXPECT_EQ((size_t)3, p_clone->getNextIndex(2));
    EXPECT_EQ((size_t)3, p_clone->getOwnIndex());
    EXPECT_EQ((size_t)25, p_clone->getMaxIndex());
    delete p_clone;
}

TEST_F(MaskTest, EllipseFirstIndex)
{
    EXPECT_EQ((size_t)0, p_ellipse_mask->getFirstValidIndex(0));
}

TEST_F(MaskTest, EllipseNextUninitialized)
{
    EXPECT_EQ((size_t)1, p_ellipse_mask->getNextIndex(0));
    EXPECT_EQ((size_t)25, p_ellipse_mask->getMaxIndex());
    EXPECT_EQ((size_t)1, p_ellipse_mask->getOwnIndex());
    EXPECT_EQ((size_t)2, p_ellipse_mask->getNextIndex(1));
    EXPECT_EQ((size_t)25, p_ellipse_mask->getMaxIndex());
    EXPECT_EQ((size_t)2, p_ellipse_mask->getOwnIndex());
}

TEST_F(MaskTest, EllipseMaskedElements)
{
    EXPECT_EQ((size_t)6, p_ellipse_mask->getNextIndex(5));
    EXPECT_EQ((size_t)25, p_ellipse_mask->getMaxIndex());
    EXPECT_EQ((size_t)1, p_ellipse_mask->getOwnIndex());
    EXPECT_EQ((size_t)8, p_ellipse_mask->getNextIndex(6));
    EXPECT_EQ((size_t)25, p_ellipse_mask->getMaxIndex());
    EXPECT_EQ((size_t)3, p_ellipse_mask->getOwnIndex());
    EXPECT_EQ((size_t)14, p_ellipse_mask->getNextIndex(12));
    EXPECT_EQ((size_t)25, p_ellipse_mask->getMaxIndex());
    EXPECT_EQ((size_t)5, p_ellipse_mask->getOwnIndex());
}

TEST_F(MaskTest, EllipseNextEnd)
{
    EXPECT_EQ((size_t)24, p_ellipse_mask->getNextIndex(23));
    EXPECT_EQ((size_t)25, p_ellipse_mask->getMaxIndex());
    EXPECT_EQ((size_t)1, p_ellipse_mask->getOwnIndex());
    EXPECT_EQ((size_t)25, p_ellipse_mask->getNextIndex(24));
    EXPECT_EQ((size_t)25, p_ellipse_mask->getMaxIndex());
    EXPECT_EQ((size_t)2, p_ellipse_mask->getOwnIndex());
    EXPECT_EQ((size_t)25, p_ellipse_mask->getNextIndex(25));
    EXPECT_EQ((size_t)25, p_ellipse_mask->getMaxIndex());
    EXPECT_EQ((size_t)2, p_ellipse_mask->getOwnIndex());
}

TEST_F(MaskTest, EllipseClone)
{
    Mask* p_mask  = p_ellipse_mask->clone();
    p_mask->setMaxIndex(10);
    EXPECT_EQ((size_t)0, p_mask->getFirstValidIndex(0));
    EXPECT_EQ((size_t)1, p_mask->getNextIndex(0));
    Mask* p_clone = p_mask->clone();
    EXPECT_EQ((size_t)2, p_clone->getNextIndex(1));
    EXPECT_EQ((size_t)2, p_clone->getOwnIndex());
    delete p_mask;
    EXPECT_EQ((size_t)3, p_clone->getNextIndex(2));
    EXPECT_EQ((size_t)3, p_clone->getOwnIndex());
    EXPECT_EQ((size_t)10, p_clone->getMaxIndex());
    delete p_clone;
}

TEST_F(MaskTest, CompoundMask)
{
    Mask* p_compound_mask = new MaskIndexModulus(3, 0, p_default_mask->clone());
    p_compound_mask->setMaxIndex(10);
    EXPECT_EQ((size_t)0, p_compound_mask->getFirstValidIndex(0));
    EXPECT_EQ((size_t)3, p_compound_mask->getNextIndex(0));
    EXPECT_EQ((size_t)6, p_compound_mask->getNextIndex(3));
    EXPECT_EQ((size_t)9, p_compound_mask->getNextIndex(6));
    EXPECT_EQ((size_t)10, p_compound_mask->getNextIndex(9));
    EXPECT_EQ((size_t)10, p_compound_mask->getOwnIndex());
    EXPECT_EQ((size_t)10, p_compound_mask->getMaxIndex());
    delete p_compound_mask;
}

TEST_F(MaskTest, CompoundMaskClone)
{
    Mask* p_compound_mask = new MaskIndexModulus(3, 1, p_default_mask->clone());
    p_compound_mask->setMaxIndex(20);
    EXPECT_EQ((size_t)1, p_compound_mask->getFirstValidIndex(0));
    EXPECT_EQ((size_t)4, p_compound_mask->getNextIndex(1));
    EXPECT_EQ((size_t)7, p_compound_mask->getNextIndex(4));
    EXPECT_EQ((size_t)7, p_compound_mask->getOwnIndex());
    EXPECT_EQ((size_t)20, p_compound_mask->getMaxIndex());
    Mask* p_compound_clone = p_compound_mask->clone();
    delete p_compound_mask;
    EXPECT_EQ((size_t)1, p_compound_clone->getFirstValidIndex(0));
    EXPECT_EQ((size_t)4, p_compound_clone->getNextIndex(1));
    EXPECT_EQ((size_t)7, p_compound_clone->getNextIndex(4));
    EXPECT_EQ((size_t)7, p_compound_clone->getOwnIndex());
    EXPECT_EQ((size_t)20, p_compound_clone->getMaxIndex());
    size_t index = p_compound_clone->getNextIndex(7);
    for (size_t i=0; i<3; ++i)
        index = p_compound_clone->getNextIndex(index);
    EXPECT_EQ((size_t)19, p_compound_clone->getOwnIndex());
    EXPECT_EQ((size_t)20, p_compound_clone->getMaxIndex());
    delete p_compound_clone;
}

#endif // MASKTEST_H
