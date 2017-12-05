// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SessionXML2.cpp
//! @brief     Implements reader and writer classes for SessionModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "SessionXML2.h"
#include "SessionXML.h"
#include "SessionItem.h"
#include "SessionFlags.h"
#include "SessionModel.h"
#include "GUIHelpers.h"
#include "ItemFactory.h"
#include "GroupItem.h"
#include <QXmlStreamWriter>
#include <QXmlStreamWriter>
#include <QDebug>

namespace
{

SessionItem* createItem(SessionItem* parent, const QString& modelType, const QString& tag)
{
    SessionItem* result(nullptr);

    if (parent->modelType() == Constants::GroupItemType) {
        result = parent->parent()
                     ->item<GroupItem>(parent->parent()->tagFromItem(parent))
                     .groupProperty()
                     ->getItemOfType(modelType);
    } else {
        SessionTagInfo info = parent->getTagInfo(tag);
        if (info.min == 1 && info.max == 1 && info.childCount == 1)
            result = parent->getItem(tag);
        else
            result = parent->model()->insertNewItem(modelType, parent->index(), -1, tag);
    }
    Q_ASSERT(result);
    return result;
}

}

void SessionXML2::writeItemAndChildItems(QXmlStreamWriter* writer, const SessionItem* item)
{
    if (item->parent()) {
        writer->writeStartElement(SessionXML::ItemTag);
        writer->writeAttribute(SessionXML::ModelTypeAttribute, item->modelType());
        QString tag = item->parent()->tagFromItem(item);
        writer->writeAttribute(SessionXML::TagAttribute, tag);
        writer->writeAttribute(SessionXML::DisplayNameAttribute,
                               item->data(SessionFlags::DisplayNameRole).toString());
        for (int role : item->getRoles()) {
            if (role == Qt::DisplayRole || role == Qt::EditRole)
                SessionWriter::writeVariant(writer, item->value(), role);
        }
    }

    for (auto child : item->children())
        writeItemAndChildItems(writer, child);

    if (item->parent())
        writer->writeEndElement(); // ItemTag
}

void SessionXML2::readItems(QXmlStreamReader* reader, SessionItem* parent)
{
    Q_ASSERT(parent);
    const QString start_type = parent->model()->getModelTag();
    while (!reader->atEnd()) {
        reader->readNext();
        if (reader->isStartElement()) {
            if (reader->name() == SessionXML::ItemTag) {
                const QString model_type
                    = reader->attributes().value(SessionXML::ModelTypeAttribute).toString();
                QString tag = reader->attributes().value(SessionXML::TagAttribute).toString();
                parent = createItem(parent, model_type, tag);
            } else if (reader->name() == SessionXML::ParameterTag) {
                SessionReader::readProperty(reader, parent);
            }
        } else if (reader->isEndElement()) {
            if (reader->name() == SessionXML::ItemTag && parent)
                parent = parent->parent();

            if (reader->name() == start_type)
                break;
        }
    }
}
