// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/src/OutputDataIOHelper.cpp
//! @brief     Implements class OutputDataIOHelper.
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "OutputDataIOHelper.h"
#include "FixedBinAxis.h"
#include "VariableBinAxis.h"
#include "ConstKBinAxis.h"
#include "CustomBinAxis.h"
#include "Exceptions.h"
#include "Utils.h"
#include "OutputData.h"
#include <iostream>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/assign/list_of.hpp>


//! Returns true if string representation of the axis contains one of
//! FixedBinAxis, ConstKBinAxis or CustomBinAxis to parse it later in
//! similar way.
bool OutputDataIOHelper::isSimilarToFixedBinAxisType(const std::string &line)
{
    if(line.find(FixedBinAxisType) != std::string::npos ||
       line.find(ConstKBinAxisType) != std::string::npos ||
       line.find(CustomBinAxisType) != std::string::npos)
    {
        return true;
    }
    return false;
}


bool OutputDataIOHelper::isVariableBinAxisType(const std::string &line)
{
    if(line.find(VariableBinAxisType) != std::string::npos) {
        return true;
    } else {
        return false;
    }
}



//! Creates axis of certain type from input stream
IAxis *OutputDataIOHelper::createAxis(std::istream &input_stream)
{
    std::string line;
    std::getline(input_stream, line);

    if(isSimilarToFixedBinAxisType(line))
    {
        return createFixedBinAxis(line);
    }
    else if(isVariableBinAxisType(line))
    {
        return createVariableBinAxis(line);
    }
    else {
        throw Exceptions::LogicErrorException("OutputDataIOHelper::createAxis() -> Error. Unknown axis '"+line+"'");
    }
}


//! Create one of FixedBinAxis from string representation
//! FixedBinAxis("axis0", 10, -1, 1)
//! ConstKBinAxis("axis0", 10, -1, 1)
//! CustomBinAxis("axis0", 10, -1, 1)
IAxis *OutputDataIOHelper::createFixedBinAxis(std::string line)
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

    if(type == FixedBinAxisType) {
        return new FixedBinAxis(name, nbins, boundaries[0], boundaries[1]);
    }
    else if(type == ConstKBinAxisType) {
        return new ConstKBinAxis(name, nbins, boundaries[0], boundaries[1]);
    }
    else if(type == CustomBinAxisType) {
        return new CustomBinAxis(name, nbins, boundaries[0], boundaries[1]);
    }
    else {
        throw Exceptions::LogicErrorException("OutputDataIOHelper::createOneOfFixedBinAxis() -> Error. Unexpected place.");
    }
}


//! Create VariableBinAxis from string representation
//! VariableBinAxis("axis0", 4, [-1, -0.5, 0.5, 1, 2])
IAxis *OutputDataIOHelper::createVariableBinAxis(std::string line)
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




