// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @copyright Forschungszentrum Jülich GmbH 2013
//             
//  Homepage:  apps.jcns.fz-juelich.de/BornAgain
//  License:   GNU General Public License v3 or higher (see COPYING)
//
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
//! @file      Algorithms/ResolutionFunction2DSimple.cpp 
//! @brief     Implements class ResolutionFunction2DSimple.
//
// ************************************************************************** //

#include "ResolutionFunction2DSimple.h"
#include "MathFunctions.h"

/* ************************************************************************* */
// c-tors, clone
/* ************************************************************************* */
ResolutionFunction2DSimple::ResolutionFunction2DSimple(double sigma_x,
        double sigma_y)
: m_sigma_x(sigma_x)
, m_sigma_y(sigma_y)
{
    setName("ResolutionFunction2D");
    init_parameters();
}

ResolutionFunction2DSimple::~ResolutionFunction2DSimple()
{
}

ResolutionFunction2DSimple::ResolutionFunction2DSimple(const ResolutionFunction2DSimple &other) : IResolutionFunction2D(other)
{
    m_sigma_x = other.m_sigma_x;
    m_sigma_y = other.m_sigma_y;
    init_parameters();
}

ResolutionFunction2DSimple *ResolutionFunction2DSimple::clone() const
{
    return new ResolutionFunction2DSimple(*this);
}

/* ************************************************************************* */
//
/* ************************************************************************* */
double ResolutionFunction2DSimple::evaluateCDF(double x, double y) const
{
    return MathFunctions::IntegratedGaussian(x, 0.0, m_sigma_x)
                * MathFunctions::IntegratedGaussian(y, 0.0, m_sigma_y);
}

void ResolutionFunction2DSimple::init_parameters()
{
    getParameterPool()->clear();
    getParameterPool()->registerParameter("sigma_x", &m_sigma_x);
    getParameterPool()->registerParameter("sigma_y", &m_sigma_y);
}
