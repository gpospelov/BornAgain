// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      InputOutput/OutputDataWriter.h
//! @brief     Defines class OutputDataWriter.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef OUTPUTDATAWRITER_H
#define OUTPUTDATAWRITER_H

#include "WinDllMacros.h"
#include "OutputDataWriteStrategy.h"
#include <string>
#include <boost/scoped_ptr.hpp>

template <class T> class OutputData;

//! @class OutputDataWriter
//! @ingroup input_output_internal
//! @brief Write OutputData to file using different witing strategies
class BA_CORE_API_ OutputDataWriter
{
public:
    OutputDataWriter(const std::string& file_name);

    //! write output data to file
    void writeOutputData(const OutputData<double >& data);

    //! Sets concrete writing strategy
    void setStrategy(IOutputDataWriteStrategy *write_strategy);

private:
    std::string m_file_name;
    boost::scoped_ptr<IOutputDataWriteStrategy> m_write_strategy;
};

#endif // OUTPUTDATAWRITER_H


