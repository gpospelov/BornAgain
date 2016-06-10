// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      TestMachinery/FutestSuite.h
//! @brief     Declares class FutestSuite.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FUNCTIONALTESTCOMPONENTSERVICE_H
#define FUNCTIONALTESTCOMPONENTSERVICE_H

#include <vector>
#include <string>
#include <memory>

#include "WinDllMacros.h"
#include "OutputData.h"
#include "ISampleBuilder.h"
#include "ISingleton.h"

//! @class FutestSuite
//! @brief To execute one functional test of given name.

//! Used in functional tests CoreSuite, PydumpSuite, GUISuite, where it is
//! subclassed as a singleton. The only call is instance().execute(argc, argv).

//! When processing execute, dependent classes will call back getFutest().
//! Certain tests have subtests; they will call back getFormFactor() etc.

class BA_CORE_API_ FutestSuite : public INamed
{
public:
    FutestSuite();
    virtual ~FutestSuite();

    int execute(int argc, char** argv);
    virtual class IFutest* getFutest() const = 0;

    virtual class IFormFactor* getFormFactor() const;
    virtual class IFTDistribution2D* getFTDistribution2D() const;

protected:
    virtual class GISASSimulation* getSimulation() const;
    virtual std::shared_ptr<class ISampleBuilder> getSampleBuilder() const;
    virtual OutputData<double>* getReferenceData() const;

    std::string getReferenceFileName() const;
    const class FutestInfo* getTestInfo() const { return m_info; }

    std::string getTestName() const;
    std::string getTestDescription() const;
    double getTestThreshold() const;

    const class FutestInfo* m_info;
    class IFormFactor* m_formfactor;
    class IFTDistribution2D* m_ft_distribution_2d;

    class TestFormFactorsRegistry* m_ff_registry;
    class TestFTDistribution2DRegistry* m_ft2d_registry;
    size_t m_current_component;
    std::string m_subtest_name;
};

#endif
