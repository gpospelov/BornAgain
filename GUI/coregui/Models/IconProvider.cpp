#include "IconProvider.h"


QIcon IconProvider::icon(const QString &name)
{
    if(name == QStringLiteral("Instrument")) {
        return QIcon(":/images/config.png");
    }
    return QIcon();
}
