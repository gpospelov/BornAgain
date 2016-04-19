// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/TestComponentView.h
//! @brief     Declares class TestComponentView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef TECTCOMPONENTVIEW_H
#define TECTCOMPONENTVIEW_H

#include <QWidget>

class MainWindow;
class SampleModel;
class ComponentEditor;
class ComponentProxyEditor;
class QTreeView;
class QItemSelection;

class TestComponentView : public QWidget
{
    Q_OBJECT
public:
    TestComponentView(MainWindow *mainWindow = 0);

private slots:
    void onSelectionChanged(const QItemSelection &, const QItemSelection &);

private:
    void init_editors();

    MainWindow *m_mainWindow;
    SampleModel *m_model;
    QTreeView *m_treeView;
    QTreeView *m_treeView2;
    ComponentEditor *m_editor1;
    ComponentEditor *m_editor2;
    ComponentEditor *m_editor3;
};

#endif
