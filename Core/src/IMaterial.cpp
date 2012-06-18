#include "IMaterial.h"


IMaterial::IMaterial(const IMaterial &other) : INamed(other)
{

}


IMaterial &IMaterial::operator=(const IMaterial &other)
{
    if( this != &other) {
        INamed::operator=(other);
        m_name = other.m_name;
    }
    return *this;
}

