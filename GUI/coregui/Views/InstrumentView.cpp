// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentView.cpp
//! @brief     Implements class InstrumentView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "InstrumentView.h"
#include "ExtendedDetectorDialog.h"
#include "InstrumentEditorWidget.h"
#include "InstrumentModel.h"
#include "InstrumentSelectorWidget.h"
#include "InstrumentViewActions.h"
#include "InstrumentViewToolBar.h"
#include "mainwindow.h"
#include <QBoxLayout>

InstrumentView::InstrumentView(MainWindow* mainWindow)
    : QWidget(mainWindow), m_actions(new InstrumentViewActions(this)),
      m_toolBar(new InstrumentViewToolBar(m_actions, this)),
      m_instrumentSelector(new InstrumentSelectorWidget),
      m_instrumentEditor(new ItemStackPresenter<InstrumentEditorWidget>(true)),
      m_instrumentModel(mainWindow->instrumentModel())
{
    auto horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(m_instrumentSelector);
    horizontalLayout->addWidget(m_instrumentEditor, 1);

    auto mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(m_toolBar);
    mainLayout->addLayout(horizontalLayout);
    setLayout(mainLayout);

    m_instrumentSelector->setModel(m_instrumentModel);
    m_actions->setModel(m_instrumentModel);
    m_actions->setSelectionModel(m_instrumentSelector->selectionModel());

    connect(m_instrumentSelector, &InstrumentSelectorWidget::contextMenuRequest, m_actions,
            &InstrumentViewActions::onContextMenuRequest);

    connect(m_instrumentSelector, &InstrumentSelectorWidget::selectionChanged, this,
            &InstrumentView::onItemSelectionChanged);
}

void InstrumentView::onExtendedDetectorEditorRequest(DetectorItem* detectorItem)
{
    auto dialog = new ExtendedDetectorDialog(this);
    dialog->setDetectorContext(m_instrumentModel, detectorItem);
    dialog->show();
}

void InstrumentView::onItemSelectionChanged(SessionItem* instrumentItem)
{
    m_instrumentEditor->setItem(instrumentItem);
}

void InstrumentView::showEvent(QShowEvent*)
{
    m_instrumentSelector->updateSelection();
}
