// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SessionDecorationModel.h
//! @brief     Defines class SessionDecorationModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SessionDecorationModel.h"
#include "SessionModel.h"
#include "MaterialItem.h"
#include <QColor>
#include <QIcon>
#include <QPixmap>

namespace {

QIcon instrumentIcon() {
    QIcon result;
    result.addPixmap(QPixmap(":/images/gisas_instrument_bw.png"), QIcon::Normal);
    result.addPixmap(QPixmap(":/images/gisas_instrument.png"), QIcon::Selected);
    return result;
}

QIcon materialIcon(const QColor& color)
{
    QIcon result;
    QPixmap pixmap(10,10);
    pixmap.fill(color);
    result.addPixmap(pixmap);
    return result;
}

}

SessionDecorationModel::SessionDecorationModel(QObject* parent, SessionModel* model)
    : QIdentityProxyModel(parent)
    , m_model(nullptr)
{
    setSessionModel(model);
}

void SessionDecorationModel::setSessionModel(SessionModel* model)
{
    QIdentityProxyModel::setSourceModel(model);
    m_model = model;
}

QVariant SessionDecorationModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::DecorationRole) {
        QVariant result = createIcon(index);
        if (result.isValid())
            return result;
    }

    if(role == Qt::TextColorRole) {
        QVariant result = textColor(index);
        if (result.isValid())
            return result;
    }

    return QIdentityProxyModel::data(index, role);
}

SessionModel* SessionDecorationModel::sessionModel()
{
    return m_model;
}

QVariant SessionDecorationModel::createIcon(const QModelIndex& index) const
{
    QVariant result;

    if (SessionItem* item = m_model->itemForIndex(index)) {
        if (item->modelType() == Constants::InstrumentType) {
            return instrumentIcon();
        } else if(item->modelType() == Constants::HomogeneousMaterialType) {
            if (const MaterialItem *materialItem = dynamic_cast<const MaterialItem *>(item))
                return materialIcon(materialItem->getColor());
        }
    }

    return result;
}

//! Returns text color. Disabled SessionItem's will appear in gray.

QVariant SessionDecorationModel::textColor(const QModelIndex& index) const
{
    QVariant result;

    if (SessionItem* item = m_model->itemForIndex(index)) {
        if (item->isEnabled() == false)
            return QColor(Qt::gray);
    }

    return result;
}
