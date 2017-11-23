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
#include "SampleModel.h"
#include "item_constants.h"
#include "SessionModelDelegate.h"
#include "StyleUtils.h"
#include "SampleBuilderFactory.h"
#include "ISample.h"
#include "GUIObjectBuilder.h"
#include "MultiLayer.h"
#include "SampleModel.h"
#include "ComponentTreeView.h"
#include "ObsoleteComponentEditor.h"
#include "minisplitter.h"
#include "ObsoleteComponentBoxEditor.h"
#include "ComponentFlatView.h"
#include "MaterialItem.h"
#include "MaterialDataItem.h"
#include "MaterialItemUtils.h"
#include <QTreeView>
#include <QBoxLayout>
#include <QItemSelectionModel>
#include <QPushButton>
#include <QDebug>
#include <limits>

TestComponentView::TestComponentView(MainWindow* mainWindow)
    : m_mainWindow(mainWindow)
    , m_sourceModel(new SampleModel(this))
    , m_sourceTree(new QTreeView)
    , m_componentTree(new ComponentTreeView)
    , m_componentFlat(new ComponentFlatView)
    , m_updateButton(new QPushButton("Update models"))
    , m_addItemButton(new QPushButton("Add item"))
    , m_expandButton(new QPushButton("Expand tree"))
    , m_obsoleteEditor(new ObsoleteComponentEditor)
    , m_obsoleteBoxEditor(new ObsoleteComponentBoxEditor)
    , m_splitter(new Manhattan::MiniSplitter)
    , m_delegate(new SessionModelDelegate(this))
    , m_isExpaned(false)
{
    auto buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(m_updateButton);
    buttonLayout->addWidget(m_addItemButton);
    buttonLayout->addWidget(m_expandButton);

    m_sourceTree->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    m_sourceTree->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    m_splitter->addWidget(m_sourceTree);
    m_splitter->addWidget(componentTreePanel());
    m_splitter->addWidget(componentBoxPanel());

    auto layout = new QVBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addLayout(buttonLayout);
    layout->addWidget(m_splitter);

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

}

void TestComponentView::onUpdateRequest()
{
    m_componentTree->setModel(m_sourceModel);
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
        m_componentTree->treeView()->expandAll();
        m_componentTree->treeView()->resizeColumnToContents(0);
        m_componentTree->treeView()->resizeColumnToContents(1);
    } else {
        m_sourceTree->collapseAll();
        m_componentTree->treeView()->collapseAll();
    }

//    const auto imax = std::numeric_limits<int>::max();
    const int imax = 1;
    QList<int> sizes = {imax, imax, imax};
    m_splitter->setSizes(sizes);

    m_isExpaned = !m_isExpaned;
}

//! Inserts test items into source model.

void TestComponentView::init_source()
{
    SampleBuilderFactory factory;
    const std::unique_ptr<ISample> sample(factory.createSample("CylindersAndPrismsBuilder"));
    GUIObjectBuilder guiBuilder;
    guiBuilder.populateSampleModel(m_sourceModel, *sample);
    m_sourceModel->insertNewItem(Constants::VectorType);
    m_sourceModel->insertNewItem(Constants::BeamType);

    // adding material to the test model
    MaterialItem* materialItem
        = dynamic_cast<MaterialItem*>(m_sourceModel->insertNewItem(Constants::HomogeneousMaterialType));
    materialItem->setItemName("air");
    MaterialDataItem* materialDataItem = dynamic_cast<MaterialDataItem*>(
        materialItem->getItem(MaterialItem::P_MATERIAL_DATA));
    Q_ASSERT(materialDataItem);
    materialDataItem->setReal(1e-3);
    materialDataItem->setImag(1e-5);
    materialItem->setItemValue(MaterialItem::P_COLOR,
                               MaterialItemUtils::suggestMaterialColorProperty("air").getVariant());

    // adding intensity data item
    m_sourceModel->insertNewItem(Constants::IntensityDataType);

//    SessionItem* multilayer = m_sourceModel->insertNewItem(Constants::MultiLayerType);
//    m_sourceModel->insertNewItem(Constants::LayerType, m_sourceModel->indexOfItem(multilayer));
//    m_sourceModel->insertNewItem(Constants::LayerType, m_sourceModel->indexOfItem(multilayer));

//    m_sourceModel->insertNewItem(Constants::VectorType);
}

void TestComponentView::onSelectionChanged(const QItemSelection& selected, const QItemSelection&)
{
    QModelIndexList indices = selected.indexes();

    if (indices.size()) {
        QModelIndex selectedIndex = indices.front();
        m_componentTree->setRootIndex(selectedIndex);
        m_componentTree->treeView()->expandAll();

        auto item = m_sourceModel->itemForIndex(indices.front());
        m_obsoleteEditor->setItem(item, item->modelType());
        m_obsoleteBoxEditor->clearEditor();
        m_obsoleteBoxEditor->addPropertyItems(item);

        m_componentFlat->addItemProperties(item);
    }

}

QWidget* TestComponentView::componentTreePanel()
{
    Manhattan::MiniSplitter* result = new Manhattan::MiniSplitter(Qt::Vertical);
    result->addWidget(m_componentTree);
    result->addWidget(m_obsoleteEditor);

    m_componentTree->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    m_obsoleteEditor->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    return result;
}

QWidget* TestComponentView::componentBoxPanel()
{
    Manhattan::MiniSplitter* result = new Manhattan::MiniSplitter(Qt::Vertical);
    result->addWidget(m_componentFlat);
    result->addWidget(m_obsoleteBoxEditor);

    m_componentFlat->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    m_obsoleteBoxEditor->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    return result;
}
