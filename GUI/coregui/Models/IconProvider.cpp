#include "IconProvider.h"


QIcon IconProvider::icon(const QString &modelType)
{
    if(modelType == QStringLiteral("Instrument")) {
        return QIcon(":/images/config.png");
    }
    return QIcon();
}
