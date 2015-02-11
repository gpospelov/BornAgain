// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InstrumentWidgets/InstrumentSelectorWidget.h
//! @brief     Defines class InstrumentSelectorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INSTRUMENT_SELECTOR_WIDGET_H
#define INSTRUMENT_SELECTOR_WIDGET_H

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

    QSize sizeHint() const { return QSize(200, 600); }
    QSize minimumSizeHint() const { return QSize(128, 300); }

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


#endif

