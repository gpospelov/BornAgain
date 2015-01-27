// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/Components/MaterialEditor/MaterialEditor.h
//! @brief     Defines class MaterialEditor
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MATERIALEDITOR_H
#define MATERIALEDITOR_H

#include "WinDllMacros.h"
#include "MaterialProperty.h"
#include <QObject>

class MaterialModel;
class SessionModel;

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

private:
    MaterialProperty this_selectMaterialProperty();
    MaterialProperty this_getMaterialProperty(const QString &name);
    MaterialProperty this_getDefaultMaterialProperty();
    MaterialModel *this_getMaterialModel();

    static MaterialEditor *m_instance;
    MaterialModel *m_materialModel;
};



#endif


