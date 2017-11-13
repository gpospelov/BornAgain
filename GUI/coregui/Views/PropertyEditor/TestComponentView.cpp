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
#include "SampleBuilderFactory.h"
#include "ISample.h"
#include "GUIObjectBuilder.h"
#include "MultiLayer.h"
#include "SampleModel.h"
#include <QTreeView>
#include <QBoxLayout>
#include <QItemSelectionModel>
#include <QPushButton>
#include <QDebug>

TestComponentView::TestComponentView(MainWindow* mainWindow)
    : m_mainWindow(mainWindow)
    , m_sourceModel(new SampleModel(this))
    , m_proxyModel(new ComponentProxyModel(this))
    , m_sourceTree(new QTreeView)
    , m_proxyTree(new QTreeView)
    , m_updateButton(new QPushButton("Update models"))
    , m_addItemButton(new QPushButton("Add item"))
    , m_expandButton(new QPushButton("Expand tree"))
    , m_delegate(new SessionModelDelegate(this))
    , m_isExpaned(false)
{
    auto buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(m_updateButton);
    buttonLayout->addWidget(m_addItemButton);
    buttonLayout->addWidget(m_expandButton);

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
    connect(m_expandButton, &QPushButton::clicked, this, &TestComponentView::onExpandRequest);

    m_sourceTree->setModel(m_sourceModel);
    m_sourceTree->setItemDelegate(m_delegate);
    StyleUtils::setPropertyStyle(m_sourceTree);
    connect(m_sourceTree->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &TestComponentView::onSelectionChanged);

    m_proxyTree->setModel(m_proxyModel);
//    m_proxyTree->setModel(m_sourceModel);
    m_proxyTree->setItemDelegate(m_delegate);
    m_proxyTree->setRootIsDecorated(false);
    StyleUtils::setPropertyStyle(m_proxyTree);
}

void TestComponentView::onUpdateRequest()
{
    qDebug() << "TestComponentView::onUpdateRequest() ->";
    m_proxyModel->setSessionModel(m_sourceModel);
    m_proxyTree->reset();
}

void TestComponentView::onAddItemRequest()
{
    m_sourceModel->insertNewItem(Constants::ParticleType);
}

void TestComponentView::onExpandRequest()
{
    if (!m_isExpaned) {
        m_sourceTree->expandAll();
        m_sourceTree->resizeColumnToContents(0);
        m_sourceTree->resizeColumnToContents(1);
        m_proxyTree->expandAll();
        m_proxyTree->resizeColumnToContents(0);
        m_proxyTree->resizeColumnToContents(1);
    } else {
        m_sourceTree->collapseAll();
        m_proxyTree->collapseAll();
    }
    m_isExpaned = !m_isExpaned;
}

//! Inserts test items into source model.

void TestComponentView::init_source()
{
//    SampleBuilderFactory factory;
//    const std::unique_ptr<ISample> sample(factory.createSample("CylindersAndPrismsBuilder"));
//    GUIObjectBuilder guiBuilder;
//    guiBuilder.populateSampleModel(m_sourceModel, *sample);
//    m_sourceModel->insertNewItem(Constants::VectorType);

    SessionItem* multilayer = m_sourceModel->insertNewItem(Constants::MultiLayerType);
    m_sourceModel->insertNewItem(Constants::LayerType, m_sourceModel->indexOfItem(multilayer));
    m_sourceModel->insertNewItem(Constants::LayerType, m_sourceModel->indexOfItem(multilayer));
}

void TestComponentView::onSelectionChanged(const QItemSelection& selected, const QItemSelection&)
{
    QModelIndexList indexes = selected.indexes();

    if (indexes.size()) {
        QModelIndex selectedIndex = indexes.front();
        SessionItem* item = m_sourceModel->itemForIndex(selectedIndex);
        QString modelType = item->modelType();
//        if (modelType ==  Constants::PropertyType || modelType == Constants::GroupItemType
//            || modelType == Constants::VectorType)
//            selectedIndex = selectedIndex.parent();

//        if (item->parent()) {
            //m_proxyTree->setRootIndex(m_proxyModel->mapFromSource(selectedIndex));
            //m_proxyTree->setRootIndex(selectedIndex);
        qDebug() << "!!!" << item->modelType();
            m_proxyModel->setRootIndex(selectedIndex);
            m_proxyTree->expandAll();
//        }
    }

}
