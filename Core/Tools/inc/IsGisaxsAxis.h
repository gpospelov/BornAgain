// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/IsGisaxsAxis.h
//! @brief     Defines class IsGisaxsAxis.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISGISAXSAXIS_H
#define ISGISAXSAXIS_H


#include "VariableBinAxis.h"

//! @class IsGisaxsAxis
//! @ingroup tools
//! @brief Axis with fixed bin size in sin(angle) space used for numerical
//! comparison with IsGisaxs. The main feature of the axis that it produces
//! zero bins size.

class BA_CORE_API_ IsGisaxsAxis : public VariableBinAxis
{
public:
    //! @brief IsGisaxsAxis constructor
    //! @param name Axis name
    //! @param nbins number of bins
    //! @param start center of first bin (IsGisaxs convention)
    //! @param end center of last bin (IsGisaxs convention)
    IsGisaxsAxis(std::string name, size_t nbins, double start, double end);
    virtual ~IsGisaxsAxis() {}

    IsGisaxsAxis *clone() const;

    Bin1D getBin(size_t index) const;

protected:
    void print(std::ostream& ostr) const;

    double m_start;
    double m_end;
    std::vector<double> m_bin_centers;
};


#endif
