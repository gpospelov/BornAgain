// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaterialEditor/MaterialEditor.h
//! @brief     Defines class MaterialEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MATERIALEDITOR_H
#define MATERIALEDITOR_H

#include "WinDllMacros.h"
#include <QWidget>

class MaterialModel;
class MaterialEditorToolBar;
class QSplitter;
class QListView;
class ComponentEditor;
class QItemSelection;
class QItemSelectionModel;
class MaterialItem;

//! Main widget of MaterialEditor
class BA_CORE_API_ MaterialEditor : public QWidget
{
    Q_OBJECT

public:
    MaterialEditor(MaterialModel *materialModel, QWidget *parent = 0);

    QItemSelectionModel *getSelectionModel();

    MaterialItem *getSelectedMaterial();

private slots:
    void onSelectionChanged(const QItemSelection &selected, const QItemSelection&);

protected:
    void contextMenuEvent(QContextMenuEvent *event);

private:
    void init_views();

    MaterialModel *m_materialModel;
    MaterialEditorToolBar *m_toolBar;
    QSplitter *m_splitter;
    QListView *m_listView;
    ComponentEditor *m_componentEditor;
};


#endif

