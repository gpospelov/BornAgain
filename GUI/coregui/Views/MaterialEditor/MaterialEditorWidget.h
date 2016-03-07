// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaterialEditor/MaterialEditorWidget.h
//! @brief     Defines class MaterialEditorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MATERIALEDITORWIDGET_H
#define MATERIALEDITORWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class MaterialModel;
class MaterialEditorToolBar;
class QSplitter;
class QListView;
class ComponentEditor;
class QItemSelection;

//! Main widget of MaterialEditor
class BA_CORE_API_ MaterialEditorWidget : public QWidget
{
    Q_OBJECT

public:
    MaterialEditorWidget(MaterialModel *materialModel, QWidget *parent = 0);


private slots:
    void onSelectionChanged(const QItemSelection &selected, const QItemSelection&);

private:
    void init_views();

    MaterialModel *m_materialModel;
    MaterialEditorToolBar *m_toolBar;
    QSplitter *m_splitter;
    QListView *m_listView;
    ComponentEditor *m_componentEditor;
};


#endif

