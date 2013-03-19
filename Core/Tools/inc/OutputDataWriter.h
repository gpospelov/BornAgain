// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @copyright Forschungszentrum Jülich GmbH 2013
//             
//  Homepage:  apps.jcns.fz-juelich.de/BornAgain
//  License:   GNU General Public License v3 or higher (see COPYING)
//
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
//! @file      Tools/OutputDataWriter.h 
//! @brief     Defines class OutputDataWriter.
//
// ************************************************************************** //

#ifndef OUTPUTDATAWRITER_H
#define OUTPUTDATAWRITER_H

#include "OutputData.h"
#include "OutputDataWriteStrategy.h"
#include "Types.h"
#include <string>

//! Write OutputData to file using different witing strategies

class OutputDataWriter
{
public:
    OutputDataWriter() : m_write_strategy(0) {}
    OutputDataWriter(const std::string &file_name) : m_file_name(file_name), m_write_strategy(0) {}
    OutputDataWriter(IOutputDataWriteStrategy *write_strategy) : m_write_strategy(write_strategy) {}
    virtual ~OutputDataWriter() { delete m_write_strategy; }

    //! write output data to file
    void writeOutputData(const OutputData<double > &data);

    //! set concrete writing strategy
    void setStrategy(IOutputDataWriteStrategy *write_strategy) { delete m_write_strategy; m_write_strategy = write_strategy; }

private:
    std::string m_file_name;
    IOutputDataWriteStrategy *m_write_strategy;
};

#endif // OUTPUTDATAWRITER_H
