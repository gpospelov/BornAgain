#ifndef MASKCOORDINATEFUNCTION_H_
#define MASKCOORDINATEFUNCTION_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   MaskCoordinateFunction.h
//! @brief  Definition of MaskCoordinateFunction classes
//! @author Scientific Computing Group at FRM II
//! @date   Nov 20, 2012

#include <cstddef>
#include "ICloneable.h"

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

class MaskCoordinateRectangleFunction : public MaskCoordinateFunction
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

class MaskCoordinateEllipseFunction : public MaskCoordinateFunction
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
