// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/OutputDataIOFactory.h
//! @brief     Defines class OutputDataIOFactory.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef OUTPUTDATAIOHELPER_H
#define OUTPUTDATAIOHELPER_H

#include<string>
#include <iostream>

class IAxis;
class FixedBinAxis;
template <class T> class OutputData;

namespace OutputDataIOHelper {

const std::string FixedBinAxisType = "FixedBinAxis";

IAxis *createAxis(std::istream &input_stream);
FixedBinAxis *createFixedBinAxis(std::string line);

void fillOutputData(OutputData<double> *data, std::istream &input_stream);

}


#endif
