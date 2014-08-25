#ifndef BEAMITEM_H
#define BEAMITEM_H


#include "ParameterizedItem.h"

class BA_CORE_API_ BeamItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_INTENSITY, P_WAVELENGTH, P_INCLINATION_ANGLE, P_AZIMUTHAL_ANGLE;
    explicit BeamItem(ParameterizedItem *parent=0);
    ~BeamItem(){}

    void onPropertyChange(const QString &name);

};



#endif

