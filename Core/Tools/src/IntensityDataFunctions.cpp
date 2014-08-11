#include "IntensityDataFunctions.h"
#include "OutputDataFunctions.h"
#include "MathFunctions.h"


void IntensityDataFunctions::setRectangularMask(OutputData<double>& data,
    double x1, double y1, double x2, double y2)
{
    Mask *mask1 = OutputDataFunctions::CreateRectangularMask(data, x1, y1, x2, y2);
    data.setMask(*mask1);
}


void IntensityDataFunctions::setEllipticMask(OutputData<double>& data,
    double xc, double yc, double rx, double ry)
{
    Mask *mask1 = OutputDataFunctions::CreateEllipticMask(data, xc, yc, rx, ry);
    data.setMask(*mask1);
}

double IntensityDataFunctions::GetRelativeDifference(const OutputData<double> &result, const OutputData<double> &reference)
{
    OutputData<double> *c_result = result.clone();

    // Calculating average relative difference.
    *c_result -= reference;
    *c_result /= reference;

    double diff(0);
    for(OutputData<double>::const_iterator it =
            c_result->begin(); it!=c_result->end(); ++it) {
        diff+= std::fabs(*it);
    }
    diff /= c_result->getAllocatedSize();

    if (MathFunctions::isnan(diff)) throw RuntimeErrorException("diff=NaN!");

    delete c_result;

    return diff;
}


OutputData<double> *IntensityDataFunctions::createClippedDataSet(const OutputData<double> &origin, double x1, double y1, double x2, double y2)
{
//    if (origin.getRank() != 2) {
//        throw LogicErrorException("IntensityDataFunctions::createClippedData()"
//                " -> Error! Works only on two-dimensional data");
//    }

    return 0;
}

