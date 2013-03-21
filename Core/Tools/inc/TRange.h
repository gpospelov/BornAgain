// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/TRange.h
//! @brief     Defines and implements template classes TRange and TSampledRange.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef TRANGE_H_
#define TRANGE_H_

//! An interval [min..max[.

template <class T> class TRange
{
  public:
    TRange(T min, T max) : m_min(min), m_max(max) {}
    virtual ~TRange(){}

    T getMin() const { return m_min; }
    T getMax() const { return m_max; }
    T getDifference() const { return m_max-m_min; }

    bool inRange(T value) const { return value >= m_min && value < m_max; }
  private:
    T m_min, m_max;
};

//! An interval [min..max[, and a number of samples.

template <class T> class TSampledRange : public TRange<T>
{
  public:
    TSampledRange(size_t n_samples, T min, T max)
        : TRange<T>(min, max), m_n_samples(n_samples) {}

    size_t getNSamples() const { return m_n_samples; }
  private:
    size_t m_n_samples;
};

#endif /* TRANGE_H_ */
