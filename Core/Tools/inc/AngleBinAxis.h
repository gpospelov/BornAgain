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

#ifndef ANGLEBINAXIS_H
#define ANGLEBINAXIS_H


#include "IAxis.h"

//! @class AngleBinAxis
//! @ingroup tools
//! @brief Axis with fixed bin size in sin(angle) space.

class BA_CORE_API_ AngleBinAxis : public IAxis
{
public:
    //! @brief AngleBinAxis constructor
    //! @param name Axis name
    //! @param nbins number of bins
    //! @param start low edge of first bin
    //! @param end upper edge of last bin
    AngleBinAxis(std::string name, size_t nbins, double start, double end);
    virtual ~AngleBinAxis() {}

    AngleBinAxis *clone() const;

    size_t getSize() const;

    double operator[](size_t index) const;

    Bin1D getBin(size_t index) const;

    double getMin() const;

    double getMax() const;

    size_t findClosestIndex(double value) const;

    static AngleBinAxis *createIsGISAXSAxis(std::string name, size_t nbins, double start, double end);

protected:
    void print(std::ostream& ostr) const;
    virtual bool equals(const IAxis& other) const;

private:
    size_t m_nbins;
    double m_start;
    double m_end;
    double m_start_sin;
    double m_end_sin;
    double m_step_sin;
};



#endif
