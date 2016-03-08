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
#include "MaterialProperty.h"
#include <QObject>

class MaterialModel;
class SessionModel;
class MaterialItem;

//! The MaterialEditor is the main class to access materials.
class BA_CORE_API_ MaterialEditor : public QObject
{
    Q_OBJECT
public:
    MaterialEditor(MaterialModel *materialModel);
    virtual ~MaterialEditor();

    static MaterialEditor *instance();

    static MaterialProperty getMaterialProperty(const QString &name);
    static MaterialProperty selectMaterialProperty();
    static MaterialProperty getDefaultMaterialProperty();

    static MaterialModel *getMaterialModel();

    static MaterialItem *getMaterial(const MaterialProperty &property);
//    MaterialItem *getMaterial(const QString &material_name);

private:
    MaterialProperty this_selectMaterialProperty();
    MaterialProperty this_getMaterialProperty(const QString &name);
    MaterialProperty this_getDefaultMaterialProperty();
    MaterialModel *this_getMaterialModel();
    MaterialItem *this_getMaterial(const MaterialProperty &property);
//    MaterialItem *this_getMaterial(const QString &material_name);

    static MaterialEditor *m_instance;
    MaterialModel *m_materialModel;
};



#endif


