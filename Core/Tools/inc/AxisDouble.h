// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/AxisDouble.h
//! @brief     Defines class AxisDouble.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef AXISDOUBLE_H_
#define AXISDOUBLE_H_

#include "WinDllMacros.h"
#include "IAxis.h"

//class AxisBin;  // forward declaration needed for conversion constructor
#include "AxisBin.h"

//! The points of an axis

class BA_CORE_API_ AxisDouble : public IAxis
{
public:
    //! constructors
    AxisDouble(std::string name);
    AxisDouble(std::string name, size_t size, double start, double end);

    //! explicit conversion from BinAxis
    explicit AxisDouble(const AxisBin& source);

    virtual AxisDouble *clone() const;

    virtual AxisDouble *createDoubleBinSize() const;

    //! destructor
    virtual ~AxisDouble() {}

    virtual size_t getSize() const { return m_sample_vector.size(); }

    //! Adds point to the end of the axis
    void push_back(double element) { m_sample_vector.push_back(element); }

    virtual double operator[](size_t index) const { return m_sample_vector[index]; }

    virtual Bin1D getBin(size_t index) const;

    //! Returns value of first point of axis
    virtual double getMin() const { return m_sample_vector.front(); }

    //! Returns value of last point of axis
    virtual double getMax() const { return m_sample_vector.back(); }

    //! Initializes axis points
    void initElements(size_t size, double start, double end);

    //! find number of bin which is closest to given value
    virtual size_t findClosestIndex(double value) const;

    //! find the index that corresponds to the given lower bound (index is inclusive)
    size_t getLowerBoundIndex(double value) const;

    //! find the index that corresponds to the given upper bound (index is inclusive)
    size_t getUpperBoundIndex(double value) const;

    //! returns vector containing the axis points
    std::vector<double> getVector() const { return m_sample_vector; }

protected:
    virtual bool equals(const IAxis& other) const;

private:
    std::vector<double> m_sample_vector;  //!< vector containing the axis points
    double m_bin_size;
};

#endif /* AXISDOUBLE_H_ */


