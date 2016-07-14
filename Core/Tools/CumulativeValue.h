// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Tools/CumulativeValue.h
//! @brief     Declares class CumulativeValue.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef CUMULATIVEVALUE_H
#define CUMULATIVEVALUE_H

//! @class CumulativeValue
//! @ingroup tools
//! @brief The cumulative value with average and rms on-the-flight calculations.

class BA_CORE_API_ CumulativeValue
{
public:
    CumulativeValue() { clear(); }

    void clear();
    void setContent(double value) { m_sum = value; }
    void add(double value, double weight=1.0);

    int getNumberOfEntries() const { return m_n_entries; }
    double getContent() const { return m_sum; }
    double getAverage() const { return m_average; }
    double getRMS() const;

    friend bool operator< (const CumulativeValue& lhs, const CumulativeValue& rhs);
    friend bool operator> (const CumulativeValue& lhs, const CumulativeValue& rhs);

private:
    int m_n_entries;
    double m_sum;
    double m_average;
    double m_rms2; //sum[ (x-x_aver)^2]/nentries
    double m_sum_of_weights;
};

#endif // CUMULATIVEVALUE_H
