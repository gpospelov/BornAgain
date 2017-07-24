// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/IFunctionalTest.h
//! @brief     Defines and implements pure virtual base class IFunctionalTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IFUNCTIONALTEST_H
#define IFUNCTIONALTEST_H

#include "INamed.h"
#include <map>

//! Base class for all functional tests.
//! @class IFunctionalTest

class BA_CORE_API_ IFunctionalTest : public INamed
{
public:
    IFunctionalTest() {}
    IFunctionalTest(const std::string& name, const std::string& description)
        : INamed(name), m_description(description) {}
    virtual ~IFunctionalTest() {}

    virtual bool runTest() = 0; //!< Returns true when successful

    std::string getDescription() const { return m_description; }
    void setDescription(const std::string& description) { m_description = description; }

protected:
    std::string m_description;
};

#endif // IFUNCTIONALTEST_H
