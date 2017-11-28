// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaterialEditor/MaterialSvc.cpp
//! @brief     Implements class MaterialSvc
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "MaterialSvc.h"
#include "MaterialEditorDialog.h"
#include "MaterialItem.h"
#include "MaterialModel.h"
#include "SessionModel.h"
#include "AppSvc.h"

MaterialSvc *MaterialSvc::m_instance = 0;

MaterialSvc::MaterialSvc()
{
    Q_ASSERT(!m_instance);
    m_instance = this;
}


MaterialSvc::~MaterialSvc()
{
    m_instance = 0;
}

MaterialSvc *MaterialSvc::instance()
{
    return m_instance;
}

MaterialItem *MaterialSvc::getMaterial(const MaterialProperty &property)
{
    Q_ASSERT(m_instance);
    return m_instance->this_getMaterial(property);
}


MaterialItem *MaterialSvc::this_getMaterial(const MaterialProperty &property)
{
    return AppSvc::materialModel()->getMaterial(property);
}

