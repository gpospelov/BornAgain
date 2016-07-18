// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Detector/IntensityDataFunctions.h
//! @brief     Declares class IntensityDataFunctions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INTENSITYDATAFUNCTIONS_H
#define INTENSITYDATAFUNCTIONS_H

#include "OutputData.h"
class IResolutionFunction2D;
class IHistogram;

//! @class IntensityDataFunctions
//! @ingroup tools
//! @brief Class holding collection of static methods to work with intensity data.

class  BA_CORE_API_ IntensityDataFunctions
{
public:
    //! Returns relative difference between two data sets
    //! sum(result[i] - reference[i])/reference[i])
    static double getRelativeDifference(const OutputData<double> &result,
                         const OutputData<double> &reference);

    static OutputData<double> *createRelativeDifferenceData(const OutputData<double> &data,
                                                            const OutputData<double> &reference);

    static double getRelativeDifference(const IHistogram &result,
                         const IHistogram &reference);

    //! Returns new IntensityData objects which axes clipped to represent the specified rectangle
    static OutputData<double> *createClippedDataSet(
        const OutputData<double> &origin, double x1, double y1, double x2, double y2);

    //! Applies detector resolution function and returns new IntensityData object
    static OutputData<double> *applyDetectorResolution(
        const OutputData<double> &origin, const IResolutionFunction2D &resolution_function);

};

#endif // INTENSITYDATAFUNCTIONS_H
