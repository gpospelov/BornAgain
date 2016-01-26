// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/IAxis.h
//! @brief     Defines class IAxis.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IAXIS_H_
#define IAXIS_H_

#include "Bin.h"

//! @class IAxis
//! @ingroup tools_internal
//! @brief Interface for one-dimensional axes

class BA_CORE_API_ IAxis
{
public:
    //! constructors
    IAxis(const std::string &name) : m_name(name) {}

    //! clone function
    virtual IAxis *clone() const=0;

    //! Creates a new axis with half the number of bins
    virtual IAxis *createDoubleBinSize() const;

    //! destructor
    virtual ~IAxis() {}

    //! retrieve the number of bins
    virtual size_t getSize() const=0;

    //! retrieve the label of the axis
    std::string getName() const { return m_name; }

    //! Sets the axis label
    void setName(std::string name) { m_name = name; }

    //! indexed accessor retrieves a sample
    virtual double operator[](size_t index) const=0;

    //! retrieve a 1d bin for the given index
    virtual Bin1D getBin(size_t index) const=0;

    //! Returns value of first point of axis
    virtual double getMin() const=0;

    //! Returns value of last point of axis
    virtual double getMax() const=0;

    virtual double getBinCenter(size_t index) const=0;

    //! find bin index which is best match for given value
    virtual size_t findClosestIndex(double value) const=0;

    //! test for equality
    friend bool operator==(const IAxis& left, const IAxis& right);

    friend std::ostream& operator<<(std::ostream& ostr, const IAxis& m)
    { m.print(ostr); return ostr; }

    virtual std::vector<double > getBinCenters() const;

    virtual  std::vector<double > getBinBoundaries() const;

    //! Creates a new clipped axis
    virtual IAxis *createClippedAxis(double left, double right) const;

    //! Returns true if axis contains given point
    virtual bool contains(double value) const;

protected:
    virtual void print(std::ostream& ostr) const=0;
    virtual bool equals(const IAxis& other) const;
    std::string m_name;  //!< axis label

private:
    IAxis(const IAxis& );
    IAxis& operator=(const IAxis& );
};

inline IAxis *IAxis::createDoubleBinSize() const
{
    throw Exceptions::NotImplementedException("IAxis::createDoubleBinSize() -> Error. Not implemented.");
}

inline bool IAxis::equals(const IAxis& other) const
{
    return getName()==other.getName();
}

inline bool operator==(const IAxis& left, const IAxis& right) {
    return left.equals(right);
}

inline bool operator!=(const IAxis& left, const IAxis& right) {
    return !(left == right);
}

inline std::vector<double> IAxis::getBinCenters() const
{
    throw Exceptions::NotImplementedException("IAxis::getBinCenters() -> Error. Not implemented.");
}

inline std::vector<double> IAxis::getBinBoundaries() const
{
    throw Exceptions::NotImplementedException("IAxis::getBinBoundaries() -> Error. Not implemented.");
}

inline IAxis *IAxis::createClippedAxis(double /* left */, double /* right */) const
{
    throw Exceptions::NotImplementedException("IAxis::createClippedAxis() -> Error. Not implemented.");
}

inline bool IAxis::contains(double value) const
{
    return (value >= getMin() && value < getMax());
}


//! global helper function for comparison of axes
inline bool HaveSameNameAndShape(const IAxis& left, const IAxis& right)
{
    return left == right;
}

#endif /* IAXIS_H_ */


