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
class DocksController;
class SampleDesigner;
class SampleToolBar;
class ApplicationModels;
class QItemSelectionModel;
class SampleWidgetBox;
class SampleTreeWidget;
class SamplePropertyWidget;
class ScriptPanel;
class RealSpacePanel;

class SampleView : public QMainWindow {
    Q_OBJECT
public:
    enum ESubWindows { WIDGET_BOX, SAMPLE_TREE, PROPERTY_EDITOR, INFO, REALSPACEPANEL };

    SampleView(MainWindow* mainWindow);

    ApplicationModels* models();
    void toggleRealSpaceView();
    void fillViewMenu(QMenu* menu);

private:
    void createSubWindows();
    void connectSignals();
    void resetLayout();

    DocksController* m_docks = nullptr;
    SampleToolBar* m_toolBar = nullptr;

    SampleDesigner* m_sampleDesigner = nullptr;
    SampleWidgetBox* m_widgetBox = nullptr;
    SampleTreeWidget* m_treeWidget = nullptr;
    SamplePropertyWidget* m_propertyWidget = nullptr;
    ScriptPanel* m_scriptPanel = nullptr;
    RealSpacePanel* m_realSpacePanel = nullptr;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEVIEW_H
