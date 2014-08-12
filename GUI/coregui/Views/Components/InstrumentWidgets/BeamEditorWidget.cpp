#include "BeamEditorWidget.h"
#include "ComboProperty.h"
#include "DetectorItems.h"
#include "BeamItem.h"
#include "Units.h"
#include "AngleProperty.h"
#include "GUIHelpers.h"
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

    m_intensityValidator  = new QDoubleValidator(0.1, 1e+100, 2, this);
    m_intensityValidator->setNotation(QDoubleValidator::ScientificNotation);
    m_intensityText->setValidator(m_intensityValidator);

    m_wavelengthSpinBox->setSingleStep(0.1);
    m_wavelengthSpinBox->setDecimals(3);
    m_wavelengthSpinBox->setMaximum(100.);

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
            disconnect(m_currentItem, SIGNAL(propertyChanged(const QString &)), this, SLOT(onPropertyChanged(const QString &)));
            //disconnect(m_currentItem, SIGNAL(propertyItemChanged(const QString &)), this, SLOT(onPropertyChanged(const QString &)));
        }

        m_currentItem = item;

        connect(item, SIGNAL(propertyChanged(const QString &)), this, SLOT(onPropertyChanged(const QString &)));
        connect(item, SIGNAL(propertyItemChanged(const QString &)), this, SLOT(onPropertyChanged(const QString &)));

        updateWidgets();
    }
}


void BeamEditorWidget::onIntensityEditingFinished()
{
    if(m_block_signals) return;
    m_currentItem->setRegisteredProperty(BeamItem::P_INTENSITY, m_intensityText->text().toDouble());
}


void BeamEditorWidget::onChangedWavelength(const QString & /* text */)
{
    if(m_block_signals) return;
    m_currentItem->setRegisteredProperty(BeamItem::P_WAVELENGTH, m_wavelengthSpinBox->value());
}

void BeamEditorWidget::onChangedAngle(const QString &)
{
    if(m_block_signals) return;
//    m_currentItem->setRegisteredProperty(BeamItem::P_INCLINATION_ANGLE, m_inclinationAngleSpinBox->value());

    AngleProperty inclination_angle = m_currentItem->getRegisteredProperty(BeamItem::P_INCLINATION_ANGLE2).value<AngleProperty>();
    inclination_angle.setValue(m_inclinationAngleSpinBox->value());
    m_currentItem->setRegisteredProperty(BeamItem::P_INCLINATION_ANGLE2, inclination_angle.getVariant());

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

//    double alpha = m_currentItem->getRegisteredProperty(BeamItem::P_INCLINATION_ANGLE).toDouble();
//    double phi = m_currentItem->getRegisteredProperty(BeamItem::P_AZIMUTHAL_ANGLE).toDouble();

//    ComboProperty angle_units_property = m_currentItem->getRegisteredProperty(BeamItem::P_ANGLE_UNITS).value<ComboProperty>();
//    updateAngleUnits(angle_units_property.getValue());

//    if(m_angleUnits->currentText() == "Degrees") {
//        m_inclinationAngleSpinBox->setValue(Units::rad2deg(alpha));
//        m_azimuthalAngleSpinBox->setValue(Units::rad2deg(phi));
//    } else {
//        m_inclinationAngleSpinBox->setValue(Units::deg2rad(alpha));
//        m_azimuthalAngleSpinBox->setValue(Units::deg2rad(phi));
//    }

}


void BeamEditorWidget::updateWidgets()
{
    Q_ASSERT(m_currentItem);
    qDebug() << "DetectorEditorWidget::updateWidgets() ->";

    setBlockSignals(true);
    m_intensityText->setText(QString::number(m_currentItem->getRegisteredProperty(BeamItem::P_INTENSITY).toDouble()));
    m_wavelengthSpinBox->setValue(m_currentItem->getRegisteredProperty(BeamItem::P_WAVELENGTH).toDouble());

    m_angleUnits->clear();
    ComboProperty angle_units_property = m_currentItem->getRegisteredProperty(BeamItem::P_ANGLE_UNITS).value<ComboProperty>();
    m_angleUnits->addItems(angle_units_property.getValues());
    m_angleUnits->setCurrentText(angle_units_property.getValue());


    AngleProperty inclination_angle = m_currentItem->getRegisteredProperty(BeamItem::P_INCLINATION_ANGLE2).value<AngleProperty>();
    if(inclination_angle.inDegrees()) {
        setAngleUnits(m_inclinationAngleSpinBox, "Degrees");
    } else {
        setAngleUnits(m_inclinationAngleSpinBox, "Radians");
    }
//    m_inclinationAngleSpinBox->setValue(m_currentItem->getRegisteredProperty(BeamItem::P_INCLINATION_ANGLE).toDouble());
    m_inclinationAngleSpinBox->setValue(inclination_angle.getValue());



    m_azimuthalAngleSpinBox->setValue(m_currentItem->getRegisteredProperty(BeamItem::P_AZIMUTHAL_ANGLE).toDouble());

    setBlockSignals(false);
}


void BeamEditorWidget::setBlockSignals(bool flag)
{
    m_block_signals = flag;
}


//! Update angle limits for all angle editors depending on units: radians or degrees
void BeamEditorWidget::updateAngleUnits(const QString &units)
{
    setAngleUnits(m_inclinationAngleSpinBox, units);
    setAngleUnits(m_azimuthalAngleSpinBox, units);
}


//! Sets angle units and corresponding limits for QDoubleSpinBox
void BeamEditorWidget::setAngleUnits(QDoubleSpinBox *editor, const QString &units)
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
        editor->setDecimals(6);
    }
    else {
        throw GUIHelpers::Error("BeamEditorWidget::setAngleUnits() ->");
    }
}

