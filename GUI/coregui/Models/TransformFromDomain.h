#ifndef TRANSFORMFROMDOMAIN_H
#define TRANSFORMFROMDOMAIN_H

#include "WinDllMacros.h"
#include <QString>

class FormFactorAnisoPyramid;
class ParameterizedItem;
class InterferenceFunction1DParaCrystal;
class InterferenceFunction2DParaCrystal;
class InterferenceFunction2DLattice;
class LayerRoughness;
class LayerInterface;
class Layer;
class Detector;
class ParticleCollection;

namespace TransformFromDomain
{
BA_CORE_API_ void setItemFromSample(ParameterizedItem *item,
                       const FormFactorAnisoPyramid *sample);

BA_CORE_API_ void setItemFromSample(ParameterizedItem *item,
                       const InterferenceFunction1DParaCrystal *sample);

BA_CORE_API_ void setItemFromSample(ParameterizedItem *item,
                       const InterferenceFunction2DParaCrystal *sample);

BA_CORE_API_ void setItemFromSample(ParameterizedItem *item,
                       const InterferenceFunction2DLattice *sample);

BA_CORE_API_ void setItemFromSample(ParameterizedItem *layerItem,
                                    const Layer *layer,
                                    const LayerInterface *top_interface);

BA_CORE_API_ void setItemFromSample(ParameterizedItem *item ,
                                    const LayerRoughness *sample);

BA_CORE_API_ void setItemFromSample(ParameterizedItem *item ,
                                    const ParticleCollection *sample);

BA_CORE_API_ bool isValidRoughness(const LayerRoughness *roughness);
BA_CORE_API_ bool isSquareLattice(double length1, double length2, double angle);
BA_CORE_API_ bool isHexagonalLattice(double length1, double length2, double angle);

BA_CORE_API_ QString getDetectorBinning(const Detector *detector);

}

#endif
