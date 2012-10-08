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
//! @brief  Definition of classes from OutputDataReader family
//! @author Scientific Computing Group at FRM II
//! @date   01.10.2012


#include "OutputData.h"
#include "Types.h"
#include <string>


//- -------------------------------------------------------------------
//! @class IOutputDataReadStrategy
//! @brief Define interface for reading OututData from file
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
//! @class OutputDataReadStreamGzip
//! @brief Decorator to read outputdata from zipped files
//- -------------------------------------------------------------------
class OutputDataReadStreamGZip : public IOutputDataReadStrategy
{
public:
    OutputDataReadStreamGZip(IOutputDataReadStrategy *reader) : m_reader(reader){}
    virtual ~OutputDataReadStreamGZip(){ delete m_reader; }

    OutputData<double > *readOutputData(std::istream &file_stream);

private:
    IOutputDataReadStrategy *m_reader;
};



//- -------------------------------------------------------------------
//! @class OutputDataReadStreamV1
//! @brief Define concrete strategy to read OutputData from ASCII file
//!  1d array for x-axis, 1d array for y-axis, 2d array for data expected
//- -------------------------------------------------------------------
class OutputDataReadStreamV1 : public IOutputDataReadStrategy
{
public:
    OutputDataReadStreamV1(){}
    virtual ~OutputDataReadStreamV1(){}

    OutputData<double > *readOutputData(std::istream &file_stream);

    //! double numbers in string will be rounded according to the precision: if precision is 6, then 7.2908527770e+03 -> 7.290853e+03
    static std::string round_doubles(const std::string &str, int precision=10);

    //! parse double values from string to vector of double
    static vdouble1d_t parse_doubles(const std::string &str);

private:
};


//- -------------------------------------------------------------------
//! @class OutputDataReader
//! @brief Reads OutputData from file using different reading strategies
//- -------------------------------------------------------------------
class OutputDataReader
{
public:
    OutputDataReader() : m_reader(0) {}
    OutputDataReader(const std::string &file_name) : m_file_name(file_name), m_reader(0) {}
    OutputDataReader(IOutputDataReadStrategy *reader) : m_reader(reader) {}
    virtual ~OutputDataReader() { delete m_reader; }

    //! read output data from file
    OutputData<double > *getOutputData(const std::string &file_name);

    //! read output data from file (file name was set already from OutputDataIOFactory)
    OutputData<double > *getOutputData() { return getOutputData(m_file_name); }

    //! set concrete reading strategy
    void setStrategy(IOutputDataReadStrategy *reader) { m_reader = reader; }

private:
    std::string m_file_name;
    IOutputDataReadStrategy *m_reader;
};




#endif // OUTPUTDATAREADER_H
