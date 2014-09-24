#include "AdvModelTuningWidget.h"
#include "JobItem.h"
#include "QuickSimulationSettings.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QTreeView>

AdvModelTuningWidget::AdvModelTuningWidget(QWidget *parent)
    : QWidget(parent)
    , m_currentJobItem(0)
    , m_quickSimulationSettings(0)
{
    setMinimumSize(128, 128);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

//    QColor bgColor(0,0,255,255);
//    QPalette palette;
//    palette.setColor(QPalette::Background, bgColor);
//    setAutoFillBackground(true);

    m_quickSimulationSettings = new QuickSimulationSettings();

    m_treeView = new QTreeView();
    m_treeView->setStyleSheet("QTreeView::branch {background: palette(base);}QTreeView::branch:has-siblings:!adjoins-item {border-image: url(:/images/treeview-vline.png) 0;}QTreeView::branch:has-siblings:adjoins-item {border-image: url(:/images/treeview-branch-more.png) 0;}QTreeView::branch:!has-children:!has-siblings:adjoins-item {border-image: url(:/images/treeview-branch-end.png) 0;}QTreeView::branch:has-children:!has-siblings:closed,QTreeView::branch:closed:has-children:has-siblings {border-image: none;image: url(:/images/treeview-branch-closed.png);}QTreeView::branch:open:has-children:!has-siblings,QTreeView::branch:open:has-children:has-siblings  {border-image: none;image: url(:/images/treeview-branch-open.png);}");

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    mainLayout->addWidget(m_quickSimulationSettings);
    mainLayout->addWidget(m_treeView);
    mainLayout->addStretch();

    setLayout(mainLayout);

}

void AdvModelTuningWidget::setCurrentItem(JobItem *item)
{
    m_currentJobItem = item;
}
