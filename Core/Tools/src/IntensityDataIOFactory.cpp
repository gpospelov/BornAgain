// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/src/OutputDataIOFactory.cpp
//! @brief     Implements class OutputDataIOFactory.
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IntensityDataIOFactory.h"
#include "OutputDataReadStrategy.h"
#include "OutputDataWriteStrategy.h"
#include "OutputDataReader.h"
#include "OutputDataWriter.h"
#include "Exceptions.h"
#include "Utils.h"
#include "FileSystem.h"

/* ************************************************************************* */
// reading output data
/* ************************************************************************* */
OutputData<double > *IntensityDataIOFactory::readIntensityData(
        const std::string& file_name)
{
    return getReader(file_name)->getOutputData();
}


IntensityDataIOFactory::OutputDataReader_t IntensityDataIOFactory::getReader(
        const std::string& file_name)
{
    OutputDataReader *reader = new OutputDataReader( file_name );

    IOutputDataReadStrategy *read_strategy(0);
    if( Utils::FileSystem::GetFileMainExtension(file_name) == ".int") {
        read_strategy = new OutputDataReadStreamINT();
    } else {
        throw LogicErrorException("IntensityDataIOFactory::getReader() -> Error. "
                "Don't know how to read file '" + file_name+std::string("'"));
    }

    if( Utils::FileSystem::isGZipped(file_name) ) {
        reader->setStrategy( new OutputDataReadStreamGZip( read_strategy ) );
    } else {
        reader->setStrategy( read_strategy );
    }

    return OutputDataReader_t(reader);
}

/* ************************************************************************* */
// writing output data
/* ************************************************************************* */
void IntensityDataIOFactory::writeIntensityData(const OutputData<double>& data,
        const std::string& file_name)
{
    return getWriter(file_name)->writeOutputData(data);
}

IntensityDataIOFactory::OutputDataWriter_t IntensityDataIOFactory::getWriter(
        const std::string& file_name)
{
    OutputDataWriter *writer = new OutputDataWriter( file_name );

    IOutputDataWriteStrategy *write_strategy(0);
    if( Utils::FileSystem::GetFileExtension(file_name) == ".int") {
        write_strategy = new OutputDataWriteStreamINT();
    } else {
        throw LogicErrorException("IntensityDataIOFactory::getWriter() -> Error. "
                "Don't know how to write file '" + file_name+std::string("'"));
    }

    writer->setStrategy( write_strategy );

    return OutputDataWriter_t(writer);
}


