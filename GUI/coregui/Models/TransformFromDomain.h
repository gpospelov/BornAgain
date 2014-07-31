#ifndef TRANSFORMFROMDOMAIN_H
#define TRANSFORMFROMDOMAIN_H

class FormFactorAnisoPyramid;
class ParameterizedItem;
class InterferenceFunction2DParaCrystal;
class InterferenceFunction1DParaCrystal;
class LayerRoughness;
class LayerInterface;
class Layer;

namespace TransformFromDomain
{
void setItemFromSample(ParameterizedItem *item,
                       const FormFactorAnisoPyramid *sample);

void setItemFromSample(ParameterizedItem *item,
                       const InterferenceFunction2DParaCrystal *sample);

void setItemFromSample(ParameterizedItem *item,
                       const InterferenceFunction1DParaCrystal *sample);

void setItemFromSample(ParameterizedItem *layerItem, const Layer *layer, const LayerInterface *top_interface);

void setItemFromSample(ParameterizedItem *item , const LayerRoughness *sample);

bool isSquareLattice(const InterferenceFunction2DParaCrystal *sample);
bool isHexagonalLattice(const InterferenceFunction2DParaCrystal *sample);
bool isValidRoughness(const LayerRoughness *roughness);
}

#endif
