#ifndef OUTPUTDATATEST_H
#define OUTPUTDATATEST_H

#include "OutputData.h"

class OutputDataTest : public ::testing::Test
{
protected:
    OutputDataTest();
    virtual ~OutputDataTest();

    OutputData<int> int_data_0d;
    OutputData<float> fl_data_1d;
    OutputData<double> db_data_3d;
};

OutputDataTest::OutputDataTest()
{
    fl_data_1d.addAxis(new NamedVector<double>("angle", 0.0, 0.1, 20));

    db_data_3d.addAxis(new NamedVector<double>("angle", 0.0, 0.1, 20));
    db_data_3d.addAxis(new NamedVector<double>("length", 0.0, 0.5, 10));
    db_data_3d.addAxis(new NamedVector<int>("index", 10, 1, 10));
}

OutputDataTest::~OutputDataTest()
{
}

#endif // OUTPUTDATATEST_H
