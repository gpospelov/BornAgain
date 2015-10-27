// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      InputOutput/OutputDataReadStrategy.cpp
//! @brief     Implements class OutputDataReadStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "OutputDataReadStrategy.h"
#include "Types.h"
#include "Exceptions.h"
#include "Utils.h"
#include "BornAgainNamespace.h"
#include "OutputData.h"
#include "OutputDataIOHelper.h"
#include "TiffHandler.h"
#include <fstream>

OutputData<double > *OutputDataReadINTStrategy::readOutputData(std::istream &input_stream)
{
    OutputData<double > *result = new OutputData<double>;

    std::string line;

    while( std::getline(input_stream, line) )
    {
        if (line.find("axis") != std::string::npos) {
            IAxis *axis = OutputDataIOHelper::createAxis(input_stream);
            result->addAxis(*axis);
            delete axis;
        }

        if (line.find("data") != std::string::npos) {
            OutputDataIOHelper::fillOutputData(result, input_stream);
        }
    }

    return result;
}

// ----------------------------------------------------------------------------

#ifdef BORNAGAIN_TIFF_SUPPORT
OutputDataReadTiffStrategy::OutputDataReadTiffStrategy()
    : m_d(new TiffHandler)
{

}

OutputDataReadTiffStrategy::~OutputDataReadTiffStrategy()
{
    delete m_d;
}

OutputData<double> *OutputDataReadTiffStrategy::readOutputData(std::istream &input_stream)
{
    m_d->read(input_stream);
    return m_d->getOutputData()->clone();
}

#endif // BORNAGAIN_TIFF_SUPPORT
