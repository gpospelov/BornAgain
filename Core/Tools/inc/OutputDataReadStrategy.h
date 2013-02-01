#ifndef OUTPUTDATAREADSTRATEGY_H
#define OUTPUTDATAREADSTRATEGY_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   OutputDataReadStrategy.h
//! @brief  Definition of classes from OutputDataReadStrategy family
//! @author Scientific Computing Group at FRM II
//! @date   15.01.2013


#include "OutputData.h"
#include "Types.h"
#include <string>


//- -------------------------------------------------------------------
//! @class IOutputDataReadStrategy
//! @brief Define interface for reading strategy of OutputData from file
//- -------------------------------------------------------------------
class IOutputDataReadStrategy
{
public:
    IOutputDataReadStrategy(){}
    virtual ~IOutputDataReadStrategy(){}

    virtual OutputData<double > *readOutputData(std::istream &input_stream) = 0;
private:
};


//- -------------------------------------------------------------------
//! @class IOutputDataReadStrategyDecorator
//! @brief Interface for decoration of read strategies (e.g. gzip compression)
//- -------------------------------------------------------------------
class IOutputDataReadStrategyDecorator : public IOutputDataReadStrategy
{
public:
    IOutputDataReadStrategyDecorator(IOutputDataReadStrategy *read_strategy) : m_read_strategy(read_strategy) {}
    virtual ~IOutputDataReadStrategyDecorator() { delete m_read_strategy; }
protected:
    IOutputDataReadStrategy *m_read_strategy;
};


//- -------------------------------------------------------------------
//! @class OutputDataReadStreamGzip
//! @brief Decorator to read outputdata from zipped files
//- -------------------------------------------------------------------
class OutputDataReadStreamGZip : public IOutputDataReadStrategyDecorator
{
public:
    OutputDataReadStreamGZip(IOutputDataReadStrategy *read_strategy) : IOutputDataReadStrategyDecorator(read_strategy) { }
    virtual ~OutputDataReadStreamGZip() { }

    OutputData<double > *readOutputData(std::istream &file_stream);
};


//- -------------------------------------------------------------------
//! @class OutputDataReadStreamIMA
//! @brief Define strategy to read OutputData from IsGISAXS *.ima files
//! which contains 2D array in the form of [nX] lines of [nY] size
//- -------------------------------------------------------------------
class OutputDataReadStreamIMA : public IOutputDataReadStrategy
{
public:
    OutputData<double > *readOutputData(std::istream &file_stream);
};


//- -------------------------------------------------------------------
//! @class OutputDataReadStreamV1
//! @brief Define concrete strategy to read OutputData from ASCII file
//!  1d array for x-axis, 1d array for y-axis, 2d array for data expected
//- -------------------------------------------------------------------
class OutputDataReadStreamV1 : public IOutputDataReadStrategy
{
public:
    OutputData<double > *readOutputData(std::istream &file_stream);
};


#endif // OUTPUTDATAREADSTRATEGY_H
