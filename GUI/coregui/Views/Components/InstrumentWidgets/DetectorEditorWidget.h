#ifndef DETECTOR_EDITOR_WIDGET_H
#define DETECTOR_EDITOR_WIDGET_H

#include <QWidget>

class QComboBox;
class QLabel;
class ParameterizedItem;

class DetectorEditorWidget : public QWidget
{
    Q_OBJECT

public:
    DetectorEditorWidget(QWidget *parent = 0);

    void initFromItem(ParameterizedItem *item);

public slots:
    void onPropertyChanged(const QString &);
    void onDetectorTypeChanged(int);

private:
    void updateWidgets();

    QComboBox *m_detectorTypeCombo;
    QComboBox *m_unitsCombo;
    QComboBox *m_binningTypeCombo;

    QLabel *m_axis0Label;
    QLabel *m_axis1Label;


    ParameterizedItem *m_currentItem;

    bool m_block_signals;
};

#endif
