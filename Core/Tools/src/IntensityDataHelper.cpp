#include "IntensityDataHelper.h"
#include "OutputDataFunctions.h"


void IntensityDataHelper::setRectangularMask(OutputData<double>& data,
    double x1, double y1, double x2, double y2)
{
    Mask *mask1 = OutputDataFunctions::CreateRectangularMask(data, x1, y1, x2, y2);
    data.setMask(*mask1);
}


void IntensityDataHelper::setEllipticMask(OutputData<double>& data,
    double xc, double yc, double rx, double ry)
{
    Mask *mask1 = OutputDataFunctions::CreateEllipticMask(data, xc, yc, rx, ry);
    data.setMask(*mask1);
}

