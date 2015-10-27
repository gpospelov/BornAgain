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
#include "boost_streams.h"
#include <fstream>

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
	if (OutputDataIOHelper::isBinaryFile(m_file_name)) {
		std::cout << "XXX is binary file" << m_file_name << std::endl;
		openmode = std::ios::in | std::ios_base::binary;
	}
	else {
		std::cout << "XXX NOT binary file " << m_file_name << std::endl;

	}
    fin.open(m_file_name.c_str(), openmode );
    if(!fin.is_open()) {
        throw FileNotIsOpenException("OutputDataReader::getOutputData() -> Error. Can't open file '"
                                     + m_file_name + "' for reading.");
    }
    if (!fin.good()) {
        throw FileIsBadException("OutputDataReader::getOutputData() -> Error! File is not good, "
                                 "probably it is a directory.");
    }

    // FIXME Here we read whole file content into the buffer and then make a stream out of it.
    // This is not efficient, and in most cases would be better to return filtered stream instead.
    // But such approach cause a problem in the case of gzipped tiff files. So for unification we
    // use reading through the buffer which always works.
	std::cout << "XXX 1.1" << std::endl;

//    std::vector<char> buffer = readBuffer(fin);
	//	std::cout << "XXX 1.2" << std::endl;
	//	boost::iostreams::stream<boost::iostreams::array_source> array_stream(&buffer[0], buffer.size());
	//	std::cout << "XXX 1.3" << std::endl;

	//    OutputData<double > *result = m_read_strategy->readOutputData(array_stream);
	//	std::cout << "XXX 1.4" << std::endl;


	OutputData<double > *result = getFromStream(fin);

	fin.close();
	std::cout << "XXX 1.5" << std::endl;

    return result;
}


void OutputDataReader::setStrategy(IOutputDataReadStrategy *read_strategy)
{
    m_read_strategy.reset(read_strategy);
}

std::vector<char> OutputDataReader::readBuffer(std::istream &input_stream)
{
	std::cout << "XXX 2.1" << std::endl;
	boost::iostreams::filtering_streambuf<boost::iostreams::input> input_filtered;
    if(OutputDataIOHelper::isGZipped(m_file_name)) {
		std::cout << "XXX 2.2" << std::endl;
		input_filtered.push(boost::iostreams::gzip_decompressor());
		std::cout << "XXX 2.3" << std::endl;

	}	
    else if(OutputDataIOHelper::isBZipped(m_file_name)) {
        input_filtered.push(boost::iostreams::bzip2_decompressor());
    }

	std::cout << "XXX 2.4" << std::endl;
	input_filtered.push(input_stream);
	std::cout << "XXX 2.5" << std::endl;
	std::vector<char> buffer;
	std::cout << "XXX 2.6a" << std::endl;
	std::istream incoming(&input_filtered);
	boost::iostreams::copy(incoming, boost::iostreams::back_inserter(buffer));

//	std::vector<char> buffer((std::istreambuf_iterator<char>(incoming)),  (std::istreambuf_iterator<char>()));

//	stringstream strstream;
	//	boost::iostreams::copy(in, strstream);
	//	return strstream.str();


	std::cout << "XXX 2.7" << std::endl;
	return buffer;
}


OutputData<double > *OutputDataReader::getFromStream(std::istream &input_stream)
{
	std::cout << "XXX 2.1" << std::endl;
	boost::iostreams::filtering_streambuf<boost::iostreams::input> input_filtered;
	if (OutputDataIOHelper::isGZipped(m_file_name)) {
		std::cout << "XXX 2.2" << std::endl;
		input_filtered.push(boost::iostreams::gzip_decompressor());
		std::cout << "XXX 2.3" << std::endl;

	}
	else if (OutputDataIOHelper::isBZipped(m_file_name)) {
		std::cout << "XXX 2.4" << std::endl;
		input_filtered.push(boost::iostreams::bzip2_decompressor());
		std::cout << "XXX 2.5" << std::endl;
	}
	input_filtered.push(input_stream);
	std::stringstream strstream;
	//	std::cout << "XXX 2.6" << std::endl;
	boost::iostreams::copy(input_filtered, strstream);
	//	std::cout << "XXX 2.7" << std::endl;

	//std::istream incoming(&input_filtered);
	//return m_read_strategy->readOutputData(incoming);

	return m_read_strategy->readOutputData(strstream);
}