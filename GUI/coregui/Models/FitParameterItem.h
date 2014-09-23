#ifndef FITPARAMETERITEM_H
#define FITPARAMETERITEM_H

#include "ParameterizedItem.h"


class BA_CORE_API_ FitParameterItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_MIN;
    explicit FitParameterItem(ParameterizedItem *parent=0);
    ~FitParameterItem(){}
private:
    QStringList m_par_names;
};


// bool fixed, start_value, min, max, step

#endif

