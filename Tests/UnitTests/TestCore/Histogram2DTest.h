#ifndef HISTOGRAM2DTEST_H
#define HISTOGRAM2DTEST_H

#include "Histogram2D.h"
#include <boost/assign/list_of.hpp>
#include "gtest/gtest.h"

class Histogram2DTest : public ::testing::Test
{
 protected:
    Histogram2DTest();
    virtual ~Histogram2DTest();

    Histogram2D *hist;
};


// y
// 4.0   -----------------------------------
//       |     |          |     |          |
//       |  2  |    5     |  8  |    11    |
// 2.0   -----------------------------------
//       |  1  |    4     |  7  |    10    |
// 1.0   -----------------------------------
//       |  0  |    3     |  6  |    9     |
// 0.0   -----------------------------------
//     -1.0  -0.5        0.5   1.0        2.0  X

Histogram2DTest::Histogram2DTest()
{
    std::vector<double> xbin_edges = boost::assign::list_of(-1.0)(-0.5)(0.5)(1.0)(2.0);
    std::vector<double> ybin_edges = boost::assign::list_of(0.0)(1.0)(2.0)(4.0);
    hist = new Histogram2D(4, xbin_edges, 3, ybin_edges);
}

Histogram2DTest::~Histogram2DTest()
{
    delete hist;
}

TEST_F(Histogram2DTest, VariableHist)
{
    hist->reset();

    // basic axes check
    EXPECT_EQ(12, hist->getTotalNumberOfBins());
    EXPECT_EQ(hist->getRank(), 2);
    EXPECT_EQ(hist->getXaxis()->getName(), std::string("x-axis"));
    EXPECT_EQ(hist->getXaxis()->getSize(), 4);
    EXPECT_EQ(hist->getXmin(), -1.0);
    EXPECT_EQ(hist->getXmax(), 2.0);
    EXPECT_EQ(hist->getYaxis()->getName(), std::string("y-axis"));
    EXPECT_EQ(hist->getYaxis()->getSize(), 3);
    EXPECT_EQ(hist->getYmin(), 0.0);
    EXPECT_EQ(hist->getYmax(), 4.0);

    // globalbin -> axes indices
    EXPECT_EQ(hist->getXaxisIndex(0), 0);
    EXPECT_EQ(hist->getXaxisIndex(1), 0);
    EXPECT_EQ(hist->getXaxisIndex(2), 0);
    EXPECT_EQ(hist->getXaxisIndex(3), 1);
    EXPECT_EQ(hist->getXaxisIndex(4), 1);
    EXPECT_EQ(hist->getXaxisIndex(5), 1);
    EXPECT_EQ(hist->getXaxisIndex(9), 3);
    EXPECT_EQ(hist->getXaxisIndex(10), 3);
    EXPECT_EQ(hist->getXaxisIndex(11), 3);

    EXPECT_EQ(hist->getYaxisIndex(0), 0);
    EXPECT_EQ(hist->getYaxisIndex(1), 1);
    EXPECT_EQ(hist->getYaxisIndex(2), 2);
    EXPECT_EQ(hist->getYaxisIndex(3), 0);
    EXPECT_EQ(hist->getYaxisIndex(4), 1);
    EXPECT_EQ(hist->getYaxisIndex(5), 2);
    EXPECT_EQ(hist->getYaxisIndex(9), 0);
    EXPECT_EQ(hist->getYaxisIndex(10), 1);
    EXPECT_EQ(hist->getYaxisIndex(11), 2);

    // axes indices -> global bin
    EXPECT_EQ(hist->getGlobalBin(0,0), 0);
    EXPECT_EQ(hist->getGlobalBin(0,2), 2);
    EXPECT_EQ(hist->getGlobalBin(1,1), 4);
    EXPECT_EQ(hist->getGlobalBin(3,2), 11);

    // bin centers
    EXPECT_EQ(hist->getXaxisValue(0), -0.75);
    EXPECT_EQ(hist->getXaxisValue(2), -0.75);
    EXPECT_EQ(hist->getXaxisValue(4), 0.0);
    EXPECT_EQ(hist->getXaxisValue(10), 1.5);
    EXPECT_EQ(hist->getXaxisValue(11), 1.5);

    EXPECT_EQ(hist->getYaxisValue(0), 0.5);
    EXPECT_EQ(hist->getYaxisValue(2), 3.0);
    EXPECT_EQ(hist->getYaxisValue(4), 1.5);
    EXPECT_EQ(hist->getYaxisValue(10), 1.5);
    EXPECT_EQ(hist->getYaxisValue(11), 3.0);

}

// y
// 4.0   -----------------------------------
//       |     |          |     |          |
//       |  2  |    5     |  8  |    11    |
// 2.0   -----------------------------------
//       |  1  |    4     |  7  |    10    |
// 1.0   -----------------------------------
//       |  0  |    3     |  6  |    9     |
// 0.0   -----------------------------------
//     -1.0  -0.5        0.5   1.0        2.0  X

TEST_F(Histogram2DTest, VariableHistFill)
{
    hist->reset();

    // values to fill all histogram
    std::vector<double> xvalues = boost::assign::list_of(-0.75)(-0.75)(-0.75)(0.0)(0.0)(0.0)(0.75)(0.75)(0.75)(1.5)(1.5)(1.5);
    std::vector<double> yvalues = boost::assign::list_of(0.5)(1.5)(3.0)(0.5)(1.5)(3.0)(0.5)(1.5)(3.0)(0.5)(1.5)(3.0);

    for(size_t i=0; i<xvalues.size(); ++i) {
        hist->fill(xvalues[i], yvalues[i], i*10.0);
    }

    for(size_t globalbin=0; globalbin<hist->getTotalNumberOfBins(); ++globalbin) {
        EXPECT_EQ(globalbin*10.0, hist->getBinContent(globalbin));
        EXPECT_EQ(1.0, hist->getBinNumberOfEntries(globalbin));

    }

    for(size_t binx=0; binx<hist->getXaxis()->getSize(); ++binx){
        for(size_t biny=0; biny<hist->getYaxis()->getSize(); ++biny){
            int globalbin = hist->getGlobalBin(binx, biny);
            EXPECT_EQ(globalbin*10.0, hist->getBinContent(binx, biny));
            EXPECT_EQ(1.0, hist->getBinNumberOfEntries(binx, biny));
        }
    }

}


#endif
