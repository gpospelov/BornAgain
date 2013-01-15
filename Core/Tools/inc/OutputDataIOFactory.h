#ifndef OUTPUTDATAIOFACTORY_H
#define OUTPUTDATAIOFACTORY_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   OutputDataIOFactory.h
//! @brief  Definition of OutputDataIOFactory class
//! @author Scientific Computing Group at FRM II
//! @date   01.10.2012

#include "OutputDataReader.h"
#include "OutputDataWriter.h"
#include <string>
#include <boost/shared_ptr.hpp>


//- -------------------------------------------------------------------
//! @class OutputDataIOFactory
//! @brief Reads OutputData from files in different format
//- -------------------------------------------------------------------
class OutputDataIOFactory
{
public:
    typedef boost::shared_ptr<OutputDataReader > OutputDataReader_t;
    OutputDataIOFactory();

    static OutputData<double > *getOutputData(const std::string &file_name);
    static OutputDataReader_t getReader(const std::string &file_name);
};

#endif // OUTPUTDATAIOFACTORY_H
