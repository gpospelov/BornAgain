#include "SpecularData.h"

SpecularData::SpecularData() : data_type_used(DATA_TYPE::Invalid) {}

SpecularData::SpecularData(MatrixVector coefficients)
    : data(std::move(coefficients))
    , data_type_used(DATA_TYPE::Matrix)
{
}

SpecularData::SpecularData(ScalarVector coefficients)
    : data(std::move(coefficients))
    , data_type_used(DATA_TYPE::Scalar)
{
}

const ILayerRTCoefficients& SpecularData::operator[](size_t index) const
{
    if (data_type_used == DATA_TYPE::Invalid)
        throw std::runtime_error(
            "Error in SpecularData::operator[]: attempt to access uninitialized data");
    if (data_type_used == DATA_TYPE::Scalar) {
        const auto data_ptr = boost::get<ScalarVector>(&data);
        if (data_ptr->size() <= index)
            throw std::runtime_error("Error in SpecularData::operator[]: index exceeds data dimension");
        return (*data_ptr)[index];
    } else {
        const auto data_ptr = boost::get<MatrixVector>(&data);
        if (data_ptr->size() <= index)
            throw std::runtime_error("Error in SpecularData::operator[]: index exceeds data dimension");
        return (*data_ptr)[index];
    }
}

