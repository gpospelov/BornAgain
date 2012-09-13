#ifndef TRANGE_H_
#define TRANGE_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TRange.h
//! @brief  Definition of TRange template
//! @author Scientific Computing Group at FRM II
//! @date   Sep 12, 2012

template <class T> class TRange
{
public:
    TRange(T min, T max) : m_min(min), m_max(max) {}

    T getMin() const { return m_min; }
    T getMax() const { return m_max; }
    T getDifference() const { return m_max-m_min; }

    bool inRange(T value) const { return value >= m_min && value < m_max; }
private:
    T m_min, m_max;
};

#endif /* TRANGE_H_ */
