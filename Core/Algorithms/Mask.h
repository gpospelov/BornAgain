// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Algorithms/Mask.h
//! @brief     Declares classes Mask, MaskIndexModulus, MaskCoordinates.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MASK_H_
#define MASK_H_

#include "MaskCoordinateFunction.h"


//! @class Mask
//! @ingroup simulation_internal
//! @brief Base class for masking OutputData elements.

class BA_CORE_API_ Mask : public ICloneable
{
public:
    template <class TValue, class TContainer> friend class OutputDataIterator;
    template <class TValue> friend class OutputData;
    explicit Mask(Mask *p_submask=0)
        : m_own_index(0), m_max_index(0), mp_submask(p_submask) {}
    virtual ~Mask() { delete mp_submask; }
    virtual Mask *clone() const;

    size_t getFirstValidIndex(size_t start_index);
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


//! @class MaskIndexModulus
//! @ingroup simulation_internal
//! @brief %Mask based on the index modulo a given number.

class BA_CORE_API_ MaskIndexModulus : public Mask
{
public:
    MaskIndexModulus(size_t modulus, size_t remainder, Mask *p_submask=0)
        : Mask(p_submask), m_modulus(modulus), m_remainder(remainder) {}
    virtual ~MaskIndexModulus() {}
    virtual MaskIndexModulus *clone() const;

protected:
    virtual bool isMasked(size_t total_index) const;

private:
    size_t m_modulus;
    size_t m_remainder;
};


//! @class MaskCoordinates
//! @ingroup simulation_internal
//! @brief %Mask based on the coordinates.

class BA_CORE_API_ MaskCoordinates : public Mask
{
public:
    MaskCoordinates(size_t rank, const int *dims, Mask *p_submask=0);
    virtual ~MaskCoordinates();
    virtual MaskCoordinates *clone() const;

    void setMaskCoordinateFunction(MaskCoordinateFunction *p_mask_function);

protected:
    virtual bool isMasked(size_t total_index) const;

private:
    void setCachedCoordinates(size_t index) const;
    size_t m_rank;
    int *m_dims;
    mutable int *m_coordinates;
    MaskCoordinateFunction *mp_mask_function;
};

#endif /* MASK_H_ */
