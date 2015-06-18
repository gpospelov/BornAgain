// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/IComponentLocator.h
//! @brief     Defines interface IComponentLocator.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ICOMPONENTLOCATOR_H
#define ICOMPONENTLOCATOR_H

#include "WinDllMacros.h"
#include <boost/shared_ptr.hpp>

class IFormFactor;

//! @class IComponentLocator
//! @ingroup simulation_internal
//! @brief Interface to the class which provides client with objects he needs

class BA_CORE_API_ IComponentLocator
{
public:
    virtual IFormFactor *getFormFactor() { return 0;}

};

typedef boost::shared_ptr<class IComponentLocator > ComponentLocator_t;

/*
 *
 *

class IComponentProvider {
    IComponentLocator *createLocator();
};

// FormFactorComponentProvider, DistributionsCOmponentProvider

TestFormFactorRegistry {
    std::map<string, IFormFactor *> map;
    map["CLone"] = new FormFactorClone(1.0);

    it->value->clone();
    }
}


std::vector<Creator *>;

class Creator {
    std::map<string, IFormFactor *>:: iterator m_it;
    IComponentLocator *locator createLocator
}

for(provider::iterator it=provider.begin(); it!= provider.end())

    ILOcator *locator it->createLocator();


class FunctionalTestAssmbler {

    IFunctionalTest *getTest(test_name) {
        TestInfo info = TestInfoRegistry::get(test_name);
        std::string m_simulation_name = TestInfo.m_simulation_name;
        std::string m_sample_builder_name;
        std::string m_component_provider_name;

        Simulation *simulation = SimulationRegistry::createSimulation(m_simulation_name);
        SampleBuilder *builder = SampleBuidlerFactory::createBuilder(m_sample_builder_name);
        simulatyion->setBuilder(builder);
        IntensityData *reference = getFromSomewhere();
        return new FunctionalTest(m_test_name, simulation, reference);
    }


    IFunctionalTest *getTest(test_name) {
        ComponentProvider provider = ProviderRegistry::getComponentProvider();
        for(int i=0; i<provider.getN(); i++) {

            ICOmponentLocator *locator = provider->createLocvator();

            SampleBuilder *builder = SampleBuidlerFactory::createBuilder(m_sample_builder_name);
            builder->init_from(locator);
            simulatyion->setBuilder(builder);


        }
            return new FunctionalMultiTest(m_test_name, simulation, provider, builder, reference);

    }

};


class FunctionalTest {
    FunctionalTest(std::string &name, Simulation *simulation, IntensityData *reference)
    void runSimulation();
    int analyseResults();
};

class FunctionalMultiTest {
    FunctionalMultiTest(string name, SampleBuilder *builder, Simulation *simulation, IComponentProvider);
    FunctionalMultiTest(FunctionalTestComponentLocator);

    void runTest() {
    for(FunctionalTestComponentLocator::iterator it=begin(); it!=end(); ++it) {
        Simulation *it->getSimulation();

    }

};





int RUN_FUNCTIONAL_TEST(name) {
    FunctionalTest *test = Assembler::getTest(name);
}

*/

#endif /* ICOMPONENTLOCATOR_H */
