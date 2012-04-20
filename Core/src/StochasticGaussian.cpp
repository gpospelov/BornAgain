#include "StochasticGaussian.h"
#include "MathFunctions.h"

StochasticDoubleGaussian::StochasticDoubleGaussian(double average, double std_dev)
    : m_average(average)
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

void StochasticDoubleGaussian::setToAverage()
{
    m_current = m_average;
}

double StochasticDoubleGaussian::getRandom()
{
    setToRandom();
    return getCurrent();
}

double StochasticDoubleGaussian::getAverage()
{
    setToAverage();
    return getCurrent();
}

double StochasticDoubleGaussian::getCurrentProbDensity()
{
    return MathFunctions::Gaussian(m_current, m_average, m_std_dev);
}
