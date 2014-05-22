#ifndef ICON_PROVIDER_H
#define ICON_PROVIDER_H

#include <QIcon>
#include <QString>

//! Class which returns icons for ParameterizedItems to used from SessionModel
class IconProvider
{
public:
    IconProvider(){}
    virtual ~IconProvider(){}

    virtual QIcon icon(const QString &name);

};


#endif

