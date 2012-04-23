#include "StochasticGaussian.h"
#include "MathFunctions.h"

StochasticDoubleGaussian::StochasticDoubleGaussian(double average, double std_dev)
    : StochasticParameter<double>(average)
    , m_std_dev(std_dev)
{
}

StochasticDoubleGaussian::~StochasticDoubleGaussian()
{
}

void StochasticDoubleGaussian::setToRandom()
{
    m_current = MathFunctions::GenerateNormalRandom(m_average, m_std_dev);
}

double StochasticDoubleGaussian::probabilityDensity(double value) const
{
    return MathFunctions::Gaussian(value, m_average, m_std_dev);
}
