#ifndef TESTFRESNELCOEFF_H
#define TESTFRESNELCOEFF_H

#include "IAlgorithm.h"
#include "OpticalFresnel.h"


class TestFresnelCoeff : public IAlgorithm
{
public:
    TestFresnelCoeff();

    class MyData {
    public:
        double alpha_i;
        OpticalFresnel::MultiLayerCoeff_t coeffs;
    };
    typedef std::vector<MyData > MyDataSet_t;

    void execute();
    void Draw(const MyDataSet_t &data);

private:

};


#endif // TESTFRESNELCOEFF_H
