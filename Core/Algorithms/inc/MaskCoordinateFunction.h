// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/MaskCoordinateFunction.h
//! @brief     Defines classes MaskCoordinateFunction,
//!              MaskCoordinateRectangleFunction, MaskCoordinateEllipseFunction
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MASKCOORDINATEFUNCTION_H_
#define MASKCOORDINATEFUNCTION_H_

#include "WinDllMacros.h"
#include <cstddef>
#include "ICloneable.h"

//! ?

class MaskCoordinateFunction : public ICloneable
{
 public:
    MaskCoordinateFunction(size_t rank);
    virtual MaskCoordinateFunction *clone() const;
    virtual ~MaskCoordinateFunction() {}

    bool isMasked(size_t rank, const int *coordinates) const;
    void setInvertFlag(bool invert) { m_invert = invert; }
 protected:
    virtual bool isInStandardMaskedArea(const int *coordinates) const;
    size_t m_rank;
    bool m_invert;  //!< if true, the complement is masked instead
};

//! ?

class BA_CORE_API_ MaskCoordinateRectangleFunction : public MaskCoordinateFunction
{
 public:
    MaskCoordinateRectangleFunction(size_t rank, const int *minima, const int *maxima);
    virtual MaskCoordinateRectangleFunction *clone() const;
    virtual ~MaskCoordinateRectangleFunction();

 protected:
    virtual bool isInStandardMaskedArea(const int *coordinates) const;

 private:
    int *m_minima;
    int *m_maxima;
};

//! ?

class BA_CORE_API_ MaskCoordinateEllipseFunction : public MaskCoordinateFunction
{
 public:
    MaskCoordinateEllipseFunction(size_t rank, const int *center, const int *radii);
    virtual MaskCoordinateEllipseFunction *clone() const;
    virtual ~MaskCoordinateEllipseFunction();

 protected:
    virtual bool isInStandardMaskedArea(const int *coordinates) const;

 private:
    int *m_center;
    int *m_radii;
};

#endif /* MASKCOORDINATEFUNCTION_H_ */


