// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/PropertyEditor/ComponentEditorPrivate.cpp
//! @brief     Implements class ComponentEditorPrivate
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ComponentEditorPrivate.h"
#include "PropertyVariantManager.h"
#include "PropertyVariantFactory.h"
#include "qttreepropertybrowser.h"
#include "qtgroupboxpropertybrowser.h"
#include "qtbuttonpropertybrowser.h"


ComponentEditorPrivate::ComponentEditorPrivate(QWidget *parent)
    : m_browser(0)
    , m_manager(0)
    , m_read_only_manager(0)
    , m_propertyFactory(new PropertyVariantFactory(parent))
{
    QtTreePropertyBrowser *browser = new QtTreePropertyBrowser(parent);
    browser->setResizeMode(QtTreePropertyBrowser::Interactive);
    browser->setRootIsDecorated(false);
    m_browser = browser;

    m_read_only_manager = new PropertyVariantManager(parent);

    m_manager = new PropertyVariantManager(parent);
    m_browser->setFactoryForManager(m_manager, m_propertyFactory);
}

