#ifndef FITPARAMETERITEM_H
#define FITPARAMETERITEM_H

#include "ParameterizedItem.h"


class BA_CORE_API_ FitParameterItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_MIN;
    static const QString P_MAX;
    static const QString P_VALUE;
    static const QString P_USE;
    explicit FitParameterItem(ParameterizedItem *parent=0);
    ~FitParameterItem(){}

    void setParNames(QStringList par_names);
    QStringList getParNames();
private:
    QStringList m_par_names;
};


// bool fixed, start_value, min, max, step

#endif

