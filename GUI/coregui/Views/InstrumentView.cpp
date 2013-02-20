#include "InstrumentView.h"

#include <QGroupBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QCheckBox>
#include <QDoubleSpinBox>

InstrumentManager::InstrumentManager(QWidget *parent)
    : QWidget(parent)
{
    // selection of instrument by name
    QGroupBox *instrumentListGroup = new QGroupBox(tr("Instrument List"));
      // instrument combo box
    QLabel *nameLabel = new QLabel(tr("Select Instrument:"));
    QComboBox *instrumentBox = new QComboBox;
    instrumentBox->addItem(tr("Default GISAXS"));
      // layout
    QHBoxLayout *instrumentListLayout = new QHBoxLayout;
    instrumentListLayout->addWidget(nameLabel);
    instrumentListLayout->addWidget(instrumentBox);
    instrumentListGroup->setLayout(instrumentListLayout);

    // beam parameters
    QGroupBox *beamParamsGroup = new QGroupBox(tr("Beam Parameters"));
      // intensity
    QLabel *beamIntensityLabel = new QLabel(tr("Intensity (1/s):"));
    QDoubleSpinBox *beamIntensityEdit = new QDoubleSpinBox;
      // incoming angles
    QLabel *beamAlphaInLabel = new QLabel(tr("Inclination Angle (degrees):"));
    QDoubleSpinBox *beamAlphaInEdit = new QDoubleSpinBox;
    QLabel *beamPhiInLabel = new QLabel(tr("Azimuthal Angle (degrees):"));
    QDoubleSpinBox *beamPhiInEdit = new QDoubleSpinBox;
      // layout
    QGridLayout *beamParamsLayout = new QGridLayout;
    beamParamsLayout->addWidget(beamIntensityLabel, 0, 0);
    beamParamsLayout->addWidget(beamIntensityEdit, 0, 1);
    beamParamsLayout->addWidget(beamAlphaInLabel, 1, 0);
    beamParamsLayout->addWidget(beamAlphaInEdit, 1, 1);
    beamParamsLayout->addWidget(beamPhiInLabel, 2, 0);
    beamParamsLayout->addWidget(beamPhiInEdit, 2, 1);
    beamParamsGroup->setLayout(beamParamsLayout);

    // detector parameters
    QGroupBox *detectorParamsGroup = new QGroupBox(tr("Detector Parameters"));
      // range labels
    QLabel *startRangeLabel = new QLabel(tr("Start"));
    QLabel *endRangeLabel = new QLabel(tr("End"));
    QLabel *nbrValuesRangeLabel = new QLabel(tr("# values"));
      // angle labels
    QLabel *detectorAlphaRangeLabel = new QLabel(tr("Inclination Range (degrees):"));
    QLabel *detectorPhiRangeLabel = new QLabel(tr("Azimuthal Range (degrees):"));
      // range input edits
    QDoubleSpinBox *detectorAlphaStartEdit = new QDoubleSpinBox;
    QDoubleSpinBox *detectorAlphaEndEdit = new QDoubleSpinBox;
    QSpinBox *detectorAlphaValuesEdit = new QSpinBox;
    QDoubleSpinBox *detectorPhiStartEdit = new QDoubleSpinBox;
    QDoubleSpinBox *detectorPhiEndEdit = new QDoubleSpinBox;
    QSpinBox *detectorPhiValuesEdit = new QSpinBox;
      // checkbox for IsGISAXS angle initialization
    QCheckBox *detectorAnglesIsGISAXSBox = new QCheckBox(tr("IsGISAXS Angle Initialization"));
      // layout
    QGridLayout *detectorParamsLayout = new QGridLayout;
    detectorParamsLayout->addWidget(startRangeLabel, 0, 1);
    detectorParamsLayout->addWidget(endRangeLabel, 0, 2);
    detectorParamsLayout->addWidget(nbrValuesRangeLabel, 0, 3);
    detectorParamsLayout->addWidget(detectorAlphaRangeLabel, 1, 0);
    detectorParamsLayout->addWidget(detectorAlphaStartEdit, 1, 1);
    detectorParamsLayout->addWidget(detectorAlphaEndEdit, 1, 2);
    detectorParamsLayout->addWidget(detectorAlphaValuesEdit, 1, 3);
    detectorParamsLayout->addWidget(detectorPhiRangeLabel, 2, 0);
    detectorParamsLayout->addWidget(detectorPhiStartEdit, 2, 1);
    detectorParamsLayout->addWidget(detectorPhiEndEdit, 2, 2);
    detectorParamsLayout->addWidget(detectorPhiValuesEdit, 2, 3);
    detectorParamsLayout->addWidget(detectorAnglesIsGISAXSBox, 3, 0);
    detectorParamsGroup->setLayout(detectorParamsLayout);

    // main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(instrumentListGroup);
   // mainLayout->addSpacing(12);
    mainLayout->addWidget(beamParamsGroup);
    mainLayout->addWidget(detectorParamsGroup);
    mainLayout->addStretch();
    setLayout(mainLayout);
}

