#ifndef OUTPUTDATAREADER_H
#define OUTPUTDATAREADER_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   OutputDataReader.h
//! @brief  Definition of OutputDataReader class
//! @author Scientific Computing Group at FRM II
//! @date   01.10.2012

#include "OutputData.h"
#include "OutputDataReadStrategy.h"
#include "Types.h"
#include <string>


//- -------------------------------------------------------------------
//! @class OutputDataReader
//! @brief Reads OutputData from file using different reading strategies
//- -------------------------------------------------------------------
class OutputDataReader
{
public:
    OutputDataReader() : m_read_strategy(0) {}
    OutputDataReader(const std::string &file_name) : m_file_name(file_name), m_read_strategy(0) {}
    OutputDataReader(IOutputDataReadStrategy *read_strategy) : m_read_strategy(read_strategy) {}
    virtual ~OutputDataReader() { delete m_read_strategy; }

    //! read output data from file (file name was set already from OutputDataIOFactory)
//    OutputData<double > *getOutputData() { return getOutputData(m_file_name); }
    OutputData<double > *getOutputData();

    //! set concrete reading strategy
    void setStrategy(IOutputDataReadStrategy *read_strategy) { delete m_read_strategy; m_read_strategy = read_strategy; }

private:
//    //! read output data from file
//    OutputData<double > *getOutputData(const std::string &file_name);

    std::string m_file_name;
    IOutputDataReadStrategy *m_read_strategy;
};




#endif // OUTPUTDATAREADER_H
