// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/OutputDataIterator.h
//! @brief     Declares and implements template class OutputDataIterator.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef OUTPUTDATAITERATOR_H_
#define OUTPUTDATAITERATOR_H_

#include "Mask.h"

#include <iterator>

//! @class OutputDataIterator
//! @ingroup tools_internal
//! @brief Iterator for underlying OutputData container

template <class TValue, class TContainer> class OutputDataIterator
{
public:
    //! Empty constructor to comply with stl forward iterators
    OutputDataIterator();

    //! constructor
    OutputDataIterator(TContainer *p_output_data, size_t start_at_index=0);

    //! templated copy construction
    template<class TValue2, class TContainer2> OutputDataIterator(
            const OutputDataIterator<TValue2, TContainer2>& other);

    //! non-templated copy construction
    OutputDataIterator(const OutputDataIterator<TValue, TContainer>& other);

    //! templated copy assignment
    template<class TValue2, class TContainer2>
        OutputDataIterator<TValue, TContainer>& operator=(
            const OutputDataIterator<TValue2, TContainer2>& right);

    //! non-templated copy asssignment
    OutputDataIterator<TValue, TContainer>& operator=(
            const OutputDataIterator<TValue, TContainer>& right);

    virtual ~OutputDataIterator();

    //! prefix increment
    virtual OutputDataIterator<TValue, TContainer>& operator++();

    //! postfix increment
    virtual OutputDataIterator<TValue, TContainer> operator++(int);

    //! retrieve current element
    virtual TValue& operator*() const;

    //! pointer access
    virtual TValue* operator->() const;

    //! Returns current index
    size_t getIndex() const { return m_current_index; }

    //! Returns container pointer
    TContainer *getContainer() const { return mp_output_data; }

    //! Returns mask
    Mask *getMask() const { return mp_mask; }

    //! Sets mask (or a stack of masks)
    void setMask(const Mask& mask);

    //! Adds mask (also resets index to first available element)
    void addMask(const Mask& mask);

    // typedefs for std::iterator_traits
    typedef std::forward_iterator_tag iterator_category;
    typedef TValue value_type;
    typedef ptrdiff_t difference_type;
    typedef TValue* pointer_type;
    typedef TValue& reference_type;
//#ifdef _MSC_VER
	typedef TValue* pointer;
    typedef TValue& reference;
//#endif

protected:
    virtual void swapContents(OutputDataIterator<TValue, TContainer>& other);
    size_t m_current_index;
    TContainer *mp_output_data;
    Mask *mp_mask;
};

template<class TValue, class TContainer>
    OutputDataIterator<TValue, TContainer>::OutputDataIterator()
: m_current_index(0)
, mp_output_data(0)
, mp_mask(0)
{
}

template<class TValue, class TContainer>
    OutputDataIterator<TValue, TContainer>::OutputDataIterator(
        TContainer *p_output_data, size_t start_at_index)
: m_current_index(start_at_index)
, mp_output_data(p_output_data)
, mp_mask(0)
{
}

template<class TValue, class TContainer>
template<class TValue2, class TContainer2>
    OutputDataIterator<TValue, TContainer>::OutputDataIterator(
        const OutputDataIterator<TValue2, TContainer2>& other)
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

template<class TValue, class TContainer>
    OutputDataIterator<TValue, TContainer>::OutputDataIterator(
        const OutputDataIterator<TValue, TContainer>& other)
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

//! comparison
template <class TValue1, class TContainer1, class TValue2, class TContainer2>
    bool operator==(
        const OutputDataIterator<TValue1, TContainer1>& left,
        const OutputDataIterator<TValue2, TContainer2>& right)
{
    return left.getContainer()==right.getContainer() &&
            left.getIndex()==right.getIndex();
}

template <class TValue1, class TContainer1, class TValue2, class TContainer2>
    bool operator!=(
        const OutputDataIterator<TValue1, TContainer1>& left,
        const OutputDataIterator<TValue2, TContainer2>& right)
{
    return !(left == right);
}

template<class TValue, class TContainer>
template<class TValue2, class TContainer2>
    OutputDataIterator<TValue, TContainer>&
    OutputDataIterator<TValue, TContainer>::operator=(
        const OutputDataIterator<TValue2, TContainer2>& right)
{
    OutputDataIterator<TValue, TContainer> copy(right);
    swapContents(copy);
    return *this;
}

template<class TValue, class TContainer>
    OutputDataIterator<TValue, TContainer>&
    OutputDataIterator<TValue, TContainer>::operator=(
        const OutputDataIterator<TValue, TContainer>& right)
{
    OutputDataIterator<TValue, TContainer> copy(right);
    swapContents(copy);
    return *this;
}

template<class TValue, class TContainer>
    OutputDataIterator<TValue, TContainer>::~OutputDataIterator()
{
    if (mp_mask) delete mp_mask;
}

template<class TValue, class TContainer>
    OutputDataIterator<TValue, TContainer>&
    OutputDataIterator<TValue, TContainer>::operator++()
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

template<class TValue, class TContainer>
    OutputDataIterator<TValue, TContainer>
    OutputDataIterator<TValue, TContainer>::operator++(int dummy)
{
    (void)dummy;
    OutputDataIterator<TValue, TContainer> result(*this);
    this->operator++();
    return result;
}

template<class TValue, class TContainer> TValue&
    OutputDataIterator<TValue, TContainer>::operator*() const
{
    return (*mp_output_data)[m_current_index];
}

template<class TValue, class TContainer> TValue*
    OutputDataIterator<TValue, TContainer>::operator->() const
{
    return& ((*mp_output_data)[m_current_index]);
}

template<class TValue, class TContainer>
    void OutputDataIterator<TValue, TContainer>::setMask(const Mask& mask)
{
    if (mp_mask !=& mask) {
        delete mp_mask;
        mp_mask = mask.clone();
        mp_mask->setMaxIndex(mp_output_data->getAllocatedSize());
    }
    m_current_index = mp_mask->getFirstValidIndex(m_current_index);
}

template<class TValue, class TContainer>
    void OutputDataIterator<TValue, TContainer>::addMask(const Mask& mask)
{
    if (mask.mp_submask) {
        throw RuntimeErrorException("OutputDataIterator<>::addMask()"
            " -> Error! One can only add single masks to OutputDataIterator"
            " at a time");
    }
    Mask *p_old_mask = getMask();
    mp_mask = mask.clone();
    mp_mask->mp_submask = p_old_mask;
    mp_mask->setMaxIndex(mp_output_data->getAllocatedSize());
    m_current_index = mp_mask->getFirstValidIndex(m_current_index);
}

template<class TValue, class TContainer>
    void OutputDataIterator<TValue, TContainer>::swapContents(
        OutputDataIterator<TValue, TContainer>& other)
{
    std::swap(this->m_current_index, other.m_current_index);
    std::swap(this->mp_output_data, other.mp_output_data);
    std::swap(this->mp_mask, other.mp_mask);
}

#endif /* OUTPUTDATAITERATOR_H_ */


