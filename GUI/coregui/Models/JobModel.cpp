#include "JobModel.h"

#include "Simulation.h"

JobModel::JobModel(Simulation *p_simulation)
    : mp_simulation(p_simulation)
{
}

JobModel::~JobModel()
{
    delete mp_simulation;
}

void JobModel::run()
{
    mp_simulation->runSimulation();
}
