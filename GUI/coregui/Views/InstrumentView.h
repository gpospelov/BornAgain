#ifndef INSTRMANAGER_H
#define INSTRMANAGER_H

#include <QWidget>

class SimulationDataModel;
class Instrument;
class QDoubleSpinBox;
class QComboBox;
class QPushButton;
class QLineEdit;
class QSpinBox;
class QCheckBox;

class InstrumentView : public QWidget
{
    Q_OBJECT

public:
    InstrumentView(SimulationDataModel *simulation_data_model, QWidget *parent = 0);

public slots:
    void onAddInstrument();
    void onSaveInstrument();
    void onInstrumentSelectionChanged(int index);
    void onInstrumentEntryChanged();
private:
    void updateEditBoxes();
    void setToInstrumentData(Instrument *p_instrument);
    void initInstrumentFromForm(Instrument *p_instrument);
    void removeInstrumentName(QString name);
    void setSignalBlock(bool block);
    SimulationDataModel *mp_simulation_data_model;
    Instrument *mp_cached_instrument;
    QString m_cached_name;
    // qt widgets:
    QComboBox *instrumentBox;
    QPushButton *addInstrumentButton;
    QPushButton *saveInstrumentButton;
    QLineEdit *beamIntensityEdit;
    QDoubleSpinBox *beamWavelengthEdit;
    QDoubleSpinBox *beamAlphaInEdit;
    QDoubleSpinBox *beamPhiInEdit;
    QDoubleSpinBox *detectorAlphaStartEdit;
    QDoubleSpinBox *detectorAlphaEndEdit;
    QSpinBox *detectorAlphaValuesEdit;
    QDoubleSpinBox *detectorPhiStartEdit;
    QDoubleSpinBox *detectorPhiEndEdit;
    QSpinBox *detectorPhiValuesEdit;
    QCheckBox *detectorAnglesIsGISAXSBox;
};

#endif // INSTRMANAGER_H
