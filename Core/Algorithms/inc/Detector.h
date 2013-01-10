#ifndef DETECTOR_H_
#define DETECTOR_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   Detector.h
//! @brief  Definition of Detector class
//! @author Scientific Computing Group at FRM II
//! @date   Jun 21, 2012

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

protected:
    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();
	bool isCorrectAxisIndex(size_t index) const { return index<getDimension(); }
private:
    //! swap function
    void swapContent(Detector &other);

    //! initialize axis the way IsGISAXS does
    void initializeAnglesIsgisaxs(AxisDouble *p_axis, const TSampledRange<double> &axis_range) const;

    SafePointerVector<IAxis> m_axes;
	IDetectorResolution *mp_detector_resolution;
};

#endif /* DETECTOR_H_ */
