#include "DetectorEditorWidget.h"
#include "GroupProperty.h"
#include "ComboProperty.h"
#include "DetectorItems.h"
#include "GUIHelpers.h"
#include "Units.h"
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
    , m_detectorTypeCombo(new QComboBox)
    , m_unitsCombo(new QComboBox)
    , m_binningTypeCombo(new QComboBox)
    , m_axis0Label(0)
    , m_axis1Label(0)
    , m_phiMinEdit(new QDoubleSpinBox)
    , m_phiMaxEdit(new QDoubleSpinBox)
    , m_nphiEdit(new QSpinBox)
    , m_alphaMinEdit(new QDoubleSpinBox)
    , m_alphaMaxEdit(new QDoubleSpinBox)
    , m_nalphaEdit(new QSpinBox)
    , m_currentItem(0)
    , m_block_signals(false)

{

    QGroupBox *detectorGroup = new QGroupBox("Detector Parameters");

    m_axis0Label = new QLabel("Phi");
    m_axis1Label = new QLabel("Alpha");

    m_nphiEdit->setMinimum(1);
    m_nphiEdit->setMaximum(1024);
    m_nalphaEdit->setMinimum(1);
    m_nalphaEdit->setMaximum(1024);

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
    detectorLayout->addWidget(m_phiMinEdit, 5, 1);
    detectorLayout->addWidget(m_phiMaxEdit, 5, 2);
    detectorLayout->addWidget(m_nphiEdit, 5, 3);

    detectorLayout->addWidget(m_axis1Label, 6, 0);
    detectorLayout->addWidget(m_alphaMinEdit, 6, 1);
    detectorLayout->addWidget(m_alphaMaxEdit, 6, 2);
    detectorLayout->addWidget(m_nalphaEdit, 6, 3);


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
    connect(m_phiMinEdit, SIGNAL(valueChanged(QString)), this, SLOT(onAngleEditorChanged(QString)));
    connect(m_phiMaxEdit, SIGNAL(valueChanged(QString)), this, SLOT(onAngleEditorChanged(QString)));
    connect(m_nphiEdit, SIGNAL(valueChanged(QString)), this, SLOT(onAngleEditorChanged(QString)));
    connect(m_alphaMinEdit, SIGNAL(valueChanged(QString)), this, SLOT(onAngleEditorChanged(QString)));
    connect(m_alphaMaxEdit, SIGNAL(valueChanged(QString)), this, SLOT(onAngleEditorChanged(QString)));
    connect(m_nalphaEdit, SIGNAL(valueChanged(QString)), this, SLOT(onAngleEditorChanged(QString)));
}

void DetectorEditorWidget::initFromItem(ParameterizedItem *item)
{
    qDebug() << "DetectorEditorWidget::initFromItem()" << item->modelType();

    if(item != m_currentItem) {
        if(m_currentItem) {
            disconnect(item, SIGNAL(propertyChanged(const QString &)), this, SLOT(onPropertyChanged(const QString  &)));
            disconnect(item, SIGNAL(propertyItemChanged(const QString &)), this, SLOT(onPropertyChanged(const QString &)));
        }

        m_currentItem = item;

        connect(item, SIGNAL(propertyChanged(const QString &)), this, SLOT(onPropertyChanged(const QString &)));
        connect(item, SIGNAL(propertyItemChanged(const QString &)), this, SLOT(onPropertyChanged(const QString &)));

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

    m_binningTypeCombo->clear();
    ComboProperty binning_property = detectorTypeItem->getRegisteredProperty(DetectorItem::P_BINNING).value<ComboProperty>();
    m_binningTypeCombo->addItems(binning_property.getValues());
    m_binningTypeCombo->setCurrentText(binning_property.getValue());

    ParameterizedItem *subDetector = m_currentItem->getSubItems()[DetectorItem::P_DETECTOR_TYPE];
    Q_ASSERT(subDetector);

    if (subDetector->modelType() == ThetaPhiDetectorItem::P_MODEL_TYPE) {
        int nphi = subDetector->getRegisteredProperty(ThetaPhiDetectorItem::P_NPHI).toInt();
        double phi_min = subDetector->getRegisteredProperty(ThetaPhiDetectorItem::P_PHI_MIN).toDouble();
        double phi_max = subDetector->getRegisteredProperty(ThetaPhiDetectorItem::P_PHI_MAX).toDouble();
        int nalpha = subDetector->getRegisteredProperty(ThetaPhiDetectorItem::P_NALPHA).toInt();
        double alpha_min = subDetector->getRegisteredProperty(ThetaPhiDetectorItem::P_ALPHA_MIN).toDouble();
        double alpha_max = subDetector->getRegisteredProperty(ThetaPhiDetectorItem::P_ALPHA_MAX).toDouble();

        ComboProperty units_property = subDetector->getRegisteredProperty(DetectorItem::P_AXES_UNITS).value<ComboProperty>();
        updateAngleUnits(units_property.getValue());

        m_phiMinEdit->setValue(phi_min);
        m_phiMaxEdit->setValue(phi_max);
        m_nphiEdit->setValue(nphi);
        m_alphaMinEdit->setValue(alpha_min);
        m_alphaMaxEdit->setValue(alpha_max);
        m_nalphaEdit->setValue(nalpha);
    } else {
        throw GUIHelpers::Error("DetectorEditorWidget::updateWidgets() -> Unknown detector item");
    }

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

void DetectorEditorWidget::onAngleEditorChanged(const QString &)
{
    qDebug() << "DetectorEditorWidget::onAngleEditorChanged() ->";
    if(m_block_signals) return;
    qDebug() << "DetectorEditorWidget::onAngleEditorChanged()";
    ParameterizedItem *subDetector = m_currentItem->getSubItems()[DetectorItem::P_DETECTOR_TYPE];
    Q_ASSERT(subDetector);
    Q_ASSERT(subDetector->modelType() == ThetaPhiDetectorItem::P_MODEL_TYPE);
    subDetector->setRegisteredProperty(ThetaPhiDetectorItem::P_PHI_MIN, m_phiMinEdit->value());
    subDetector->setRegisteredProperty(ThetaPhiDetectorItem::P_PHI_MAX, m_phiMaxEdit->value());
    subDetector->setRegisteredProperty(ThetaPhiDetectorItem::P_NPHI, m_nphiEdit->value());

    subDetector->setRegisteredProperty(ThetaPhiDetectorItem::P_ALPHA_MIN, m_alphaMinEdit->value());
    subDetector->setRegisteredProperty(ThetaPhiDetectorItem::P_ALPHA_MAX, m_alphaMaxEdit->value());
    subDetector->setRegisteredProperty(ThetaPhiDetectorItem::P_NALPHA, m_nalphaEdit->value());
}


//! Update angle limits for all angle editors depending on units: radians or degrees
void DetectorEditorWidget::updateAngleUnits(const QString &units)
{
    setAngleUnits(m_phiMinEdit, units);
    setAngleUnits(m_phiMaxEdit, units);
    setAngleUnits(m_alphaMinEdit, units);
    setAngleUnits(m_alphaMaxEdit, units);
}


//! Sets angle units and corresponding limits for QDoubleSpinBox
void DetectorEditorWidget::setAngleUnits(QDoubleSpinBox *editor, const QString &units)
{
    if(units == QStringLiteral("Degrees")) {
        editor->setSingleStep(0.01);
        editor->setMinimum(-90.0);
        editor->setMaximum(90.0);
        editor->setDecimals(3);
    }
    else if(units == QStringLiteral("Radians")) {
        editor->setSingleStep(0.0001);
        editor->setMinimum(Units::deg2rad(-90.0));
        editor->setMaximum(Units::deg2rad(90.0));
        editor->setDecimals(5);
    }
    else {
        throw GUIHelpers::Error("DetectorEditorWidget::setAngleUnits() ->");
    }
}

