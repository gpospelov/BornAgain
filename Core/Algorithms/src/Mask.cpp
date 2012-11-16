#include "Mask.h"

Mask::Mask(Mask* p_submask)
: m_mask_index(0), m_end_index(0), mp_submask(p_submask)
{
}

Mask* Mask::clone() const
{
    Mask *p_new_submask = mp_submask ? mp_submask->clone() : 0;
    Mask *p_new = new Mask(p_new_submask);
    p_new->m_mask_index = m_mask_index;
    p_new->setMaxIndex(m_end_index);
    return p_new;
}

size_t Mask::getFirstValidIndex()
{
    m_mask_index = 0;
    size_t result = 0;
    if (mp_submask) result = mp_submask->getFirstValidIndex();
    while (isMasked(result)) {
        result = nextSubIndex(result);
        if (result >= m_end_index) {
            return m_end_index;
        }
    }
    return result;
}

size_t Mask::getNextIndex(size_t total_index)
{
    size_t result = nextSubIndex(total_index);
    while (isMasked(result)) {
        result = nextSubIndex(result);
        if (result >= m_end_index) {
            return m_end_index;
        }
    }
    return result;
}

void Mask::setMaxIndex(size_t max_index)
{
    m_end_index = max_index;
    if (mp_submask) mp_submask->setMaxIndex(max_index);
}

bool Mask::isMasked(size_t total_index) const
{
    (void)total_index;
    return false;
}

size_t Mask::nextSubIndex(size_t total_index)
{
    size_t result=0;
    if (!mp_submask) {
        result = total_index+1;
    }
    else {
        result = mp_submask->getNextIndex(total_index);
    }
    ++m_mask_index;
    return result;
}

MaskIndexModulus* MaskIndexModulus::clone() const
{
    Mask *p_new_submask = mp_submask ? mp_submask->clone() : 0;
    MaskIndexModulus *p_new = new MaskIndexModulus(m_modulus, m_remainder, p_new_submask);
    p_new->m_mask_index = m_mask_index;
    p_new->setMaxIndex(m_end_index);
    return p_new;
}

bool MaskIndexModulus::isMasked(size_t total_index) const
{
    (void)total_index;
    return m_mask_index % m_modulus != m_remainder;
}
