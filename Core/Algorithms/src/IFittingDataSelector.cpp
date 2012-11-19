#include "IFittingDataSelector.h"
#include "Exceptions.h"

OutputData<double> *DefaultAllDataSelector::createWeightMap(const OutputData<double>& real_data,
        const OutputData<double>& simulated_data) const
{

    if (simulated_data.getAllocatedSize() != real_data.getAllocatedSize()) {
        throw RuntimeErrorException("DefaultAllDataSelector::createWeightMap() -> Size of simulated data should be equal to the size of real data.");
    }
    OutputData<double> *p_result = real_data.clone();
    p_result->setAllTo(1.0);
    return p_result;
}
