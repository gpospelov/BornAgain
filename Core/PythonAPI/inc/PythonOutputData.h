// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      PythonAPI/inc/PythonOutputData.h
//! @brief     Defines a few global functions: GetOutputDataNdimensions, ..
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PYTHONOUTPUTDATA_H
#define PYTHONOUTPUTDATA_H

#include <Python.h>
#include "OutputData.h"
#include "Simulation.h"

#include <string>

//! Returns number of dimensions in output data of simulation.
int GetOutputDataNdimensions(const Simulation& simulation);

//! Exports output data array of simulation to python numpy array object.
PyObject *GetOutputData(const Simulation& simulation);

//! Exports single matrix component of output data array of simulation
//! to python numpy array object
PyObject *GetPolarizedOutputDataComponent(const Simulation& simulation,
        int row, int column);

//! Returns one dimensional python-numpy array representing binning of the axis with given index of simulation output data
PyObject *GetOutputDataAxis(const Simulation& simulation, int naxis);

//! exports output data to the python numpy array
PyObject *ExportOutputData(const OutputData<double >& output_data);

#endif // PYTHONOUTPUTDATA_H


