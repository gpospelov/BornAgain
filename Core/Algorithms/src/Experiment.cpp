#include "Experiment.h"

Experiment::Experiment()
: mp_sample(0)
{
}

Experiment::Experiment(ISample* p_sample)
: mp_sample(p_sample)
{
}

void Experiment::runSimulation()
{
}

void Experiment::setSample(ISample* p_sample)
{
	mp_sample = p_sample;  ///< Not owned by Experiment
}

void Experiment::setOutputData(OutputData<double>* p_data)
{
	mp_intensity_map = p_data;  ///< Not owned by Experiment
}
