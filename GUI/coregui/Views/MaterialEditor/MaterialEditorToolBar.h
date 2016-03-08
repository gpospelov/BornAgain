// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaterialEditor/MaterialEditorToolBar.h
//! @brief     Defines class MaterialEditorToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MATERIALEDITORTOOLBAR_H
#define MATERIALEDITORTOOLBAR_H

#include "WinDllMacros.h"
#include <QToolBar>

class QAction;
class MaterialModel;
class QItemSelectionModel;

//! Main widget of MaterialEditor
class BA_CORE_API_ MaterialEditorToolBar : public QToolBar
{
    Q_OBJECT
public:
    MaterialEditorToolBar(MaterialModel *materialModel, QWidget *parent = 0);

    void setSelectionModel(QItemSelectionModel *selectionModel);

private slots:
    void onNewMaterialAction();
    void onCloneMaterialAction();
    void onRemoveMaterialAction();

private:
    MaterialModel *m_materialModel;
    QItemSelectionModel *m_selectionModel;
    QAction *m_newMaterialAction;
    QAction *m_cloneMaterialAction;
    QAction *m_removeMaterialAction;
};

#endif
