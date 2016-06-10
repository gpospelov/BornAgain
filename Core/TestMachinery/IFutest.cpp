// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/IFutest.cpp
//! @brief     Implements class IFutest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IFutest.h"
#include "Utils.h"
#include <sstream>

namespace {

std::map<IFutest::ETestResult, std::string> InitTestResultToString()
{
    std::map<IFutest::ETestResult, std::string> result;
    result[IFutest::SUCCESS] = "[SUCCESS]";
    result[IFutest::FAILED_DIFF] = "[FAILED_DIFF]";
    result[IFutest::FAILED_NOREF] = "[FAILED_NOREF]";
    result[IFutest::FAILED] = "[FAILED]";
    return result;
}

const size_t width_name = 25;
const size_t width_description = 40;
const size_t width_result = 15;

} // namespace

std::map<IFutest::ETestResult, std::string> IFutest::m_result_to_string = InitTestResultToString();

IFutest::IFutest()
    : m_result(SUCCESS)
{
}

IFutest::IFutest(const std::string& name, const std::string& description)
    : INamed(name)
    , m_description(description)
    , m_result(SUCCESS)
{
}

std::string IFutest::getTestResultString() const
{
	return m_result_to_string[m_result];
}

std::string IFutest::getFormattedInfoString() const
{
    std::ostringstream ostr;
    ostr << Utils::AdjustStringLength(getName(), width_name);
    ostr << Utils::AdjustStringLength(getDescription(), width_description);
    ostr << Utils::AdjustStringLength(getTestResultString(), width_result);
    return ostr.str();
}
