// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/Components/OutputDataWidgets/OutputDataWidget.cpp
//! @brief     Implements class OutputDataWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "OutputDataWidget.h"
#include "PlotWidget.h"
#include "PropertyWidget.h"
#include "OutputDataToolBar.h"
#include "projectmanager.h"
#include <QVBoxLayout>
#include <QModelIndex>
#include <QMouseEvent>


OutputDataWidget::OutputDataWidget(QWidget *parent, bool isCreateToolBar, bool isCreatePropertyWidget, bool isProjections)
    : QWidget(parent)
    , m_plotWidget(0)
    , m_data(0)
    , m_propertyWidget(0)
    , m_toolBar(0)
    , m_gradient(QCPColorGradient::gpPolar)
    , m_currentOutputDataItem(0)
    , m_isProjectionsVisible(isProjections)

{
    qDebug() << " ";
    qDebug() << "OutputDataWidget::OutputDataWidget() -> c-tor";
//    setModel(model);

    setMinimumSize(600, 600);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setWindowTitle(QLatin1String("Job Properties"));
    setObjectName(QLatin1String("Job Properties"));
//    setStyleSheet("background-color:white;");



    m_plotWidget = new PlotWidget(0, true, m_isProjectionsVisible);
    connect(m_plotWidget, SIGNAL(projectionsVisibilityChanged(bool)),this, SLOT(projectionsChanged(bool)));
    connect(m_plotWidget, SIGNAL(propertyWidgetVisibilityChanged(bool)),this, SLOT(setPropertyPanelVisible(bool)));


//    m_splitter = new QSplitter(this);
//    m_splitter->setStyleSheet("background-color:white;");
//    m_splitter->addWidget(m_plotWidget);

    m_propertyWidget = new PropertyWidget(this, m_isProjectionsVisible);
    connect(m_propertyWidget, SIGNAL(projectionsChanged(bool)), this, SLOT(projectionsChanged(bool)));
    connect(m_propertyWidget, SIGNAL(gradientChanged(QCPColorGradient)), this, SLOT(gradientChanged(QCPColorGradient)));

    //m_splitter->addWidget(m_propertyWidget);
    //connect(m_splitter, SIGNAL(splitterMoved(int,int)), this, SLOT(onPropertySplitterMoved(int,int)));
    //m_currentPropertyWidgetWidth = m_propertyWidget->getWidth();


    m_layout = new QHBoxLayout;
    m_layout->setMargin(0);
    m_layout->setSpacing(0);

    m_layout->addWidget(m_plotWidget);
    m_layout->addWidget(m_propertyWidget);

    m_mainLayout = new QVBoxLayout;
    m_mainLayout->setMargin(0);
    m_mainLayout->setSpacing(0);

    if(isCreateToolBar)
    {
        m_toolBar = new OutputDataToolBar();
        //m_toolBar->hide();
        connectToobarSignals();
        m_mainLayout->addWidget(m_toolBar);
    }

    m_mainLayout->addLayout(m_layout);
    setLayout(m_mainLayout);

    m_propertyWidget->setVisible(isCreatePropertyWidget);

}


void OutputDataWidget::setCurrentItem(NIntensityDataItem *item)
{
    qDebug() << "OutputDataWidget::setCurrentItem()" << item;
    m_currentOutputDataItem = item;

    m_plotWidget->drawPlot(item);

    m_propertyWidget->updateData(item, m_gradient);


    //connectPropertyWidgetSignals(isPropertyWidgetVisible);

}

void OutputDataWidget::setProjectManager(ProjectManager *projectManager)
{
    if(m_projectManager == projectManager)
        return;

    m_projectManager = projectManager;
    if(m_plotWidget)
    {
        m_plotWidget->setProjectManager(projectManager);
    }

}

void OutputDataWidget::connectToobarSignals()
{
    connect(m_toolBar, SIGNAL(togglePropertyPanel()), this, SLOT(togglePropertyPanel()));
    connect(m_toolBar, SIGNAL(toggleProjections()), this, SLOT(toggleProjections()));
    connect(m_toolBar, SIGNAL(resetView()), this, SLOT(resetTriggered()));
    connect(m_toolBar, SIGNAL(savePlot()), this, SLOT(savePlot()));

}

void OutputDataWidget::togglePropertyPanel()
{
    //qDebug() << "OutputDataWidget::togglePropertyPanel()";
    setPropertyPanelVisible(!m_propertyWidget->isVisible());

}

void OutputDataWidget::setPropertyPanelVisible(bool visible)
{
    //int width = 0;
    if(visible)
    {
        //width = m_propertyWidget->getWidth();
        m_propertyWidget->updateData(m_currentOutputDataItem, m_gradient);
    }
    else
    {
        //width = 0;
        m_propertyWidget->updateData(0);
    }
    m_propertyWidget->setVisible(visible);
    m_plotWidget->setPropertyWidgetVisibilityFlag(visible);

}


/*void OutputDataWidget::onPropertySplitterMoved(int pos, int index)
{

    QList<int> sizes_org = this->m_splitter->sizes();

    if(sizes_org.at(index) != m_currentPropertyWidgetWidth)
    {

        if(sizes_org.at(index) == m_propertyWidget->getWidth())
        {
            qDebug() << "OutputDataWidget::onPropertySplitterMoved() about to enable propertyWidget";
            m_currentPropertyWidgetWidth = sizes_org.at(1);
            m_propertyWidget->updateData(m_currentOutputDataItem, m_gradient);
        }
        else
        {
            qDebug() << "OutputDataWidget::onPropertySplitterMoved() about to disable propertyWidget";
            m_currentPropertyWidgetWidth = 0;
            m_propertyWidget->updateData(0, m_gradient);
        }


    }
}*/

void OutputDataWidget::toggleProjections()
{
    m_propertyWidget->toggleProjections();
}

void OutputDataWidget::resetTriggered()
{
    m_plotWidget->resetTriggered();
}

void OutputDataWidget::savePlot()
{

    m_plotWidget->savePlot();

}

void OutputDataWidget::projectionsChanged(bool projection)
{
    if(m_isProjectionsVisible == projection)
    {
        return;
    }

    m_isProjectionsVisible = projection;
    m_plotWidget->projectionsChanged(projection);
    m_propertyWidget->setProjections(projection);
}

void OutputDataWidget::gradientChanged(QCPColorGradient gradient)
{
    m_gradient = gradient;
    m_plotWidget->gradientChanged(gradient);

}





