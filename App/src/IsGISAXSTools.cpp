#include "IsGISAXSTools.h"

#include <cmath>

complex_t transmission_fresnel(double alpha_i)
{
    (void)alpha_i;
    return complex_t(1.0, 0.0);
}

// For IsGISAXS comparison:
void initialize_angles_sine(NamedVector<double> *p_axis, double start, double end, size_t size) {
	double start_sin = std::sin(start*M_PI/180);
	double end_sin = std::sin(end*M_PI/180);
	double step = (end_sin-start_sin)/(size-1);
	for(size_t i=0; i<size; ++i) {
		p_axis->push_back(std::asin(start_sin + step*i)*180/M_PI);
	}
	return;
}

ReflectionFresnelFunctionWrapper* ReflectionFresnelFunctionWrapper::clone() const
{
    return new ReflectionFresnelFunctionWrapper(m_refraction_index);
}

complex_t ReflectionFresnelFunctionWrapper::reflection_fresnel(double alpha_i, complex_t refraction_index)
{
    complex_t cos_alpha_0_squared = std::cos(alpha_i)*std::cos(alpha_i);
    complex_t f0 = std::sqrt(complex_t(1.0, 0.0) - cos_alpha_0_squared);
    complex_t f1 = std::sqrt(refraction_index*refraction_index - cos_alpha_0_squared);
    return (f0 - f1)/(f0 + f1);
}

