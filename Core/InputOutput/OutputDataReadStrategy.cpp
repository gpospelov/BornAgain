// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      InputOutput/OutputDataReadStrategy.cpp
//! @brief     Implements class OutputDataReadStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "OutputDataReadStrategy.h"
#include "Types.h"
#include "Exceptions.h"
#include "Utils.h"
#include "BornAgainNamespace.h"
#include "OutputData.h"
#include "OutputDataIOHelper.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include "Macros.h"
GCC_DIAG_OFF(unused-parameter);
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
#ifdef _MSC_VER
#pragma warning(pop)
#endif
#include <string>
GCC_DIAG_ON(unused-parameter);


/* ************************************************************************* */
// decorator to unzip stream
/* ************************************************************************* */
OutputData<double > *OutputDataReadStreamGZip::readOutputData(std::istream &input_stream)
{
    boost::iostreams::filtering_streambuf<boost::iostreams::input> input_filtered;
    input_filtered.push(boost::iostreams::gzip_decompressor());
    input_filtered.push(input_stream);

//    std::vector<char> buffer;
//    boost::iostreams::copy(input_filtered, boost::iostreams::back_inserter(buffer)); // working

    std::istream incoming(&input_filtered);

//    std::istream incoming;
//    boost::iostreams::copy(input_filtered, incoming);


//    std::vector<char> buffer((
//            std::istreambuf_iterator<char>(incoming)),
//            (std::istreambuf_iterator<char>()));

////    std::cout << "AAA" << buffer.size() << std::endl;

//    boost::iostreams::stream<boost::iostreams::array_source> array_stream(&buffer[0], buffer.size());
//    boost::iostreams::stream<boost::iostreams::array_source> array_stream(&buffer[0], buffer.size());

//    boost::iostreams::stream<boost::iostreams::array_source> array_stream;
//    array_stream << buffer;

//    boost::iostreams::copy(buffer.begin(), buffer.end(), array_stream);

        return m_read_strategy->readOutputData(incoming);
//        return m_read_strategy->readOutputData(input_filtered);
//    return m_read_strategy->readOutputData(array_stream);
}


OutputData<double > *OutputDataReadStreamINT::readOutputData(std::istream &input_stream)
{
    OutputData<double > *result = new OutputData<double>;

    std::string line;

    while( std::getline(input_stream, line) )
    {
        if (line.find("axis") != std::string::npos) {
            IAxis *axis = OutputDataIOHelper::createAxis(input_stream);
            result->addAxis(*axis);
            delete axis;
        }

        if (line.find("data") != std::string::npos) {
            OutputDataIOHelper::fillOutputData(result, input_stream);
        }
    }

    return result;
}

