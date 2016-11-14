// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/ItemStackWidget.h
//! @brief     Defines class ItemStackWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef ITEMSTACKWIDGET_H
#define ITEMSTACKWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class SessionModel;
class SessionItem;

//! The ItemStackWidget class contains a stack of widgets presenting top level items
//! of SessionModel. Every item corresponds to its own widget.

//! This is the base for ItemStackPresenter, which actually contains item
//! specific editor's logic. Used in InstrumentView, ImportDataView, JobView to show editors for
//! currently selected items.

class BA_CORE_API_ ItemStackWidget : public QWidget
{
    Q_OBJECT

public:
    ItemStackWidget(QWidget *parent = 0);

    void setModel(SessionModel *model);

    //! Shows the widget for given item (and hides previous one).
    //! If no widget yet exists, it will be created (flag isNew will become 'true' in this case).
    virtual void setItem(SessionItem *item, bool &isNew) = 0;

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

    void setSizeHint(const QSize &size_hint);

public slots:
    virtual void onModelAboutToBeReset();
    virtual void onRowsAboutToBeRemoved(const QModelIndex &parent,int first,int);
    virtual void onSelectionChanged(SessionItem *item);

protected:
    void connectModel();
    void disconnectModel();
    void validateItem(SessionItem *item);
    virtual void removeWidgetForItem(SessionItem *item) = 0;
    virtual void removeWidgets() = 0;

    class QStackedWidget *m_stackedWidget;
    SessionModel *m_model;
    QSize m_size_hint;
};

#endif // ITEMSTACKWIDGET_H
