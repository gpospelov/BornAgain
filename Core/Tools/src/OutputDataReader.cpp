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

OutputData<double > *OutputDataReader::getOutputData()
{
    // opening file
    std::ifstream fin;
    fin.open(m_file_name.c_str(), std::ios::in);
    if( !fin.is_open() ) {
        throw FileNotIsOpenException("OutputDataReader::getOutputData() -> Error. Can't open file '"+m_file_name+"' for reading.");
    }
    if ( !fin.good() ) {
        throw FileIsBadException("OutputDataReader::getOutputData() -> Error! File is not good, probably it is a directory.");
    }

    assert(m_read_strategy != NULL);
    OutputData<double > *data = m_read_strategy->readOutputData(fin);
    fin.close();
    return data;
}


