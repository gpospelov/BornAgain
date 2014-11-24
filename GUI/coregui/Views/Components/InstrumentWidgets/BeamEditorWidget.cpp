#include "BeamEditorWidget.h"
#include "ComboProperty.h"
#include "DetectorItems.h"
#include "BeamItem.h"
#include "Units.h"
#include "AngleProperty.h"
#include "GUIHelpers.h"
#include "GroupBox.h"
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




    GroupBox *settingsGroupBox = new GroupBox("Beam Type Settings");
    QVBoxLayout *beamTypeSettingsGroupLayout2 = new QVBoxLayout;
    settingsGroupBox->setLayout(beamTypeSettingsGroupLayout2);

    QGridLayout *beamTypeLayout2 = new QGridLayout;
    beamTypeLayout2->addWidget(new QLabel("Param 1"), 0, 0);
    beamTypeLayout2->addWidget(new QLineEdit, 0, 1);
    beamTypeLayout2->addWidget(new QLabel("Param 2"), 1, 0);
    beamTypeLayout2->addWidget(new QLineEdit, 1, 1);

    beamTypeSettingsGroupLayout2->addLayout(beamTypeLayout2);

    beamParamsLayout->addWidget(settingsGroupBox, 6,1,1,1);





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
//        connect(item, SIGNAL(propertyItemChanged(const QString &)), this, SLOT(onPropertyChanged(const QString &)));

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

    AngleProperty inclination_angle = m_currentItem->getRegisteredProperty(BeamItem::P_INCLINATION_ANGLE).value<AngleProperty>();
    inclination_angle.setValue(m_inclinationAngleSpinBox->value());
    m_currentItem->setRegisteredProperty(BeamItem::P_INCLINATION_ANGLE, inclination_angle.getVariant());

    AngleProperty azimuthal_angle = m_currentItem->getRegisteredProperty(BeamItem::P_AZIMUTHAL_ANGLE).value<AngleProperty>();
    azimuthal_angle.setValue(m_azimuthalAngleSpinBox->value());
    m_currentItem->setRegisteredProperty(BeamItem::P_AZIMUTHAL_ANGLE, azimuthal_angle.getVariant());
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
    AngleProperty inclination_angle = m_currentItem->getRegisteredProperty(BeamItem::P_INCLINATION_ANGLE).value<AngleProperty>();
    inclination_angle.setUnits(m_angleUnits->currentText());
    m_currentItem->setRegisteredProperty(BeamItem::P_INCLINATION_ANGLE, inclination_angle.getVariant());
}


void BeamEditorWidget::updateWidgets()
{
    Q_ASSERT(m_currentItem);
    qDebug() << "DetectorEditorWidget::updateWidgets() ->";

    setBlockSignals(true);
    m_intensityText->setText(QString::number(m_currentItem->getRegisteredProperty(BeamItem::P_INTENSITY).toDouble()));
    m_wavelengthSpinBox->setValue(m_currentItem->getRegisteredProperty(BeamItem::P_WAVELENGTH).toDouble());

    AngleProperty inclination_angle = m_currentItem->getRegisteredProperty(BeamItem::P_INCLINATION_ANGLE).value<AngleProperty>();
    AngleProperty azimuthal_angle = m_currentItem->getRegisteredProperty(BeamItem::P_AZIMUTHAL_ANGLE).value<AngleProperty>();

    // Units from inclination_agle will control azimuthal_angle too
    m_angleUnits->clear();
    m_angleUnits->addItems(inclination_angle.getLabels());
    m_angleUnits->setCurrentText(inclination_angle.getUnits());

    setAngleUnits(m_inclinationAngleSpinBox, inclination_angle);
    setAngleUnits(m_azimuthalAngleSpinBox, azimuthal_angle);

    setBlockSignals(false);
}


void BeamEditorWidget::setBlockSignals(bool flag)
{
    m_block_signals = flag;
}


void BeamEditorWidget::setAngleUnits(QDoubleSpinBox *editor, const AngleProperty &units, double min_deg, double max_deg)
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
