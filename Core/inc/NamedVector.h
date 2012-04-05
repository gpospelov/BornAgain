#ifndef NAMEDVECTOR_H
#define NAMEDVECTOR_H

#include <string>
#include <vector>

template <class T> class NamedVector
{
public:
    NamedVector(std::string name) { m_name = name; }
    ~NamedVector();

    size_t getSize() { return m_value_vector.size(); }
    std::string getName() { return m_name; }
    void push_back(T element) { m_value_vector.push_back(element); }
    T& operator[](size_t index) { return m_value_vector.at(index); }

private:
    std::string m_name;
    std::vector<T> m_value_vector;
};

template <class T> NamedVector<T>::~NamedVector()
{
    m_value_vector.clear();
}

#endif // NAMEDVECTOR_H
