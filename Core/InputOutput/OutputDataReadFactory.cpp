// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      InputOutput/OutputDataReadFactory.cpp
//! @brief     Implements class OutputDataReadFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "OutputDataReadFactory.h"
#include "OutputDataReader.h"
#include "OutputDataReadStrategy.h"
#include "OutputDataIOHelper.h"
#include "Exceptions.h"
#include "FileSystem.h"


OutputDataReader *OutputDataReadFactory::getReader(const std::string &file_name)
{
    OutputDataReader *result = new OutputDataReader(file_name);

    result->setStrategy(getReadStrategy(file_name));
    return result;
}

IOutputDataReadStrategy *OutputDataReadFactory::getReadStrategy(const std::string &file_name)
{
    IOutputDataReadStrategy *result(0);
    if(OutputDataIOHelper::isIntFile(file_name)) {
        result = new OutputDataReadINTStrategy();
    }
    else if(OutputDataIOHelper::isTxtFile(file_name)) {
        result = new OutputDataReadNumpyTXTStrategy();
    }
#ifdef BORNAGAIN_TIFF_SUPPORT
    else if(OutputDataIOHelper::isTiffFile(file_name)) {
       result = new OutputDataReadTiffStrategy();
    }
#endif // BORNAGAIN_TIFF_SUPPORT
    else {
        throw LogicErrorException("OutputDataReadFactory::getReader() -> Error. "
                "Don't know how to read file '" + file_name+std::string("'"));
    }
    return result;
}
