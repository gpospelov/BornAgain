// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InfoWidgets/InfoWidget.cpp
//! @brief     Implements class InfoWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "InfoWidget.h"
#include "PySampleWidget.h"
#include "InfoToolBar.h"
#include <QResizeEvent>
#include <QVBoxLayout>
#include <QDebug>

namespace {
const int minimum_widget_height = 25; // height of toolbar
const int minimum_height_before_collapse = 40;
}

InfoWidget::InfoWidget(QWidget *parent)
    : QWidget(parent)
    , m_infoToolBar(new InfoToolBar(this))
    , m_pySampleWidget(new PySampleWidget(this))
    , m_placeHolder(new QWidget(this))
    , m_cached_height(0)
{
    setWindowTitle(tr("Info Stream"));
    setObjectName(tr("InfoStream"));
    //setMinimumSize(128, 128);
//    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

//    m_placeHolder->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_infoToolBar);
    mainLayout->addWidget(m_placeHolder);
    mainLayout->addWidget(m_pySampleWidget);

    m_placeHolder->show();
    m_pySampleWidget->hide();

    //mainLayout->addStretch();
    //mainLayout->setSizeConstraint();
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    setLayout(mainLayout);

    connect(m_infoToolBar, SIGNAL(expandButtonClicked()), this, SLOT(onExpandButtonClicked()));
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
    qDebug() << "InfoWidget::sizeHint()" << result;
    return result;
}

QSize InfoWidget::minimumSizeHint() const
{
    return QSize(minimum_widget_height, minimum_widget_height);
}

void InfoWidget::onExpandButtonClicked()
{
    qDebug() << "InfoWidget::onExpandButtonClicked()" << m_cached_height;
    setEditorVisible(!isEditorVisible(), true);

//    if(m_pySampleWidget->isHidden()) {
//        if(m_cached_height) {
//            QSize new_size = size();
//            new_size.setHeight(m_cached_height);
//            qDebug() << "xxx 1.1";
//            //resize(new_size);
//            emit widgetHeightRequest(new_size.height());
//        }
//        m_placeHolder->hide();
//        m_pySampleWidget->show();
//    } else {
//        m_cached_height = height();
//        m_pySampleWidget->hide();
//        m_placeHolder->show();
//        qDebug() << "xxx 1.2 ask for" << m_infoToolBar->size();
//        //resize(m_infoToolBar->size());
//        emit widgetHeightRequest(m_infoToolBar->height());
//    }
////    layout()->invalidate();
//    layout()->update();
//    layout()->activate();
//    update();
}

void InfoWidget::setEditorVisible(bool editor_status, bool dock_notify)
{
    m_infoToolBar->setExpandStatus(editor_status);
    if(editor_status) {
        if(m_cached_height) {
            if(dock_notify) emit widgetHeightRequest(m_cached_height);
        }
        m_placeHolder->hide();
        m_pySampleWidget->show();
    } else {
        m_cached_height = height();
        m_pySampleWidget->hide();
        m_placeHolder->show();
        if(dock_notify) emit widgetHeightRequest(minimum_widget_height);
    }
}

void InfoWidget::resizeEvent(QResizeEvent *event)
{
    qDebug() << "InfoWidget::resizeEvent -> current_size"
             << size() << "hint:" << sizeHint() << "event->size" << event->size() << "event->oldsize:" << event->oldSize();

    // widget is schrinking in height
    if(event->oldSize().height() > event->size().height()) {
        if(event->size().height() <= minimum_height_before_collapse && isEditorVisible()) {
            setEditorVisible(false);
        }
    }

    // widget is growing
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
