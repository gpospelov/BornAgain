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

JobPropertiesWidget::JobPropertiesWidget(QWidget *parent)
    : QWidget(parent)
    , m_currentItem(0)
    , m_tabWidget(new QTabWidget)
    , m_propertyEditor(new ComponentEditor)
    , m_commentsEditor(new QTextEdit)
    , m_block_update(false)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setWindowTitle(Constants::JobPropertiesWidgetName);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0,0,0,0);

    m_tabWidget->setTabPosition(QTabWidget::South);
    m_tabWidget->insertTab(JOB_PROPERTIES, m_propertyEditor, "Job Properties");
    m_tabWidget->insertTab(JOB_COMMENTS, m_commentsEditor, "Details");

    mainLayout->addWidget(m_tabWidget);
    setLayout(mainLayout);

    connect(m_commentsEditor, SIGNAL(textChanged()), this, SLOT(onTextChanged()));
}

void JobPropertiesWidget::setItem(JobItem *jobItem)
{
    m_propertyEditor->setItem(jobItem);

    if (m_currentItem == jobItem) {
        return;

    } else {
        if(m_currentItem)
            m_currentItem->mapper()->unsubscribe(this);

        m_currentItem = jobItem;
        if (!m_currentItem) return;

        updateItem(m_currentItem);

        m_currentItem->mapper()->setOnPropertyChange(
                    [this](const QString &name)
        {
            if(name == JobItem::P_COMMENTS) {
                updateItem(m_currentItem);
            }
        }, this);
    }
}

void JobPropertiesWidget::onTextChanged()
{
    m_block_update = true;
    Q_ASSERT(m_currentItem);

    m_currentItem->setComments(m_commentsEditor->toPlainText());
    m_block_update = false;
}

void JobPropertiesWidget::updateItem(JobItem *jobItem)
{
    if(m_block_update) return;

    if(jobItem) {
        if(jobItem->getStatus() == Constants::STATUS_FAILED) {
            m_tabWidget->tabBar()->setTabTextColor(JOB_COMMENTS, Qt::red);
        } else {
            m_tabWidget->tabBar()->setTabTextColor(JOB_COMMENTS, Qt::black);
        }
        m_commentsEditor->setText(jobItem->getComments());
    }
}
