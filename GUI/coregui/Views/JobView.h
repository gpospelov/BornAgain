#ifndef JOBVIEW_H
#define JOBVIEW_H

#include <QWidget>
#include <QString>

class JobModel;
class SimulationDataModel;
class RootCanvas;
class QListWidget;
class TH2D;

class JobView : public QWidget
{
    Q_OBJECT

public:
    JobView(SimulationDataModel *p_simulation_data_model, QWidget *parent = 0);
    virtual ~JobView() {}

public slots:
    void updateJobsAndGraphics();
    void updateGraphics();
    void onSelectionChanged();

private:
    void updateJobList();
    JobModel *getCurrentJobModel() const;
    void setJobSelection();
    SimulationDataModel *mp_simulation_data_model;
    RootCanvas *mp_canvas;
    QListWidget *m_joblist;
    QString m_current_job;
    TH2D *mp_cached_histo;
};

#endif // JOBVIEW_H
