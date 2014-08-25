#ifndef MODELTUNINGWIDDGET_H
#define MODELTUNINGWIDDGET_H

#include <QWidget>
#include <QTreeView>
#include <QAction>
#include <QSignalMapper>
#include <QTableWidget>
#include <QStandardItemModel>

#include "ItemLink.h"

class ModelTuningDelegate;
class ParameterizedItem;
class SampleModel;
class InstrumentModel;
class QuickSimulationRunner;


//! TestView window to try things in mainwindow
class ModelTuningWidget : public QWidget
{
    Q_OBJECT

public:
    ModelTuningWidget(SampleModel *sampleModel, InstrumentModel *instrumentModel, QWidget *parent = 0);
    void updateTreeView(const QString &instrument, const QString &sample);

    void setSampleModel(SampleModel *sampleModel);

    void setInstrumentModel(InstrumentModel *instrumentModel);

    void setQuickSimulationRunner(QuickSimulationRunner * simulationRunner);
    void setSliderRangeFactor(double value);


public slots:
    void onModelChanged(const QModelIndex &first, const QModelIndex &second);
    void onCurrentLinkChanged(ItemLink link);

private:
    QModelIndex getMultiLayerIndex(const QString &name);

    QStandardItemModel *m_parameterModel;
    QTreeView *m_treeView;
    ModelTuningDelegate *m_delegate;
    SampleModel *m_sampleModel;
    InstrumentModel *m_instrumentModel;

    QString m_instrument_name;
    QString m_sample_name;

    QuickSimulationRunner *m_simulationRunner;

    bool m_update_in_progress;
};


#endif // MODELTUNINGWIDDGET_H
