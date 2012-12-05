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

#include <string>
#include <vector>

//- -------------------------------------------------------------------
//! @class AxisDouble
//! @brief Definition of AxisDouble class that stores the points of an axis
//- -------------------------------------------------------------------
class AxisDouble
{
public:
    //! constructors
    AxisDouble(std::string name);
    AxisDouble(std::string name, size_t size, double start, double end);

    //! clone function
    AxisDouble* clone() const;

    //! create a new axis with half the number of bins
    AxisDouble createDoubleBinSize() const;

    //! destructor
    ~AxisDouble() {}

    //! retrieve the number of bins
    size_t getSize() const { return m_value_vector.size(); }

    //! retrieve the label of the axis
    std::string getName() const { return m_name; }

    //! set the axis label
    void setName(std::string name) { m_name = name; }

    //! add point to the end of the axis
    void push_back(double element) { m_value_vector.push_back(element); }

    //! indexed accessor
    double& operator[](size_t index) { return m_value_vector.at(index); }

    //! const indexed accessor
    const double& operator[](size_t index) const { return m_value_vector.at(index); }

    //! get value of first point of axis
    double getMin() const { return m_value_vector.front(); }

    //! get value of last point of axis
    double getMax() const { return m_value_vector.back(); }

    //! initialize axis points
    void initElements(size_t size, double start, double end);

    //! find number of bin which is closest to given value
    size_t findClosestIndex(double value) const;

    //! find the index that corresponds to the given lower bound (index is inclusive)
    size_t getLowerBoundIndex(double value) const;

    //! find the index that corresponds to the given upper bound (index is inclusive)
    size_t getUpperBoundIndex(double value) const;
private:
    std::string m_name;  //!< axis label
    std::vector<double> m_value_vector;  //!< vector containing the axis points
};

//! global helper function for comparison of axes
bool HaveSameNameAndShape(const AxisDouble &left, const AxisDouble &right);



#endif /* AXISDOUBLE_H_ */
