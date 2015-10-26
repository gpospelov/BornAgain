// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      InputOutput/OutputDataReader.cpp
//! @brief     Implements class OutputDataReader.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //
#include "OutputData.h"
#include "OutputDataReader.h"
#include "OutputDataReadStrategy.h"
#include "OutputDataIOHelper.h"
#include <fstream>
#include <cassert>
#include <iostream>

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
GCC_DIAG_ON(unused-parameter);


OutputDataReader::OutputDataReader(const std::string &file_name)
    : m_file_name(file_name)
{

}


OutputData<double > *OutputDataReader::getOutputData()
{
    if(!m_read_strategy) {
        throw NullPointerException("OutputDataReader::getOutputData() ->"
                                   " Error! No read strategy defined");
    }

    std::ifstream fin;
    std::ios_base::openmode openmode = std::ios::in;
    if(OutputDataIOHelper::isBinaryFile(m_file_name)) openmode = std::ios::in | std::ios_base::binary;

    fin.open(m_file_name.c_str(), openmode );
    if( !fin.is_open() ) {
        throw FileNotIsOpenException("OutputDataReader::getOutputData() -> Error. Can't open file '"
                                     + m_file_name + "' for reading.");
    }
    if ( !fin.good() ) {
        throw FileIsBadException("OutputDataReader::getOutputData() -> Error! File is not good, "
                                 "probably it is a directory.");
    }

    // FIXME Here we read whole file content into the buffer and then make a stream out of it.
    // This is not efficient, and in most cases would be better to return filtered stream instead.
    // But such approach cause a problem in the case of gzipped tiff files. So for unification we
    // use reading through the buffer which always works.
    std::vector<char> buffer = readBuffer(fin);
    boost::iostreams::stream<boost::iostreams::array_source> array_stream(&buffer[0], buffer.size());

    OutputData<double > *result = m_read_strategy->readOutputData(array_stream);
    fin.close();

    return result;
}


void OutputDataReader::setStrategy(IOutputDataReadStrategy *read_strategy)
{
    m_read_strategy.reset(read_strategy);
}

std::vector<char> OutputDataReader::readBuffer(std::istream &input_stream)
{
    boost::iostreams::filtering_streambuf<boost::iostreams::input> input_filtered;
    if(OutputDataIOHelper::isGZipped(m_file_name)) {
        input_filtered.push(boost::iostreams::gzip_decompressor());
    }
    else if(OutputDataIOHelper::isBZipped(m_file_name)) {
        input_filtered.push(boost::iostreams::bzip2_decompressor());
    }

    input_filtered.push(input_stream);
    std::vector<char> buffer;
    boost::iostreams::copy(input_filtered, boost::iostreams::back_inserter(buffer));
    return buffer;
}


