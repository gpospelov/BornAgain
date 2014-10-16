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
#include <limits>




ModelTuningDelegate::ModelTuningDelegate(QObject *parent)
    : QItemDelegate(parent)
    , m_valueColumn(1)
    , m_sliderRangeFactor(100.0)
    , m_multiplyFactor(100)

{

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

        m_lowerLimit = std::numeric_limits<double>::min();
        m_upperLimit = std::numeric_limits<double>::max();

        ParameterizedItem *item = m_current_link.getItem();
        PropertyAttribute attribute = item->getPropertyAttribute(m_current_link.getPropertyName());
        AttLimits limits = attribute.getLimits();
        //qDebug() << "ModelTuningDelegate::createEditor(): limits: " << limits.hasLowerLimit() << limits.hasUpperLimit() << limits.getLowerLimit() << limits.getUpperLimit();
        if(limits.hasLowerLimit())
        {
            m_lowerLimit = limits.getLowerLimit();
        }
        if(limits.hasUpperLimit())
        {
            m_upperLimit = limits.getUpperLimit();
        }

        m_valueBox = new QDoubleSpinBox();
        m_valueBox->setKeyboardTracking(false);
        m_valueBox->setFixedWidth(80);
        m_valueBox->setMinimum(m_lowerLimit);
        m_valueBox->setMaximum(m_upperLimit);
        m_valueBox->setDecimals(attribute.getDecimals());
        m_valueBox->setSingleStep(1./std::pow(10,attribute.getDecimals()-1));

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

    qDebug() << "ModelTuningDelegate::updateSlider() 1.1 values: " << sliderValue << m_sliderRangeFactor;

    if(sliderValue == 0)
    {
        minValue = m_multiplyFactor*(m_sliderRangeFactor/100) * -1.0;
        maxValue = m_multiplyFactor*(m_sliderRangeFactor/100);
    }
    else
    {
        double factor = std::abs(sliderValue*(m_sliderRangeFactor/100));
        minValue = sliderValue - factor;
        maxValue = sliderValue + factor;

        qDebug() << "ModelTuningDelegate::updateSlider() 1.2 factor: " << minValue << maxValue << factor;
    }

    if(minValue < m_lowerLimit* m_multiplyFactor)
    {
        minValue = m_lowerLimit*m_multiplyFactor;
    }

    if(maxValue > m_upperLimit*m_multiplyFactor)
    {
        maxValue = m_upperLimit*m_multiplyFactor;
    }

    m_slider->setMinimum((int)std::floor(minValue));
    m_slider->setMaximum((int)std::ceil(maxValue));
    m_slider->setValue((int)sliderValue);

    connect(m_slider, SIGNAL(valueChanged(int)),this, SLOT(sliderValueChanged(int)));

}


void ModelTuningDelegate::sliderValueChanged(int position)
{
    disconnect(m_valueBox, SIGNAL(valueChanged(double)),this, SLOT(editorValueChanged(double)));

    double value = (double)position/m_multiplyFactor;
    m_valueBox->setValue(value);

    qDebug() << "ModelTuningDelegate::sliderValueChanged() 1.1 factor: " << position << value;

    connect(m_valueBox, SIGNAL(valueChanged(double)),this, SLOT(editorValueChanged(double)));

    emitSignals(value);
}


void ModelTuningDelegate::editorValueChanged(double value)
{
    disconnect(m_slider, SIGNAL(valueChanged(int)),this, SLOT(sliderValueChanged(int)));
    double sliderValue = value * m_multiplyFactor;

    if(sliderValue!= m_slider->value())
    {
        updateSlider(value);
    }

    connect(m_slider, SIGNAL(valueChanged(int)),this, SLOT(sliderValueChanged(int)));

    emitSignals(value);
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

void ModelTuningDelegate::emitSignals(double value)
{
    if(m_current_link.getItem()) {
        m_current_link.setValue(value);
        //qDebug() << "SampleTuningDelegate::editorValueChanged() -> Working on item " << m_current_link.getItem()->modelType() << m_current_link.getPropertyName();
        //m_current_link.getItem()->setRegisteredProperty(m_current_link.getPropertyName(), m_valueBox->value());
        emit currentLinkChanged(m_current_link);
    }
}

void ModelTuningDelegate::setSliderRangeFactor(double value)
{
    if(m_sliderRangeFactor!=value)
    {
        qDebug() << "ModelTuningDelegate::setSliderRangeFactor" << value;
        m_sliderRangeFactor = value;
    }

}
