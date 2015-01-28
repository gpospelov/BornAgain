// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/IntensityDataFunctions.h
//! @brief     Defines class IntensityDataFunctions.
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INTENSITYDATAFUNCTIONS_H
#define INTENSITYDATAFUNCTIONS_H


#include "OutputData.h"

//! @class IntensityDataFunctions
//! @ingroup tools
//! @brief Class holding collection of static methods to work with intensity data.

class  BA_CORE_API_ IntensityDataFunctions
{
public:

    //! @brief Sets rectangular mask to IntensityData to exclude all points outside the
    //! mask from analysis. If masks alreay exists, they will be replaced.
    //! @param data Intensity data object to set the mask
    //! @param x1 x-cordinate of lower left corner of the rectangle
    //! @param y1 y-cordinate of lower left corner of the rectangle
    //! @param x2 x-cordinate of top right corner of the rectangle
    //! @param y2 y-cordinate of top right corner of the rectangle
    //! @param invert_flag if true the area will be included in the analysis
    static void setRectangularMask(OutputData<double>& data,
        double x1, double y1, double x2, double y2, bool invert_flag = false);

    //! @brief Adds rectangular mask to IntensityData to exclude all points outside the
    //! mask from analysis
    static void addRectangularMask(OutputData<double>& data,
        double x1, double y1, double x2, double y2, bool invert_flag = false);

    //! Sets elliptic mask to IntensityData to exclude all points outside the
    //! mask from analysis
    static void setEllipticMask(OutputData<double>& data,
        double xc, double yc, double rx, double ry, bool invert_flag = false);

    //! Adds elliptic mask to IntensityData to exclude all points outside the
    //! mask from analysis
    static void addEllipticMask(OutputData<double>& data,
        double xc, double yc, double rx, double ry, bool invert_flag = false);

    //! Returns relative difference between two data sets
    //! sum(result[i] - reference[i])/reference[i])
    static double getRelativeDifference(const OutputData<double> &result,
                         const OutputData<double> &reference);

    //! Returns new IntensityData objects which axes clipped to represent the specified rectangle
    static OutputData<double> *createClippedDataSet(const OutputData<double> &origin, double x1, double y1, double x2, double y2);

};


#endif // INTENSITYDATAHELPER_H
