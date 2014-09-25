#include "FitView.h"
#include "RealDataWidget.h"
#include "FitParameterWidget.h"
#include "RunFitWidget.h"
#include "FitToolBar.h"
#include "qdebug.h"
#include "mainwindow.h"
#include <QTabWidget>
#include <QVBoxLayout>


FitView::FitView(FitModel *fitModel, MainWindow *mainWindow)
    : QWidget(mainWindow)
    , m_fitModel(fitModel)
{

    m_realDataWidget = new RealDataWidget();
    m_fitParameterWidget = new FitParameterWidget(m_fitModel);
    m_runFitWidget = new RunFitWidget();

    m_tabWidget = new QTabWidget();
    m_tabWidget->insertTab(RealDataTab, m_realDataWidget, tr("Real Data"));
    m_tabWidget->insertTab(FitParameterTab, m_fitParameterWidget, tr("Fit Parameters"));
    m_tabWidget->insertTab(RunFitTab, m_runFitWidget, tr("Run Fit"));

    connect(m_tabWidget, SIGNAL(currentChanged(int)), this, SLOT(onChangeTabWidget(int)));


    m_toolBar = new FitToolBar(this);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setSizeConstraint(QLayout::SetNoConstraint);
    mainLayout->addWidget(m_toolBar);
    mainLayout->addWidget(m_tabWidget);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);
}


void FitView::onChangeTabWidget(int index)
{

}
