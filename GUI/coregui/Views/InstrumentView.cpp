#include "InstrumentView.h"

#include "SimulationDataModel.h"
#include "Units.h"
#include "ExperimentConstants.h"

#include <boost/lexical_cast.hpp>

#include <QGroupBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QInputDialog>
#include <QMessageBox>

InstrumentView::InstrumentView(SimulationDataModel *p_simulation_data_model, QWidget *parent)
    : QWidget(parent)
    , mp_simulation_data_model(p_simulation_data_model)
    , mp_cached_instrument(0)
{
    // selection of instrument by name
    QGroupBox *instrumentListGroup = new QGroupBox(tr("Instrument List"));
      // instrument combo box
    QLabel *nameLabel = new QLabel(tr("Select Instrument:"));
    instrumentBox = new QComboBox;
    if (parent) {
        instrumentBox->addItems(mp_simulation_data_model->getInstrumentList().keys());
    }
    addInstrumentButton = new QPushButton(tr("Add..."));
    saveInstrumentButton = new QPushButton(tr("Save"));
    saveInstrumentButton->setEnabled(false);
      // layout
    QGridLayout *instrumentListLayout = new QGridLayout;
    instrumentListLayout->addWidget(nameLabel, 0, 0);
    instrumentListLayout->addWidget(instrumentBox, 0, 1);
    QHBoxLayout *addAndSaveButtonLayout = new QHBoxLayout;
    addAndSaveButtonLayout->addWidget(saveInstrumentButton);
    addAndSaveButtonLayout->addWidget(addInstrumentButton);
    instrumentListLayout->addLayout(addAndSaveButtonLayout, 1, 1);
    instrumentListGroup->setLayout(instrumentListLayout);

    // beam parameters
    QGroupBox *beamParamsGroup = new QGroupBox(tr("Beam Parameters"));
      // intensity
    QLabel *beamIntensityLabel = new QLabel(tr("Intensity (1/s):"));
    beamIntensityEdit = new QLineEdit;
      // wavelength
    QLabel *beamWavelengthLabel = new QLabel(tr("Wavelength (nanometer):"));
    beamWavelengthEdit = new QDoubleSpinBox;
    beamWavelengthEdit->setSingleStep(0.1);
    beamWavelengthEdit->setDecimals(3);
    beamWavelengthEdit->setMaximum(100.);
      // incoming angles
    QLabel *beamAlphaInLabel = new QLabel(tr("Inclination Angle (degrees):"));
    beamAlphaInEdit = new QDoubleSpinBox;
    beamAlphaInEdit->setSingleStep(0.01);
    beamAlphaInEdit->setDecimals(5);
    beamAlphaInEdit->setMaximum(90.);
    QLabel *beamPhiInLabel = new QLabel(tr("Azimuthal Angle (degrees):"));
    beamPhiInEdit = new QDoubleSpinBox;
    beamPhiInEdit->setSingleStep(0.01);
    beamPhiInEdit->setDecimals(5);
    beamPhiInEdit->setMinimum(-90.);
    beamPhiInEdit->setMaximum(90.);
      // layout
    QGridLayout *beamParamsLayout = new QGridLayout;
    beamParamsLayout->addWidget(beamIntensityLabel, 0, 0);
    beamParamsLayout->addWidget(beamIntensityEdit, 0, 1);
    beamParamsLayout->addWidget(beamWavelengthLabel, 1, 0);
    beamParamsLayout->addWidget(beamWavelengthEdit, 1, 1);
    beamParamsLayout->addWidget(beamAlphaInLabel, 2, 0);
    beamParamsLayout->addWidget(beamAlphaInEdit, 2, 1);
    beamParamsLayout->addWidget(beamPhiInLabel, 3, 0);
    beamParamsLayout->addWidget(beamPhiInEdit, 3, 1);
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
    detectorAlphaStartEdit = new QDoubleSpinBox;
    detectorAlphaStartEdit->setSingleStep(0.01);
    detectorAlphaStartEdit->setMinimum(-90.0);
    detectorAlphaStartEdit->setMaximum(90.0);
    detectorAlphaStartEdit->setDecimals(5);
    detectorAlphaEndEdit = new QDoubleSpinBox;
    detectorAlphaEndEdit->setSingleStep(0.01);
    detectorAlphaEndEdit->setMinimum(-90.0);
    detectorAlphaEndEdit->setMaximum(90.0);
    detectorAlphaEndEdit->setDecimals(5);
    detectorAlphaValuesEdit = new QSpinBox;
    detectorAlphaValuesEdit->setMaximum(1000000);
    detectorPhiStartEdit = new QDoubleSpinBox;
    detectorPhiStartEdit->setSingleStep(0.01);
    detectorPhiStartEdit->setMinimum(-90.0);
    detectorPhiStartEdit->setMaximum(90.0);
    detectorPhiStartEdit->setDecimals(5);
    detectorPhiEndEdit = new QDoubleSpinBox;
    detectorPhiEndEdit->setSingleStep(0.01);
    detectorPhiEndEdit->setMinimum(-90.0);
    detectorPhiEndEdit->setMaximum(90.0);
    detectorPhiEndEdit->setDecimals(5);
    detectorPhiValuesEdit = new QSpinBox;
    detectorPhiValuesEdit->setMaximum(1000000);
      // checkbox for IsGISAXS angle initialization
    detectorAnglesIsGISAXSBox = new QCheckBox(tr("IsGISAXS Angle Initialization"));
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

    // update edit boxes to reflect values for selected instrument
    updateEditBoxes();

    // connect signals with slots
    connect(addInstrumentButton, SIGNAL(clicked()), this, SLOT(onAddInstrument()));
    connect(saveInstrumentButton, SIGNAL(clicked()), this, SLOT(onSaveInstrument()));
    connect(instrumentBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onInstrumentSelectionChanged(int)));
    connect(beamIntensityEdit, SIGNAL(textEdited(QString)), this, SLOT(onInstrumentEntryChanged()));
    connect(beamWavelengthEdit, SIGNAL(valueChanged(double)), this, SLOT(onInstrumentEntryChanged()));
    connect(beamAlphaInEdit, SIGNAL(valueChanged(double)), this, SLOT(onInstrumentEntryChanged()));
    connect(beamPhiInEdit, SIGNAL(valueChanged(double)), this, SLOT(onInstrumentEntryChanged()));
    connect(detectorAlphaStartEdit, SIGNAL(valueChanged(double)), this, SLOT(onInstrumentEntryChanged()));
    connect(detectorAlphaEndEdit, SIGNAL(valueChanged(double)), this, SLOT(onInstrumentEntryChanged()));
    connect(detectorAlphaValuesEdit, SIGNAL(valueChanged(int)), this, SLOT(onInstrumentEntryChanged()));
    connect(detectorPhiStartEdit, SIGNAL(valueChanged(double)), this, SLOT(onInstrumentEntryChanged()));
    connect(detectorPhiEndEdit, SIGNAL(valueChanged(double)), this, SLOT(onInstrumentEntryChanged()));
    connect(detectorPhiValuesEdit, SIGNAL(valueChanged(int)), this, SLOT(onInstrumentEntryChanged()));
    connect(detectorAnglesIsGISAXSBox, SIGNAL(clicked()), this, SLOT(onInstrumentEntryChanged()));
}

void InstrumentView::onAddInstrument()
{
    if (saveInstrumentButton->isEnabled()) {
        int ret = saveDiscardCancel();
        if (ret == QMessageBox::Cancel) {
            return;
        }
    }
    bool ok;
    QString instrument_name = QInputDialog::getText(this, tr("New Instrument"),
                                              tr("Instrument Name:"), QLineEdit::Normal,
                                         tr("instrument"), &ok);
    if (ok && !instrument_name.isEmpty()) {
        if (mp_simulation_data_model->getInstrumentList().contains(instrument_name)) {
            QMessageBox::warning(this, tr("Duplicate Instrument Name"),
                                 tr("Instrument Name Already Exists."));
            return;
        }
        QString selected_entry = instrumentBox->currentText();
        Instrument *p_current_instrument;
        if ( (p_current_instrument = mp_simulation_data_model->getInstrumentList().value(selected_entry, 0)) ) {
            mp_cached_instrument = new Instrument(*p_current_instrument);
        } else {
            mp_cached_instrument = new Instrument;
        }
        m_cached_name = instrument_name;
        instrumentBox->addItem(m_cached_name);
        int index = instrumentBox->findText(m_cached_name);
        if (index != -1) {
            instrumentBox->setCurrentIndex(index);
            saveInstrumentButton->setEnabled(true);
            updateEditBoxes();
        }
    }
}

void InstrumentView::onSaveInstrument()
{
    if (mp_cached_instrument) {
        initInstrumentFromForm(mp_cached_instrument);
        if (mp_simulation_data_model->getInstrumentList().contains(m_cached_name)) {
            mp_simulation_data_model->changeInstrument(m_cached_name, mp_cached_instrument);
        } else {
            mp_simulation_data_model->addInstrument(m_cached_name, mp_cached_instrument);
        }
        mp_cached_instrument = 0;
    }
    saveInstrumentButton->setEnabled(false);
}

void InstrumentView::onInstrumentSelectionChanged(int index)
{
    (void)index;
    if ( instrumentBox->currentText() == m_cached_name ) return;
    if (saveInstrumentButton->isEnabled()) {
        int ret = saveDiscardCancel();
        if (ret == QMessageBox::Cancel) {
            return;
        }
    }
    updateEditBoxes();
}

void InstrumentView::onInstrumentEntryChanged()
{
    if (!mp_cached_instrument) {
        mp_cached_instrument = new Instrument;
    }
    saveInstrumentButton->setEnabled(true);
}

void InstrumentView::updateEditBoxes()
{
    if (saveInstrumentButton->isEnabled()) {
        setToInstrumentData(mp_cached_instrument);
    } else {
        m_cached_name = instrumentBox->currentText();
        Instrument *p_instrument;
        if ( (p_instrument = mp_simulation_data_model->getInstrumentList().value(m_cached_name, 0)) ) {
            setToInstrumentData(p_instrument);
        }
    }
}

void InstrumentView::setToInstrumentData(Instrument *p_instrument)
{
    // temporarily block form field changed signals
    setSignalBlock(true);
    // beam data
    QString intensity_string = QString("%1").arg( p_instrument->getIntensity() );
    beamIntensityEdit->setText(intensity_string);
    const cvector_t k_in = p_instrument->getBeam().getCentralK();
    kvector_t k_in_real(k_in.x().real(), k_in.y().real(), k_in.z().real());
    double wavelength = 2.0*M_PI/( k_in_real.mag() );
    beamWavelengthEdit->setValue(wavelength);
    beamAlphaInEdit->setValue(90.0 - k_in_real.theta()/Units::degree);
    beamPhiInEdit->setValue(k_in_real.phi()/Units::degree);

    // detector data
    if (p_instrument->getDetectorDimension()==2) {
        const IAxis &axis1 = p_instrument->getDetectorAxis(0);
        detectorPhiStartEdit->setValue(axis1.getMin()/Units::degree);
        detectorPhiEndEdit->setValue(axis1.getMax()/Units::degree);
        detectorPhiValuesEdit->setValue(axis1.getSize());
        const IAxis &axis2 = p_instrument->getDetectorAxis(1);
        detectorAlphaStartEdit->setValue(axis2.getMin()/Units::degree);
        detectorAlphaEndEdit->setValue(axis2.getMax()/Units::degree);
        detectorAlphaValuesEdit->setValue(axis2.getSize());
        //TODO: add isgisaxs flag
    }
    // remove block
    setSignalBlock(false);
}

void InstrumentView::initInstrumentFromForm(Instrument *p_instrument)
{
    if (!p_instrument) return;
    double intensity = beamIntensityEdit->text().toDouble();
    double lambda = beamWavelengthEdit->value();
    double alpha_i = beamAlphaInEdit->value()*Units::degree;
    double phi_i = beamPhiInEdit->value()*Units::degree;
    double alpha_f_min = detectorAlphaStartEdit->value()*Units::degree;
    double alpha_f_max = detectorAlphaEndEdit->value()*Units::degree;
    size_t alpha_f_n = (size_t)detectorAlphaValuesEdit->value();
    double phi_f_min = detectorPhiStartEdit->value()*Units::degree;
    double phi_f_max = detectorPhiEndEdit->value()*Units::degree;
    size_t phi_f_n = (size_t)detectorPhiValuesEdit->value();
    bool isgisaxs_axes = detectorAnglesIsGISAXSBox->isChecked();
    p_instrument->setBeamIntensity(intensity);
    p_instrument->setBeamParameters(lambda, alpha_i, phi_i);
    p_instrument->setDetectorParameters(phi_f_n, phi_f_min, phi_f_max,
                                        alpha_f_n, alpha_f_min, alpha_f_max,
                                        isgisaxs_axes);
}

void InstrumentView::removeInstrumentName(QString name)
{
    int index = instrumentBox->findText(name);
    if (index != -1) {
        instrumentBox->blockSignals(true);
        instrumentBox->removeItem(index);
        instrumentBox->blockSignals(false);
    }
}

int InstrumentView::saveDiscardCancel()
{
    if (!saveInstrumentButton->isEnabled()) return QMessageBox::NoButton;
    QMessageBox unsaved_changes_box;
    unsaved_changes_box.setText("There are unsaved changes to the current instrument.");
    unsaved_changes_box.setInformativeText("Do you want to save your changes?");
    unsaved_changes_box.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    unsaved_changes_box.setDefaultButton(QMessageBox::Save);
    int ret = unsaved_changes_box.exec();
    switch (ret) {
    case QMessageBox::Save:
        // Save was clicked
        onSaveInstrument();
        break;
    case QMessageBox::Discard:
        // Don't Save was clicked: cached changes are discarded
        delete mp_cached_instrument;
        mp_cached_instrument = 0;
        if (!mp_simulation_data_model->getInstrumentList().contains(m_cached_name)) {
             removeInstrumentName(m_cached_name);
        }
        m_cached_name.clear();
        saveInstrumentButton->setEnabled(false);
        break;
    case QMessageBox::Cancel:
        // Cancel was clicked: selection does not change
        break;
    default:
        // should never be reached
        break;
    }
    return ret;
}

void InstrumentView::setSignalBlock(bool block)
{
    beamIntensityEdit->blockSignals(block);
    beamWavelengthEdit->blockSignals(block);
    beamAlphaInEdit->blockSignals(block);
    beamPhiInEdit->blockSignals(block);
    detectorAlphaStartEdit->blockSignals(block);
    detectorAlphaEndEdit->blockSignals(block);
    detectorAlphaValuesEdit->blockSignals(block);
    detectorPhiStartEdit->blockSignals(block);
    detectorPhiEndEdit->blockSignals(block);
    detectorPhiValuesEdit->blockSignals(block);
    detectorAnglesIsGISAXSBox->blockSignals(block);
}
