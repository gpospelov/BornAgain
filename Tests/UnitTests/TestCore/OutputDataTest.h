#ifndef OUTPUTDATATEST_H
#define OUTPUTDATATEST_H

#include "OutputData.h"
#include <algorithm>
#include "OutputDataFunctions.h"
#include "ThreadInfo.h"
#include <boost/assign/list_of.hpp>


#include "gtest/gtest.h"

class OutputDataTest : public ::testing::Test
{
 protected:
    OutputDataTest();
    virtual ~OutputDataTest();

    OutputData<int> int_data_0d;
    OutputData<float> fl_data_1d;
    OutputData<double> db_data_3d;
    std::vector<size_t> zero_3d_coordinate;
};

OutputDataTest::OutputDataTest()
{
    zero_3d_coordinate.push_back(0);
    zero_3d_coordinate.push_back(0);
    zero_3d_coordinate.push_back(0);
    AxisDouble angle_axis("angle", 20, 0.0, 0.1);
    AxisDouble length_axis("length", 10, 0.0, 0.5);
    AxisDouble index_axis("index", 10, 1, 10);
    fl_data_1d.addAxis(angle_axis);

    db_data_3d.addAxis(angle_axis);
    db_data_3d.addAxis(length_axis);
    db_data_3d.addAxis(index_axis);
    OutputData<double>::iterator it = db_data_3d.begin();
    for (size_t i=0; i<2000; ++i)
    {
        *it = (double)i;
        ++it;
    }
}

OutputDataTest::~OutputDataTest()
{
}

TEST_F(OutputDataTest, SingleElementAfterConstruction)
{
    EXPECT_EQ((size_t)1, int_data_0d.getAllocatedSize());
}

TEST_F(OutputDataTest, SizeAfterAddingAxes)
{
    EXPECT_EQ((size_t)1, int_data_0d.getAllocatedSize());
    EXPECT_EQ((size_t)20, fl_data_1d.getAllocatedSize());
    EXPECT_EQ((size_t)2000, db_data_3d.getAllocatedSize());
}

TEST_F(OutputDataTest, DataInitialization)
{
    std::vector<int> coordinates;
    coordinates.push_back(11);
    coordinates.push_back(4);
    coordinates.push_back(3);
    EXPECT_DOUBLE_EQ((double)1143, db_data_3d[db_data_3d.toIndex(coordinates)]);
}

TEST_F(OutputDataTest, DataCopying)
{
    OutputData<double> data1;
    OutputData<double> data2;
    data1.addAxis("axis1", 10, 0., 10.);
    data2.addAxis("axis1", 10, 0., 10.);
    EXPECT_TRUE( data1.hasSameDimensions(data2));
    EXPECT_TRUE( data1.hasSameShape(data2));

    data1.addAxis("axis2", 10, 0., 10.);
    data2.addAxis("axis2", 10, 1., 10.);
    EXPECT_TRUE( data1.hasSameDimensions(data2));
    EXPECT_FALSE( data1.hasSameShape(data2));

    data2.copyFrom(data1);
    EXPECT_TRUE( data1.hasSameDimensions(data2));
    EXPECT_TRUE( data1.hasSameShape(data2));

    data1.addAxis("axis3", 10, 0., 10.);
    data2.addAxis("axis3another", 10, 0., 10.);
    EXPECT_TRUE( data1.hasSameDimensions(data2));
    EXPECT_FALSE( data1.hasSameShape(data2));

    data1.setAllTo(10);
    data2.copyFrom(data1);
    EXPECT_TRUE( data1.totalSum() == data2.totalSum() );
    EXPECT_TRUE( data1.hasSameDimensions(data2));
    EXPECT_TRUE( data1.hasSameShape(data2));
    EXPECT_TRUE( data2.hasSameDimensions(data1));
    EXPECT_TRUE( data2.hasSameShape(data1));
    EXPECT_TRUE( data1.hasSameDimensions(data1));
    EXPECT_TRUE( data1.hasSameShape(data1));
    EXPECT_TRUE( data2.hasSameDimensions(data2));
    EXPECT_TRUE( data2.hasSameShape(data2));

}

TEST_F(OutputDataTest, MaxElement)
{
    OutputData<double > data;
    data.addAxis("axis1", 10, 0., 10.);
    data.addAxis("axis2", 2, 0., 10.);
    data.setAllTo(1.0);

    OutputData<double >::iterator it = data.begin();
    for (size_t i=0; i<data.getAllocatedSize(); ++i) if(i==10) (*it)=10.0;
    OutputData<double >::const_iterator cit = std::max_element(data.begin(), data.end());
    EXPECT_EQ( double(10.0), (*cit));
}

TEST_F(OutputDataTest, ValueOfAxis)
{
    OutputData<double > data;
    data.addAxis("axis1", 10, 0., 9.);
    data.addAxis("axis2", 2, 0., 10.);
    EXPECT_EQ( double(0.0), data.getValueOfAxis("axis1", 0));
    EXPECT_EQ( double(0.0), data.getValueOfAxis("axis2", 0));
    EXPECT_EQ( double(0.0), data.getValueOfAxis("axis1", 1));
    EXPECT_EQ( double(10.0), data.getValueOfAxis("axis2", 1));
    EXPECT_EQ( double(1.0), data.getValueOfAxis("axis1", 2));
    EXPECT_EQ( double(0.0), data.getValueOfAxis("axis2", 2));
    EXPECT_EQ( double(9.0), data.getValueOfAxis("axis1", 19));
    EXPECT_EQ( double(10.0), data.getValueOfAxis("axis2", 19));
}


TEST_F(OutputDataTest, SetRectangularMask)
{
    OutputData<double > data;
    data.addAxis("x", 10, 0., 9.);
    data.addAxis("y", 6, 0., 5.);
    data.setAllTo(0.0);
    const double minima[]={0.6, 0.6};
    const double maxima[]={2.6, 2.6};
    Mask *mask1 = OutputDataFunctions::CreateRectangularMask(data, minima, maxima);
    data.setMask(*mask1);
    int index(0);
    for(OutputData<double>::iterator it = data.begin(); it!=data.end(); ++it) {
        double x = data.getValueOfAxis("x", it.getIndex());
        double y = data.getValueOfAxis("y", it.getIndex());
        EXPECT_EQ( x, double(index/3+1) );
        EXPECT_EQ( y, double(index%3+1) );
        ++index;
    }
    data.removeAllMasks();
    index=0;
    for(OutputData<double>::iterator it = data.begin(); it!=data.end(); ++it) {
        EXPECT_EQ( int(index++), int(it.getIndex()) );
    }
}

TEST_F(OutputDataTest, SetEllipticMask)
{
    OutputData<double > data;
    data.addAxis("x", 10, 0., 9.);
    data.addAxis("y", 6, 0., 5.);
    data.setAllTo(0.0);
    const double center[]={2., 3.};
    const double radii[]={1., 2.};
    Mask *mask1 = OutputDataFunctions::CreateEllipticMask(data, center, radii);
    data.setMask(*mask1);
    int index(0);
    const int reference[]={9,13,14,15,16,17,21};
    for(OutputData<double>::iterator it = data.begin(); it!=data.end(); ++it) {
        EXPECT_EQ( int(reference[index++]), int(it.getIndex()) );
    }
}

TEST_F(OutputDataTest, SetCleared)
{
    db_data_3d.clear();
    db_data_3d.setAllTo(1.0);
    EXPECT_EQ( db_data_3d[0], 1.0);
}


// y |
// --------------------------------------------
// 4 | 4   9   14  19  24  29  34  39  44  49 |
// 3 | 3   8   13  18  23  28  33  38  43  48 |
// 2 | 2   7   12  17  22  27  32  37  42  47 |
// 1 | 1   6   11  16  21  26  31  36  41  46 |
// 0 | 0   5   10  15  20  25  30  35  40  45 |
// --------------------------------------------
//   | 0   1   2   3   4   5   6   7   8   9  | x

TEST_F(OutputDataTest, ThreadInfoIterator)
{
    OutputData<double > data;
    data.addAxis("x", 10, 0., 9.);
    data.addAxis("y", 5, 0., 4.);

    int index(0);
    for(OutputData<double>::iterator it = data.begin(); it!=data.end(); ++it) {
        (*it) = double(index++);
    }

    ThreadInfo thread_info;
    thread_info.n_threads = 4;
    int istart[] = {0, 13, 26, 39};
    for(size_t i_thread=0; i_thread<4; i_thread++) {
        index = istart[i_thread];
        thread_info.current_thread = i_thread;
        for(OutputData<double>::iterator it = data.begin(thread_info); it!=data.end(thread_info); ++it) {
            EXPECT_EQ((*it), (double)index++);
        }
    }

}


// y |
// --------------------------------------------
// 4 | 4   9   14  19  24  29  34  39  44  49 |
// 3 | 3   8   13  18  23  28  33  38  43  48 |
// 2 | 2   7   12  17  22  27  32  37  42  47 |
// 1 | 1   6   11  16  21  26  31  36  41  46 |
// 0 | 0   5   10  15  20  25  30  35  40  45 |
// --------------------------------------------
//   | 0   1   2   3   4   5   6   7   8   9  | x

TEST_F(OutputDataTest, ThreadInfoMaskedIterator)
{
    OutputData<double > data;
    data.addAxis("x", 10, 0., 9.);
    data.addAxis("y", 5, 0., 4.);

    int index(0);
    for(OutputData<double>::iterator it = data.begin(); it!=data.end(); ++it) {
        (*it) = double(index++);
    }

    Mask *mask1 = OutputDataFunctions::CreateRectangularMask(data, 1.99, 0.99, 7.01, 3.01);
    data.setMask(*mask1);

    const int nthreads = 4;
    ThreadInfo thread_info;
    thread_info.n_threads = nthreads;

    std::vector<std::vector<int> > values;
    values.resize(nthreads);
    values[0] = boost::assign::list_of(11)(12);
    values[1] = boost::assign::list_of(13)(16)(17)(18)(21)(22)(23);
    values[2] = boost::assign::list_of(26)(27)(28)(31)(32)(33)(36)(37)(38);

    for(size_t i_thread=0; i_thread<4; i_thread++) {
        int index = 0;
        thread_info.current_thread = i_thread;
        for(OutputData<double>::iterator it = data.begin(thread_info); it!=data.end(thread_info); ++it) {
            EXPECT_EQ((*it), values[i_thread][index++]);
        }
    }

}

#endif // OUTPUTDATATEST_H
