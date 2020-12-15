// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <Sample/Slice/Slice.h>
#include <darefl/quicksimeditor/materialprofile.h>
#include <darefl/quicksimeditor/profilehelper.h>
#include <darefl/quicksimeditor/quicksimutils.h>

namespace DaRefl
{

std::vector<complex_t> MaterialProfile::CalculateProfile(const multislice_t& multilayer,
                                                         int n_points, double z_min, double z_max)
{
    auto baSlices = Utils::createBornAgainSlices(multilayer);
    ProfileHelper helper(baSlices);
    std::vector<double> z_values = GenerateZValues(n_points, z_min, z_max);
    return helper.calculateProfile(z_values);
}

std::pair<double, double>
MaterialProfile::DefaultMaterialProfileLimits(const multislice_t& multilayer)
{
    auto baSlices = Utils::createBornAgainSlices(multilayer);
    ProfileHelper helper(baSlices);
    return helper.defaultLimits();
}

std::vector<double> MaterialProfile::GenerateZValues(int n_points, double z_min, double z_max)
{
    std::vector<double> result;
    if (n_points < 1)
        return result;
    double step = n_points > 1 ? (z_max - z_min) / (n_points - 1) : 0.0;
    for (int i = 0; i < n_points; ++i) {
        result.push_back(z_min + i * step);
    }
    return result;
}

} // namespace DaRefl
