#include "IconProvider.h"
#include "item_constants.h"
#include <QPixmap>

QIcon IconProvider::icon(const QString &modelType)
{
    if(modelType == Constants::InstrumentType) {
        QIcon icon;
        icon.addPixmap(QPixmap(":/images/gisas_instrument_bw.png"),QIcon::Normal);
        icon.addPixmap(QPixmap(":/images/gisas_instrument.png"),QIcon::Selected);
        return icon;
    }
    return QIcon();
}
