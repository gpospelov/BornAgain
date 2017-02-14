// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/IntensityDataWidget.cpp
//! @brief     Implements class IntensityDataWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "IntensityDataWidget.h"
#include "IntensityDataItem.h"
#include "IntensityDataPropertyWidget.h"
#include "IntensityDataCanvas.h"
#include "RealDataItem.h"
#include "SessionItem.h"
#include "JobItem.h"
#include <QAction>
#include <QBoxLayout>
#include <QMenu>
#include <QLabel>
#include <QDebug>

TestWidget::TestWidget(QWidget* parent) : NewSessionItemWidget(parent), m_label(new QLabel("XXX"))
{
    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->setMargin(0);
    hlayout->setSpacing(0);

    hlayout->addWidget(m_label);
    setLayout(hlayout);
}

void TestWidget::subscribeToItem()
{
    Q_ASSERT(currentItem());

    qDebug() << "TestWidget::subscribeToItem()" << currentItem()->modelType();
    currentItem()->mapper()->setOnPropertyChange(
                 [this](const QString &name)
    {
        qDebug() << "TestWidget::lambda()" << name;
    }, this);

    currentItem()->mapper()->setOnChildPropertyChange(
                 [this](SessionItem* item, const QString &name)
    {
        qDebug() << "TestWidget::lambda() 2" << item->modelType() << name;
    }, this);

}

IntensityDataWidget::IntensityDataWidget(QWidget *parent)
    : SessionItemWidget(parent)
    , m_intensityWidget(new IntensityDataCanvas)
    , m_propertyWidget(new IntensityDataPropertyWidget)
    , m_testWidget(new TestWidget)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->setMargin(0);
    hlayout->setSpacing(0);

    hlayout->addWidget(m_intensityWidget);
    hlayout->addWidget(m_propertyWidget);
    hlayout->addWidget(m_testWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    mainLayout->addLayout(hlayout);
    setLayout(mainLayout);

    connect(m_intensityWidget, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(onContextMenuRequest(const QPoint &)));
}

void IntensityDataWidget::setItem(SessionItem *item)
{
    JobItem *jobItem = dynamic_cast<JobItem *>(item);
    Q_ASSERT(jobItem);
    IntensityDataItem *intensityData = jobItem->intensityDataItem();
    m_intensityWidget->setItem(intensityData);
    m_propertyWidget->setItem(intensityData);
    m_testWidget->setItem(intensityData);
}

QList<QAction *> IntensityDataWidget::actionList()
{
    return m_intensityWidget->actionList() + m_propertyWidget->actionList();
}

void IntensityDataWidget::onContextMenuRequest(const QPoint& point)
{
    QMenu menu;
    for(auto action : actionList())
        menu.addAction(action);
    menu.exec(point);
}
