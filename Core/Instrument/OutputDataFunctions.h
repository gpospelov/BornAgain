// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/OutputDataFunctions.h
//! @brief     Defines functions in namespace OutputDataFunctions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef OUTPUTDATAFUNCTIONS_H
#define OUTPUTDATAFUNCTIONS_H

#include "Complex.h"
#include "OutputData.h"

class IIntensityFunction;

//! Collection of functions to deal with OutputData

namespace OutputDataFunctions
{
    //! double the bin size for each dimension
    BA_CORE_API_ OutputData<double>* doubleBinSize(const OutputData<double>& source);

    //! unnormalized Fourier transformation for real data
    BA_CORE_API_ void FourierTransform(
        const OutputData<double>& source, OutputData<complex_t>* p_destination);

    //! unnormalized reverse Fourier transformation for real data
    BA_CORE_API_ void FourierTransformR(
        const OutputData<complex_t>& source, OutputData<double>* p_destination);

    //! reduces the data to the element-wise real, imaginary or modulus part
    BA_CORE_API_ OutputData<double>* getRealPart(const OutputData<complex_t>& source);
    BA_CORE_API_ OutputData<double>* getImagPart(const OutputData<complex_t>& source);
    BA_CORE_API_ OutputData<double>* getModulusPart(const OutputData<complex_t>& source);

#ifndef SWIG
    //! Selects an element-wise component of the matrix-valued OutputData
    //! structure and returns a new double-valued one
    BA_CORE_API_ OutputData<double>* getComponentData(
        const OutputData<Eigen::Matrix2d>& source, int row, int column);
#endif
}

#endif // OUTPUTDATAFUNCTIONS_H
