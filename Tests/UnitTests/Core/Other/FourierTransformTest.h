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
TEST_F(FourierTransformTest, fft2DTest1)
{
    std::vector<std::vector<double>> signal, result;
    std::vector<double> row_vec;

    //Works
    row_vec.push_back(1);
    row_vec.push_back(1);
    row_vec.push_back(1);
    row_vec.push_back(0);
    signal.push_back(row_vec);
    row_vec.clear();
    row_vec.push_back(1);
    row_vec.push_back(0);
    row_vec.push_back(0);
    row_vec.push_back(0);
    signal.push_back(row_vec);

    std::cout << "Example 1:" << std::endl;
    std::cout << "Contents of 2D signal:" << std::endl;

    for(std::vector<std::vector<double>>::const_iterator i = signal.begin(); i != signal.end(); i++)
    {
        for(std::vector<double>::const_iterator j = (*i).begin(); j != (*i).end(); j++)
            std::cout << *j << ' ';
        std::cout << std::endl;
    }

    FourierTransform ft;
    ft.fft(signal, result);

    std::cout << "Contents of 2D result:" << std::endl;
    for(std::vector<std::vector<double>>::const_iterator i = result.begin(); i != result.end(); i++)
    {
        for(std::vector<double>::const_iterator j = (*i).begin(); j != (*i).end(); j++)
            std::cout << *j << ' ';
        std::cout << std::endl;
    }


    EXPECT_EQ(2,2);

}


TEST_F(FourierTransformTest, fft2DTest2)
{
    std::vector<std::vector<double>> signal, result;
    std::vector<double> row_vec;


    //Works
    row_vec.push_back(1);
    row_vec.push_back(1);
    row_vec.push_back(0);
    row_vec.push_back(0);
    signal.push_back(row_vec);
    row_vec.clear();
    row_vec.push_back(0);
    row_vec.push_back(0);
    row_vec.push_back(0);
    row_vec.push_back(0);
    signal.push_back(row_vec);


    std::cout << "Example 2:" << std::endl;
    std::cout << "Contents of 2D signal:" << std::endl;

    for(std::vector<std::vector<double>>::const_iterator i = signal.begin(); i != signal.end(); i++)
    {
        for(std::vector<double>::const_iterator j = (*i).begin(); j != (*i).end(); j++)
            std::cout << *j << ' ';
        std::cout << std::endl;
    }

    FourierTransform ft;
    ft.fft(signal, result);

    std::cout << "Contents of 2D result:" << std::endl;
    for(std::vector<std::vector<double>>::const_iterator i = result.begin(); i != result.end(); i++)
    {
        for(std::vector<double>::const_iterator j = (*i).begin(); j != (*i).end(); j++)
            std::cout << *j << ' ';
        std::cout << std::endl;
    }


    EXPECT_EQ(2,2);

}

TEST_F(FourierTransformTest, fft2DTest3)
{
    std::vector<std::vector<double>> signal, result;
    std::vector<double> row_vec;

    //Doesnt work
    row_vec.push_back(1);
    row_vec.push_back(0);
    row_vec.push_back(1);
    signal.push_back(row_vec);
    row_vec.clear();
    row_vec.push_back(0);
    row_vec.push_back(1);
    row_vec.push_back(0);
    signal.push_back(row_vec);

    std::cout << "Example 3:" << std::endl;
    std::cout << "Contents of 2D signal:" << std::endl;

    for(std::vector<std::vector<double>>::const_iterator i = signal.begin(); i != signal.end(); i++)
    {
        for(std::vector<double>::const_iterator j = (*i).begin(); j != (*i).end(); j++)
            std::cout << *j << ' ';
        std::cout << std::endl;
    }

    FourierTransform ft;
    ft.fft(signal, result);

    std::cout << "Contents of 2D result:" << std::endl;
    for(std::vector<std::vector<double>>::const_iterator i = result.begin(); i != result.end(); i++)
    {
        for(std::vector<double>::const_iterator j = (*i).begin(); j != (*i).end(); j++)
            std::cout << *j << ' ';
        std::cout << std::endl;
    }


    EXPECT_EQ(2,2);

}


TEST_F(FourierTransformTest, fft2DTest4)
{
    std::vector<std::vector<double>> signal, result;
    std::vector<double> row_vec;

    //Doesn"t work
    row_vec.push_back(1);
    row_vec.push_back(88);
    row_vec.push_back(0);
    row_vec.push_back(1);
    row_vec.push_back(0);
    signal.push_back(row_vec);
    row_vec.clear();
    row_vec.push_back(0);
    row_vec.push_back(1);
    row_vec.push_back(1);
    row_vec.push_back(1);
    row_vec.push_back(0);
    signal.push_back(row_vec);

    std::cout << "Example 4:" << std::endl;
    std::cout << "Contents of 2D signal:" << std::endl;

    for(std::vector<std::vector<double>>::const_iterator i = signal.begin(); i != signal.end(); i++)
    {
        for(std::vector<double>::const_iterator j = (*i).begin(); j != (*i).end(); j++)
            std::cout << *j << ' ';
        std::cout << std::endl;
    }

    FourierTransform ft;
    ft.fft(signal, result);

    std::cout << "Contents of 2D result:" << std::endl;
    for(std::vector<std::vector<double>>::const_iterator i = result.begin(); i != result.end(); i++)
    {
        for(std::vector<double>::const_iterator j = (*i).begin(); j != (*i).end(); j++)
            std::cout << *j << ' ';
        std::cout << std::endl;
    }


    EXPECT_EQ(2,2);

}


TEST_F(FourierTransformTest, fft2DTest5)
{
    std::vector<std::vector<double>> signal, result;
    std::vector<double> row_vec;

    //Works
    row_vec.push_back(1);
    row_vec.push_back(0);
    row_vec.push_back(1);
    row_vec.push_back(5);
    signal.push_back(row_vec);
    row_vec.clear();
    row_vec.push_back(1);
    row_vec.push_back(0);
    row_vec.push_back(0);
    row_vec.push_back(0);
    signal.push_back(row_vec);
    row_vec.clear();
    row_vec.push_back(0);
    row_vec.push_back(1);
    row_vec.push_back(0);
    row_vec.push_back(1);
    signal.push_back(row_vec);
    row_vec.clear();
    row_vec.push_back(0);
    row_vec.push_back(1);
    row_vec.push_back(1);
    row_vec.push_back(1);
    signal.push_back(row_vec);

    std::cout << "Example 5:" << std::endl;
    std::cout << "Contents of 2D signal:" << std::endl;

    for(std::vector<std::vector<double>>::const_iterator i = signal.begin(); i != signal.end(); i++)
    {
        for(std::vector<double>::const_iterator j = (*i).begin(); j != (*i).end(); j++)
            std::cout << *j << ' ';
        std::cout << std::endl;
    }

    FourierTransform ft;
    ft.fft(signal, result);

    std::cout << "Contents of 2D result:" << std::endl;
    for(std::vector<std::vector<double>>::const_iterator i = result.begin(); i != result.end(); i++)
    {
        for(std::vector<double>::const_iterator j = (*i).begin(); j != (*i).end(); j++)
            std::cout << *j << ' ';
        std::cout << std::endl;
    }


    EXPECT_EQ(2,2);

}


TEST_F(FourierTransformTest, fft2DTest6)
{
    std::vector<std::vector<double>> signal, result;
    std::vector<double> row_vec;

    //Works
    row_vec.push_back(1);
    row_vec.push_back(0);
    row_vec.push_back(1);
    row_vec.push_back(5);
    signal.push_back(row_vec);
    row_vec.clear();
    row_vec.push_back(1);
    row_vec.push_back(0);
    row_vec.push_back(0);
    row_vec.push_back(0);
    signal.push_back(row_vec);
    row_vec.clear();
    row_vec.push_back(0);
    row_vec.push_back(1);
    row_vec.push_back(0);
    row_vec.push_back(1);
    signal.push_back(row_vec);
    row_vec.clear();
    row_vec.push_back(0);
    row_vec.push_back(1);
    row_vec.push_back(1);
    row_vec.push_back(1);
    signal.push_back(row_vec);
    row_vec.clear();
    row_vec.push_back(0);
    row_vec.push_back(0);
    row_vec.push_back(0);
    row_vec.push_back(0);
    signal.push_back(row_vec);

    std::cout << "Example 6:" << std::endl;
    std::cout << "Contents of 2D signal:" << std::endl;

    for(std::vector<std::vector<double>>::const_iterator i = signal.begin(); i != signal.end(); i++)
    {
        for(std::vector<double>::const_iterator j = (*i).begin(); j != (*i).end(); j++)
            std::cout << *j << ' ';
        std::cout << std::endl;
    }

    FourierTransform ft;
    ft.fft(signal, result);

    std::cout << "Contents of 2D result:" << std::endl;
    for(std::vector<std::vector<double>>::const_iterator i = result.begin(); i != result.end(); i++)
    {
        for(std::vector<double>::const_iterator j = (*i).begin(); j != (*i).end(); j++)
            std::cout << *j << ' ';
        std::cout << std::endl;
    }


    EXPECT_EQ(2,2);

}



TEST_F(FourierTransformTest, fft2DTest7)
{
    std::vector<std::vector<double>> signal, result;
    std::vector<double> row_vec;

    int nrows = 18; //# rows
    int ncols = 18; //# columns

    for(int row=0; row<nrows; row++)
    {
        row_vec.clear();
        for(int col=0; col<ncols; col++)
        {
            if(col != 5)
                row_vec.push_back(0);
            else
                row_vec.push_back(0);
            row_vec[0]=1;
        }
        signal.push_back(row_vec);
    }
    signal[5][5] = 23;

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
TEST_F(FourierTransformTest, fft1DTest)
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
