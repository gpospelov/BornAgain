#ifndef OUTPUTDATAITERATOR_H_
#define OUTPUTDATAITERATOR_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   OutputDataIterator.h
//! @brief  Definition of OutputDataIterator template
//! @author Scientific Computing Group at FRM II
//! @date   Nov 12, 2012

#include "Mask.h"

//- -------------------------------------------------------------------
//! @class OutputDataIterator
//! @brief Definition of iterator for underlying OutputData container
//- -------------------------------------------------------------------
template <class TValue, class TContainer> class OutputDataIterator
{
public:
    //! constructor
    OutputDataIterator(TContainer *p_output_data, size_t start_at_index=0);

    //! templated copy construction
    template<class TValue2, class TContainer2> OutputDataIterator(
            const OutputDataIterator<TValue2, TContainer2> &other);

    //! non-templated copy construction
    OutputDataIterator(const OutputDataIterator<TValue, TContainer> &other);

    //! templated copy assignment
    template<class TValue2, class TContainer2> OutputDataIterator<TValue, TContainer> &operator=(
            const OutputDataIterator<TValue2, TContainer2> &right);

    //! non-templated copy asssignment
    OutputDataIterator<TValue, TContainer> &operator=(const OutputDataIterator<TValue, TContainer> &right);

    virtual ~OutputDataIterator();

    //! prefix increment
    virtual OutputDataIterator<TValue, TContainer> &operator++();

    //! postfix increment
    virtual OutputDataIterator<TValue, TContainer> operator++(int);

    //! retrieve current element
    virtual TValue &operator*() const;

    //! pointer access
    virtual TValue* operator->() const;

    //! get current index
    const size_t getIndex() const { return m_current_index; }

    //! get container pointer
    TContainer *getContainer() const { return mp_output_data; }

    //! get mask
    Mask *getMask() const { return mp_mask; }

    //! set mask (or a stack of masks)
    void setMask(const Mask &mask);

    //! add mask (also resets index to first available element)
    void addMask(const Mask &mask);

protected:
    virtual void swapContents(OutputDataIterator<TValue, TContainer> &other);
    size_t m_current_index;
    TContainer *mp_output_data;
    Mask *mp_mask;
};

//! comparison
template <class TValue1, class TContainer1, class TValue2, class TContainer2> bool operator==(
        const OutputDataIterator<TValue1, TContainer1> &left,
        const OutputDataIterator<TValue2, TContainer2> &right) {
    return left.getContainer()==right.getContainer() && left.getIndex()==right.getIndex();
}

template <class TValue1, class TContainer1, class TValue2, class TContainer2> bool operator!=(
        const OutputDataIterator<TValue1, TContainer1> &left,
        const OutputDataIterator<TValue2, TContainer2> &right) {
    return !(left == right);
}

template<class TValue, class TContainer> OutputDataIterator<TValue, TContainer>::OutputDataIterator(
        TContainer *p_output_data, size_t start_at_index)
: m_current_index(start_at_index)
, mp_output_data(p_output_data)
, mp_mask(0)
{
}

template<class TValue, class TContainer>
template<class TValue2, class TContainer2>
OutputDataIterator<TValue, TContainer>::OutputDataIterator(const OutputDataIterator<TValue2, TContainer2> &other)
: m_current_index(0)
, mp_output_data(0)
, mp_mask(0)
{
    mp_output_data = static_cast<TContainer *>(other.getContainer());
    m_current_index = other.getIndex();
    if (other.getMask()) {
        mp_mask = other.getMask()->clone();
    }
}

template<class TValue, class TContainer> OutputDataIterator<TValue, TContainer>::OutputDataIterator(
        const OutputDataIterator<TValue, TContainer> &other)
: m_current_index(0)
, mp_output_data(0)
, mp_mask(0)
{
    mp_output_data = other.getContainer();
    m_current_index = other.getIndex();
    if (other.getMask()) {
        mp_mask = other.getMask()->clone();
    }
}

template<class TValue, class TContainer>
template<class TValue2, class TContainer2>
OutputDataIterator<TValue, TContainer> &OutputDataIterator<TValue, TContainer>::operator=(
        const OutputDataIterator<TValue2, TContainer2> &right)
{
    OutputDataIterator<TValue, TContainer> copy(right);
    swapContents(copy);
    return *this;
}

template<class TValue, class TContainer>
OutputDataIterator<TValue, TContainer> &OutputDataIterator<TValue, TContainer>::operator=(
        const OutputDataIterator<TValue, TContainer>& right)
{
    OutputDataIterator<TValue, TContainer> copy(right);
    swapContents(copy);
    return *this;
}

template<class TValue, class TContainer> OutputDataIterator<TValue, TContainer>::~OutputDataIterator()
{
    if (mp_mask) delete mp_mask;
}

template<class TValue, class TContainer> OutputDataIterator<TValue, TContainer> &OutputDataIterator<TValue, TContainer>::operator++()
{
    if (mp_mask) {
        m_current_index = mp_mask->getNextIndex(m_current_index);
    }
    else {
        if (m_current_index<mp_output_data->getAllocatedSize()) {
            ++m_current_index;
        }
    }
    return *this;
}

template<class TValue, class TContainer> OutputDataIterator<TValue, TContainer> OutputDataIterator<TValue, TContainer>::operator++(int dummy)
{
    (void)dummy;
    OutputDataIterator<TValue, TContainer> result(*this);
    this->operator++();
    return result;
}

template<class TValue, class TContainer> TValue &OutputDataIterator<TValue, TContainer>::operator*() const
{
    return (*mp_output_data)[m_current_index];
}

template<class TValue, class TContainer> TValue* OutputDataIterator<TValue, TContainer>::operator->() const
{
    return &((*mp_output_data)[m_current_index]);
}

template<class TValue, class TContainer> void OutputDataIterator<TValue, TContainer>::setMask(const Mask &mask)
{
    if (mp_mask != &mask) {
        delete mp_mask;
        mp_mask = mask.clone();
        mp_mask->setMaxIndex(mp_output_data->getAllocatedSize());
    }
    m_current_index = mp_mask->getFirstValidIndex();
}

template<class TValue, class TContainer> void OutputDataIterator<TValue, TContainer>::addMask(const Mask &mask)
{
    if (mask.mp_submask) {
        throw RuntimeErrorException("One can only add single masks to OutputDataIterator at a time");
    }
    Mask *p_old_mask = getMask();
    mp_mask = mask.clone();
    mp_mask->mp_submask = p_old_mask;
    mp_mask->setMaxIndex(mp_output_data->getAllocatedSize());
    m_current_index = mp_mask->getFirstValidIndex();
}

template<class TValue, class TContainer> void OutputDataIterator<TValue, TContainer>::swapContents(OutputDataIterator<TValue, TContainer>& other)
{
    std::swap(this->m_current_index, other.m_current_index);
    std::swap(this->mp_output_data, other.mp_output_data);
    std::swap(this->mp_mask, other.mp_mask);
}

#endif /* OUTPUTDATAITERATOR_H_ */
