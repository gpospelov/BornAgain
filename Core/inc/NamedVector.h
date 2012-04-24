#ifndef NAMEDVECTOR_H
#define NAMEDVECTOR_H

#include <string>
#include <vector>

class NamedVectorBase
{
public:
    NamedVectorBase(std::string name) : m_name(name) {}
    virtual ~NamedVectorBase() {}

    virtual size_t getSize()=0;
    std::string getName() { return m_name; }

private:
    std::string m_name;
};

template <class T> class NamedVector : public NamedVectorBase
{
public:
    NamedVector(std::string name) : NamedVectorBase(name) {}
    NamedVector(std::string name, T start, T step, size_t size);
    ~NamedVector();

    size_t getSize() { return m_value_vector.size(); }
    void initElements(T start, T end, size_t size);
    void push_back(T element) { m_value_vector.push_back(element); }
    T& operator[](size_t index) { return m_value_vector.at(index); }

private:
    std::vector<T> m_value_vector;
};

template <class T> NamedVector<T>::NamedVector(std::string name, T start, T end, size_t size)
    : NamedVectorBase(name)
{
    T step = size>1 ? (end - start)/(size-1) : end;
    initElements(start, step, size);
}

template <class T> NamedVector<T>::~NamedVector()
{
    m_value_vector.clear();
}

template <class T> void NamedVector<T>::initElements(T start, T step, size_t size)
{
    for (size_t i=0; i<size; ++i)
    {
        push_back(start + step*i);
    }
}

#endif // NAMEDVECTOR_H
