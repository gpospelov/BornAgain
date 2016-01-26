// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/TransformFromDomain.h
//! @brief     Defines class TransformFromDomain
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TRANSFORMFROMDOMAIN_H
#define TRANSFORMFROMDOMAIN_H

#include "WinDllMacros.h"
#include <QString>

class ParameterizedItem;
class BeamItem;
class PhiAlphaDetectorItem;
class FormFactorAnisoPyramid;
class InterferenceFunctionRadialParaCrystal;
class InterferenceFunction2DParaCrystal;
class InterferenceFunction1DLattice;
class InterferenceFunction2DLattice;
class LayerRoughness;
class LayerInterface;
class Layer;
class IDetector2D;
class ParticleDistribution;
class Beam;
class GISASSimulation;
class BeamDistributionItem;
class ParameterDistribution;
class DistributionItem;
class IDistribution1D;
class DetectorItem;

namespace TransformFromDomain
{
BA_CORE_API_ void setItemFromSample(ParameterizedItem *item, const FormFactorAnisoPyramid *sample);

BA_CORE_API_ void setItemFromSample(ParameterizedItem *item,
                                    const InterferenceFunctionRadialParaCrystal *sample);

BA_CORE_API_ void setItemFromSample(ParameterizedItem *item,
                                    const InterferenceFunction2DParaCrystal *sample);

BA_CORE_API_ void setItemFromSample(ParameterizedItem *item,
                                    const InterferenceFunction1DLattice *sample);

BA_CORE_API_ void setItemFromSample(ParameterizedItem *item,
                                    const InterferenceFunction2DLattice *sample);

BA_CORE_API_ void setItemFromSample(ParameterizedItem *layerItem, const Layer *layer,
                                    const LayerInterface *top_interface);

BA_CORE_API_ void setItemFromSample(ParameterizedItem *item, const LayerRoughness *sample);

BA_CORE_API_ void setItemFromSample(ParameterizedItem *item, const ParticleDistribution *sample);

BA_CORE_API_ bool isValidRoughness(const LayerRoughness *roughness);

BA_CORE_API_ bool isSquareLattice(double length1, double length2, double angle);

BA_CORE_API_ bool isHexagonalLattice(double length1, double length2, double angle);

BA_CORE_API_ void setItemFromSample(BeamItem *beamItem, const GISASSimulation &simulation);

BA_CORE_API_ void setItemFromSample(PhiAlphaDetectorItem *detectorItem,
                                    const GISASSimulation &simulation);
BA_CORE_API_ void setDetectorMasks(DetectorItem *detectorItem, const GISASSimulation &simulation);

BA_CORE_API_ void setItemFromSample(BeamDistributionItem *beamDistributionItem,
                                    const ParameterDistribution &parameterDistribution);

BA_CORE_API_ QString translateParameterNameToGUI(ParameterizedItem *item, const QString &par_name);
}

#endif
