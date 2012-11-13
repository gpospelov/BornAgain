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

template <class TValue> class IIterator
{
public:
    // construction/destruction
    IIterator() {}
    virtual ~IIterator() {}
    virtual IIterator &operator++() { return *this; }
    virtual TValue &operator*() const {
        TValue *p_new = new TValue();
        return *p_new;
    }
};

template <class TValue, class TContainer> class OutputDataIterator : public IIterator<TValue>
{
public:
    //! constructor
    OutputDataIterator(TContainer *p_output_data, size_t start_at_index=0): IIterator<TValue>(),
        m_current_index(start_at_index), mp_output_data(p_output_data) {}

    //! templated copy construction
    template<class TValue2, class TContainer2> OutputDataIterator(
            const OutputDataIterator<TValue2, TContainer2> &other);

    //! templated copy assignment
    template<class TValue2, class TContainer2> OutputDataIterator<TValue, TContainer> &operator=(
            const OutputDataIterator<TValue2, TContainer2> &right);

    virtual ~OutputDataIterator();

    //! prefix increment
    OutputDataIterator<TValue, TContainer> &operator++();

    //! postfix increment
    OutputDataIterator<const TValue, TContainer> operator++(int);

    //! retrieve current element
    virtual TValue &operator*() const;

    //! pointer access
    virtual TValue* operator->() const;

    //! retrieve indexed element
    TValue &operator[](size_t index) const;

    //! get current index
    const size_t getIndex() const { return m_current_index; }

    //! get container pointer
    TContainer *const getContainer() const { return mp_output_data; }

    //! comparison
    template <class TValue2, class TContainer2> bool operator==(
            const OutputDataIterator<TValue2, TContainer2> &other);
    template <class TValue2, class TContainer2> bool operator!=(
            const OutputDataIterator<TValue2, TContainer2> &other) { return !(*this == other); }

protected:
    virtual void swapContents(OutputDataIterator<TValue, TContainer> &other);
    size_t m_current_index;
    TContainer *mp_output_data;
};

template<class TValue, class TContainer>
template<class TValue2, class TContainer2>
OutputDataIterator<TValue, TContainer>::OutputDataIterator(const OutputDataIterator<TValue2, TContainer2> &other)
: m_current_index(0)
, mp_output_data(0)
{
    mp_output_data = other.getContainer();
    m_current_index = other.getIndex();
}

template<class TValue, class TContainer>
template<class TValue2, class TContainer2>
OutputDataIterator<TValue, TContainer> &OutputDataIterator<TValue, TContainer>::operator=(const OutputDataIterator<TValue2, TContainer2> &right)
{
    OutputDataIterator<TValue, TContainer> copy(right);
    swapContents(copy);
    return *this;
}

template<class TValue, class TContainer> OutputDataIterator<TValue, TContainer>::~OutputDataIterator()
{
}

template<class TValue, class TContainer> OutputDataIterator<TValue, TContainer> &OutputDataIterator<TValue, TContainer>::operator++()
{
    ++m_current_index;
    return *this;
}

template<class TValue, class TContainer> OutputDataIterator<const TValue, TContainer> OutputDataIterator<TValue, TContainer>::operator ++(int dummy)
{
    (void)dummy;
    OutputDataIterator<const TValue, TContainer> result = *this;
    ++(*this);
    return result;
}

template<class TValue, class TContainer> TValue &OutputDataIterator<TValue, TContainer>::operator*() const
{
    return (*this)[m_current_index];
}

template<class TValue, class TContainer> TValue* OutputDataIterator<TValue, TContainer>::operator ->() const
{
    return &((*this)[m_current_index]);
}

template<class TValue, class TContainer> TValue &OutputDataIterator<TValue, TContainer>::operator[](size_t index) const
{
    return (*mp_output_data)[index];
}

template<class TValue, class TContainer>
template<class TValue2, class TContainer2>
bool OutputDataIterator<TValue, TContainer>::operator ==(
        const OutputDataIterator<TValue2, TContainer2>& other)
{
    return mp_output_data==other.getContainer() && m_current_index==other.getIndex();
}

template<class TValue, class TContainer> void OutputDataIterator<TValue, TContainer>::swapContents(OutputDataIterator<TValue, TContainer>& other)
{
    std::swap(this->m_current_index, other.m_current_index);
    std::swap(this->mp_output_data, other.mp_output_data);
}

#endif /* OUTPUTDATAITERATOR_H_ */
