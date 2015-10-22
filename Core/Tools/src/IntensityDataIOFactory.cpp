// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/src/OutputDataIOFactory.cpp
//! @brief     Implements class OutputDataIOFactory.
//!
//! @homepage  http://www.bornagainproject.org
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
#include "IHistogram.h"

#include <boost/scoped_ptr.hpp>

/* ************************************************************************* */
// reading output data
/* ************************************************************************* */
OutputData<double > *IntensityDataIOFactory::readOutputData(
        const std::string& file_name)
{
    boost::scoped_ptr<OutputDataReader> P_reader(getReader(file_name));
    return P_reader->getOutputData();
}

IHistogram *IntensityDataIOFactory::readHistogram(const std::string &file_name)
{
    boost::scoped_ptr<OutputData<double> > data(readOutputData(file_name));
    return IHistogram::createHistogram(*data);
}

IHistogram *IntensityDataIOFactory::readIntensityData(const std::string &file_name)
{
    return readHistogram(file_name);
}


OutputDataReader* IntensityDataIOFactory::getReader(
        const std::string& file_name)
{
    OutputDataReader *result = new OutputDataReader( file_name );

    IOutputDataReadStrategy *read_strategy(0);
    if( Utils::FileSystem::GetFileMainExtension(file_name) == ".int") {
        read_strategy = new OutputDataReadStreamINT();
    } else {
        throw LogicErrorException("IntensityDataIOFactory::getReader() -> Error. "
                "Don't know how to read file '" + file_name+std::string("'"));
    }

    if( Utils::FileSystem::isGZipped(file_name) ) {
        result->setStrategy( new OutputDataReadStreamGZip( read_strategy ) );
    } else {
        result->setStrategy( read_strategy );
    }

    return result;
}

/* ************************************************************************* */
// writing output data
/* ************************************************************************* */
void IntensityDataIOFactory::writeOutputData(const OutputData<double>& data,
        const std::string& file_name)
{
    boost::scoped_ptr<OutputDataWriter> P_writer(getWriter(file_name));
    return P_writer->writeOutputData(data);
}

//void IntensityDataIOFactory::writeOutputData(const IHistogram &histogram,
//                                                const std::string &file_name)
//{
//    writeHistogram(histogram, file_name);
//}

void IntensityDataIOFactory::writeHistogram(const IHistogram &histogram,
                                                const std::string &file_name)
{
    boost::scoped_ptr<OutputData<double> > data(histogram.createOutputData());
    writeOutputData(*data, file_name);
}

void IntensityDataIOFactory::writeIntensityData(const IHistogram &histogram, const std::string &file_name)
{
    writeHistogram(histogram, file_name);
}

OutputDataWriter* IntensityDataIOFactory::getWriter(
        const std::string& file_name)
{
    IOutputDataWriteStrategy *write_strategy(0);
    if( Utils::FileSystem::GetFileExtension(file_name) == ".int") {
        write_strategy = new OutputDataWriteStreamINT();
    } else {
        throw LogicErrorException("IntensityDataIOFactory::getWriter() -> Error. "
                "Don't know how to write file '" + file_name+std::string("'"));
    }

    OutputDataWriter *writer = new OutputDataWriter( file_name );
    writer->setStrategy( write_strategy );

    return writer;
}


