#ifndef TRANSFORMFROMDOMAIN_H
#define TRANSFORMFROMDOMAIN_H

class FormFactorAnisoPyramid;
class ParameterizedItem;
class InterferenceFunction2DParaCrystal;
class InterferenceFunction1DParaCrystal;

namespace TransformFromDomain
{
void setItemFromSample(ParameterizedItem *item,
                       const FormFactorAnisoPyramid *sample);

void setItemFromSample(ParameterizedItem *item,
                       const InterferenceFunction2DParaCrystal *sample);

void setItemFromSample(ParameterizedItem *item,
                       const InterferenceFunction1DParaCrystal *sample);

bool isSquareLattice(const InterferenceFunction2DParaCrystal *sample);
bool isHexagonalLattice(const InterferenceFunction2DParaCrystal *sample);
}

#endif
