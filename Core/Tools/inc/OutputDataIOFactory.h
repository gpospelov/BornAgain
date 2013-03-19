// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @copyright Forschungszentrum Jülich GmbH 2013
//             
//  Homepage:  apps.jcns.fz-juelich.de/BornAgain
//  License:   GNU General Public License v3 or higher (see COPYING)
//
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
//! @file      Tools/OutputDataIOFactory.h 
//! @brief     Defines class OutputDataIOFactory.
//
// ************************************************************************** //

#ifndef OUTPUTDATAIOFACTORY_H
#define OUTPUTDATAIOFACTORY_H

#include "OutputDataReader.h"
#include "OutputDataWriter.h"
#include <string>
#include <boost/shared_ptr.hpp>

//! Reads OutputData from files in different format

class OutputDataIOFactory
{
public:
    typedef boost::shared_ptr<OutputDataReader > OutputDataReader_t;
    typedef boost::shared_ptr<OutputDataWriter > OutputDataWriter_t;

    OutputDataIOFactory();

    static OutputData<double > *getOutputData(const std::string &file_name);
    static OutputDataReader_t getReader(const std::string &file_name);

    static void writeOutputData(const OutputData<double> &data, const std::string &file_name);
    static OutputDataWriter_t getWriter(const std::string &file_name);
};

#endif // OUTPUTDATAIOFACTORY_H
