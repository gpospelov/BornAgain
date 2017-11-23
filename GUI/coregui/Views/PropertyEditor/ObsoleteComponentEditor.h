// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/ObsoleteComponentEditor.h
//! @brief     Defines class ObsoleteComponentEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef OBSOLETECOMPONENTEDITOR_H
#define OBSOLETECOMPONENTEDITOR_H

#include "ObsoleteComponentEditorFlags.h"
#include "WinDllMacros.h"
#include <QWidget>
#include <memory>

class ObsoleteComponentEditorPrivate;
class SessionItem;
class SessionModel;
class QtVariantProperty;
class QtProperty;

class BA_CORE_API_ ObsoleteComponentEditor : public QWidget
{
    Q_OBJECT
public:
    ObsoleteComponentEditor(ObsoleteComponentEditorFlags::PresentationType flags = ObsoleteComponentEditorFlags::BROWSER_TABLE, QWidget *parent = 0);

    virtual ~ObsoleteComponentEditor();

    void setItem(SessionItem *item, const QString &group_name=QString());

    void updateEditor(SessionItem *item, QtVariantProperty *parentProperty = 0);

    void clearEditor();

    void setHeaderHidden(bool hide);

public slots:
    virtual void onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles);
    virtual void onRowsInserted(const QModelIndex &parent, int first, int last);

private slots:
    void onQtPropertyChanged(QtProperty *, const QVariant &value);

protected:
    QList<SessionItem *> componentItems(SessionItem *item) const;
    void cleanChildren(SessionItem *item);

    void disconnectModel(SessionModel *model);
    void connectModel(SessionModel *model);
    void disconnectManager();
    void connectManager();

    std::unique_ptr<ObsoleteComponentEditorPrivate> m_d;
};


#endif // OBSOLETECOMPONENTEDITOR_H
