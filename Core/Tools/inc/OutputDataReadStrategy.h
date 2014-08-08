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

#include <string>
#include "WinDllMacros.h"
template <class T> class OutputData;


//! @class IOutputDataReadStrategy
//! @ingroup tools_internal
//! @brief Interface for reading strategy of OutputData from file

class BA_CORE_API_ IOutputDataReadStrategy
{
public:
    IOutputDataReadStrategy(){}
    virtual ~IOutputDataReadStrategy(){}

    virtual OutputData<double > *readOutputData(std::istream& input_stream) = 0;

    //! returns true if strategy needs binary stream
    virtual bool isBinary() { return false; }
private:
};


//! @class IOutputDataReadStrategyDecorator
//! @ingroup tools_internal
//! @brief Interface for decoration of read strategies (e.g. gzip compression)

class BA_CORE_API_ IOutputDataReadStrategyDecorator : public IOutputDataReadStrategy
{
public:
    IOutputDataReadStrategyDecorator(IOutputDataReadStrategy *read_strategy) : m_read_strategy(read_strategy) {}
    virtual ~IOutputDataReadStrategyDecorator() { delete m_read_strategy; }
protected:
    IOutputDataReadStrategy *m_read_strategy;
};


//! @class OutputDataReadStreamGZip
//! @ingroup tools_internal
//! @brief Decorator to read outputdata from zipped files

class BA_CORE_API_ OutputDataReadStreamGZip : public IOutputDataReadStrategyDecorator
{
public:
    OutputDataReadStreamGZip(IOutputDataReadStrategy *read_strategy) : IOutputDataReadStrategyDecorator(read_strategy) { }
    virtual ~OutputDataReadStreamGZip() { }

    virtual bool isBinary() { return true; }

    OutputData<double > *readOutputData(std::istream& file_stream);
};


//! @class OutputDataReadStreamIMA
//! @ingroup tools_internal
//! @brief Strategy to read OutputData from IsGISAXS *.ima files
//! which contains 2D array in the form of [nX] lines of [nY] size

//class BA_CORE_API_ OutputDataReadStreamIMA : public IOutputDataReadStrategy
//{
//public:
//    OutputData<double > *readOutputData(std::istream& file_stream);
//};

////! Strategy to read OutputData from ASCII file
////!  1d array for x-axis, 1d array for y-axis, 2d array for data expected

//class OutputDataReadStreamV1 : public IOutputDataReadStrategy
//{
//public:
//    OutputData<double > *readOutputData(std::istream& file_stream);
//};

//! Strategy to read BornAgain native IntensityData from ASCII file

class OutputDataReadStreamBA : public IOutputDataReadStrategy
{
public:
    OutputData<double > *readOutputData(std::istream& file_stream);
};


#endif // OUTPUTDATAREADSTRATEGY_H


