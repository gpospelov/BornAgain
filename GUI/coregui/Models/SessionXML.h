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

namespace SessionXML {
const QString ItemMimeType = "application/org.bornagainproject.xml.item.z";
const QString LinkMimeType = "application/org.bornagainproject.fittinglink";

const QString ModelTag("SessionModel");
const QString InstrumentModelTag("InstrumentModel");
const QString SampleModelTag("SampleModel");
const QString MaterialModelTag("MaterialModel");
const QString FitModelTag("FitModel");
const QString JobModelTag("JobModel");
const QString MaskModelTag("MaskModel");
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

const QString IdentifierAttribute("Identifier");

const QString ColorRedAttribute("Red");
const QString ColorGreenAttribute("Green");
const QString ColorBlueAttribute("Blue");
const QString ColorAlphaAttribute("Alpha");

const QString AngleUnitsAttribute("Units");

}

class BA_CORE_API_ SessionWriter
{
public:
    static void writeTo(QXmlStreamWriter *writer, SessionItem *parent);
    static void writeItemAndChildItems(QXmlStreamWriter *writer, const SessionItem *item);
private:
    static void writeVariant(QXmlStreamWriter *writer, QVariant variant, int role);
};

class BA_CORE_API_ SessionReader
{
public:
    static void readItems(QXmlStreamReader *reader, SessionItem *item,
                          const QString &topTag = QString(),
                          WarningMessageService *messageService=0);
private:
    static QString readProperty(QXmlStreamReader *reader, SessionItem *item,
                                WarningMessageService *messageService=0);

    static void report_error(WarningMessageService *messageService, SessionItem *item,
                      const QString &error_type, const QString &message);
};

#endif // SESSIONXML_H
