// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaterialEditor/MaterialEditor.h
//! @brief     Defines class MaterialEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
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
class MaterialProperty;

//! Main widget of MaterialEditor

class BA_CORE_API_ MaterialEditor : public QWidget
{
    Q_OBJECT

public:
    MaterialEditor(MaterialModel* materialModel, QWidget* parent = 0);

    QItemSelectionModel* getSelectionModel();

    MaterialItem* getSelectedMaterial();

    void setInitialMaterialProperty(const MaterialProperty& matProperty);

    bool isModelWasModified() const;

private slots:
    void onSelectionChanged(const QItemSelection& selected, const QItemSelection&);
    void onDataChanged(const QModelIndex&, const QModelIndex&, const QVector<int>&);
    void onRowsInserted(const QModelIndex&, int, int);
    void onRowsRemoved(const QModelIndex&, int, int);

protected:
    void contextMenuEvent(QContextMenuEvent* event);

private:
    void init_views();

    MaterialModel* m_materialModel;
    MaterialEditorToolBar* m_toolBar;
    QSplitter* m_splitter;
    QListView* m_listView;
    ComponentEditor* m_componentEditor;
    bool m_model_was_modified;
};

#endif // MATERIALEDITOR_H

