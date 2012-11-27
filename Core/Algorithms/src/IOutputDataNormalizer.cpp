#include "IOutputDataNormalizer.h"
#include <algorithm>
#include <iostream>


OutputDataNormalizerScaleAndShift::OutputDataNormalizerScaleAndShift()
    : m_scale(1.0)
    , m_shift(0)
{
    setName("Normalizer");
    init_parameters();
}

OutputDataNormalizerScaleAndShift::OutputDataNormalizerScaleAndShift(double scale, double shift)
    : m_scale(scale)
    , m_shift(shift)
{
    setName("Normalizer");
    init_parameters();
}

OutputDataNormalizerScaleAndShift::OutputDataNormalizerScaleAndShift(const OutputDataNormalizerScaleAndShift &other) : IOutputDataNormalizer(other)
{
    m_scale = other.m_scale;
    m_shift = other.m_shift;
    init_parameters();
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

    OutputData<double >::const_iterator cit = std::max_element(data.begin(), data.end());
    double max_intensity = (*cit);
    std::cout << "QQQ before " << data.totalSum() << std::endl;
    if(max_intensity) {
        OutputData<double >::iterator it = normalized_data->begin();
        while(it!=normalized_data->end()) {
            double value = (*it);
            (*it) = m_scale*(value/max_intensity) + m_shift;
            ++it;
        }
        std::cout << "QQQ after " << normalized_data->totalSum() << std::endl;
    } else {
        std::cout << "OutputDataNormalizerScaleAndShift::createNormalizedData() -> Warning! Zero maximum intensity" << std::endl;
    }

    return normalized_data;
}
