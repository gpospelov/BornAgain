// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/IFunctionalTest.cpp
//! @brief     Implements class IFunctionalTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IFunctionalTest.h"
#include "Utils.h"
#include <sstream>

namespace {

std::map<IFunctionalTest::ETestResult, std::string> InitTestResultToString()
{
    std::map<IFunctionalTest::ETestResult, std::string> result;
    result[IFunctionalTest::SUCCESS] = "[SUCCESS]";
    result[IFunctionalTest::FAILED_DIFF] = "[FAILED_DIFF]";
    result[IFunctionalTest::FAILED_NOREF] = "[FAILED_NOREF]";
    result[IFunctionalTest::FAILED] = "[FAILED]";
    return result;
}

const size_t width_name = 25;
const size_t width_description = 40;
const size_t width_result = 15;

} // namespace

std::map<IFunctionalTest::ETestResult, std::string> IFunctionalTest::m_result_to_string =
    InitTestResultToString();

IFunctionalTest::IFunctionalTest()
    : m_result(SUCCESS)
{
}

IFunctionalTest::IFunctionalTest(const std::string& name, const std::string& description)
    : m_name(name)
    , m_description(description)
    , m_result(SUCCESS)
{
}

std::string IFunctionalTest::getTestResultString() const
{
	return m_result_to_string[m_result];
}

std::string IFunctionalTest::getFormattedInfoString() const
{
    std::ostringstream ostr;
    ostr << Utils::AdjustStringLength(getName(), width_name);
    ostr << Utils::AdjustStringLength(getDescription(), width_description);
    ostr << Utils::AdjustStringLength(getTestResultString(), width_result);
    return ostr.str();
}
