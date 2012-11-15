#ifndef MASKEDOUTPUTDATAITERATOR_H_
#define MASKEDOUTPUTDATAITERATOR_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   MaskedOutputDataIterator.h
//! @brief  Definition of MaskedOutputDataIterator class
//! @author Scientific Computing Group at FRM II
//! @date   Nov 13, 2012

#include "OutputDataIterator.h"
#include "OutputDataMaskStrategies.h"

template <class TValue, class TContainer> class MaskedOutputDataIterator : public OutputDataIterator<TValue, TContainer>
{
public:
    // typedefs
    typedef OutputDataMaskStrategyBase strategy_t;
    typedef OutputDataIterator<TValue, TContainer> base_t;

    //! constructor
    MaskedOutputDataIterator(const base_t &iterator);

    //! templated copy construction
    template<class TValue2, class TContainer2> MaskedOutputDataIterator(
            const MaskedOutputDataIterator<TValue2, TContainer2> &other);

    //! templated copy assignment
    template<class TValue2, class TContainer2> MaskedOutputDataIterator<TValue, TContainer> &operator=(
            const MaskedOutputDataIterator<TValue2, TContainer2> &other);

    virtual ~MaskedOutputDataIterator();

    //! prefix increment
    virtual MaskedOutputDataIterator<TValue, TContainer> &operator++();

    //! postfix increment (return value is sliced)
    virtual OutputDataIterator<const TValue, const TContainer> operator++(int);

    //! retrieve indexed element
    virtual TValue &operator[](size_t index) const;

    //! set strategy for element selection
    void setStrategy(const strategy_t &strategy);

    //! get strategy for element selection
    const strategy_t *getStrategy() const { return mp_strategy; }

protected:
    //! indicate if the current data element is not masked
    virtual bool isSelected() const;
    virtual void swapContents(MaskedOutputDataIterator<TValue, TContainer> &other);
    strategy_t* mp_strategy;
};

template<class TValue, class TContainer>
MaskedOutputDataIterator<TValue, TContainer>::MaskedOutputDataIterator(const base_t &iterator)
: base_t(iterator)
, mp_strategy(0)
{
    mp_strategy = new OutputDataMaskStrategyBase();
}

template<class TValue, class TContainer>
MaskedOutputDataIterator<TValue, TContainer>::~MaskedOutputDataIterator()
{
    delete mp_strategy;
}

template<class TValue, class TContainer>
template<class TValue2, class TContainer2> MaskedOutputDataIterator<TValue, TContainer>::MaskedOutputDataIterator(
        const MaskedOutputDataIterator<TValue2, TContainer2>& other)
: base_t(other)
{
    mp_strategy = other.getStrategy()->clone();
}

template<class TValue, class TContainer>
template<class TValue2, class TContainer2>
MaskedOutputDataIterator<TValue, TContainer> &MaskedOutputDataIterator<TValue, TContainer>::operator=(
        const MaskedOutputDataIterator<TValue2, TContainer2> &other)
{
    MaskedOutputDataIterator<TValue, TContainer> copy(other);
    swapContents(other);
    return *this;
}

template<class TValue, class TContainer>
MaskedOutputDataIterator<TValue, TContainer>& MaskedOutputDataIterator<TValue, TContainer>::operator++()
{
    base_t::operator ++();
    while (!isSelected()) base_t::operator++();
    return *this;
}

template<class TValue, class TContainer>
OutputDataIterator<const TValue, const TContainer> MaskedOutputDataIterator<TValue, TContainer>::operator++(int dummy)
{
    (void)dummy;
    MaskedOutputDataIterator<const TValue, const TContainer> result = *this;
    ++(*this);
    return (OutputDataIterator<const TValue, const TContainer>)result;
}

template<class TValue, class TContainer>
TValue& MaskedOutputDataIterator<TValue, TContainer>::operator[](size_t index) const
{
    OutputDataIterator<TValue, TContainer> it(this->getContainer(), index);
    if (!isSelected()) {
        throw LogicErrorException("Accessing a masked value through its masked iterator is not allowed");
    }
    return *it;
}

template<class TValue, class TContainer>
void MaskedOutputDataIterator<TValue, TContainer>::setStrategy(const strategy_t& strategy)
{
    if (mp_strategy != &strategy) {
        delete mp_strategy;
        mp_strategy = strategy.clone();
        if (!isSelected()) ++(*this);
    }
}

template<class TValue, class TContainer> inline bool MaskedOutputDataIterator<TValue, TContainer>::isSelected() const
{
    return (mp_strategy->isSelected(this->getIndex())) || (this->getIndex() == this->getContainer()->getAllocatedSize());
}

template<class TValue, class TContainer>
void MaskedOutputDataIterator<TValue, TContainer>::swapContents(MaskedOutputDataIterator<TValue, TContainer> &other)
{
    base_t::swapContents(other);
    std::swap(this->mp_strategy, other.mp_strategy);
}

#endif /* MASKEDOUTPUTDATAITERATOR_H_ */
