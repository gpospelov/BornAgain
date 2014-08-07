// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/src/OutputDataReadStrategy.cpp
//! @brief     Implements class OutputDataReadStrategy.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "OutputDataReadStrategy.h"
#include "Types.h"
#include "Exceptions.h"
#include "Utils.h"
#include "BornAgainNamespace.h"
#include "OutputData.h"
#include "OutputDataIOHelper.h"
#include "AxisDouble.h"

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
    std::istream incoming(&input_filtered);
    return m_read_strategy->readOutputData(incoming);
}

/* ************************************************************************* */
// read data from ASCII file (2D assumed) and fill newly created OutputData with it
/* ************************************************************************* */
OutputData<double > *OutputDataReadStreamIMA::readOutputData(std::istream &input_stream)
{
    std::string sline;
    vdouble2d_t buff_2d;
    // reading file line by line, every line is parsed into vector of double, so at the end we have buffer_2d of doubles

    while( std::getline(input_stream, sline))
    {
        //std::string str = Utils::String::round_doubles(sline, 10);
        //vdouble1d_t buff = Utils::String::parse_doubles(str);
        vdouble1d_t buff = Utils::String::parse_doubles(sline);

        buff_2d.push_back(buff);
    }

    // creating new OutputData and filling it with values from buffer_2d
//    int y_size = (int)buff_2d.size();
//    int x_size = buff_2d.size() ? (int)buff_2d[0].size() : 0;
    int x_size = (int)buff_2d.size();
    int y_size = buff_2d.size() ? (int)buff_2d[0].size() : 0;
    if(x_size==0 || y_size==0) {
        std::stringstream ostr;
        ostr << "OutputDataReadStreamIMA::readOutputData() -> Error. Zero x_size: "
             << x_size << " or y_size: " << y_size;
        throw LogicErrorException(ostr.str());
    }

    OutputData<double> *p_result = new OutputData<double>;
//    p_result->addAxis(NDetector2d::PHI_AXIS_NAME, x_size, 0.0, double(x_size));
//    p_result->addAxis(NDetector2d::ALPHA_AXIS_NAME, y_size, 0.0, double(y_size));
    p_result->addAxis(BornAgain::PHI_AXIS_NAME, x_size, 0.0, double(x_size));
    p_result->addAxis(BornAgain::ALPHA_AXIS_NAME, y_size, 0.0, double(y_size));
    p_result->setAllTo(0.0);

    OutputData<double>::iterator it = p_result->begin();
    while (it != p_result->end())
    {
        size_t index_x = p_result->toCoordinates(it.getIndex())[0];
        size_t index_y = p_result->toCoordinates(it.getIndex())[1];
        *it = buff_2d[index_x][index_y];
        ++it;
    }

    return p_result;
}

/* ************************************************************************* */
// parsing stream of double's into OutputData object
// '#' - comments (not treated)
// ' ' - delimeter between double's
// Each line is 1D array (or 1D slice of 2D array
// Expected:
// line representing x bins [nX]
// line representing y bins [nY]
// [nX] lines of [nY] size representing data itself
/* ************************************************************************* */
OutputData<double > *OutputDataReadStreamV1::readOutputData(std::istream &input_stream)
{
    std::string sline;
    vdouble1d_t buff_xaxis, buff_yaxis;
    vdouble2d_t buff_data; // [x][y]

    while( std::getline(input_stream, sline) )
    {
        if(sline[0] == '#') continue;
        //std::string str = Utils::String::round_doubles(sline, 10);
        vdouble1d_t buff = Utils::String::parse_doubles(sline);

        if( buff_xaxis.empty() ) {
            buff_xaxis = buff;
        } else if( buff_yaxis.empty() ) {
            buff_yaxis = buff;
        } else {
            buff_data.push_back(buff);
        }
    }

    // check consistency of x dimension and data buffer
    if( buff_data.size() != buff_xaxis.size()) {
        throw LogicErrorException("OutputDataReadASCII::readOutputData() -> Error. Unconsistent x-size.");
    }
    // check consistency of y dimension and data buffer
    for(size_t i = 0; i<buff_xaxis.size(); ++i) {
        if( buff_data[i].size() != buff_yaxis.size()) {
            throw LogicErrorException("OutputDataReadASCII::readOutputData() -> Error. Unconsistent y-size.");
        }
    }

    // creating output data
//    AxisDouble xaxis(NDetector2d::PHI_AXIS_NAME);
    AxisDouble xaxis(BornAgain::PHI_AXIS_NAME);
    for(size_t i=0; i<buff_xaxis.size(); ++i) xaxis.push_back(buff_xaxis[i]);
//    AxisDouble yaxis(NDetector2d::ALPHA_AXIS_NAME);
    AxisDouble yaxis(BornAgain::ALPHA_AXIS_NAME);
    for(size_t i=0; i<buff_yaxis.size(); ++i) yaxis.push_back(buff_yaxis[i]);

    OutputData<double > *p_result = new OutputData<double>;
    p_result->addAxis(xaxis);
    p_result->addAxis(yaxis);
    p_result->setAllTo(0.0);
    OutputData<double>::iterator it = p_result->begin();
    while (it != p_result->end())
    {
        size_t index_x = p_result->toCoordinates(it.getIndex())[0];
        size_t index_y = p_result->toCoordinates(it.getIndex())[1];
        *it = buff_data[index_x][index_y];
        ++it;
    }
    return p_result;
}


OutputData<double > *OutputDataReadStreamBA::readOutputData(std::istream &input_stream)
{
    OutputData<double > *result = new OutputData<double>;

    std::string line;

    while( std::getline(input_stream, line) )
    {
        if (line.find("axis") != std::string::npos) {
            IAxis *axis = OutputDataIOHelper::createAxis(input_stream);
            result->addAxis(*axis);
        }

        if (line.find("data") != std::string::npos) {
            OutputDataIOHelper::fillOutputData(result, input_stream);
        }
    }

    return result;
}

