// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitView.h
//! @brief     Defines class FitView
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITVIEW_H
#define FITVIEW_H

#include "FitProxyModel.h"
#include "WinDllMacros.h"
#include <QWidget>


class MainWindow;
class QTabWidget;
class RealDataWidget;
class FitParameterWidget;
class RunFitWidget;
class FitToolBar;

class BA_CORE_API_ FitView : public QWidget
{
    Q_OBJECT

public:
    enum ETabViewId { REAL_DATA, FIT_PARAMETER, RUN_FIT};
    FitView(FitProxyModel *fitProxyModel, MainWindow *mainWindow);


public slots:
    void onChangeTabWidget(int index);

private:

    QTabWidget *m_tabWidget;
    RealDataWidget *m_realDataWidget;
    FitParameterWidget *m_fitParameterWidget;
    RunFitWidget *m_runFitWidget;
    FitToolBar *m_toolBar;

    FitProxyModel *m_fitProxyModel;

};


#endif // SIMULATIONVIEW_H
