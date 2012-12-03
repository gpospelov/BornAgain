#ifndef MASK_H_
#define MASK_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   Mask.h
//! @brief  Definition of mask classes for OutputData masking
//! @author Scientific Computing Group at FRM II
//! @date   Nov 15, 2012

#include "MaskCoordinateFunction.h"

#include <cstddef>

//- -------------------------------------------------------------------
//! @class Mask
//! @brief Definition of base class for masking OutputData elements
//- -------------------------------------------------------------------
class Mask
{
public:
    template <class TValue, class TContainer> friend class OutputDataIterator;
    template <class TValue> friend class OutputData;
    Mask(Mask *p_submask=0);
    virtual ~Mask() { delete mp_submask; }
    virtual Mask *clone() const;

    size_t getFirstValidIndex();
    size_t getNextIndex(size_t total_index);
    void setMaxIndex(size_t max_index);

    size_t getOwnIndex() const { return m_own_index; }
    size_t getMaxIndex() const { return m_max_index; }

protected:
    virtual bool isMasked(size_t total_index) const;
    size_t m_own_index;
    size_t m_max_index;
    Mask *mp_submask;
private:
    size_t nextSubIndex(size_t total_index);
};

//- -------------------------------------------------------------------
//! @class MaskIndexModulus
//! @brief Mask based on the index modulo a given number
//- -------------------------------------------------------------------
class MaskIndexModulus : public Mask
{
public:
    MaskIndexModulus(size_t modulus, size_t remainder, Mask *p_submask=0)
        : Mask(p_submask), m_modulus(modulus), m_remainder(remainder) {}
    virtual ~MaskIndexModulus() {}
    virtual MaskIndexModulus *clone() const;

private:
    virtual bool isMasked(size_t total_index) const;
    size_t m_modulus;
    size_t m_remainder;
};

//- -------------------------------------------------------------------
//! @class MaskCoordinates
//! @brief Mask based on the coordinates
//- -------------------------------------------------------------------
class MaskCoordinates : public Mask
{
public:
    MaskCoordinates(size_t rank, const int *dims, Mask *p_submask=0);
    virtual ~MaskCoordinates();
    virtual MaskCoordinates *clone() const;

    void setMaskCoordinateFunction(MaskCoordinateFunction *p_mask_function);

private:
    virtual bool isMasked(size_t total_index) const;
    void setCachedCoordinates(size_t index) const;
    size_t m_rank;
    int *m_dims;
    mutable int *m_coordinates;
    MaskCoordinateFunction *mp_mask_function;
};

#endif /* MASK_H_ */
