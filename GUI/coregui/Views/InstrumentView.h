// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentView.h
//! @brief     Defines class InstrumentView
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

#include "WinDllMacros.h"
#include "ItemStackPresenter.h"
#include <QWidget>

class MainWindow;
class DetectorItem;
class InstrumentViewActions;
class InstrumentViewToolBar;
class InstrumentSelectorWidget;
class InstrumentEditorWidget;
class InstrumentModel;

class BA_CORE_API_ InstrumentView : public QWidget
{
    Q_OBJECT

public:
    InstrumentView(MainWindow* mainWindow);

public slots:
    void onExtendedDetectorEditorRequest(DetectorItem* detectorItem);

private slots:
    void onItemSelectionChanged(SessionItem* instrumentItem);

protected:
    void showEvent(QShowEvent*);

private:
    InstrumentViewActions* m_actions;
    InstrumentViewToolBar* m_toolBar;
    InstrumentSelectorWidget* m_instrumentSelector;
    ItemStackPresenter<InstrumentEditorWidget>* m_instrumentEditor;
    InstrumentModel* m_instrumentModel;
};

#endif // INSTRUMENTVIEW_H
