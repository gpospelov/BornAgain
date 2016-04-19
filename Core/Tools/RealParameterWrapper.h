// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/RealParameterWrapper.h
//! @brief     Declares class RealParameterWrapper.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef REALPARAMETERWRAPPER_H
#define REALPARAMETERWRAPPER_H

#include "WinDllMacros.h"
#include "Exceptions.h"
#include "AttLimits.h"

#include <ostream>


//! @class RealParameterWrapper
//! @ingroup tools_internal
//! @brief Wrapper to real parameter for remote access to its value and callback abilities

class BA_CORE_API_ RealParameterWrapper {
public:
    explicit RealParameterWrapper(double *par, const AttLimits &limits = AttLimits::limitless());
    RealParameterWrapper(const RealParameterWrapper& other );
    RealParameterWrapper& operator=(const RealParameterWrapper& other);

    //! Sets value of wrapped parameter and emit signal
    bool setValue(double value);

    //! Returns value of wrapped parameter
    double getValue() const;

    //! Returns true if wrapped parameter was not initialized with proper real value
    bool isNull() const;

    //! throw exception if parameter was not initialized with proper value
    void checkNull() const;

    //! Prints the parameter's address to an output stream
    friend std::ostream& operator<<(std::ostream& ostr, const RealParameterWrapper& p);

    AttLimits getAttLimits() const { return m_limits; }

    bool operator==(const RealParameterWrapper &other) const;
    bool operator!=(const RealParameterWrapper &other) const;

private:
    //! swap function
    void swapContent(RealParameterWrapper& other);

    volatile double *m_data;
    AttLimits m_limits;
};

inline double RealParameterWrapper::getValue() const
{
    checkNull();
    return *m_data;
}

inline bool RealParameterWrapper::isNull() const
{
    return (m_data ? false : true);
}

inline void RealParameterWrapper::checkNull() const
{
    if(isNull())
        throw NullPointerException(
                "RealParameterWrapper::getValue() -> Attempt to access uninitialised pointer.");
}

inline std::ostream &operator<<(std::ostream &ostr, const RealParameterWrapper &p)
{
    ostr << p.m_data; return ostr;
}

inline bool RealParameterWrapper::operator==(const RealParameterWrapper &other) const
{
    return (m_limits == other.m_limits) && (m_data == other.m_data);
}

inline bool RealParameterWrapper::operator!=(const RealParameterWrapper &other) const
{
    return !(*this == other);
}

#endif // REALPARAMETERPROXY_H
