// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/ParameterPool.h
//! @brief     Declares class ParameterPool.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARAMETERPOOL_H
#define PARAMETERPOOL_H

#include <functional>
#include <ostream>
#include <string>
#include <vector>

class AttLimits;
class RealParameter;

//! @class ParameterPool
//! @ingroup tools_internal
//! @brief Holds a map of pointers to parameters (which must have different names).

class BA_CORE_API_ ParameterPool
{
public:
    explicit ParameterPool(const std::string& name, const std::function<void()>& onChange);
    ParameterPool(const ParameterPool&) = delete;
    ParameterPool& operator=(const ParameterPool&) = delete;
    virtual ~ParameterPool();

    //! Returns a literal clone.
    ParameterPool* clone() const;

    //! Returns a clone with _prefix_ added to every parameter key.
    ParameterPool* cloneWithPrefix(const std::string& prefix) const;

    //! Copies parameters to _external_pool_, adding _prefix_ to every key.
    void copyToExternalPool(const std::string& prefix, ParameterPool* external_pool) const;

    //! Deletes parameter map.
    void clear();

    std::string getName() const { return m_name; }

    //! Returns number of parameters in the pool.
    size_t size() const { return m_params.size(); }

    //! Adds parameter to the pool
    void addParameter(RealParameter* par);

    //! Returns parameter named _name_.
    RealParameter* getParameter(const std::string& name);

    //! Returns parameter named _name_.
    const RealParameter* getParameter(const std::string& name) const;

    //! Returns vector of parameters which fit pattern
    std::vector<RealParameter*> getMatchedParameters(const std::string& wildcards) const;

    //! Sets parameter value
    void setParameterValue(const std::string& name, double value);

    //! Sets parameter value, return number of changed parameters
    int setMatchedParametersValue(const std::string& wildcards, double value);

    //! Returns all parameter names
    std::vector<std::string> getParameterNames() const;

    friend std::ostream& operator<<(std::ostream& ostr, const ParameterPool& obj) {
        obj.print(ostr); return ostr; }

protected:
    //! Called from RealParameter, calls back to owning IParameterized.
    void onChange() const { m_onChange(); }

private:
    //! Prints parameter pool contents.
    virtual void print(std::ostream& ostr) const;

    //! prints error message
    std::string get_error_message(const std::string& criteria) const;

    //! reports error while finding parameters matching given name
    void report_find_matched_parameters_error(const std::string& pattern) const;

    //! reports error while setting parname to given value
    void report_set_value_error(const std::string& parname, double value) const;

    //! The name of this pool, ought to be the name of the owning IParameterized.
    std::string m_name;

    //! The parameters in this pool.
    std::vector<RealParameter*> m_params;

    //!< Callback to the owning IParameterized, called whenever a parameter has changed.
    std::function<void()> m_onChange;

    friend RealParameter; //!< allow call of onChange().
};

#endif // PARAMETERPOOL_H
