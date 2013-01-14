#include "Beam.h"


/* ************************************************************************* */
// c-tors, assignment operators, swap
/* ************************************************************************* */
Beam::Beam() : m_central_k(), m_intensity(1.0)
{
    setName("Beam");
    init_parameters();
}

Beam::Beam(const Beam &other) : IParameterized(), m_central_k(other.m_central_k), m_intensity(other.m_intensity)
{
    setName(other.getName());
    init_parameters();
}

Beam &Beam::operator=(const Beam &other)
{
    if( this != &other)
    {
        Beam tmp(other);
        tmp.swapContent(*this);
    }
    return *this;
}

void Beam::swapContent(Beam &other)
{
    std::swap(this->m_central_k, other.m_central_k);
    std::swap(this->m_intensity, other.m_intensity);
}


/* ************************************************************************* */
// c-tors, assignment operators, swap
/* ************************************************************************* */
void Beam::setCentralK(const cvector_t& k_i)
{
    m_central_k = k_i;
}

void Beam::setCentralK(double lambda, double alpha_i, double phi_i)
{
    cvector_t k_i;
    k_i.setLambdaAlphaPhi(lambda, alpha_i, phi_i);
    m_central_k = k_i;
}

void Beam::init_parameters()
{
    getParameterPool()->clear();
    getParameterPool()->registerParameter("intensity", &m_intensity);
}
