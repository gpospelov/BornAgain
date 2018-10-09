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
#include "ApplicationModels.h"
#include "FilterPropertyProxy.h"
#include "InfoWidget.h"
#include "SampleDesigner.h"
#include "SamplePropertyWidget.h"
#include "SampleTreeWidget.h"
#include "SampleView.h"
#include "SampleWidgetBox.h"
#include <QDockWidget>
#include <QTreeView>

SampleViewDocks::SampleViewDocks(SampleView* parent)
    : DocksController(parent), m_sampleDesigner(new SampleDesigner(parent)),
      m_widgetBox(new SampleWidgetBox(sampleDesigner(), parent)),
      m_treeWidget(new SampleTreeWidget(parent, parent->models()->sampleModel())),
      m_propertyWidget(
          new SamplePropertyWidget(m_treeWidget->treeView()->selectionModel(), parent)),
      m_infoWidget(new InfoWidget(parent))
{
    addWidget(WIDGET_BOX, m_widgetBox, Qt::LeftDockWidgetArea);
    addWidget(SAMPLE_TREE, m_treeWidget, Qt::RightDockWidgetArea);
    addWidget(PROPERTY_EDITOR, m_propertyWidget, Qt::RightDockWidgetArea);
    addWidget(INFO, m_infoWidget, Qt::BottomDockWidgetArea);

    connect(m_infoWidget, &InfoWidget::widgetHeightRequest, this,
            &DocksController::setDockHeightForWidget);
    connect(m_infoWidget, &InfoWidget::widgetCloseRequest, this,
            &SampleViewDocks::onWidgetCloseRequest);

    m_infoWidget->setSampleModel(parent->models()->sampleModel());
    m_infoWidget->setInstrumentModel(parent->models()->instrumentModel());

    m_sampleDesigner->setModels(parent->models());
    m_sampleDesigner->setSelectionModel(
        m_treeWidget->treeView()->selectionModel(),
        dynamic_cast<FilterPropertyProxy*>(
            const_cast<QAbstractItemModel*>(m_treeWidget->treeView()->model())));

    parent->setCentralWidget(m_sampleDesigner->getCentralWidget());
    onResetLayout();
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
