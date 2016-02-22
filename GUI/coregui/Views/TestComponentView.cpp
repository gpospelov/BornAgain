// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/TestView.cpp
//! @brief     Implements class TestView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //
#include "TestComponentView.h"
#include "mainwindow.h"
#include "SessionModel.h"
#include "ComponentEditor.h"
#include "item_constants.h"
#include "MultiLayerItem.h"
#include <QHBoxLayout>
#include <QTreeView>

TestComponentView::TestComponentView(MainWindow *mainWindow)
    : QWidget(mainWindow)
    , m_mainWindow(mainWindow)
{
    test_ComponentEditor();
}

void TestComponentView::test_ComponentEditor()
{
    QHBoxLayout *layout = new QHBoxLayout;

    QTreeView *treeView = new QTreeView();
    ComponentEditor *componentEditor = new ComponentEditor();

    layout->addWidget(treeView);
    layout->addWidget(componentEditor);

    setLayout(layout);

    // ---

    SessionModel *model = new SessionModel("XXX");
    ParameterizedItem *item = model->insertNewItem(Constants::MultiLayerType);

    componentEditor->addItem(item->getChildByName(MultiLayerItem::P_CROSS_CORR_LENGTH));


    treeView->setModel(model);
}
