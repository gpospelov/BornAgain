// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      InputOutput/OutputDataWriteStrategy.cpp
//! @brief     Implements class OutputDataWriteStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "OutputDataWriteStrategy.h"
#include "OutputData.h"
#include "TiffHandler.h"
#include "BornAgainNamespace.h"
#include <iostream>
#include <iomanip>


void OutputDataWriteINTStrategy::writeOutputData(const OutputData<double> &data,
                                               std::ostream &output_stream)
{
    output_stream << "# BornAgain Intensity Data" << std::endl;

    for(size_t i=0; i<data.getRank(); ++i) {
        const IAxis *axis = data.getAxis(i);
        output_stream << std::endl;
        output_stream << "# axis-" << i << std::endl;
        output_stream << (*axis) << std::endl;
    }
    size_t n_columns = data.getAxis(data.getRank()-1)->getSize();

    output_stream << std::endl;
    output_stream << "# data" << std::endl;
    OutputData<double>::const_iterator it = data.begin();
    size_t ncol(0);
    while(it != data.end()) {
        ncol++;
        double z_value = *it++;
        output_stream << std::scientific << std::setprecision(m_precision) << z_value << "    ";
        if(ncol == n_columns) {
            output_stream << std::endl;
            ncol = 0;
        }
    }
    output_stream << std::endl;

}

// ----------------------------------------------------------------------------

void OutputDataWriteNumpyTXTStrategy::writeOutputData(const OutputData<double> &data,
                                                      std::ostream &output_stream)
{
    if(data.getRank() != 2) {
        throw LogicErrorException("OutputDataWriteNumpyTXTStrategy::writeOutputData -> Error. "
                                  "Only 2-dim arrays supported");
    }

    output_stream << "# BornAgain Intensity Data" << std::endl;
    output_stream << "# Simple 2D array suitable for numpy, matlab etc." << std::endl;

    size_t nrows = data.getAxis(BornAgain::Y_AXIS_INDEX)->getSize();
    size_t ncols = data.getAxis(BornAgain::X_AXIS_INDEX)->getSize();

    output_stream << "# [nrows=" << nrows
                  << ", ncols=" << ncols << "]" << std::endl;

    std::vector<int> axes_indices(2);
    for(size_t row=0; row<nrows; ++row) {
        for(size_t col=0; col<ncols; ++col) {
            axes_indices[0] = col;
            axes_indices[1] = nrows - 1 - row;
            size_t global_index = data.toGlobalIndex(axes_indices);
            output_stream << std::scientific << std::setprecision(m_precision)
                          << data[global_index] << "    ";
        }
        output_stream << std::endl;
    }

}

// ----------------------------------------------------------------------------


#ifdef BORNAGAIN_TIFF_SUPPORT

OutputDataWriteTiffStrategy::OutputDataWriteTiffStrategy()
    : m_d(new TiffHandler)
{

}

OutputDataWriteTiffStrategy::~OutputDataWriteTiffStrategy()
{
    delete m_d;
}

void OutputDataWriteTiffStrategy::writeOutputData(const OutputData<double> &data,
                                                  std::ostream &output_stream)
{
    m_d->write(data, output_stream);
}

#endif



