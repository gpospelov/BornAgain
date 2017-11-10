// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/ObsoleteTestComponentView.h
//! @brief     Defines class ObsoleteTestComponentView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef OBSOLETETESTCOMPONENTVIEW_H
#define OBSOLETETESTCOMPONENTVIEW_H

#include <QWidget>

class MainWindow;
class SampleModel;
class ComponentEditor;
class QTreeView;
class QItemSelection;

class ObsoleteTestComponentView : public QWidget
{
    Q_OBJECT
public:
    ObsoleteTestComponentView(MainWindow *mainWindow = 0);

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

#endif // TESTCOMPONENTVIEW_H
