#ifndef BEAMITEM_H
#define BEAMITEM_H


#include "ParameterizedItem.h"

class BeamItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_INTENSITY, P_WAVELENGTH, P_ANGLE_UNITS, P_INCLINATION_ANGLE, P_AZIMUTHAL_ANGLE, P_INCLINATION_ANGLE2, P_AZIMUTHAL_ANGLE2;
    explicit BeamItem(ParameterizedItem *parent=0);
    ~BeamItem(){}

    void onPropertyChange(const QString &name);

};



#endif

