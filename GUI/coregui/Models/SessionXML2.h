// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SessionXML2.h
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

#ifndef SESSIONXML2_H
#define SESSIONXML2_H

#include "WinDllMacros.h"
#include <QString>
class QXmlStreamWriter;
class QXmlStreamReader;
class SessionItem;

namespace SessionXML2
{

void writeItemAndChildItems(QXmlStreamWriter *writer, const SessionItem *item);

void readItems(QXmlStreamReader *reader, SessionItem *parent, QString topTag=QString());

}

#endif
