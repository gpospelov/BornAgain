#ifndef AXISBIN_H_
#define AXISBIN_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   BinAxis.h
//! @brief  Definition of BinAxis class
//! @author Scientific Computing Group at FRM II
//! @date   Dec 6, 2012

#include "IAxis.h"

//#include <string>
//#include <vector>

//- -------------------------------------------------------------------
//! @class BinAxis
//! @brief Definition of BinAxis class that stores the bins of an axis
//- -------------------------------------------------------------------
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
