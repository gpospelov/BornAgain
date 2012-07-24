#ifndef PYTHONOUTPUTDATA_H
#define PYTHONOUTPUTDATA_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   PythonOutputData.h
//! @brief  Export of OutputData class to python numpy array
//! @author Scientific Computing Group at FRM II
//! @date   19.07.2012

#include <Python.h>
#include "OutputData.h"
#include "GISASExperiment.h"

#include <string>



//! return number of dimensions in output data of GISASExperiment
int GetOutputDataNdimensions(const GISASExperiment &experiment);

//! export output data array of GISASExperiment to python-numpy array object
PyObject *GetOutputData(const GISASExperiment &experiment);

//! return one dimensional python-numpy array representing binning of the axis
//! with given index of GISASExperiment's oputput data
PyObject *GetOutputDataAxis(const GISASExperiment &experiment, int naxis);






#endif // PYTHONOUTPUTDATA_H
