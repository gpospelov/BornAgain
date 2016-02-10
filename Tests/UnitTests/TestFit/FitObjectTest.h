#ifndef FITOBJECTTEST_H
#define FITOBJECTTEST_H

#include "Units.h"
#include "FitObject.h"
#include "GISASSimulation.h"
#include "BornAgainNamespace.h"
#include <iostream>
#include "gtest/gtest.h"


class FitObjectTest : public ::testing::Test
{
 protected:
    FitObjectTest(){}
    virtual ~FitObjectTest(){}

};



TEST_F(FitObjectTest, Initialization)
{
    EXPECT_EQ(1, 1);

    GISASSimulation simulation;

    int nx(100), ny(100);
    double xmin(-1.0*Units::degree), xmax(1.0*Units::degree);
    double ymin(0.0*Units::degree), ymax(2.0*Units::degree);
    simulation.setDetectorParameters(nx, xmin, xmax, ny, ymin, ymax);

    OutputData<double> data;
    data.addAxis(FixedBinAxis(BornAgain::PHI_AXIS_NAME, nx, xmin, xmax));
    data.addAxis(FixedBinAxis(BornAgain::ALPHA_AXIS_NAME, ny, ymin, ymax));

    double weight(0.5);
    FitObject obj(simulation, data, weight);

    EXPECT_EQ(obj.getWeight(), weight);
    EXPECT_EQ(obj.getSizeOfData(), nx*ny);

    EXPECT_EQ(nullptr, obj.getSimulationData());
    EXPECT_TRUE(obj.getSimulation()->getOutputData()->hasSameShape(*obj.getRealData()));
}




#endif
