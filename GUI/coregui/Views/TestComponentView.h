// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/TestComponentView.h
//! @brief     Defines class TestComponentView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TECTCOMPONENTVIEW_H
#define TECTCOMPONENTVIEW_H

#include <QWidget>

class MainWindow;
class SampleModel;
class ComponentEditor;
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
    ComponentEditor *m_editor1;
    ComponentEditor *m_editor2;
};

#endif
