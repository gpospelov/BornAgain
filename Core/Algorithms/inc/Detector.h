// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/Detector.h
//! @brief     Defines class Detector.
//!
//! @homepage  apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef DETECTOR_H_
#define DETECTOR_H_

#include "IDetectorResolution.h"
#include "DetectorParameters.h"
#include "IParameterized.h"
#include "SafePointerVector.h"

#include <vector>

//- -------------------------------------------------------------------
//! @class Detector
//! @brief Definition of Detector with axes and resolution function
//- -------------------------------------------------------------------
class Detector : public IParameterized
{
public:
	Detector();
    Detector(const Detector &other);
    Detector &operator=(const Detector &other);

	virtual ~Detector();

	void addAxis(const IAxis &axis);
	void addAxis(const AxisParameters &axis_params);
	const IAxis &getAxis(size_t index) const;
	size_t getDimension() const { return m_axes.size(); }
	void clear();
    void setDetectorResolution(IDetectorResolution *p_detector_resolution) { delete mp_detector_resolution; mp_detector_resolution = p_detector_resolution; }
	void applyDetectorResolution(OutputData<double> *p_intensity_map) const;
    const IDetectorResolution *getDetectorResolutionFunction() const { return mp_detector_resolution; }

	//! add parameters from local pool to external pool and call recursion over direct children
    virtual std::string addParametersToExternalPool(std::string path, ParameterPool *external_pool, int copy_number=-1) const;

    //! normalize intensity data with detector cell sizes
    void normalize(OutputData<double> *p_data, double sin_alpha_i) const;
protected:
    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();
	bool isCorrectAxisIndex(size_t index) const { return index<getDimension(); }

	//! check if data has a compatible format with the detector
    bool dataShapeMatches(const OutputData<double> *p_data) const;

private:
    //! swap function
    void swapContent(Detector &other);

    //! initialize axis the way IsGISAXS does
    void initializeAnglesIsgisaxs(AxisDouble *p_axis, const TSampledRange<double> &axis_range) const;

    //! calculate the solid angle for the given data element
    double getSolidAngle(OutputData<double> *p_data, size_t index) const;

    SafePointerVector<IAxis> m_axes;
	IDetectorResolution *mp_detector_resolution;
};

#endif /* DETECTOR_H_ */
