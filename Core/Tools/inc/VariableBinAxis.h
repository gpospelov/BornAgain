// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/VariableBinAxis.h
//! @brief     Defines class VariableBinAxis.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef VARIABLEBINAXIS_H
#define VARIABLEBINAXIS_H


#include "IAxis.h"

//! @class VariableBinAxis
//! @ingroup tools
//! @brief Axis with variable bin size.

class BA_CORE_API_ VariableBinAxis : public IAxis
{
public:
    //! @brief VariableBinAxis constructor
    //! @param name Axis name
    //! @param nbins number of bins
    //! @param bin_boundaries Array of size nbins+1 containing low-edges for each
    //! bin and upper edge of last bin.
    VariableBinAxis(std::string name, size_t nbins, const std::vector<double> &bin_boundaries);
    virtual ~VariableBinAxis() {}

    VariableBinAxis *clone() const;

    size_t getSize() const;

    double operator[](size_t index) const;

    Bin1D getBin(size_t index) const;

    double getMin() const;

    double getMax() const;

    size_t findClosestIndex(double value) const;

    std::vector<double > getBinCenters() const;

    std::vector<double > getBinBoundaries() const;

protected:
    VariableBinAxis(std::string name, int nbins = 0);
    void setBinBoundaries(const std::vector<double> &bin_boundaries);

    void print(std::ostream& ostr) const;
    virtual bool equals(const IAxis& other) const;
    size_t m_nbins;

private:
    std::vector<double> m_bin_boundaries;  //!< vector containing the bin limits
};


#endif
