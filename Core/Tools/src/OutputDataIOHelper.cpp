#include "OutputDataIOHelper.h"
#include "FixedBinAxis.h"
#include "Exceptions.h"
#include "Utils.h"
#include "OutputData.h"
#include <iostream>
#include <algorithm>
#include <boost/algorithm/string.hpp>

IAxis *OutputDataIOHelper::createAxis(std::istream &input_stream)
{
    std::string line;
    std::getline(input_stream, line);

    if(line.find(FixedBinAxisType) != std::string::npos)
    {
        return createFixedBinAxis(line);
    }
    else {
        throw Exceptions::LogicErrorException("OutputDataIOHelper::createAxis() -> Error. Unknown axis '"+line+"'");
    }
}


// FixedBinAxis("axis0", 10, -1, 1)
FixedBinAxis *OutputDataIOHelper::createFixedBinAxis(std::string line)
{
    boost::replace_all(line, FixedBinAxisType, "");
    boost::replace_all(line, ",", " ");
    boost::replace_all(line, "\"", " ");
    boost::replace_all(line, "(", " ");
    boost::replace_all(line, ")", " ");

    std::string name;
    int nbins(0);
    double start(0), end(0);

    std::istringstream iss(line);
    if( !(iss >> name >> nbins >> start >> end) )
        throw Exceptions::FormatErrorException("OutputDataIOHelper::createFixedBinAxis() -> Error. Can't parse the string.");

    std::cout << line << " " << name << " " << nbins << " " << start << " " << end << std::endl;
    FixedBinAxis *result = new FixedBinAxis(name, nbins, start, end);
    return result;
}




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
}
