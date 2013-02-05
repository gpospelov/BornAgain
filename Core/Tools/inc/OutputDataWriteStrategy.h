#ifndef OUTPUTDATAWRITESTRATEGY_H
#define OUTPUTDATAWRITESTRATEGY_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   OutputDataWriteStrategy.h
//! @brief  Definition of classes from OutputDataWriteStrategy family
//! @author Scientific Computing Group at FRM II
//! @date   15.01.2013


#include "OutputData.h"
#include "Types.h"
#include <string>


//- -------------------------------------------------------------------
//! @class IOutputDataWriteStrategy
//! @brief Define strategy interface to write OututData in file
//- -------------------------------------------------------------------
class IOutputDataWriteStrategy
{
public:
    IOutputDataWriteStrategy() : m_precision(10) {}
    virtual ~IOutputDataWriteStrategy(){}

    virtual void writeOutputData(const OutputData<double> &data, std::ostream &output_stream) = 0;
protected:
    int m_precision;
};


//- -------------------------------------------------------------------
//! @class OutputDataWriteStreamIMA
//! @brief Define strategy to write OutputData to IsGisaxs *.ima files
//- -------------------------------------------------------------------
class OutputDataWriteStreamIMA : public IOutputDataWriteStrategy
{
public:
    virtual void writeOutputData(const OutputData<double> &data, std::ostream &output_stream);
};



#endif // OUTPUTDATAWRITESTRATEGY_H
