#ifndef BINAXIS_H_
#define BINAXIS_H_
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

#include <string>
#include <vector>

//- -------------------------------------------------------------------
//! @class Bin
//! @brief Definition of Bin class that stores the bounds of a bin
//- -------------------------------------------------------------------
struct Bin
{
    double m_lower;  //!< lower bound of the bin
    double m_upper;  //!< upper bound of the bin
    double getMidPoint() { return (m_lower + m_upper)/2.0; }
};

//! equality operator for bins
bool operator==(const Bin &left, const Bin &right);

//! inequality operator for bins
bool operator!=(const Bin &left, const Bin &right) {
    return !(left==right);
}

//- -------------------------------------------------------------------
//! @class BinAxis
//! @brief Definition of BinAxis class that stores the bins of an axis
//- -------------------------------------------------------------------
class BinAxis
{
public:
    //! constructors
    BinAxis(std::string name);
    BinAxis(std::string name, size_t nbr_bins, double start, double end);

    //! clone function
    BinAxis* clone() const;

    //! create a new axis with half the number of bins
    BinAxis createDoubleBinSize() const;

    //! destructor
    ~BinAxis() {}

    //! retrieve the number of bins
    size_t getSize() const;

    //! retrieve the label of the axis
    std::string getName() const { return m_name; }

    //! set the axis label
    void setName(std::string name) { m_name = name; }

    //! add new bin limit to the end
    void push_back(double limit) { m_value_vector.push_back(limit); }

    //! indexed accessor retrieves midpoint of given bin
    Bin operator[](size_t index);

    //! const indexed accessor retrieves midpoint of given bin
    const Bin operator[](size_t index) const;

    //! get minimum value of axis
    double getMin() const { return m_value_vector.front(); }

    //! get maximum value of axis
    double getMax() const { return m_value_vector.back(); }

    //! initialize axis bins
    void initBins(size_t nbr_bins, double start, double end);

    //! find number of bin for the given value
    size_t findClosestIndex(double value) const;

//    //! find the index that corresponds to the given lower bound (index is inclusive)
//    size_t getLowerBoundIndex(double value) const;
//
//    //! find the index that corresponds to the given upper bound (index is inclusive)
//    size_t getUpperBoundIndex(double value) const;
private:
    std::string m_name;  //!< axis label
    std::vector<double> m_value_vector;  //!< vector containing the bin limits
};

//! global helper function for comparison of axes
bool HaveSameNameAndShape(const BinAxis &left, const BinAxis &right);


#endif /* BINAXIS_H_ */
