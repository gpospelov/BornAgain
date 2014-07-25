#ifndef QUICKSIMULATIONWIDGET_H
#define QUICKSIMULATIONWIDGET_H

#include <QWidget>
#include <QString>
class SampleModel;
class InstrumentModel;
class SampleTuningWidget;
class PlotWidget;

class QuickSimulationWidget : public QWidget
{
    Q_OBJECT

public:
    QuickSimulationWidget(SampleModel *sampleModel, InstrumentModel *instrumentModel, QWidget *parent = 0);
    void updateViews(const QString &instrument, const QString &sample);

private:
    SampleModel *m_sampleModel;
    InstrumentModel *m_instrumentModel;
    SampleTuningWidget *m_sampleTuningWidget;
    PlotWidget *m_plotWidget;

};


#endif // QUICKSIMULATIONWIDGET_H

