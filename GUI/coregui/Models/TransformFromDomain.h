// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/TransformFromDomain.h
//! @brief     Defines class TransformFromDomain
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef TRANSFORMFROMDOMAIN_H
#define TRANSFORMFROMDOMAIN_H

#include "WinDllMacros.h"
#include <QString>

namespace TransformFromDomain
{
BA_CORE_API_ void setItemFromSample(class SessionItem *item,
                                    const class FormFactorAnisoPyramid *sample);

BA_CORE_API_ void setItemFromSample(class SessionItem *item,
                                    const class InterferenceFunctionRadialParaCrystal *sample);

BA_CORE_API_ void setItemFromSample(class SessionItem *item,
                                    const class InterferenceFunction2DParaCrystal *sample);

BA_CORE_API_ void setItemFromSample(class SessionItem *item,
                                    const class InterferenceFunction1DLattice *sample);

BA_CORE_API_ void setItemFromSample(class SessionItem *item,
                                    const class InterferenceFunction2DLattice *sample);

BA_CORE_API_ void setItemFromSample(class SessionItem *layerItem, const class Layer *layer,
                                    const class LayerInterface *top_interface);

BA_CORE_API_ void setItemFromSample(class SessionItem *item,
                                    const class LayerRoughness *sample);

BA_CORE_API_ void setItemFromSample(class SessionItem *item,
                                    const class ParticleDistribution *sample);

BA_CORE_API_ bool isValidRoughness(const class LayerRoughness *roughness);

BA_CORE_API_ bool isSquareLattice(double length1, double length2, double angle);

BA_CORE_API_ bool isHexagonalLattice(double length1, double length2, double angle);

BA_CORE_API_ void setItemFromSample(class BeamItem *beamItem,
                                    const class GISASSimulation &simulation);

BA_CORE_API_ void setItemFromSample(class DetectorItem *detectorItem,
                                    const class GISASSimulation &simulation);

BA_CORE_API_ void setItemFromSample(class SphericalDetectorItem *detectorItem,
                                    const class SphericalDetector &detector);

BA_CORE_API_ void setItemFromSample(class RectangularDetectorItem *detectorItem,
                                    const class RectangularDetector &detector);

BA_CORE_API_ void setDetectorMasks(class DetectorItem *detectorItem,
                                   const class GISASSimulation &simulation);

BA_CORE_API_ void setItemFromSample(class BeamDistributionItem *beamDistributionItem,
                                    const class ParameterDistribution &parameterDistribution);

BA_CORE_API_ void setItemFromSample(class BeamDistributionItem *beamDistributionItem,
                                    const class ParameterDistribution &parameterDistribution);


BA_CORE_API_ QString translateParameterNameToGUI(class SessionItem *item,
                                                 const class QString &par_name);
}

#endif
