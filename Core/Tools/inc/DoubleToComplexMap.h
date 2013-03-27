// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/DoubleToComplexMap.h
//! @brief     Defines classes DoubleToComplexMap, DoubleToPairOfComplexMap.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef DOUBLETOCOMPLEXUNORDEREDMAP_H
#define DOUBLETOCOMPLEXUNORDEREDMAP_H

//#include "Exceptions.h"
//#include "Types.h"
#include "Utils.h"
#include "IDoubleToComplexFunction.h"

//! Double to complex unordered map.

class DoubleToComplexMap : public IDoubleToComplexMap
{
 public:
    typedef Utils::UnorderedMap<double, complex_t> container_t;

    DoubleToComplexMap(){}
    DoubleToComplexMap(const container_t& value_map) : m_value_map(value_map) {}

    complex_t&  operator[] (double key) { return m_value_map[key]; }
    DoubleToComplexMap *clone() const { return new DoubleToComplexMap(m_value_map); }
    const complex_t& evaluate(double value) const { return m_value_map.find(value); }
 private:
    container_t m_value_map;
};

//! Double to pair of complex unordered map.

class DoubleToPairOfComplexMap : public IDoubleToPairOfComplexMap
{
 public:
    typedef Utils::UnorderedMap<double, complexpair_t> container_t;

    DoubleToPairOfComplexMap(){}
    DoubleToPairOfComplexMap(const container_t& value_map) : m_value_map(value_map) {}

    complexpair_t&  operator[] (double key) { return m_value_map[key]; }
    DoubleToPairOfComplexMap *clone() const { return new DoubleToPairOfComplexMap(m_value_map); }
   const complexpair_t& evaluate(double value) const { return m_value_map.find(value); }
 private:
    container_t m_value_map;
};

#endif // DOUBLETOCOMPLEXUNORDEREDMAP_H
