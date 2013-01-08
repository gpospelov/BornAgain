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
//! @brief Definition of INamed class for all objects having a name
//- -------------------------------------------------------------------
class INamed
{
public:
    INamed() {}
    INamed(const std::string &name) : m_name(name) { }
    INamed(const std::string &name, const std::string &title) : m_name(name), m_title(title) { }
    virtual ~INamed(){}

    void setName(std::string name) { m_name = name; }
    std::string getName() const { return m_name; }

    std::string getTitle() const { return m_title; }
    void setTitle(std::string title) { m_title = title; }

protected:
    std::string m_name;
    std::string m_title;
};

#endif // INAMED_H
