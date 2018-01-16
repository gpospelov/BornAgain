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


Detector2DElement::Detector2DElement(std::unique_ptr<IPixel> P_pixel)
    : mP_pixel(std::move(P_pixel))
{
    initAnalyzerOperator();
}

void Detector2DElement::initAnalyzerOperator()
{
    m_analyzer_operator = Eigen::Matrix2cd::Identity();
}
