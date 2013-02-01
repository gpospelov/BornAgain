#ifndef OUTPUTDATAWRITER_H
#define OUTPUTDATAWRITER_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   OutputDataWrite.h
//! @brief  Definition of OutputDataWriter class
//! @author Scientific Computing Group at FRM II
//! @date   15.01.2013

#include "OutputData.h"
#include "OutputDataWriteStrategy.h"
#include "Types.h"
#include <string>


//- -------------------------------------------------------------------
//! @class OutputDataWriter
//! @brief Write OutputData to file using different witing strategies
//- -------------------------------------------------------------------
class OutputDataWriter
{
public:
    OutputDataWriter() : m_write_strategy(0) {}
    OutputDataWriter(const std::string &file_name) : m_file_name(file_name), m_write_strategy(0) {}
    OutputDataWriter(IOutputDataWriteStrategy *write_strategy) : m_write_strategy(write_strategy) {}
    virtual ~OutputDataWriter() { delete m_write_strategy; }

    //! write output data to file
    void writeOutputData(const OutputData<double > &data);

    //! set concrete writing strategy
    void setStrategy(IOutputDataWriteStrategy *write_strategy) { delete m_write_strategy; m_write_strategy = write_strategy; }

private:
    std::string m_file_name;
    IOutputDataWriteStrategy *m_write_strategy;
};



#endif // OUTPUTDATAWRITER_H
