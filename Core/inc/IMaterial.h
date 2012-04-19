#ifndef IMATERIAL_H
#define IMATERIAL_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   IMaterial.h
//! @brief  Definition of IMaterial class
//! @author James Bond <j.bond@fz-juelich.de>, Chuck Norris <c.norris@fz-juelich.de>
//! @date   01.04.2012

#include <string>


//- -------------------------------------------------------------------
/// @class IMaterial
/// @brief Material definition
//- -------------------------------------------------------------------
class IMaterial
{
public:
    IMaterial() {}
    IMaterial(const std::string &name) : m_name(name) {}
    /// copy constructor
    IMaterial(const IMaterial &other);
    /// assignment operator
    IMaterial &operator=(const IMaterial &other);
    virtual ~IMaterial() {}

    /// set name of the material
    void setName(const std::string &name) { m_name = name; }

    /// return name of the material
    std::string getName() const { return m_name; }

private:
    std::string m_name;
};

#endif // IMATERIAL_H
