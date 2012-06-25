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

#include "NamedVector.h"

#include <vector>

class Detector
{
public:
	Detector();
	virtual ~Detector();

	void addAxis(const NamedVector<double> &axis);
	NamedVector<double>& getAxis(size_t index);
	size_t getDimension() { return m_axes.size(); }
	void clear();
protected:
	bool isCorrectAxisIndex(size_t index) { return index<getDimension(); }
private:
	std::vector<NamedVector<double> > m_axes;

};

#endif /* DETECTOR_H_ */
