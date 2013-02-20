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
#include "Simulation.h"

#include <string>



//! return number of dimensions in output data of simulation
int GetOutputDataNdimensions(const Simulation &simulation);

//! export output data array of simulation to python-numpy array object
PyObject *GetOutputData(const Simulation &simulation);

//! return one dimensional python-numpy array representing binning of the axis
//! with given index of simulation output data
PyObject *GetOutputDataAxis(const Simulation &simulation, int naxis);

#endif // PYTHONOUTPUTDATA_H
