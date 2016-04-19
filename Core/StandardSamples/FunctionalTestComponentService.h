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

#include "IComponentService.h"
#include "FunctionalTestRegistry.h"
#include <vector>
#include <string>

class IFormFactor;
class GISASSimulation;
class TestFormFactorsRegistry;
class TestFTDistribution2DRegistry;
class IFunctionalTest;

//! @class FunctionalTestComponentService
//! @ingroup standard_samples
//! @brief Contains all necessary information to compose functional test.

class BA_CORE_API_ FunctionalTestComponentService : public IComponentService
{
public:
    FunctionalTestComponentService(const FunctionalTestInfo &info);
    virtual ~FunctionalTestComponentService();

    virtual IFormFactor *getFormFactor() const;
    virtual IFTDistribution2D *getFTDistribution2D() const;
    virtual GISASSimulation *getSimulation() const;
    virtual SampleBuilder_t getSampleBuilder() const;
    virtual OutputData<double> *getReferenceData() const;
    virtual IFunctionalTest *getFunctionalTest() const;

    size_t getNumberOfComponents() const;
    void initComponent(size_t component_index);
    std::string getCurrentComponentName() const;

    std::string getReferenceFileName() const;
    FunctionalTestInfo getTestInfo() const;

protected:
    void init_registry(const std::string &registry_name);
    std::string getTestName() const;
    std::string getTestDescription() const;
    double getTestThreshold() const;

    FunctionalTestInfo m_testInfo;
    IFormFactor *m_form_factor;
    IFTDistribution2D *m_ft_distribution_2d;

    TestFormFactorsRegistry *m_ff_registry;
    TestFTDistribution2DRegistry *m_ft2d_registry;
    std::vector<std::string> m_component_names;
    size_t m_current_component;
};

#endif
