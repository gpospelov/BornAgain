#include "Detector.h"
#include "Exceptions.h"

Detector::Detector()
: mp_detector_resolution(0)
{
    setName("Detector");
    init_parameters();
}

Detector::~Detector()
{
}

void Detector::addAxis(const NamedVector<double> &axis)
{
	m_axes.push_back(axis);
}

NamedVector<double> Detector::getAxis(size_t index) const
{
	if (isCorrectAxisIndex(index)) {
		return m_axes[index];
	}
	throw OutOfBoundsException("Not so many axes in this detector.");
}

void Detector::clear()
{
    m_axes.clear();
}

void Detector::applyDetectorResolution(
        OutputData<double>* p_intensity_map) const
{
    if (mp_detector_resolution) {
        mp_detector_resolution->applyDetectorResolution(p_intensity_map);
    }
}

std::string Detector::addParametersToExternalPool(std::string path,
        ParameterPool* external_pool, int copy_number) const
{
    // add own parameters
    std::string  new_path = IParameterized::addParametersToExternalPool(path, external_pool, copy_number);

    // add parameters of the resolution function
    if( mp_detector_resolution )  {
        mp_detector_resolution->addParametersToExternalPool(new_path, external_pool, -1);
    }

    return new_path;
}

void Detector::init_parameters()
{
}
