#include "HomogeneousMaterial.h"


HomogeneousMaterial::HomogeneousMaterial()
{

}


HomogeneousMaterial::HomogeneousMaterial(complex_t refractive_index)
    : IMaterial("noname"), m_refractive_index(refractive_index)
{

}


HomogeneousMaterial::HomogeneousMaterial(const std::string &name, complex_t refractive_index)
    : IMaterial(name), m_refractive_index(refractive_index)
{

}


HomogeneousMaterial::HomogeneousMaterial(const HomogeneousMaterial &other) : IMaterial(other)
{
    m_refractive_index = m_refractive_index;
}


HomogeneousMaterial &HomogeneousMaterial::operator=(const HomogeneousMaterial &other)
{
    if(this != &other)
    {
        IMaterial::operator=(other);
        m_refractive_index = other.m_refractive_index;
    }
    return *this;
}

