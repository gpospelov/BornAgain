// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Mask/MaskCoordinateFunction.h
//! @brief     Defines classes MaskCoordinateFunction,
//!              MaskCoordinateRectangleFunction, MaskCoordinateEllipseFunction
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MASKCOORDINATEFUNCTION_H
#define MASKCOORDINATEFUNCTION_H

#include "ICloneable.h"
#include <cstddef>

using std::size_t;

//! Base class for all kind of OutputData's masks.
//! @ingroup simulation_internal

class BA_CORE_API_ MaskCoordinateFunction : public ICloneable
{
public:
    MaskCoordinateFunction(size_t rank);
    virtual MaskCoordinateFunction* clone() const;
    virtual ~MaskCoordinateFunction() {}

    bool isMasked(size_t rank, const int* coordinates) const;
    void setInvertFlag(bool invert) { m_invert = invert; }
protected:
    virtual bool isInStandardMaskedArea(const int* coordinates) const;
    size_t m_rank;
    bool m_invert;  //!< if true, the complement is masked instead
};


//! Rectangular mask for OutputData.
//! @ingroup simulation_internal

class BA_CORE_API_ MaskCoordinateRectangleFunction : public MaskCoordinateFunction
{
public:
    MaskCoordinateRectangleFunction(size_t rank, const int* minima, const int* maxima);
    virtual MaskCoordinateRectangleFunction* clone() const;
    virtual ~MaskCoordinateRectangleFunction();

protected:
    virtual bool isInStandardMaskedArea(const int* coordinates) const;

private:
    int* m_minima;
    int* m_maxima;
};

//! Ellipse shaped mask for OutputData.
//! @ingroup simulation_internal

class BA_CORE_API_ MaskCoordinateEllipseFunction : public MaskCoordinateFunction
{
public:
    MaskCoordinateEllipseFunction(size_t rank, const int* center, const int* radii);
    virtual MaskCoordinateEllipseFunction* clone() const;
    virtual ~MaskCoordinateEllipseFunction();

protected:
    virtual bool isInStandardMaskedArea(const int* coordinates) const;

private:
    int* m_center;
    int* m_radii;
};

#endif // MASKCOORDINATEFUNCTION_H
