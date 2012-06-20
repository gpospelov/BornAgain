#ifndef INAMED_H
#define INAMED_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   INamed.h
//! @brief  Definition of INamed class
//! @author Scientific Computing Group at FRM II
//! @date   18.06.2012

#include <string>


//- -------------------------------------------------------------------
//! @class INamed
//! @brief Definition of INamed class for all objects havint the name
//- -------------------------------------------------------------------
class INamed
{
public:
    INamed() {}
    INamed(std::string name) { m_name = name; }
    virtual ~INamed(){}

    virtual std::string getName() const { return m_name; }
    virtual void setName(std::string name) { m_name = name; }

protected:
    std::string m_name;
};

#endif // INAMED_H
