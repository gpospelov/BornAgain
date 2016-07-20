// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentView.h
//! @brief     Declares class InstrumentView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef INSTRUMENTVIEW_H
#define INSTRUMENTVIEW_H

#include <QMap>
#include <QWidget>

class MainWindow;
class InstrumentSelectorWidget;
class InstrumentEditorWidget;
class InstrumentModel;
class QStackedWidget;
class QItemSelection;
class SessionItem;
class QToolButton;
class DetectorItem;


class BA_CORE_API_ InstrumentView : public QWidget
{
    Q_OBJECT

public:
    InstrumentView(MainWindow *mainWindow);

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
    class StyledToolBar *m_toolBar;
    InstrumentSelectorWidget *m_instrumentSelector;
    QStackedWidget *m_stackWidget;
    QMap<SessionItem *, InstrumentEditorWidget *> m_instrumentToEditor;
    QAction *m_addInstrumentAction;
    QAction *m_removeInstrumentAction;
    QToolButton *m_addInstrumentButton;
    QToolButton *m_removeInstrumentButton;

    QMap<QString, int> m_name_to_copy;
};


#endif // INSTRUMENTVIEW_H
