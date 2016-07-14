// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SessionModelView.h
//! @brief     Declares class SessionModelView
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

#include <QWidget>

class MainWindow;
class QToolBar;
class QTabWidget;
class QToolButton;
class SessionModel;
class QTreeView;
class SessionModelDelegate;

//! The SessionModelView is a technical view which shows the content all current application
//! models. It appears as an additional view in the main navigation bar on the left, right
//! after the jobView (if corresponding setting of MainWindow is On).

class BA_CORE_API_ SessionModelView : public QWidget
{
    Q_OBJECT

public:
    SessionModelView(MainWindow *mainWindow = 0);

    // keeps info about tree and it's model together
    class ModelTree {
    public:
        ModelTree() : m_model(0), m_tree(0), m_is_expanded(false) {}
        ModelTree(SessionModel *model, QTreeView *tree);
        void toggleExpanded();
        void setExpanded(bool expanded);
        bool isExpanded() const { return m_is_expanded;}
        void setActive(bool is_active);
        SessionModel *m_model;
        QTreeView *m_tree;
        bool m_is_expanded;
    };

    void setViewActive(bool is_active);

private slots:
    void onExpandCollapseTree();

private:
    void init_tabs();

    MainWindow *m_mainWindow;
    QToolBar *m_toolBar;
    QTabWidget *m_tabs;
    QToolButton *m_expandCollapseButton;
    SessionModelDelegate *m_delegate;
    QVector<ModelTree> m_content;
};

#endif // SESSIONMODELVIEW_H
