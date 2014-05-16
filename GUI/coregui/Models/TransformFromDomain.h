#ifndef TRANSFORMFROMDOMAIN_H
#define TRANSFORMFROMDOMAIN_H

class ParameterizedItem;
class InterferenceFunction2DParaCrystal;

namespace TransformFromDomain
{

void setItemFromSample(ParameterizedItem *item, const InterferenceFunction2DParaCrystal *sample);

bool isSquareLattice(const InterferenceFunction2DParaCrystal *sample);
bool isHexagonalLattice(const InterferenceFunction2DParaCrystal *sample);


}

#endif
