// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaterialEditor/ExternalProperty.h
//! @brief     Defines class ExternalProperty
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef EXTERNALPROPERTY_H
#define EXTERNALPROPERTY_H

#include "WinDllMacros.h"
#include <QColor>
#include <QMetaType>
#include <QPixmap>
#include <QString>
#include <QVariant>

//! The ExternalProperty class defines custom QVariant property to carry the text, color and
//! an identifier.

class BA_CORE_API_ ExternalProperty
{
public:
    explicit ExternalProperty();

    QString text() const;
    void setText(const QString& name);

    QColor color() const;
    void setColor(const QColor& color);

    QString identifier() const;
    void setIdentifier(const QString& identifier);

    QPixmap pixmap() const;

    bool isValid() const;

    QVariant variant() const;

    bool operator==(const ExternalProperty& other) const;
    bool operator!=(const ExternalProperty& other) const;
    bool operator<(const ExternalProperty& other) const;

private:
    QString m_text;
    QColor m_color;
    QString m_identifier;
};

Q_DECLARE_METATYPE(ExternalProperty)

#endif // EXTERNALPROPERTY_H
