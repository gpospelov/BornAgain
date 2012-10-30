#include "IFittingDataSelector.h"
#include "Exceptions.h"

void DefaultAllDataSelector::getFittingData(const OutputData<double>& real_data,
        const OutputData<double>& simulated_data,
        std::vector<double>& real_data_vector,
        std::vector<double>& simulated_data_vector,
        std::vector<double>& weights) const
{
    size_t data_size = real_data.getAllocatedSize();
    if (simulated_data.getAllocatedSize()!=data_size) {
        throw RuntimeErrorException("Size of simulated data should be equal to the size of real data.");
    }
    real_data_vector.resize(data_size);
    simulated_data_vector.resize(data_size);
    weights.resize(data_size, 1.0);
    real_data_vector = real_data.getRawDataVector();
    simulated_data_vector = simulated_data.getRawDataVector();
    return;
}
