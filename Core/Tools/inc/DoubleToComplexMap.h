#ifndef DOUBLETOCOMPLEXUNORDEREDMAP_H
#define DOUBLETOCOMPLEXUNORDEREDMAP_H

//#include "Exceptions.h"
//#include "Types.h"
#include "Utils.h"
#include "IDoubleToComplexFunction.h"



//- -------------------------------------------------------------------
//! @class DoubleToComplexMap
//! @brief Double to complex unordered map
//- -------------------------------------------------------------------
class DoubleToComplexMap : public IDoubleToComplexMap
{
public:
    typedef Utils::UnorderedMap<double, complex_t> container_t;

    DoubleToComplexMap(){}
    DoubleToComplexMap(const container_t &value_map) : m_value_map(value_map) {}

    complex_t & operator[] (double key) { return m_value_map[key]; }
    DoubleToComplexMap *clone() const { return new DoubleToComplexMap(m_value_map); }
    const complex_t &evaluate(double value) const { return m_value_map.find(value); }
private:
    container_t m_value_map;
};


//- -------------------------------------------------------------------
//! @class DoubleToPairOfComplexMap
//! @brief Double to pair of complex unordered map
//- -------------------------------------------------------------------
class DoubleToPairOfComplexMap : public IDoubleToPairOfComplexMap
{
public:
    typedef Utils::UnorderedMap<double, complexpair_t> container_t;

    DoubleToPairOfComplexMap(){}
    DoubleToPairOfComplexMap(const container_t &value_map) : m_value_map(value_map) {}

    complexpair_t & operator[] (double key) { return m_value_map[key]; }
    DoubleToPairOfComplexMap *clone() const { return new DoubleToPairOfComplexMap(m_value_map); }
   const complexpair_t &evaluate(double value) const { return m_value_map.find(value); }
private:
    container_t m_value_map;
};




#endif // DOUBLETOCOMPLEXUNORDEREDMAP_H
