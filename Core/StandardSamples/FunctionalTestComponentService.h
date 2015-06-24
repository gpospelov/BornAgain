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
#include "ISampleBuilder.h"
#include "AdvancedFunctionalTestRegistry.h"
#include <vector>
#include <string>

class IFormFactor;
class GISASSimulation;
class TestFormFactorsRegistry;


class FunctionalTestComponentService : public IComponentService
{
public:

    FunctionalTestComponentService(const AdvancedFunctionalTestInfo &info);

    ~FunctionalTestComponentService();

    IFormFactor *getFormFactor();
    GISASSimulation *getSimulation();
    OutputData<double> *getReferenceData();
    SampleBuilder_t getSampleBuilder();

    size_t getNumberOfComponents() const { return m_component_names.size(); }

    void setComponent(size_t current_component);

    std::string getReferenceFileName();

    double getThreshold() const;

    AdvancedFunctionalTestInfo getTestInfo() const;

    std::string getCurrentComponentName() const;

private:
    void init_registry(const std::string &registry_name);

    AdvancedFunctionalTestInfo m_testInfo;
    IFormFactor *m_form_factor;
    GISASSimulation *m_simulation;
    SampleBuilder_t m_sample_builder;
    TestFormFactorsRegistry *m_ff_registry;
    std::vector<std::string> m_component_names;
    size_t m_current_component;
};


#endif

