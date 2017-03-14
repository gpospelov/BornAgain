// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/TransformFromDomain.h
//! @brief     Defines namespace TransformFromDomain
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

class BeamDistributionItem;
class BeamItem;
class FormFactorAnisoPyramid;
class GISASSimulation;
class InterferenceFunction1DLattice;
class InterferenceFunction2DLattice;
class InterferenceFunction2DParaCrystal;
class InterferenceFunctionRadialParaCrystal;
class Layer;
class LayerInterface;
class LayerRoughness;
class ParameterDistribution;
class ParticleDistribution;
class RectangularDetector;
class RectangularDetectorItem;
class SessionItem;
class SphericalDetector;
class SphericalDetectorItem;
class DetectorItem;
class MaskContainerItem;
class IDetector2D;
class InstrumentItem;

namespace TransformFromDomain
{
BA_CORE_API_ void setItemFromSample(SessionItem *item,
                                    const FormFactorAnisoPyramid *sample);

BA_CORE_API_ void setItemFromSample(SessionItem *item,
                                    const InterferenceFunctionRadialParaCrystal *sample);

BA_CORE_API_ void setItemFromSample(SessionItem *item,
                                    const InterferenceFunction2DParaCrystal *sample);

BA_CORE_API_ void setItemFromSample(SessionItem *item,
                                    const InterferenceFunction1DLattice *sample);

BA_CORE_API_ void setItemFromSample(SessionItem *item,
                                    const InterferenceFunction2DLattice *sample);

BA_CORE_API_ void setItemFromSample(SessionItem *layerItem, const Layer *layer,
                                    const LayerInterface *top_interface);

BA_CORE_API_ void setItemFromSample(SessionItem *item,
                                    const LayerRoughness *sample);

BA_CORE_API_ void setItemFromSample(SessionItem *item,
                                    const ParticleDistribution *sample);

BA_CORE_API_ bool isValidRoughness(const LayerRoughness *roughness);

BA_CORE_API_ void setItemFromSample(BeamItem *beamItem,
                                    const GISASSimulation &simulation);

BA_CORE_API_ void setInstrumentDetectorFromSample(InstrumentItem *detectorItem,
                                    const GISASSimulation &simulation);

BA_CORE_API_ void setItemFromSample(SphericalDetectorItem *detectorItem,
                                    const SphericalDetector &detector);

BA_CORE_API_ void setItemFromSample(RectangularDetectorItem *detectorItem,
                                    const RectangularDetector &detector);

BA_CORE_API_ void setDetectorMasks(DetectorItem *detectorItem,
                                   const GISASSimulation &simulation);

BA_CORE_API_ void setDetectorMasks(MaskContainerItem *containerItem,
                                   const IDetector2D &detector, double scale);

BA_CORE_API_ void setItemFromSample(BeamDistributionItem *beamDistributionItem,
                                    const ParameterDistribution &parameterDistribution);

BA_CORE_API_ void setItemFromSample(BeamDistributionItem *beamDistributionItem,
                                    const ParameterDistribution &parameterDistribution);

}

#endif // TRANSFORMFROMDOMAIN_H
