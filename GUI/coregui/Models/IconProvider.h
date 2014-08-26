#ifndef ICON_PROVIDER_H
#define ICON_PROVIDER_H

#include "WinDllMacros.h"
#include <QIcon>
#include <QString>

//! Class which returns icons for ParameterizedItems to use in SessionModel
class BA_CORE_API_ IconProvider
{
public:
    IconProvider(){}
    virtual ~IconProvider(){}

    virtual QIcon icon(const QString &modelType);

};


#endif

