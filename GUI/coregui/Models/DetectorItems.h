#ifndef DETECTOR_ITEMS_H
#define DETECTOR_ITEMS_H

#include "ParameterizedItem.h"


class BA_CORE_API_ DetectorItem : public ParameterizedItem
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
    static const QString P_AXES_UNITS;
    static const QString P_BINNING;
    static const QString P_PHI_MIN;
    static const QString P_PHI_MAX;
    static const QString P_NPHI;
    static const QString P_ALPHA_MIN;
    static const QString P_ALPHA_MAX;
    static const QString P_NALPHA;
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
