// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InfoWidgets/InfoWidget.cpp
//! @brief     Implements class InfoWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "InfoWidget.h"
#include "InfoToolBar.h"
#include "PySampleWidget.h"
#include <QResizeEvent>
#include <QVBoxLayout>

namespace {
const int minimum_widget_height = 25; // height of toolbar
const int minimum_height_before_collapse = 40;
}

InfoWidget::InfoWidget(QWidget *parent)
    : QWidget(parent)
    , m_infoToolBar(new InfoToolBar(this))
    , m_pySampleWidget(new PySampleWidget(this))
    , m_placeHolder(new QWidget(this))
    , m_cached_height(200)
{
    setWindowTitle("Python Script Viewer");
    setObjectName("PythonScriptViewer");

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_infoToolBar);
    mainLayout->addWidget(m_placeHolder);
    mainLayout->addWidget(m_pySampleWidget);

    m_placeHolder->show();
    m_pySampleWidget->hide();

    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    setLayout(mainLayout);

    connect(m_infoToolBar, SIGNAL(expandButtonClicked()), this, SLOT(onExpandButtonClicked()));
    connect(m_infoToolBar, SIGNAL(closeButtonClicked()), this, SIGNAL(widgetCloseRequest()));

}

void InfoWidget::setSampleModel(SampleModel *sampleModel)
{
    Q_ASSERT(m_pySampleWidget);
    m_pySampleWidget->setSampleModel(sampleModel);
}

void InfoWidget::setInstrumentModel(InstrumentModel *instrumentModel)
{
    Q_ASSERT(m_pySampleWidget);
    m_pySampleWidget->setInstrumentModel(instrumentModel);
}

QSize InfoWidget::sizeHint() const
{
    QSize result = m_infoToolBar->sizeHint();
    if(m_pySampleWidget->isHidden()) {
        result.setHeight(m_infoToolBar->height() );
    } else {
        result.setHeight(m_pySampleWidget->height() + m_infoToolBar->height() );
    }
    return result;
}

QSize InfoWidget::minimumSizeHint() const
{
    return QSize(minimum_widget_height, minimum_widget_height);
}

void InfoWidget::onDockVisibilityChange(bool is_visible)
{
    Q_ASSERT(m_pySampleWidget);
    if(isEditorVisible()) {
        if(!is_visible)
            m_pySampleWidget->setEditorConnected(false);
        else
            m_pySampleWidget->setEditorConnected(true);
    }
}

void InfoWidget::onExpandButtonClicked()
{
    setEditorVisible(!isEditorVisible(), true);
}

//! sets the editor to be visible or not.
//! @param dock_notify is used to inform parent QDockWidget about necessary adjustments
//! in its own height
void InfoWidget::setEditorVisible(bool editor_status, bool dock_notify)
{
    m_infoToolBar->setExpandStatus(editor_status);
    if(editor_status) {
        if(m_cached_height) {
            if(dock_notify) emit widgetHeightRequest(m_cached_height);
        }
        m_placeHolder->hide();
        m_pySampleWidget->show();
        m_pySampleWidget->setEditorConnected(true);
    } else {
        m_cached_height = height();
        m_pySampleWidget->hide();
        m_pySampleWidget->setEditorConnected(false);
        m_placeHolder->show();
        if(dock_notify) emit widgetHeightRequest(minimum_widget_height);
    }
}

//! Method watches over the height of the widget (which is triggered from outside, i.e. from
//! DockWindow splitter) and if height becomes too small, disables python editor.
//! Similarly, if widget is growing in height, the editor will be enabled back again
void InfoWidget::resizeEvent(QResizeEvent *event)
{
    // widget is schrinking in height
    if(event->oldSize().height() > event->size().height()) {
        if(event->size().height() <= minimum_height_before_collapse && isEditorVisible()) {
            setEditorVisible(false);
        }
    }

    // widget is growing in height
    if(event->oldSize().height() < event->size().height()) {
        if(event->size().height() > minimum_height_before_collapse && !isEditorVisible()) {
            setEditorVisible(true);
        }
    }

    QWidget::resizeEvent(event);
}

bool InfoWidget::isEditorVisible()
{
    return m_pySampleWidget->isVisible();
}
