#ifndef FOURIERTRANSFORMTEST_H
#define FOURIERTRANSFORMTEST_H

#include "google_test.h"
#include "BornAgainNamespace.h"
#include "FourierTransform.h"
#include "MathConstants.h"
#include "OutputData.h"


class FourierTransformTest : public ::testing::Test
{
protected:
    ~FourierTransformTest();
};

FourierTransformTest::~FourierTransformTest() = default;

// Just for checking implementation of 2D FT
TEST_F(FourierTransformTest, fwfft2DTest)
{
    std::vector<std::vector<double>> signal, result;
    std::vector<double> row_vec;

    int nrows = 19; //rows
    int ncols = 17; //columns

    for(int row=0; row<nrows; row++)
    {
        row_vec.clear();
        for(int col=0; col<ncols; col++)
        {
            if(col != 5)
                row_vec.push_back(col+1);
            else
                row_vec.push_back(col+1);
        }
        signal.push_back(row_vec);
    }

    std::cout << "\nRows of 2D signal:" << signal.size() << std::endl;
    std::cout << "Columns of 2D signal:" << signal[0].size() << std::endl;
    std::cout << "Contents of 2D signal:" << std::endl;

    for(std::vector<std::vector<double>>::const_iterator i = signal.begin(); i != signal.end(); i++)
    {
        for(std::vector<double>::const_iterator j = (*i).begin(); j != (*i).end(); j++)
            std::cout << *j << ' ';
        std::cout << std::endl;
    }

    FourierTransform ft;
    ft.fft(signal, result);

    std::cout << "\nRows of 2D result:" << result.size() << std::endl;
    std::cout << "Columns of 2D result:" << result[0].size() << std::endl;
    std::cout << "Contents of 2D result:" << std::endl;
    for(std::vector<std::vector<double>>::const_iterator i = result.begin(); i != result.end(); i++)
    {
        for(std::vector<double>::const_iterator j = (*i).begin(); j != (*i).end(); j++)
            std::cout << *j << ' ';
        std::cout << std::endl;
    }


    EXPECT_EQ(2,2);
}


// Just for checking implementation of 1D FT
TEST_F(FourierTransformTest, fwfft1DTest)
{
    std::vector<double> signal, result;

    int ncols = 17; //columns

    for(int col=0; col<ncols; col++)
    {
        if(col != 5)
            signal.push_back(col+1);
        else
            signal.push_back(col+1);
    }

    std::cout << "Columns of 1D signal:" << signal.size() << std::endl;
    std::cout << "Contents of 1D signal:" << std::endl;

    for(std::vector<double>::const_iterator i = signal.begin(); i != signal.end(); i++)
    {
        std::cout << *i << ' ';
    }

    FourierTransform ft;
    ft.fft(signal, result);

    std::cout << "\nColumns of 1D result:" << result.size() << std::endl;
    std::cout << "Contents of 1D result:" << std::endl;
    for(std::vector<double>::const_iterator i = result.begin(); i != result.end(); i++)
    {
        std::cout << *i << ' ';
    }

    EXPECT_EQ(2,2);
}

#endif // FOURIERTRANSFORMTEST_H
