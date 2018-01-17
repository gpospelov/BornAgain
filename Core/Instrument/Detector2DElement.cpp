// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Binning/Detector2DElement.cpp
//! @brief     Implements class Detector2DElement.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Detector2DElement.h"
#include "IPixel.h"


Detector2DElement::Detector2DElement(IPixel* p_pixel, Eigen::Matrix2cd analyzer_operator)
    : m_specular(false)
    , mP_pixel(p_pixel)
    , m_analyzer_operator(analyzer_operator)
{}

void Detector2DElement::setSpecular(bool specular)
{
    m_specular = specular;
}

bool Detector2DElement::isSpecular() const
{
    return m_specular;
}

std::unique_ptr<IPixel> Detector2DElement::pixel() const
{
    return std::unique_ptr<IPixel>(mP_pixel->clone());
}
