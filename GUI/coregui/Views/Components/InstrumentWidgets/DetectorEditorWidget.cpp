#include "DetectorEditorWidget.h"
#include "FancyGroupProperty.h"
#include "ComboProperty.h"
#include "DetectorItems.h"
#include "GUIHelpers.h"
#include "Units.h"
#include "AngleProperty.h"
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
    detectorGroup->setLayout(detectorLayout);

    // main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(detectorGroup);
    setLayout(mainLayout);

    connect(m_detectorTypeCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(onDetectorTypeChanged(int)));
    connect(m_unitsCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(onAngleUnitsChanged(int)));
    connect(m_binningTypeCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(onBinningTypeChanged(int)));
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
//    FancyGroupProperty_t *detector_property = m_currentItem->getRegisteredProperty(DetectorItem::P_DETECTOR).value<FancyGroupProperty_t *>();
    FancyGroupProperty_t detector_property = m_currentItem->getRegisteredProperty(DetectorItem::P_DETECTOR).value<FancyGroupProperty_t>();

    m_detectorTypeCombo->addItems(detector_property->getValueLabels());
    m_detectorTypeCombo->setCurrentIndex(detector_property->toIndex(detector_property->getValue()));


    ParameterizedItem *subDetector = m_currentItem->getSubItems()[DetectorItem::P_DETECTOR];
    Q_ASSERT(subDetector);

    if (subDetector->modelType() == Constants::PhiAlphaDetectorType) {

        AngleProperty units = subDetector->getRegisteredProperty(PhiAlphaDetectorItem::P_AXES_UNITS).value<AngleProperty>();
        m_unitsCombo->clear();
        m_unitsCombo->addItems(units.getLabels());
        m_unitsCombo->setCurrentText(units.getUnits());

        m_binningTypeCombo->clear();
        ComboProperty binning_property = subDetector->getRegisteredProperty(PhiAlphaDetectorItem::P_BINNING).value<ComboProperty>();
        m_binningTypeCombo->addItems(binning_property.getValues());
        m_binningTypeCombo->setCurrentText(binning_property.getValue());

        int nphi = subDetector->getRegisteredProperty(PhiAlphaDetectorItem::P_NPHI).toInt();
        m_nphiEdit->setValue(nphi);
        AngleProperty phi_min_property = subDetector->getRegisteredProperty(PhiAlphaDetectorItem::P_PHI_MIN).value<AngleProperty>();
        setAngleUnits(m_phiMinEdit, phi_min_property);
        AngleProperty phi_max_property = subDetector->getRegisteredProperty(PhiAlphaDetectorItem::P_PHI_MAX).value<AngleProperty>();
        setAngleUnits(m_phiMaxEdit, phi_max_property);

        int nalpha = subDetector->getRegisteredProperty(PhiAlphaDetectorItem::P_NALPHA).toInt();
        AngleProperty alpha_min_property = subDetector->getRegisteredProperty(PhiAlphaDetectorItem::P_ALPHA_MIN).value<AngleProperty>();
        setAngleUnits(m_alphaMinEdit, alpha_min_property);
        AngleProperty alpha_max_property = subDetector->getRegisteredProperty(PhiAlphaDetectorItem::P_ALPHA_MAX).value<AngleProperty>();
        setAngleUnits(m_alphaMaxEdit, alpha_max_property);
        m_nalphaEdit->setValue(nalpha);

    } else {
        throw GUIHelpers::Error("DetectorEditorWidget::updateWidgets() -> Unknown detector item");
    }

    m_block_signals = false;
}



void DetectorEditorWidget::onPropertyChanged(const QString &name)
{
    qDebug() << "DetectorEditorWidget::onPropertyChanged() -> " << name;
    updateWidgets();
}


void DetectorEditorWidget::onDetectorTypeChanged(int)
{
    qDebug() << "DetectorEditorWidget::onDetectorTypeChanged() -> ";
    if(m_block_signals) return;
    m_currentItem->setGroupProperty(Constants::DetectorGroup, m_detectorTypeCombo->currentText());
}


void DetectorEditorWidget::onAngleUnitsChanged(int)
{
    if(m_block_signals) return;
    qDebug() << "DetectorEditorWidget::onAngleUnitsChanged()" << m_currentItem;
    ParameterizedItem *subDetector = m_currentItem->getSubItems()[DetectorItem::P_DETECTOR];


    AngleProperty units = subDetector->getRegisteredProperty(PhiAlphaDetectorItem::P_AXES_UNITS).value<AngleProperty>();
    units.setUnits(m_unitsCombo->currentText());
    subDetector->setRegisteredProperty(PhiAlphaDetectorItem::P_AXES_UNITS, units.getVariant());
    updateWidgets();

}


void DetectorEditorWidget::onBinningTypeChanged(int)
{
    qDebug() << "DetectorEditorWidget::onBinningTypeChanged() -> " << m_block_signals;
    if(m_block_signals) return;

    ParameterizedItem *subDetector = m_currentItem->getSubItems()[DetectorItem::P_DETECTOR];

    ComboProperty combo_property = subDetector->getRegisteredProperty(PhiAlphaDetectorItem::P_BINNING).value<ComboProperty>();
    combo_property.setValue(m_binningTypeCombo->currentText());
    subDetector->setRegisteredProperty(PhiAlphaDetectorItem::P_BINNING, combo_property.getVariant());
}




void DetectorEditorWidget::onAngleEditorChanged(const QString &)
{
    qDebug() << "DetectorEditorWidget::onAngleEditorChanged() ->";
    if(m_block_signals) return;
    qDebug() << "DetectorEditorWidget::onAngleEditorChanged()";
    ParameterizedItem *subDetector = m_currentItem->getSubItems()[DetectorItem::P_DETECTOR];
    Q_ASSERT(subDetector);
    Q_ASSERT(subDetector->modelType() == Constants::PhiAlphaDetectorType);
    subDetector->setRegisteredProperty(PhiAlphaDetectorItem::P_NPHI, m_nphiEdit->value());

    AngleProperty phi_min_property = subDetector->getRegisteredProperty(PhiAlphaDetectorItem::P_PHI_MIN).value<AngleProperty>();
    phi_min_property.setValue(m_phiMinEdit->value());
    subDetector->setRegisteredProperty(PhiAlphaDetectorItem::P_PHI_MIN, phi_min_property.getVariant());

    AngleProperty phi_max_property = subDetector->getRegisteredProperty(PhiAlphaDetectorItem::P_PHI_MAX).value<AngleProperty>();
    phi_max_property.setValue(m_phiMaxEdit->value());
    subDetector->setRegisteredProperty(PhiAlphaDetectorItem::P_PHI_MAX, phi_max_property.getVariant());

    subDetector->setRegisteredProperty(PhiAlphaDetectorItem::P_NALPHA, m_nalphaEdit->value());

    AngleProperty alpha_min_property = subDetector->getRegisteredProperty(PhiAlphaDetectorItem::P_ALPHA_MIN).value<AngleProperty>();
    alpha_min_property.setValue(m_alphaMinEdit->value());
    subDetector->setRegisteredProperty(PhiAlphaDetectorItem::P_ALPHA_MIN, alpha_min_property.getVariant());

    AngleProperty alpha_max_property = subDetector->getRegisteredProperty(PhiAlphaDetectorItem::P_ALPHA_MAX).value<AngleProperty>();
    alpha_max_property.setValue(m_alphaMaxEdit->value());
    subDetector->setRegisteredProperty(PhiAlphaDetectorItem::P_ALPHA_MAX, alpha_max_property.getVariant());

}


void DetectorEditorWidget::setAngleUnits(QDoubleSpinBox *editor, const AngleProperty &units, double min_deg, double max_deg)
{
    if(units.inDegrees()) {
        editor->setSingleStep(0.01);
        editor->setMinimum(min_deg);
        editor->setMaximum(max_deg);
        editor->setDecimals(3);
        editor->setValue(units.getValue());
    }
    else {
        editor->setSingleStep(0.0001);
        editor->setMinimum(Units::deg2rad(min_deg));
        editor->setMaximum(Units::deg2rad(max_deg));
        editor->setDecimals(6);
        editor->setValue(units.getValue());
    }
}

