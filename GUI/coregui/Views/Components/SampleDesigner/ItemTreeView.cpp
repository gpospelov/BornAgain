// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/Components/SampleDesigner/ItemTreeView.cpp
//! @brief     Implements class ItemTreeView
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ItemTreeView.h"
#include "SessionModel.h"
#include "GUIHelpers.h"

#include <QDragMoveEvent>
#include <QMimeData>

ItemTreeView::ItemTreeView(QWidget *parent)
    : QTreeView(parent)
{

    setAllColumnsShowFocus(true);
    setWindowTitle(QString("Sample Tree View"));
    setObjectName(QString("ObjectTree"));
    setContextMenuPolicy(Qt::CustomContextMenu);
    setDragDropMode(QAbstractItemView::InternalMove);
}

ItemTreeView::~ItemTreeView()
{
}

void ItemTreeView::dragMoveEvent(QDragMoveEvent *event)
{
    QTreeView::dragMoveEvent(event);
    SessionModel *model = static_cast<SessionModel *>(this->model());
    model->setDraggedItemType(QString());
    QByteArray xml_data = qUncompress(
                event->mimeData()->data(SessionXML::MimeType));
    QXmlStreamReader reader(xml_data);
    while (!reader.atEnd()) {
        reader.readNext();
        if (reader.isStartElement()) {
            if (reader.name() == SessionXML::ItemTag) {
                const QString model_type = reader.attributes()
                        .value(SessionXML::ModelTypeAttribute).toString();
                model->setDraggedItemType(model_type);
                break;
            }
        }
    }
}
