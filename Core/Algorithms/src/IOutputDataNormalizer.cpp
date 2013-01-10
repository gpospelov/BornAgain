#include "IOutputDataNormalizer.h"
#include <algorithm>
#include <iostream>


OutputDataNormalizerScaleAndShift::OutputDataNormalizerScaleAndShift()
    : m_scale(1.0)
    , m_shift(0)
    , m_max_intensity(0)
{
    setName("Normalizer");
    init_parameters();
}

OutputDataNormalizerScaleAndShift::OutputDataNormalizerScaleAndShift(double scale, double shift)
    : m_scale(scale)
    , m_shift(shift)
    , m_max_intensity(0)
{
    setName("Normalizer");
    init_parameters();
}

OutputDataNormalizerScaleAndShift::OutputDataNormalizerScaleAndShift(const OutputDataNormalizerScaleAndShift &other)
{
    m_scale = other.m_scale;
    m_shift = other.m_shift;
    m_max_intensity = other.m_max_intensity;
}


OutputDataNormalizerScaleAndShift *OutputDataNormalizerScaleAndShift::clone() const
{
    return new OutputDataNormalizerScaleAndShift(*this);
}

void  OutputDataNormalizerScaleAndShift::init_parameters()
{
    getParameterPool()->clear();
    getParameterPool()->registerParameter("scale", &m_scale);
    getParameterPool()->registerParameter("shift", &m_shift);
}


OutputData<double> *OutputDataNormalizerScaleAndShift::createNormalizedData(const OutputData<double > &data) const
{
    OutputData<double > *normalized_data = data.clone();

    double max_intensity = m_max_intensity;
    if( max_intensity == 0 ) {
        OutputData<double >::const_iterator cit = std::max_element(data.begin(), data.end());
        max_intensity = (*cit);
    }
    if(max_intensity == 0) throw LogicErrorException("OutputDataNormalizerScaleAndShift::createNormalizedData() -> Error! Zero maximum intensity");
    OutputData<double >::iterator it = normalized_data->begin();
    while(it!=normalized_data->end()) {
        double value = (*it);
        (*it) = m_scale*(value/max_intensity) + m_shift;
        ++it;
    }

    return normalized_data;
}
