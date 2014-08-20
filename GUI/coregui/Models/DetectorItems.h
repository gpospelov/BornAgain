#ifndef DETECTOR_ITEMS_H
#define DETECTOR_ITEMS_H

#include "ParameterizedItem.h"


class DetectorItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_DETECTOR;
    explicit DetectorItem(ParameterizedItem *parent=0);
    ~DetectorItem(){}
};


class PhiAlphaDetectorItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_AXES_UNITS, P_BINNING, P_PHI_MIN, P_PHI_MAX, P_NPHI, P_ALPHA_MIN, P_ALPHA_MAX, P_NALPHA;
    explicit PhiAlphaDetectorItem(ParameterizedItem *parent=0);
    ~PhiAlphaDetectorItem(){}

    virtual void onPropertyChange(const QString &name);
};


//class XYDetectorItem : public ParameterizedItem
//{
//    Q_OBJECT
//public:
//    explicit XYDetectorItem(ParameterizedItem *parent=0);
//    ~XYDetectorItem(){}

//};

#endif
