#ifndef NAMEDVECTOR_H
#define NAMEDVECTOR_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   NamedVector.h
//! @brief  Definition of NamedVector class
//! @author Scientific Computing Group at FRM II
//! @date   01.04.2012

#include <string>
#include <vector>


class NamedVectorBase
{
public:
    NamedVectorBase(std::string name) : m_name(name) {}
    virtual ~NamedVectorBase() {}

    virtual size_t getSize()=0;
    std::string getName() { return m_name; }
    void setName(std::string name) { m_name = name; }
    virtual NamedVectorBase* clone()=0;

private:
    std::string m_name;
};

template <class T> class NamedVector : public NamedVectorBase
{
public:
    NamedVector(std::string name) : NamedVectorBase(name) {}
    NamedVector(std::string name, T start, T end, size_t size);
    ~NamedVector();

    size_t getSize() { return m_value_vector.size(); }
    virtual NamedVectorBase* clone();
    void initElements(T start, T end, size_t size);
    void push_back(T element) { m_value_vector.push_back(element); }
    T& operator[](size_t index) { return m_value_vector.at(index); }

private:
    std::vector<T> m_value_vector;
};

template <class T> NamedVector<T>::NamedVector(std::string name, T start, T end, size_t size)
    : NamedVectorBase(name)
{
    initElements(start, end, size);
}

template <class T> NamedVector<T>::~NamedVector()
{
    m_value_vector.clear();
}

template <class T> NamedVectorBase* NamedVector<T>::clone()
{
    return new NamedVector<T>(*this);
}

template <class T> void NamedVector<T>::initElements(T start, T end, size_t size)
{
	T step = size>1 ? (end - start)/(size-1) : end;
    for (size_t i=0; i<size; ++i)
    {
        push_back(start + step*i);
    }
}

#endif // NAMEDVECTOR_H
