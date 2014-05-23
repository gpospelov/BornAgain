#include "DetectorEditorWidget.h"
#include "GroupProperty.h"
#include "ComboProperty.h"
#include "DetectorItems.h"
#include <QBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QDebug>

DetectorEditorWidget::DetectorEditorWidget(QWidget *parent)
    : QWidget(parent)
    , m_currentItem(0)
    , m_block_signals(false)
{




    QGroupBox *detectorGroup = new QGroupBox("Detector Parameters");

    m_detectorTypeCombo = new QComboBox();
    m_unitsCombo = new QComboBox();
    m_binningTypeCombo = new QComboBox();

    m_axis0Label = new QLabel("x-axis");
    m_axis1Label = new QLabel("x-axis");

    QGridLayout *detectorLayout = new QGridLayout;
    detectorLayout->addWidget(new QLabel("Detector Type"), 0, 0);
    detectorLayout->addWidget(m_detectorTypeCombo, 0, 1, 1, 1);
    detectorLayout->addWidget(new QLabel("Units"), 1, 0);
    detectorLayout->addWidget(m_unitsCombo, 1, 1);
    detectorLayout->addWidget(new QLabel("Binning"), 2, 0);
    detectorLayout->addWidget(m_binningTypeCombo, 2, 1);
    detectorLayout->addWidget(m_binningTypeCombo, 2, 1);

    detectorLayout->addWidget(new QLabel("min"), 3, 1);
    detectorLayout->addWidget(new QLabel("max"), 3, 2);
    detectorLayout->addWidget(new QLabel("nbins"), 3, 3);

    detectorLayout->addWidget(m_axis0Label, 5, 0);
    detectorLayout->addWidget(new QDoubleSpinBox(), 5, 1);
    detectorLayout->addWidget(new QDoubleSpinBox(), 5, 2);
    detectorLayout->addWidget(new QSpinBox(), 5, 3);

    detectorLayout->addWidget(m_axis1Label, 6, 0);
    detectorLayout->addWidget(new QDoubleSpinBox(), 6, 1);
    detectorLayout->addWidget(new QDoubleSpinBox(), 6, 2);
    detectorLayout->addWidget(new QSpinBox(), 6, 3);


    detectorLayout->setColumnStretch(0,1);
    detectorLayout->setColumnStretch(1,3);
    detectorLayout->setColumnStretch(2,3);
    detectorLayout->setColumnStretch(3,1);
    detectorLayout->setColumnStretch(4,3);


    //detectorLayout->columnStretch(0);

    detectorGroup->setLayout(detectorLayout);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(detectorGroup);

    setLayout(mainLayout);


    connect(m_detectorTypeCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(onDetectorTypeChanged(int)));

}

void DetectorEditorWidget::initFromItem(ParameterizedItem *item)
{
    qDebug() << "DetectorEditorWidget::initFromItem()";

    if(item != m_currentItem) {
        m_currentItem = item;

        connect(item, SIGNAL(propertyChanged(QString)), this, SLOT(onPropertyChanged(QString)));
        connect(item, SIGNAL(propertyItemChanged(QString)), this, SLOT(onPropertyChanged(QString)));

        updateWidgets();
    }
}


void DetectorEditorWidget::updateWidgets()
{
    qDebug() << "DetectorEditorWidget::updateWidgets() ->";

    m_block_signals = true;
    m_detectorTypeCombo->clear();
    GroupProperty detector_property = m_currentItem->getRegisteredProperty(DetectorItem::P_DETECTOR_TYPE).value<GroupProperty>();
    m_detectorTypeCombo->addItems(detector_property.getValues());
    m_detectorTypeCombo->setCurrentText(detector_property.getValue());

    ParameterizedItem *detectorTypeItem = m_currentItem->getSubItems()[DetectorItem::P_DETECTOR_TYPE];
    Q_ASSERT(detectorTypeItem);
    m_unitsCombo->clear();
    ComboProperty units_property = detectorTypeItem->getRegisteredProperty(DetectorItem::P_AXES_UNITS).value<ComboProperty>();
    m_unitsCombo->addItems(units_property.getValues());
    m_unitsCombo->setCurrentText(units_property.getValue());

    m_block_signals = false;
}


void DetectorEditorWidget::onPropertyChanged(const QString &name)
{
    qDebug() << "DetectorEditorWidget::onPropertyChanged() -> " << name;

//    qDebug() << "xxx 1.1";
//    m_detectorTypeCombo->clear();
//    GroupProperty detector_property = m_currentItem->getRegisteredProperty(DetectorItem::P_DETECTOR_TYPE).value<GroupProperty>();
//    qDebug() << "xxx 1.2";
//    m_detectorTypeCombo->addItems(detector_property.getValues());
//    qDebug() << "xxx 1.3";
//    m_detectorTypeCombo->setCurrentText(detector_property.getValue());
//    qDebug() << "xxx 1.4";

//    ParameterizedItem *detectorTypeItem = m_currentItem->getSubItems()[DetectorItem::P_DETECTOR_TYPE];
//    Q_ASSERT(detectorTypeItem);
//    m_unitsCombo->clear();
//    ComboProperty units_property = detectorTypeItem->getRegisteredProperty(DetectorItem::P_AXES_UNITS).value<ComboProperty>();
//    m_unitsCombo->addItems(units_property.getValues());
//    m_unitsCombo->setCurrentText(units_property.getValue());
    updateWidgets();
}

void DetectorEditorWidget::onDetectorTypeChanged(int)
{
    qDebug() << "DetectorEditorWidget::onDetectorTypeChanged() -> ";
    Q_ASSERT(m_currentItem);
    if(m_block_signals) return;

    m_currentItem->setGroupProperty(DetectorItem::P_DETECTOR_TYPE, m_detectorTypeCombo->currentText());

}
