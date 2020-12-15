// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_QUICKSIMEDITOR_PROFILEHELPER_H
#define DAREFL_QUICKSIMEDITOR_PROFILEHELPER_H

#include <darefl/darefl_export.h>
#include <minikernel/Computation/Slice.h>
#include <utility>
#include <vector>

//! Object that can generate the material profile of a sample as a function of depth.
namespace DaRefl {

class DAREFLCORE_EXPORT ProfileHelper {
public:
    ProfileHelper(const std::vector<BornAgain::Slice>& sample);
    ~ProfileHelper();

    std::vector<complex_t> calculateProfile(const std::vector<double>& z_values) const;
    std::pair<double, double> defaultLimits() const;

private:
    std::vector<complex_t> m_materialdata;
    std::vector<double> m_zlimits;
    std::vector<double> m_sigmas;
};

} // namespace DaRefl

#endif // DAREFL_QUICKSIMEDITOR_PROFILEHELPER_H
