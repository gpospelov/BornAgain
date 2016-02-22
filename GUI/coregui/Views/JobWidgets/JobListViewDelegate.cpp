// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/JobWidgets/JobListViewDelegate.cpp
//! @brief     Implements class JobListViewDelegate
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "JobListViewDelegate.h"
#include "JobModel.h"
#include "JobItem.h"
#include "progressbar.h"
#include <QDebug>
#include <QPainter>
#include <QPaintDevice>
#include <QApplication>
#include <QWidget>
#include <QMouseEvent>
#include <QStyleOptionProgressBarV2>
#include "hostosinfo.h"

JobListViewDelegate::JobListViewDelegate(QWidget *parent)
    : QItemDelegate(parent)
{
    m_buttonState =  QStyle::State_Enabled;
    m_status_to_color[Constants::STATUS_IDLE] = QColor(255, 286, 12);
    m_status_to_color[Constants::STATUS_RUNNING] = QColor(5, 150, 230);
    m_status_to_color[Constants::STATUS_COMPLETED] = QColor(5, 150, 230);
    m_status_to_color[Constants::STATUS_CANCELED] = QColor(186, 0, 0);
    m_status_to_color[Constants::STATUS_FAILED] = QColor(255, 186, 12);
}

void JobListViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                  const QModelIndex &index ) const
{
    if (option.state & QStyle::State_Selected)
        painter->fillRect(option.rect, option.palette.highlight());

    const JobModel* model = static_cast<const JobModel*>(index.model());
    Q_ASSERT(model);

    const JobItem *item = model->getJobItemForIndex(index);
    Q_ASSERT(item);

    painter->save();

    painter->setRenderHint(QPainter::Antialiasing, true);

    QString text = item->itemName();
    QRect textRect = getTextRect(option.rect);
    painter->drawText(textRect,text);

    drawCustomProjectBar(item, painter, option);

    if(item->isRunning()) {
        QStyleOptionButton button;
        button.rect = getButtonRect(option.rect);
        button.state = m_buttonState | QStyle::State_Enabled;
        button.icon = QIcon(":/images/darkclosebutton.png");
        button.iconSize = QSize(12,12);

        QApplication::style()->drawControl (QStyle::CE_PushButton, &button, painter);
    }

    painter->restore();
}

bool JobListViewDelegate::editorEvent(QEvent *event,
    QAbstractItemModel *model,
    const QStyleOptionViewItem &option,
    const QModelIndex &index)
{
    if( event->type() == QEvent::MouseButtonPress ||
        event->type() == QEvent::MouseButtonRelease ) {
    } else {
        m_buttonState = QStyle::State_Raised;
        return QItemDelegate::editorEvent(event, model, option, index);
        return true;
    }

    const JobModel* jqmodel = static_cast<const JobModel*>(index.model());
    Q_ASSERT(model);

    const JobItem *item = jqmodel->getJobItemForIndex(index);
    Q_ASSERT(item);

    if(!item->isRunning()) return false;

    QRect buttonRect = getButtonRect(option.rect);

    QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
    if( !buttonRect.contains( mouseEvent->pos()) ) {
        m_buttonState = QStyle::State_Raised;
        return false; // so that selection can change
    }

    if( event->type() == QEvent::MouseButtonPress) {
        m_buttonState = QStyle::State_Sunken;
    } else if( event->type() == QEvent::MouseButtonRelease) {
        m_buttonState = QStyle::State_Raised;
        qDebug("JobListViewDelegate::editorEvent() -> cancel clicked");
        emit cancelButtonClicked( index);
    }
    return true;
}

void JobListViewDelegate::drawCustomProjectBar(const JobItem *item, QPainter *painter, const QStyleOptionViewItem &option) const
{
    int progress = item->getProgress();
    QRect rect = getProgressBarRect(option.rect);

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(QColor(204, 223, 230));
    painter->setPen(QColor("transparent"));
    QRect rect2(rect.x(), rect.y(), rect.width(),
                rect.height());
    painter->drawRoundedRect(rect2, 2, 2);
    painter->restore();

    int progBarWidth = float((rect.width() * progress) / 100);
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QColor("transparent"));
    painter->setBrush(m_status_to_color[item->getStatus()]);
    QRect rect5(rect.x(), rect.y(), progBarWidth,
                    rect.height());
    painter->drawRoundedRect(rect5, 2, 2);
    painter->restore();
}

//! returns rectangle for text
QRect JobListViewDelegate::getTextRect(QRect optionRect) const
{
    int width = optionRect.width()*0.4;
    int height = optionRect.height();
    int x = optionRect.x() + 3;
    int y = optionRect.y();
    QRect result(x,y,width,height);
    return result;
}

//! returns rectangle for progress bar
QRect JobListViewDelegate::getProgressBarRect(QRect optionRect) const
{
    int width = optionRect.width()*0.4;
    int height = optionRect.height()*0.6;
    int x = optionRect.x() + optionRect.width()*0.5;
    int y = optionRect.y() + (optionRect.height() - height)/2.;
    QRect result(x,y,width,height);
    return result;
}

//! returns rectangle for button
QRect JobListViewDelegate::getButtonRect(QRect optionRect) const
{
    int height = 10;
    int width = 10;
    int x = optionRect.x() + optionRect.width()*0.92;
    int y = optionRect.y() + (optionRect.height() - height)/2.;
    QRect result(x,y,width,height);
    return result;
}




