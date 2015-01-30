// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/OutputDataIOFactory.h
//! @brief     Defines class OutputDataIOFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef OUTPUTDATAIOHELPER_H
#define OUTPUTDATAIOHELPER_H


#include "WinDllMacros.h"
#include<string>
#include <iostream>

class IAxis;
template <class T> class OutputData;

namespace OutputDataIOHelper {

const std::string FixedBinAxisType = "FixedBinAxis";
const std::string VariableBinAxisType = "VariableBinAxis";
const std::string ConstKBinAxisType = "ConstKBinAxis";
const std::string CustomBinAxisType = "CustomBinAxis";

BA_CORE_API_ bool isSimilarToFixedBinAxisType(const std::string &line);
BA_CORE_API_ bool isVariableBinAxisType(const std::string &line);

BA_CORE_API_ IAxis *createAxis(std::istream &input_stream);
BA_CORE_API_ IAxis *createFixedBinAxis(std::string line);
BA_CORE_API_ IAxis *createVariableBinAxis(std::string line);

BA_CORE_API_ void fillOutputData(OutputData<double> *data, std::istream &input_stream);

}


#endif
