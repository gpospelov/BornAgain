#include "Detector.h"
#include "AxisBin.h"
#include "AxisDouble.h"


/* ************************************************************************* */
// c-tors, assignment operators, swap
/* ************************************************************************* */
Detector::Detector()
: m_axes(), mp_detector_resolution(0)
{
    setName("Detector");
    init_parameters();
}


Detector::Detector(const Detector &other) : IParameterized()
, m_axes(other.m_axes), mp_detector_resolution(0)
{
    setName(other.getName());
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
void Detector::addAxis(const IAxis &axis)
{
	m_axes.push_back(axis.clone());
}

void Detector::addAxis(const AxisParameters &axis_params)
{
    IAxis *p_new_axis(0);
    switch (axis_params.m_sample_method)
    {
    case AxisParameters::E_DEFAULT:
    {
        p_new_axis = new AxisBin(axis_params.m_name, axis_params.m_range.getNSamples(),
                axis_params.m_range.getMin(), axis_params.m_range.getMax());
        break;
    }
    case AxisParameters::E_ISGISAXS:
    {
        AxisDouble *p_axis = new AxisDouble(axis_params.m_name);
        initializeAnglesIsgisaxs(p_axis, axis_params.m_range);
        p_new_axis = p_axis;
        break;
    }
    default:
        throw RuntimeErrorException("Invalid sample method for axis.");
    }
    if (p_new_axis) m_axes.push_back(p_new_axis);
}

const IAxis &Detector::getAxis(size_t index) const
{
	if (isCorrectAxisIndex(index)) {
		return *m_axes[index];
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

void Detector::initializeAnglesIsgisaxs(AxisDouble* p_axis, const TSampledRange<double>& axis_range) const
{
    double start_sin = std::sin(axis_range.getMin());
    double end_sin = std::sin(axis_range.getMax());
    double step = (end_sin-start_sin)/(axis_range.getNSamples()-1);
    for(size_t i=0; i<axis_range.getNSamples(); ++i) {
        p_axis->push_back(std::asin(start_sin + step*i));
    }
}
