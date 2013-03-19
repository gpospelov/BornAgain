// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @copyright Forschungszentrum Jülich GmbH 2013
//             
//  Homepage:  apps.jcns.fz-juelich.de/BornAgain
//  License:   GNU General Public License v3 or higher (see COPYING)
//
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
//! @file      PythonAPI/inc/PythonOutputData.h 
//! @brief     Defines a few global functions: GetOutputDataNdimensions, ..
//
// ************************************************************************** //

#ifndef PYTHONOUTPUTDATA_H
#define PYTHONOUTPUTDATA_H

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
