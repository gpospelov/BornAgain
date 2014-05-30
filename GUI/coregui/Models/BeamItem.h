#ifndef BEAMITEM_H
#define BEAMITEM_H


#include "ParameterizedItem.h"

class BeamItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_INTENSITY, P_WAVELENGTH, P_ANGLE_UNITS, P_INCLINATION_ANGLE, P_AZIMUTHAL_ANGLE;
    explicit BeamItem(ParameterizedItem *parent=0);
    ~BeamItem(){}
};



#endif

