#ifndef QUICKSIMULATIONWIDGET_H
#define QUICKSIMULATIONWIDGET_H

#include <QWidget>
#include <QString>
class SampleModel;
class InstrumentModel;
class ModelTuningWidget;
class QuickSimulationRunner;
class OutputDataWidget;
class QSplitter;
class QuickSimulationSettings;


//! The QuickSimulationWidget is the main widget to access quick simulation functionality.
//! Resides on the second tab of the SimulationView. Holds widget for tuning model
//! parameters and plot widget.
class QuickSimulationWidget : public QWidget
{
    Q_OBJECT

public:
    QuickSimulationWidget(SampleModel *sampleModel, InstrumentModel *instrumentModel, QWidget *parent = 0);
    void updateViews(const QString &instrument, const QString &sample);

public slots:
    void sliderRangeChanged(double value);

private:
    SampleModel *m_sampleModel;
    InstrumentModel *m_instrumentModel;
    ModelTuningWidget *m_modelTuningWidget;
    QuickSimulationRunner *m_quickSimulationRunner;
    OutputDataWidget *m_outputDataWidget;
    QSplitter *m_splitter;
    QuickSimulationSettings *m_quickSimulationSettings;

};


#endif // QUICKSIMULATIONWIDGET_H

