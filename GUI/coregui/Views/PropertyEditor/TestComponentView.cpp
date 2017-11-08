// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/TestComponentView.cpp
//! @brief     Defines class TestComponentView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "TestComponentView.h"
#include "mainwindow.h"
#include "ComponentProxyModel.h"
#include "SampleModel.h"
#include <QTreeView>
#include <QBoxLayout>
#include <QPushButton>
#include <QDebug>

TestComponentView::TestComponentView(MainWindow* mainWindow)
    : m_mainWindow(mainWindow)
    , m_proxyModel(new ComponentProxyModel(this))
    , m_sourceTree(new QTreeView)
    , m_proxyTree(new QTreeView)
    , m_updateButton(new QPushButton("Update models"))
{
    auto layout = new QHBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(0);

    layout->addWidget(m_sourceTree);
    layout->addWidget(m_proxyTree);

    // vertical layout
    auto vlayout = new QVBoxLayout;
    auto button = new QPushButton("Update models");
    connect(button, &QPushButton::clicked, this, &TestComponentView::onUpdateRequest);

    vlayout->addWidget(button);
    vlayout->addLayout(layout);

    setLayout(vlayout);

    m_sourceTree->setModel(m_mainWindow->sampleModel());
}

void TestComponentView::onUpdateRequest()
{
    qDebug() << "TestComponentView::onUpdateRequest() ->";
    m_proxyTree->setModel(m_proxyModel);
    m_proxyModel->setSessionModel(m_mainWindow->sampleModel());
}
