#include <iostream>
#include "GUIFunctionalTest.h"
//#include "SimulationRegistry.h"
//#include "GUIObjectBuilder.h"
//#include "SessionModel.h"
//#include "MaterialEditor.h"
//#include "MaterialModel.h"
//#include "Instrument.h"
//#include "DomainObjectBuilder.h"
//#include "ParameterizedItem.h"


//int test()
//{

//    SimulationRegistry sim_registry;
//    Simulation *simulation = sim_registry.createSimulation("isgisaxs01");
//    simulation->runSimulation();

//    Instrument *instrument = new Instrument(simulation->getInstrument());
//    ISample *sample = simulation->getSample()->clone();

//    OutputData<double> *data = simulation->getIntensityData();
//    std::cout << data->totalSum();

//    //
//    SessionModel *sampleModel = new SessionModel(SessionXML::SampleModelTag);
//    SessionModel *instrumentModel = new SessionModel(SessionXML::InstrumentModelTag);

//    MaterialModel *materialModel = new MaterialModel();
//    MaterialEditor *materialEditor = new MaterialEditor(materialModel);

//    GUIObjectBuilder guiBuilder;
//    guiBuilder.populateSampleModel(sampleModel, sample);
//    guiBuilder.populateInstrumentModel(instrumentModel, instrument);


//    // building sample back
//    QModelIndex sampleIndex = sampleModel->index(0, 0, QModelIndex());
//    ParameterizedItem *sampleItem = sampleModel->itemForIndex(sampleIndex);
//    Q_ASSERT(sampleItem);
//    DomainObjectBuilder builder;
//    MultiLayer *new_sample = builder.buildMultiLayer(*sampleItem);
//    new_sample->printSampleTree();

//    // building multilayer back
//    QModelIndex instrumentIndex = instrumentModel->index(0, 0, QModelIndex());
//    ParameterizedItem *instrumentItem = sampleModel->itemForIndex(instrumentIndex);
//    Q_ASSERT(sampleItem);
//    Instrument *new_instrument = builder.buildInstrument(*instrumentItem);

//    // running simulation again
//    Simulation *new_simulation = new Simulation;
//    new_simulation->setSample(*new_sample);
//    new_simulation->setInstrument(*new_instrument);

//    new_simulation->runSimulation();
//    OutputData<double> *new_data = new_simulation->getIntensityData();
//    std::cout << new_data->totalSum();

//    return 0;
//}

int main()
{
    return GUI_FUNCTIONAL_TEST("isgisaxs01");
}


