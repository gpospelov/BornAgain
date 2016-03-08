// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/IconProvider.cpp
//! @brief     Implements class IconProvider
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IconProvider.h"
#include "item_constants.h"
#include "SessionItem.h"
#include "MaterialItem.h"
#include <QPixmap>

QIcon IconProvider::icon(const SessionItem *item)
{
    Q_ASSERT(item);
    QIcon result;

    if(item->modelType() == Constants::InstrumentType) {
        result.addPixmap(QPixmap(":/images/gisas_instrument_bw.png"), QIcon::Normal);
        result.addPixmap(QPixmap(":/images/gisas_instrument.png"), QIcon::Selected);
    }

    else if(item->modelType() == Constants::MaterialType) {
        if(const MaterialItem *materialItem = dynamic_cast<const MaterialItem *>(item)) {
            QPixmap pixmap(10,10);
            pixmap.fill(materialItem->getColor());
            result.addPixmap(pixmap);
        }

    }

    return result;
}
