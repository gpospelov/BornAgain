#include "QuickSimulationView.h"
#include "qdebug.h"
#include "QHBoxLayout"

QuickSimulationView::QuickSimulationView(SessionModel *sessionModel, QWidget *parent)
    : QWidget(parent)
    , m_sessionModel(sessionModel)
{

    QColor bgColor(0,0,255,255);
    QPalette palette;
    palette.setColor(QPalette::Background, bgColor);
    setAutoFillBackground(true);
    //setPalette(palette);

    m_plotWidget = new PlotWidget(false);
    m_plotWidget->setObjectName(QString::fromUtf8("OutputDataWidget::customPlot"));
    m_plotWidget->setProjectionsVisible(false);
    m_plotWidget->setPropertyPanelVisible(false);
    //m_plotWidget->setFixedWidth(600);

    m_testView = new TestView(m_sessionModel);
    m_testView->setFixedWidth(380);
    m_testView->setContentsMargins(0,0,0,0);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addStretch();
    mainLayout->addWidget(m_plotWidget);
    mainLayout->addStretch();
    mainLayout->addWidget(m_testView);

    mainLayout->setContentsMargins(0,0,0,0);

    setLayout(mainLayout);
}

void QuickSimulationView::updateViews()
{
    m_testView->updateTreeView();
}








