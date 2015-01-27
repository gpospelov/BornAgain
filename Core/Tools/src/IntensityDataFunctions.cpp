// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/src/IntensityDataFunctions.cpp
//! @brief     Implement class IntensityDataFunctions.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IntensityDataFunctions.h"
#include "OutputDataFunctions.h"
#include "MathFunctions.h"
#include <boost/scoped_ptr.hpp>

void IntensityDataFunctions::setRectangularMask(OutputData<double>& data,
    double x1, double y1, double x2, double y2, bool invert_flag)
{
    Mask *mask1 = OutputDataFunctions::CreateRectangularMask(data, x1, y1, x2, y2, invert_flag);
    data.setMask(*mask1);
}

void IntensityDataFunctions::addRectangularMask(OutputData<double> &data, double x1, double y1, double x2, double y2, bool invert_flag)
{
    Mask *mask1 = OutputDataFunctions::CreateRectangularMask(data, x1, y1, x2, y2, invert_flag);
    data.addMask(*mask1);
}


void IntensityDataFunctions::setEllipticMask(OutputData<double>& data,
    double xc, double yc, double rx, double ry, bool invert_flag)
{
    Mask *mask1 = OutputDataFunctions::CreateEllipticMask(data, xc, yc, rx, ry, invert_flag);
    data.setMask(*mask1);
}

void IntensityDataFunctions::addEllipticMask(OutputData<double> &data, double xc, double yc, double rx, double ry, bool invert_flag)
{
    Mask *mask1 = OutputDataFunctions::CreateEllipticMask(data, xc, yc, rx, ry, invert_flag);
    data.addMask(*mask1);
}

double IntensityDataFunctions::getRelativeDifference(
        const OutputData<double> &result, const OutputData<double> &reference)
{
    OutputData<double> *c_result = result.clone();

    // Calculating average relative difference.
    *c_result -= reference;
    *c_result /= reference;

    double diff(0);
    for(OutputData<double>::const_iterator it =
            c_result->begin(); it!=c_result->end(); ++it) {
        diff+= std::abs(*it);
    }
    diff /= c_result->getAllocatedSize();

    if (MathFunctions::isnan(diff)) throw RuntimeErrorException("diff=NaN!");

    delete c_result;

    return diff;
}


OutputData<double> *IntensityDataFunctions::createClippedDataSet(
        const OutputData<double> &origin, double x1, double y1,
        double x2, double y2)
{
    if (origin.getRank() != 2) {
        throw LogicErrorException("IntensityDataFunctions::createClippedData()"
                " -> Error! Works only on two-dimensional data");
    }

    OutputData<double > *result = new OutputData<double >;
    for(size_t i_axis=0; i_axis<origin.getRank(); i_axis++) {
        const IAxis *axis = origin.getAxis(i_axis);
        IAxis *new_axis;
        if(i_axis == 0) {
            new_axis = axis->createClippedAxis(x1, x2);
        } else {
            new_axis = axis->createClippedAxis(y1, y2);
        }
        result->addAxis(*new_axis);
        delete new_axis;
    }
    result->setAllTo(0.0);

    OutputData<double>::const_iterator it_origin = origin.begin();
    OutputData<double>::iterator it_result = result->begin();
    while (it_origin != origin.end())
    {
        double x = origin.getValueOfAxis(0, it_origin.getIndex());
        double y = origin.getValueOfAxis(1, it_origin.getIndex());
        if(result->getAxis(0)->contains(x) && result->getAxis(1)->contains(y)) {
            *it_result = *it_origin;
            ++it_result;
        }

        ++it_origin;
    }

    return result;
}

