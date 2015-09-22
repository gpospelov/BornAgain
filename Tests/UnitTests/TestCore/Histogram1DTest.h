#ifndef HISTOGRAM1DTEST_H
#define HISTOGRAM1DTEST_H

#include "Histogram1D.h"
#include "Exceptions.h"
#include <boost/assign/list_of.hpp>
#include "gtest/gtest.h"

class Histogram1DTest : public ::testing::Test
{
 protected:
    Histogram1DTest(){}
    virtual ~Histogram1DTest(){}
};

TEST_F(Histogram1DTest, FixedBinConstructor)
{
    Histogram1D hist(5, 0.0, 5.0);

    EXPECT_EQ(1, hist.getRank());
    EXPECT_EQ(5, hist.getTotalNumberOfBins());
    EXPECT_EQ(0.0, hist.getXmin());
    EXPECT_EQ(5.0, hist.getXmax());
    EXPECT_EQ(std::string("x-axis"), hist.getXaxis()->getName());
    EXPECT_THROW(hist.getYaxis(), LogicErrorException);
    for(size_t index=0; index<hist.getTotalNumberOfBins(); ++index) {
        EXPECT_EQ(index, hist.getGlobalBin(index));
        EXPECT_EQ(index, hist.getXaxisIndex(index));
    }
}

TEST_F(Histogram1DTest, FixedBinDefaultContent)
{
    Histogram1D hist(5, 0.0, 5.0);

    // bin centers
    std::vector<double> bin_centers = boost::assign::list_of(0.5)(1.5)(2.5)(3.5)(4.5);
    std::vector<double> centers = hist.getBinCenters();
    for(size_t index=0; index < bin_centers.size(); ++index) {
        EXPECT_EQ(centers[index], bin_centers[index]);
        EXPECT_EQ(hist.getXaxisValue(index), bin_centers[index]);
        EXPECT_EQ(hist.getXaxis()->getBinCenter(index), bin_centers[index]);
    }

    // default bin values
    std::vector<double> values = hist.getBinValues();
    for(size_t index=0; index < bin_centers.size(); ++index) {
        EXPECT_EQ(hist.getBinContent(index), 0.0);
        EXPECT_EQ(values[index], 0.0);
    }

    // default bin errors
    std::vector<double> errors = hist.getBinErrors();
    for(size_t index=0; index < bin_centers.size(); ++index) {
        EXPECT_EQ(hist.getBinError(index), 0.0);
        EXPECT_EQ(errors[index], 0.0);
    }

    // default bin entries
    for(size_t index=0; index < bin_centers.size(); ++index) {
        EXPECT_EQ(hist.getBinNumberOfEntries(index), 0);
    }

}

TEST_F(Histogram1DTest, FixedBinFill)
{
    Histogram1D hist(5, 0.0, 5.0);

    // filling two different bins

    hist.fill(0.5, 88.0);
    hist.fill(4.5, 99.0);
    EXPECT_EQ(hist.getBinContent(0), 88.0);
    EXPECT_EQ(hist.getBinNumberOfEntries(0), 1);
    EXPECT_EQ(hist.getBinError(0), 0.0);

    EXPECT_EQ(hist.getBinContent(4), 99.0);
    EXPECT_EQ(hist.getBinNumberOfEntries(4), 1);
    EXPECT_EQ(hist.getBinError(4), 0.0);

    std::vector<double> values = boost::assign::list_of(88.0)(0.0)(0.0)(0.0)(99.0);
    for(size_t index=0; index<hist.getTotalNumberOfBins(); ++index) {
        EXPECT_EQ(hist.getBinValues()[index], values[index]);
        EXPECT_EQ(hist.getBinErrors()[index], 0.0);
    }

    // resetting histograms
    hist.reset();
    EXPECT_EQ(hist.getBinContent(0), 0.0);
    EXPECT_EQ(hist.getBinNumberOfEntries(0), 0);
    EXPECT_EQ(hist.getBinError(0), 0.0);
    EXPECT_EQ(hist.getBinContent(4), 0.0);
    EXPECT_EQ(hist.getBinNumberOfEntries(4), 0);
    EXPECT_EQ(hist.getBinError(4), 0.0);

    // another fill
    const double xvalue(1.5);
    const int xbin = 1;

    hist.fill(xvalue, 1.0);
    hist.fill(xvalue, 3.0);
    EXPECT_EQ(2, hist.getBinNumberOfEntries(xbin));
    EXPECT_EQ(4.0, hist.getBinContent(xbin));
    EXPECT_EQ(1.0, hist.getBinError(xbin));

    // another fill
    hist.reset();
    hist.fill(xvalue, 1.0);
    hist.fill(xvalue, 2.0);
    hist.fill(xvalue, 3.0);
    EXPECT_EQ(3, hist.getBinNumberOfEntries(xbin));
    EXPECT_EQ(6.0, hist.getBinContent(xbin));
    EXPECT_EQ(2.0/3.0, hist.getBinError(xbin)*hist.getBinError(xbin));
}





#endif

