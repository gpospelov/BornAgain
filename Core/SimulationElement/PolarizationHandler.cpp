#include "PolarizationHandler.h"

PolarizationHandler::PolarizationHandler()
{
    m_polarization = Eigen::Matrix2cd::Identity();
    m_analyzer_operator = Eigen::Matrix2cd::Identity();
}

void PolarizationHandler::swapContent(PolarizationHandler& other)
{
    std::swap(m_polarization, other.m_polarization);
    std::swap(m_analyzer_operator, other.m_analyzer_operator);
}

