// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/AxisBin.h
//! @brief     Defines class AxisBin.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef CONSTKBINAXIS_H
#define CONSTKBINAXIS_H


#include "VariableBinAxis.h"

//! @class ConstKBinAxis
//! @ingroup tools
//! @brief Axis with fixed bin size in sin(angle) space.

class BA_CORE_API_ ConstKBinAxis : public VariableBinAxis
{
public:
    //! @brief ConstKBinAxis constructor
    //! @param name Axis name
    //! @param nbins number of bins
    //! @param start low edge of first bin
    //! @param end upper edge of last bin
    ConstKBinAxis(std::string name, size_t nbins, double start, double end);
    virtual ~ConstKBinAxis() {}

    ConstKBinAxis *clone() const;

protected:
    void print(std::ostream& ostr) const;

    double m_start;
    double m_end;
};


#endif
