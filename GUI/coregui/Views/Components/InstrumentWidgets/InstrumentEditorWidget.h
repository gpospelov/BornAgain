#ifndef INSTRUMENT_EDITOR_WIDGET_H
#define INSTRUMENT_EDITOR_WIDGET_H


#include <QWidget>
#include <QLabel>
#include <QMap>

class ParameterizedItem;
class DetectorEditorWidget;
class BeamEditorWidget;
class QLineEdit;
class QComboBox;

class InstrumentEditorWidget : public QWidget
{
    Q_OBJECT

public:
    InstrumentEditorWidget(QWidget *parent = 0);
    QSize sizeHint() const { return QSize(600, 600); }

    void setInstrumentItem(ParameterizedItem *instrument);

public slots:
    void onChangedEditor(const QString &);
    void onPropertyChanged(const QString &);

private:
    void updateWidgets();

    QLineEdit *m_nameLineEdit;
    QComboBox *m_typeComboBox;
    BeamEditorWidget *m_beamWidget;
    DetectorEditorWidget *m_detectorWidget;

    ParameterizedItem *m_currentItem;
    bool m_block_signals;
};

#endif
