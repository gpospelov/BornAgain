#include "GUIFunctionalTest.h"
#include "SimulationRegistry.h"
#include "GUIObjectBuilder.h"
#include "InstrumentModel.h"
#include "SampleModel.h"
#include "MaterialEditor.h"
#include "MaterialModel.h"
#include "Instrument.h"
#include "DomainObjectBuilder.h"
#include "ParameterizedItem.h"
#include "IntensityDataFunctions.h"
#include <boost/scoped_ptr.hpp>
#include <QDebug>


GUIFunctionalTest::GUIFunctionalTest(const std::string &name)
    : m_name(name)
    , m_threshold(2e-10)
    , m_reference_simulation(0)
    , m_domain_simulation(0)
{
    SimulationRegistry sim_registry;
    m_reference_simulation = sim_registry.createSimulation(m_name);
}


GUIFunctionalTest::~GUIFunctionalTest()
{
    delete m_reference_simulation;
    delete m_domain_simulation;
}


void GUIFunctionalTest::runTest()
{
    assert(m_reference_simulation);
    m_reference_simulation->runSimulation();

    createDomainSimulation();
    m_domain_simulation->runSimulation();
}


int GUIFunctionalTest::analyseResults()
{
    double diff = IntensityDataFunctions::getRelativeDifference(*m_domain_simulation->getOutputData(),*m_reference_simulation->getOutputData());

    std::cout << m_name<< " " << " " << diff
              << " " << (diff>m_threshold ? "[FAILED]" : "[OK]") << std::endl;

    if( diff > m_threshold ) return FAILED;
    return SUCCESS;

}



//! returns new simulation from
void GUIFunctionalTest::createDomainSimulation()
{
    assert(m_reference_simulation->getSample());
    // initializing necessary GUI
    boost::scoped_ptr<SampleModel> sampleModel(new SampleModel());
    boost::scoped_ptr<InstrumentModel> instrumentModel(new InstrumentModel());
    boost::scoped_ptr<MaterialModel> materialModel(new MaterialModel());
    boost::scoped_ptr<MaterialEditor> materialEditor(new MaterialEditor(materialModel.get()));

    // populating GUI models from domain
    boost::scoped_ptr<ISample> reference_sample(m_reference_simulation->getSample()->clone());
    boost::scoped_ptr<Instrument> reference_instrument(new Instrument(m_reference_simulation->getInstrument()));

    GUIObjectBuilder guiBuilder;
    guiBuilder.populateSampleModel(sampleModel.get(), reference_sample.get());
    guiBuilder.populateInstrumentModel(instrumentModel.get(), reference_instrument.get());

    // building sample back
    QModelIndex sampleIndex = sampleModel->index(0, 0, QModelIndex());
    ParameterizedItem *sampleItem = sampleModel->itemForIndex(sampleIndex);
    DomainObjectBuilder builder;
    MultiLayer *new_sample = builder.buildMultiLayer(*sampleItem);
    new_sample->printSampleTree();

    // building multilayer back
    QModelIndex instrumentIndex = instrumentModel->index(0, 0, QModelIndex());
    ParameterizedItem *instrumentItem = sampleModel->itemForIndex(instrumentIndex);
    Q_ASSERT(sampleItem);
    Instrument *new_instrument = builder.buildInstrument(*instrumentItem);

    // running simulation again
    m_domain_simulation = new Simulation;
    m_domain_simulation->setSample(*new_sample);
    m_domain_simulation->setInstrument(*new_instrument);
}


int GUI_FUNCTIONAL_TEST(const std::string &name)
{
    GUIFunctionalTest test(name);
    test.runTest();
    return test.analyseResults();
}

