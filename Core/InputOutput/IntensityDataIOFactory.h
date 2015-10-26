// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      InputOutput/IntensityDataIOFactory.h
//! @brief     Defines class IntensityDataIOFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INTENSITYDATAIOFACTORY_H
#define INTENSITYDATAIOFACTORY_H

#include "WinDllMacros.h"
#include "OutputDataReader.h"
#include "OutputDataWriter.h"

#include <string>

template <class T> class OutputData;
class IHistogram;

//! @class IntensityDataIOFactory
//! @ingroup input_output
//! @brief Provides users with possibility to read and write IntensityData from/to files
//! in different format.

class BA_CORE_API_ IntensityDataIOFactory
{
public:
    static OutputData<double > *readOutputData(const std::string& file_name);

    static IHistogram *readHistogram(const std::string& file_name);

    static IHistogram *readIntensityData(const std::string& file_name);


    static void writeOutputData(const OutputData<double>& data,
            const std::string& file_name);

    static void writeHistogram(const IHistogram &histogram,
            const std::string& file_name);

    static void writeIntensityData(const IHistogram &histogram,
            const std::string& file_name);

};

#endif // OUTPUTDATAIOFACTORY_H


