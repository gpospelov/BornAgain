#ifndef QUICKSIMULATIONHELPER_H
#define QUICKSIMULATIONHELPER_H

#include <QString>
class Simulation;
class MultiLayer;
class Instrument;
class SampleModel;
class InstrumentModel;

//! The QuickSimulationBuilder class is a static class with various helper
//! functions for QuickSimulation widgets.
//! Provides generation of domain simulations out of GUI models during sample
//! and instrument real time tuning.
class QuickSimulationHelper
{
public:


    static Simulation *getSimulation(SampleModel *sampleModel, const QString &sample_name, InstrumentModel *instrumentModel, const QString &instrument_name);

    static Instrument *getInstrument(InstrumentModel *instrumentModel, const QString &instrument_name);

    static MultiLayer *getMultiLayer(SampleModel *sampleModel, const QString &sample_name);

};


#endif
