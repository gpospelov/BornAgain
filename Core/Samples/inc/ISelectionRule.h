#ifndef ISELECTIONRULE_H_
#define ISELECTIONRULE_H_

// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   ISelectionRule.h
//! @brief  Definition of ISelectionRule interface
//! @author Scientific Computing Group at FRM II
//! @date   Sep 11, 2012

#include "Coordinate3D.h"

class ISelectionRule
{
public:
    virtual ~ISelectionRule() {}

    virtual ISelectionRule *clone() const=0;

    virtual bool coordinateSelected(Coordinate3D<int> coordinate) const=0;
};

class SimpleSelectionRule : public ISelectionRule
{
public:
    SimpleSelectionRule(int a, int b, int c, int modulus);
    virtual ~SimpleSelectionRule() {}

    virtual SimpleSelectionRule *clone() const;

    virtual bool coordinateSelected(Coordinate3D<int> coordinate) const;
private:
    int m_a, m_b, m_c;
    int m_mod;
};

inline SimpleSelectionRule::SimpleSelectionRule(int a, int b, int c,
        int modulus)
: m_a(a), m_b(b), m_c(c)
, m_mod(modulus)
{
}

inline SimpleSelectionRule* SimpleSelectionRule::clone() const
{
    return new SimpleSelectionRule(m_a, m_b, m_c, m_mod);
}

inline bool SimpleSelectionRule::coordinateSelected(
        Coordinate3D<int> coordinate) const
{
    return (m_a*coordinate[0]+m_b*coordinate[1]+m_c*coordinate[2])%m_mod == 0;
}

#endif /* ISELECTIONRULE_H_ */
