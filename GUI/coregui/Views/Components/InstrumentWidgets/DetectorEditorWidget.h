#ifndef DETECTOR_EDITOR_WIDGET_H
#define DETECTOR_EDITOR_WIDGET_H

#include <QWidget>

class QComboBox;
class QLabel;
class ParameterizedItem;
class QSpinBox;
class QDoubleSpinBox;

class DetectorEditorWidget : public QWidget
{
    Q_OBJECT

public:
    DetectorEditorWidget(QWidget *parent = 0);

    void initFromItem(ParameterizedItem *item);

public slots:
    void onPropertyChanged(const QString &);
    void onDetectorTypeChanged(int);
    void onAngleEditorChanged(const QString &);

private:
    void updateWidgets();
    void updateAngleUnits(const QString &units);
    void setAngleUnits(QDoubleSpinBox *, const QString &units);

    QComboBox *m_detectorTypeCombo;
    QComboBox *m_unitsCombo;
    QComboBox *m_binningTypeCombo;

    QLabel *m_axis0Label;
    QLabel *m_axis1Label;

    QDoubleSpinBox *m_phiMinEdit;
    QDoubleSpinBox *m_phiMaxEdit;
    QSpinBox *m_nphiEdit;
    QDoubleSpinBox *m_alphaMinEdit;
    QDoubleSpinBox *m_alphaMaxEdit;
    QSpinBox *m_nalphaEdit;

    ParameterizedItem *m_currentItem;
    bool m_block_signals;
};

#endif
