#include "OutputDataWriter.h"
#include <fstream>
#include <cassert>


void OutputDataWriter::writeOutputData(const OutputData<double > &data)
{
    // opening file
    std::ofstream fout;
    fout.open(m_file_name.c_str(), std::ios::out);
    if( !fout.is_open() ) {
        throw FileNotIsOpenException("OutputDataWriter::writeOutputData() -> Error. Can't open file '"+m_file_name+"' for writing.");
    }
    if ( !fout.good() ) {
        throw FileIsBadException("OutputDataReader::writeOutputData() -> Error! File is not good, probably it is a directory.");
    }

    assert(m_write_strategy != NULL);
    m_write_strategy->writeOutputData(data, fout);

    fout.close();
}



