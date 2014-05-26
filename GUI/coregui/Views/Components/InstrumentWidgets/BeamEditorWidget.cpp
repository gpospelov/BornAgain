#include "BeamEditorWidget.h"
#include "GroupProperty.h"
#include "ComboProperty.h"
#include "DetectorItems.h"
#include "BeamItem.h"
#include "Units.h"
#include <QLineEdit>
#include <QBoxLayout>
#include <QDoubleValidator>
#include <QLabel>
#include <QGroupBox>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QDebug>

BeamEditorWidget::BeamEditorWidget(QWidget *parent)
    : QWidget(parent)
    , m_intensityText( new QLineEdit)
    , m_intensityValidator(0)
    , m_wavelengthSpinBox(new QDoubleSpinBox)
    , m_angleUnits(new QComboBox)
    , m_inclinationAngleSpinBox(new QDoubleSpinBox)
    , m_azimuthalAngleSpinBox(new QDoubleSpinBox)
    , m_beamTypeCombo(new QComboBox)
    , m_currentItem(0)
    , m_block_signals(false)
{

//    QGroupBox *angleGroup = new QGroupBox("Incident angle");
//    QGridLayout *angleLayout = new QGridLayout;
//    angleLayout->addWidget(new QLabel("Units"), 0, 0);
//    angleLayout->addWidget(m_angleUnits, 0, 1);
//    angleLayout->addWidget(new QLabel("Inclination"), 1, 0);
//    angleLayout->addWidget(m_inclinationAngleSpinBox, 1, 1);
//    angleLayout->addWidget(new QLabel("Azimuthal angle"), 2, 0);
//    angleLayout->addWidget(m_azimuthalAngleSpinBox, 2, 1);
//    angleGroup->setLayout(angleLayout);

    // initial setting

    m_intensityValidator  = new QDoubleValidator(0.1, 1e+100, 2, this);
    m_intensityValidator->setNotation(QDoubleValidator::ScientificNotation);
    m_intensityText->setValidator(m_intensityValidator);

    m_wavelengthSpinBox->setSingleStep(0.1);
    m_wavelengthSpinBox->setDecimals(3);
    m_wavelengthSpinBox->setMaximum(100.);

//    m_inclinationAngleSpinBox->setSingleStep(0.01);
//    m_inclinationAngleSpinBox->setDecimals(5);
//    m_inclinationAngleSpinBox->setMaximum(90.);

//    m_azimuthalAngleSpinBox->setSingleStep(0.01);
//    m_azimuthalAngleSpinBox->setDecimals(5);
//    m_azimuthalAngleSpinBox->setMinimum(-90.);
//    m_azimuthalAngleSpinBox->setMaximum(90.);


    m_beamTypeCombo->addItem("Monochromatic");

    // group box layout
    QGroupBox *beamGroup = new QGroupBox("Beam Parameters");
    QVBoxLayout *beamGroupLayout = new QVBoxLayout;
    beamGroup->setLayout(beamGroupLayout);

    QGridLayout *beamParamsLayout = new QGridLayout;
    beamParamsLayout->addWidget(new QLabel(BeamItem::P_INTENSITY), 0, 0);
    beamParamsLayout->addWidget(m_intensityText, 0, 1);
    beamParamsLayout->addWidget(new QLabel(BeamItem::P_WAVELENGTH), 1, 0);
    beamParamsLayout->addWidget(m_wavelengthSpinBox, 1, 1);

    beamParamsLayout->addWidget(new QLabel("   "), 2, 2);

    beamParamsLayout->addWidget(new QLabel("Inclination angle"), 3, 0);
    beamParamsLayout->addWidget(m_inclinationAngleSpinBox, 3, 1);
    beamParamsLayout->addWidget(m_angleUnits, 3, 2);
    beamParamsLayout->addWidget(new QLabel("Azimuthal angle"), 4, 0);
    beamParamsLayout->addWidget(m_azimuthalAngleSpinBox, 4, 1);

    beamParamsLayout->addWidget(new QLabel("Beam Type"), 5, 0);
    beamParamsLayout->addWidget(m_beamTypeCombo, 5, 1);

    beamGroupLayout->addLayout(beamParamsLayout);

    // main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(beamGroup);
    setLayout(mainLayout);

    // signals
    connect(m_intensityText, SIGNAL(editingFinished()), this, SLOT(onIntensityEditingFinished()));
    connect(m_wavelengthSpinBox, SIGNAL(valueChanged(const QString &)), this, SLOT(onChangedWavelength(const QString &)));
    connect(m_angleUnits, SIGNAL(currentIndexChanged(int)), this, SLOT(onAngleUnitsChanged(int)));
    connect(m_inclinationAngleSpinBox, SIGNAL(valueChanged(const QString &)), this, SLOT(onChangedAngle(const QString &)));
    connect(m_azimuthalAngleSpinBox, SIGNAL(valueChanged(const QString &)), this, SLOT(onChangedAngle(const QString &)));

}

void BeamEditorWidget::initFromItem(BeamItem *item)
{
    qDebug() << "DetectorEditorWidget::initFromItem()";

    if(item != m_currentItem) {
        if(m_currentItem) {
            disconnect(m_currentItem, SIGNAL(propertyChanged(QString)), this, SLOT(onPropertyChanged(QString)));
            //disconnect(m_currentItem, SIGNAL(propertyItemChanged(QString)), this, SLOT(onPropertyChanged(QString)));
        }

        m_currentItem = item;

        connect(item, SIGNAL(propertyChanged(QString)), this, SLOT(onPropertyChanged(QString)));
        connect(item, SIGNAL(propertyItemChanged(QString)), this, SLOT(onPropertyChanged(QString)));

        updateWidgets();
    }
}


void BeamEditorWidget::onIntensityEditingFinished()
{
    if(m_block_signals) return;
    m_currentItem->setRegisteredProperty(BeamItem::P_INTENSITY, m_intensityText->text().toDouble());
}


void BeamEditorWidget::onChangedWavelength(const QString &text)
{
    if(m_block_signals) return;
    m_currentItem->setRegisteredProperty(BeamItem::P_WAVELENGTH, m_wavelengthSpinBox->value());
}

void BeamEditorWidget::onChangedAngle(const QString &)
{
    if(m_block_signals) return;
    m_currentItem->setRegisteredProperty(BeamItem::P_INCLINATION_ANGLE, m_inclinationAngleSpinBox->value());
    m_currentItem->setRegisteredProperty(BeamItem::P_AZIMUTHAL_ANGLE, m_azimuthalAngleSpinBox->value());
}


void BeamEditorWidget::onPropertyChanged(const QString &name)
{
    qDebug() << "BeamEditorWidget::onPropertyChanged() -> " << name;
    updateWidgets();
}



void BeamEditorWidget::onAngleUnitsChanged(int)
{
    if(m_block_signals) return;
    qDebug() << "BeamEditorWidget::onAngleUnitsChanged(int) " << m_angleUnits->currentText();
    ComboProperty units_property = m_currentItem->getRegisteredProperty(BeamItem::P_ANGLE_UNITS).value<ComboProperty>();
    units_property.setValue(m_angleUnits->currentText());
    m_currentItem->setRegisteredProperty(BeamItem::P_ANGLE_UNITS, units_property.getVariant());

    double alpha = m_currentItem->getRegisteredProperty(BeamItem::P_INCLINATION_ANGLE).toDouble();
    double phi = m_currentItem->getRegisteredProperty(BeamItem::P_AZIMUTHAL_ANGLE).toDouble();
    updateAngleLimits();
    if(m_angleUnits->currentText() == "Degrees") {
        m_inclinationAngleSpinBox->setValue(Units::rad2deg(alpha));
        m_azimuthalAngleSpinBox->setValue(Units::rad2deg(phi));
    } else {
        m_inclinationAngleSpinBox->setValue(Units::deg2rad(alpha));
        m_azimuthalAngleSpinBox->setValue(Units::deg2rad(phi));
    }

}


void BeamEditorWidget::updateWidgets()
{
    Q_ASSERT(m_currentItem);
    qDebug() << "DetectorEditorWidget::updateWidgets() ->";

    setBlockSignals(true);
    m_intensityText->setText(QString::number(m_currentItem->getRegisteredProperty(BeamItem::P_INTENSITY).toDouble()));
    m_wavelengthSpinBox->setValue(m_currentItem->getRegisteredProperty(BeamItem::P_WAVELENGTH).toDouble());


//    m_inclinationAngleSpinBox->setSingleStep(0.01);
//    m_inclinationAngleSpinBox->setDecimals(5);
//    m_inclinationAngleSpinBox->setMaximum(90.);

//    m_azimuthalAngleSpinBox->setSingleStep(0.01);
//    m_azimuthalAngleSpinBox->setDecimals(5);
//    m_azimuthalAngleSpinBox->setMinimum(-90.);
//    m_azimuthalAngleSpinBox->setMaximum(90.);

    qDebug() << "       DetectorEditorWidget::updateWidgets() 1.1";
    m_angleUnits->clear();
    ComboProperty angle_units_property = m_currentItem->getRegisteredProperty(BeamItem::P_ANGLE_UNITS).value<ComboProperty>();
    qDebug() << "       DetectorEditorWidget::updateWidgets() 1.2";
    m_angleUnits->addItems(angle_units_property.getValues());
    m_angleUnits->setCurrentText(angle_units_property.getValue());
    qDebug() << "       DetectorEditorWidget::updateWidgets() 1.3";

    //updateAngleLimits();
    m_inclinationAngleSpinBox->setValue(m_currentItem->getRegisteredProperty(BeamItem::P_INCLINATION_ANGLE).toDouble());
    m_azimuthalAngleSpinBox->setValue(m_currentItem->getRegisteredProperty(BeamItem::P_AZIMUTHAL_ANGLE).toDouble());

    setBlockSignals(false);
}


void BeamEditorWidget::setBlockSignals(bool flag)
{
    m_block_signals = flag;
}


void BeamEditorWidget::updateAngleLimits()
{
    qDebug() << "BeamEditorWidget::updateAngleLimits()";
    if(m_angleUnits->currentText() == "Degrees") {
        qDebug() << "BeamEditorWidget::updateAngleLimits() -> Degrees";
        m_inclinationAngleSpinBox->setSingleStep(0.01);
        m_inclinationAngleSpinBox->setDecimals(5);
        m_inclinationAngleSpinBox->setMaximum(90.);

        m_azimuthalAngleSpinBox->setSingleStep(0.01);
        m_azimuthalAngleSpinBox->setDecimals(5);
        m_azimuthalAngleSpinBox->setMinimum(-90.);
        m_azimuthalAngleSpinBox->setMaximum(90.);

    } else {
        qDebug() << "BeamEditorWidget::updateAngleLimits() -> radians";
        m_inclinationAngleSpinBox->setSingleStep(0.0001);
        m_inclinationAngleSpinBox->setDecimals(8);
        m_inclinationAngleSpinBox->setMaximum(Units::deg2rad(90.));

        m_azimuthalAngleSpinBox->setSingleStep(0.0001);
        m_azimuthalAngleSpinBox->setDecimals(8);
        m_azimuthalAngleSpinBox->setMinimum(Units::deg2rad(-90.));
        m_azimuthalAngleSpinBox->setMaximum(Units::deg2rad(90.));
    }
}

