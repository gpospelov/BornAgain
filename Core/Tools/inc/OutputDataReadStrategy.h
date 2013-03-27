// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/OutputDataReadStrategy.h
//! @brief     Defines IOutputDataReadStrategy and related classes.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef OUTPUTDATAREADSTRATEGY_H
#define OUTPUTDATAREADSTRATEGY_H

#include "OutputData.h"
#include "Types.h"
#include <string>

//! Interface for reading strategy of OutputData from file

class IOutputDataReadStrategy
{
 public:
    IOutputDataReadStrategy(){}
    virtual ~IOutputDataReadStrategy(){}

    virtual OutputData<double > *readOutputData(std::istream& input_stream) = 0;
 private:
};

//! Interface for decoration of read strategies (e.g. gzip compression)

class IOutputDataReadStrategyDecorator : public IOutputDataReadStrategy
{
 public:
    IOutputDataReadStrategyDecorator(IOutputDataReadStrategy *read_strategy) : m_read_strategy(read_strategy) {}
    virtual ~IOutputDataReadStrategyDecorator() { delete m_read_strategy; }
 protected:
    IOutputDataReadStrategy *m_read_strategy;
};

//! Decorator to read outputdata from zipped files

class OutputDataReadStreamGZip : public IOutputDataReadStrategyDecorator
{
 public:
    OutputDataReadStreamGZip(IOutputDataReadStrategy *read_strategy) : IOutputDataReadStrategyDecorator(read_strategy) { }
    virtual ~OutputDataReadStreamGZip() { }

    OutputData<double > *readOutputData(std::istream& file_stream);
};

//! Strategy to read OutputData from IsGISAXS *.ima files
//! which contains 2D array in the form of [nX] lines of [nY] size

class OutputDataReadStreamIMA : public IOutputDataReadStrategy
{
 public:
    OutputData<double > *readOutputData(std::istream& file_stream);
};

//! Strategy to read OutputData from ASCII file
//!  1d array for x-axis, 1d array for y-axis, 2d array for data expected

class OutputDataReadStreamV1 : public IOutputDataReadStrategy
{
 public:
    OutputData<double > *readOutputData(std::istream& file_stream);
};

#endif // OUTPUTDATAREADSTRATEGY_H
