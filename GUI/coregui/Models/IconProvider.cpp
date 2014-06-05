#include "IconProvider.h"
#include <QPixmap>

QIcon IconProvider::icon(const QString &modelType)
{
    if(modelType == QStringLiteral("Instrument")) {
        QIcon icon;
        icon.addPixmap(QPixmap(":/images/gisas_instrument_bw.png"),QIcon::Normal);
        icon.addPixmap(QPixmap(":/images/gisas_instrument.png"),QIcon::Selected);
        return icon;
//        return QIcon(":/images/gisas_instrument2.png");
    }
    return QIcon();
}
