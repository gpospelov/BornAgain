#include "IMaterial.h"


IMaterial::IMaterial(const IMaterial &other)
{
    m_name = other.m_name;
}


IMaterial &IMaterial::operator=(const IMaterial &other)
{
    if( this != &other) {
        m_name = other.m_name;
    }
    return *this;
}

