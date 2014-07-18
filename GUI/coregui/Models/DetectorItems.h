#ifndef DETECTOR_ITEMS_H
#define DETECTOR_ITEMS_H

#include "ParameterizedItem.h"




class DetectorItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_AXES_UNITS, P_BINNING,
    P_XMIN, P_XMAX, P_NBINX, P_YMIN, P_YMAX, P_NBINY;
    explicit DetectorItem(ParameterizedItem *parent=0);
    ~DetectorItem(){}
};


class XYDetectorItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_MODEL_TYPE;
    explicit XYDetectorItem(ParameterizedItem *parent=0);
    ~XYDetectorItem(){}

};

class ThetaPhiDetectorItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_PHI_MIN, P_PHI_MAX, P_NPHI, P_ALPHA_MIN, P_ALPHA_MAX, P_NALPHA;
    explicit ThetaPhiDetectorItem(ParameterizedItem *parent=0);
    ~ThetaPhiDetectorItem(){}

    virtual void onPropertyChange(const QString &name);

};


#endif
