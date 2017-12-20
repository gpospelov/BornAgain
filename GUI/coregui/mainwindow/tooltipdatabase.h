// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/tooltipdatabase.h
//! @brief     Defines class ToolTipDataBase
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef TOOLTIPDATABASE_H
#define TOOLTIPDATABASE_H

#include "WinDllMacros.h"
#include <QObject>
#include <QMap>

//! The MaterialEditor is the main class to access materials.
class BA_CORE_API_ ToolTipDataBase : public QObject
{
    Q_OBJECT
public:
    explicit ToolTipDataBase(QObject* parent = nullptr);
    virtual ~ToolTipDataBase();

    static QString widgetboxToolTip(const QString& className);

private:
    void initDataBase();
    QString getTag(const QString& contextName, const QString& categoryName,
                   const QString& propertyName);
    void addToolTip(const QString& contextName, const QString& categoryName,
                    const QString& propertyName, const QString& tooltip);
    QString this_getToolTip(const QString& contextName, const QString& categoryName,
                            const QString& propertyName);

    static ToolTipDataBase* m_instance;

    static QMap<QString, QString> m_tagToToolTip;
};

#endif // TOOLTIPDATABASE_H
