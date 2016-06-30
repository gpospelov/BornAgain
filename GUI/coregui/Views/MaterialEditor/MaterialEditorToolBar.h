// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaterialEditor/MaterialEditorToolBar.h
//! @brief     Declares class MaterialEditorToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef MATERIALEDITORTOOLBAR_H
#define MATERIALEDITORTOOLBAR_H

#include "WinDllMacros.h"
#include <QToolBar>

class QAction;
class MaterialModel;
class QItemSelectionModel;
class QPoint;
class QMenu;

//! Main widget of MaterialEditor
class BA_CORE_API_ MaterialEditorToolBar : public QToolBar
{
    Q_OBJECT
public:
    MaterialEditorToolBar(MaterialModel *materialModel, QWidget *parent = 0);

    void setSelectionModel(QItemSelectionModel *selectionModel);

public slots:
    void onCustomContextMenuRequested(const QPoint &point);

private slots:
    void onNewMaterialAction();
    void onCloneMaterialAction();
    void onRemoveMaterialAction();

private:
    void initItemContextMenu(QMenu &menu);

    MaterialModel *m_materialModel;
    QItemSelectionModel *m_selectionModel;
    QAction *m_newMaterialAction;
    QAction *m_cloneMaterialAction;
    QAction *m_removeMaterialAction;
};

#endif
