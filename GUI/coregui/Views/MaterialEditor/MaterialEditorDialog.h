// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaterialEditor/MaterialEditorDialog.h
//! @brief     Defines class MaterialEditorDialog
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MATERIALEDITORDIALOG_H
#define MATERIALEDITORDIALOG_H

#include "MaterialProperty.h"
#include "WinDllMacros.h"
#include <QDialog>
#include <memory>

class MaterialModel;
class MaterialEditor;

//! Main widget of MaterialEditor
class BA_CORE_API_ MaterialEditorDialog : public QDialog
{
    Q_OBJECT

public:
    MaterialEditorDialog(MaterialModel *materialModel, QWidget *parent = 0);

    MaterialProperty getSelectedMaterialProperty();

    void setInitialMaterialProperty(const MaterialProperty &matProperty);

public slots:
    void onOKButton();
    void onCancelButton();

private:
    void init_material_editor();
    void readSettings();
    void writeSettings();

    MaterialModel *m_origMaterialModel;
    std::unique_ptr<MaterialModel>  m_tmpMaterialModel;
    MaterialEditor *m_materialEditor;
};

#endif
