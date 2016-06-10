// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/FutestSuite.h
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
//! @class FutestSuite
//! @ingroup standard_samples
//! @brief Contains all necessary information to compose functional test.

class BA_CORE_API_ FutestSuite : public INamed
{
public:
    typedef class IFutest* (*get_futest_t) (const FutestSuite*);
    FutestSuite(const std::string& name, get_futest_t functionalTest);
    virtual ~FutestSuite();

    int execute(int argc, char** argv);
    class IFutest* getFutest() const { return (*m_functionalTest)(this); }
    virtual class IFormFactor* getFormFactor() const;
    virtual class IFTDistribution2D* getFTDistribution2D() const;
    virtual class GISASSimulation* getSimulation() const;
    virtual std::shared_ptr<class ISampleBuilder> getSampleBuilder() const;
    virtual OutputData<double>* getReferenceData() const;

    size_t getNumberOfComponents() const { return m_component_names.size(); }

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
    std::vector<std::string> m_component_names;
    size_t m_current_component;
    get_futest_t m_functionalTest;
};

#endif
