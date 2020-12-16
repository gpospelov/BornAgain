//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleView.h
//! @brief     Defines class SampleView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEVIEW_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEVIEW_H

#include <QMainWindow>

class MainWindow;
class SampleViewDocks;
class DocksController;
class SampleDesigner;
class SampleToolBar;
class ApplicationModels;
class QItemSelectionModel;
class QShowEvent;
class QHideEvent;
class SampleViewActions;

class SampleView : public QMainWindow {
    Q_OBJECT

public:
    SampleView(MainWindow* mainWindow);

    ApplicationModels* models();

    DocksController* docks();

private:
    void connectSignals();

    QItemSelectionModel* selectionModel();

    ApplicationModels* m_models;

    SampleViewDocks* m_docks;

    SampleDesigner* sampleDesigner();

    SampleViewActions* m_actions;

    SampleToolBar* m_toolBar;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEVIEW_H
