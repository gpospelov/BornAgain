#include "SpecularData.h"

SpecularData::SpecularData() : data_type_used(DATA_TYPE::Invalid) {}

SpecularData::SpecularData(MatrixVector coefficients)
    : data(std::move(coefficients))
    , data_type_used(DATA_TYPE::Matrix)
{}

SpecularData::SpecularData(ScalarVector coefficients)
    : data(std::move(coefficients))
    , data_type_used(DATA_TYPE::Scalar)
{}

SpecularData* SpecularData::clone()
{
    switch(data_type_used) {
    case DATA_TYPE::Invalid:
        return new SpecularData();
    case DATA_TYPE::Scalar:
        return new SpecularData(*boost::get<ScalarVector>(&data));
    case DATA_TYPE::Matrix:
        return new SpecularData(*boost::get<MatrixVector>(&data));
    }
    return nullptr;
}

const ILayerRTCoefficients& SpecularData::operator[](size_t index) const
{
    if (data_type_used == DATA_TYPE::Invalid)
        throw std::runtime_error(
            "Error in SpecularData::operator[]: attempt to access uninitialized data");
    if (data_type_used == DATA_TYPE::Scalar)
        return (*boost::get<ScalarVector>(&data))[index];
    else
        return (*boost::get<MatrixVector>(&data))[index];
}

