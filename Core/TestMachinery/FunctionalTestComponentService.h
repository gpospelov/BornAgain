// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/FunctionalTestComponentService.h
//! @brief     Declares class FunctionalTestComponentService.
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

#include "WinDllMacros.h"
#include "OutputData.h"
#include "ISampleBuilder.h"

class IFormFactor;
class IFTDistribution2D;
class GISASSimulation;
class TestFormFactorsRegistry;
class TestFTDistribution2DRegistry;
class FunctionalTestInfo;
class IFunctionalTest;

//! @class FunctionalTestComponentService
//! @ingroup standard_samples
//! @brief Contains all necessary information to compose functional test.

class BA_CORE_API_ FunctionalTestComponentService
{
public:
    FunctionalTestComponentService(const FunctionalTestInfo* info);
    virtual ~FunctionalTestComponentService();

    virtual IFormFactor* getFormFactor() const;
    virtual IFTDistribution2D* getFTDistribution2D() const;
    virtual GISASSimulation* getSimulation() const;
    virtual std::shared_ptr<class ISampleBuilder> getSampleBuilder() const;
    virtual OutputData<double>* getReferenceData() const;
    virtual IFunctionalTest* getFunctionalTest() const = 0;

    size_t getNumberOfComponents() const { return m_component_names.size(); }
    void initComponent(size_t component_index);
    std::string getCurrentComponentName() const;

    std::string getReferenceFileName() const;
    const FunctionalTestInfo* getTestInfo() const { return m_testInfo; }

protected:
    void init_registry(const std::string& registry_name);
    std::string getTestName() const;
    std::string getTestDescription() const;
    double getTestThreshold() const;

    const FunctionalTestInfo* m_testInfo;
    IFormFactor* m_form_factor;
    IFTDistribution2D* m_ft_distribution_2d;

    TestFormFactorsRegistry* m_ff_registry;
    TestFTDistribution2DRegistry* m_ft2d_registry;
    std::vector<std::string> m_component_names;
    size_t m_current_component;
};

#endif
