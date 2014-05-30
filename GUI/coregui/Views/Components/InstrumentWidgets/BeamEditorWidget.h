#ifndef BEAM_EDITOR_WIDGET_H
#define BEAM_EDITOR_WIDGET_H

#include <QWidget>

class QComboBox;
class QDoubleSpinBox;
class QLineEdit;
class QLabel;
class BeamItem;
class QDoubleValidator;

class BeamEditorWidget : public QWidget
{
    Q_OBJECT

public:
    BeamEditorWidget(QWidget *parent = 0);

    void initFromItem(BeamItem *item);

public slots:
    void onIntensityEditingFinished();
    void onChangedWavelength(const QString &);
    void onChangedAngle(const QString &);

    void onPropertyChanged(const QString &);

    void onAngleUnitsChanged(int);

private:
    void updateWidgets();
    void setBlockSignals(bool flag);
    void updateAngleUnits(const QString &units);
    void setAngleUnits(QDoubleSpinBox *, const QString &units);

    QLineEdit *m_intensityText;
    QDoubleValidator *m_intensityValidator;
    QDoubleSpinBox *m_wavelengthSpinBox;
    QComboBox *m_angleUnits;
    QDoubleSpinBox *m_inclinationAngleSpinBox;
    QDoubleSpinBox *m_azimuthalAngleSpinBox;
    QComboBox *m_beamTypeCombo;
    BeamItem *m_currentItem;
    bool m_block_signals;
};


#endif
