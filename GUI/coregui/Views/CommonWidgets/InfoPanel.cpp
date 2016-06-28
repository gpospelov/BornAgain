// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/InfoPanel.h
//! @brief     Declares class InfoPanel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "InfoPanel.h"
#include "InfoPanelToolBar.h"
#include <QStackedWidget>
#include <QBoxLayout>
#include <QDebug>

namespace {
const int minimum_widget_height = 25; // height of toolbar
const int minimum_height_before_collapse = 40;
}

InfoPanel::InfoPanel(QWidget *parent)
    : QFrame(parent)
    , m_toolBar(new InfoPanelToolBar)
    , m_stackedWidget(new QStackedWidget)
    , m_cached_height(200)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_toolBar);
    mainLayout->addWidget(m_stackedWidget);

    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    setLayout(mainLayout);

    connect(m_toolBar, SIGNAL(expandButtonClicked()), this, SLOT(onExpandButtonClicked()));
    connect(m_toolBar, SIGNAL(closeButtonClicked()), this, SLOT(onCloseButtonClicked()));
}

QSize InfoPanel::sizeHint() const
{
    QSize result = m_toolBar->sizeHint();

    if(QWidget *widget = m_stackedWidget->currentWidget()) {
        result.setHeight(widget->height() + m_toolBar->height() );
    } else {
        result.setHeight(m_toolBar->height() );
    }
    qDebug() << "InfoPanel::sizeHint()" << result;
    return result;
}

QSize InfoPanel::minimumSizeHint() const
{
    return QSize(minimum_widget_height, minimum_widget_height);
}

void InfoPanel::onExpandButtonClicked()
{
    qDebug() << "InfoPanel::onExpandButtonClicked()  isContentVisible()?" << isContentVisible();
    setContentVisible(!isContentVisible(), true);
}

void InfoPanel::onCloseButtonClicked()
{
    qDebug() << "InfoPanel::onCloseButtonClicked()";
}

void InfoPanel::setContentVisible(bool editor_status, bool dock_notify)
{
    qDebug() << "InfoPanel::setContentVisible" << editor_status << dock_notify;

    m_toolBar->setExpandStatus(editor_status);
    if(editor_status) {
        if(m_cached_height)
            if(dock_notify) emit widgetHeightRequest(m_cached_height);

        if(m_stackedWidget->currentWidget())
            m_stackedWidget->currentWidget()->show();

    } else {
        m_cached_height = height();
        if(m_stackedWidget->currentWidget())
            m_stackedWidget->currentWidget()->hide();

        if(dock_notify) emit widgetHeightRequest(minimum_widget_height);
    }

}

bool InfoPanel::isContentVisible()
{
    qDebug() << "InfoPanel::isContentVisible() m_stackedWidget->currentWidget()" << m_stackedWidget->currentWidget();
    if(m_stackedWidget->currentWidget()) {
        qDebug() << "m_stackedWidget->currentWidget()->isVisible()" << m_stackedWidget->currentWidget()->isVisible();
        return m_stackedWidget->currentWidget()->isVisible();
    }

    return false;
}

