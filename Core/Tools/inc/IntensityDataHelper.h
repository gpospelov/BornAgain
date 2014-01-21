// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/IntensityDataHelper.h
//! @brief     Defines class IntensityDataHelper.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INTENSITYDATAHELPER_H
#define INTENSITYDATAHELPER_H


#include "OutputData.h"

//! @class IntensityDataHelper
//! @ingroup tools
//! @brief Class holding collection of static methods to work with intensity data.

class BA_CORE_API_ IntensityDataHelper
{
public:

    //! Sets rectangular mask to IntensityData to exclude all points outside the
    //! mask from analysis
    BA_CORE_API_ static void setRectangularMask(OutputData<double>& data,
        double x1, double y1, double x2, double y2);


    //! Sets elliptic mask to IntensityData to exclude all points outside the
    //! mask from analysis
    BA_CORE_API_ static void setEllipticMask(OutputData<double>& data,
        double xc, double yc, double rx, double ry);

};


#endif // INTENSITYDATAHELPER_H
