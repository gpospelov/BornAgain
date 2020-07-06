// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/InputOutput/OutputDataReadFactory.h
//! @brief     Defines class OutputDataReadFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef OUTPUTDATAREADFACTORY_H
#define OUTPUTDATAREADFACTORY_H

#include "Core/InputOutput/OutputDataReader.h"

//! Creates reader appropariate for given type of files.
//! @ingroup input_output_internal

class BA_CORE_API_ OutputDataReadFactory
{
public:
    static OutputDataReader* getReader(const std::string& file_name);
    static OutputDataReader* getReflectometryReader(const std::string& file_name);

private:
    static IOutputDataReadStrategy* getReadStrategy(const std::string& file_name);
};

#endif // OUTPUTDATAREADFACTORY_H
