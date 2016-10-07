// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataView.cpp
//! @brief     Implements class ImportDataView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ImportDataView.h"
#include "ImportDataToolBar.h"
#include "ItemSelectorWidget.h"
#include "RealDataModel.h"
#include "RealDataSelectorWidget.h"
#include "mainwindow.h"
#include "mainwindow_constants.h"
#include "minisplitter.h"
#include <QVBoxLayout>

ImportDataView::ImportDataView(MainWindow *mainWindow)
    : QWidget(mainWindow)
    , m_toolBar(new ImportDataToolBar)
    , m_splitter(new Manhattan::MiniSplitter)
    , m_selectorWidget(new RealDataSelectorWidget)
//    , m_stackedWidget(new ItemStackPresenter<RealDataEditorWidget>)
    , m_stackedWidget(new ItemStackPresenter<RealDataMaskWidget>)
    , m_realDataModel(mainWindow->realDataModel())
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0,0,0,0);

    m_stackedWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_selectorWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    m_stackedWidget->setSizeHint(QSize(1024, 1024));

    m_splitter->addWidget(m_selectorWidget);
    m_splitter->addWidget(m_stackedWidget);
    m_splitter->setCollapsible(0, false);
    m_splitter->setCollapsible(1, false);

    m_splitter->setSizes(QList<int>() << Constants::ITEM_SELECTOR_WIDGET_WIDTH
                         << Constants::ITEM_SELECTOR_WIDGET_WIDTH*7);

    mainLayout->addWidget(m_toolBar);
    mainLayout->addWidget(m_splitter);

    setLayout(mainLayout);

    setupConnections();

    m_selectorWidget->setModels(mainWindow->instrumentModel(), mainWindow->realDataModel());
    m_stackedWidget->setModel(mainWindow->realDataModel());
    m_toolBar->setRealDataModel(mainWindow->realDataModel());
    m_toolBar->setInstrumentModel(mainWindow->instrumentModel());
    m_toolBar->setSelectionModel(m_selectorWidget->selectionModel());
}

void ImportDataView::onSelectionChanged(SessionItem *item)
{
    if(!item) return;

    bool isNew(false);
    m_stackedWidget->setItem(item, isNew);
    if(isNew) {
//        RealDataEditorWidget *widget = m_stackedWidget->currentWidget();
        RealDataMaskWidget *widget = m_stackedWidget->currentWidget();
        Q_ASSERT(widget);
        widget->setItem(item);
    }
    m_toolBar->setActionList(m_stackedWidget->currentWidget()->actionList());

}

void ImportDataView::setupConnections()
{
    connect(m_selectorWidget, SIGNAL(selectionChanged(SessionItem *)),
        this, SLOT(onSelectionChanged(SessionItem *)));
}
