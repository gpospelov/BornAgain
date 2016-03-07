// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/SessionModel.h
//! @brief     Defines class SessionModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SESSIONXML_H
#define SESSIONXML_H

#include "WinDllMacros.h"
#include <QString>
#include <QVariant>

class QXmlStreamWriter;
class QXmlStreamReader;
class ParameterizedItem;

namespace SessionXML {
const QString MimeType = "application/org.bornagainproject.xml.item.z";
const QString ModelTag("SessionModel");
const QString InstrumentModelTag("InstrumentModel");
const QString SampleModelTag("SampleModel");
const QString MaterialModelTag("MaterialModel");
const QString FitModelTag("FitModel");
const QString JobModelTag("JobModel");
const QString MaskModelTag("MaskModel");

const QString TagAttribute("Tag");

const QString ModelNameAttribute("Name");
const QString ItemTag("Item");
const QString ModelTypeAttribute("ModelType");
const QString ItemNameAttribute("ItemName");
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
    static void writeTo(QXmlStreamWriter *writer, ParameterizedItem *parent);
    static void writeItemAndChildItems(QXmlStreamWriter *writer, const ParameterizedItem *item);
private:
    static void writeVariant(QXmlStreamWriter *writer, QVariant variant, int role);
};

class BA_CORE_API_ SessionReader
{
public:
    static void readItems(QXmlStreamReader *reader, ParameterizedItem *item, int row = -1);
private:
    static QString readProperty(QXmlStreamReader *reader, ParameterizedItem *item);
};

#endif // SESSIONXML_H
