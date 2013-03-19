// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/AxisBin.h
//! @brief     Defines class AxisBin.
//!
//! @homepage  apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef AXISBIN_H_
#define AXISBIN_H_

#include "IAxis.h"

//! The bins of an axis

class AxisBin : public IAxis
{
public:
    //! constructors
    AxisBin(std::string name);
    AxisBin(std::string name, size_t nbr_bins, double start, double end);

    //! clone function
    virtual AxisBin *clone() const;

    //! create a new axis with half the number of bins
    virtual AxisBin *createDoubleBinSize() const;

    //! destructor
    virtual ~AxisBin() {}

    //! add new bin limit to the end
    void push_back(double limit) { m_value_vector.push_back(limit); }

    virtual size_t getSize() const;

   //! indexed accessor retrieves midpoint of given bin
    virtual double operator[](size_t index) const;

    virtual Bin1D getBin(size_t index) const;

    virtual double getMin() const { return m_value_vector.front(); }

    virtual double getMax() const { return m_value_vector.back(); }

    //! initialize axis bins
    void initBins(size_t nbr_bins, double start, double end);

    virtual size_t findClosestIndex(double value) const;

//    //! find the bin that contains the given value
//    Bin1D findMatchingBin(double value) const;
protected:
    virtual bool equals(const IAxis &other) const;
private:
    std::vector<double> m_value_vector;  //!< vector containing the bin limits
};

#endif /* AXISBIN_H_ */
