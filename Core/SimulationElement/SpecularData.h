// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/SimulationElement/SpecularData.h
//! @brief     Defines class SpecularData.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SPECULARDATA_H_
#define SPECULARDATA_H_

#include "MatrixRTCoefficients.h"
#include "ScalarRTCoefficients.h"
#include "WinDllMacros.h"
#include <boost/variant.hpp>
#include <vector>

//! Helper class for SimulationElement to carry specular information
//! @ingroup simulation

class BA_CORE_API_ SpecularData
{
    // FIXME: find a better way to carry the specular data in SimulationElement (see TODO above)
    using ScalarVector = std::vector<ScalarRTCoefficients>;
    using MatrixVector = std::vector<MatrixRTCoefficients>;
public:
    SpecularData();

    SpecularData(MatrixVector coefficients);

    SpecularData(ScalarVector coefficients);

    SpecularData* clone();

    const ILayerRTCoefficients& operator[](size_t index) const;

    bool isInited() const {return data_type_used != DATA_TYPE::Invalid;}

private:
    enum class DATA_TYPE { Invalid = -1, Scalar, Matrix };
    boost::variant<ScalarVector, MatrixVector> data;
    DATA_TYPE data_type_used;
};

#endif /* SPECULARDATA_H_ */
