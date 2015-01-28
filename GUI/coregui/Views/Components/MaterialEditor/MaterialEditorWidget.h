// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/Components/MaterialEditor/MaterialEditorWidget.h
//! @brief     Defines class MaterialEditorWidget
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MATERIALEDITORWIDGET_H
#define MATERIALEDITORWIDGET_H

#include <QDialog>

#include "MaterialProperty.h"
#include "WinDllMacros.h"


class MaterialModel;
class MaterialPropertyBrowser;
class QStatusBar;
class QToolBar;

//! Main widget of MaterialEditor
class BA_CORE_API_ MaterialEditorWidget : public QDialog
{
    Q_OBJECT

public:

    explicit MaterialEditorWidget(MaterialModel *materialModel, QWidget *parent = 0);
    virtual ~MaterialEditorWidget(){}

    void setModel(MaterialModel *materialModel);

    MaterialProperty getSelectedMaterialProperty();

public slots:
    void addMaterial();
    void removeMaterial();
    void showMessage(const QString &message);
    void onSelectButton();
    void onCancelButton();

private:
    void setupActions();

    MaterialModel *m_materialModel;
    MaterialPropertyBrowser *m_propertyBrowser;
    QStatusBar *m_statusBar;
    QToolBar *m_toolBar;
    static int m_IndexOfUnnamed;
};



#endif
