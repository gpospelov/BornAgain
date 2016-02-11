// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitView.h
//! @brief     Defines class FitView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITVIEW_H
#define FITVIEW_H

#include <WinDllMacros.h>
#include <QWidget>

class MainWindow;
class QTabWidget;
class ImportDataWidget;
class FitSettingsWidget;
class RunFitWidget;

class BA_CORE_API_ FitView : public QWidget
{
    Q_OBJECT

public:
    //! View containing tabs for fitting
    FitView(MainWindow *window);

private:
    QTabWidget *m_tabs;
    ImportDataWidget *m_importDataWidget;
    FitSettingsWidget *m_fitSettingsWidget;
    RunFitWidget *m_runFitWidget;

};

#endif
