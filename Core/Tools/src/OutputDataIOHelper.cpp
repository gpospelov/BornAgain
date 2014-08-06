#include "OutputDataIOHelper.h"
#include "FixedBinAxis.h"
#include "VariableBinAxis.h"
#include "Exceptions.h"
#include "Utils.h"
#include "OutputData.h"
#include <iostream>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/assign/list_of.hpp>

//! Creates axis of certain type from input stream
IAxis *OutputDataIOHelper::createAxis(std::istream &input_stream)
{
    std::string line;
    std::getline(input_stream, line);

    if(line.find(FixedBinAxisType) != std::string::npos)
    {
        return createFixedBinAxis(line);
    }
    else if(line.find(VariableBinAxisType) != std::string::npos)
    {
        return createVariableBinAxis(line);
    }
    else {
        throw Exceptions::LogicErrorException("OutputDataIOHelper::createAxis() -> Error. Unknown axis '"+line+"'");
    }
}


//! Create FixedBinAxis from string representation
//! FixedBinAxis("axis0", 10, -1, 1)
FixedBinAxis *OutputDataIOHelper::createFixedBinAxis(std::string line)
{
    std::vector<std::string> to_replace = boost::assign::list_of(",")("\"")("(")(")");
    Utils::String::replaceItemsFromString(line, to_replace, " ");

    std::string type, name;
    size_t nbins(0);

    std::istringstream iss(line);
    if( !(iss >> type >> name >> nbins) )
        throw Exceptions::FormatErrorException("OutputDataIOHelper::createFixedBinAxis() -> Error. Can't parse the string.");

    std::vector<double> boundaries;
    std::string value;
    while( iss >> value) {
        boundaries.push_back(std::strtod(value.c_str(), NULL));
    }

    if(boundaries.size() != 2)
        throw Exceptions::FormatErrorException("OutputDataIOHelper::createFixedBinAxis() -> Error. Can't parse the string at p2.");

    return new FixedBinAxis(name, nbins, boundaries[0], boundaries[1]);
}


//! Create VariableBinAxis from string representation
//! VariableBinAxis("axis0", 4, [-1, -0.5, 0.5, 1, 2])
VariableBinAxis *OutputDataIOHelper::createVariableBinAxis(std::string line)
{
    std::vector<std::string> to_replace = boost::assign::list_of(",")("\"")("(")(")")("[")("]");
    Utils::String::replaceItemsFromString(line, to_replace, " ");

    std::string type, name;
    size_t nbins(0);

    std::istringstream iss(line);
    if( !(iss >> type >> name >> nbins) )
        throw Exceptions::FormatErrorException("OutputDataIOHelper::createVariableBinAxis() -> Error. Can't parse the string.");

    std::vector<double> boundaries;
    std::string value;
    while( iss >> value) {
        boundaries.push_back(std::strtod(value.c_str(), NULL));
    }

    if(boundaries.size() != nbins+1)
        throw Exceptions::FormatErrorException("OutputDataIOHelper::createVariableBinAxis() -> Error. Can't parse the string at p2.");

    return new VariableBinAxis(name, nbins, boundaries);
}


//! Fills output data raw buffer from input stream
void OutputDataIOHelper::fillOutputData(OutputData<double> *data, std::istream &input_stream)
{
    std::string line;

    data->setAllTo(0.0);
    OutputData<double>::iterator it = data->begin();

    while( std::getline(input_stream, line) )
    {
        if(line.empty() || line[0] == '#') break;

        std::istringstream iss(line);
        std::string svalue;
        while(iss >> svalue) {
            *it = std::strtod(svalue.c_str(), NULL);
            ++it;
        }
    }

    if(it!= data->end())
        throw Exceptions::FormatErrorException("OutputDataIOHelper::fillOutputData() -> Error while parsing data.");
}
