// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/src/OutputDataReader.cpp
//! @brief     Implements class OutputDataReader.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "OutputDataReader.h"
#include <fstream>
#include <cassert>
#include <iostream>

OutputData<double > *OutputDataReader::getOutputData()
{
    if(!m_read_strategy) {
        throw NullPointerException("OutputDataReader::getOutputData() -> Error! No read strategy defined");
    }

    // opening file
    std::ifstream fin;

    std::ios_base::openmode openmode = std::ios::in;
    if(m_read_strategy->isBinary()) openmode = std::ios::in | std::ios_base::binary;

    fin.open(m_file_name.c_str(), openmode );
    if( !fin.is_open() ) {
        throw FileNotIsOpenException("OutputDataReader::getOutputData() -> Error. Can't open file '"+m_file_name+"' for reading.");
    }
    if ( !fin.good() ) {
        throw FileIsBadException("OutputDataReader::getOutputData() -> Error! File is not good, probably it is a directory.");
    }

    OutputData<double > *result = m_read_strategy->readOutputData(fin);
    fin.close();

    return result;
}


