// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/IconProvider.cpp
//! @brief     Implements class IconProvider
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

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
