#include "Beam.h"

Beam::Beam()
: m_intensity(1.0)
{
}

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


