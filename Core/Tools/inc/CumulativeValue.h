// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/CumulativeValue.h
//! @brief     Defines class CumulativeValue.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef CUMULATIVE_VALUE_H
#define CUMULATIVE_VALUE_H

#include "WinDllMacros.h"

//! @class CumulativeValue
//! @ingroup tools
//! @brief The cumulative value with average and rms on-the-flight calculations.

class BA_CORE_API_ CumulativeValue
{
public:
    CumulativeValue();

    int getNumberOfEntries() const;

    double getContent() const;
    void setContent(double value);

    double getAverage() const;

    double getRMS() const;

    void add(double value, double weight=1.0);

    void clear();

    friend bool operator< (const CumulativeValue& lhs, const CumulativeValue& rhs);
    friend bool operator> (const CumulativeValue& lhs, const CumulativeValue& rhs);

private:
    int m_n_entries;
    double m_sum;
    double m_average;
    double m_rms2; //sum[ (x-x_aver)^2]/nentries
    double m_sum_of_weights;
};

inline CumulativeValue::CumulativeValue()
{
    clear();
}

inline int CumulativeValue::getNumberOfEntries() const
{
    return m_n_entries;
}

inline double CumulativeValue::getContent() const
{
    return m_sum;
}

inline void CumulativeValue::setContent(double value)
{
    m_sum = value;
}

inline double CumulativeValue::getAverage() const
{
    return m_average;
}

inline double CumulativeValue::getRMS() const
{
    return std::sqrt(m_rms2);
}

inline void CumulativeValue::add(double value, double weight)
{
    m_n_entries++;
    m_sum += value;
    m_rms2 = (m_sum_of_weights/(m_sum_of_weights+weight))*
            (m_rms2+(weight/(m_sum_of_weights+weight))*(value-m_average)*(value-m_average));
    m_average = m_average+(value-m_average)*weight/(m_sum_of_weights+weight);
    m_sum_of_weights += weight;
}

inline void CumulativeValue::clear()
{
    m_n_entries = 0;
    m_sum = 0.0;
    m_average = 0.0;
    m_rms2 = 0.0;
    m_sum_of_weights = 0.0;
}

inline bool operator<(const CumulativeValue& lhs, const CumulativeValue& rhs)
{
    return lhs.getContent()< rhs.getContent();
}

inline bool operator>(const CumulativeValue& lhs, const CumulativeValue& rhs)
{
    return rhs<lhs;
}

#endif
