#include "Detector.h"
#include "Exceptions.h"


/* ************************************************************************* */
// c-tors, assignment operators, swap
/* ************************************************************************* */
Detector::Detector()
: mp_detector_resolution(0)
{
    setName("Detector");
    init_parameters();
}


Detector::Detector(const Detector &other) : IParameterized()
, mp_detector_resolution(0)
{
    setName(other.getName());
    m_axes = other.m_axes;
    if(other.mp_detector_resolution) mp_detector_resolution = other.mp_detector_resolution->clone();
    init_parameters();
}


Detector::~Detector()
{
    delete mp_detector_resolution;
}

Detector &Detector::operator=(const Detector &other)
{
    if( this != &other) {
        Detector tmp(other);
        tmp.swapContent(*this);
    }
    return *this;
}

void Detector::swapContent(Detector &other)
{
    std::swap(this->m_axes, other.m_axes);
    std::swap(this->mp_detector_resolution, other.mp_detector_resolution);
}


/* ************************************************************************* */
// other methods
/* ************************************************************************* */
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

void Detector::applyDetectorResolution(OutputData<double>* p_intensity_map) const
{
    if(!p_intensity_map) {
        throw NullPointerException("Detector::applyDetectorResolution() -> Error! Null pointer to intensity map");
    }
    if (mp_detector_resolution) {
        mp_detector_resolution->applyDetectorResolution(p_intensity_map);
    } else {
//        std::cout << "Detector::applyDetectorResolution() -> Warning! No detector resolution function found" << std::endl;
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
