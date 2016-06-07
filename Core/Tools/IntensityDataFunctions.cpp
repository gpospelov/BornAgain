// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/IntensityDataFunctions.cpp
//! @brief     Implement class IntensityDataFunctions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IntensityDataFunctions.h"
#include "OutputDataFunctions.h"
#include "MathFunctions.h"
#include "IDetectorResolution.h"
#include "IResolutionFunction2D.h"
#include "ConvolutionDetectorResolution.h"
#include "IHistogram.h"
#include <memory>

double IntensityDataFunctions::getRelativeDifference(
        const OutputData<double> &result, const OutputData<double> &reference)
{
    double diff = 0.0;
    for(size_t i=0; i<result.getAllocatedSize(); ++i) {
        diff+= Numeric::get_relative_difference(result[i], reference[i]);
    }
    diff /= result.getAllocatedSize();

    if (std::isnan(diff)) throw RuntimeErrorException("diff=NaN!");
    return diff;
}

double IntensityDataFunctions::getRelativeDifference(
    const IHistogram &result, const IHistogram &reference)
{
    if(!result.hasSameDimensions(reference)) {
        throw LogicErrorException("IntensityDataFunctions::getRelativeDifference() -> Error. "
                                  "Histograms have different dimensions.");
    }

    double summ(0.0);
    for(size_t i=0; i<result.getTotalNumberOfBins(); ++i) {
        summ += Numeric::get_relative_difference(result.getBinContent(i),
                                                 reference.getBinContent(i));
    }
    return summ/result.getTotalNumberOfBins();
}


OutputData<double> *IntensityDataFunctions::createClippedDataSet(
        const OutputData<double> &origin, double x1, double y1, double x2, double y2)
{
    if (origin.getRank() != 2)
        throw LogicErrorException("IntensityDataFunctions::createClippedData()"
                " -> Error! Works only on two-dimensional data");

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
        double x = origin.getAxisValue(it_origin.getIndex(), 0);
        double y = origin.getAxisValue(it_origin.getIndex(), 1);
        if(result->getAxis(0)->contains(x) && result->getAxis(1)->contains(y)) {
            *it_result = *it_origin;
            ++it_result;
        }

        ++it_origin;
    }

    return result;
}

OutputData<double> *IntensityDataFunctions::applyDetectorResolution(
    const OutputData<double> &origin, const IResolutionFunction2D &resolution_function)
{
    if (origin.getRank() != 2)
        throw LogicErrorException("IntensityDataFunctions::applyDetectorResolution()"
                " -> Error! Works only on two-dimensional data");
    OutputData<double > *result = origin.clone();
    const std::unique_ptr<ConvolutionDetectorResolution> P_resolution(
        new ConvolutionDetectorResolution(resolution_function));
    P_resolution->applyDetectorResolution(result);
    return result;
}
