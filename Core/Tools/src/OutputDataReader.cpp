#include "OutputDataReader.h"
#include <fstream>

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

    OutputData<double > *data = m_read_strategy->readOutputData(fin);
    fin.close();
    return data;
}

