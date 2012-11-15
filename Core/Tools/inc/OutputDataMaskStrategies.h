#ifndef OUTPUTDATAMASKSTRATEGIES_H_
#define OUTPUTDATAMASKSTRATEGIES_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   OutputDataMaskStrategies.h
//! @brief  Definition of different strategies for OutputData masks
//! @author Scientific Computing Group at FRM II
//! @date   Nov 13, 2012

#include "OutputDataIterator.h"

//- -------------------------------------------------------------------
//! @class OutputDataMaskStrategyBase
//! @brief Definition of basic strategy interface for masked OutputDataIterator's
//- -------------------------------------------------------------------
class OutputDataMaskStrategyBase
{
public:
    //! constructor
    OutputDataMaskStrategyBase() {}

    //! copy constructor
    OutputDataMaskStrategyBase(const OutputDataMaskStrategyBase &other) { (void)other; }

    //! copy assignment
    OutputDataMaskStrategyBase &operator=(const OutputDataMaskStrategyBase &right) { (void)right; return *this; }

    virtual ~OutputDataMaskStrategyBase() {}

    //! clone
    virtual OutputDataMaskStrategyBase *clone() const { return new OutputDataMaskStrategyBase(); }

    //! indicates if given index is not masked
    virtual bool isSelected(size_t index) { (void)index; return true; }
};

//- -------------------------------------------------------------------
//! @class OutputDataMaskStrategyIndexModulus
//! @brief Definition of strategy interface for masked OutputDataIterator's
//! based on the remainder after division of the index by a given modulus
//- -------------------------------------------------------------------
class OutputDataMaskStrategyIndexModulus : public OutputDataMaskStrategyBase
{
public:
    typedef OutputDataMaskStrategyBase base_t;
    //! constructor
    OutputDataMaskStrategyIndexModulus(size_t modulus, size_t remainder)
        : m_modulus(modulus), m_remainder(remainder) {}

    //! copy constructor
    OutputDataMaskStrategyIndexModulus(const OutputDataMaskStrategyIndexModulus &other)
        : base_t(other), m_modulus(other.m_modulus), m_remainder(other.m_remainder) {}

    //! templated copy assignment
    OutputDataMaskStrategyIndexModulus &operator=(const OutputDataMaskStrategyIndexModulus &right) {
        m_modulus = right.m_modulus;
        m_remainder = right.m_remainder;
        return *this;
    }

    virtual ~OutputDataMaskStrategyIndexModulus() {}

    //! clone
    virtual OutputDataMaskStrategyIndexModulus *clone() const {
        return new OutputDataMaskStrategyIndexModulus(*this);
    }

    //! indicates if given iterator is not masked
    virtual bool isSelected(size_t index) {
        return (index%m_modulus)==m_remainder;
    }
private:
    size_t m_modulus;
    size_t m_remainder;
};

#endif /* OUTPUTDATAMASKSTRATEGIES_H_ */
