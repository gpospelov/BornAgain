// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Algorithms/IDetectorResolution.cpp
//! @brief     Implements default behaviour of IDetectorResolution interface.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "OutputDataFunctions.h"
#include "IDetectorResolution.h"
#include <memory>

void IDetectorResolution::applyDetectorResolutionPol(
        OutputData<Eigen::Matrix2d>* p_matrix_intensity) const
{
    if (!p_matrix_intensity) return;
    const std::unique_ptr<OutputData<double> > P_intensity00(
            OutputDataFunctions::getComponentData(*p_matrix_intensity, 0, 0) );
    const std::unique_ptr<OutputData<double> > P_intensity01(
            OutputDataFunctions::getComponentData(*p_matrix_intensity, 0, 1) );
    const std::unique_ptr<OutputData<double> > P_intensity10(
            OutputDataFunctions::getComponentData(*p_matrix_intensity, 1, 0) );
    const std::unique_ptr<OutputData<double> > P_intensity11(
            OutputDataFunctions::getComponentData(*p_matrix_intensity, 1, 1) );
   applyDetectorResolution(P_intensity00.get());
   applyDetectorResolution(P_intensity01.get());
   applyDetectorResolution(P_intensity10.get());
   applyDetectorResolution(P_intensity11.get());
   const std::unique_ptr<OutputData<Eigen::Matrix2d> > P_result(
           OutputDataFunctions::createFromComponents(
                   *P_intensity00.get(), *P_intensity01.get(),
                   *P_intensity10.get(), *P_intensity11.get() ) );
   p_matrix_intensity->copyFrom(*P_result.get());
}
