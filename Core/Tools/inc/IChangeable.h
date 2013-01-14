#ifndef ICHANGEABLE_H
#define ICHANGEABLE_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   IChangeable.h
//! @brief  Definition of IChangeable interface
//! @author Scientific Computing Group at FRM II
//! @date   Dec 14, 2012


//- -------------------------------------------------------------------
//! @class IChangeable
//! @brief Definition of IChangeable
//- -------------------------------------------------------------------
class IChangeable
{
public:
    IChangeable(bool is_changed=false) : m_is_changed(is_changed){}
    virtual ~IChangeable(){}

    bool isChanged()
    {
        bool result = m_is_changed;
        m_is_changed = false;
        return result;
    }

    void setIsChanged(bool is_changed) { m_is_changed = is_changed; }

private:
    bool m_is_changed;
};

#endif // ICHANGEABLE_H
