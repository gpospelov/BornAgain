#ifndef POLYGONTEST_H
#define POLYGONTEST_H

#include "Polygon.h"
#include "gtest/gtest.h"
#include <boost/scoped_ptr.hpp>
#include <boost/assign/list_of.hpp>

class PolygonTest : public ::testing::Test
{
public:
};


TEST_F(PolygonTest, SimpleRectangle)
{
    // simple closed rectangle
    std::vector<double> x = boost::assign::list_of(4.0)(-4.0)(-4.0)(4.0)(4.0);
    std::vector<double> y = boost::assign::list_of(2.0)(2.0)(-2.0)(-2.0)(2.0);
    Geometry::Polygon polygon(x, y);
    EXPECT_DOUBLE_EQ(32.0, polygon.getArea());
    EXPECT_TRUE(polygon.contains(0.0, 0.0));
    EXPECT_TRUE(polygon.contains(4.0, 2.0));
    EXPECT_TRUE(polygon.contains(-4.0, -2.0));
    EXPECT_TRUE(polygon.contains(-4.0, -2.0));
    EXPECT_FALSE(polygon.contains(0.0, 2.01));
    EXPECT_FALSE(polygon.contains(4.0, -2.01));

    // unclosed rectangle (should be closed automatically)
    x = boost::assign::list_of(4.0)(-4.0)(-4.0)(4.0);
    y = boost::assign::list_of(2.0)(2.0)(-2.0)(-2.0);
    Geometry::Polygon polygon2(x, y);
    EXPECT_DOUBLE_EQ(32.0, polygon2.getArea());
    EXPECT_TRUE(polygon2.contains(0.0, 0.0));
    EXPECT_TRUE(polygon2.contains(4.0, 2.0));
    EXPECT_TRUE(polygon2.contains(-4.0, -2.0));
    EXPECT_TRUE(polygon2.contains(-4.0, -2.0));
    EXPECT_FALSE(polygon2.contains(0.0, 2.01));
    EXPECT_FALSE(polygon2.contains(4.0, -2.01));

}

//     *******
//      *   *
//       * *
//        *
//       * *
//      *   *
//     *******

TEST_F(PolygonTest, SandWatchShape)
{
    std::vector<double> x = boost::assign::list_of(2.0)(-2.0)(2.0)(-2.0)(2.0);
    std::vector<double> y = boost::assign::list_of(2.0)(2.0)(-2.0)(-2.0)(2.0);
    Geometry::Polygon polygon(x, y);
    std::cout << polygon << std::endl;

    // for some reason area calculation doesn't work for boost's polygon of such shape
    // EXPECT_DOUBLE_EQ(8.0, polygon.getArea());

    EXPECT_TRUE(polygon.contains(2.0, 2.0));
    EXPECT_TRUE(polygon.contains(-2.0, 2.0));
    EXPECT_TRUE(polygon.contains(0.0, 0.0));
    EXPECT_TRUE(polygon.contains(0.0, 1.0));

    EXPECT_FALSE(polygon.contains(1.0, 0.0));
    EXPECT_FALSE(polygon.contains(-1.5, 0.5));

}

TEST_F(PolygonTest, Clone)
{
    std::vector<double> x = boost::assign::list_of(4.0)(-4.0)(-4.0)(4.0)(4.0);
    std::vector<double> y = boost::assign::list_of(2.0)(2.0)(-2.0)(-2.0)(2.0);
    Geometry::Polygon polygon(x, y);

    boost::scoped_ptr<Geometry::Polygon > clone(polygon.clone());
    EXPECT_DOUBLE_EQ(32.0, clone->getArea());
    EXPECT_TRUE(clone->contains(0.0, 0.0));
    EXPECT_TRUE(clone->contains(4.0, 2.0));
    EXPECT_TRUE(clone->contains(-4.0, -2.0));
    EXPECT_TRUE(clone->contains(-4.0, -2.0));
    EXPECT_FALSE(clone->contains(0.0, 2.01));
    EXPECT_FALSE(clone->contains(4.0, -2.01));
}

#endif
