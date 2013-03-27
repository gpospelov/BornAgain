// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/src/OutputDataWriteStrategy.cpp
//! @brief     Implements OutputDataWriteStreamIMA::writeOutputData.
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

//! Read data from ASCII file (2D assumed) into newly created OutputData.

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
