// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaterialEditor/MaterialProperty.h
//! @brief     Declares class MaterialProperty
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef MATERIALPROPERTY_H
#define MATERIALPROPERTY_H

#include "WinDllMacros.h"
#include <QColor>
#include <QMetaType>
#include <QPixmap>
#include <QString>
#include <QVariant>

//! The MaterialProperty class defines unique identifier to help LayerItem, ParticleItem etc
//! to access materials from MaterialEditor;
class BA_CORE_API_ MaterialProperty
{
public:
    explicit MaterialProperty(const QString &identifier=QString())
        : m_identifier(identifier){}

    QString getIdentifier() const {
        return m_identifier;
    }

    QVariant getVariant() const
    {
        QVariant variant;
        variant.setValue(*this);
        return variant;
    }

    QString getName() const;
    QColor getColor() const;
    QPixmap getPixmap() const;

    bool isDefined() const;

private:
    QString m_identifier;
};

Q_DECLARE_METATYPE(MaterialProperty)

#endif // MATERIALPROPERTY_H
