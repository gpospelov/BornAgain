#include "OutputDataReader.h"
#include "Types.h"
#include "Exceptions.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <iomanip>
#include <cmath>
#include <algorithm>

#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>


OutputData<double > *OutputDataReader::getOutputData(const std::string &file_name)
{
    // opening file
    std::ifstream fin;
    fin.open(file_name.c_str(), std::ios::in);
    if( !fin.is_open() ) {
        throw FileNotIsOpenException("OutputDataReader::getOutputData() -> Error. Can't open file '"+file_name+"' for reading.");
    }
    if ( !fin.good() ) {
        throw FileIsBadException("OutputDataReader::getOutputData() -> Error! File is not good, probably it is a directory.");
    }

    OutputData<double > *data = m_reader->readOutputData(fin);
    fin.close();
    return data;
}


/* ************************************************************************* */
// decorator to unzip stream
/* ************************************************************************* */
OutputData<double > *OutputDataReadStreamGZip::readOutputData(std::istream &input_stream)
{
    boost::iostreams::filtering_streambuf<boost::iostreams::input> input_filtered;
    input_filtered.push(boost::iostreams::gzip_decompressor());
    input_filtered.push(input_stream);
    std::istream incoming(&input_filtered);
    return m_reader->readOutputData(incoming);
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
    vdouble2d_t buff_data; // [y][x]

    while( std::getline(input_stream, sline) )
    {
        if(sline[0] == '#') continue;
        std::string str = round_doubles(sline, 10);
        vdouble1d_t buff = parse_doubles(str);

        if( buff_xaxis.empty() ) {
            buff_xaxis = buff;
        } else if( buff_yaxis.empty() ) {
            buff_yaxis = buff;
        } else {
            buff_data.push_back(buff);
        }
    }

    // check consistency of y dimension and data buffer
    if( buff_data.size() != buff_yaxis.size()) {
        throw LogicErrorException("OutputDataReadASCII::readOutputData() -> Error. Unconsistent y-size.");
    }
    // check consistency of x dimension and data buffer
    for(size_t i = 0; i<buff_yaxis.size(); ++i) {
        if( buff_data[i].size() != buff_xaxis.size()) {
            throw LogicErrorException("OutputDataReadASCII::readOutputData() -> Error. Unconsistent x-size.");
        }
    }

    // creating output data
    AxisDouble xaxis("x-axis");
    for(size_t i=0; i<buff_xaxis.size(); ++i) xaxis.push_back(buff_xaxis[i]);
    AxisDouble yaxis("y-axis");
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
        *it = buff_data[index_y][index_x];
        ++it;
    }
    return p_result;
}


/* ************************************************************************* */
// double numbers in string will be rounded according to the precision
// if precision is 6, then 7.2908527770e+03 -> 7.290853e+03
// (this method is used to compare IsGisaxs and our ASCII files at equal precision)
/* ************************************************************************* */
std::string OutputDataReadStreamV1::round_doubles(const std::string &str, int precision)
{
    std::string newline;
    std::istringstream is0(str.c_str());
    double number;
    while( is0 >> number ) {
        std::ostringstream os;
        os << std::scientific << std::setprecision(precision) << number;
        newline += os.str() + std::string("    ");
    }
    return newline;
}


/* ************************************************************************* */
// parse double values from string to vector of double
/* ************************************************************************* */
vdouble1d_t OutputDataReadStreamV1::parse_doubles(const std::string &str)
{
    vdouble1d_t buff_1d;
    std::istringstream iss(str);
    std::copy(std::istream_iterator<double>(iss), std::istream_iterator<double>(), back_inserter(buff_1d));
    if( buff_1d.empty() ) {
        std::cout << "OutputDataReadFileASCII::parse_doubles() -> Warning! No parsed values in 1d vector of doubles." << std::endl;
    }
    return buff_1d;
}


