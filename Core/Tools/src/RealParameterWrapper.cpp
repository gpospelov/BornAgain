#include "RealParameterWrapper.h"



RealParameterWrapper::RealParameterWrapper(const RealParameterWrapper &other )
{
    m_data = other.m_data;
}

RealParameterWrapper &RealParameterWrapper::operator=(const RealParameterWrapper &other)
{
    if( this != &other )  {
        RealParameterWrapper tmp(other);
        tmp.swapContent(*this);
    }
    return *this;
}

void RealParameterWrapper::swapContent(RealParameterWrapper &other)
{
    std::swap(this->m_data, other.m_data);
}

