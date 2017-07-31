// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SessionModelView.h
//! @brief     Defines class SessionModelView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef SESSIONMODELVIEW_H
#define SESSIONMODELVIEW_H

#include "WinDllMacros.h"
#include <QWidget>

class MainWindow;
class QToolBar;
class QTabWidget;
class QToolButton;
class SessionModel;
class ModelTreeView;
class SessionModelDelegate;

//! The SessionModelView is a technical view which shows the content all current application
//! models. It appears as an additional view in the main navigation bar on the left, right
//! after the jobView (if corresponding setting of MainWindow is On).

class BA_CORE_API_ SessionModelView : public QWidget
{
    Q_OBJECT

public:
    SessionModelView(MainWindow* mainWindow = 0);

    void setViewActive(bool is_active);

private slots:
    void onExpandCollapseTree();

private:
    void init_tabs();
    QList<SessionModel*> modelsForTabs();

    MainWindow* m_mainWindow;
    QToolBar* m_toolBar;
    QTabWidget* m_tabs;
    QToolButton* m_expandCollapseButton;
    SessionModelDelegate* m_delegate;
    QVector<ModelTreeView*> m_content;
};

#endif // SESSIONMODELVIEW_H
