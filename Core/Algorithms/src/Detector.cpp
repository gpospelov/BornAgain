#include "Detector.h"

#include "AxisBin.h"
#include "AxisDouble.h"
#include "ExperimentConstants.h"


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

bool Detector::dataShapeMatches(const OutputData<double>* p_data) const
{
    if (p_data->getRank() != getDimension()) return false;
    for (size_t i=0; i<getDimension(); ++i) {
        const IAxis *p_data_axis = p_data->getAxis(i);
        const IAxis &detector_axis = getAxis(i);
        if (detector_axis != *p_data_axis) return false;
    }
    return true;
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

void Detector::normalize(OutputData<double>* p_data, double sin_alpha_i) const
{
    // if shapes do not match, do nothing
    if (!dataShapeMatches(p_data)) return;

    // if not a 2d detector, do nothing
    if (p_data->getRank()!=2) return;

    // if not a gisas detector, do nothing
    const IAxis *p_alpha_axis = p_data->getAxis(NDetector2d::ALPHA_AXIS_NAME);
    const IAxis *p_phi_axis = p_data->getAxis(NDetector2d::PHI_AXIS_NAME);
    if (!p_alpha_axis || !p_phi_axis) return;

    // GISAS normalization
    // This normalization assumes that the intensity map contains total differential scattering cross sections
    // (so not the cross section per scattering particle as is usual)
    for (OutputData<double>::iterator it = p_data->begin(); it != p_data->end(); ++it) {
        double factor = getSolidAngle(p_data, it.getIndex())/sin_alpha_i;
        (*it) *= factor;
    }
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

double Detector::getSolidAngle(OutputData<double>* p_data, size_t index) const
{
    const IAxis *p_alpha_axis = p_data->getAxis(NDetector2d::ALPHA_AXIS_NAME);
    const IAxis *p_phi_axis = p_data->getAxis(NDetector2d::PHI_AXIS_NAME);
    size_t alpha_index = p_data->getIndexOfAxis(NDetector2d::ALPHA_AXIS_NAME, index);
    size_t alpha_size = p_alpha_axis->getSize();
    size_t phi_index = p_data->getIndexOfAxis(NDetector2d::PHI_AXIS_NAME, index);
    size_t phi_size = p_phi_axis->getSize();
    if (alpha_size<2 && phi_size<2) {
        // Cannot determine detector cell size!
        throw LogicErrorException("Experiment::getSolidAngle() -> Error! Can't determine size of detector cell.");
    }
    double dalpha(0), dphi(0);

    double alpha_f = p_data->getValueOfAxis(NDetector2d::ALPHA_AXIS_NAME, index);
    double cos_alpha_f = std::cos(alpha_f);

    if(alpha_size>1) {
        if (alpha_index==0) {
            dalpha = (*p_alpha_axis)[1] - (*p_alpha_axis)[0];
        }
        else if (alpha_index==alpha_size-1) {
            dalpha = (*p_alpha_axis)[alpha_size-1] - (*p_alpha_axis)[alpha_size-2];
        }
        else {
            dalpha = ((*p_alpha_axis)[alpha_index+1] - (*p_alpha_axis)[alpha_index-1])/2.0;
        }
        dalpha = std::abs(dalpha);
    } else {
        //std::cout << "Experiment::getSolidAngle() -> Warning! Only one bin on alpha_f axis, size of the bin will be taken from phi_f axis" << std::endl;
    }
    if(phi_size > 1) {
        if (phi_index==0) {
            dphi = (*p_phi_axis)[1] - (*p_phi_axis)[0];
        }
        else if (phi_index==phi_size-1) {
            dphi = (*p_phi_axis)[phi_size-1] - (*p_phi_axis)[phi_size-2];
        }
        else {
            dphi = ((*p_phi_axis)[phi_index+1] - (*p_phi_axis)[phi_index-1])/2.0;
        }
        dphi = std::abs(dphi);
    } else {
        //std::cout << "Experiment::getSolidAngle() -> Warning! Only one bin on phi_f axis, size of the bin will be taken from alpha_f axis" << std::endl;
    }
    if(!dalpha || !dphi) {
        std::cout << "Experiment::getSolidAngle() -> Warning! Not defined normalization" << std::endl;
        return 1;
    } else {
        return cos_alpha_f*dalpha*dphi;
    }
}
