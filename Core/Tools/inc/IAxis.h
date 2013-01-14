#ifndef IAXIS_H_
#define IAXIS_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   IAxis.h
//! @brief  Definition of IAxis interface
//! @author Scientific Computing Group at FRM II
//! @date   Dec 10, 2012

#include "Bin.h"

//#include <string>

//- -------------------------------------------------------------------
//! @class IAxis
//! @brief Definition of IAxis interface for 1d axes
//- -------------------------------------------------------------------

class IAxis
{
public:
    //! constructors
    IAxis(std::string name) : m_name(name) {}

    //! clone function
    virtual IAxis *clone() const=0;

    //! create a new axis with half the number of bins
    virtual IAxis *createDoubleBinSize() const=0;

    //! destructor
    virtual ~IAxis() {}

    //! retrieve the number of bins
    virtual size_t getSize() const=0;

    //! retrieve the label of the axis
    std::string getName() const { return m_name; }

    //! set the axis label
    void setName(std::string name) { m_name = name; }

    //! indexed accessor retrieves a sample
    virtual double operator[](size_t index) const=0;

    //! retrieve a 1d bin for the given index
    virtual Bin1D getBin(size_t index) const=0;

    //! get value of first point of axis
    virtual double getMin() const=0;

    //! get value of last point of axis
    virtual double getMax() const=0;

    //! find bin index which is best match for given value
    virtual size_t findClosestIndex(double value) const=0;

    //! test for equality
    friend bool operator==(const IAxis &left, const IAxis &right) {
        return left.equals(right);
    }

//    //! find the index that corresponds to the given lower bound (index is inclusive)
//    virtual size_t getLowerBoundIndex(double value) const=0;
//
//    //! find the index that corresponds to the given upper bound (index is inclusive)
//    virtual size_t getUpperBoundIndex(double value) const=0;
protected:
    virtual bool equals(const IAxis &other) const;
    std::string m_name;  //!< axis label
};

inline bool IAxis::equals(const IAxis& other) const
{
    return getName()==other.getName();
}

//! test for inequality
inline bool operator!=(const IAxis &left, const IAxis &right) {
    return !(left ==  right);
}

//! global helper function for comparison of axes
inline bool HaveSameNameAndShape(const IAxis &left, const IAxis &right)
{
    return left == right;
}

#endif /* IAXIS_H_ */
