// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SessionXML.h
//! @brief     Defines reader and writer classes for SessionModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef SESSIONXML_H
#define SESSIONXML_H

#include "WinDllMacros.h"
#include <QVariant>

class QXmlStreamWriter;
class QXmlStreamReader;
class SessionItem;
class WarningMessageService;

namespace SessionXML
{
const QString ItemMimeType = "application/org.bornagainproject.xml.item.z";
const QString LinkMimeType = "application/org.bornagainproject.fittinglink";

const QString InstrumentModelTag("InstrumentModel");
const QString SampleModelTag("SampleModel");
const QString MaterialModelTag("MaterialModel");
const QString JobModelTag("JobModel");
const QString DocumentModelTag("DocumentModel");
const QString RealDataModelTag("RealDataModel");

const QString TagAttribute("Tag");

const QString ModelNameAttribute("Name");
const QString ItemTag("Item");
const QString ModelTypeAttribute("ModelType");
const QString DisplayNameAttribute("DisplayName");
const QString ParameterTag("Parameter");
const QString ParameterNameAttribute("ParName");
const QString ParameterTypeAttribute("ParType");
const QString ParameterValueAttribute("ParValue");
const QString ParameterRoleAttribute("ParRole");
const QString ParameterExtAttribute("ParExt");

const QString ExternalPropertyTextAtt("Text");
const QString ExternalPropertyColorAtt("Color");
const QString ExternalPropertyIdentifierAtt("Identifier");

BA_CORE_API_ void writeTo(QXmlStreamWriter* writer, SessionItem* parent);
BA_CORE_API_ void writeItemAndChildItems(QXmlStreamWriter* writer, const SessionItem* item);
BA_CORE_API_ void writeVariant(QXmlStreamWriter* writer, QVariant variant, int role);

BA_CORE_API_ void readItems(QXmlStreamReader* reader, SessionItem* parent,
                            QString topTag = QString(),
                            WarningMessageService* messageService = nullptr);
BA_CORE_API_ QString readProperty(QXmlStreamReader* reader, SessionItem* item,
                                  WarningMessageService* messageService = nullptr);
}

#endif // SESSIONXML_H
