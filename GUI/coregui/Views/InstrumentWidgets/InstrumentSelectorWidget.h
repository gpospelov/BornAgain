// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/InstrumentSelectorWidget.h
//! @brief     Declares class InstrumentSelectorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef INSTRUMENTSELECTORWIDGET_H
#define INSTRUMENTSELECTORWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>
class InstrumentModel;
class QListView;
class QAction;
class QItemSelectionModel;
class QItemSelection;


class BA_CORE_API_ InstrumentSelectorWidget : public QWidget
{
    Q_OBJECT

public:
    InstrumentSelectorWidget(InstrumentModel *model, QWidget *parent = 0);

    QSize sizeHint() const { return QSize(200, 400); }
    QSize minimumSizeHint() const { return QSize(128, 200); }

    void setInstrumentModel(InstrumentModel *model);

    QItemSelectionModel *getSelectionModel();
    QListView *getListView() { return m_listView; }

signals:
    void selectionChanged(const QItemSelection&, const QItemSelection&);

public slots:
    void updateSelection();

private:
    InstrumentModel *m_instrumentModel;
    QListView *m_listView;
};


#endif // INSTRUMENTSELECTORWIDGET_H

