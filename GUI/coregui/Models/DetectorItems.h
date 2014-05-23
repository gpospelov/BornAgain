#ifndef DETECTOR_ITEMS_H
#define DETECTOR_ITEMS_H

#include "ParameterizedItem.h"




class DetectorItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_DETECTOR_TYPE, P_AXES_UNITS, P_BINNING;
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
    static const QString P_MODEL_TYPE;
    explicit ThetaPhiDetectorItem(ParameterizedItem *parent=0);
    ~ThetaPhiDetectorItem(){}

};


#endif
