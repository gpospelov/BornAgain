#ifndef BEAMITEM_H
#define BEAMITEM_H


#include "ParameterizedItem.h"

class BA_CORE_API_ BeamItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_INTENSITY;
    static const QString P_WAVELENGTH;
    static const QString P_INCLINATION_ANGLE;
    static const QString P_AZIMUTHAL_ANGLE;
    explicit BeamItem(ParameterizedItem *parent=0);
    ~BeamItem(){}

    void onPropertyChange(const QString &name);

};



#endif

