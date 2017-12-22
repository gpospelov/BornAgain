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

TEST_F(FourierTransformTest, fwfftTest)
{
    //std::vector<double> signal, result;
    std::vector<std::vector<double>> signal, result;
    std::vector<double> row;

    int h = 17*17; //rows
    int w = 17; //columns

    for(int i=0; i<h; i++)
    {
        row.clear();
        for(int j=0; j<w; j++)
        {
            if(j != 4)
                row.push_back(1);
            else
                row.push_back(1);
        }
        signal.push_back(row);
    }

    std::cout << "\nRows of signal:" << signal.size() << std::endl;
    std::cout << "Columns of signal:" << signal[0].size() << std::endl;
    std::cout << "Contents of signal:" << std::endl;
    for(std::vector<std::vector<double>>::const_iterator i = signal.begin(); i != signal.end(); i++)
    {
        for(std::vector<double>::const_iterator j = (*i).begin(); j != (*i).end(); j++)
            std::cout << *j << ' ';
        std::cout << std::endl;
    }

    FourierTransform ft;
    ft.fft(signal, result);

    std::cout << "\nRows of result:" << result.size() << std::endl;
    std::cout << "Columns of result:" << result[0].size() << std::endl;
    std::cout << "Contents of result:" << std::endl;
    for(std::vector<std::vector<double>>::const_iterator i = result.begin(); i != result.end(); i++)
    {
        for(std::vector<double>::const_iterator j = (*i).begin(); j != (*i).end(); j++)
            std::cout << *j << ' ';
        std::cout << std::endl;
    }



    /*
    std::cout << "\nSize of signal:" << signal.size() << std::endl;
    std::cout << "Contents of signal:" << std::endl;
    for(std::vector<std::vector<double>>::const_iterator i = signal.begin(); i != signal.end(); i++)
    {
        std::cout << "LOOP1";
        for(std::vector<double>::const_iterator j = (*i).begin(); j != (*i).end(); j++)
            std::cout << *j << ' ';
        std::cout << "LOOP1";
    }


    FourierTransform ft;
    ft.fft(signal, result);

    std::cout << "\n\nSize of result:" << result.size() << std::endl;
    std::cout << "Contents of result:" << std::endl;
    for(std::vector<std::vector<double>>::const_iterator i = result.begin(); i != result.end(); i++)
    {
        for(std::vector<double>::const_iterator j = (*i).begin(); j != (*i).end(); j++)
            std::cout << *j << ' ';
        std::cout << "LOOP1";
    }

    */

    EXPECT_EQ(2,1) << "doesnt work";
}





void fun2()
{
    //std::vector<double> signal, result;
    std::vector<std::vector<double>> signal, result;
    std::vector<double> row;



    size_t h = 2; //rows
    size_t w = 10; //columns

    double init_value = 3.14;


    //now we have an empty 2D-matrix of size (0,0). Resizing it with one single command:
    signal.resize(w ,std::vector<double>(h , init_value) );

    for(size_t i=1; i<=h; i++)
    {
        for(size_t j=1; j<=w; j++)
            std::cout << signal[i][j] << " ";
        std::cout << std::endl;
        //row.clear();
    }

    /*
    std::cout << "\nSize of signal:" << signal.size() << std::endl;
    std::cout << "Contents of signal:" << std::endl;
    for(std::vector<std::vector<double>>::const_iterator i = signal.begin(); i != signal.end(); i++)
    {
        std::cout << "LOOP1";
        for(std::vector<double>::const_iterator j = (*i).begin(); j != (*i).end(); j++)
            std::cout << *j << ' ';
        std::cout << "LOOP1";
    }


    FourierTransform ft;
    ft.fft(signal, result);

    std::cout << "\n\nSize of result:" << result.size() << std::endl;
    std::cout << "Contents of result:" << std::endl;
    for(std::vector<std::vector<double>>::const_iterator i = result.begin(); i != result.end(); i++)
    {
        for(std::vector<double>::const_iterator j = (*i).begin(); j != (*i).end(); j++)
            std::cout << *j << ' ';
        std::cout << "LOOP1";
    }

    */

    EXPECT_EQ(2,1) << "doesnt work";
}




void fun()
{
    std::vector<std::vector<double>> signal, result;
    for(size_t i = 1; i <= 10; i++)
    {
        for(size_t j = 1; j <= 10; j++)
            signal[i].push_back(j);
        /*
        if(i != 50)
            signal.push_back(1);
        else
            signal.push_back(50);
        */
    }

    std::cout << "\nSize of signal:" << signal.size() << std::endl;
    std::cout << "Contents of signal:" << std::endl;
    /*
    for (std::vector<double>::const_iterator i = signal.begin(); i != signal.end(); ++i)
    {
        std::cout << *i << ' ';
    }
    */
    for (size_t i = 0; i < signal.size(); i++)
    {
        for (size_t j = 0; j < signal[i].size(); j++)
        {
            std::cout << signal[i][j];
        }
    }

    /*
    FourierTransform ft;
    ft.fft(signal, result);
    */
    std::cout << "\n\nSize of result:" << result.size() << std::endl;
    std::cout << "Contents of result:" << std::endl;
    /*
    for (std::vector<std::vector<double>>::const_iterator i = result.begin(); i != result.end(); ++i)
    {
        std::cout << *i << ' ';
    }
    */


    for (size_t i = 0; i < result.size(); i++)
    {
        for (size_t j = 0; j < result[i].size(); j++)
        {
            std::cout << result[i][j];
        }
    }
}

#endif // FOURIERTRANSFORMTEST_H
