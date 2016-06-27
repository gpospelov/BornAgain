// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/IntensityDataPropertyWidget.cpp
//! @brief     Implements class IntensityDataPropertyWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "IntensityDataPropertyWidget.h"
#include "JobModel.h"
#include "IntensityDataItem.h"
#include "ComponentEditor.h"
#include <QVBoxLayout>
#include <QAction>
#include <QDebug>

IntensityDataPropertyWidget::IntensityDataPropertyWidget(QWidget *parent)
    : SessionItemWidget(parent)
    , m_togglePanelAction(0)
    , m_currentItem(0)
    , m_componentEditor(0)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    setWindowTitle(QLatin1String("Intensity Data Properties"));
    setObjectName(QLatin1String("Intensity Data Properties"));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    m_componentEditor = new ComponentEditor();

    mainLayout->addWidget(m_componentEditor);

    setLayout(mainLayout);

    m_togglePanelAction = new QAction(this);
    m_togglePanelAction->setText("Properties");
    m_togglePanelAction->setIcon(QIcon(":/images/toolbar16light_propertypanel.svg"));
    m_togglePanelAction->setToolTip("Toggle Property Panel");
    connect(m_togglePanelAction, SIGNAL(triggered()), this, SLOT(onTogglePanelAction()));

}

IntensityDataPropertyWidget::~IntensityDataPropertyWidget()
{
    if(m_currentItem)
        m_currentItem->mapper()->unsubscribe(this);
}

void IntensityDataPropertyWidget::setItem(SessionItem *item)
{
    if(m_currentItem == item)
        return;

    if(m_currentItem)
        m_currentItem->mapper()->unsubscribe(this);

    m_currentItem = item;
   if (!m_currentItem) return;

    m_componentEditor->setItem(item);

    setPanelVisible(m_currentItem->getItemValue(IntensityDataItem::P_PROPERTY_PANEL_FLAG).toBool());

    m_currentItem->mapper()->setOnPropertyChange(
                 [this](const QString &name)
    {
        if(name == IntensityDataItem::P_PROPERTY_PANEL_FLAG) {
            setPanelVisible(m_currentItem->getItemValue(IntensityDataItem::P_PROPERTY_PANEL_FLAG).toBool());
        }
    }, this);

    m_currentItem->mapper()->setOnItemDestroy(
                [this](SessionItem *) {
        m_currentItem = 0;
    }, this);


}

QList<QAction *> IntensityDataPropertyWidget::actionList()
{
    return QList<QAction *>() << m_togglePanelAction;
}

void IntensityDataPropertyWidget::onTogglePanelAction()
{
    if(m_currentItem) {
        bool current_flag = m_currentItem->getItemValue(IntensityDataItem::P_PROPERTY_PANEL_FLAG).toBool();
        m_currentItem->setItemValue(IntensityDataItem::P_PROPERTY_PANEL_FLAG, !current_flag);
    }

}

void IntensityDataPropertyWidget::setPanelVisible(bool visible)
{
    if(visible) {
        m_componentEditor->setItem(m_currentItem);

    } else {
        m_componentEditor->setItem(0);
    }
    setVisible(visible);
}
