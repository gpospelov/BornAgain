// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/IntensityDataIOFactory.h
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
#include <boost/shared_ptr.hpp>

template <class T> class OutputData;

//! @class IntensityDataIOFactory
//! @ingroup tools
//! @brief Reads OutputData from files in different format

class BA_CORE_API_ IntensityDataIOFactory
{
public:
    typedef boost::shared_ptr<OutputDataReader > OutputDataReader_t;
    typedef boost::shared_ptr<OutputDataWriter > OutputDataWriter_t;

    static OutputData<double > *readIntensityData(const std::string& file_name);
    static OutputDataReader_t getReader(const std::string& file_name);

    static void writeIntensityData(const OutputData<double>& data,
            const std::string& file_name);
    static OutputDataWriter_t getWriter(const std::string& file_name);
};

#endif // OUTPUTDATAIOFACTORY_H


