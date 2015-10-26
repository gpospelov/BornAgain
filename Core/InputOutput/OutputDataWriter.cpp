// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      InputOutput/OutputDataWriter.cpp
//! @brief     Implements class OutputDataWriter.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "OutputDataWriter.h"
#include "OutputDataWriteStrategy.h"
#include "OutputDataIOHelper.h"
#include "OutputData.h"
#include <fstream>
#include <cassert>

#include "Macros.h"
GCC_DIAG_OFF(unused-parameter)
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/copy.hpp>
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4244)
#endif
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filter/bzip2.hpp>
#ifdef _MSC_VER
#pragma warning(pop)
#endif
#include <string>
GCC_DIAG_ON(unused-parameter)


OutputDataWriter::OutputDataWriter(const std::string &file_name)
    : m_file_name(file_name)
{

}

void OutputDataWriter::writeOutputData(const OutputData<double >& data)
{
    if(!m_write_strategy) {
        throw NullPointerException("OutputDataWriter::getOutputData() ->"
                                   " Error! No read strategy defined");
    }

    std::ofstream fout;

    std::ios_base::openmode openmode = std::ios::out;
    if(OutputDataIOHelper::isBinaryFile(m_file_name)) openmode = std::ios::out | std::ios_base::binary;

    fout.open(m_file_name.c_str(), openmode );

    if(!fout.is_open()) {
        throw FileNotIsOpenException("OutputDataWriter::writeOutputData() -> Error. "
                                     "Can't open file '"+m_file_name+"' for writing.");
    }
    if (!fout.good()) {
        throw FileIsBadException("OutputDataReader::writeOutputData() -> Error! "
                                 "File is not good, probably it is a directory.");
    }

    std::stringstream ss;
    m_write_strategy->writeOutputData(data, ss);

    boost::iostreams::filtering_streambuf<boost::iostreams::input> input_filtered;
    if(OutputDataIOHelper::isGZipped(m_file_name)) {
        input_filtered.push(boost::iostreams::gzip_compressor());
    }
    else if(OutputDataIOHelper::isBZipped(m_file_name)) {
        input_filtered.push(boost::iostreams::bzip2_compressor());
    }
    input_filtered.push(ss);

    boost::iostreams::copy(input_filtered, fout);


    fout.close();
}


void OutputDataWriter::setStrategy(IOutputDataWriteStrategy *write_strategy)
{
    m_write_strategy.reset(write_strategy);
}



