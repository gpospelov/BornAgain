// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/OutputDataWriter.h
//! @brief     Defines class OutputDataWriter.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef OUTPUTDATAWRITER_H
#define OUTPUTDATAWRITER_H

#include "OutputDataWriteStrategy.h"
#include <string>

//! @class OutputDataWriter
//! @ingroup tools
//! @brief Write OutputData to file using different witing strategies

class BA_CORE_API_ OutputDataWriter
{
public:
    OutputDataWriter() : m_write_strategy(0) {}
    OutputDataWriter(const std::string& file_name)
    : m_file_name(file_name), m_write_strategy(0) {}
    OutputDataWriter(IOutputDataWriteStrategy *write_strategy)
    : m_write_strategy(write_strategy) {}
    virtual ~OutputDataWriter() { delete m_write_strategy; }

    //! write output data to file
    void writeOutputData(const OutputData<double >& data);

    //! Sets concrete writing strategy
    void setStrategy(IOutputDataWriteStrategy *write_strategy)
    { delete m_write_strategy; m_write_strategy = write_strategy; }

private:
    std::string m_file_name;
    IOutputDataWriteStrategy *m_write_strategy;
};

#endif // OUTPUTDATAWRITER_H


