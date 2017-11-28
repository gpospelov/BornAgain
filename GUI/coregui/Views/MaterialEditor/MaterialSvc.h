// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaterialEditor/MaterialSvc.h
//! @brief     Defines class MaterialSvc
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef MATERIALSVC_H
#define MATERIALSVC_H

#include "MaterialProperty.h"
#include "WinDllMacros.h"
#include <QObject>

class MaterialModel;
class SessionModel;
class MaterialItem;

//! The MaterialEditor is the main class to access materials.
class BA_CORE_API_ MaterialSvc : public QObject
{
    Q_OBJECT
public:
    MaterialSvc();
    virtual ~MaterialSvc();

    static MaterialSvc *instance();

    static MaterialProperty selectMaterialProperty(const MaterialProperty &previousMaterial=MaterialProperty());
    static MaterialProperty getDefaultMaterialProperty();

    static MaterialItem *getMaterial(const MaterialProperty &property);

private:
    MaterialProperty this_selectMaterialProperty(const MaterialProperty &previousMaterial);
    MaterialProperty this_getDefaultMaterialProperty();
    MaterialItem *this_getMaterial(const MaterialProperty &property);

    static MaterialSvc *m_instance;
};



#endif // MATERIALSVC_H


