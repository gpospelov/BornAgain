#include "SampleTuningDelegate.h"
#include <QDebug>
#include <QPainter>
#include <QPaintDevice>
#include <QApplication>
#include <QWidget>
#include <QMouseEvent>
#include <QStyleOptionSlider>
#include <QAbstractItemModel>
#include <cmath>
#include "ItemLink.h"



SampleTuningDelegate::SampleTuningDelegate(int valueColumn, QObject *parent)
    : QItemDelegate(parent)
{
    this->m_valueColumn = valueColumn;
    this->m_multiplyFactor = 100;
}

void SampleTuningDelegate::paint(QPainter *painter,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const
{

    if (index.column() == m_valueColumn) {

        if(index.parent().isValid() == false)
        {
            return;
        }

        QVariant prop_value = index.model()->data(index, Qt::EditRole);


//        QVariant param_value = index.model()->data(index, Qt::UserRole);
//        ItemLink itemLink = param_value.value<ItemLink>();
//        qDebug() << "Item Link: " << itemLink.getName();

        int type = prop_value.type();
        if (type == QVariant::Double) {
            double value = prop_value.toDouble();
            QString text(QString::number(value));

            QStyleOptionViewItem myOption = option;
            myOption.displayAlignment = Qt::AlignLeft | Qt::AlignVCenter;


            drawDisplay(painter, myOption, myOption.rect, text);
            drawFocus(painter, myOption, myOption.rect);
        }
        else
        {
            return;
        }


    } else{
        QItemDelegate::paint(painter, option, index);
    }
}


QWidget *SampleTuningDelegate::createEditor(QWidget *parent,
        const QStyleOptionViewItem &option,
        const QModelIndex &index) const
{
    if (index.column() == m_valueColumn) {


        if(index.parent().isValid() == false)
        {
            return NULL;
        }

        double value = index.model()->data(index, Qt::EditRole).toDouble();
        double sliderValue = value * m_multiplyFactor;

        double minValue = 0;
        double maxValue = 0;
        if(sliderValue == 0)
        {
            minValue = (m_multiplyFactor/10.0) * -1.0;
            maxValue = (m_multiplyFactor/10.0);
        }
        else
        {
            minValue = sliderValue - std::abs(sliderValue*0.1);
            maxValue = sliderValue + std::abs(sliderValue*0.1);
        }

        m_valueBox = new QDoubleSpinBox();
        m_valueBox->setFixedWidth(80);
        m_valueBox->setMaximum(99999.00);
        m_valueBox->setMinimum(-99999.00);
        m_valueBox->setValue(value);



        m_slider = new QSlider(Qt::Horizontal);
        m_slider->setFocusPolicy(Qt::StrongFocus);
        m_slider->setTickPosition(QSlider::NoTicks);
        m_slider->setTickInterval(1);
        m_slider->setSingleStep(1);
        m_slider->setMinimum((int)std::floor(minValue));
        m_slider->setMaximum((int)std::ceil(maxValue));
        m_slider->setValue((int)sliderValue);

        connect(m_valueBox, SIGNAL(valueChanged(double)),this, SLOT(editorValueChanged(double)));
        connect(m_slider, SIGNAL(valueChanged(int)),this, SLOT(sliderValueChanged(int)));

        m_contentWidget = new QWidget(parent);
        m_contentLayout = new QHBoxLayout(parent);
        m_contentLayout->setMargin(0);
        m_contentLayout->setSpacing(0);
        m_contentLayout->addWidget(m_valueBox);
        m_contentLayout->addWidget(m_slider);

        m_contentWidget->setLayout(m_contentLayout);

        return m_contentWidget;
    } else {
        return QItemDelegate::createEditor(parent, option, index);
    }
}


void SampleTuningDelegate::sliderValueChanged(int position)
{
    double value = (double)position/m_multiplyFactor;
    m_valueBox->setValue(value);
}

void SampleTuningDelegate::editorValueChanged(double value)
{
    qDebug() << "XXXX: new value: " << value;
}

void SampleTuningDelegate::setEditorData(QWidget *editor,
                                  const QModelIndex &index) const
{
    if (index.column() == m_valueColumn) {
        //as using custom widget, doing nothing here
    } else {
        QItemDelegate::setEditorData(editor, index);
    }
}


void SampleTuningDelegate::setModelData(QWidget *editor,
                                 QAbstractItemModel *model,
                                 const QModelIndex &index) const
{
    if (index.column() == m_valueColumn) {

        model->setData(index, m_valueBox->value());
        ItemLink link = model->data(index, Qt::UserRole).value<ItemLink>();

        if(link.getItem() != NULL)
        {
            link.getItem()->setRegisteredProperty(link.getName(), m_valueBox->value());
        }

    } else {
        QItemDelegate::setModelData(editor, model, index);
    }
}
