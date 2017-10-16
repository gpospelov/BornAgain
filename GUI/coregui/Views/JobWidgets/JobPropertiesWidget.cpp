// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobPropertiesWidget.cpp
//! @brief     Implements class JobPropertiesWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "JobPropertiesWidget.h"
#include "ComponentEditor.h"
#include "JobItem.h"
#include "mainwindow_constants.h"
#include <QTabBar>
#include <QTabWidget>
#include <QTextEdit>
#include <QVBoxLayout>

JobPropertiesWidget::JobPropertiesWidget(QWidget* parent)
    : SessionItemWidget(parent)
    , m_tabWidget(new QTabWidget)
    , m_propertyEditor(new ComponentEditor)
    , m_commentsEditor(new QTextEdit)
    , m_block_update(false)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setWindowTitle(Constants::JobPropertiesWidgetName);

    auto mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    m_tabWidget->setTabPosition(QTabWidget::South);
    m_tabWidget->insertTab(JOB_PROPERTIES, m_propertyEditor, "Job Properties");
    m_tabWidget->insertTab(JOB_COMMENTS, m_commentsEditor, "Details");

    mainLayout->addWidget(m_tabWidget);
    setLayout(mainLayout);

    connect(m_commentsEditor, &QTextEdit::textChanged, this, &JobPropertiesWidget::onTextChanged);
}

void JobPropertiesWidget::subscribeToItem()
{
    currentItem()->mapper()->setOnPropertyChange(
        [this](const QString& name) {
            if (name == JobItem::P_COMMENTS)
                updateItem();
        }, this);

    m_propertyEditor->setItem(currentItem());

    updateItem();
}

void JobPropertiesWidget::unsubscribeFromItem()
{
    m_propertyEditor->setItem(nullptr);
}

void JobPropertiesWidget::onTextChanged()
{
    m_block_update = true;
    jobItem()->setComments(m_commentsEditor->toPlainText());
    m_block_update = false;
}

void JobPropertiesWidget::updateItem()
{
    if (m_block_update)
        return;

    if (JobItem* item = jobItem()) {
        if (item->getStatus() == Constants::STATUS_FAILED)
            m_tabWidget->tabBar()->setTabTextColor(JOB_COMMENTS, Qt::red);
        else
            m_tabWidget->tabBar()->setTabTextColor(JOB_COMMENTS, Qt::black);

        m_commentsEditor->setText(item->getComments());
    }
}

JobItem* JobPropertiesWidget::jobItem()
{
    return dynamic_cast<JobItem*>(currentItem());
}
