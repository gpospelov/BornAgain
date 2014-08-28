// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/IntensityDataFunctions.h
//! @brief     Defines class IntensityDataFunctions.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
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

    //! Sets rectangular mask to IntensityData to exclude all points outside the
    //! mask from analysis
    static void setRectangularMask(OutputData<double>& data,
        double x1, double y1, double x2, double y2);

    //! Sets elliptic mask to IntensityData to exclude all points outside the
    //! mask from analysis
    static void setEllipticMask(OutputData<double>& data,
        double xc, double yc, double rx, double ry);

    //! Returns relative difference between two data sets
    //! sum(result[i] - reference[i])/reference[i])
    static double getRelativeDifference(const OutputData<double> &result,
                         const OutputData<double> &reference);

    //! Returns new IntensityData objects which axes clipped to represent the specified rectangle
    static OutputData<double> *createClippedDataSet(const OutputData<double> &origin, double x1, double y1, double x2, double y2);

};


#endif // INTENSITYDATAHELPER_H
