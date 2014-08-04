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

#ifndef ASYMMETRICBINAXIS_H
#define ASYMMETRICBINAXIS_H


#include "IAxis.h"

//! @class AsymmetricBinAxis
//! @ingroup tools
//! @brief Axis with variable bin size and bins having custom mid point.

class BA_CORE_API_ AsymmetricBinAxis : public IAxis
{
public:
    //! @brief AsymmetricBinAxis constructor
    //! @param name Axis name
    //! @param nbins number of bins
    //! @param bin_centers Array of size [nbins] containing centers of all bins.
    AsymmetricBinAxis(std::string name, size_t nbins, const std::vector<double> &bin_centers);
    virtual ~AsymmetricBinAxis() {}

    AsymmetricBinAxis *clone() const;

    AsymmetricBinAxis *createDoubleBinSize() const;

    size_t getSize() const;

    double operator[](size_t index) const;

    Bin1D getBin(size_t index) const;

    double getMin() const;

    double getMax() const;

    size_t findClosestIndex(double value) const;

protected:
    void init_bin_edges();
    void print(std::ostream& ostr) const;
    virtual bool equals(const IAxis& other) const;
    size_t m_nbins;
    std::vector<double> m_bin_centers;
    std::vector<double> m_bin_edges;  //!< vector containing the bin limits
};


#endif
