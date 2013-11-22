#ifndef SIMULATIONREGISTRY_H
#define SIMULATIONREGISTRY_H

#include "IFactory.h"
#include "Simulation.h"

//! Factory to create standard pre-defined simulations.
//! Used in functional tests, performance measurements, etc.

class BA_CORE_API_ SimulationRegistry : public IFactory<std::string, Simulation>
{
public:
    SimulationRegistry();

    Simulation *createSimulation(const std::string& name);
};



#endif // SIMULATIONREGISTRY_H
