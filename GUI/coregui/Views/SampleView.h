// ************************************************************************** //
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
// ************************************************************************** //

#ifndef SAMPLEVIEW_H
#define SAMPLEVIEW_H

#include "WinDllMacros.h"
#include "fancymainwindow.h"

class MainWindow;
class SampleViewDocks;
class SampleDesigner;
class SampleToolBar;
class ApplicationModels;
class QItemSelectionModel;

class BA_CORE_API_ SampleView : public Manhattan::FancyMainWindow
{
    Q_OBJECT

public:
    SampleView(MainWindow* mainWindow);

    ApplicationModels* models();

private:
    void connectSignals();

    QItemSelectionModel* selectionModel();

    ApplicationModels* m_models;

    SampleViewDocks* m_docks;

    SampleDesigner* sampleDesigner();

    SampleToolBar* m_toolBar;
};

#endif // SAMPLEVIEW_H
