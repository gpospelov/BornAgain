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
#include "item_constants.h"
#include "SessionModelDelegate.h"
#include "StyleUtils.h"
#include <QTreeView>
#include <QBoxLayout>
#include <QPushButton>
#include <QDebug>

TestComponentView::TestComponentView(MainWindow* mainWindow)
    : m_mainWindow(mainWindow)
    , m_sourceModel(new SessionModel("TestModel", this))
    , m_proxyModel(new ComponentProxyModel(this))
    , m_sourceTree(new QTreeView)
    , m_proxyTree(new QTreeView)
    , m_updateButton(new QPushButton("Update models"))
    , m_addItemButton(new QPushButton("Add item"))
    , m_delegate(new SessionModelDelegate(this))
{
    auto buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(m_updateButton);
    buttonLayout->addWidget(m_addItemButton);
    buttonLayout->addStretch();

    auto widgetLayout = new QHBoxLayout;
    widgetLayout->addWidget(m_sourceTree);
    widgetLayout->addWidget(m_proxyTree);

    auto layout = new QVBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addLayout(buttonLayout);
    layout->addLayout(widgetLayout);

    setLayout(layout);

    init_source();

    connect(m_updateButton, &QPushButton::clicked, this, &TestComponentView::onUpdateRequest);
    connect(m_addItemButton, &QPushButton::clicked, this, &TestComponentView::onAddItemRequest);

    m_sourceTree->setModel(m_sourceModel);
    m_sourceTree->setItemDelegate(m_delegate);
    m_sourceTree->setStyleSheet(StyleUtils::propertyTreeStyle());
    m_sourceTree->setAlternatingRowColors(true);

    m_proxyTree->setModel(m_proxyModel);
    m_proxyTree->setItemDelegate(m_delegate);
    m_proxyTree->setStyleSheet(StyleUtils::propertyTreeStyle());
    m_proxyTree->setAlternatingRowColors(true);
}

void TestComponentView::onUpdateRequest()
{
    qDebug() << "TestComponentView::onUpdateRequest() ->";
    m_proxyModel->setSessionModel(m_sourceModel);
}

void TestComponentView::onAddItemRequest()
{
    m_sourceModel->insertNewItem(Constants::ParticleType);
}

//! Inserts test items into source model.

void TestComponentView::init_source()
{
    m_sourceModel->insertNewItem(Constants::VectorType);
}
