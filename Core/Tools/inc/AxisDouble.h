#ifndef AXISDOUBLE_H_
#define AXISDOUBLE_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   AxisDouble.h
//! @brief  Definition of AxisDouble class
//! @author Scientific Computing Group at FRM II
//! @date   Dec 4, 2012

#include "IAxis.h"

//#include <string>
//#include <vector>

// Forward declaration of BinAxis class, as needed for conversion constructor
class AxisBin;

//- -------------------------------------------------------------------
//! @class AxisDouble
//! @brief Definition of AxisDouble class that stores the points of an axis
//- -------------------------------------------------------------------
class AxisDouble : public IAxis
{
public:
    //! constructors
    AxisDouble(std::string name);
    AxisDouble(std::string name, size_t size, double start, double end);

    //! explicit conversion from BinAxis
    //TODO: make explicit
    AxisDouble(const AxisBin &source);

    virtual AxisDouble *clone() const;

    virtual AxisDouble *createDoubleBinSize() const;

    //! destructor
    virtual ~AxisDouble() {}

    virtual size_t getSize() const { return m_sample_vector.size(); }

    //! add point to the end of the axis
    void push_back(double element) { m_sample_vector.push_back(element); }

    virtual double operator[](size_t index) const { return m_sample_vector[index]; }

    virtual Bin1D getBin(size_t index) const;

    //! get value of first point of axis
    virtual double getMin() const { return m_sample_vector.front(); }

    //! get value of last point of axis
    virtual double getMax() const { return m_sample_vector.back(); }

    //! initialize axis points
    void initElements(size_t size, double start, double end);

    //! find number of bin which is closest to given value
    virtual size_t findClosestIndex(double value) const;

    //! find the index that corresponds to the given lower bound (index is inclusive)
    size_t getLowerBoundIndex(double value) const;

    //! find the index that corresponds to the given upper bound (index is inclusive)
    size_t getUpperBoundIndex(double value) const;

protected:
    virtual bool equals(const IAxis &other) const;

private:
    std::vector<double> m_sample_vector;  //!< vector containing the axis points
    double m_bin_size;
};

#endif /* AXISDOUBLE_H_ */
