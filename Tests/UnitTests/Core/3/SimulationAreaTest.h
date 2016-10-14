#ifndef SIMULATIONAREATEST_H
#define SIMULATIONAREATEST_H

#include "SimulationArea.h"
#include "SphericalDetector.h"
#include "Rectangle.h"
#include <memory>
#include <iostream>

class SimulationAreaTest : public ::testing::Test
{
 protected:
    SimulationAreaTest(){}
    virtual ~SimulationAreaTest(){}
};

// Iterators test

TEST_F(SimulationAreaTest, iteratorOperations)
{
    SphericalDetector detector(4, -1.0, 3.0, 2, 0.0, 2.0);
    SimulationArea area(&detector);

    // begin iterator
    SimulationArea::iterator it_begin = area.begin();
    EXPECT_EQ(it_begin.index(), 0);
    EXPECT_EQ(it_begin.elementIndex(), 0);
    EXPECT_TRUE(it_begin == area.begin());
    EXPECT_FALSE(it_begin != area.begin());

    // end iterator
    SimulationArea::iterator it_end = area.end();
    EXPECT_EQ(it_end.index(), detector.getTotalSize());
    EXPECT_EQ(it_end.elementIndex(), 0); // has initial value

    // begin/end comparison
    EXPECT_TRUE(it_begin != it_end);
    EXPECT_FALSE(it_begin == it_end);

    // assignment
    SimulationArea::iterator it = area.begin();
    EXPECT_TRUE(it == it_begin);
    EXPECT_FALSE(it != it_begin);

    // increment
    it++;
    EXPECT_EQ(it.index(), 1);
    EXPECT_EQ(it.elementIndex(), 1);
    EXPECT_TRUE(it != it_begin);
    EXPECT_FALSE(it == it_begin);
    ++it;
    EXPECT_EQ(it.index(), 2);
    EXPECT_EQ(it.elementIndex(), 2);
}

//! Iteration over non-masked detector

TEST_F(SimulationAreaTest, detectorIteration)
{
    SphericalDetector detector(4, -1.0, 3.0, 2, 0.0, 2.0);
    SimulationArea area(&detector);

    std::vector<int> expectedIndexes = {0, 1, 2, 3, 4, 5, 6, 7};
    std::vector<int> expectedElementIndexes = {0, 1, 2, 3, 4, 5, 6, 7};

    std::vector<int> indexes;
    std::vector<int> elementIndexes;
    for(SimulationArea::iterator it = area.begin(); it!=area.end(); ++it) {
        indexes.push_back(it.index());
        elementIndexes.push_back(it.elementIndex());
    }
    EXPECT_EQ(indexes, expectedIndexes);
    EXPECT_EQ(elementIndexes, expectedElementIndexes);

    // testing C++-11
//    for(SimulationArea::iterator it : area) {
//        std::cout << "KKK" << std::endl;
//    }
}

//! Iteration over masked detector

TEST_F(SimulationAreaTest, maskedDetectorIteration)
{
    SphericalDetector detector(5, -1.0, 4.0, 4, 0.0, 4.0);
    detector.addMask(Geometry::Rectangle(0.1, 1.1, 2.9, 2.9), true);
    detector.addMask(Geometry::Rectangle(3.1, 3.1, 3.9, 3.9), true);
    SimulationArea area(&detector);

    std::vector<int> expectedIndexes = {0, 1, 2, 3, 4, 7, 8, 11, 12, 15, 16, 17, 18};
    std::vector<int> expectedElementIndexes = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    std::vector<int> indexes;
    std::vector<int> elementIndexes;
    for(SimulationArea::iterator it = area.begin(); it!=area.end(); ++it) {
        indexes.push_back(it.index());
        elementIndexes.push_back(it.elementIndex());
    }
    EXPECT_EQ(indexes, expectedIndexes);
    EXPECT_EQ(elementIndexes, expectedElementIndexes);


}

#endif
