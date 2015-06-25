// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/FunctionalTestComponentService.h
//! @brief     Defines class FunctionalTestComponentService.
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
class IFunctionalTest;

//! @class FunctionalTestComponentService
//! @ingroup standard_samples
//! @brief Contains all necessary information to compose functional test.

class FunctionalTestComponentService : public IComponentService
{
public:

    FunctionalTestComponentService(const FunctionalTestInfo &info);
    ~FunctionalTestComponentService();

    IFormFactor *getFormFactor() const;
    GISASSimulation *getSimulation() const;
    SampleBuilder_t getSampleBuilder() const;
    OutputData<double> *getReferenceData() const;
    IFunctionalTest *getFunctionalTest() const;

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
    TestFormFactorsRegistry *m_ff_registry;
    std::vector<std::string> m_component_names;
    size_t m_current_component;
};


#endif

