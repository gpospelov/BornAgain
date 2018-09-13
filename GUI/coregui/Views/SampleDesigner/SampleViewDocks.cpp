// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/SampleViewDocks.h
//! @brief     Defines class SampleViewDocks
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "SampleViewDocks.h"
#include "SampleView.h"
#include "SampleDesigner.h"
#include "SampleTreeWidget.h"
#include "SamplePropertyWidget.h"
#include "InfoWidget.h"

SampleViewDocks::SampleViewDocks(SampleView* parent)
    : DocksController(parent)
    , m_widgetBox(nullptr)
    , m_treeWidget(new SampleTreeWidget(parent, parent->getSampleModel()))
    , m_propertyWidget(new SamplePropertyWidget(m_treeWidget->treeView()->selectionModel(), parent))
    , m_sampleDesigner(new SampleDesigner(parent))
    , m_infoWidget(new InfoWidget(parent))
{

}

SampleWidgetBox* SampleViewDocks::widgetBox()
{
    return m_widgetBox;
}

SampleTreeWidget* SampleViewDocks::treeWidget()
{
    return m_treeWidget;
}

SamplePropertyWidget* SampleViewDocks::propertyWidget()
{
    return m_propertyWidget;
}

SampleDesigner* SampleViewDocks::sampleDesigner()
{
    return m_sampleDesigner;
}

InfoWidget* SampleViewDocks::infoWidget()
{
    return m_infoWidget;
}
