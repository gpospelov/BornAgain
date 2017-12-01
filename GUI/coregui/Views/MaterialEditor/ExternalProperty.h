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

//! The MaterialProperty class defines unique identifier to help LayerItem, ParticleItem etc
//! to access materials from MaterialEditor;
class BA_CORE_API_ ExternalProperty
{
public:
    explicit ExternalProperty();

    QString identifier() const;
    void setIdentifier(const QString& identifier);

    QString text() const;
    void setText(const QString& name);

    QColor color() const;
    void setColor(const QColor& color);

    QPixmap pixmap() const;

    bool isValid() const;

    QVariant variant() const;

private:
    QString m_identifier;
    QString m_text;
    QColor m_color;
};

Q_DECLARE_METATYPE(ExternalProperty)

#endif // EXTERNALPROPERTY_H
