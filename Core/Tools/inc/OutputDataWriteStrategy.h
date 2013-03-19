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
//! @file      Tools/OutputDataWriteStrategy.h 
//! @brief     Defines classes OutputDataWriteStrategy and OutputDataWriteStreamIMA.
//
// ************************************************************************** //

#ifndef OUTPUTDATAWRITESTRATEGY_H
#define OUTPUTDATAWRITESTRATEGY_H

#include "OutputData.h"
#include "Types.h"
#include <string>

//! Strategy interface to write OututData in file

class IOutputDataWriteStrategy
{
public:
    IOutputDataWriteStrategy() : m_precision(10) {}
    virtual ~IOutputDataWriteStrategy(){}

    virtual void writeOutputData(const OutputData<double> &data, std::ostream &output_stream) = 0;
protected:
    int m_precision;
};

//! Strategy to write OutputData to IsGisaxs *.ima files

class OutputDataWriteStreamIMA : public IOutputDataWriteStrategy
{
public:
    virtual void writeOutputData(const OutputData<double> &data, std::ostream &output_stream);
};

#endif // OUTPUTDATAWRITESTRATEGY_H
