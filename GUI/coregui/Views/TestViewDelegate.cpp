#include "TestViewDelegate.h"
#include <QDebug>
#include <QPainter>
#include <QPaintDevice>
#include <QApplication>
#include <QWidget>
#include <QMouseEvent>
#include "hostosinfo.h"
#include <QStyleOptionSlider>
#include <QAbstractItemModel>


TestViewDelegate::TestViewDelegate(QWidget *parent, QItemSelectionModel *selectionModel)
    : QItemDelegate(parent),
      m_slider(new QStyleOptionSlider),
      m_selectionModel(selectionModel)
{

}



void TestViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                  const QModelIndex &index ) const
{

    if(!m_selectionModel)
    {
        return QItemDelegate::paint(painter, option, index);
    }
    else if(!m_selectionModel->isSelected(index))
    {
        return QItemDelegate::paint(painter, option, index);
    }
    else if(!index.parent().isValid())
    {
        return QItemDelegate::paint(painter, option, index);
    }

    double currentValue = 0.0;
    double minValue = 0.0;
    double maxValue = 0.0;
    //qDebug() << " ";
    //qDebug() << "Curent index" << m_selectionModel->currentIndex().data(Qt::DisplayRole);
    QModelIndexList selected_list = m_selectionModel->selectedIndexes();
    if(selected_list.size()) {
        QModelIndex selected = selected_list.back();
        //qDebug() << selected << selected.parent();
        const QAbstractItemModel *model = selected.model();
        //qDebug() << model->data(selected, Qt::DisplayRole) << selected.data(Qt::DisplayRole);
        qDebug() << model->data(selected, Qt::DisplayRole);

        currentValue = model->data(selected, Qt::DisplayRole).toDouble();


        //minValue = currentValue - (currentValue*0.1);
        //maxValue = currentValue + (currentValue*0.1);
        minValue = currentValue - 1;
        maxValue = currentValue + 1;

    }

    if (option.state & QStyle::State_Selected)
    {
        painter->fillRect(option.rect, option.palette.highlight());
    }

    painter->save();

    painter->setRenderHint(QPainter::Antialiasing, true);

    QString text(QString::number(currentValue));
    QRect textRect = getTextRect(option.rect);
    //textRect.setHeight( 10);
    painter->drawText(textRect,text);


    if (option.state & QStyle::State_Selected)
    {
        m_slider->minimum = minValue;
        m_slider->maximum = maxValue;

        m_slider->state = QStyle::State_Enabled;
        m_slider->direction = QApplication::layoutDirection();
        m_slider->rect = getSliderRect(option.rect);
        m_slider->type = QStyleOption::SO_Slider;


        QApplication::style()->drawComplexControl(QStyle::CC_Slider, m_slider, painter);
    }

    m_slider->sliderPosition = (int)currentValue;

    painter->restore();




}

/*void QSlider::paintEvent(QPaintEvent *)
{
    Q_D(QSlider);
    QPainter p(this);
    QStyleOptionSlider opt;
    initStyleOption(&opt);

    opt.subControls = QStyle::SC_SliderGroove | QStyle::SC_SliderHandle;
    if (d->tickPosition != NoTicks)
        opt.subControls |= QStyle::SC_SliderTickmarks;
    if (d->pressedControl) {
        opt.activeSubControls = d->pressedControl;
        opt.state |= QStyle::State_Sunken;
    } else {
        opt.activeSubControls = d->hoverControl;
    }

    style()->drawComplexControl(QStyle::CC_Slider, &opt, &p, this);
}*/

bool TestViewDelegate::editorEvent(QEvent *event,
    QAbstractItemModel *model,
    const QStyleOptionViewItem &option,
    const QModelIndex &index)
{
    //return QItemDelegate::editorEvent(event, model, option, index);

    QMouseEvent *mouseEvent = (QMouseEvent *)event;
    int sliderPosition = this->pixelPosToRangeValue(mouseEvent->pos().x());
    m_slider->sliderPosition = sliderPosition;
    qDebug() << "TestViewDelegate: QStItem clicked: " << sliderPosition;

    //model->setData(index, QVariant(sliderPosition), Qt::EditRole);



    return true;
}

int TestViewDelegate::pixelPosToRangeValue(int pos) const
{
    //Q_Q(const QSlider);
    //QStyleOptionSlider opt;//m_slider
    //q->initStyleOption(&opt);
    QRect gr = QApplication::style()->subControlRect(QStyle::CC_Slider, m_slider, QStyle::SC_SliderGroove);
    QRect sr = QApplication::style()->subControlRect(QStyle::CC_Slider, m_slider, QStyle::SC_SliderHandle);
    int sliderMin, sliderMax, sliderLength;

    /*if (orientation == Qt::Horizontal) {
        sliderLength = sr.width();
        sliderMin = gr.x();
        sliderMax = gr.right() - sliderLength + 1;
    } else {
        sliderLength = sr.height();
        sliderMin = gr.y();
        sliderMax = gr.bottom() - sliderLength + 1;
    }*/

    sliderLength = sr.width();
    sliderMin = gr.x();
    sliderMax = gr.right() - sliderLength + 1;
    return QStyle::sliderValueFromPosition(m_slider->minimum, m_slider->maximum, pos - sliderMin,
                                           sliderMax - sliderMin, m_slider->upsideDown);
}



//! returns rectangle for text
QRect TestViewDelegate::getTextRect(QRect optionRect) const
{
    int width = optionRect.width()*0.4;
    int height = optionRect.height();
    int x = optionRect.x() + 3;
    int y = optionRect.y();
    QRect result(x,y,width,height);
    return result;
}


//! returns rectangle for progress bar
QRect TestViewDelegate::getSliderRect(QRect optionRect) const
{
    int width = optionRect.width()*0.4;
    int height = optionRect.height()*0.6;
    int x = optionRect.x() + optionRect.width()*0.5;
    int y = optionRect.y() + (optionRect.height() - height)/2.;
    if( Utils::HostOsInfo::isMacHost() ) {
        y = optionRect.y();
        height = optionRect.height()*0.5;
    }

    QRect result(x,y,width,height);
    return result;
}





