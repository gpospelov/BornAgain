// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/src/OutputDataWriter.cpp
//! @brief     Implements class OutputDataWriter.
//!
//! @homepage  apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

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
