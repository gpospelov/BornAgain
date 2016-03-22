// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InstrumentView.h
//! @brief     Defines class InstrumentView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INSTRUMENTVIEW_H
#define INSTRUMENTVIEW_H

#include "WinDllMacros.h"
#include <QWidget>
#include <QString>
#include <QMap>

class InstrumentSelectorWidget;
class InstrumentEditorWidget;
class InstrumentModel;
class QListView;
class QStackedWidget;
class QMenu;
class QAction;
class QItemSelection;
class SessionItem;
class QToolBar;
class QToolButton;
class DetectorItem;

namespace Manhattan{
    class StyledBar;
}

class BA_CORE_API_ InstrumentView : public QWidget
{
    Q_OBJECT

public:
    InstrumentView(InstrumentModel *model, QWidget *parent = 0);

public slots:
    void updateView();
    void resetView();
    void onSelectionChanged(const QItemSelection&, const QItemSelection&);
    void onAddInstrument();
    void onRemoveInstrument();
    void onRowsAboutToBeRemoved(QModelIndex,int,int);
    void onExtendedDetectorEditorRequest(DetectorItem *detectorItem);

private:
    void setupConnections();
    void setupActions();
    QString getNewInstrumentName(const QString &name);
    void updateMapOfNames();

    InstrumentModel *m_instrumentModel;
    QToolBar *m_toolBar;
    InstrumentSelectorWidget *m_instrumentSelector;
    QStackedWidget *m_stackWidget;
    QMap<SessionItem *, InstrumentEditorWidget *> m_instrumentToEditor;
    QAction *m_addInstrumentAction;
    QAction *m_removeInstrumentAction;
    QToolButton *m_addInstrumentButton;
    QToolButton *m_removeInstrumentButton;

    QMap<QString, int> m_name_to_copy;
};


#endif
