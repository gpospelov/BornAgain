// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/CommonWidgets/ItemSelectorWidget.h
//! @brief     Declares class ItemSelectorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef ITEMSELECTORWIDGET_H
#define ITEMSELECTORWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class SessionModel;
class SessionItem;
class QItemSelection;

//! The ItemSelectorWidget class holds QListView to show top level items of SessionModel.
//! Used in InstrumentView and ImportDataView to switch between items.

class BA_CORE_API_ ItemSelectorWidget : public QWidget
{
    Q_OBJECT

public:
    ItemSelectorWidget(QWidget *parent = 0);

    QSize sizeHint() const { return QSize(200, 400); }
    QSize minimumSizeHint() const { return QSize(128, 200); }

    void setModel(SessionModel *model);

signals:
    void selectionChanged(SessionItem *item);

private slots:
    void onSelectionChanged(const QItemSelection &selected, const QItemSelection&);

protected:
    void connectModel();
    void disconnectModel();

private:
    class QListView *m_listView;
    SessionModel *m_model;
};

#endif
