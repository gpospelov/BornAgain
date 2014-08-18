#include "ModelTuningDelegate.h"
#include "ItemLink.h"

#include <QDebug>
#include <QPainter>
#include <QPaintDevice>
#include <QApplication>
#include <QWidget>
#include <QMouseEvent>
#include <QStyleOptionSlider>
#include <QAbstractItemModel>
#include <QRect>
#include <QItemSelectionModel>
#include <QHBoxLayout>
#include <QDoubleSpinBox>
#include <cmath>




ModelTuningDelegate::ModelTuningDelegate(int valueColumn, QObject *parent)
    : QItemDelegate(parent)
{
    this->m_valueColumn = valueColumn;
    this->m_multiplyFactor = 100;
}

void ModelTuningDelegate::paint(QPainter *painter,
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


QWidget *ModelTuningDelegate::createEditor(QWidget *parent,
        const QStyleOptionViewItem &option,
        const QModelIndex &index) const
{
    if (index.column() == m_valueColumn) {


        if(index.parent().isValid() == false)
        {
            return NULL;
        }

        double value = index.model()->data(index, Qt::EditRole).toDouble();

        m_current_link = index.model()->data(index, Qt::UserRole).value<ItemLink>();



        m_valueBox = new QDoubleSpinBox();
        m_valueBox->setFixedWidth(80);
        m_valueBox->setMaximum(999999.00);
        m_valueBox->setMinimum(-999999.00);
        m_valueBox->setValue(value);
        connect(m_valueBox, SIGNAL(valueChanged(double)),this, SLOT(editorValueChanged(double)));


        m_slider = new QSlider(Qt::Horizontal);
        m_slider->setFocusPolicy(Qt::StrongFocus);
        m_slider->setTickPosition(QSlider::NoTicks);
        m_slider->setTickInterval(1);
        m_slider->setSingleStep(1);

        updateSlider(value);

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

void ModelTuningDelegate::updateSlider(double value) const
{
    double sliderValue = value * m_multiplyFactor;

    disconnect(m_slider, SIGNAL(valueChanged(int)),this, SLOT(sliderValueChanged(int)));
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

    m_slider->setMinimum((int)std::floor(minValue));
    m_slider->setMaximum((int)std::ceil(maxValue));
    m_slider->setValue((int)sliderValue);

    connect(m_slider, SIGNAL(valueChanged(int)),this, SLOT(sliderValueChanged(int)));

}


void ModelTuningDelegate::sliderValueChanged(int position)
{
    double value = (double)position/m_multiplyFactor;
    m_valueBox->setValue(value);
}

void ModelTuningDelegate::editorValueChanged(double value)
{
    double sliderValue = value * m_multiplyFactor;

    if(sliderValue!= m_slider->value())
    {
        updateSlider(value);
    }

    if(m_current_link.getItem()) {
        m_current_link.setValue(value);
        //qDebug() << "SampleTuningDelegate::editorValueChanged() -> Working on item " << m_current_link.getItem()->modelType() << m_current_link.getPropertyName();
        //m_current_link.getItem()->setRegisteredProperty(m_current_link.getPropertyName(), m_valueBox->value());
        emit currentLinkChanged(m_current_link);
    }
}

void ModelTuningDelegate::setEditorData(QWidget *editor,
                                  const QModelIndex &index) const
{
    if (index.column() == m_valueColumn) {
        //as using custom widget, doing nothing here
    } else {
        QItemDelegate::setEditorData(editor, index);
    }
}


void ModelTuningDelegate::setModelData(QWidget *editor,
                                 QAbstractItemModel *model,
                                 const QModelIndex &index) const
{
    if (index.column() == m_valueColumn) {

        model->setData(index, m_valueBox->value());
        ItemLink link = model->data(index, Qt::UserRole).value<ItemLink>();

        if(link.getItem() != NULL)
        {
            qDebug() << "SampleTuningDelegate::setModelData() -> setting property " << link.getPropertyName();
            link.getItem()->setRegisteredProperty(link.getPropertyName(), m_valueBox->value());
        }

    } else {
        QItemDelegate::setModelData(editor, model, index);
    }
}
