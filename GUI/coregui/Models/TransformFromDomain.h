#ifndef TRANSFORMFROMDOMAIN_H
#define TRANSFORMFROMDOMAIN_H

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

namespace TransformFromDomain
{
void setItemFromSample(ParameterizedItem *item,
                       const InterferenceFunction1DParaCrystal *sample);

void setItemFromSample(ParameterizedItem *item,
                       const InterferenceFunction2DParaCrystal *sample);

void setItemFromSample(ParameterizedItem *item,
                       const InterferenceFunction2DLattice *sample);

void setItemFromSample(ParameterizedItem *layerItem, const Layer *layer, const LayerInterface *top_interface);

void setItemFromSample(ParameterizedItem *item , const LayerRoughness *sample);


bool isValidRoughness(const LayerRoughness *roughness);
bool isSquareLattice(double length1, double length2, double angle);
bool isHexagonalLattice(double length1, double length2, double angle);

QString getDetectorBinning(const Detector *detector);

}

#endif
