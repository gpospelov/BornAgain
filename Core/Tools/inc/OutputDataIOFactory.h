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


//#include "IFactory.h"
#include "ISingleton.h"
#include "OutputDataReader.h"
#include "OutputDataWriter.h"
#include <string>


//- -------------------------------------------------------------------
//! @class OutputDataIOFactory
//! @brief Define number o
//- -------------------------------------------------------------------
//class OutputDataIOFactory : public ISingleton<OutputDataIOFactory >, public IFactory<std::string, IOutputDataReadStrategy>
class OutputDataIOFactory : public ISingleton<OutputDataIOFactory >
{
public:
    OutputDataIOFactory();

    OutputDataReader *getReader(const std::string &file_name) const;
};

#endif // OUTPUTDATAIOFACTORY_H
