// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/src/OutputDataWriteStrategy.cpp
//! @brief     Implements class OutputDataWriteStrategy.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "OutputDataWriteStrategy.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cassert>

// write OutputData to IsGisaxs *.ima files

void OutputDataWriteStreamIMA::writeOutputData(const OutputData<double>& data, std::ostream& output_stream)
{
    size_t row_length = data.getAxis(1)->getSize();
    OutputData<double>::const_iterator it = data.begin();
    while(it != data.end()) {
        double z_value = *it++;
        output_stream << std::scientific << std::setprecision(m_precision) << z_value << "    ";
        if(it.getIndex()%row_length==0) output_stream << std::endl;
    }
}


// write OutputData to ascii files
// '#' - comments (not treated)
// ' ' - delimeter between double's
// Each line is 1D array (or 1D slice of 2D array)
// Records:
// line representing x bins [nX]
// line representing y bins [nY]
// [nX] lines of [nY] size representing data itself
void OutputDataWriteStreamV1::writeOutputData(const OutputData<double> &data, std::ostream &output_stream)
{
    assert(data.getRank() == 2);

    output_stream << "# 2D scattering data" << std::endl;
    output_stream << "# shape " << data.getAxis(0)->getSize() << " " << data.getAxis(1)->getSize() << std::endl;

    // writing x and y axis

    for(size_t i_dim=0; i_dim<data.getRank(); ++i_dim) {
        (i_dim == 0 ? output_stream << "# 0-axis [phi]" : output_stream << "# 1-axis [theta]");
        output_stream << std::endl;
        for(size_t i_bin=0; i_bin<data.getAxis(i_dim)->getSize(); ++i_bin) {
            output_stream << std::scientific << std::setprecision(m_precision) << (*data.getAxis(i_dim))[i_bin] << "    ";
        }
        output_stream << std::endl;
    }

    output_stream << "# data" << std::endl;
    size_t row_length = data.getAxis(1)->getSize();
    OutputData<double>::const_iterator it = data.begin();
    while(it != data.end()) {
        double z_value = *it++;
        output_stream << std::scientific << std::setprecision(m_precision) << z_value << "    ";
        if(it.getIndex()%row_length==0) output_stream << std::endl;
    }
}



