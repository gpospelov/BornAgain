// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Algorithms/MaskCoordinateFunction.cpp
//! @brief     Implements classes MaskCoordinateFunction, MaskCoordinate..Function
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MaskCoordinateFunction.h"


MaskCoordinateFunction::MaskCoordinateFunction(size_t rank)
    : m_rank(rank)
    , m_invert(false)
{
}

MaskCoordinateFunction* MaskCoordinateFunction::clone() const
{
    MaskCoordinateFunction* p_clone = new MaskCoordinateFunction(m_rank);
    p_clone->setInvertFlag(m_invert);
    return p_clone;
}

bool MaskCoordinateFunction::isMasked(size_t rank, const int* coordinates) const
{
    if (rank != m_rank)
        throw Exceptions::LogicErrorException(
            "Mask function must have same rank as data structure");
    if (m_invert) {
        return !isInStandardMaskedArea(coordinates);
    } else {
        return isInStandardMaskedArea(coordinates);
    }
}

bool MaskCoordinateFunction::isInStandardMaskedArea(const int* /* coordinates */) const
{
    return false;
}

MaskCoordinateRectangleFunction::MaskCoordinateRectangleFunction(
    size_t rank, const int* minima, const int* maxima)
    : MaskCoordinateFunction(rank)
    , m_minima(0)
    , m_maxima(0)
{
    m_minima = new int[m_rank];
    m_maxima = new int[m_rank];
    std::copy(minima, minima + m_rank, m_minima);
    std::copy(maxima, maxima + m_rank, m_maxima);
}

MaskCoordinateRectangleFunction* MaskCoordinateRectangleFunction::clone() const
{
    MaskCoordinateRectangleFunction *p_clone =
        new MaskCoordinateRectangleFunction(m_rank, m_minima, m_maxima);
    p_clone->setInvertFlag(m_invert);
    return p_clone;
}

MaskCoordinateRectangleFunction::~MaskCoordinateRectangleFunction()
{
    delete [] m_minima;
    delete [] m_maxima;
}

bool MaskCoordinateRectangleFunction::isInStandardMaskedArea(const int* coordinates) const
{
    for (size_t i=0; i<m_rank; ++i) {
        if (m_minima[i] > coordinates[i]) return false;
        if (m_maxima[i] < coordinates[i]) return false;
    }
    return true;
}

MaskCoordinateEllipseFunction::MaskCoordinateEllipseFunction(
    size_t rank, const int* center, const int* radii)
    : MaskCoordinateFunction(rank)
    , m_center(0)
    , m_radii(0)
{
    m_center = new int[m_rank];
    m_radii = new int[m_rank];
    std::copy(center, center + m_rank, m_center);
    std::copy(radii, radii + m_rank, m_radii);
}

MaskCoordinateEllipseFunction* MaskCoordinateEllipseFunction::clone() const
{
    MaskCoordinateEllipseFunction *p_clone =
        new MaskCoordinateEllipseFunction(m_rank, m_center, m_radii);
    p_clone->setInvertFlag(m_invert);
    return p_clone;
}

MaskCoordinateEllipseFunction::~MaskCoordinateEllipseFunction()
{
    delete [] m_center;
    delete [] m_radii;
}

bool MaskCoordinateEllipseFunction::isInStandardMaskedArea(const int* coordinates) const
{
    double weighted_squares = 0.0;
    for (size_t i=0; i<m_rank; ++i) {
        double dist = (double)coordinates[i] - (double)m_center[i];
        if (dist==0.0) continue;
        double d_radius = (double)m_radii[i];
        weighted_squares += dist*dist/d_radius/d_radius;
    }
    return weighted_squares <= 1.0;
}
