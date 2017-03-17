// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/GroupInfo.h
//! @brief     Defines class GroupInfo
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef GROUPINFO_H
#define GROUPINFO_H

#include "WinDllMacros.h"
#include <QString>
#include <QVector>
#include <QStringList>

//! Defines info for GroupProperty, i.e. collection of model types, their labels and
//! the name of default item's modelType.

class BA_CORE_API_ GroupInfo
{
public:
    explicit GroupInfo(const QString& groupName = QString(), bool is_sorted = true);

    void add(const QString& modelType, const QString& label);

    QString defaultType() const;
    void setDefaultType(const QString& modelType);

    QString groupName() const;

    QStringList types() const;

    QStringList labels() const;

private:
    struct TypeAndLabel {
        QString m_modelType;
        QString m_label;
    };

    bool containsType(const QString& modelType) const;

    //!< Default model type for given group (i.e. FFCylinder for formfactor group)
    QString m_defaultType;
    //!< Unique group name for GroupInfoCatalogue
    QString m_groupName;
    //!< Info will be sorted if true, otherwise order of insertion will be preserved
    bool is_sorted;
    QVector<TypeAndLabel> m_info;
};

#endif
