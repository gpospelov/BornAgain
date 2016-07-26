// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Mask/Mask.cpp
//! @brief     Implements classes Mask, MaskIndexModulus, MaskCoordinates.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Mask.h"
#include "MaskCoordinateFunction.h"
#include <algorithm>

// ************************************************************************** //
// implement class Mask
// ************************************************************************** //

Mask* Mask::clone() const
{
    Mask *p_new_submask = 0;
    if (mp_submask) {
        p_new_submask = mp_submask->clone();
    }
    Mask *p_new = new Mask(p_new_submask);
    p_new->m_own_index = m_own_index;
    p_new->setMaxIndex(m_max_index);
    return p_new;
}

size_t Mask::getFirstValidIndex(size_t start_index)
{
    m_own_index = 0;
    size_t result = start_index;
    if (mp_submask) result = mp_submask->getFirstValidIndex(start_index);
    while (isMasked(result)) {
        result = nextSubIndex(result);
        if (result >= m_max_index) {
            return m_max_index;
        }
    }
    return result;
}

size_t Mask::getNextIndex(size_t total_index)
{
    size_t result = nextSubIndex(total_index);
    while (isMasked(result)) {
        result = nextSubIndex(result);
        if (result >= m_max_index) {
            return m_max_index;
        }
    }
    return result;
}

void Mask::setMaxIndex(size_t max_index)
{
    m_max_index = max_index;
    if (mp_submask) mp_submask->setMaxIndex(max_index);
}

bool Mask::isMasked(size_t total_index) const
{
    (void)total_index;
    return false;
}

size_t Mask::nextSubIndex(size_t total_index)
{
    size_t result=total_index;
    if (total_index < m_max_index) {
        if (!mp_submask) {
            ++result;
        }
        else {
            result = mp_submask->getNextIndex(total_index);
        }
        ++m_own_index;
    }
    else {
        return m_max_index;
    }
    return result;
}

// ************************************************************************** //
// implement class MaskIndexModulus
// ************************************************************************** //

MaskIndexModulus* MaskIndexModulus::clone() const
{

    Mask *p_new_submask = 0;
    if (mp_submask) {
        p_new_submask = mp_submask->clone();
    }
    MaskIndexModulus *p_new =
        new MaskIndexModulus(m_modulus, m_remainder, p_new_submask);
    p_new->m_own_index = m_own_index;
    p_new->setMaxIndex(m_max_index);
    return p_new;
}

bool MaskIndexModulus::isMasked(size_t total_index) const
{
    (void)total_index;
    return m_own_index % m_modulus != m_remainder;
}

// ************************************************************************** //
// implement class MaskCoordinates
// ************************************************************************** //

MaskCoordinates::MaskCoordinates(size_t rank, const int* dims, Mask* p_submask)
: Mask(p_submask)
, m_rank(rank)
, m_dims(0)
, m_coordinates(0)
, mp_mask_function(0)
{
    m_dims = new int[m_rank];
    m_coordinates = new int[m_rank];
    std::copy(dims, dims + m_rank, m_dims);
    size_t max_index = (m_rank==0) ? 0 : 1;
    for (size_t i=0; i<m_rank; ++i) {
        max_index *= m_dims[i];
    }
    setMaxIndex(max_index);
}

MaskCoordinates::~MaskCoordinates()
{
    delete [] m_dims;
    delete [] m_coordinates;
    if (mp_mask_function) delete mp_mask_function;
}

MaskCoordinates* MaskCoordinates::clone() const
{
    Mask *p_new_submask = 0;
    if (mp_submask) {
        p_new_submask = mp_submask->clone();
    }
    MaskCoordinates *p_new = new MaskCoordinates(m_rank, m_dims, p_new_submask);
    p_new->m_own_index = m_own_index;
    p_new->setMaxIndex(m_max_index);
    if (mp_mask_function) {
        p_new->setMaskCoordinateFunction(mp_mask_function->clone());
    }
    return p_new;
}

void MaskCoordinates::setMaskCoordinateFunction(
    MaskCoordinateFunction* p_mask_function)
{
    if(mp_mask_function && mp_mask_function != p_mask_function) {
        delete mp_mask_function;
    }
    mp_mask_function = p_mask_function;
}

bool MaskCoordinates::isMasked(size_t total_index) const
{
    if (!mp_mask_function) return false;
    setCachedCoordinates(total_index);
    return mp_mask_function->isMasked(m_rank, m_coordinates);
}

void MaskCoordinates::setCachedCoordinates(size_t index) const
{
    int remainder = (int)index;
    for (size_t i=m_rank; i>0; --i) {
        m_coordinates[i-1] = remainder % m_dims[i-1];
        remainder = remainder / m_dims[i-1];
    }
}
